#ifndef AUTOPLAY_H
#define AUTOPLAY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "menu.h"
#include "slideshow.h"
#include "mp3.h"


extern enum ScreenState currentScreen;

extern int show_Auto_play(int *addr, FILE *fp_auto_play);
extern int playAutoshow(Node *head, Node **current, int *addr, int startX, int startY, int endX, int endY);
extern void displayBMPImageBlinds(const char* filename, int* addr);
extern void displayBMPImageExpandingInward(const char *filename, int *addr);
extern void displayBMPImageExpandingOutward(const char *filename, int *addr);
extern void displayBMPImage_openScreen1(const char *filename, int *addr);
extern void displayBMPImage_openScreen2(const char *filename, int *addr);
#endif