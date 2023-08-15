#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
    客户端
*/

#define SERVER_IP "192.168.1.3" //ubuntu的服务器的ip
// #define SERVER_IP "192.168.1.2" //windows的服务器的ip
#define SERVER_PORT 60000

#define MY_IP "192.168.1.3" //客户端自己的ip
#define MY_PORT 60007 //客户端自己的端口

void * recv_buf(void *arg)
{
    //设置自己的分离属性
    pthread_detach(pthread_self());

    int ret = 0;
    int scoket_fd = *(int *)arg;

    char buf[1024] = {0};
    while(1)
    {
        //接收客户端反弹的消息
        memset(buf,0,sizeof(buf));
        ret = recv(scoket_fd, buf, sizeof(buf), 0);
        printf("recv buf:%s ret:%d\n", buf, ret);
        if(ret == 0)
        {
            printf("服务器掉线\n");
            exit(0);
        }        
    }
}

int main(int argc, char **argv)
{
    // 建立套接字---socket
    int scoket_fd;
    // SOCK_STREAM--TCP的协议
    scoket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (scoket_fd < 0)
    {
        perror("socket fail");
        return -1;
    }

    // 所以设置端口号可以复用,这两条语句放在 绑定bind 之前
    int optval = 1;
    setsockopt(scoket_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    int ret;
    //绑定本机ip和端口---客户端可有可无(如果有就固定没有就随机)
    // 填充自己的ip和端口号----新结构体
    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;                   // Ipv4 网络协议
    my_addr.sin_port = htons(MY_PORT);          // 本机端口转换为网络端口host to net short
    my_addr.sin_addr.s_addr = inet_addr(MY_IP); // 本机ip转换为网络ip
    socklen_t my_addrlen = sizeof(struct sockaddr_in);
    // 绑定自己的ip和端口号(必须要有)---bind
    ret = bind(scoket_fd, (struct sockaddr *)&my_addr, my_addrlen);
    if (ret < 0)
    {
        perror("bind fail");
        return -1;
    }

    // 填充服务器的ip和端口号----新结构体
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;                   // Ipv4 网络协议
    server_addr.sin_port = htons(SERVER_PORT);          // 本机端口转换为网络端口host to net short
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP); // 本机ip转换为网络ip
    socklen_t addrlen = sizeof(struct sockaddr_in);

    // 连接服务器---connect
    // 注意：要将新结构体的指针类型转换为旧结构体的指针类型
    ret = connect(scoket_fd, (struct sockaddr *)&server_addr, addrlen);
    if (ret < 0)
    {
        printf("connect server fail\n");
        return -1;
    }

    //创建接收数据的线程
    pthread_t tid;
    ret = pthread_create(&tid,NULL,recv_buf,(void *)&scoket_fd);
    if(ret != 0)
    {
        perror("pthread_create fail");
        return -1;
    }

    // 与服务器之间交互数据---send/recv
    char buf[1024] = {0};
    while(1)
    {
        memset(buf,0,sizeof(buf));
        scanf("%s",buf);
        ret = send(scoket_fd, buf, strlen(buf), 0);
        printf("send ret:%d\n", ret);

    }


    // 关闭套接字---close
    close(scoket_fd);

    return 0;
}