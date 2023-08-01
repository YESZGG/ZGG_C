#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#if 0
int main()
{
    int fd[2];         // 用于存储管道的文件描述符
    char buffer[1024]; // 用于存储读取的数据
    pid_t pid;

    if (pipe(fd) == -1)
    {                       // 创建管道
        perror("pipe");     // 打印错误信息
        exit(EXIT_FAILURE); // 退出进程，表示执行失败
    }

    pid = fork(); // 创建子进程

    if (pid == -1)
    { // 出错处理
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {                 // 子进程
        close(fd[0]); // 关闭子进程中不需要的读取文件描述符

        char *message = "Hello from child process!";
        write(fd[1], message, strlen(message) + 1); // 写入数据到管道

        close(fd[1]); // 关闭写入文件描述符
        exit(EXIT_SUCCESS);
    }
    else
    {                 // 父进程
        close(fd[1]); // 关闭父进程中不需要的写入文件描述符
        
        read(fd[0], buffer, sizeof(buffer)); // 从管道读取数据
        printf("Received message from child: %s\n", buffer);

        close(fd[0]); // 关闭读取文件描述符
        wait(NULL);
        exit(EXIT_SUCCESS);
    }

    return 0;
}
#endif

#if 1 
// 无名管道通信
int main()
{
    int fd[2];
    char buffer[1024];
    pid_t pid;

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        close(fd[1]);

        while (1)
        {
            ssize_t bytesRead = read(fd[0], buffer, sizeof(buffer));

            if (bytesRead == -1)
            {
                perror("read");
                exit(EXIT_FAILURE);
            }
            else if (bytesRead == 0)
            {
                // 管道已关闭，子进程结束
                break;
            }
            else
            {
                printf("Received message from parent: %s\n", buffer);

                // 如果接收到 "exit"，子进程结束
                if (strcmp(buffer, "exit") == 0)
                {
                    break;
                }
            }
        }

        close(fd[0]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(fd[0]);

        while (1)
        {
            printf("Enter a message to send to child process (or enter 'exit' to quit): ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0'; // 去掉换行符

            write(fd[1], buffer, strlen(buffer) + 1);

            // 如果发送 "exit"，父进程等待子进程结束后退出
            if (strcmp(buffer, "exit") == 0)
            {
                wait(NULL);
                break;
            }
        }

        close(fd[1]);
        exit(EXIT_SUCCESS);
    }

    return 0;
}

#endif