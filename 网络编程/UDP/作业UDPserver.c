#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024
#define SERVER_PORT 8888

typedef struct
{
    struct sockaddr_in addr;
} ClientInfo;

void error_handling(const char *message);

int main(void)
{
    int server_sock;                // 服务器套接字
    struct sockaddr_in server_addr; // 服务器地址信息
    struct sockaddr_in client_addr; // 客户端地址信息
    socklen_t client_addr_size;
    char message[BUF_SIZE];

    // 创建服务器套接字
    server_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_sock == -1)
        error_handling("socket() error");

    // 设置服务器地址信息
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    // 绑定服务器套接字与地址
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        error_handling("bind() error");

    printf("服务器已启动，等待客户端连接...\n");

    ClientInfo client_list[10]; // 最多保存10个客户端信息
    memset(client_list,0,sizeof(client_list));
    int num_clients = 0;        // 当前客户端数量

    ClientInfo client1;
    memset(&client1.addr, 0, sizeof(client1.addr));
    client1.addr.sin_family = AF_INET;
    client1.addr.sin_addr.s_addr = inet_addr("192.168.1.148");
    client1.addr.sin_port = htons(7777);
    memcpy(&client_list[0],&client1,sizeof(client1));
    num_clients++;

    ClientInfo client2;
    memset(&client2.addr, 0, sizeof(client2.addr));
    client2.addr.sin_family = AF_INET;
    client2.addr.sin_addr.s_addr = inet_addr("192.168.1.149");
    client2.addr.sin_port = htons(9999);
    memcpy(&client_list[1],&client2,sizeof(client2));
    num_clients++;


    while (1)
    {
        client_addr_size = sizeof(client_addr);

        // 接收客户端的消息
        if (recvfrom(server_sock, message, BUF_SIZE, 0, (struct sockaddr *)&client_addr, &client_addr_size) == -1)
            error_handling("recvfrom() error");

        printf("收到来自 %s:%d 的消息：%s\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), message);
        for (int i = 0; i < 10; i++)
        {
            printf("Client %d IP: %s, Port: %d\n", i + 1, inet_ntoa(client_list[i].addr.sin_addr), ntohs(client_list[i].addr.sin_port));
        }

        int i;
        // 遍历客户端列表，将消息发送给其他客户端
        for (i = 0; i < num_clients; i++)
        {
            if (memcmp(&client_list[i].addr, &client_addr, sizeof(client_addr)) != 0)
            {
                if (sendto(server_sock, message, strlen(message), 0,
                           (struct sockaddr *)&client_list[i].addr, client_addr_size) == -1)
                    error_handling("sendto() error");
            }
        }

        // 如果客户端不在列表中，则将其添加到列表中
        int found = 0;
        for (i = 0; i < num_clients; i++)
        {
            if (memcmp(&client_list[i].addr, &client_addr, sizeof(client_addr)) == 0)
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            memcpy(&client_list[num_clients].addr, &client_addr, sizeof(client_addr));
            num_clients++;
        }

        // 清空消息缓冲区
        memset(message, 0, sizeof(message));

        // 示例：如果接收到消息的客户端是 client1，则向 client2 发送一条回复消息
        if (memcmp(&client_addr, &client1.addr, sizeof(client_addr)) == 0)
        {
            char reply_message[] = "这是服务器的回复消息给 client1";
            if (sendto(server_sock, reply_message, strlen(reply_message), 0,
                       (struct sockaddr *)&client2.addr, client_addr_size) == -1)
                error_handling("sendto() error");
        }
    }

    close(server_sock);
    return 0;
}

void error_handling(const char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
