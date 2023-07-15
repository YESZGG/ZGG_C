#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> // 添加 math.h 头文件

#define BUFFER_SIZE 800 * 480

int *addr = NULL;

void draw(int x, int y, int color)
{
    if (x >= 0 && x < 800 && y >= 0 && y < 480)
    {
        *(addr + x + y * 800) = color;
    }
}

int main(int argc, char *argv[])
{
    // 打开设备文件
    int fd_lcd = open("/dev/fb0", O_RDWR);

    // 白色、黑色
    int white = 0x00ffffff;
    int black = 0x00000000;
    int red = 0x00ff0000;
    int green = 0x0000ff00;
    int blue = 0x000000ff;

    // lcd的映射 ---- mmap
    addr =
        mmap(NULL,
             BUFFER_SIZE * 4,        // LCD的大小
             PROT_READ | PROT_WRITE, // LCD的权限
             MAP_SHARED,             // 标志量
             fd_lcd,                 // 文件描述符
             0);                     // 偏移量

    if (addr == NULL)
    {
        perror("mmap failed.");
        return -1;
    }

    // 绘制太极图
    int center_x = 400; // 圆心横坐标
    int center_y = 240; // 圆心纵坐标
    int radius = 100;   // 半径

    int scradius = 50;    // 半圆半径
    int smallradius = 15; // 小圆半径

    // 循环条件
    int angle = 0; // 初始化旋转角度为0

    while (1)
    {
        // 清空屏幕为红色
        for (int y = 0; y < 480; y++) // 行
        {
            for (int x = 0; x < 800; x++) // 列
            {
                draw(x, y, red); // 绘制红色背景
                // 根据旋转角度计算对应位置
                double radians = angle * M_PI / 180; // 将角度转换为弧度
                int rotate_x = (x - center_x) * cos(radians) - (y - center_y) * sin(radians) + center_x;
                int rotate_y = (x - center_x) * sin(radians) + (y - center_y) * cos(radians) + center_y;
                if ((rotate_y - center_y) * (rotate_y - center_y) + (rotate_x - center_x) * (rotate_x - center_x) <= (radius * radius) && rotate_x <= center_x)
                {
                    draw(x, y, black);
                }
                if ((rotate_y - center_y) * (rotate_y - center_y) + (rotate_x - center_x) * (rotate_x - center_x) <= (radius * radius) && rotate_x >= center_x)
                {
                    draw(x, y, white);
                }
                if ((rotate_y - center_y + scradius) * (rotate_y - center_y + scradius) + (rotate_x - center_x) * (rotate_x - center_x) <= scradius * scradius && rotate_x <= center_x)
                {
                    draw(x, y, white);
                }
                if ((rotate_y - center_y - scradius) * (rotate_y - center_y - scradius) + (rotate_x - center_x) * (rotate_x - center_x) <= scradius * scradius && rotate_x >= center_x)
                {
                    draw(x, y, black);
                }
                if ((rotate_y - center_y + scradius) * (rotate_y - center_y + scradius) + (rotate_x - center_x) * (rotate_x - center_x) <= smallradius * smallradius)
                {
                    draw(x, y, black);
                }
                if ((rotate_y - center_y - scradius) * (rotate_y - center_y - scradius) + (rotate_x - center_x) * (rotate_x - center_x) <= smallradius * smallradius)
                {
                    draw(x, y, white);
                }
            }
        }

        // 增加旋转角度
        angle += 5; // 每次增加1度
        if (angle >= 360)
            angle = 0; // 重置角度为0，重新开始旋转
    }

    // lcd映射的释放
    int ret = munmap(addr, BUFFER_SIZE * 4);
    if (ret == -1)
    {
        printf("munmap failed\n");
        return -1;
    }

    // 关闭lcd
    int close_ret = close(fd_lcd);
    if (close_ret == -1)
    {
        printf("close failed.\n");
        return -1;
    }
    return 0;
}
