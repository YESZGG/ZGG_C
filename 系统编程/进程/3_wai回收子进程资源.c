#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#if 0
// 情况1 ： 父进程的运行时间比子进程的运行时间长
int main()
{
    printf("main id:%d\n", getpid());
    // 创建一条子进程id1
    pid_t id1 = fork();
    if (id1 > 0) // 父进程
    {
        // wait(NULL); //如果wait放在这里 它会一直阻塞等待子进程退出

        int cnt = 10;
        while (cnt--)
        {
            sleep(1);
            printf("父进程 id:%d 当前正在执行任务:%d\n", getpid(), cnt);
        }
        // 父进程主动回收子进程的资源
        wait(NULL);
    }
    else if (id1 == 0) // 子进程1
    {
        /*
            5秒之后结束
        */
        int cnt = 5;
        while (cnt--)
        {
            printf("子进程1:%d----%d\n", getpid(),cnt);
            sleep(1);
        }
        printf("子进程1 退出...\n");
    }

    return 0;
}
#endif

// 情况2 ： 父进程的运行时间比子进程的运行时间短
int main()
{
    printf("main id:%d\n", getpid());
    // 创建一条子进程id1
    pid_t id1 = fork();
    if (id1 > 0) // 父进程
    {
        // wait(NULL); //如果wait放在这里 它会一直阻塞等待子进程退出

        int cnt = 5;
        while (cnt--)
        {
            sleep(1);
            printf("父进程 id:%d 当前正在执行任务:%d\n", getpid(), cnt);
        }
        // 父进程主动回收子进程的资源 只要用了wait(NULL);那么父进程一定会比子进程后退出
        wait(NULL);
        printf("父进程 退出 ...\n");
    }
    else if (id1 == 0) // 子进程1
    {
        /*
            10秒之后结束
        */
        int cnt = 10;
        while (cnt--)
        {
            printf("子进程1:%d----%d\n", getpid(),cnt);
            sleep(1);
        }
        printf("子进程1 退出...\n");
    }

    return 0;
}