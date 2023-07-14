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

void draw_circle(int center_x, int center_y, int radius)
{
    for (int y = center_y - radius; y <= center_y + radius; y++)
    {
        for (int x = center_x - radius; x <= center_x + radius; x++)
        {
            if ((y - center_y) * (y - center_y) + (x - center_x) * (x - center_x) <= (radius * radius) && x <= center_x)
            {
                draw(x, y, 0x00000000);
            }
            if ((y - center_y) * (y - center_y) + (x - center_x) * (x - center_x) <= (radius * radius) && x >= center_x)
            {
                draw(x, y, 0x00ffffff);
            }
        }
    }
}

void draw_taiji(int center_x, int center_y, int radius)
{
    int i, j;
    int scradius = 50;    // 半圆半径
    int smallradius = 15; // 小圆半径
    for (i = center_y - radius; i <= center_y + radius; i++)
    {
        for (j = center_x - radius; j <= center_x + radius; j++)
        {
            if ((i - center_y + scradius) * (i - center_y + scradius) + (j - center_x) * (j - center_x) <= scradius * scradius && j <= center_x)
            {
                draw(j, i, 0x00ffffff);
            }
            if ((i - center_y - scradius) * (i - center_y - scradius) + (j - center_x) * (j - center_x) <= scradius * scradius && j >= center_x)
            {
                draw(j, i, 0x00000000);
            }
            if ((i - center_y + scradius) * (i - center_y + scradius) + (j - center_x) * (j - center_x) <= smallradius * smallradius)
            {
                draw(j, i, 0x00000000);
            }
            if ((i - center_y - scradius) * (i - center_y - scradius) + (j - center_x) * (j - center_x) <= smallradius * smallradius)
            {
                draw(j, i, 0x00ffffff);
            }
        }
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

    // 清空屏幕为白色
    for (int y = 0; y < 480; y++) // 行
    {
        for (int x = 0; x < 800; x++) // 列
        {
            draw(x, y, red); // 绘制红色背景
        }
    }

    // 绘制太极图
    int center_x = 400; // 圆心横坐标
    int center_y = 240; // 圆心纵坐标
    int radius = 100;   // 半径

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

        // 清空屏幕为白色
        for (int y = 0; y < 480; y++) // 行
        {
            for (int x = 0; x < 800; x++) // 列
            {
                draw(x, y, red); // 绘制红色背景
            }
        }

        // 绘制太极图
        draw_circle(center_x, center_y, radius);

        draw_taiji(center_x, center_y, radius);

        // 等待一段时间，以控制动画的速度
        usleep(100000); // 10毫秒
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
