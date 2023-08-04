#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

//线程例程，创建一条线程之后，去执行这个函数
void* start_routine(void *arg)
{   
    /*
        int pthread_setcanceltype(int type,int *oldtype);
        参数:
            type: PTHREAD_CANCEL_DEFERRED 延迟 取消状态 遇到一个取消点函数才会响应取消状态
                  PTHREAD_CANCEL_ASYNCHRONOUS 立即响应取消状态
            oldtype: 保存之前的状态，如果不关心，则填NULL     
        取消点函数 man 7 pthreads
        fprintf 、 fputc()、fputs()、sleep()、printf()、scanf() 
        相当于遇到 \n 会响应取消状态s
    */
    //延迟取消---默认状态
    // pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);

    //立即响应---(非默认状态)
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);

    while(1)
    {
        printf("start_routine\n");//取消点函数
        // sleep(1); //取消点函数
    }
} 

int main()
{
    //创建一条子线程
    pthread_t thread;
    pthread_create(&thread,NULL,start_routine,NULL);
    
    //给子线程发送一个取消请求
    pthread_cancel(thread);

    //等待子线程退出
    pthread_join(thread,NULL);
    
    return 0;
}