#include "bookmanagement.h"

int main()
{
    struct bookList *head = init_head();
    if(head == (struct bookList *)-1)
    {
        perror("head init failed.");
        return -1;
    }

    // 功能界面函数
    Function_Select(head);
    // 释放链表
    release(head);
    return 0;
}