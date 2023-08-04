/*
 * @Description: 
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-08-03 16:54:56
 * @LastEditors: ZGG
 * @LastEditTime: 2023-08-03 19:44:39
 */
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

// 1）定义互斥锁变量   -> 数据类型： pthread_mutex_t
// pthread_mutex_t m;  //动态初始化

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; //静态初始化

int g_val = 0; // 全局变量---->共享资源（临界资源）

// 线程1的线程函数
void *start_routine1(void *arg)
{
    printf("%s start ...\n", __FUNCTION__);

    // 上锁---互斥锁
    pthread_mutex_lock(&m);

    g_val = 200;
    sleep(2);
    printf("start_routine1 g_val:%d\n", g_val);

    // 解锁---互斥锁
    pthread_mutex_unlock(&m);
    printf("%s end ...\n", __FUNCTION__);
}

// 线程2的线程函数
void *start_routine2(void *arg)
{
    printf("%s start ...\n", __FUNCTION__);

    // 上锁---互斥锁
    pthread_mutex_lock(&m);

    sleep(1);
    g_val = 400;
    printf("start_routine2 g_val:%d\n", g_val);

    // 解锁---互斥锁
    pthread_mutex_unlock(&m);
    printf("%s end ...\n", __FUNCTION__);
}

// 线程3 的 线程函数
void *start_routine3(void *arg)
{
    printf("%s start ...\n", __FUNCTION__);

    // 上锁---互斥锁
    pthread_mutex_lock(&m);

    sleep(1);
    g_val = 600;
    printf("start_routine3 g_val:%d\n", g_val);

    // 解锁---互斥锁
    pthread_mutex_unlock(&m);
    printf("%s end ...\n", __FUNCTION__);
}

int main()
{
    // 2）初始化互斥锁  -> pthread_mutex_init()
    // pthread_mutex_init(&m, NULL);

    // 创建一条子线程
    pthread_t thread1;
    pthread_create(&thread1, NULL, start_routine1, NULL);

    pthread_t thread2;
    pthread_create(&thread2, NULL, start_routine2, NULL);

    pthread_t thread3;
    pthread_create(&thread3, NULL, start_routine3, NULL);

    // 上锁---互斥锁
    pthread_mutex_lock(&m);
    g_val = 1000;
    printf("main g_val:%d\n", g_val);

    // 解锁---互斥锁
    pthread_mutex_unlock(&m);

    // 阻塞等待子线程退出，回收资源
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    // 销毁无名信号量
    pthread_mutex_destroy(&m);
}
