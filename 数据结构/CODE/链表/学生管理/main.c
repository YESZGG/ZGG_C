#include "studentlist.h"

int main()
{
    struct list *head = init_head(); // 头节点初始化
    if (head == NULL)
    {
        printf("init head fail\n"); // 头节点初始化失败
        return -1;
    }
    Function_Select(head); // 功能界面

    // 释放链表内存
    freeList(head);
    return 0;
}