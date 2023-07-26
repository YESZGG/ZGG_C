#include "menu.h"
#include "open_file.h"


int fd_lcd_open()
{
    int fd_lcd = open(LCD_PATH, O_RDWR);

    if (fd_lcd == -1)
    {
        perror("open lcd fail");
        return -1;
    }
}
