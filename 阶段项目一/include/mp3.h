#ifndef MP3_H
#define MP3_H

#include <stdio.h>
#include "menu.h"

#define MP3_START_PATH "MP3_start.bmp"
#define MP3_STOP_PATH "MP3_stop.bmp"
#define MP3_CONTINUE_PATH "MP3_continue.bmp"

extern enum ScreenState currentScreen;

void play_mp3(const char *mp3_file_path);
void pause_mp3();
void continue_mp3();
void quit_mp3();
int get_num_mp3_files();
void play_next_mp3();
void play_previous_mp3();
void show_bmp_image(int *addr, FILE *fp, int offset_x, int offset_y);
int show_MP3_start(int *addr, FILE *fp_mp3_start);
int show_MP3_stop(int *addr, FILE *fp_mp3_stop);
int show_MP3_continue(int *addr, FILE *fp_mp3_continue);
void handleMP3ScreenTouch(int *addr, int startX, int startY, int endX, int endY);

#endif
