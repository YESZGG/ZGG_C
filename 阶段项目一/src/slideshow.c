#include "slideshow.h"
#include "mp3.h"
#include "lcdjpg.h"
#include <stdlib.h>
#include <string.h>


// 使用LCD库显示图像的功能（JPEG格式）
void displayJPEGImage(const char *filename)
{
    lcd_draw_jpg_centered(filename, NULL, 0, 0);
}

// 使用LCD库显示图像的功能（BMP格式）
void displayBMPImage(const char *filename, int *addr)
{
    FILE *fp_bmp = fopen(filename, "rb");
    if (fp_bmp == NULL)
    {
        perror("fopen BMPImage fail.");
        return;
    }
    memset(addr, 0, 800 * 420 * 4);

    fseek(fp_bmp, 18, SEEK_SET);
    int width = 0, height = 0;
    if (fread(&width, sizeof(width), 1, fp_bmp) != 1 ||
        fread(&height, sizeof(height), 1, fp_bmp) != 1)
    {
        fprintf(stderr, "Failed to read image width and height.\n");
        return;
    }

    int offset_x = (SCREEN_WIDTH - width) / 2;
    int offset_y = (SCREEN_HEIGHT - 60 - height) / 2;

    fseek(fp_bmp, 54, SEEK_SET);

    unsigned char buf[width * height * 3];
    memset(buf, 0, sizeof(buf));
    if (fread(buf, 1, sizeof(buf), fp_bmp) != sizeof(buf))
    {
        fprintf(stderr, "Failed to read image data.\n");
        return;
    }

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
    fclose(fp_bmp);
}

// 判断滑动方向
int SlideDirection(int startX, int startY, int endX, int endY)
{
    int diffX = abs(endX - startX);
    int diffY = abs(endY - startY);

    if (diffX > THRESHOLD || diffY > THRESHOLD)
    {
        if (diffX > diffY)
        {
            if (endX > startX)
            {
                // Right slide
                return RIGHT;
            }
            else
            {
                // Left slide
                return LEFT;
            }
        }
    }
}

// 处理手动播放界面的input事件
int playSlideshow(Node *head, Node **current, int *addr, int startX, int startY, int endX, int endY)
{
    // EXIT 退出手动播放功能
    if ((startX > 600 && endX < 800) && (startY > 420 && endY < 480))
    {
        // 切换屏幕状态到 MainMenu
        currentScreen = MainMenu;

        FILE *fp_menu = fopen("desktop.bmp", "r+");
        if (fp_menu == NULL)
        {
            perror("fopen bmp fail.");
            return -1;
        }

        if (show_return_menu(addr, fp_menu) != 0)
        {
            fclose(fp_menu);
            return -1;
        }
        fclose(fp_menu);
        return -1;
    }
    int slideDirection = SlideDirection(startX, startY, endX, endY);
    if (slideDirection == LEFT)
    {
        *current = (*current)->next; // 下一张图片

        // 如果到达头部节点，则移动到头部之后的第一个节点
        if (*current == head)
        {
            *current = head->next;
        }
    }
    else if (slideDirection == RIGHT)
    {
        *current = (*current)->previous; // 上一张图片

        // 如果到达头部节点，则移动到头部之前的最后一个节点
        if (*current == head)
        {
            *current = head->previous;
        }
    }

    // 展示当前图片
    if (strstr((*current)->filename, ".bmp") != NULL)
    {
        displayBMPImage((*current)->filename, addr);
    }
    else if (strstr((*current)->filename, ".jpg") != NULL)
    {
        displayJPEGImage((*current)->filename);
    }

    return 0;
}

// 显示手动播放界面
int show_Manual_play(int *addr, FILE *fp_manual_play)
{
    if (fp_manual_play == NULL)
    {
        fprintf(stderr, "File pointer is null.\n");
        return -1;
    }

    // 清空LCD显示
    memset(addr, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);

    fseek(fp_manual_play, 18, SEEK_SET);
    int width, height;
    if (fread(&width, sizeof(width), 1, fp_manual_play) != 1 ||
        fread(&height, sizeof(height), 1, fp_manual_play) != 1)
    {
        fprintf(stderr, "Failed to read image width and height.\n");
        return -1;
    }

    int offset_x = (SCREEN_WIDTH - width) / 2;
    int offset_y = (SCREEN_HEIGHT - height) / 2;

    show_bmp_image(addr, fp_manual_play, offset_x, offset_y);

    return 0;
}



