#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/* 在程序的执行文件中，通常会包含以下几个段（section）：

1. .data 段（Data Segment）：.data 段存储已初始化的全局变量和静态变量的数据。这些变量在程序运行时具有固定的初始值，并且占用的空间在编译时就确定了。当程序加载到内存中时，.data 段被分配给对应的数据块。

2. .bss 段（Block Started by Symbol）：.bss 段存储未初始化的全局变量和静态变量。这些变量在程序运行时将被自动初始化为零值，因此在可执行文件中不需要存储它们的实际数据。.bss 段只保存变量的大小信息，而不占用实际存储空间，当程序加载到内存中时，操作系统会自动将 .bss 段的变量初始化为零。

3. .rodata 段（Read-Only Data Segment）：.rodata 段存储只读数据，例如字符串常量、常量数组等。这些数据在程序运行期间保持不变，因此被标记为只读。.rodata 段是只读的，防止程序在运行过程中修改这些数据。

4. .text 段（Text Segment）：.text 段存储程序的可执行指令（机器指令或汇编代码）。这些指令在程序执行过程中被逐条加载到 CPU 中执行。.text 段是只读的，以确保程序的指令不会在运行时被修改。

这些段在可执行文件中的布局以及在内存中的分配有助于实现数据和指令的有效组织、安全性和运行效率。它们有助于优化内存使用，提高程序执行效率，并确保数据的正确性和安全性。
 */
int val = 250;

// 线程例程，创建一条线程之后，去执行这个函数
void *start_routine(void *arg)
{
    int cnt = 2;
    while (cnt--)
    {
        printf("[%s][%d] :%d\n", __FUNCTION__, __LINE__, cnt);
        sleep(1);
    }

    // 子线程退出
    //  pthread_exit(&val); //全局变量----数据段中(.data/.bss/.rodata)
    pthread_exit("1");//字符串常量---- 数据段中的.rodata中
}

int main()
{
    // 创建一条线程
    int ret = 0;
    pthread_t thread;
    ret = pthread_create(&thread, NULL, start_routine, NULL);
    if (ret != 0)
    {
        perror("pthread_create fail");
        return -1;
    }

    int cnt = 3;
    while (cnt--)
    {
        printf("[%s][%d] :%d\n", __FUNCTION__, __LINE__, cnt);
        sleep(1);
    }

    // 等待子线程退出---阻塞等待子线程的退出（回收子线程资源）
    void *retval = NULL;
    pthread_join(thread, &retval);
    // printf("阻塞等待子线程[%lu]的退出 成功 退出值为:%d\n",thread,*(int*)retval);
    printf("阻塞等待子线程[%lu]的退出 成功 退出值为:%s\n", thread, (char *)retval);

    /*
        接收子线程退出值的特殊用法
    */
    char *val = (char *)retval;
    // if(返回值 == 1)
    // if (strcmp(val, "1") == 0)
    if(atoi(val)==1)
    {
        printf("处理其他事\n");
    }

    return 0;
}