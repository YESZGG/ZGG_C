#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define BUFFER_SIZE 800 * 480

int *addr = NULL;

void draw(int x, int y, int color)
{
    if (x >= 0 && x < 800 && y >= 0 && y < 480)
    {
        *(addr + x + y * 800) = color;
    }
}

void draw_circle(int center_x, int center_y, int radius, int color)
{
    for (int y = center_y - radius; y <= center_y + radius; y++)
    {
        for (int x = center_x - radius; x <= center_x + radius; x++)
        {
            if ((y - center_y) * (y - center_y) + (x - center_x) * (x - center_x) <= radius * radius)
            {
                draw(x, y, color);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    // 打开设备文件
    int fd_lcd = open("/dev/fb0", O_RDWR);

    // 黑、红、白、黄
    // int black = 0x00000000;
    int red = 0x00ff0000;
    int white = 0x00ffffff;
    // int yellow = 0x00ffff00;

    // lcd的映射 ---- mmap
    addr = mmap(NULL,
                     // If addr is NULL，then the kernel chooses the (page-aligned) address at which to create the mapping;
                     // 如果addr为NULL，那么内核将选择(页面对齐)地址来创建映射；
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

    // 3. 绘制屏幕
    for (int y = 0; y < 480; y++) // 行
    {
        for (int x = 0; x < 800; x++) // 列
        {
            draw(x, y, white); // 绘制白色背景
        }
    }

    // 绘制红色圆形
    int center_x = 400;     // 圆心横坐标
    int center_y = 240;     // 圆心纵坐标
    int radius = 100;       // 半径


    draw_circle(center_x, center_y, radius, red);

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
