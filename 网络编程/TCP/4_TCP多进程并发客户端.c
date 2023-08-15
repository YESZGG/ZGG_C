#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX_IP_LENGTH 16 // 最大IP地址长度（包括终止符）

int main(int argc, char *argv[])
{
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    int ret;

    // 输入服务器的IP地址
    char server_ip[MAX_IP_LENGTH];
    printf("Enter the server IP address: ");
    scanf("%s", server_ip);

    // 输入服务器的端口号
    unsigned short server_port;
    printf("Enter the server port: ");
    scanf("%hu", &server_port);

    // 建立套接字
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        perror("Socket creation failed");
        return -1;
    }

    // 配置服务器的IP地址和端口号
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;                   // IPV4 网络协议
    server_addr.sin_port = htons(server_port);          // 本机器端口号转化为网络段 host to net short
    server_addr.sin_addr.s_addr = inet_addr(server_ip); // 将用户输入的IP地址转换为网络IP地址
    socklen_t addrlen = sizeof(struct sockaddr_in);

    // 连接服务器
    if (ret = connect(socket_fd, (struct sockaddr *)&server_addr, addrlen) < 0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    char message[1024]; // 存储用户输入的消息
    while (1)
    {
        memset(message, 0, sizeof(message));
        // 输入要发送的消息
        printf("Enter the message (enter 'exit' to quit): ");
        fgets(message, sizeof(message), stdin);

        size_t len = strlen(message);
        if (len > 0 && message[len - 1] == '\n')
        {
            message[len - 1] = '\0';
        }

        // 发送数据
        if ((ret = send(socket_fd, message, strlen(message), 0)) < 0)
        {
            perror("Send failed");
            exit(EXIT_FAILURE);
        }
        printf("Message sent to server: %s ret:%d\n", message, ret);
    }

    // 关闭套接字
    close(socket_fd);
    return 0;
}
