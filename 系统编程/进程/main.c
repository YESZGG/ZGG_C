// main.c

#include <stdio.h> 
#include <unistd.h> 
#include <sys/wait.h> 

int main()
{
    // 子进程
    if(fork() == 0)
    {
        printf("加载新程序之前的代码\n");

        // 加载新程序，并传递参数3
        execl("./child", "./child", "3", NULL);

        printf("加载新程序之后的代码\n");
    }

    // 父进程
    else
    {
        // 等待子进程的退出
        int status;
        int ret = waitpid(-1, &status, 0);

        if(ret > 0)
        {
            if(WIFEXITED(status))
                printf("[%d]: 子进程[%d]的退出值是:%d\n",
                        getpid(), ret, WEXITSTATUS(status));
        }
        else
        {
            printf("暂无僵尸子进程\n");
        }
    }
}
