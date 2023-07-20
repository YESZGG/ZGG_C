#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/input.h>
#include <stdlib.h>

#define THRESHOLD 50
enum SLIDE_STATUS
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    CLICK
};
int handle_touch_events(int fd_ts);

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

int handle_touch_events(int fd_ts)
{
    struct input_event ts;
    memset(&ts, 0, sizeof(struct input_event));

    int x, y;
    int x_Start, y_Start;
    int x_End, y_End;
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

        if (ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 1)
        {
            x_Start = x;
            y_Start = y;
            printf("Down x = %d y = %d\n", x_Start, y_Start);
        }
        if (ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 0)
        {
            x_End = x;
            y_End = y;
            printf("Up x = %d y = %d\n", x_End, y_End);

            int diffX = abs(x_End - x_Start); // 计算横向滑动的距离差值
            int diffY = abs(y_End - y_Start); // 计算纵向滑动的距离差值

            if (diffX > THRESHOLD || diffY > THRESHOLD) // 如果横向或纵向的距离差值超过阈值
            {
                if (diffX > diffY) // 如果横向距离差值大于纵向距离差值，则判定为横向滑动
                {
                    if (x_End > x_Start) // 如果终点坐标大于起始坐标，则判定为向右滑动
                    {
                        // printf("Slide right\n");
                        return RIGHT;
                    }
                    else // 否则判定为向左滑动
                    {
                        // printf("Slide left\n");
                        return LEFT;
                    }
                }
                else // 如果纵向距离差值大于等于横向距离差值，则判定为纵向滑动
                {
                    if (y_End > y_Start) // 如果终点坐标大于起始坐标，则判定为向下滑动
                    {
                        // printf("Slide down\n");
                        return DOWN;
                    }
                    else // 否则判定为向上滑动
                    {
                        // printf("Slide up\n");
                        return UP;
                    }
                }
            }
            else // 如果距离差值都小于等于阈值，则判定为没有发生滑动
            {
                // printf("Click\n");
                return CLICK;
            }
        }
    }
}

int main(int argc, char *argv[])
{

    int fd_lcd = open("/dev/fb0", O_RDWR);
    if (fd_lcd < 0)
    {
        perror("open /dev/fb0 error.");
        return -1;
    }

    int fd_ts;
    fd_ts = open("/dev/input/event0", O_RDWR);
    if (fd_ts < 0)
    {
        perror("open ts fail");
        return -1;
    }

    char *bmp_files[] = {"1.bmp", "2.bmp", "3.bmp", "4.bmp", "5.bmp"};
    int bmp_size = sizeof(bmp_files) / sizeof(bmp_files[0]);
    int current_bmp = 0;

    show_bmp_on_lcd(fd_lcd, bmp_files[current_bmp]);

    while (1)
    {
        int ret = handle_touch_events(fd_ts);
        switch (ret)
        {
        case UP:
            printf("Slide up\n\n");
            break;
        case DOWN:
            printf("Slide down\n\n");
            break;
        case LEFT:
            printf("Slide left\n\n");
            current_bmp = (current_bmp - 1 + bmp_size) % bmp_size;
            show_bmp_on_lcd(fd_lcd, bmp_files[current_bmp]);
            break;
        case RIGHT:
            printf("Slide right\n\n");
            current_bmp = (current_bmp + 1) % bmp_size;
            show_bmp_on_lcd(fd_lcd, bmp_files[current_bmp]);
            break;
        case CLICK: // 点击
            printf("Click\n\n");
            break;
        default:
            break;
        }
    }

    close(fd_ts);

    return 0;
}
