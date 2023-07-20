/*
 * @Description: 4_ts获取触摸屏的坐标值
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-07-18 17:04:14
 * @LastEditors: ZGG
 * @LastEditTime: 2023-07-19 14:32:13
 */
#include <stdio.h> //ls /usr/include/stdio.h
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h> //ls /usr/include/linux/input.h

// #define EV_ABS 0x3       // 触摸屏事件类型
// #define EV_KEY 0x1       // 按键事件类型
// #define ABS_x 0x00       // x轴编码
// #define ABS_Y 0x01       // y轴编码
// #define BTN_TOUCH 0x14a  // 按键编码

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

    int x = 0, y = 0;
    // 读触摸屏信息
    while (1)
    {
        // 此处的read是一个带阻塞属性的函数
        read(fd_ts, &ts, sizeof(struct input_event));
        if (ts.type == EV_ABS && ts.code == ABS_X) // x轴坐标值
        {
            // printf("x=%d ", ts.value * 800 / 1024); // 黑色的板子1024 * 600 转化为 800 * 480
            x = ts.value * 800 / 1024;
        }
        if (ts.type == EV_ABS && ts.code == ABS_Y) // y轴坐标值
        {
            // printf("y=%d\n", ts.value * 480 / 600); // 黑色的板子1024 * 600 转化为 800 * 480
            y = ts.value * 480 / 600;
        }
        if (ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 1) // 按下去的坐标
        {
            printf("Down x = %d y = %d\n", x, y);
        }
        if (ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 0) // 松开的坐标
        {
            printf("Up x = %d y = %d\n", x, y);
        }
    }

    // 关闭触摸屏
    close(fd_ts);

    return 0;
}
