#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node
{
    char filename[30];// 图片的路径
    int num;   // 图片的序号
    char type; // 图片的类型
    struct Node *previous;
    struct Node *next;
} Node;

extern struct Node *init_head();
extern struct Node *init_node();
extern void printLink(struct Node *head);
extern void freeLinkedList(Node *head);
extern int read_path_list(Node* head);

#endif
