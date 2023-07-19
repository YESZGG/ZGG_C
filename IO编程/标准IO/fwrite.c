/*
 * @Description:
 * @version:
 * @Author: ZGG
 * @Date: 2023-07-18 10:42:40
 * @LastEditors: ZGG
 * @LastEditTime: 2023-07-18 10:53:30
 */
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp = fopen("1.txt", "w+");
    if (fp == NULL)
    {
        perror("fopen file fail.");
        return -1;
    }

    char buf[] = "helloworldhelloworldhelloworld";

    int ret = fwrite(buf, 1, 30, fp);
    printf("ret:%d strlen:%ld\n", ret, strlen(buf));
    // 当size=5 nmemb=6 ret = 6
    // 当size=1 nmemb=30 ret = 30
    // 当size=7 nmemb=5 ret = 5
    // 当size=7 nmemb=3 ret = 3
    fclose(fp);

    return 0;
}