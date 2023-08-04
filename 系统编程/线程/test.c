
#if 0
#include <stdio.h>
int add(int a, int b) {
    return a + b;
}

int main() {
    // 声明一个函数指针
    int (*functionPtr)(int, int);

    // 将函数指针指向具体的函数
    functionPtr = add;

    // 使用函数指针调用函数
    int result = functionPtr(3, 4);

    printf("Result: %d\n", result);

    return 0;
}
#endif

#if 0
#include <stdio.h>
typedef int (*OperationFuncPtr)(int, int);

int add(int a, int b) {
    return a + b;
}

int main() {
    // 声明一个别名为 OperationFuncPtr 的函数指针
    OperationFuncPtr operation;

    // 将函数指针指向具体的函数
    operation = add;

    // 使用函数指针调用函数
    int result = operation(3, 4);

    printf("Result: %d\n", result);

    return 0;
}

#endif

#if 0
/* 验证一个进程可以创建多少条线程 */
#include <stdio.h>
#include <pthread.h>

#define MAX_THREAD_COUNT 1000000

void *thread_function(void *arg)
{
    // 任务逻辑
    // while (1)
    // {
    // }
    return NULL;
}

int main()
{
    pthread_t threads[MAX_THREAD_COUNT];
    int thread_count = 0;

    // 创建线程直到达到最大线程数量或创建失败为止
    while (thread_count < MAX_THREAD_COUNT && pthread_create(&threads[thread_count], NULL, thread_function, NULL) == 0)
    {
        printf("线程创建数量：%d\n",thread_count);
        thread_count++;
    }

    printf("最大线程数量：%d\n", thread_count);

    // 等待所有线程结束，实际运行时可以根据需要设置超时时间
    for (int i = 0; i < thread_count; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

#endif

#if 0
/*
练习3：
struct st
{
    char name[20];
    char sex;
    int height;
    float score;
}
使用线程将一个学生信息传递给子线程，然后在子线程中打印该学生的信息。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct st
{
    char name[20];
    char sex;
    int height;
    float score;
};

void *printStudent(void *arg)
{
    // 类型转化为结构体指针
    struct st *student = (struct st *)arg;
    printf("姓名：%s\n", student->name);
    printf("性别：%c\n", student->sex);
    printf("身高：%d\n", student->height);
    printf("分数：%-4.1f\n", student->score);

    return NULL;
}

int main()
{
    // 1.定义一个结构体变量
    struct st student;
    /*  // 定义就初始化
        struct st student ={"小明","M",180,90.5};
    */
    // 结果受到内存对齐的影响，结果为32字节
    printf("结构体大小：%ld 字节\n", sizeof(struct st));
    // 2.初始化结构体变量
    strcpy(student.name, "小明");
    student.sex = 'M';
    student.height = 180;
    student.score = 90.5;

    pthread_t tid;
    pthread_create(&tid, NULL, printStudent, (void *)&student);
    pthread_join(tid, NULL);

    return 0;
}

#endif

#if 0
#include <stdio.h>
#include <pthread.h>

int global_variable = 0; // 全局变量

void *thread_func(void *arg)
{
    int local_variable = 5; // 局部变量

    global_variable = 10; // 修改全局变量的值

    pthread_exit((void *)&local_variable); // 线程退出，返回局部变量的地址
}

int main()
{
    pthread_t thread;
    void *exit_value;

    pthread_create(&thread, NULL, thread_func, NULL);

    pthread_join(thread, &exit_value); // 等待线程结束并获取退出值

    printf("局部变量的退出值: %d\n", *((int *)exit_value));
    printf("全局变量的值: %d\n", global_variable);

    return 0;
}

#endif

#if 0
/* 
在一般情况下，分离属性的线程退出后，其资源会被系统自动回收，而主线程无法再对其进行接合（阻塞等待回收）。分离属性的线程是指该线程的资源在其退出时会立即被回收，不需要其他线程等待或进行回收操作。

当一个线程被设置为分离属性时，它的状态和资源将与主线程完全分离。一旦分离属性的线程完成其任务并终止，其相关资源会被系统回收，包括内存等。

因此，主线程在该线程退出后无法阻塞等待其回收，也无法对其执行任何操作。如果需要等待线程的完成或回收，应使用非分离属性的线程，并通过等待线程的 join() 方法来实现主线程的阻塞等待和资源回收。 
*/
/* 验证一个分离属性的线程退出，主线程还可不可以去阻塞等待回收它？ */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// 线程函数
void *threadFunction(void *arg)
{
    printf("子线程[%s]开始执行\n",__FUNCTION__);

    // 模拟子线程正在执行的操作
    sleep(3);

    printf("子线程执行完毕\n");

    return NULL;
}

int main()
{
    pthread_t thread;
    int result;

    // 创建分离属性的线程
    result = pthread_create(&thread, NULL, threadFunction, NULL);
    if (result != 0)
    {
        perror("线程创建失败");
        exit(EXIT_FAILURE);
    }

    // 设置线程为分离属性
    result = pthread_detach(thread);
    if (result != 0)
    {
        perror("线程设置分离属性失败");
        exit(EXIT_FAILURE);
    }

    printf("主线程继续执行\n");

    // 尝试接合线程（阻塞等待回收）
    result = pthread_join(thread, NULL);
    if (result != 0)
    {
        printf("尝试接合线程失败，返回值为：%d\n", result);
    }

    printf("主线程执行完毕\n");

    return 0;
}

#endif

#if 0
/*
 * @Description: 有一个进程，创建5个线程出来，每一个线程任务都是一样。  (使用无名信号量去处理同步互斥)
                 将"helloworld"字符串每隔1S打印一个字符。
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-08-03 15:52:39
 * @LastEditors: ZGG
 * @LastEditTime: 2023-08-03 16:02:22
 */
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>


//定义一个无名信号量变量 -- 建议设置为全局变量
sem_t g_sem;

char arr[]="HelloWorld";

//线程的启动函数
void* start_routine(void *arg)
{
    // printf("%s start ...\n",__FUNCTION__);
    int numsize = strlen(arr);
    //在访问 共享资源之前，先看看有没有其他线程正在使用
    //无名信号量的P操作   
    //也就是说，能不能进行 -1 操作  如果能 则往下面 走
    //如果不能 ，则阻塞在这里
    sem_wait(&g_sem);
    for (int i = 0; i < numsize; i++)
    {       
        sleep(1);
        printf("%c",arr[i]);
        fflush(stdout); // 刷新缓冲区
    }
    //当这个线程不再使用这个共享资源的时候，无名信号量 进行 V操作
    sem_post(&g_sem);

    pthread_exit(0);
    // printf("%s end!\n",__FUNCTION__);
}


int main()
{
    //2、初始化无名信号量 ---sem_init
    sem_init(&g_sem,0, 1);

    pthread_t thread[5];
    //创建线程
    for(int i = 0; i < 5;i++)
    {
        pthread_create(&thread[i],NULL,start_routine,NULL);
    }

    //阻塞等待子线程退出，回收资源
    for (int i = 0; i < 5; i++)
    {
        pthread_join(thread[i],NULL);
    }
    printf("\n");

    //销毁无名信号量
    sem_destroy(&g_sem);
}

#endif

#if 0
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

char arr[]="HelloWorld";

//线程的启动函数
void* start_routine(void *arg)
{

    int numsize = strlen(arr);

    for (int i = 0; i < numsize; i++)
    {       
        sleep(1);
        printf("%c",arr[i]);
        fflush(stdout); // 刷新缓冲区
    }


    pthread_exit(0);

}


int main()
{
    pthread_t thread[5];
    //创建线程
    for(int i = 0; i < 5;i++)
    {
        pthread_create(&thread[i],NULL,start_routine,NULL);
    }

    //阻塞等待子线程退出，回收资源
    for (int i = 0; i < 5; i++)
    {
        pthread_join(thread[i],NULL);
    }
    printf("\n");


}
#endif

#if 1
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define N 5
int array[N][N] = {{10, 20, 30, 40, 50},
                   {11, 22, 33, 44, 55},
                   {66, 77, 88, 99, 11},
                   {12, 31, 12, 34, 45},
                   {12, 43, 45, 66, 77}};

int total = 0;
pthread_mutex_t mutex;

void *threadFunction(void *arg)
{
    int row = *(int *)arg;
    int sum = 0;

    for (int i = 0; i < N; ++i)
    {
        sum += array[row][i];
    }
    printf("计算第%d行 sum:%d \n", row, sum);
    pthread_mutex_lock(&mutex);   // 上锁
    total += sum;                 // 累加到全局变量
    pthread_mutex_unlock(&mutex); // 解锁

    pthread_exit(NULL);
}

int main()
{
    const int NUM_THREADS = N;
    pthread_t threads[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL); // 初始化互斥锁

    // 创建线程，每个线程负责一行元素的求和
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        int *row = malloc(sizeof(int));
        *row = i;

        pthread_create(&threads[i], NULL, threadFunction, row);
    }

    // 等待线程结束
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex); // 销毁互斥锁

    printf("Total sum: %d\n", total);

    return 0;
}

#endif
