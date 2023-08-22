#include <stdio.h>

/*
5_c指针变量.c: In function ‘main’:
5_c指针变量.c:6:14: warning: initialization makes pointer from integer without a cast [-Wint-conversion]
     int *p = 0x12345678; //左边是int*类型，右边是int类型，类型不
*/
int main()
{

    int *p = 0x12345678; //左边是int*类型，右边是int类型，类型不一致会警告

    return 0;
}    