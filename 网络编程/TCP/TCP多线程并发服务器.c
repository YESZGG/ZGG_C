#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strlen
#include <unistd.h> //close
#include <pthread.h> //pthread_create
#include <sys/types.h> /* See NOTES */ //soket 
#include <sys/socket.h>
#include <netinet/in.h> //inet_addr
#include <arpa/inet.h>

#define SERVER_IP "192.168.1.148" // ubuntu的服务器的ip
#define SERVER_PORT 8888

struct client
{
    int socket_client;
    struct sockaddr_in client_addr;
};

void *clientThread(void *arg)
{
    struct client *args = (struct client *)arg;
    int client_sock = args->socket_client;
    struct sockaddr_in client_addr = args->client_addr;

    char buffer[1024] = {0};
    int ret = 0;
    while (1)
    {
        memset(buffer, 0, sizeof(buffer));
        // 接收来自客户端的消息
        if ((ret = (recv(client_sock, buffer, sizeof(buffer), 0))) < 0)
        {
            perror("Receive failed");
            break;
        }        
        if (ret == 0)
        {
            printf("[IP:%s][PORT:%d] 客户端已下线.\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            break;
        }
        printf("Message from client [IP:%s][PORT:%d]: %s\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);


    }

    // 关闭客户端套接字
    close(client_sock);
    free(arg); // 为线程参数释放分配的内存
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    struct sockaddr_in server_addr;
    // 创建套接字
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        perror("Socket create failed");
        exit(EXIT_FAILURE);
    }

    // 设置端口复用
    int optval = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // 配置服务器的地址信息
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 绑定地址信息
    if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    printf("[IP:%s][PORT:%d] 绑定本机成功。\n", SERVER_IP, SERVER_PORT);

    // 监听
    if (listen(socket_fd, 10) < 0)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Listening on port %d ... \n", SERVER_PORT);

    while (1)
    {
        struct client *args = malloc(sizeof(struct client));
        socklen_t client_addrlen = sizeof(struct sockaddr_in);
        // 接收连接请求
        args->socket_client = accept(socket_fd, (struct sockaddr *)&args->client_addr, &client_addrlen);
        if (args->socket_client < 0)
        {
            perror("Accept failed");
            free(args);
            continue;
        }
        printf("新的客户端上线: [IP:%s][PORT:%d]\n",
               inet_ntoa(args->client_addr.sin_addr), ntohs(args->client_addr.sin_port));
        // 创建线程
        pthread_t thread;
        if (pthread_create(&thread, NULL, clientThread, (void *)args) != 0)
        {
            perror("Thread creation failed");
            close(args->socket_client);
            free(args);
            continue;
        }

        // 分离线程，使其自动终止并清理
        pthread_detach(thread);
    }

    // 关闭服务器套接字
    close(socket_fd);
    return 0;
}