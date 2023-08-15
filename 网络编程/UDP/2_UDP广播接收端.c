#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// #define MY_IP "192.168.1.3"
#define MY_PORT 9999

/*
    广播----->udp协议

*/

int main()
{

    int ret;

    // 建立套截字
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd < 0)
    {
        perror("socket fail");
        return -1;
    }

    // htonl  ---> 本机ip转换为网络ip 不要和htons混淆（l---->转的是ip s---->转的是端口）
    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MY_PORT);
    // uint32_t htonl(uint32_t hostlong);  将 主机IP转为 网络IP
    // my_addr.sin_addr.s_addr = inet_addr(本机ip);
    // INADDR_ANY -->代表当前主机所有的地址
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY); // INADDR_ANY(0.0.0.0) 代表本机所有的地址
    bind(socket_fd, (struct sockaddr *)&my_addr, sizeof(my_addr));

    // 接收其它的客户端的地址
    struct sockaddr_in other_addr;
    int len = sizeof(struct sockaddr_in);
    while (1)
    {
        char buf[1024] = {0};

        ret = recvfrom(socket_fd, buf, sizeof(buf), 0, (struct sockaddr *)&other_addr, &len);

        printf("[%s][%d] buf:%s ret:%d\n", inet_ntoa(other_addr.sin_addr), ntohs(other_addr.sin_port), buf, ret);
    }

    // 关闭套截字
    close(socket_fd);

    return 0;
}