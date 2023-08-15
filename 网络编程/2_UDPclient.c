#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

#define MY_PORT 7777
#define MY_IP "192.168.1.149"

#define SERVER_IP "192.168.1.148"
#define SERVER_PORT 8888

void error_handling(const char *message);

int main(void)
{
    int client_sock;
    struct sockaddr_in server_addr, my_addr;
    socklen_t server_addr_size, my_addr_size;
    char message[BUF_SIZE];

    // 创建客户端套接字
    client_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_sock == -1)
        error_handling("socket() error");

    // 设置客户端地址信息
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MY_PORT);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // 绑定客户端套接字与地址
    if (bind(client_sock, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1)
        error_handling("bind() error");

    // 设置服务器地址信息
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);

    while (1)
    {
        // printf("请输入要发送的消息（输入 q 退出）：");
        // fgets(message, BUF_SIZE, stdin);

        // // 发送消息到服务器
        // if (sendto(client_sock, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        //     error_handling("sendto() error");

        // // 退出条件
        // if (strcmp(message, "q\n") == 0 || strcmp(message, "Q\n") == 0)
        //     break;
        // 清空缓冲区
        memset(message,0,sizeof(message));
        // 接收服务器的回复
        server_addr_size = sizeof(server_addr);
        if (recvfrom(client_sock, message, BUF_SIZE, 0, (struct sockaddr *)&server_addr, &server_addr_size) == -1)
            error_handling("recvfrom() error");

        printf("收到服务器的回复：%s\n", message);
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
