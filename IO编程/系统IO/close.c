#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd = open("a.txt", O_CREAT | O_TRUNC | O_WRONLY, 0664);
    if (fd < 0)
    {
        perror("open file fail.");
        return -1;
    }
    printf("open success!.\n");

    printf("fd:%d\n", fd);

    int ret = close(fd);
    if (ret == 0)
    {
        printf("close success.\n");
    }
    else
    {
        perror("close failed");
    }

    return 0;
}
