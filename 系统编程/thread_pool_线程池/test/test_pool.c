#include "test_pool.h"
// 压栈的句柄函数
void handler(void *arg)
{
	// 解锁
	pthread_mutex_unlock(arg);
	printf("线程取消例程函数\n");
}

// 做任务的线程--删除任务节点
void *routine(void *arg)
{
	// 拿到线程池的初始化值
	thread_pool *pool = (thread_pool *)arg;
	// 定义任务链表指针
	struct task *p;
	// 执行任务是在这个里面---删除节点
	while (1)
	{
		// 线程取消例程函数
		pthread_cleanup_push(handler, (void *)&pool->lock);

		// 临界资源的操作---需要上锁
		pthread_mutex_lock(&pool->lock);

		// 如果当前线程池没有关闭，并且当前线程池没有任务做（有线程没有任务，池子是打开的）
		while (pool->waiting_tasks == 0 && !pool->shutdown)
		{
			// 那么就进去条件变量中睡觉。
			pthread_cond_wait(&pool->cond, &pool->lock); // 自动解锁
		}

		// 要是线程池关闭了，或者有任务做，这些线程就会运行到这行代码
		// 判断当前线程池是不是关闭了，并且没有等待的任务
		if (pool->waiting_tasks == 0 && pool->shutdown == true)
		{
			// 如果线程池关闭，又没有任务做
			// 线程那么就会解锁
			pthread_mutex_unlock(&pool->lock);

			// 线程走人
			pthread_exit(NULL);
		}

		// 执行任务
		p = pool->task_list->next;

		// 让头结点指向p的下一个节点
		pool->task_list->next = p->next;

		// 任务数 - 1
		pool->waiting_tasks--;

		// 解锁
		pthread_mutex_unlock(&pool->lock);

		// 删除线程取消例程函数
		pthread_cleanup_pop(0);

		// 设置线程不能响应取消
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

		// 执行这个p节点指向的节点的函数（执行任务）
		(p->do_task)(p->arg); // 等价于 运行了函数 eat(NULL)

		// 设置线程能响应取消
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

		// 释放p对应的空间
		free(p);
	}
	pthread_exit(NULL);
}

// 线程池的初始化
bool init_pool(thread_pool *pool, unsigned int threads_number)
{
	// 初始化互斥锁
	pthread_mutex_init(&pool->lock, NULL);

	// 初始化条件变量
	pthread_cond_init(&pool->cond, NULL);

	// 初始化线程池开关量
	pool->shutdown = false; // 0 代表开启线程池

	// 初始化线程池任务链表(单向链表)
	// 也就是初始化任务链表里面的链表头
	pool->task_list = malloc(sizeof(struct task));

	// 为存储线程ID申请空间
	pool->tids = malloc(sizeof(pthread_t) * MAX_ACTIVE_THREADS);
	// 判断空间申请是否成功
	if (pool->task_list == NULL || pool->tids == NULL)
	{
		perror("malloc memory error. ");
		return false;
	}
	// 为线程池任务队列的头结点的指针赋值为NULL
	pool->task_list->next = NULL;
	// 设置线程池最大的任务个数为 100
	pool->max_waiting_tasks = MAX_WAITING_TASKS;
	// 当前需要处理的任务数量
	pool->waiting_tasks = 0;
	// 初始化线程中线程的个数
	pool->active_threads = threads_number;
	// 根据自定义的线程的数量创建线程
	// 使用for循环循环创建
	for (int i = 0; i < pool->active_threads; i++)
	{
		// (void *)pool 表示将线程池的地址作为参数传递给线程函数。
		if (pthread_create(&((pool->tids)[i]), NULL, routine, (void *)pool) != 0)
		{
			perror("pthread_create error.");
			return false;
		}
	}

	// 返回链表的开关量
	return true;
}

