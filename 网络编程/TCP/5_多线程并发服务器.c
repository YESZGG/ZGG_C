#include <stdio.h>
#include <string.h> //strlen
#include <unistd.h> //close
#include <pthread.h> //pthread_create
#include <sys/types.h> /* See NOTES */ //soket 
#include <sys/socket.h>
#include <netinet/in.h> //inet_addr
#include <arpa/inet.h>

#define SERVER_IP "192.168.1.3" // ubuntu的服务器的ip
#define SERVER_PORT 60000

/*
    多线程并发服务器
*/

//接收客户端发送的数据
void *recv_info(void *arg)
{
    //设置自己为分离属性
    pthread_detach(pthread_self());

    int ret = 0;
    int socket_client = *(int *)arg;

    // 与客户端之间交互数据---send/recv
    char buf[1024] = {0};
    while(1)
    {
        memset(buf,0,sizeof(buf));
        ret = recv(socket_client, buf, sizeof(buf), 0);
        printf("[%s][%d]recv buf:%s ret:%d\n", ip,port,buf, ret);
        //printf("buf:%s ret:%d\n",buf,ret);

        if(ret == 0)
        {
            printf("客户端掉线[%d]\n",socket_client);          
            break;
        }
    }   
    close(socket_client); 

    return NULL;
}

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

    while (1)
    {
        // 接收客户端的链接---accept(阻塞)
        int socket_client;
        struct sockaddr_in client_addr; // 用来接收客户端的ip和端口
        socklen_t len = sizeof(struct sockaddr_in);
        socket_client = accept(socket_fd, (struct sockaddr *)&client_addr, &len);
        if (socket_client < 0)
        {
            perror("accept fail");
            return -1;
        }
        char *ip = inet_ntoa(client_addr.sin_addr); // 将网络ip转换为本机ip
        int port = ntohs(client_addr.sin_port);     // 将网络端口转本机端口
        printf("新的客户端上线：[%s][%d]\n", ip, port);

        // 创建一个子线程用来接收客户端的数据---recv(阻塞)
        pthread_t tid;
        ret = pthread_create(&tid, NULL, recv_info, &socket_client);
        if (ret != 0)
        {
            printf("pthread_create fail\n");
            return -1;
        }
    }

    // 关闭套接字
    close(socket_fd);

    return 0;
}