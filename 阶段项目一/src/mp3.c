#include "mp3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int current_song = 1;
int mp3_playing = 0; // Indicator for MP3 player state, 0: stopped, 1: playing
int mp3_continue = 0;

// 播放MP3文件
void play_mp3(const char *mp3_file_path)
{
    char command[100];
    sprintf(command, "madplay %s &", mp3_file_path);
    system(command);
    mp3_playing = 1; // Set MP3 player state to playing
}

// 暂停MP3播放
void pause_mp3()
{
    system("killall -SIGSTOP madplay");
    mp3_playing = 1; // Set MP3 player state to stopped
    mp3_continue = 1;
}

// 继续播放MP3
void continue_mp3()
{
    system("killall -SIGCONT madplay");
    mp3_continue = 0;
}

// 结束MP3播放
void quit_mp3()
{
    system("killall -SIGKILL madplay");
    mp3_playing = 0;
}

// 获取.mp3格式的数量
int get_num_mp3_files()
{
    int count = 0;
    struct dirent *entry;
    DIR *dir = opendir(".");

    if (dir == NULL)
    {
        perror("opendir failed.");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strstr(entry->d_name, ".mp3") != NULL)
            count++;
    }

    closedir(dir);
    return count;
}

// 播放下一首歌
void play_next_mp3()
{
    quit_mp3();
    mp3_playing = 0;
    current_song++;

    int num_mp3_files = get_num_mp3_files();
    if (num_mp3_files == -1)
        return;

    if (current_song > num_mp3_files)
        current_song = 1;

    char song_path[30];
    snprintf(song_path, sizeof(song_path), "%d.mp3", current_song);
    play_mp3(song_path);
}

// 播放上一首歌
void play_previous_mp3()
{
    quit_mp3();
    mp3_playing = 0;
    current_song--;

    int num_mp3_files = get_num_mp3_files();
    if (num_mp3_files == -1)
        return;

    if (current_song < 1)
        current_song = num_mp3_files;

    char song_path[30];
    snprintf(song_path, sizeof(song_path), "%d.mp3", current_song);
    play_mp3(song_path);
}

// 处理界面bmp图片
void show_bmp_image(int *addr, FILE *fp, int offset_x, int offset_y)
{
    fseek(fp, 18, SEEK_SET);
    int width, height;
    if (fread(&width, sizeof(width), 1, fp) != 1 ||
        fread(&height, sizeof(height), 1, fp) != 1)
    {
        fprintf(stderr, "Failed to read image width and height.\n");
        return;
    }

    fseek(fp, 54, SEEK_SET);

    unsigned char buf[BUFFER_SIZE * 3];
    memset(buf, 0, sizeof(buf));
    if (fread(buf, 1, sizeof(buf), fp) != sizeof(buf))
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
}

// 显示MP3_start.bmp界面
int show_MP3_start(int *addr, FILE *fp_mp3_start)
{
    if (fp_mp3_start == NULL)
    {
        fprintf(stderr, "File pointer is null.\n");
        return -1;
    }

    // 清空LCD显示
    memset(addr, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);

    fseek(fp_mp3_start, 18, SEEK_SET);
    int width, height;
    if (fread(&width, sizeof(width), 1, fp_mp3_start) != 1 ||
        fread(&height, sizeof(height), 1, fp_mp3_start) != 1)
    {
        fprintf(stderr, "Failed to read image width and height.\n");
        return -1;
    }

    int offset_x = (SCREEN_WIDTH - width) / 2;
    int offset_y = (SCREEN_HEIGHT - height) / 2;

    show_bmp_image(addr, fp_mp3_start, offset_x, offset_y);

    return 0;
}

// 显示MP3_stop.bmp界面
int show_MP3_stop(int *addr, FILE *fp_mp3_stop)
{
    if (fp_mp3_stop == NULL)
    {
        fprintf(stderr, "File pointer is null.\n");
        return -1;
    }

    // 清空LCD显示
    memset(addr, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);

    fseek(fp_mp3_stop, 18, SEEK_SET);
    int width, height;
    if (fread(&width, sizeof(width), 1, fp_mp3_stop) != 1 ||
        fread(&height, sizeof(height), 1, fp_mp3_stop) != 1)
    {
        fprintf(stderr, "Failed to read image width and height.\n");
        return -1;
    }

    int offset_x = (SCREEN_WIDTH - width) / 2;
    int offset_y = (SCREEN_HEIGHT - height) / 2;

    show_bmp_image(addr, fp_mp3_stop, offset_x, offset_y);

    return 0;
}

