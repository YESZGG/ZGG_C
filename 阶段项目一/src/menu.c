#include "menu.h"
#include <stdlib.h>
#include <string.h>
#include "mp3.h"
#include "led_control.h"
#include "slideshow.h"
#include "autoplay.h"
#include "admin.h"

enum ScreenState currentScreen = MainMenu;

int show_Exit(int *addr, FILE *fp_exit)
{
    if (fp_exit == NULL)
    {
        fprintf(stderr, "File pointer is null.\n");
        return -1;
    }

    // 清空LCD显示
    memset(addr, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);

    fseek(fp_exit, 18, SEEK_SET);
    int width, height;
    if (fread(&width, sizeof(width), 1, fp_exit) != 1 ||
        fread(&height, sizeof(height), 1, fp_exit) != 1)
    {
        fprintf(stderr, "Failed to read image width and height.\n");
        return -1;
    }

    int offset_x = (SCREEN_WIDTH - width) / 2;
    int offset_y = (SCREEN_HEIGHT - height) / 2;

    show_bmp_image(addr, fp_exit, offset_x, offset_y);

    return 0;
}



// 返回主菜单界面
int show_return_menu(int *addr, FILE *fp_menu)
{
    if (fp_menu == NULL)
    {
        fprintf(stderr, "File pointer is null.\n");
        return -1;
    }

    // 清空LCD显示
    memset(addr, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);

    fseek(fp_menu, 18, SEEK_SET);
    int width, height;
    if (fread(&width, sizeof(width), 1, fp_menu) != 1 ||
        fread(&height, sizeof(height), 1, fp_menu) != 1)
    {
        fprintf(stderr, "Failed to read image width and height.\n");
        return -1;
    }

    int offset_x = (SCREEN_WIDTH - width) / 2;
    int offset_y = (SCREEN_HEIGHT - height) / 2;

    show_bmp_image(addr, fp_menu, offset_x, offset_y);

    return 0;
}

// 处理主菜单界面下的触摸事件
void handleMainMenuTouch(int *addr, FILE *fp_menu, int startX, int startY, int endX, int endY)
{
    ioctl_led(startX, startY, endX, endY);
    // 切换到MP3界面
    if ((startX > 0 && endX < 200) && (startY > 420 && endY < 480))
    {
        // 切换屏幕状态到MP3Screen
        currentScreen = MP3Screen;

        FILE *fp_mp3_start = fopen("MP3_start.bmp", "r");
        if (fp_mp3_start == NULL)
        {
            perror("fopen bmp fail.");
            show_return_menu(addr, fp_menu);
            return;
        }

        if (show_MP3_start(addr, fp_mp3_start) != 0)
        {
            fclose(fp_mp3_start);
            show_return_menu(addr, fp_menu);
            return;
        }
        fclose(fp_mp3_start);
    }
    // 切换到手动播放界面SlideshowScreen
    if ((startX > 200 && endX < 400) && (startY > 0 && endY < 60))
    {
        currentScreen = SlideshowScreen;
        FILE *fp_manual_play = fopen("Manual_play.bmp", "r");
        if (fp_manual_play == NULL)
        {
            perror("fopen bmp fail.");
            show_return_menu(addr, fp_menu);
            return;
        }
        if (show_Manual_play(addr, fp_manual_play) != 0)
        {
            fclose(fp_manual_play);
            show_return_menu(addr, fp_menu);
            return;
        }
        fclose(fp_manual_play);
    }
    // 切换到自动播放界面AutoplayScreen
    if ((startX > 0 && endX < 200) && (startY > 0 && endY < 60))
    {
        currentScreen = AutoplayScreen;
        FILE *fp_auto_play = fopen("Auto_play.bmp", "r");
        if (fp_auto_play == NULL)
        {
            perror("fopen bmp fail.");
            show_return_menu(addr, fp_menu);
            return;
        }
        if (show_Auto_play(addr, fp_auto_play) != 0)
        {
            fclose(fp_auto_play);
            show_return_menu(addr, fp_menu);
            return;
        }
        fclose(fp_auto_play);
    }
    // 切换到管理员界面AdminScreen
    if ((startX > 400 && endX < 600) && (startY > 0 && endY < 60))
    {
        currentScreen = AdminScreen;
        FILE *fp_admin = fopen("Admin.bmp", "r");
        if (fp_admin == NULL)
        {
            perror("fopen Admin.bmp fail.");
            show_return_menu(addr, fp_menu);
            return;
        }
        if (show_Admin(addr, fp_admin) != 0)
        {
            fclose(fp_admin);
            show_return_menu(addr, fp_menu);
            return;
        }
        fclose(fp_admin);
    }
    // 切换到退出界面
    if ((startX > 600 && endX < 800) && (startY > 0 && endY < 60))
    {
        currentScreen = ExitScreen;
        FILE *fp_exit = fopen("Exit.bmp", "r");
        if (fp_exit == NULL)
        {
            perror("fopen Exit.bmp fail.");
            show_return_menu(addr, fp_menu);
            return;
        }
        if (show_Exit(addr, fp_exit) != 0)
        {
            fclose(fp_exit);
            show_return_menu(addr, fp_menu);
            return;
        }
        fclose(fp_exit);
        sleep(2);
        exit(0); 
    }
}
