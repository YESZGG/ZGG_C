#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* 文件描述符
最大的文件描述符是1023(3 ~ 1023)
文件描述符的一共有1024个，包括了标准输入、标准输出、标准出错(0、1、2)
*/
int main(int argc, char *argv[])
{
    while (1)
    {
        int fd = open("a.txt", O_WRONLY);
        if (fd < 0)
        {
            perror("open file fail.");
            return -1;
        }
        printf("open success!.\n");

        printf("fd=%d\n", fd);
        write()
    }

    return 0;
}


