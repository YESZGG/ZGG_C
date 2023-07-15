#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <time.h>

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

    int dx = 3; // 水平方向速度
    int dy = 3; // 垂直方向速度

    while (1)
    {
        // 更新位置
        center_x += dx;
        center_y += dy;

        // 检测碰撞屏幕边界
        if (center_x - radius <= 0 || center_x + radius >= 800)
        {
            dx = -dx; // 水平方向取反
        }

        if (center_y - radius <= 0 || center_y + radius >= 480)
        {
            dy = -dy; // 垂直方向取反
        }

        // 清空屏幕为红色
        for (int y = 0; y < 480; y++) // 行
        {
            for (int x = 0; x < 800; x++) // 列
            {
                draw(x, y, red); // 绘制红色背景
                // 绘制太极图
                if ((y - center_y) * (y - center_y) + (x - center_x) * (x - center_x) <= (radius * radius) && x <= center_x)
                {
                    draw(x, y, black);
                }
                if ((y - center_y) * (y - center_y) + (x - center_x) * (x - center_x) <= (radius * radius) && x >= center_x)
                {
                    draw(x, y, white);
                }
                if ((y - center_y + scradius) * (y - center_y + scradius) + (x - center_x) * (x - center_x) <= scradius * scradius && x <= center_x)
                {
                    draw(x, y, white);
                }
                if ((y - center_y - scradius) * (y - center_y - scradius) + (x - center_x) * (x - center_x) <= scradius * scradius && x >= center_x)
                {
                    draw(x, y, black);
                }
                if ((y - center_y + scradius) * (y - center_y + scradius) + (x - center_x) * (x - center_x) <= smallradius * smallradius)
                {
                    draw(x, y, black);
                }
                if ((y - center_y - scradius) * (y - center_y - scradius) + (x - center_x) * (x - center_x) <= smallradius * smallradius)
                {
                    draw(x, y, white);
                }
            }
        }


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
