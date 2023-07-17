#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 800*480

int main(int argc, char *argv[])
{
    // 打开设备文件
    int fd_lcd = open("/dev/fb0", O_RDWR);

    int buffer[BUFFER_SIZE];

    int x = 0, y = 0; // 长、高

    // 黑、红、黄
    int black = 0x00000000;
    int red = 0x00ff0000;
    int yellow = 0x00ffff00;
    for (y = 0; y < 160; y++)
    {
        for (x = 0; x < 800; x++)
        {
            buffer[y * 800 + x] = black;
        }
    }
    for (y = 160; y < 320; y++)
    {
        for (x = 0; x < 800; x++)
        {
            buffer[y * 800 + x] = red;
        }
    }
    for (y = 320; y < 480; y++)
    {
        for (x = 0; x < 800; x++)
        {
            buffer[y * 800 + x] = yellow;
        }
    }

    // 写lcd--写的时候写的是800*480*4byte不是800*480
    write(fd_lcd, buffer, BUFFER_SIZE * 4);

    // 关闭lcd
    close(fd_lcd);
}