#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int ret = 0;
    // O_RDONLY,只读o_WRONLY,只写O_RDWR.可读可写
    int fd1 = open("1.txt", O_RDWR);
    if (fd1 < 0)
    {
        perror("open file fail.");
        return -1;
    }
    int fd2 = open("2.txt", O_CREAT | O_TRUNC | O_RDWR,0666 );
    if (fd2 < 0)
    {
        perror("open file fail.");
        return -1;
    }
    char read_buf[100];
    memset(read_buf, 0, sizeof(read_buf));
    // 偏移3个字节到456789
    ret = lseek(fd1, 3, SEEK_SET);
    // 读取456789
    read(fd1, read_buf, sizeof(read_buf));

    // 写入2.txt文件中
    write(fd2, read_buf, strlen(read_buf));

    return 0;
}
