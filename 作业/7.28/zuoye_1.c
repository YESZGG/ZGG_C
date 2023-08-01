#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char argv[])
{
    char arr1[10][100];
    char *arr2[10];
    memset(arr1, 0, sizeof(arr1));
    memset(arr2, 0, sizeof(arr2));
    int num_strings = (int)(sizeof(arr2) / sizeof(arr2[0]));
    printf("请输入要输入的字符串数量（最多%d个）：", num_strings);
    scanf("%d", &num_strings);
    getchar(); // 读取换行符

    printf("请输入%d个字符串：\n", num_strings);
    for (int i = 0; i < num_strings; ++i)
    {
        fgets(arr1[i], 100, stdin);
        arr1[i][strcspn(arr1[i], "\n")] = '\0'; // 去掉换行符
        arr2[i] = arr1[i];                     // 将字符串指针存入指针数组
    }

    printf("\n你输入的%d个字符串为：\n", num_strings);
    for (int i = 0; i < num_strings; ++i) {
        printf("字符串 %d: %s\n", i+1, arr1[i]);
    }

    printf("\n通过指针数组访问这些字符串：\n");
    for (int i = 0; i < num_strings; ++i) {
        printf("字符串 %d: %s\n", i+1, arr2[i]);
    }


    return 0;
}
