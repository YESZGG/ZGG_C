#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
    客户端
*/

#define SERVER_IP "192.168.1.148" //ubuntu的服务器的ip
// #define SERVER_IP "192.168.1.2" //windows的服务器的ip
#define SERVER_PORT 8888

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


    //绑定本机ip和端口---客户端可有可无

    int ret;
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