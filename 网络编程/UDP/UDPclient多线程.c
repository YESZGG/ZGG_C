/*
 * @Description:
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-08-11 15:31:05
 * @LastEditors: ZGG
 * @LastEditTime: 2023-08-11 21:14:27
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_BUFFER_SIZE 1024
#define MAX_IP_LENGTH 16 // 最大IP地址长度（包括终止符）
#define MY_PORT 8888
#define MY_ADDR "192.168.1.147"

void *receive_messages(void *arg)
{
    int socket_fd = *(int *)arg;
    struct sockaddr_in dest_addr;

    while (1)
    {
        char buffer[MAX_BUFFER_SIZE];
        memset(buffer, 0, sizeof(buffer));
        socklen_t dest_addrlen = sizeof(dest_addr);
        ssize_t num_bytes_received = recvfrom(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&dest_addr,&dest_addrlen);
        if (num_bytes_received == -1)
        {
            perror("Recvfrom failed");
            break;
        }

        buffer[num_bytes_received] = '\0'; // Add string termination

        printf("Received message from [IP:%s][PORT:%d]: %s\n", inet_ntoa(dest_addr.sin_addr), ntohs(dest_addr.sin_port), buffer);

        if (strcmp(buffer, "exit") == 0)
        {
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    // 输入服务器的IP地址
    char server_ip[MAX_IP_LENGTH];
    printf("Enter the server IP address: ");
    scanf("%s", server_ip);

    // 输入服务器的端口号
    unsigned short server_port;
    printf("Enter the server port: ");
    scanf("%hu", &server_port);

    // 创建套接字
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd == -1)
    {
        perror("Socket creation failed");
        return -1;
    }
    // 设置端口复用
    int optval = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    // 绑定本机IP --- 可有可无
    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;                                             // 地址簇
    my_addr.sin_port = htons(MY_PORT);                                        // 本机端口转为网络端口
    my_addr.sin_addr.s_addr = inet_addr(MY_ADDR);                             // 本机IP转为网络IP
    bind(socket_fd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_in)); // 固定本机端口

    // 配置接收端的IP地址和端口号
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;                   // IPV4 网络协议
    server_addr.sin_port = htons(server_port);          // 本机器端口号转化为网络段 host to net short
    server_addr.sin_addr.s_addr = inet_addr(server_ip); // 将用户输入的IP地址转换为网络IP地址
    socklen_t addrlen = sizeof(struct sockaddr_in);

    pthread_t tid;
    pthread_create(&tid, NULL, receive_messages, (void *)&socket_fd);
    while (1)
    {
        // 输入待发送的消息
        char buffer[MAX_BUFFER_SIZE];
        // 输入要发送的消息
        printf("Enter the message (enter 'exit' to quit): ");
        fgets(buffer, sizeof(buffer), stdin);

        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }

        sendto(socket_fd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, addrlen);

        if (strcmp(buffer, "exit") == 0)
        {
            break;
        }
    }

    // 关闭套接字
    close(socket_fd);

    return 0;
}