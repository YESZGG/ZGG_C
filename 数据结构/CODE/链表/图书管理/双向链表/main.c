#include "bookmanagement.h"

int main()
{
    struct bookLink *head = init_head();
    if(head == (struct bookLink *)-1)
    {
        perror("head init failed.");
        return -1;
    }

    // 调用功能界面函数
    Function_Select(head);
    // 释放内存
    release(head);

    return 0;
}