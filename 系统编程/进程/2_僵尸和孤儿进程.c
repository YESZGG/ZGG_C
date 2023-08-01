#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#if 0
/*
    Zombie Process
僵尸进程（Zombie Process）是指一个子进程已经终止，但是其父进程还没有调用wait()或waitpid()等系统调用来获取该子进程的退出状态，
导致子进程的进程描述符仍然保留在系统进程表中，并且在进程表中的部分信息（如进程ID、退出状态等）仍然可见。
僵尸进程不会占用实际的内存空间，但会占用一个唯一的进程ID。

僵尸进程通常发生在一个子进程比父进程先退出的情况下。父进程应该负责回收子进程的资源和获取其退出状态，
但如果父进程没有处理僵尸进程，那么子进程就会成为僵尸进程。
*/


void create_zombie() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // 子进程
        printf("子进程正在执行\n");
        sleep(2);
        printf("子进程执行完毕\n");
    } else if (pid > 0) {
        // 父进程
        printf("父进程创建了子进程（PID: %d）\n", pid);
        sleep(5);  // 父进程暂停一段时间，不回收子进程资源
        
        // 此处应该调用 wait() 或 waitpid() 来获取子进程的退出状态，
        // 但在示例中省略了这一步，导致子进程成为僵尸进程
    } else {
        // fork() 失败
        fprintf(stderr, "无法创建子进程\n");
        exit(1);
    }
}

int main() {
    create_zombie();// 创建僵尸进程
    
    return 0;
}
#endif

#if 1
/*
    孤儿进程是指在父进程结束或被终止后，子进程仍然在运行的进程。
    这些子进程将被操作系统的init进程（PID为1）接管，并由它来完成子进程的资源回收。
*/
void create_orphan()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        // 子进程
        printf("子进程开始执行\n");
        printf("子进程的父进程ID：%d\n", getppid());
        sleep(5);
        printf("子进程执行完毕\n");
    }
    else if (pid > 0)
    {
        // 父进程
        printf("父进程开始执行\n");
        printf("父进程ID：%d\n", getpid());
        sleep(2);
        printf("父进程执行完毕\n");
        // 父进程终止，子进程成为孤儿进程
    }
    else
    {
        // fork() 失败
        fprintf(stderr, "无法创建子进程\n");
        exit(1);
    }
}

int main()
{
    create_orphan();

    return 0;
}

#endif
