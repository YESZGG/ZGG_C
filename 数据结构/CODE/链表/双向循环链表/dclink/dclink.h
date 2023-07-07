#ifndef __DCLINK_H__
#define __DCLINK_H__

#include <stdio.h>
#include <stdlib.h>

/*设计一个双向循环链表的结点模型*/
struct dclink
{
    /*数据域*/
    int num;

    /*指针域*/
    struct dclink *prev; //前驱指针
    struct dclink *next; //后驱指针
};

struct dclink *init_head();                                 // 初始化头结点
struct dclink *init_node(int data);                         // 初始化其它结点
void insert_head(struct dclink *head,struct dclink *node);  // 头插
void insert_tail(struct dclink *head,struct dclink *node);  // 尾插
void insert_head_data(struct dclink *head,int data);        // 头插+新建结点
void insert_tail_data(struct dclink *head,int data);        // 尾插+新建结点
void insert_node(struct dclink *prev_node,struct dclink *node,struct dclink *next_node); // 任意插
void delete_head(struct dclink *head);                      // 头删
void delete_tail(struct dclink *head);                      // 尾删
void delete_node(struct dclink *head,int data);             // 任意删
void display_next(struct dclink *head);                     // 遍历从头结点开始
void display_prev(struct dclink *head);                     // 遍历从尾结点开始
void release(struct dclink *head);                          // 释放链表
void find_node(struct dclink *head,int data);               // 查找结点
void change_node(struct dclink *head,int data,int new_data);// 修改结点


#if 0
typedef struct dclink
{
    /*数据域*/
    int num;

    /*指针域*/
    struct dclink *prev; //前驱指针
    struct dclink *next; //后驱指针
}dclink_t,*dclink_p;
#endif

#endif