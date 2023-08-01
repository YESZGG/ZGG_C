#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
    无名管道：不需要open
    写--write   读--read
*/

int main()
{
    char buffer[1024];
    int fd[2];
    // 创建一个无名管道文件 ,创建成功之后 pipefd[0] 读端  pipefd[1] 写端
    pipe(fd);
    printf("fd[0]:%d fd[1]:%d\n", fd[0], fd[1]); // 文件描述符以及被标准输入、输出、出错占用，所以分配给 3、 4
    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // 创建一个子进程
    pid_t id = fork();

    if (id == -1) // 出错
    {
        printf("fork error\n");
        return -1;
    }
    else if (id > 0) // 父进程----->写fd[1]
    {
        close(fd[0]);
        while (1)
        {
            printf("Enter a message to send to child process(or enter 'exit' to quit):\n");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0'; // 去掉换行符

            write(fd[1], buffer, strlen(buffer) + 1);

            if (strcmp(buffer, "exit") == 0)
            {
                break;
            }
        }
        wait(NULL); // 阻塞等待子进程退出
        close(fd[1]);
        exit(0);
    }
    else if (id == 0) // 子进程 ---->读fd[0]
    {
        close(fd[1]);
        char buffer[1024] = {0};
        int ret = 0;
        while (1)
        {
            bzero(buffer, sizeof(buffer));
            ret = read(fd[0], buffer, sizeof(buffer));
            // 如果接收到 "exit"，子进程结束
            if (strcmp(buffer, "exit") == 0)
            {
                break;
            }
            printf("Received message from parent: %s  ret:%d\n", buffer, ret);
        }
        close(fd[0]);
        // 子进程正常退出
        exit(0);
    }
    return 0;
}
