#include <stdio.h>


int main(int argc,char *argv[])
{
    // 创建文件指针
    /* 
        r 只读方式打开已存在的文件。
        r+ 以可读可写方式打开已经存在的文件。
        w   将文件清零或以只写方式创建文件。
        w+  以可读可写打开文件，如果文件不存在就创建,存在就会截断（就是清零）。
        a   在文件末尾追加写入，如果文件不存在就创建，文件流在文件末尾。
        a+  以可读和追加方式打开文件，如果文件不存在就创建，读取从文件开始，但是输出总是在文件末尾。
     */
    FILE *fp = fopen("1.txt","w+");
    if (fp == NULL)
    {
        perror("fopen fail.");
        return -1;
    }
    printf("fopen success.\n");

    return 0;
}