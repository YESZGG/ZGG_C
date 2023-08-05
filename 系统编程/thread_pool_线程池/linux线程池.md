## 一、分析线程池文件
pool_test/  -> 线程池的源码
        thread_pool.c  -> 线程池函数接口源码  -> 待会主要分析这个文件
		thread_pool.h  -> 线程池函数声明、线程池结构体..
		main.c   -> 简单应用。
线程池接口设计说明书.doc  -> 详细说明了线程池中函数的用法。

## 二、线程池实现过程。
#### 1、 什么是线程池？
线程池就是多个线程组合起来的一个集合，就好像一家公司，由多个员工组成的一个集合。当有任务时，这些线程就会去处理这些任务，当没有任务时，线程就会休息。

#### 2、 如何来描述一个线程池？  -> 使用一个结构体。
```c
typedef struct thread_pool
{
	pthread_mutex_t lock;    -> 互斥锁
	pthread_cond_t  cond;    -> 条件变量
	bool shutdown;		 -> 当前线程池的标志位  true -> 线程池关闭了，  false  -> 线程池没有关闭。
	struct task *task_list;  -> 任务队列的头节点
	pthread_t *tids;         -> 储存所有线程的ID号
	unsigned max_waiting_tasks;  -> 最大等待任务的数目
	unsigned waiting_tasks;	     -> 当前正在等待处理的任务的个数//链表中有多少个结点，每个结点就是一个任务，也就是当前有多少个任务
	unsigned active_threads;     -> 活跃的线程个数 //表示当前线程池里面有多少条线程
	
}thread_pool;

//任务队列 的结点数据类型---- 也就是说 任务结构体的数据类型
struct task
{
	/* 数据域 */
	void *(*do_task)(void *arg); //函数指针 -> 这个任务需要执行的函数，这个函数必须是: void *fun(void *arg)
	void *arg;  --> 传递给执行的函数的参数

	/* 指针域 */
	struct task *next;  -> 指向下一个任务节点的指针。
};
```
##### 3.1、 如何实现初始化？  -> init_pool() 
```c
	bool init_pool(thread_pool *pool, unsigned int threads_number)
	{
		//1. 初始化线程池互斥锁
		pthread_mutex_init(&pool->lock, NULL);
		
		//2. 初始化条件变量
		pthread_cond_init(&pool->cond, NULL);

		//3. 初始化标志位为false，代表当前线程池正在运行。
		pool->shutdown = false;
		
		//4. 初始化任务队列的头节点
		pool->task_list = malloc(sizeof(struct task));
		
		//5. 为储存线程ID号申请空间。
		pool->tids = malloc(sizeof(pthread_t) * MAX_ACTIVE_THREADS);

		//第4步与第5步错误判断
		if(pool->task_list == NULL || pool->tids == NULL)
		{
			perror("allocate memory error");
			return false; //初始化线程池失败
		}

		//6. 为线程池任务队列的头节点的指针域赋值NULL
		pool->task_list->next = NULL; //单向链表
		
		//7. 设置线程池最大任务个数为1000
		pool->max_waiting_tasks = MAX_WAITING_TASKS;
		
		//8. 当前需要处理的任务为0
		pool->waiting_tasks = 0;
		
		//9. 初始化线程池中线程的个数
		pool->active_threads = threads_number;

		//10. 创建线程
		int i;
		for(i=0; i<pool->active_threads; i++)
		{
			// (void *)pool 表示将线程池的地址作为参数传递给线程函数。
			if(pthread_create(&((pool->tids)[i]), NULL,routine, (void *)pool) != 0)
			{
				perror("create threads error");
				return false;
			}
		}

		//11. 线程池初始化成功
		return true;
}
```
总结：初始化线程池函数其实就是给线程池的结构体赋值，将一些变量赋初值，以及初始化变量，为指针申请空间。

