#include<stdio.h>
#include<pthread.h>
#include <unistd.h>

int pthread_status = 10;

//线程例程，创建一条线程之后，去执行这个函数
void* start_routine(void *arg)
{
    int cnt=30;
    while(cnt--)
    {
        sleep(1);
        printf("[%lu]start_routine cnt:%d\n",pthread_self(),cnt); //pthread_self 打印自己的线程ID号
    }

    pthread_exit(&pthread_status);
} 

int main()
{
    int  ret;
    //创建一条子线程
    pthread_t thread;
    ret = pthread_create(&thread,NULL,start_routine,NULL);
    if(ret != 0)
    {
        perror("pthread_create fail");
        return -1;
    }

    sleep(5);
    //给子线程发送一个取消请求
    pthread_cancel(thread);
    
    //等待子线程退出
    void *p = NULL;
    ret = pthread_join(thread,&p); // p = (void*)&pthread_status
    if (ret != 0)
    {
        printf("pthread_join error\n");
    }    
    printf("retval=%d",*(int *)p); //p没有被函数pthread_join分配空间,它还是NULL指针

    return 0;
}
