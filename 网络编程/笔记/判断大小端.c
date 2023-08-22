/*
 * @Description: 验证系统是大端还是小端 (1.直接访问地址  2.使用共用体union特性查看)
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-08-10 14:28:14
 * @LastEditors: ZGG
 * @LastEditTime: 2023-08-10 19:33:39
 */
#if 0
#include <stdio.h>

int isLittleEndian()
{
    unsigned int i = 1;
    char *c = (char *)&i;  

    // 如果低地址处保存的是最低有效字节，那么则为小端
    if (*c)
    {
        return 1;
    }

    return 0;
}

int main()
{
    if (isLittleEndian())
    {
        printf("系统是小端（Little Endian）\n");
    }
    else
    {
        printf("系统是大端（Big Endian）\n");
    }

    return 0;
}
#endif

#if 0
#include <stdio.h>

typedef union {
    unsigned int i;
    unsigned char c[4];
} endian_test;

int isLittleEndian() {
    endian_test test;
    test.i = 1;

    // 如果低地址处保存的是最低有效字节，那么则为小端
    if (test.c[0] == 1) {
        return 1;
    }

    return 0;
}

int main() {
    if (isLittleEndian()) {
        printf("系统是小端（Little Endian）\n");
    } else {
        printf("系统是大端（Big Endian）\n");
    }

    return 0;
}
#endif

#if 0
#include <stdio.h>
//联合体
union num
{
    int a;
    char b;
};

int main(int argc,char **argv)
{
    //方法一：联合体
#if 0 
    union num n;
    n.a = 0x12345678;
    if(n.b == 0x78)
    {
        printf("little end\n");
    }
    if(n.b == 0x12)
    {
        printf("big end\n");
    }
#endif

    //方法二：指针
    int a = 0x12345678;
    char b = *((char *)&a);
    // &a ---> int *
    // (char *)&a ---> char *
    if(b == 0x78)
    {
        printf("little end\n");
    }
    if(b == 0x12)
    {
        printf("big end\n");
    }


    return 0;
}
#endif

