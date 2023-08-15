#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define ZUBO_IP "224.0.0.10"
#define ZUBO_PORT 9999

int main()
{
    // 1、创建UDP数据报套接字
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd < 0)
    {
        perror("socket fail");
        return -1;
    }

    // 2、发送数据，往组播地址(224.0.0.10 )里面发送数据
    struct sockaddr_in send_addr;
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = htons(ZUBO_PORT);
    send_addr.sin_addr.s_addr = inet_addr(ZUBO_IP); // 一定是广播地址，广播发送

    while (1)
    {

        sendto(socket_fd, "组播 你好", strlen("组播 你好"), 0, (struct sockaddr *)&send_addr, sizeof(send_addr));

        sleep(1);
    }

    // 关闭套接字
    close(socket_fd);

    return 0;
}