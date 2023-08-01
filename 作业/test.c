#if 0
/* 求字符串的数目以及真子串的数目 */
#include <stdio.h>
#include <string.h>

int countSubstrings(char *string)
{
    int n = strlen(string);
    int count = 0;

    // 外层循环遍历子串的起始位置
    for (int i = 0; i < n; i++)
    {
        // 内层循环遍历子串的结束位置
        for (int j = i + 1; j <= n; j++)
        {
            // 截取子串并计数
            for (int k = i; k < j; k++)
            {
                printf("%c", string[k]); // 输出所有子串（可选）
            }
            count++;
            printf("\n"); // 输出所有子串的换行符（可选）
        }
    }

    return count;
}

int main()
{
    char string[] = "software";
    int result = countSubstrings(string);
    printf("真子串的数目：%d\n", result);
    printf("子串的数目：%d\n", result + 1);
    printf("非空真子串的数目(除了空串，还有本身)：%d\n", result - 1);

    return 0;
}
#endif

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    const char *src = "hello,world";
    char *dest = NULL;
    int len = strlen(src);
    dest = (char *)malloc(len + 1); // 分配内存时增加一个字节
    char *d = dest;
    const char *s = &src[len - 1]; // 获取字符串最后一个字符的地址
    while (len-- != 0)
        *d++ = *s--;
    *d = '\0';            // 添加字符串结尾的空字符
    printf("%s\n", dest); // 输出字符串后添加换行符
    free(dest);           // 释放动态分配的内存
    return 0;
}

#endif

#if 0
#include <stdio.h>

int main()
{
    char *s1 = "6";
    printf("%d\n",*s1);
    double t1 = 6.3;
    printf("%f\n", *s1 + t1);
}

#endif

#if 1
#include<stdio.h>
 
#include<string.h>
 
#define N 1024
 
char* encrypt(char* str) {
 
        int i, len = strlen(str);
 
        for (i = 0; i < len; i++) {
 
               str[i] = (str[i] + i) % 128;
 
        }
 
        return str;
 
}
int main() {
 
        char s[N] = "I am good";
 
        printf("%s\n", encrypt(s));
 
        return 0;
 
}
#endif