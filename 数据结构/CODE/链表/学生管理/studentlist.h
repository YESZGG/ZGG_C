#ifndef __LIST_H__
#define __LIST_H__

// 头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif  

// 结点模型
struct list
{
    // 数据域
    int stuno;     // 学号
    char name[20]; // 姓名
    char sex;      // 性别
    int height;    // 身高
    int score;     // 成绩
    // 指针域
    struct list *next;
};

extern struct list *init_head();
extern struct list *init_node();
extern void insertHeadNode(struct list *head);     // 头插法
extern void insertTailNode(struct list *head);     // 尾插法
extern void printList(struct list *head);          // 打印数据
extern void traverseLinkedList(struct list *head); // 查找
extern void deleteNode(struct list *head);         // 删除
extern void modifyNodes(struct list *head);        // 修改
extern void moveNodes(struct list *head);          // 移动
extern void freeList(struct list *head);           // 释放
extern int Function_Select(struct list *head);     // 功能界面
#endif