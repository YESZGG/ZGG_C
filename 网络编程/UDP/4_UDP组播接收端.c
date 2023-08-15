#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define GROUP_IP "224.0.0.10"
#define GROUP_PORT 9999

int main()
{
    int ret = 0;

    // 1、创建UDP数据报套接字
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd < 0)
    {
        perror("socket fail");
        return -1;
    }

    // 2、定义组播结构体
    struct ip_mreq vmreq;

    //   3、设置组播ip（初始化 组播结构体）
    inet_pton(AF_INET, "224.0.0.10", &vmreq.imr_multiaddr);  // 组播地址
    inet_pton(AF_INET, "192.168.1.3", &vmreq.imr_interface); // 需要添加自己的ip到组的ip中

    // 4）加入组播属性（也就是设置这个套接字 可以接收组播信息）
    setsockopt(socket_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &vmreq, sizeof(vmreq));
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(GROUP_PORT);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY); // htonl(INADDR_ANY)  代表 主机所有的地址
    bind(socket_fd, (struct sockaddr *)&saddr, sizeof(saddr));

    //6）接收数据
    struct sockaddr_in other_addr;
    int len = sizeof(struct sockaddr_in);
    while (1)
    {
        char buf[1024] = {0};

        ret = recvfrom(socket_fd, buf, sizeof(buf), 0, (struct sockaddr *)&other_addr, &len);

        printf("[%s][%d] buf:%s ret:%d\n", inet_ntoa(other_addr.sin_addr), ntohs(other_addr.sin_port), buf, ret);
    }    

    //关闭套接字
    close(socket_fd);

    return 0;
}