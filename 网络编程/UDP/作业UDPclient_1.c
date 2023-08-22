/*
 * @Description: 
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-08-14 21:06:00
 * @LastEditors: ZGG
 * @LastEditTime: 2023-08-15 08:29:48
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

#define MY_PORT 9999
#define MY_IP "192.168.1.148"

#define SERVER_IP "192.168.1.148"
#define SERVER_PORT 8888

void error_handling(const char *message);

int main(void)
{
    int client_sock;
    struct sockaddr_in server_addr;
    socklen_t server_addr_size;
    char message[BUF_SIZE];
    // 创建客户端套接字
    client_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_sock == -1)
        error_handling("socket() error");

    int optval = 1;
    setsockopt(client_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MY_PORT);
    my_addr.sin_addr.s_addr = inet_addr(MY_IP);
    bind(client_sock, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_in));
    // 设置服务器地址信息
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);

    while (1)
    {
        memset(message,0,sizeof(message));
        printf("请输入要发送的消息（输入 q 退出）：");
        fgets(message, BUF_SIZE, stdin);
        size_t len = strlen(message);
        if (len > 0 && message[len - 1] == '\n')
        {
            message[len - 1] = '\0';
        }

        // 发送消息到服务器
        if (sendto(client_sock, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
            error_handling("sendto() error");

        // 退出条件
        if (strcmp(message, "q") == 0 || strcmp(message, "Q") == 0)
            break;

        // 接收服务器的回复
        // if (recvfrom(client_sock, message, BUF_SIZE, 0, NULL, NULL) == -1)
        //     error_handling("recvfrom() error");

        // printf("收到服务器的回复：%s\n", message);
    }

    close(client_sock);
    return 0;
}

void error_handling(const char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
