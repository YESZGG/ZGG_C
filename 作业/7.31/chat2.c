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

void signalHandle(int signum)
{
    printf("捕捉到%d子进程退出中.....\n", signum);
    int cnt = 3;
    while (cnt--)
    {
        sleep(1);
        fprintf(stderr, " ======= 原神，启动！%d =======%c", cnt, cnt == 0 ? '\n' : '\r');
    }
    printf("启动完成！\n");
}

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
        int fd = open(FIFO_FILE1, O_RDONLY);
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
        kill(getppid(),SIGKILL);
        exit(EXIT_SUCCESS);
        // 关闭管道
        close(fd);
    }
    else
    {
        sigset_t set;

        // 初始化信号集
        sigemptyset(&set);

        // 将SIGCHLD加入信号集
        sigaddset(&set, SIGCHLD);

        // 注册SIGCHLD信号处理函数
        signal(SIGCHLD, signalHandle);
        // 父进程 - 写入消息到管道
        int fd = open(FIFO_FILE2, O_WRONLY);
        if (fd == -1)
        {
            perror("Failed to open pipe");
            exit(EXIT_FAILURE);
        }
        char message[MAX_BUFFER_SIZE];

        // 输入聊天消息，输入"exit"退出
        while (1)
        {
            printf("请输入消息：");
            fgets(message, MAX_BUFFER_SIZE, stdin);
            message[strcspn(message, "\n")] = '\0'; // 去掉换行符

            // 写入消息到管道
            write(fd, message, strlen(message) + 1);

            // 检查是否接收到"exit"消息以结束聊天
            if (strcmp(message, "exit") == 0)
            {
                break;
            }
        }
        kill(pid,SIGKILL);
        wait(NULL);

        // 关闭管道并删除管道文件
        close(fd);
        unlink(FIFO_FILE2);
    }

    return 0;
}
