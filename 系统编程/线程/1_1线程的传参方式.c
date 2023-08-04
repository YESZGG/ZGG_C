#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

/*
    编译的方法：gcc 2_pthread_create多线程.c -lpthread

说明：第三个参数不能是NULL
2_pthread_create多线程.c:12:5: warning: null argument where non-null required (argument 3) [-Wnonnull]
     int ret = pthread_create(&tid,NULL,NULL,NULL);
*/

// 返回值是void *类型 参数是只有一个形参void *
void *start_routine(void *arg)
{
    /*
        第一步：将void *---> int *
        第二步：解引用 *
    */
    // int num = *((int *)arg);
    // printf("收到主线程传来的参数:%d\n",num);
    printf("收到主线程传来的参数:%d\n", *((int *)arg));
    while (1)
    {
        printf("我要打野.....\n");
        sleep(1);
    }
}

void *fun(void *arg)
{
    /*
        第一步：将void *---> int *
        第二步：解引用 *
    */
    char num = *((char *)arg);
    printf("收到主线程传来的参数:%c\n", num);
    // printf("收到主线程传来的参数:%d\n",*((int *)arg));
}

void *fun2(void *arg)
{
    printf("[%s][%d]收到主线程传来的参数:%d\n", __FUNCTION__, __LINE__, *(int *)arg);
}

void *fun3(void *arg)
{
    printf("[%s][%d]收到主线程传来的参数:%s\n", __FUNCTION__, __LINE__, (char *)arg);
}

int main(int argc, char **argv)
{
    int ret = 0; // 作为函数的返回值重复使用
    /*
        传int类型的数据   &num---> int * --->强制转换为void
    */
    int num = 300; // 将num的值以void *类型传给子进程
    // 创建线程start_routine
    pthread_t tid;
    // ret = pthread_create(&tid, NULL, start_routine, (void *)&num); //建议初始的时候写这种
    ret = pthread_create(&tid, NULL, start_routine, &num); // ok int *是属于 void *中的一种 不会报警告
    if (ret != 0)
    {
        perror("pthread_create fail");
        return -1;
    }

    /*
        传char类型的数据   &num---> int * --->强制转换为void
    */
    char num1 = 'A'; // 将num的值以void *类型传给子进程
    pthread_t tid1;
    ret = pthread_create(&tid1, NULL, fun, (void *)&num1); // 建议初始的时候写这种
    // ret = pthread_create(&tid, NULL, fun, &num);  //ok int *是属于 void *中的一种 不会报警告
    if (ret != 0)
    {
        perror("pthread_create fail");
        return -1;
    }

    /*
        传指针类型的数据   &num---> int * --->强制转换为void
    */
    int num2 = 250; // 将num的值以void *类型传给子进程
    int *p = &num2;
    pthread_t tid2;
    ret = pthread_create(&tid2, NULL, fun2, (void *)p); // 建议初始的时候写这种
    if (ret != 0)
    {
        perror("pthread_create fail");
        return -1;
    }

    /*
        传字符串类型的数据   &num---> int * --->强制转换为void
    */
    char *str = "饿了 要吃饭";
    pthread_t tid3;
    ret = pthread_create(&tid3, NULL, fun3, (void *)str);
    if (ret != 0)
    {
        perror("pthread_create fail");
        return -1;
    }

    while (1)
    {
        printf("我要走中路.....\n");
        sleep(1);
    }

    return 0;
}


