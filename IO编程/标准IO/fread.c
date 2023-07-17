#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
/*
argc:argument count 参数个数
argv:argument value 参数的值
char argv[]，是个字符串的数组，每个元素都是一个字符指针，指向一个字符串，即命令行中的每一个参数。
char envp[]，也是一个字符串的数组，这个数组的每一个元素是指向一个环境变量的字符指针。
*/
int main(int argc, char *argv[])
{
    FILE *fp = fopen("1.txt", "r+");
    if (fp == NULL)
    {
        perror("fopen file fail.");
        return -1;
    }
    // printf("fopen success! fp:%p\n", fp); // 使用%p格式说明符打印指针的值

    // int fd = open("1.txt", O_CREAT | O_TRUNC | O_WRONLY, 0664);
    // if (fd < 0)
    // {
    //     perror("open file fail.");
    //     return -1;
    // }
    // printf("open success! fd:%d\n", fd); // 使用%d格式说明符打印整数值
    int ret;
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    int size, nmemb;

    size = 5, nmemb = 6;
    ret = fread(buf, size, nmemb, fp);
    printf("buf:%s  ret:%d  long:%d\n", buf, ret,(int)strlen(buf));
    // 当size=5 nmemb=6  ret = 6        strlen(buf)=30
    // 当size=1 nmemb=30 ret = 30       strlen(buf)=30
    // 当size=7 nmemb=5  ret = 4        strlen(buf)=30
    // 当size=7 nmemb=3  ret = 3        strlen(buf)=21

    fclose(fp);

    return 0;
}
