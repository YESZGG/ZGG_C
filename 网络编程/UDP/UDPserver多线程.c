/*
 * @Description:
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-08-11 19:05:24
 * @LastEditors: ZGG
 * @LastEditTime: 2023-08-11 20:51:46
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_BUFFER_SIZE 1024
#define MY_PORT 8888
#define MY_ADDR "192.168.1.148"

typedef struct
{
    int socket_fd;
    struct sockaddr_in client_addr;
} ThreadData;

void *handle_client(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    int socket_fd = data->socket_fd;
    struct sockaddr_in client_addr = data->client_addr;

    while (1)
    {
        char buffer[MAX_BUFFER_SIZE];
        memset(buffer, 0, sizeof(buffer));
        socklen_t client_addrlen = sizeof(client_addr);

        ssize_t num_bytes_received = recvfrom(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr,&client_addrlen);
        if (num_bytes_received == -1)
        {
            perror("Recvfrom failed");
            break;
        }

        buffer[num_bytes_received] = '\0'; // Add string termination

        printf("Received message from [IP:%s][PORT:%d]: %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);

        if (strcmp(buffer, "exit") == 0)
        {
            break;
        }
    }

    close(socket_fd);
    free(arg);

    pthread_exit(NULL);
}

void *sendtoclient(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    int socket_fd = data->socket_fd;
    struct sockaddr_in client_addr = data->client_addr;
    int ret = 0;

    char buffer[MAX_BUFFER_SIZE];
    while (1)
    {
        memset(buffer, 0, sizeof(buffer));
        socklen_t client_addrlen = sizeof(client_addr);
        // 输入要发送的消息
        printf("Enter the message (enter 'exit' to quit): ");
        fgets(buffer, sizeof(buffer), stdin);

        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }

        ret = sendto(socket_fd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, client_addrlen);
        if (ret < 0)
        {
            perror("sendto error");
            return NULL;
        }
        printf("Send message from [IP:%s][PORT:%d]: %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);
    }

    close(socket_fd);
    free(arg);

    pthread_exit(NULL);
}

int main()
{
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd == -1)
    {
        perror("Socket creation failed");
        return -1;
    }

    int optval = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(MY_PORT);
    server_addr.sin_addr.s_addr = inet_addr(MY_ADDR);
    socklen_t addrlen = sizeof(struct sockaddr_in);

    if (bind(socket_fd, (struct sockaddr *)&server_addr, addrlen) == -1)
    {
        perror("Bind failed");
        return -1;
    }

    // Create threads to handle clients
    pthread_t tid, sendtid;
    while (1)
    {
        struct sockaddr_in client_addr;
        socklen_t client_addrlen = sizeof(client_addr);

        ThreadData *data = (ThreadData *)malloc(sizeof(ThreadData));
        data->socket_fd = socket_fd;
        memcpy(&(data->client_addr), &client_addr, sizeof(client_addr));

        ssize_t num_bytes_received = recvfrom(socket_fd, NULL, 0, MSG_PEEK, (struct sockaddr *)&client_addr, &client_addrlen);
        if (num_bytes_received != -1)
        {
            pthread_create(&tid, NULL, handle_client, (void *)data);
            pthread_detach(tid);
            pthread_create(&sendtid, NULL, sendtoclient, (void *)data);
            pthread_detach(sendtid);
        }
    }

    close(socket_fd);

    return 0;
}
