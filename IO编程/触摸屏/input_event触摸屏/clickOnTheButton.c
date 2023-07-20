/*
 * @Description:实现点击一个范围，按钮实现动态效果
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-07-19 11:23:37
 * @LastEditors: ZGG
 * @LastEditTime: 2023-07-19 14:16:51
 */
#include <stdio.h> //ls /usr/include/stdio.h
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <linux/input.h> //ls /usr/include/linux/input.h

#define BUFFER_SIZE 800 * 480 * 4

void show_bmp_on_lcd(int fd_lcd, int *addr, char bmp_path[])
{
    FILE *fp_bmp = fopen(bmp_path, "r+");
    if (fp_bmp == NULL)
    {
        perror("fopen bmp error.");
        return;
    }

    // 读取图片宽度和高度
    int width = 0, height = 0;
    fseek(fp_bmp, 18, SEEK_SET);
    fread(&width, sizeof(int), 1, fp_bmp);
    fread(&height, sizeof(int), 1, fp_bmp);
    printf("width=%d height=%d\n", width, height);
    // 去除bmp格式图片的头54个字节
    fseek(fp_bmp, 54, SEEK_SET);

    // 读取图片信息
    unsigned char buf[BUFFER_SIZE];
    memset(buf, 0, sizeof(buf));
    fread(buf, 1, sizeof(buf), fp_bmp);
    memset(addr, 0, BUFFER_SIZE);

    // 计算偏移量
    int offset_x = (800 - width) / 2;
    int offset_y = (480 - height) / 2;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            *(addr + (offset_y + height - y - 1) * 800 + offset_x + x) =
                buf[(y * width + x) * 3] |
                buf[(y * width + x) * 3 + 1] << 8 |
                buf[(y * width + x) * 3 + 2] << 16 |
                0xff << 24;
        }
    }

    fclose(fp_bmp);
}

int main(int argc, char *argv[])
{
    int fd_lcd = open("/dev/fb0", O_RDWR);
    if (fd_lcd < 0)
    {
        perror("open /dev/fb0 error.");
        return -1;
    }

    // 打开触摸屏
    int fd_ts = open("/dev/input/event0", O_RDONLY);
    if (fd_ts < 0)
    {
        perror("open /dev/input/event0 error.");
        return -1;
    }

    struct input_event ts;
    memset(&ts, 0, sizeof(struct input_event));

    // lcd的映射--mmap
    int *addr = mmap(NULL,                   // If addr is NULL, then the kernel chooses the address
                     BUFFER_SIZE,            // LCD的大小
                     PROT_READ | PROT_WRITE, // LCD的权限
                     MAP_SHARED,             // 标志量
                     fd_lcd,                 // 文件描述符
                     0);                     // 偏移量
    if (addr == NULL)
    {
        perror("mmap fail");
        return -1;
    }

    char bmp_path_down[] = "Down.bmp";
    char bmp_path_up[] = "Up.bmp";
    show_bmp_on_lcd(fd_lcd, addr, bmp_path_up);

    int x = 0, y = 0;
    int is_button_down = 0;

    while (1)
    {
        read(fd_ts, &ts, sizeof(struct input_event));
        if (ts.type == EV_ABS && ts.code == ABS_X)
        {
            x = ts.value * 800 / 1024;
        }
        if (ts.type == EV_ABS && ts.code == ABS_Y)
        {
            y = ts.value * 480 / 600;
        }
        if (ts.type == EV_KEY && ts.code == BTN_TOUCH)
        {
            if (ts.value == 1) // 按下去
            {
                if (x >= 320 && x <= 480 && y >= 240 && y <= 360)
                {
                    if (!is_button_down)
                    {
                        show_bmp_on_lcd(fd_lcd, addr, bmp_path_down);
                        printf("Down x=%d y=%d\n", x, y);
                        is_button_down = 1;
                    }
                }
            }
            else if (ts.value == 0) // 松开
            {
                if (is_button_down)
                {
                    show_bmp_on_lcd(fd_lcd, addr, bmp_path_up);
                    printf("Up x=%d y=%d\n\n", x, y);
                    is_button_down = 0;
                }
            }
        }
    }

    // 解除映射
    munmap(addr, BUFFER_SIZE);

    // 关闭触摸屏
    close(fd_ts);

    // 关闭LCD
    close(fd_lcd);

    return 0;
}
