#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/input.h>

#define BUFFER_SIZE 800 * 480         // 缓存空间
#define SCREEN_WIDTH 800              // LCD的宽度
#define SCREEN_HEIGHT 480             // LCD的高度
#define LCD_PATH "/dev/fb0"           // LCD文件路径
#define INPUT_PATH "/dev/input/event0"// EVENT0事件文件路径

enum ScreenState
{
    MainMenu,
    MP3Screen,
    SlideshowScreen,
    AutoplayScreen,
    AdminScreen,
    ExitScreen
};


extern int show_return_menu(int *addr, FILE *fp_menu);
extern void handleMainMenuTouch(int *addr, FILE *fp_menu, int startX, int startY, int endX, int endY);


#endif