##### 3.2 如何添加任务呢？  ->  add_task()
```c
bool add_task(thread_pool *pool,void *(*do_task)(void *arg), void *arg)
{
	//1. 为新任务的节点申请空间
	struct task *new_task = malloc(sizeof(struct task));
	if(new_task == NULL)
	{
		perror("allocate memory error");
		return false;
	}
	
	//2. 为新节点的数据域与指针域赋值
	new_task->do_task = do_task;  // 将传入的任务执行函数 do_task赋值给新任务节点 do_task成员
	new_task->arg = arg; // 将传入的任务参数 arg 赋值给新任务节点 arg成员
	new_task->next = NULL;  
	
	//3.  在添加任务之前，必须先上锁，因为添加任务属于访问临界资源 -> 任务队列
	pthread_mutex_lock(&pool->lock);
	
	//4. 如果当前需要处理的任务个数>=1000
	if(pool->waiting_tasks >= MAX_WAITING_TASKS)
	{
		//解锁
		pthread_mutex_unlock(&pool->lock);
		
		//打印一句话提示一下，太多任务了
		fprintf(stderr, "too many tasks.\n");
		
		//释放掉刚刚准备好的新节点
		free(new_task);

		return false;
	}
	
	//5. 寻找任务队列中的最后一个节点(尾插)
	struct task *tmp = pool->task_list;
	while(tmp->next != NULL)
		tmp = tmp->next;
	//从循环中出来时，tmp肯定是指向最后一个节点
	
	//6. 让最后一个节点的指针域指向新节点
	tmp->next = new_task;
	
	//7. 当前需要处理的任务+1
	pool->waiting_tasks++;

	//8. 添加完毕，就解锁。
	pthread_mutex_unlock(&pool->lock);

	//9. 唤醒条件变量中的一个线程起-来做任务(单播)
	pthread_cond_signal(&pool->cond);
	
	return true;
}
```
总结： 插入一个新节点到任务队列的末尾，唤醒条件变量中的一个线程起来做任务。
###### 为什么需要pthread_cond_signal(&pool->cond)？？
唤醒条件变量中的一个线程是为了确保线程池中的线程能够立即获取到新添加的任务并执行。
在线程池中，多个线程可能同时等待着条件变量上的信号，一旦有新任务添加到任务队列中，通过调用 pthread_cond_signal() 函数唤醒其中一个线程，这个线程将被激活并开始执行任务。

这样做的好处是能够高效地利用线程资源。如果不唤醒任何线程，新添加的任务将一直等待，直到有线程主动获取到任务并执行。
而通过唤醒一个线程，可以尽快启动任务的执行，避免任务等待的时间过长，提高任务处理的响应速度。

**需要注意的是，由于线程池中的线程可能是并行执行的，因此唤醒一个线程并不意味着一定是这个线程来执行新任务。具体是哪个线程来执行任务是不确定的，取决于操作系统和线程调度器的策略。所以在代码中使用“单播”，唤醒条件变量上的一个线程进行任务处理。**

##### 3.3 线程例程函数  -> void *routine(void *arg)
```c
void *routine(void *arg)
{
	//1. 先接收线程池的地址
	thread_pool *pool = (thread_pool *)arg;
	// 定义任务链表指针
	struct task *p;

	while(1)
	{
		//2. 线程取消例程函数
		//将来要是有人要取消我，由于已经上了锁，所以定义的线程取消例程函数，请先把锁解开，然后再响应取消。
		pthread_cleanup_push(handler, (void *)&pool->lock);
		
		//3. 上锁
		pthread_mutex_lock(&pool->lock);
		
		//如果当前线程池没有关闭，并且当前线程池没有任务做（有线程没有任务，池子是打开的）
		while(pool->waiting_tasks == 0 && !pool->shutdown)
		{
			//那么就进去条件变量中睡觉。
			pthread_cond_wait(&pool->cond, &pool->lock); //自动解锁
		}
		
		//要是线程池关闭了，或者有任务做，这些线程就会运行到这行代码
		//判断当前线程池是不是关闭了，并且没有等待的任务
		if(pool->waiting_tasks == 0 && pool->shutdown == true)
		{	
			//如果线程池关闭，又没有任务做
			//线程那么就会解锁
			pthread_mutex_unlock(&pool->lock);	
			
			//线程走人
			pthread_exit(NULL); 
		}
		
		//能运行到这里，说明有任务做  （删除节点）
		//p指向头节点的下一个
		p = pool->task_list->next;
		
		//让头节点的指针域指向p的下一个节点
		pool->task_list->next = p->next;
		
		//当前任务个数-1
		pool->waiting_tasks--;

		//解锁
		pthread_mutex_unlock(&pool->lock);
		
		//删除线程取消例程函数
		pthread_cleanup_pop(0);
		
		//设置线程不能响应取消
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL); 
		
		//执行这个p节点指向的节点的函数（执行任务）
		(p->do_task)(p->arg);  //等价于 运行了函数 eat(NULL)
		
		//设置线程能响应取消
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

		//释放p对应的空间
		free(p);
	}

	pthread_exit(NULL);
}
```
总结：线程去任务队列中拿一个节点出来，就执行该任务(过程不能被取消)，如果没有任务做，就去睡觉。

