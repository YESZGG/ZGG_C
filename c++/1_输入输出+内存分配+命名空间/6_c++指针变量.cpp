#include <iostream>

/*
6_c++指针变量.cpp: In function ‘int main()’:
6_c++指针变量.cpp:11:14: error: invalid conversion from ‘int’ to ‘int*’ [-fpermissive]
     int *p = 0x12345678; //左边是int*类型，右边是int类型，类型不
*/

int main()
{

    // int *p = 0x12345678; //错误

    int *p = (int *)0x12345678; //OK

    return 0;
}    