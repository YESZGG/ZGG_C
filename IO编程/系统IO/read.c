#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // O_RDONLY,只读o_WRONLY,只写O_RDWR.可读可写
    int fd = open("1.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("open file fail.");
        return -1;
    }
    printf("open success!.\n");

    printf("fd:%d\n", fd);


    char buf[1024];
    memset(buf,0,sizeof(buf));

    int ret = 0;
    // 读的时候用sizeof
    ret = read(fd,buf,sizeof(buf));
    printf("read buf:\n%s\nret:%d\n",buf,ret);

    // 关闭
    close(fd);

    return 0;
}
