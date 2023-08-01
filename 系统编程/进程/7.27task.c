#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#if 0
int main()
{
    pid_t child_pid = fork();

    if (child_pid == -1)
    {
        fprintf(stderr, "无法创建子进程\n");
        exit(1);
    }
    else if (child_pid == 0)
    {
        // 子进程
        printf("Hello ");
    }
    else
    {
        // 父进程
        wait(NULL); // 等待子进程结束
        printf("World\n");

        pid_t child2_pid = fork();

        if (child2_pid == -1)
        {
            fprintf(stderr, "无法创建子进程\n");
            exit(1);
        }
        else if (child2_pid == 0)
        {
            // 第二个子进程
            printf("start\n");
        }
        else
        {
            // 父进程
            wait(NULL); // 等待第二个子进程结束
            printf("End\n");
        }
    }

    return 0;
}
#endif

#if 1
int main(int argc, char argv[])
{
    pid_t pid = fork();

    int count = 1;
    char letter = 'a';

    if (pid == -1)
    {
        fprintf(stderr, "无法创建子进程.\n");
        exit(1);
    }
    else if (pid == 0)
    {
        while (count <= 26)
        {
            usleep(10000);
            printf("%d ", count++);
            fflush(stdout); // 刷新输出缓冲区，确保及时输出
            usleep(10000);
        }
    }
    else
    {
        while (letter <= 'z')
        {
            usleep(20000);
            printf("%c ", letter++);
            fflush(stdout); // 刷新输出缓冲区，确保及时输出
        }
        wait(NULL);
        printf("\n");
    }
    return 0;
}
#endif