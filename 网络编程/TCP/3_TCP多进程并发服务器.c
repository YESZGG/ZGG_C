/*
 * @Description: 
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-08-14 16:46:22
 * @LastEditors: ZGG
 * @LastEditTime: 2023-08-14 18:57:23
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SERVER_PORT 8888
#define SERVER_IP "192.168.1.148"

void handle(int arg)
{
    // 回收子进程的资源
    wait(NULL);
    // printf("回收子进程的资源:%d\n", arg);
}

int main()
{
    int sockfd, client_sock;

    // 创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    int reuseaddr = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr)) < 0)
    {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }
    // 2.配置服务器的IP地址和端口号  --- sockaddr_in 新结构体
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;                   // IPV4 网络协议
    server_addr.sin_port = htons(SERVER_PORT);          // 本机器端口号转化为网络段 host to net short
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP); // 本机IP转化为网络IP
    socklen_t addrlen = sizeof(struct sockaddr_in);

    // 绑定套接字
    if (bind(sockfd, (struct sockaddr *)&server_addr, addrlen) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听连接请求
    if (listen(sockfd, 3) < 0)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Listening on port %d...\n", SERVER_PORT);

    while (1)
    {
        struct sockaddr_in client_addr;
        socklen_t client_addrlen = sizeof(struct sockaddr_in);
        // 接受客户端连接
        client_sock = accept(sockfd, (struct sockaddr *)&client_addr, &client_addrlen);
        if (client_sock < 0)
        {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
        printf("Connection accepted from [IP:%s][PORT:%d]\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork fail");
            return -1;
        }
        else if (pid > 0) // 父进程
        {
            signal(SIGCHLD, handle); // 捕捉子进程退出信号
        }
        else // 子进程
        {
            char *ip = inet_ntoa(client_addr.sin_addr); // 将网络ip转换为本机ip
            int port = ntohs(client_addr.sin_port);     // 将网络端口转本机端口
            char buffer[1024] = {0};
            // 循环监控客户端数据
            while (1)
            {
                memset(buffer, 0, sizeof(buffer));
                // 接收
                if (recv(client_sock, buffer, sizeof(buffer), 0) == 0)
                {
                    printf("[IP:%s][PORT:%d] 客户端已下线.\n", ip, port);
                    break;
                }
                printf("[IP:%s][PORT:%d] recv :%s\n", ip, port, buffer);
            }
            // 关闭客户端套接字
            close(client_sock);
            exit(0);
        }
    }

    // 关闭服务器套接字
    close(sockfd);

    return 0;
}