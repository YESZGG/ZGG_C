#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// 线程取消例程函数(注意：不要和线程函数混淆)
void routine(void *arg)
{
    printf("线程取消例程\n");
}

// 线程例程，创建一条线程之后，去执行这个函数
void *start_routine(void *arg)
{
    // 压栈
    pthread_cleanup_push(routine, NULL);

    int cnt = 5;
    while (cnt--)
    {
        printf("start_routine --- %d\n", cnt);
        sleep(1);
    }
    // 弹栈
    pthread_cleanup_pop(1); // 0不执行 非0才执行
}

int main()
{
    // 创建一条子线程
    pthread_t thread;
    pthread_create(&thread, NULL, start_routine, NULL);

    // sleep(5);
    // 给子线程发送一个取消请求
    // pthread_cancel(thread);

    // 等待子线程退出
    pthread_join(thread, NULL);

    return 0;
}