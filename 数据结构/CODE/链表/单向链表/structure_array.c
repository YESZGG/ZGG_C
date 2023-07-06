#include <stdio.h>
#include <stdlib.h>

struct st
{
    char a;
    int b;
};

int main()
{
    struct st* s = (struct st*)malloc(3 * sizeof(struct st));// 在堆空间中分配大小为3的结构体数组
    if(s == NULL)
    {
        printf("malloc failed.\n");
        return -1;
    }
    // 对结构体数组进行赋值操作
    // 结构体指针用->访问成员
    // 结构体变量用.访问成员
    s[0].a = 'A';
    s[0].b = 10;

    s[1].a = 'B';
    s[1].b = 20;

    s[2].a = 'C';
    s[2].b = 30;
    
    struct st* p = s;
    for(int i = 0;i < 3; i++,p++)
    {
            printf("s[%d] = %p  s[%d].a = %c  s[%d] = %d \n",i, p, i, s[i].a, i, s[i].b);
    }
    // 释放结构体数组占用的堆空间
    free(s);
    return 0;
}
