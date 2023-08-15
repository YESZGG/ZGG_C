/*
 * @Description: 
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-08-14 10:54:38
 * @LastEditors: ZGG
 * @LastEditTime: 2023-08-14 13:55:58
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define GUANGBO_IP "192.168.1.255"
#define GUANGBO_PORT 9999

/*
    广播----->udp协议

*/

int main()
{
    // 建立套截字
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd < 0)
    {
        perror("socket fail");
        return -1;
    }

    // 将广播属性添加到套截字socket_fd中
    int on = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));

    struct sockaddr_in send_addr;
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = htons(GUANGBO_PORT);
    send_addr.sin_addr.s_addr = inet_addr(GUANGBO_IP); // 一定是广播地址，广播发送

    while (1)
    {

        sendto(socket_fd, "亻尔 女子", strlen("亻尔 女子"), 0, (struct sockaddr *)&send_addr, sizeof(send_addr)); 
    }

    // 关闭套截字
    close(socket_fd);

    return 0;
}