首先，将传入的参数 arg 视为线程池的地址，并进行类型转换，赋值给 pool。
进入一个无限循环，在循环体内执行以下操作：
1. 使用 pthread_cleanup_push() 函数注册一个线程取消例程函数 handler，该函数会在线程取消时被调用。同时，将互斥锁 pool->lock 
   的地址作为参数传递给取消例程函数。
2. 使用 pthread_mutex_lock() 函数对互斥锁 pool->lock 上锁，这是为了保证线程安全。
3. 当前线程池没有关闭且没有待处理任务时，线程会进入条件变量等待状态，等待条件变量 pool->cond 的信号通知。在等待期间，互斥锁会被自
   动解锁，以允许其他线程对资源进行操作。
4. 如果线程池已关闭且没有待处理任务，则线程会解锁互斥锁并退出线程。
5. 如果存在待处理任务，线程会执行以下操作：
    *   将头节点的下一个节点赋值给 p，即获取待处理任务节点。
	*	更新头节点的指针域，使其指向 p 的下一个节点，相当于从任务队列中删除了该任务节点。
	*	减少等待任务数 pool->waiting_tasks 的计数。
	*	解锁互斥锁。
	*	使用 pthread_cleanup_pop() 函数移除先前注册的线程取消例程函数。
	*	使用 pthread_setcancelstate() 函数将线程设置为不响应取消状态，以确保任务的完整执行。
	*	执行任务节点 p 的任务函数 p->do_task(p->arg)。这里假设任务函数是 eat()，参数是 NULL。
	*	使用 pthread_setcancelstate() 函数将线程重新设置为可以响应取消状态。
	*	释放任务节点 p 的内存空间。
6. 当退出循环后，使用 pthread_exit() 函数退出线程。


##### 3.5 添加线程  -> add_thread()  
```c
int add_thread(thread_pool *pool, unsigned additional_threads)
{
	//如果说你想添加0条，则直接返回0。
	if(additional_threads == 0)
		return 0; 

	unsigned total_threads = pool->active_threads + additional_threads;
			 //total_threads = 原本 2条 + 现在再加2条
						
	int i, actual_increment = 0;
	
	// i = 2 ; i<4 && i<20; i++
	/* 
		i 小于总共需要创建的线程数 total_threads 且同时小于线程池支持的最大活跃线程数 MAX_ACTIVE_THREADS。
		这个条件确保了循环不会超过线程池的承载能力 
	*/
	for(i = pool->active_threads; i < total_threads && i < MAX_ACTIVE_THREADS;  i++) 
	{
		if(pthread_create(&((pool->tids)[i]),NULL, routine, (void *)pool) != 0)
		{
			perror("add threads error");
			if(actual_increment == 0) 
				return -1;

			break;
		}
		actual_increment++;  //真正创建线程的条数
	}

	pool->active_threads += actual_increment; //当前线程池线程个数 = 原来的个数 + 实际创建的个数
	
	return actual_increment; //返回真正创建的个数
}
```
总结： 根据用户的需要去创建线程，但是不能超过20条。

1. 首先，判断要添加的额外线程数量是否为0，如果是则直接返回0，表示没有添加新线程。

2. 计算总共的线程数量：将原有的活跃线程数量 `active_threads` 与要添加的额外线程数量 `additional_threads` 相加得到总共的线程数量 `total_threads`。

3. 使用循环来创建新的线程（最多不超过 `MAX_ACTIVE_THREADS`），循环变量 `i` 从当前活跃线程数量开始递增。

4. 在循环中，使用 `pthread_create()` 函数创建新的线程，并将线程执行函数 `routine` 和线程池指针 `pool` 作为参数传入。

5. 如果创建线程失败，打印错误信息并检查是否有成功创建的线程（即 `actual_increment` 变量是否为0）。如果没有成功创建的线程，则返回-1表示添加线程失败。

6. 每次成功创建一个新线程，`actual_increment` 计数器增加1，用来记录实际创建的线程数量。

7. 更新线程池的 `active_threads` 变量，将其增加 `actual_increment`，表示当前活跃线程数量为原有数量加上实际创建的线程数量。

