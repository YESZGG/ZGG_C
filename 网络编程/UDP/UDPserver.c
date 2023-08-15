/*
 * @Description:
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-08-11 16:03:13
 * @LastEditors: ZGG
 * @LastEditTime: 2023-08-11 16:26:29
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024
#define MY_PORT 8888
#define MY_ADDR "192.168.1.148"

int main()
{
    // 创建UDP套接字
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd == -1)
    {
        perror("Socket creation failed");
        return -1;
    }

    // 绑定地址信息
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;                 // IPV4 网络协议
    server_addr.sin_port = htons(MY_PORT);            // 本机器端口号转化为网络段 host to net short
    server_addr.sin_addr.s_addr = inet_addr(MY_ADDR); // 将用户输入的IP地址转换为网络IP地址
    socklen_t addrlen = sizeof(struct sockaddr_in);

    if (bind(socket_fd, (struct sockaddr *)&server_addr, addrlen) == -1)
    {
        perror("Bind failed");
        return -1;
    }

    // 循环接收客户端消息
    while (1)
    {
        char buffer[MAX_BUFFER_SIZE];
        memset(buffer, 0, sizeof(buffer));

        struct sockaddr_in client_addr;
        socklen_t client_addrlen = sizeof(client_addr);

        ssize_t num_bytes_received = recvfrom(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &client_addrlen);
        if (num_bytes_received == -1)
        {
            perror("Recvfrom failed");
            break;
        }

        buffer[num_bytes_received] = '\0'; // 添加字符串终止符

        printf("Received message from [IP:%s][PORT:%d]: %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);

        if (strcmp(buffer, "exit") == 0)
        {
            break;
        }
    }

    // 关闭套接字
    close(socket_fd);

    return 0;
}
