/*
 * 
 *    ┏┓　　　┏┓
 *  ┏┛┻━━━┛┻┓
 *  ┃　　　　　　　┃
 *  ┃　　　━　　　┃
 *  ┃　＞　　　＜　┃
 *  ┃　　　　　　　┃
 *  ┃...　⌒　...　┃
 *  ┃　　　　　　　┃
 *  ┗━┓　　　┏━┛
 *      ┃　　　┃　
 *      ┃　　　┃
 *      ┃　　　┃
 *      ┃　　　┃  神兽保佑
 *      ┃　　　┃  代码无bug　　
 *      ┃　　　┃
 *      ┃　　　┗━━━┓
 *      ┃　　　　　　　┣┓
 *      ┃　　　　　　　┏┛
 *      ┗┓┓┏━┳┓┏┛
 *        ┃┫┫　┃┫┫
 *        ┗┻┛　┗┻┛
 */

/*
 * @Description:TCPserver
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-08-10 16:30:28
 * @LastEditors: ZGG
 * @LastEditTime: 2023-08-10 20:24:20
 */
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SERVER_PORT 8888
#define SERVER_IP "192.168.1.11"

int main()
{
    int sockfd, client_sock;
    struct sockaddr_in client_addr;
    char buffer[1024] = {0};

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

    char response[1024]; // 存储接收用户发送过来的消息
    while (1)
    {
        socklen_t client_addrlen = sizeof(struct sockaddr_in);
        // 接受客户端连接
        client_sock = accept(sockfd, (struct sockaddr *)&client_addr, &client_addrlen);
        if (client_sock < 0)
        {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
        printf("Connection accepted from [IP:%s][PORT:%d]\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        while (1)
        {
            memset(buffer, 0, sizeof(buffer));
            // 接收来自客户端的消息
            if (read(client_sock, buffer, 1024) < 0)
            {
                perror("Receive failed");
                exit(EXIT_FAILURE);
            }
            printf("Message from client: %s\n", buffer);
            if (strcmp(buffer, "exit") == 0)
            {
                break;
            }

            // 向客户端发送响应消息
            // if (send(client_sock, response, strlen(response), 0) < 0)
            // {
            //     perror("Send failed");
            //     exit(EXIT_FAILURE);
            // }
            // printf("Response sent to client: %s\n", response);
            memset(response, 0, sizeof(response));
            printf("Send:");
            scanf("%s", response);
            if (send(client_sock, response, strlen(response), 0) < 0)
            {
                perror("Send failed");
                exit(EXIT_FAILURE);
            }
            printf("Response sent to client [IP:%s][PORT:%d]\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        }
    }
    // 关闭客户端套接字
    close(client_sock);
    // 关闭服务器套接字
    close(sockfd);

    return 0;
}
#endif


#if 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

#define SERVER_PORT 8888
#define SERVER_IP "192.168.1.148"

struct ThreadArgs {
    int sockfd;
    struct sockaddr_in client_addr;
};

void* clientThread(void* arg) {
    struct ThreadArgs* args = (struct ThreadArgs*)arg;
    int client_sock = args->sockfd;
    struct sockaddr_in client_addr = args->client_addr;

    char buffer[1024] = {0};
    char response[1024];

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        // 接收来自客户端的消息
        if (read(client_sock, buffer, sizeof(buffer)) < 0) {
            perror("Receive failed");
            break;
        }
        printf("Message from client [IP:%s][PORT:%d]: %s\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);
        
        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        memset(response, 0, sizeof(response));
        printf("Send: ");
        scanf("%s", response);
        // 发送消息给客户端
        if (send(client_sock, response, strlen(response), 0) < 0) {
            perror("Send failed");
            break;
        }
        printf("Response sent to client [IP:%s][PORT:%d]\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    }

    // 关闭客户端套接字
    close(client_sock);
    free(arg);  // 为线程参数释放分配的内存
    pthread_exit(NULL);
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr;

    // 创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    // 防止端口复用
    int reuseaddr = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr)) < 0) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // 配置服务器IP地址和端口号
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    socklen_t addrlen = sizeof(struct sockaddr_in);

    // 绑定套接字
    if (bind(sockfd, (struct sockaddr *)&server_addr, addrlen) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听套接字
    if (listen(sockfd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Listening on port %d...\n", SERVER_PORT);

    while (1) {
        struct ThreadArgs* args = malloc(sizeof(struct ThreadArgs));
        socklen_t client_addrlen = sizeof(struct sockaddr_in);
        args->sockfd = accept(sockfd, (struct sockaddr *)&args->client_addr, &client_addrlen);
        if (args->sockfd < 0) {
            perror("Accept failed");
            free(args);
            continue;
        }
        printf("Connection accepted from [IP:%s][PORT:%d]\n",
               inet_ntoa(args->client_addr.sin_addr), ntohs(args->client_addr.sin_port));
        // 创建线程
        pthread_t thread;
        if (pthread_create(&thread, NULL, clientThread, (void*)args) != 0) {
            perror("Thread creation failed");
            close(args->sockfd);
            free(args);
            continue;
        }

        // 分离线程，使其自动终止并清理
        pthread_detach(thread);
    }

    // 关闭服务器套接字
    close(sockfd);

    return 0;
}

#endif