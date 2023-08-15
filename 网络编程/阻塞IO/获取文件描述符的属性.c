/*
 * @Description: 获取文件描述符的属性(阻塞 非阻塞)
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-08-15 14:34:24
 * @LastEditors: ZGG
 * @LastEditTime: 2023-08-15 14:50:01
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    // 新建立的文件描述符都是具有阻塞属性
    int fd = open("1.txt", O_RDWR);
    if (fd < 0)
    {
        printf("open file fail\n");
        return -1;
    }
    // 读阻塞,当数据缓冲区中没有数据可以读取时,调用read/recv/recvfrom就会无限阻塞
    read(fd, buf, sizeof(buf));
    int status = fcntl(fd, F_GETFL); // 得到文件描述符的状态
    status |= O_NONBLOCK;            // 在原来的基础上新增非阻塞属性
    fcntl(fd, F_SETFL, status);      // 把变量status的状态设置到文件描述符中
#if 0
    // 获取文件描述符 fd_ts ---> 有阻塞属性
    int fd_ts = open("/dev/input/event0", O_RDWR);
    if (fd_ts < 0)
    {
        printf("open file fail\n");
        return -1;
    }

    // 将非阻塞属性添加到 fd_ts
    int status = fcntl(fd_ts, F_GETFL); // 得到文件描述符的状态
    status |= O_NONBLOCK;            // 在原来的基础上新增非阻塞属性
    fcntl(fd_ts, F_SETFL, status);      // 把变量status的状态设置到文件描述符中

    struct input_event ts;
    // 此处read函数阻塞是因为缓冲区< 没有 > 数据
    read(fd_ts,&ts,sizeof(struct input_event));
#endif

    return 0;
}