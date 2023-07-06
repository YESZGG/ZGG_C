#ifndef __BOOK_H__
#define __BOOK_H__

// 头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif  

// 结构体
struct bookList
{
    // 数据域
    int bookno;           // 书籍号
    char color[10];       // 书籍封面颜色
    char authorSName[20]; // 作者名字
    int page;             // 图书页数
    char title[20];       // 图书名

    // 指针域
    struct bookList *next;
};

extern struct bookList *init_head();
extern struct bookList *init_node();
extern void insertHead(struct bookList *head);
extern void findBook(struct bookList *head);
extern void printList(struct bookList *head);
extern int Function_Select(struct bookList *head); // 功能界面
#endif