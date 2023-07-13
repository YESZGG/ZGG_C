#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    /*
    O_RDONLY,只读
    O_WRONLY,只写
    O_RDWR.可读可写
    O_APPEND    文件以追加模式打开
    O_TRUNC     清零
    */
    int fd = open("1.txt", O_APPEND | O_RDWR);
    if (fd < 0)
    {
        perror("open file fail.");
        return -1;
    }
    // printf("open success!.\n");
    // printf("fd:%d\n", fd);

    // 写文件
    char buf[] = "\n写的时候用strlen write(fd,buf,strlen(buf))\n读的时候用sizeof  read(fd,buf,sizeof(buf))";
    // char *buf1 = "123456789";
    /*
    strlen(buf) = 9     // 求字符串的有效字节长度
    sizeof(buf) = 10    // 求字符串的内存大小
    strlen(buf1) = 9     
    sizeof(buf1) = 8     // 指针的大小 64位8 32位4
    */
    int ret = 0;
    // 想写多少就写多少  如果write(fd, buf, 15); ret = 15
    ret = write(fd, buf, strlen(buf));    // 写的时候用strlen
    printf("write ret:%d\n", ret);

    // 关闭
    close(fd);

    return 0;
}
