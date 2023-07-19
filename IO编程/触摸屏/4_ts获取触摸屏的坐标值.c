/*
 * @Description: 4_ts获取触摸屏的坐标值
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-07-18 17:04:14
 * @LastEditors: ZGG
 * @LastEditTime: 2023-07-18 17:28:26
 */
#include <stdio.h> //ls /usr/include/stdio.h
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h> //ls /usr/include/linux/input.h

/*
    触摸屏、lcd都是设备文件(硬件文件):只能用系统IO打开
*/

int main(int argc, char **argv)
{
    // 打开触摸屏(设备文件需要用系统IO)
    int fd_ts;
    fd_ts = open("/dev/input/event0", O_RDWR);
    if (fd_ts < 0)
    {
        perror("open ts fail");
        return -1;
    }

    // 定义一个存储触摸屏信息的结构体
    struct input_event ts; // 由内核提供额接口
    memset(&ts, 0, sizeof(struct input_event));

    // 读触摸屏信息
    while (1)
    {
        // 此处的read是一个带阻塞属性的函数
        read(fd_ts, &ts, sizeof(struct input_event));
        if (ts.type == 3 && ts.code == 0) // x轴坐标值
        {
            printf("x=%d ", ts.value * 800 / 1024);// 黑色的板子1024 * 600 转化为 800 * 480 
        }
        if (ts.type == 3 && ts.code == 1) // y轴坐标值
        {
            printf("y=%d\n", ts.value * 480 / 600);// 黑色的板子1024 * 600 转化为 800 * 480
        }
    }

    // 关闭触摸屏
    close(fd_ts);

    return 0;
}