// 添加任务节点
bool add_task(thread_pool *pool, void *(*do_task)(void *arg), void *arg)
{
	// 新建任务链表的节点
	struct task *new_task = malloc(sizeof(struct task));
	if (new_task == NULL)
	{
		perror("malloc new_task error.");
		return false;
	}
	// 初始化任务节点
	new_task->do_task = do_task;
	new_task->arg = arg;
	new_task->next = NULL;

	pthread_mutex_lock(&pool->lock);

	if (pool->waiting_tasks >= MAX_WAITING_TASKS)
	{
		// 解锁
		pthread_mutex_unlock(&pool->lock);

		fprintf(stderr, "too many tasks.\n");

		// 释放
		free(new_task);

		return false;
	}
	// 寻找任务队列中的最后一个节点
	struct task *tmp = pool->task_list;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	// 从循环中出来，tmp肯定是指向链表中最后一个节点

	// 让最后一个节点指向新的节点
	tmp->next = new_task;

	// 当前的需要处理的任务数 + 1
	pool->waiting_tasks++;

	// 添加完毕，解锁
	pthread_mutex_unlock(&pool->lock);

	// 唤醒条件变量中的一个线程来处理任务
	pthread_cond_signal(&pool->cond);

	return true;
}

// 添加线程
int add_thread(thread_pool *pool, unsigned additional_threads)
{
	// 如果添加的线程数为0
	if (additional_threads == 0)
		return 0;
	// 计算总共的线程数量
	unsigned total_threads = pool->active_threads + additional_threads;
	// 记录实际线程增加的数量
	int actual_increment = 0;
	// 创建线程
	
	for (int i = pool->active_threads; i < total_threads && i < MAX_ACTIVE_THREADS; i++)
	{
		if (pthread_create(&(pool->tids[i]), NULL, routine, (void *)pool) != 0)
		{
			perror("add threads error.");
			// 如果 actual_increment = 0 ，说明创建线程都失败了
			// 如果只是有几条失败，那就break；
			if (actual_increment == 0)
				return -1;
			break;
		}
		actual_increment++;
	}

	pool->active_threads += actual_increment; // 当前线程池线程个数 = 原来的个数 + 实际创建的个数
	// 返回实际的线程添加数
	return actual_increment;
}

// 删除线程
int remove_thread(thread_pool *pool, unsigned int removing_threads)
{
	// 如果删除的线程数为0
	if (removing_threads == 0)
		return pool->active_threads;

	int remaining_threads = pool->active_threads - removing_threads;
	// 将剩余的线程数量 `remaining_threads` 设置为至少为1，确保至少保留一个线程在线程池中。
	remaining_threads = remaining_threads > 0 ? remaining_threads : 1;
	// 删除从最后面一个线程号开始删除
	int i = 0;
	for (i = pool->active_threads - 1; i > remaining_threads - 1; i--)
	{
		if (pthread_cancel(pool->tids[i]) != 0)
		{
			perror("pthread_cancel tids:%d error.");
			break;
		}
	}

	if (i == pool->active_threads - 1) // 删除失败
	{
		return -1;
	}
	else // 删除成功
	{
		pool->active_threads = i + 1; // 当前实际线程个数
		return i + 1;				  // 返回还有多少个线程数
	}
}

// 销毁线程池
bool destroy_pool(thread_pool *pool)
{
	// 1. 设置线程池关闭标志为真
	pool->shutdown = true;

	// 广播
	pthread_cond_broadcast(&pool->cond); // 目的： 就是让线程退出！

	// 2. 接合所有的线程
	int i;
	for (i = 0; i < pool->active_threads; i++)
	{
		errno = pthread_join(pool->tids[i], NULL); // 阻塞等待所有的线程退出

		if (errno != 0)
		{
			printf("join tids[%d] error: %d\n",
				   i, strerror(errno));
		}

		else
			printf("[%u] is joined\n", (unsigned)pool->tids[i]);
	}

	// 3. 释放一些空间
	free(pool->task_list); // 释放链表
	free(pool->tids);	   // 释放线程数
	free(pool);			   // 释放线程池

	return true;
}
