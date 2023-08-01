#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAX_BUFFER_SIZE 1024
#define FIFO_FILE1 "/home/gec/fifo1"
#define FIFO_FILE2 "/home/gec/fifo2"

int main()
{
    // 先判断文件是否存在，如果存在则不用创建了
    if (access(FIFO_FILE1, F_OK) == -1) // access 判断文件是否存在，如果不存在则返回 -1
    {
        // 所以是不存在的时候才进来创建
        if (mkfifo(FIFO_FILE1, 0777) == -1) // 创建一个有名管道文件
        {
            perror("mkfifo error");
            return -1;
        }
    }
    // 先判断文件是否存在，如果存在则不用创建了
    if (access(FIFO_FILE2, F_OK) == -1) // access 判断文件是否存在，如果不存在则返回 -1
    {
        // 所以是不存在的时候才进来创建
        if (mkfifo(FIFO_FILE2, 0777) == -1) // 创建一个有名管道文件
        {
            perror("mkfifo error");
            return -1;
        }
    }

    // fork()创建子进程
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("Failed to fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        // 子进程 - 读取管道中的消息
        int fd = open(FIFO_FILE2, O_RDONLY);
        if (fd == -1)
        {
            perror("Failed to open pipe");
            exit(EXIT_FAILURE);
        }
        char message[MAX_BUFFER_SIZE];

        // 从管道中读取消息，输入"exit"退出
        while (1)
        {
            // 读取管道中的消息
            ssize_t num_bytes = read(fd, message, MAX_BUFFER_SIZE);
            if (num_bytes == -1)
            {
                perror("Failed to read from pipe");
                exit(EXIT_FAILURE);
            }
            if (num_bytes == 0)
                break;

            printf("\n收到消息：%s\n", message);

            // 检查是否接收到"exit"消息以结束聊天
            if (strcmp(message, "exit") == 0)
                break;
        }

        // 关闭管道
        close(fd);
        exit(EXIT_SUCCESS);
    }
    else
    {
        // 父进程 - 写入消息到管道
        int fd = open(FIFO_FILE1, O_WRONLY);
        if (fd == -1)
        {
            perror("Failed to open pipe");
            exit(EXIT_FAILURE);
        }
        char message[MAX_BUFFER_SIZE];

        // 输入聊天消息，输入"exit"退出
        while (1)
        {
            memset(message, 0, sizeof(message));
            printf("请输入消息：");
            scanf("%s", message);
            // 写入消息到管道
            write(fd, message, strlen(message) + 1);

            // 检查是否输入"exit"以结束聊天
            if (strcmp(message, "exit") == 0)
            {
                break;
            }
        }
        
        // 等待子进程终止并获取退出状态
        int status;
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("Failed to wait for child process");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status))
        {
            printf("子进程正常退出，退出状态：%d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("子进程收到信号终止，信号编号：%d\n", WTERMSIG(status));
        }

        // 关闭管道并删除管道文件
        close(fd);
        unlink(FIFO_FILE1);
        exit(EXIT_SUCCESS);
    }

    return 0;
}
