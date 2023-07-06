#ifndef __DLINK_H__
#define __DLINK_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

struct bookLink
{
    /*数据域*/
    int bookno;           // 书籍号
    char color[10];       // 书籍封面颜色
    char authorSName[20]; // 作者名字
    int page;             // 图书页数
    char title[20];       // 图书名

    /*指针域*/
    struct bookLink *prev; // 前驱指针
    struct bookLink *next; // 后驱指针
};
extern struct bookLink *init_head();               // 初始化头结点
extern struct bookLink *init_node();               // 初始化其他节点
extern void insertHead(struct bookLink *head);     // 插入
extern bool isStringArray(char arr[], int size);    // 判断数组存储的是不是字符串
extern void findBook(struct bookLink *head);       // 查找
extern void deleteBook(struct bookLink *head);     // 删除
extern void modifyBook(struct bookLink *head);     // 修改
extern void printLink(struct bookLink *head);      // 遍历
extern void release(struct bookLink *head);        // 释放链表
extern int Function_Select(struct bookLink *head); // 功能界面
#endif
