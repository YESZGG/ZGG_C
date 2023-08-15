/*
 * @Description:
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-08-15 09:43:29
 * @LastEditors: ZGG
 * @LastEditTime: 2023-08-15 10:13:20
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DEST_IP "192.168.1.148" // 目标地址
#define DEST_PORT 60000         // 目标ip

#define OTHER_IP "192.168.1.149" // 其它人的地址
#define OTHER_PORT 60005

// 发送数据的结构体---协议
struct info
{
    char buf[1024];                // 转发的内容
    struct sockaddr_in other_addr; // 转发的其他人
    // char *ip;// 里面尽量不要使用char *类型来存储ip
    // int port;//
};

int main(int argc, char **argv)
{
#if 0
    if(argc != 3)
    {
        printf("usage:./send <ip> <port>\n");
        return -1;
    }
#endif

    // 创建套接字
    int socket_fd;
    // AF_INET-->ipv4地址族 SOCK_DGRAM-->udp协议
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd < 0)
    {
        perror("socket fail");
        return -1;
    }

    // 绑定本机端口可有可无--->建议随机（端口随机）

    // 填充要发送的目标地址(新结构体)
    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;                 // 地址族
    dest_addr.sin_port = htons(DEST_PORT);          // 本机端口转网络端口
    dest_addr.sin_addr.s_addr = inet_addr(DEST_IP); // 本机ip转网络ip
    // dest_addr.sin_port = htons(atoi(argv[2]));//本机端口转网络端口 ---传参数的方式
    // dest_addr.sin_addr.s_addr = inet_addr(argv[1]);//本机ip转网络ip

    int ret;
    struct info send_info; // 发送数据的结构体
    memset(&send_info, 0, sizeof(struct info));

    while (1)
    {
        memset(&send_info, 0, sizeof(struct info));
        // 填充buf值
        scanf("%s", send_info.buf);

        // 填充转发的IP和端口
        send_info.other_addr.sin_family = AF_INET;                  // 地址族
        send_info.other_addr.sin_port = htons(OTHER_PORT);          // 本机端口转网络端口
        send_info.other_addr.sin_addr.s_addr = inet_addr(OTHER_IP); // 本机ip转网络ip

        ret = sendto(socket_fd, &send_info, sizeof(struct info), 0,
                     (struct sockaddr *)&dest_addr, sizeof(struct sockaddr_in));

        printf("sendto success ret:%d\n", ret);
    }

    // 关闭套接字
    close(socket_fd);

    return 0;
}