#include <stdio.h> //ls /usr/include/stdio.h
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h> //ls /usr/include/linux/input.h
#include <stdlib.h>

// #define EV_ABS 0x3       // 触摸屏事件类型
// #define EV_KEY 0x1       // 按键事件类型
// #define ABS_x 0x00       // x轴编码
// #define ABS_Y 0x01       // y轴编码
// #define BTN_TOUCH 0x14a  // 按键编码
#define THRESHOLD 50 // 判定为滑动的阈值
/*
    触摸屏、lcd都是设备文件(硬件文件):只能用系统IO打开
*/
enum SLIDE_STATUS
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    CLICK
};

int slide(int x_Start, int y_Start, int x_End, int y_End)
{
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

int main(int argc, char **argv)
{
    // 打开触摸屏(设备文件需要用系统IO)
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

    int x, y;
    int x_Start, y_Start; // 起始坐标
    int x_End, y_End;     // 终点坐标
    // 读触摸屏信息
    while (1)
    {
        // 此处的read是一个带阻塞属性的函数
        read(fd_ts, &ts, sizeof(struct input_event));
        if (ts.type == EV_ABS && ts.code == ABS_X)
        {
            x = ts.value * 800 / 1024;
        }
        if (ts.type == EV_ABS && ts.code == ABS_Y)
        {
            y = ts.value * 480 / 600;
        }

        if (ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 1) // 按下去的坐标
        {
            x_Start = x;
            y_Start = y;
            printf("Down x = %d y = %d\n", x_Start, y_Start);
        }
        if (ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 0) // 松开的坐标
        {
            x_End = x;
            y_End = y;
            printf("Up x = %d y = %d\n", x_End, y_End);
            // 判断滑动情况
            int ret = slide(x_Start, y_Start, x_End, y_End);
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
                    break;
                case RIGHT:
                    printf("Slide right\n\n");
                    break;
                case CLICK: // 点击
                    printf("Click\n\n");
                    break;
                default:
                    break;
            }
        }
    }

    // 关闭触摸屏
    close(fd_ts);

    return 0;
}
