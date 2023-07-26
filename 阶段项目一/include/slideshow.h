#ifndef SLIDESHOW_H
#define SLIDESHOW_H

#include <stdio.h>
#include "linkedlist.h"
#include "menu.h"


enum SLIDE_STATUS // 滑动状态
{
    LEFT,
    RIGHT
};
#define THRESHOLD 100                  // 滑动阀值

extern enum ScreenState currentScreen;

extern void displayJPEGImage(const char *filename);
extern void displayBMPImage(const char *filename, int *addr);
extern int SlideDirection(int startX, int startY, int endX, int endY);
extern int playSlideshow(Node *head, Node **current, int *addr, int startX, int startY, int endX, int endY);
extern int show_Manual_play(int *addr, FILE *fp_manual_play);

#endif
