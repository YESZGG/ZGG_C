#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/input.h>
#include <stdlib.h>
#include <sys/ioctl.h> // 控制led头文件
// #include "lcdjpg.h"

#define THRESHOLD 50                   // 滑动阀值
#define BUFFER_SIZE 800 * 480          // 缓存空间
#define SCREEN_WIDTH 800               // LCD的宽度
#define SCREEN_HEIGHT 480              // LCD的高度
#define LCD_PATH "/dev/fb0"            // LCD文件路径
#define INPUT_PATH "/dev/input/event0" // EVENT0事件文件路径

#define TEST_MAGIC 'x' // 定义幻数

#define LED1 _IO(TEST_MAGIC, 0)
#define LED2 _IO(TEST_MAGIC, 1)
#define LED3 _IO(TEST_MAGIC, 2)
#define LED4 _IO(TEST_MAGIC, 3)

#define LED_ON 0  // 灯亮
#define LED_OFF 1 // 灯灭

// 控制亮灯
void led_on(int fd_led, int leds)
{
    ioctl(fd_led, leds, LED_ON);
}

// 控制灭灯
void led_off(int fd_led, int leds)
{
    ioctl(fd_led, leds, LED_OFF);
}

// 判断亮灯 或 灭灯
void ioctl_led(int startX, int startY, int endX, int endY)
{
    // 定义LED数组
    int leds[] = {LED1, LED2, LED3, LED4};

    // 获取LED数组的长度
    int num_leds = sizeof(leds) / sizeof(leds[0]);

    // 打开LED灯设备文件
    int fd_led = open("/dev/Led", O_RDWR);
    // 打开小灯
    if ((startX > 200 && endX < 400) && (startY > 420 && endY < 480))
    {
        for (int i = 0; i < num_leds; i++)
        {
            led_on(fd_led, leds[i]);
            usleep(50000);// 每个小灯打开之间延迟0.05s
        }
    }

    // 关闭小灯
    if ((startX > 400 && endX < 600) && (startY > 420 && endY < 480))
    {
        for (int i = 0; i < num_leds; i++)
        {
            led_off(fd_led, leds[i]);
            usleep(50000);// 每个小灯关灯之间延迟0.05s
        }
    }
    // 关闭LED设备文件
    close(fd_led);
}

int main(int argc, char *argv[])
{
    int black = 0x00000000;

    // 打开LCD文件
    int fd_lcd = open(LCD_PATH, O_RDWR);
    if (fd_lcd == -1)
    {
        perror("open lcd fail");
        return -1;
    }

    // 打开EVENT0事件文件
    int fd_ts = open(INPUT_PATH, O_RDONLY);
    if (fd_ts == -1)
    {
        perror("open event0 fail");
        close(fd_lcd);
        return -1;
    }

    char photo_path[] = {"desktop.bmp"};
    // 打开待显示图片文件 --- 主菜单界面
    FILE *fp_bmp = fopen(photo_path, "r+");
    if (fp_bmp == NULL)
    {
        perror("fopen bmp fail.");
        return -1;
    }

    // 读取图片宽度和高度
    int width = 0, height = 0;
    fseek(fp_bmp, 18, SEEK_SET);
    fread(&width, 1, 4, fp_bmp);
    fread(&height, 1, 4, fp_bmp);

    // 去除bmp格式图片的头54个字节
    fseek(fp_bmp, 54, SEEK_SET);

    // 读取图片信息
    unsigned char buf[BUFFER_SIZE * 3];
    memset(buf, 0, sizeof(buf));
    fread(buf, 1, sizeof(buf), fp_bmp);

    // 映射LCD内存
    int *addr = mmap(NULL,                   // 如果 addr 是 NULL，那么内核将选择映射地址
                     BUFFER_SIZE * 4,        // LCD的大小（每个像素点4字节）
                     PROT_READ | PROT_WRITE, // LCD的权限
                     MAP_SHARED,             // 标志量
                     fd_lcd,                 // 文件描述符
                     0);                     // 偏移量
    if (addr == MAP_FAILED)
    {
        perror("mmap fail");
        return -1;
    }

    memset(addr, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);

    // 计算偏移量
    int offset_x = (SCREEN_WIDTH - width) / 2;
    int offset_y = (SCREEN_HEIGHT - height) / 2;

    // 将图片信息写入到LCD中
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            unsigned char b = buf[(y * width + x) * 3];
            unsigned char g = buf[(y * width + x) * 3 + 1];
            unsigned char r = buf[(y * width + x) * 3 + 2];
            *(addr + (offset_y + height - 1 - y) * SCREEN_WIDTH + offset_x + x) = (r << 16) | (g << 8) | b;
        }
    }
    // 定义一个存储触摸屏信息的结构体
    struct input_event ts; // 由内核提供额接口
    memset(&ts, 0, sizeof(struct input_event));

    int x = 0, y = 0;
    int startX, startY;
    int endX, endY;
    // 读触摸屏信息
    while (1)
    {
        // 此处的read是一个带阻塞属性的函数
        read(fd_ts, &ts, sizeof(struct input_event));
        if (ts.type == EV_ABS && ts.code == ABS_X)
        {
            x = ts.value * SCREEN_WIDTH / 1024;
        }
        if (ts.type == EV_ABS && ts.code == ABS_Y)
        {
            y = ts.value * SCREEN_HEIGHT / 600;
        }
        if (ts.type == EV_KEY && ts.code == BTN_TOUCH)
        {
            if (ts.value == 1)
            {
                startX = x;
                startY = y;
            }
            else if (ts.value == 0)
            {
                endX = x;
                endY = y;

                ioctl_led(startX, startY, endX, endY);
            }
        }
    }
    // 关闭文件描述符
    close(fd_ts);
    close(fd_lcd);

    return 0;
}
