#include <stdio.h>
#include <string.h>                    //strlen
#include <unistd.h>                    //close
#include <pthread.h>                   //pthread_create
#include <sys/types.h> /* See NOTES */ //soket
#include <sys/socket.h>
#include <netinet/in.h> //inet_addr
#include <arpa/inet.h>
#include <fcntl.h>

#define SERVER_IP "192.168.1.148" // ubuntu的服务器的ip
#define SERVER_PORT 8888

/*
    非阻塞IO轮循并发服务器
*/

typedef struct client
{
    int socket_fd;
    struct sockaddr_in client_addr;
} ClientInfo;
// 一个客户端的套接字对应一个客户端的地址

int main()
{
    int ret;
    // 建立套接字
    // 建立套接字---socket
    int socket_fd;
    // SOCK_STREAM--TCP的协议
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        perror("socket fail");
        return -1;
    }

    // 设置端口重复复用
    int optval = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    // 绑定本机ip和端口
    // 填充服务器的ip和端口号----新结构体
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;                   // Ipv4 网络协议
    server_addr.sin_port = htons(SERVER_PORT);          // 本机端口转换为网络端口host to net short
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP); // 本机ip转换为网络ip
    socklen_t addrlen = sizeof(struct sockaddr_in);

    // 绑定本机ip和端口号(必须要有)---bind
    ret = bind(socket_fd, (struct sockaddr *)&server_addr, addrlen);
    if (ret < 0)
    {
        perror("bind fail");
        return -1;
    }
    printf("绑定本机成功[%s][%d]\n", SERVER_IP, SERVER_PORT);

    // 监听
    ret = listen(socket_fd, 20);
    if (ret < 0)
    {
        perror("listen fail");
        return -1;
    }

    int status = fcntl(socket_fd, F_GETFL); // 得到文件描述符的状态
    status |= O_NONBLOCK;                   // 在原来的基础上新增非阻塞属性
    fcntl(socket_fd, F_SETFL, status);      // 把变量status的状态设置到文件描述符中

    int socket_client;
    struct sockaddr_in client_addr; // 用来接收客户端的ip和端口
    socklen_t len = sizeof(struct sockaddr_in);

    char buf[1024] = {0};

    // 用数组存储新的客户端套接字最大存10个
    ClientInfo client_list[10]; // 最多保存10个客户端信息
    memset(client_list, 0, sizeof(client_list));
    int num_clients = 0; // 当前客户端数量

    while (1)
    {
        // 接收客户端的链接---accept(阻塞)
        socket_client = accept(socket_fd, (struct sockaddr *)&client_addr, &len);
        if (socket_client != -1) // 有新的客户端上线就存起来
        {
            ClientInfo new_client;
            new_client.socket_fd = socket_client;
            new_client.client_addr = client_addr;
            client_list[num_clients++] = new_client;

            int status = fcntl(new_client.socket_fd, F_GETFL); // 得到文件描述符的状态
            status |= O_NONBLOCK;                              // 在原来的基础上新增非阻塞属性
            fcntl(new_client.socket_fd, F_SETFL, status);      // 把变量status的状态设置到文件描述符中

            printf("新的客户端上线[%d]：[%s][%d]\n", socket_client, inet_ntoa(new_client.client_addr.sin_addr), ntohs(new_client.client_addr.sin_port));
        }

        // 轮循遍历所有的套接字
        for (int i = 0; i < num_clients; i++)
        {
            // 与客户端之间交互数据---send/recv
            memset(buf, 0, sizeof(buf));
            ret = recv(client_list[i].socket_fd, buf, sizeof(buf), 0);
            if (ret > 0) // 客户端发来有效数据
            {
                printf("[IP:%s][PORT:%d]接收到来自客户端的消息：%s\n", inet_ntoa(client_list[i].client_addr.sin_addr), ntohs(client_list[i].client_addr.sin_port), buf);
            }
            if (ret == 0) // 客户端掉线，重置套接字
            {
                // 客户端掉线说明
                printf("[IP:%s][PORT:%d] 客户端已下线.\n", inet_ntoa(client_list[i].client_addr.sin_addr), ntohs(client_list[i].client_addr.sin_port));
                
                close(client_list[i].socket_fd);
                client_list[i].socket_fd = -1;
            }
        }
    }

    // 关闭套接字
    close(socket_fd);

    return 0;
}

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int main() {
    int serverSocket, clientSockets[MAX_CLIENTS], maxFd;
    fd_set readFds;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    // 创建服务器套接字
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Failed to create server socket");
        return -1;
    }

    // 设置非阻塞模式
    int flags = fcntl(serverSocket, F_GETFL, 0);
    fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK);

    // 绑定服务器地址和端口
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(5000);
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Failed to bind server socket");
        close(serverSocket);
        return -1;
    }
    
    // 监听连接
    if (listen(serverSocket, MAX_CLIENTS) < 0) {
        perror("Failed to listen");
        close(serverSocket);
        return -1;
    }
    
    // 初始化客户端套接字数组
    memset(clientSockets, 0, sizeof(clientSockets));
    maxFd = serverSocket;

    while (1) {
        // 配置文件描述符集合
        FD_ZERO(&readFds);
        FD_SET(serverSocket, &readFds);

        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clientSockets[i] > 0) {
                FD_SET(clientSockets[i], &readFds);
                maxFd = (clientSockets[i] > maxFd) ? clientSockets[i] : maxFd;
            }
        }

        // 使用 select() 函数进行轮询，等待事件发生
        int activity = select(maxFd + 1, &readFds, NULL, NULL, NULL);
        if (activity < 0) {
            perror("Failed to select");
            break;
        }

        // 处理服务器套接字的连接请求
        if (FD_ISSET(serverSocket, &readFds)) {
            int newSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen);
            if (newSocket < 0) {
                perror("Failed to accept");
                break;
            }
            
            // 设置新客户端套接字为非阻塞模式
            int flags = fcntl(newSocket, F_GETFL, 0);
            fcntl(newSocket, F_SETFL, flags | O_NONBLOCK);

            // 将新客户端套接字添加到客户端套接字数组中
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (clientSockets[i] == 0) {
                    clientSockets[i] = newSocket;
                    break;
                }
            }
        }

        // 处理客户端套接字的数据收发
        for (int i = 0; i < MAX_CLIENTS; i++) {
            int clientSocket = clientSockets[i];

            if (FD_ISSET(clientSocket, &readFds)) {
                char buffer[BUFFER_SIZE];
                memset(buffer, 0, sizeof(buffer));

                ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
                if (bytesRead > 0) {
                    printf("[IP:%s][PORT:%d] Received from client: %s\n", buffer);

                    // 在这里可以对收到的数据进行处理，并作出相应的响应

                } else if (bytesRead == 0) {
                    // 客户端连接已关闭
                    printf("Client disconnected\n");
                    close(clientSocket);
                    clientSockets[i] = 0;
                } else {
                    // 发生错误
                    perror("Failed to receive from client");
                    close(clientSocket);
                    clientSockets[i] = 0;
                }
            }
        }
    }
    
    // 关闭服务器套接字和所有客户端套接字
    close(serverSocket);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clientSockets[i] > 0) {
            close(clientSockets[i]);
        }
    }

    return 0;
}
#endif
