#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
    服务端
*/

#define SERVER_IP "192.168.1.3" //ubuntu的服务器的ip
#define SERVER_PORT 60000

void * send_buf(void *arg)
{
    //设置自己的分离属性
    pthread_detach(pthread_self());

    int ret = 0;
    int scoket_client = *(int *)arg;

    char buf[1024] = {0};
    while(1)
    {
        memset(buf,0,sizeof(buf));
        scanf("%s",buf);
        ret = send(scoket_client, buf, strlen(buf), 0);
        printf("send ret:%d\n", ret);

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
    // 填充服务器的ip和端口号----新结构体
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;                   // Ipv4 网络协议
    server_addr.sin_port = htons(SERVER_PORT);          // 本机端口转换为网络端口host to net short
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP); // 本机ip转换为网络ip
    socklen_t addrlen = sizeof(struct sockaddr_in);

    // 绑定本机ip和端口号(必须要有)---bind
    ret = bind(scoket_fd, (struct sockaddr *)&server_addr, addrlen);
    if (ret < 0)
    {
        perror("bind fail");
        return -1;
    }
    printf("bind success[%s][%d]\n",SERVER_IP,SERVER_PORT);

    // 监听---listen
    ret = listen(scoket_fd, 20);
    if (ret < 0)
    {
        perror("listen fail");
        return -1;
    }

    // 接收客户端的链接---accept
    int scoket_client; // 服务器给客户端发送数据的套接字，不是scoket_fd
    struct sockaddr_in client_addr; //用来接收客户端的ip和端口
    socklen_t addrlen1 = sizeof(struct sockaddr_in);
    scoket_client = accept(scoket_fd, (struct sockaddr *)&client_addr, &addrlen1);
    if (scoket_client < 0)
    {
        perror("accept fail");
        return -1;
    }
    char *ip = inet_ntoa(client_addr.sin_addr) ;//将网络ip转换为本机ip
    int port = ntohs(client_addr.sin_port); //将网络端口转本机端口
    printf("新的客户端上线：[%s][%d]\n",ip,port);

    //创建发送数据的线程
    pthread_t tid;
    ret = pthread_create(&tid,NULL,send_buf,(void *)&scoket_client);
    if(ret != 0)
    {
        perror("pthread_create fail");
        return -1;
    }   

    // 与客户端之间交互数据---send/recv
    char buf[1024] = {0};
    while(1)
    {
        memset(buf,0,sizeof(buf));
        ret = recv(scoket_client, buf, sizeof(buf), 0);
        printf("[%s][%d]recv buf:%s ret:%d\n", ip,port,buf, ret);
        if(ret == 0)
        {
            printf("客户端掉线[%s][%d]\n",ip,port);
            break;
        }
    }


    // 关闭套接字---close
    close(scoket_fd);

    return 0;
}