// 显示MP3_continue.bmp界面
int show_MP3_continue(int *addr, FILE *fp_mp3_continue)
{
    if (fp_mp3_continue == NULL)
    {
        fprintf(stderr, "File pointer is null.\n");
        return -1;
    }

    // 清空LCD显示
    memset(addr, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);

    fseek(fp_mp3_continue, 18, SEEK_SET);
    int width, height;
    if (fread(&width, sizeof(width), 1, fp_mp3_continue) != 1 ||
        fread(&height, sizeof(height), 1, fp_mp3_continue) != 1)
    {
        fprintf(stderr, "Failed to read image width and height.\n");
        return -1;
    }

    int offset_x = (SCREEN_WIDTH - width) / 2;
    int offset_y = (SCREEN_HEIGHT - height) / 2;

    show_bmp_image(addr, fp_mp3_continue, offset_x, offset_y);

    return 0;
}

// 处理MP3界面下的触摸事件
void handleMP3ScreenTouch(int *addr, int startX, int startY, int endX, int endY)
{
    // 返回主菜单界面
    if ((startX > 600 && endX < 800) && (startY > 420 && endY < 480))
    {
        // 切换屏幕状态到MainMenu
        currentScreen = MainMenu;

        quit_mp3();
        FILE *fp_menu = fopen("desktop.bmp", "r+");
        if (fp_menu == NULL)
        {
            perror("fopen bmp fail.");
            return;
        }

        if (show_return_menu(addr, fp_menu) != 0)
        {
            fclose(fp_menu);
            return;
        }
        fclose(fp_menu);
    }
    else if ((startX > 200 && endX < 400) && (startY > 420 && endY < 480))
    {
        // 播放/暂停 MP3
        if (mp3_playing == 0 && mp3_continue == 0)
        {
            int num_mp3_files = get_num_mp3_files();
            if (num_mp3_files == -1)
                return;

            if (num_mp3_files == 0)
            {
                printf("No mp3 files found.\n");
                return;
            }

            char song_path[30];
            snprintf(song_path, sizeof(song_path), "%d.mp3", current_song);

            play_mp3(song_path);

            FILE *fp_mp3_stop = fopen("MP3_stop.bmp", "r");
            if (fp_mp3_stop == NULL)
            {
                perror("fopen bmp fail.");
                return;
            }

            if (show_MP3_stop(addr, fp_mp3_stop) != 0)
            {
                fclose(fp_mp3_stop);
                return;
            }
            fclose(fp_mp3_stop);
        }
        else if (mp3_playing == 1)
        {
            if (mp3_continue == 0)
            {
                pause_mp3();
                FILE *fp_mp3_continue = fopen("MP3_continue.bmp", "r");
                if (fp_mp3_continue == NULL)
                {
                    perror("fopen bmp fail.");
                    return;
                }

                if (show_MP3_continue(addr, fp_mp3_continue) != 0)
                {
                    fclose(fp_mp3_continue);
                    return;
                }
                fclose(fp_mp3_continue);
            }
            else
            {
                continue_mp3();
                FILE *fp_mp3_stop = fopen("MP3_stop.bmp", "r");
                if (fp_mp3_stop == NULL)
                {
                    perror("fopen bmp fail.");
                    return;
                }

                if (show_MP3_stop(addr, fp_mp3_stop) != 0)
                {
                    fclose(fp_mp3_stop);
                    return;
                }
                fclose(fp_mp3_stop);
            }
        }
    }
    else if ((startX > 0 && endX < 200) && (startY > 420 && endY < 480))
    {
        // 上一首歌
        if (currentScreen == MP3Screen)
        {
            play_previous_mp3();
            FILE *fp_mp3_stop = fopen("MP3_stop.bmp", "r");
            if (fp_mp3_stop == NULL)
            {
                perror("fopen bmp fail.");
                return;
            }

            if (show_MP3_stop(addr, fp_mp3_stop) != 0)
            {
                fclose(fp_mp3_stop);
                return;
            }
            fclose(fp_mp3_stop);
        }
    }
    else if ((startX > 400 && endX < 600) && (startY > 420 && endY < 480))
    {
        // 下一首歌
        if (currentScreen == MP3Screen)
        {
            play_next_mp3();
            FILE *fp_mp3_stop = fopen("MP3_stop.bmp", "r");
            if (fp_mp3_stop == NULL)
            {
                perror("fopen bmp fail.");
                return;
            }

            if (show_MP3_stop(addr, fp_mp3_stop) != 0)
            {
                fclose(fp_mp3_stop);
                return;
            }
            fclose(fp_mp3_stop);
        }
    }
}