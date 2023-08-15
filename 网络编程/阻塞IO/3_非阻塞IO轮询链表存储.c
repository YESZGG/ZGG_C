#include <stdio.h>
#include <stdlib.h>
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
    struct client *next;
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

    int socket_client;//客户端套接字
    struct sockaddr_in client_addr; // 用来接收客户端的ip和端口
    socklen_t len = sizeof(struct sockaddr_in);

    char buf[1024] = {0};

    // 使用链表存储客户端信息
    ClientInfo *head = NULL;
    ClientInfo *tail = NULL;

    while (1)
    {
        // 接收客户端的链接---accept(阻塞)
        socket_client = accept(socket_fd, (struct sockaddr *)&client_addr, &len);
        if (socket_client != -1) // 有新的客户端上线就存起来
        {
            ClientInfo *new_client = malloc(sizeof(ClientInfo));
            new_client->socket_fd = socket_client;
            new_client->client_addr = client_addr;
            new_client->next = NULL;
            
            if (head == NULL) // 列表为空，则新节点为头节点
            {
                head = new_client;
                tail = new_client;
            }
            else // 否则将新节点加入链表尾部
            {
                tail->next = new_client;
                tail = new_client;
            }

            int status = fcntl(new_client->socket_fd, F_GETFL); // 得到文件描述符的状态
            status |= O_NONBLOCK;                               // 在原来的基础上新增非阻塞属性
            fcntl(new_client->socket_fd, F_SETFL, status);      // 把变量status的状态设置到文件描述符中

            printf("新的客户端上线[%d]：[%s][%d]\n", socket_client, inet_ntoa(new_client->client_addr.sin_addr), ntohs(new_client->client_addr.sin_port));
        }

        // 遍历链表处理每个客户端的数据
        ClientInfo *current = head;
        while (current != NULL)
        {
            // 与客户端之间交互数据---send/recv
            memset(buf, 0, sizeof(buf));
            ret = recv(current->socket_fd, buf, sizeof(buf), 0);
            if (ret > 0) // 客户端发来有效数据
            {
                printf("[IP:%s][PORT:%d]接收到来自客户端的消息：%s\n", inet_ntoa(current->client_addr.sin_addr), ntohs(current->client_addr.sin_port), buf);
            }
            if (ret == 0) // 客户端掉线，重置套接字
            {
                // 客户端掉线说明
                printf("[IP:%s][PORT:%d] 客户端已下线.\n", inet_ntoa(current->client_addr.sin_addr), ntohs(current->client_addr.sin_port));
                
                close(current->socket_fd);

                // 删除节点
                if (current == head) // 如果是头节点
                {
                    head = current->next;
                    free(current);
                    current = head;
                }
                else // 如果是中间或尾部节点
                {
                    ClientInfo *temp = head;
                    while (temp != NULL && temp->next != current)
                    {
                        temp = temp->next;
                    }
                    if (temp != NULL)
                    {
                        temp->next = current->next;
                        free(current);
                        current = temp->next;
                    }
                }
            }
            else
            {
                current = current->next; // 移动到下一个节点
            }
        }
    }

    // 释放链表内存
    ClientInfo *current = head;
    while (current != NULL)
    {
        ClientInfo *temp = current;
        current = current->next;
        free(temp);
    }

    // 关闭套接字
    close(socket_fd);

    return 0;
}
