#include<stdio.h>
#include<pthread.h>
#include <unistd.h>

int pthread_status = 20;

//线程例程，创建一条线程之后，去执行这个函数
void* start_routine(void *arg)
{
    //子线程设置不响应取消请求 
    /* 
        int pthread_setcancelstate(int type,int *oldtype);
        参数：
            type: PTHREAD_CANCEL_DISABLE  不响应 pthread_cancel(thread)的取消请求
                  PTHREAD_CANCEL_ENABLE   响应   pthread_cancel(thread)的取消请求
    */
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    
    int cnt=0;
    while(1)
    {
        sleep(1);
        printf("start_routine:%lu cnt:%d\n",pthread_self(),cnt++); //pthread_self 打印自己的线程ID号
        
        if(cnt == 10)
        {
            //子线程设置 取消请求能响应 
            // pthread_setcancelstate(PTHREAD_CANCEL_ENABLE  , NULL);
        }
    }
} 

int main()
{
    //创建一条子线程
    pthread_t thread;
    pthread_create(&thread,NULL,start_routine,NULL);
    
    sleep(2);
    //给子线程发送一个取消请求
    pthread_cancel(thread);

    //等待子线程退出
    pthread_join(thread,NULL);
    
    return 0;
}