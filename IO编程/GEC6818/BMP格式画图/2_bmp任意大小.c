#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

#define BUFFER_SIZE 800 * 480
/*
    实现任意大小的bmp图:
说明：
    制作的bmp图片的宽度和高度必须是4的倍数(像素点补偿)
*/

int main(int argc, char *argv[])
{
    // 打开lcd
    int fd_lcd;
    fd_lcd = open("/dev/fb0", O_RDWR);
    if (fd_lcd < 0)
    {
        perror("open lcd fail");
        return -1;
    }

    // lcd的映射--mmap
    int *addr = mmap(NULL,                   // If addr is NULL, then the kernel chooses the address
                     800 * 480 * 4,          // LCD的大小
                     PROT_READ | PROT_WRITE, // LCD的权限
                     MAP_SHARED,             // 标志量
                     fd_lcd,                 // 文件描述符
                     0);                     // 偏移量
    if (addr == NULL)
    {
        perror("mmap fail");
        return -1;
    }

    // 创建文件描述符 打开图片文件
    int fd_bmp = open("4.bmp", O_RDWR);
    if (fd_bmp < 0)
    {
        perror("open bmp fail.");
        return -1;
    }
    // 1.读出任意bmp图片的宽度和高度
    int width = 0, height = 0;   // char buf[4]
    lseek(fd_bmp, 18, SEEK_SET); // 跳过前18个字节 后面16进制第12个就是宽度、高度

    read(fd_bmp, &width, 4);  // 读出它的宽度
    read(fd_bmp, &height, 4); // 读出它的高度
    printf("bmp width:%d height:%d\n", width, height);

    // 2.去除bmp格式图片的头54个字节    因为bmp前54个字节存储的是图片格式、描述信息。  (无效的)
    lseek(fd_bmp, 54, SEEK_SET);

    // 3.读取图片信息
    char buf[BUFFER_SIZE * 3];   // 因为bmp图片格式，每一个像素点为3个字节，不同于LCD每个像素点4个字节
    memset(buf, 0, sizeof(buf)); // 初始化为0

    read(fd_bmp, buf, sizeof(buf));

    // 偏移图片  刚开始的图片坐标
    int offset_x = 100;
    int offset_y = 100;

    // 将读取到的图片信息写入到LCD中
    int x = 0; // 横轴
    int y = 0; // 纵轴
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            // 如果是480就段错误 超过了数组的范围
            *(addr + (offset_y + height - 1 - y) * 800 + offset_x + x) = buf[(y * width + x) * 3] |
                                                                         buf[(y * width + x) * 3 + 1] << 8 |
                                                                         buf[(y * width + x) * 3 + 2] << 16;
        }
    }

    // lcd映射的释放
    munmap(addr, BUFFER_SIZE * 4);

    // 关闭bmp
    close(fd_bmp);
    // 关闭lcd
    close(fd_lcd);

    return 0;
}
