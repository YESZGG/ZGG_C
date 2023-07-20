#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <stdlib.h>

#define THRESHOLD 50

struct TouchEvent {
    int x;
    int y;
    int x_Start;
    int y_Start;
    int x_End;
    int y_End;
};

void slide(int x_Start, int y_Start, int x_End, int y_End);
void handleTouchEvent(int type, int code, int value, struct TouchEvent *event);

void slide(int x_Start, int y_Start, int x_End, int y_End)
{
    int diffX = abs(x_End - x_Start);
    int diffY = abs(y_End - y_Start);

    if (diffX > THRESHOLD || diffY > THRESHOLD)
    {
        if (diffX > diffY)
        {
            if (x_End > x_Start)
            {
                printf("Slide right\n");
            }
            else
            {
                printf("Slide left\n");
            }
        }
        else
        {
            if (y_End > y_Start)
            {
                printf("Slide down\n");
            }
            else
            {
                printf("Slide up\n");
            }
        }
    }
    else
    {
        printf("No slide\n");
    }
}

void handleTouchEvent(int type, int code, int value, struct TouchEvent *event)
{
    if (type == EV_ABS && code == ABS_X)
    {
        event->x = value * 800 / 1024;
    }
    if (type == EV_ABS && code == ABS_Y)
    {
        event->y = value * 480 / 600;
    }

    if (type == EV_KEY && code == BTN_TOUCH && value == 1)
    {
        event->x_Start = event->x;
        event->y_Start = event->y;
        printf("Down x = %d y = %d\n", event->x_Start, event->y_Start);
    }
    if (type == EV_KEY && code == BTN_TOUCH && value == 0)
    {
        event->x_End = event->x;
        event->y_End = event->y;
        printf("Up x = %d y = %d\n", event->x_End, event->y_End);

        slide(event->x_Start, event->y_Start, event->x_End, event->y_End);
    }
}

int main(int argc, char **argv)
{
    int fd_ts;
    fd_ts = open("/dev/input/event0", O_RDWR);
    if (fd_ts < 0)
    {
        perror("open ts fail");
        return -1;
    }

    struct input_event ts;
    memset(&ts, 0, sizeof(struct input_event));

    struct TouchEvent event;

    while (1)
    {
        read(fd_ts, &ts, sizeof(struct input_event));
        handleTouchEvent(ts.type, ts.code, ts.value, &event);
    }

    close(fd_ts);

    return 0;
}
