/*
 * @Description: 多线程执行访问共同内存，造成数据践踏
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-08-03 15:04:40
 * @LastEditors: ZGG
 * @LastEditTime: 2023-08-03 15:11:08
 */
#include<stdio.h>
#include<pthread.h>
#include <unistd.h>

//全局变量-->共享变量
int g_val = 0;

//线程例程，创建一条线程之后，去执行这个函数
void* start_routine1(void *arg)
{
    g_val = 100;
    sleep(2);//延时2秒，此时线程2执行g_val = 200; 该变量的值已经被线程2改变了
    
    printf("start_routine1 g_val:%d\n",g_val);
    
    pthread_exit(NULL);
} 

//线程例程，创建一条线程之后，去执行这个函数
void* start_routine2(void *arg)
{
    sleep(1);//延时1秒，此时 线程1 执行 g_val = 100;
    g_val = 200;

    printf("start_routine2 g_val:%d\n",g_val);
    
    pthread_exit(NULL);
} 

int main()
{
    //创建一条子线程
    pthread_t thread1;
    pthread_create(&thread1,NULL,start_routine1,NULL);

    //创建一条子线程
    pthread_t thread2;
    pthread_create(&thread2,NULL,start_routine2,NULL);
    
    //等待子线程退出
    pthread_join(thread1,NULL); 
    
    return 0;
}