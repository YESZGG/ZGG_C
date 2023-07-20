/*
 * @Description: 点击左边显示800*480的图片，点击右边显示小于800*480的图片
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-07-18 19:09:49
 * @LastEditors: ZGG
 * @LastEditTime: 2023-07-19 14:26:53
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <linux/input.h>

#define BUFFER_SIZE 800 * 480

void show_bmp_on_lcd(int fd_lcd, char bmp_files[])
{
    // lcd的映射--mmap
    int *addr = mmap(NULL,                   // If addr is NULL, then the kernel chooses the address
                     BUFFER_SIZE * 4,        // LCD的大小
                     PROT_READ | PROT_WRITE, // LCD的权限
                     MAP_SHARED,             // 标志量
                     fd_lcd,                 // 文件描述符
                     0);                     // 偏移量
    if (addr == NULL)
    {
        perror("mmap fail");
        return;
    }
    FILE *fp_bmp = fopen(bmp_files, "r+");
    if (fp_bmp == NULL)
    {
        perror("fopen bmp fail.");
        return;
    }

    // 读取图片宽度和高度
    int width = 0, height = 0;
    fseek(fp_bmp, 18, SEEK_SET);
    fread(&width, 1, 4, fp_bmp);
    fread(&height, 1, 4, fp_bmp);

    // 去除bmp格式图片的头54个字节
    fseek(fp_bmp, 54, SEEK_SET);

    // 读取图片信息
    char buf[BUFFER_SIZE * 3];
    memset(buf, 0, sizeof(buf));
    fread(buf, 1, sizeof(buf), fp_bmp);

    memset(addr, 0, 800 * 480 * 4);

    // 计算偏移量
    int offset_x = (800 - width) / 2;
    int offset_y = (480 - height) / 2;

    // 将读取到的图片信息写入到LCD中
    int x = 0;
    int y = 0;
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            // 此处的原型为 : buf[ 800*y + x ]  --> buf[ 800*(479-y) +x ]   随后x和y变成了有偏移量的x y
            *(addr + (offset_y + height - 1 - y) * 800 + offset_x + x) = buf[(y * width + x) * 3] |
                                                                         buf[(y * width + x) * 3 + 1] << 8 |
                                                                         buf[(y * width + x) * 3 + 2] << 16;
        }
    }
    // lcd映射的释放
    munmap(addr, BUFFER_SIZE * 4);
    // 关闭fp_bmp
    fclose(fp_bmp);
}

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
    // 打开触摸屏
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

    char *bmp_files_large[] = {"2.bmp", "3.bmp"};
    char *bmp_files_small[] = {"1.bmp", "4.bmp", "5.bmp"};
    int i = 0, j = 0;
    // 读触摸屏信息
    while (1)
    {
        // 此处的read是一个带阻塞属性的函数
        read(fd_ts, &ts, sizeof(struct input_event));
        if (ts.type == 3 && ts.code == 0) // x轴坐标值
        {
            int x = ts.value * 800 / 1024; // 黑色的板子1024 * 600 转化为 800 * 480
            printf("value = %d\n", x);
            if (x < 400) // 点击左边
            {
                if (i == 2)
                {
                    i = 0;
                }
                // 显示800x480的图片
                for (i; i < sizeof(bmp_files_large) / sizeof(bmp_files_large[0]);)
                {
                    show_bmp_on_lcd(fd_lcd, bmp_files_large[i]);
                    i++;
                    break;
                }
            }
            else // 点击右边
            {
                if (j == 3)
                {
                    j = 0;
                }
                // 显示小于800x480的图片
                for (j; j < sizeof(bmp_files_small) / sizeof(bmp_files_small[0]);)
                {
                    show_bmp_on_lcd(fd_lcd, bmp_files_small[j]);
                    j++;
                    break;
                }
            }
        }
    }
    // 关闭lcd
    close(fd_lcd);

    // 关闭触摸屏
    close(fd_ts);

    return 0;
}