#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// 线程例程，创建一条线程之后，去执行这个函数
void *start_routine(void *arg)
{
    /*
        方法二：
        1.自己将自己设置为分离属性
        // 用pthread_self 函数来获取自己线程的ID号
        pthread_detach(pthread_self());
        2.用传参的方式来获取线程的ID号
        pthread_detach(*(pthread_t *)arg);
    */
    int cnt = 2;
    while (cnt--)
    {
        printf("[%s][%d] :%d\n", __FUNCTION__, __LINE__, cnt);
        sleep(1);
    }

    pthread_exit(NULL);

    // pthread_exit("1");
}

int main()
{
#if 0
    /*
        方法一：在创建子线程之前将分离属性添加到变量中
                创建的时候是带有分离属性
    */
    // 1）定义一个属性变量  -> 数据类型：pthread_attr_t
    pthread_attr_t attr;
    // 2）初始化属性变量。  -> pthread_attr_init()  -> man 3 pthread_attr_init
    pthread_attr_init(&attr);
    // 3）设置分离属性到属性变量中。//set(设置)detach(分离)state(状态) attr(attribute属性)
    // PTHREAD_CREATE_JOINABLE->非分离属性(默认状态)

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // 4)创建一条带有分离属性的线程
    pthread_t thread;
    pthread_create(&thread, &attr, start_routine, NULL);

    int cnt = 2;
    while (cnt--)
    {
        printf("[%s][%d] :%d\n", __FUNCTION__, __LINE__, cnt);
        sleep(1);
    }
    // 5）销毁属性变量
    // pthread_attr_destroy(&attr);
#endif

#if 1

    // 创建一条普通线程不具有分离属性
    pthread_t thread;
    if (pthread_create(&thread, NULL, start_routine, (void *)&thread) == -1)
    {
        perror("pthread_create fail.");
        return -1;
    }
    int cnt = 2;
    while (cnt--)
    {
        printf("[%s][%d] :%d\n", __FUNCTION__, __LINE__, cnt);
        sleep(1);
    }
    // // 等待子线程退出---阻塞等待子线程的退出（回收子线程资源）
    // void *retval = NULL;
    // pthread_join(thread, &retval);
    // printf("阻塞等待子线程[%lu]的退出 成功 退出值为:%s\n", thread, (char *)retval);
#endif

    while (1)
        ;

    return 0;
}