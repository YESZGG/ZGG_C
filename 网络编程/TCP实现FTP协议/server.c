#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define SERVER_IP "192.168.1.148"

const char *get_formatted_time(int type);

// 线程函数，用于接收文件内容并保存到服务器上的文件中
void *receiveFileContent(void *sockfd)
{
    int clientSockfd = *(int *)sockfd;
    char buffer[BUFFER_SIZE];

    // 接收文件名
    ssize_t filenameLength = recv(clientSockfd, buffer, BUFFER_SIZE - 1, 0);
    if (filenameLength == -1)
    {
        perror("接收文件名出错");
        exit(1);
    }
    buffer[filenameLength] = '\0';
    // 将文件名解析，读取最后一个' / '之后的字符串
    FILE *file;
    char *filenamePtr = strrchr(buffer, '/');
    if (filenamePtr != NULL)
    {
        // 提取文件名并创建新文件
        filenamePtr++; // 移动指针到文件名起始位置（去除 '/'）
        file = fopen(filenamePtr, "w");
    }
    else
    {
        // 在当前目录下创建文件
        file = fopen(buffer, "w");
    }

    if (file == NULL)
    {
        perror("文件打开失败");
        exit(1);
    }

    // 接受客户端发送的文件大小
    long file_size = 0; // file_size占8个字节
    ret = recv(scoket_client, &file_size, sizeof(long), 0);
    printf("[%s] 接收文件大小:%d 成功.", get_formatted_time(2), file_size, );
    ssize_t bytesRead;

    while ((bytesRead = recv(clientSockfd, buffer, BUFFER_SIZE, 0)) > 0)
    {
        // 写入数据块到文件
        if (fwrite(buffer, 1, bytesRead, file) < bytesRead)
        {
            perror("写入数据块出错");
            exit(1);
        }
    }

    fclose(file);
    printf("文件接收完成\n");

    close(clientSockfd);
    pthread_exit(NULL);

    return NULL;
}

int main()
{
    // 创建TCP socket
    int serverSockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSockfd < 0)
    {
        perror("创建socket失败");
        exit(1);
    }

    // 输入服务器的端口号
    unsigned short serverPort;
    printf("Enter the server port: ");
    scanf("%hu", &serverPort);

    // 设置服务器地址和端口
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(serverPort);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 绑定socket到指定的IP地址和端口号
    if (bind(serverSockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("绑定socket出错");
        exit(1);
    }

    // 监听连接请求
    if (listen(serverSockfd, 5) < 0)
    {
        perror("监听连接请求失败");
        exit(1);
    }

    while (1)
    {
        printf("等待客户端连接...\n");

        // 接受客户端连接
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientSockfd = accept(serverSockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSockfd < 0)
        {
            perror("接受客户端连接失败");
            exit(1);
        }

        printf("[IP:%s][PORT:%d] 客户端已连接\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

        // 创建一个线程来接收文件内容并保存
        pthread_t receiveThread;
        if (pthread_create(&receiveThread, NULL, receiveFileContent, (void *)&clientSockfd) != 0)
        {
            perror("创建接收线程失败");
            exit(1);
        }

        if (pthread_join(receiveThread, NULL) != 0)
        {
            perror("等待接收线程失败");
            exit(1);
        }

        // 分离线程，使其自动释放资源
        // if (pthread_detach(receiveThread) != 0)
        // {
        //     perror("分离线程失败");
        //     exit(1);
        // }
    }

    // 关闭socket
    close(serverSockfd);

    return 0;
}

// 获取时间，传入type来获取各种时间
const char *get_formatted_time(int type)
{
    time_t current_time;
    struct tm *time_info;

    time(&current_time);
    time_info = localtime(&current_time);

    static char formatted_time[20] = {};

    if (type == 0)
    {
        snprintf(formatted_time, sizeof(formatted_time), " ");
    }
    else if (type == 1)
    {
        snprintf(formatted_time, sizeof(formatted_time), "%04d-%02d-%02d",
                 (1900 + time_info->tm_year), (1 + time_info->tm_mon), time_info->tm_mday);
        // 年  月  日
    }
    else if (type == 2)
    {
        snprintf(formatted_time, sizeof(formatted_time), "%04d-%02d-%02d %02d:%02d:%02d",
                 (1900 + time_info->tm_year), (1 + time_info->tm_mon), time_info->tm_mday,
                 time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
        // 年  月  日  时  分  秒
    }
    // else if (type == 3)
    // {
    //     snprintf(formatted_time, sizeof(formatted_time), "%04d-%02d-%02d_%02d:%02d:%02d",
    //              (1900 + time_info->tm_year), (1 + time_info->tm_mon), time_info->tm_mday,
    //              time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
    // }
    else
    {
        // Handle invalid type here (e.g., set default value for formatted_time)
    }

    return formatted_time;
}