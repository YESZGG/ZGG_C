/*
 * @Description: 无名信号量+线程 防止数据践踏
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-08-03 15:52:39
 * @LastEditors: ZGG
 * @LastEditTime: 2023-08-03 16:04:41
 */


#include<stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>


//定义一个无名信号量变量 -- 建议设置为全局变量
sem_t g_sem;

int g_val = 0; //全局变量---->共享资源

//线程1的启动函数
void* start_routine1(void *arg)
{
    printf("%s start ...\n",__FUNCTION__);

    //在访问 共享资源之前，先看看有没有其他线程正在使用
    //无名信号量的P操作   
    //也就是说，能不能进行 -1 操作  如果能 则往下面 走
    //如果不能 ，则阻塞在这里
    sem_wait(&g_sem);

    g_val = 200; 
    sleep(2);
    printf("%s g_val:%d\n",__FUNCTION__,g_val);

    //当这个线程不再使用这个共享资源的时候，无名信号量 进行 V操作
    sem_post(&g_sem);

    printf("%s end!\n",__FUNCTION__);
}

//线程2的启动函数
void* start_routine2(void *arg)
{
    printf("%s start ...\n",__FUNCTION__);

    sem_wait(&g_sem);

    sleep(1);
    g_val = 400;
    printf("%s g_val:%d\n",__FUNCTION__,g_val);

    //当这个线程不再使用这个共享资源的时候，无名信号量 进行 V操作
    sem_post(&g_sem);
    printf("%s end!\n",__FUNCTION__);
}

//线程3 的 启动函数
void* start_routine3(void *arg)
{
    printf("%s start ...\n",__FUNCTION__);

    sem_wait(&g_sem);

    sleep(1);
    g_val = 600;
    printf("%s g_val:%d\n",__FUNCTION__,g_val);

    //当这个线程不再使用这个共享资源的时候，无名信号量 进行 V操作
    sem_post(&g_sem);
    printf("%s end!\n",__FUNCTION__);
}

int main()
{
    //2、初始化无名信号量 ---sem_init
    sem_init(&g_sem,0, 1);


    //创建线程
    pthread_t thread1;
    pthread_create(&thread1,NULL,start_routine1,NULL);

    pthread_t thread2;
    pthread_create(&thread2,NULL,start_routine2,NULL);

    pthread_t thread3;
    pthread_create(&thread3,NULL,start_routine3,NULL);


    // sem_wait(&g_sem);
    // g_val = 1000;
    // printf("main g_val:%d\n",g_val);

    // //当这个线程不再使用这个共享资源的时候，无名信号量 进行 V操作
    // sem_post(&g_sem);


    //阻塞等待子线程退出，回收资源
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);

    //销毁无名信号量
    sem_destroy(&g_sem);
}
