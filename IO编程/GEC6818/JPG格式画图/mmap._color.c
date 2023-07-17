#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define BUFFER_SIZE 800 * 480

int main(int argc, char *argv[])
{
    // 打开设备文件
    int fd_lcd = open("/dev/fb0", O_RDWR);

    int x = 0, y = 0; // 横轴、竖轴

    // 黑、红、黄
    int black = 0x00000000;
    int red = 0x00ff0000;
    int yellow = 0x00ffff00;

    // lcd的映射 ---- mmap
    int *addr = mmap(NULL,
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

    for (y = 0; y < 160; y++)
    {
        for (x = 0; x < 800; x++)
        {
            *(addr + y * 800 + x) = black;
        }
    }
    for (y = 160; y < 320; y++)
    {
        for (x = 0; x < 800; x++)
        {
            *(addr + y * 800 + x) = red;
        }
    }
    for (y = 320; y < 480; y++)
    {
        for (x = 0; x < 800; x++)
        {
            *(addr + y * 800 + x) = yellow;
        }
    }

    // lcd映射的释放
    munmap(addr,BUFFER_SIZE*4);

    // 关闭lcd
    close(fd_lcd);
}