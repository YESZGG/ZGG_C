#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

#define BUFFER_SIZE 800 * 480

int main(int argc, char *argv[])
{
    // 打开设备文件
    int fd_lcd = open("/dev/fb0", O_RDWR);

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

    // 创建文件描述符 打开图片文件
    int fd_bmp = open("3.bmp", O_RDWR);
    if (fd_bmp < 0)
    {
        perror("open bmp fail.");
        return -1;
    }

    // 1.去除bmp格式图片的头54个字节    因为bmp前54个字节存储的是图片格式、描述信息。  (无效的)
    lseek(fd_bmp, 54, SEEK_SET);

    // 2.读取图片信息
    char buf[BUFFER_SIZE * 3];   // 因为bmp图片格式，每一个像素点为3个字节，不同于LCD每个像素点4个字节
    memset(buf, 0, sizeof(buf)); // 初始化为0

    read(fd_bmp,buf,sizeof(buf));

    // 3.将读取到的图片信息映射到LCD中
    for (int y = 0; y < 480; y++)
    {
        for (int x = 0; x < 800; x++)
        {
            /*
                *(addr+y*800+x) = buf;
                *(addr+y*800+x) = buf[xy表达式] | buf[xy表达式]<<8 | buf[xy表达式]<<16;
             */
            // 如果是480就段错误 超过了数组的范围
            *(addr + (479 - y) * 800 + x) = buf[(y * 800 + x) * 3] | buf[(y * 800 + x) * 3 + 1] << 8 | buf[(y * 800 + x) * 3 + 2] << 16;
        }
    }

    // lcd映射的释放
    munmap(addr, BUFFER_SIZE * 4);

    // 关闭lcd
    close(fd_bmp);
    close(fd_lcd);
}