8. 返回实际创建的线程数量 `actual_increment`。

总之，这段代码通过循环创建指定数量的新线程，并将其添加到线程池中。最后返回成功创建的线程数量。

##### 3.5 删除线程  -> remove_thread()
```c
int remove_thread(thread_pool *pool, unsigned int removing_threads)
{
	//1. 如果你想删0条，直接返回。
	if(removing_threads == 0)
		return pool->active_threads;  //返回当前剩余的线程数

	int remaining_threads = pool->active_threads - removing_threads;
	//            3         =            5         -  2
	//	      0		=	     5         -  5
	//           -3         =            5         -  8

	// 将剩余的线程数量 `remaining_threads` 设置为至少为1，确保至少保留一个线程在线程池中。
	remaining_threads = remaining_threads > 0 ? remaining_threads : 1;

	int i;  
	for(i = pool->active_threads-1; i > remaining_threads-1; i--)
	{	
		errno = pthread_cancel(pool->tids[i]); //取消这些线程
		if(errno != 0)
			break;
	}

	if(i == pool->active_threads-1) //删除失败
		return -1;
	else
	{
		pool->active_threads = i+1; //当前实际线程个数
		return i+1; 
	}
}
```
总结： 根据用户需要，去取消掉一些线程，但是线程池中线程不能小于1条。

1. 首先，判断要删除的线程数量是否为0，如果是，则直接返回当前线程池中的活跃线程数量 `pool->active_threads`，表示没有删除任何线程。

2. 计算剩余的线程数量：将当前线程池中的活跃线程数量 `pool->active_threads` 减去要删除的线程数量 `removing_threads`，得到剩余的线程数量 `remaining_threads`。

3. 将剩余的线程数量 `remaining_threads` 设置为至少为1，确保至少保留一个线程在线程池中。

4. 使用循环逆序遍历从最后一个活跃线程开始到剩余线程数量为止。

5. 在循环中，使用 `pthread_cancel()` 函数取消线程池中的线程，使用线程ID `pool->tids[i]`。

6. 如果取消线程出错（`errno != 0`），则跳出循环。

7. 检查循环结束后的索引变量 `i` 是否等于 `pool->active_threads-1`，如果相等，表示删除失败，返回-1。

8. 否则，更新线程池的 `active_threads` 变量为 `i+1`，返回当前实际的线程数量。

总之，这段代码通过循环逆序删除指定数量的线程，并更新线程池中的活跃线程数量。最后返回成功删除的线程数量，如果删除失败则返回-1。

##### 3.6 销毁线程池。  -> destroy_pool() 
```c
bool destroy_pool(thread_pool *pool)
{
	//1. 设置线程池关闭标志为真
	pool->shutdown = true; 
	
	//广播
	pthread_cond_broadcast(&pool->cond);  //目的： 就是让线程退出！
	
	//2. 接合所有的线程
	int i;
	for(i=0; i<pool->active_threads; i++)
	{
		errno = pthread_join(pool->tids[i], NULL);  //阻塞等待所有的线程退出

		if(errno != 0)
		{
			printf("join tids[%d] error: %s\n",
					i, strerror(errno));
		}
	
		else
			printf("[%u] is joined\n", (unsigned)pool->tids[i]);
		
	}

	//3. 释放一些空间
	free(pool->task_list); //释放链表
	free(pool->tids); //释放线程数
	free(pool);//释放线程池

	return true;
}
```
总结： 唤醒所有的小孩，让小孩走人。

首先，它将线程池的关闭标志 `shutdown` 设置为 `true`，表示要关闭线程池。

然后，使用 `pthread_cond_broadcast` 函数广播条件变量 `cond`，目的是唤醒所有等待在条件变量上的线程，让它们退出。

接下来，使用循环遍历线程池中的活跃线程，并通过 `pthread_join` 函数阻塞等待每个线程退出。这里使用 `pthread_join` 是为了确保在销毁线程池之前，所有的线程都已经退出。

在循环中，如果 `pthread_join` 函数返回值不为0，说明出现了错误，会打印错误信息。

如果 `pthread_join` 函数返回值为0，表示成功地等待并加入了一个线程。会打印相应的消息。

最后，在释放资源之前，使用 `free` 函数释放线程池的任务列表、线程ID数组和线程池结构体本身。

最后，返回 `true` 表示线程池销毁成功。

这段代码的作用是关闭正在运行的线程池，并等待所有线程退出后释放相应资源。