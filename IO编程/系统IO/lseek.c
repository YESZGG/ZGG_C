#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int ret = 0;
    // O_RDONLY,只读o_WRONLY,只写O_RDWR.可读可写
    int fd = open("1.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("open file fail.");
        return -1;
    }
    // printf("open success!.\n");
    // printf("fd:%d\n", fd);
    
    // 从头文件开始 偏移 n 
    ret = lseek(fd,20,SEEK_SET);
    printf("lseek ret:%d\n", ret);
    // 从当前的位置开始 偏移 n
    ret = lseek(fd,20,SEEK_CUR);
    printf("lseek ret:%d\n", ret);
    
    //设置为0，即偏移量为0，文件头到文件尾 可求文件的大小
    // ret = lseek(fd, 0, SEEK_END);
    // printf("lseek ret:%d\n", ret);

    char buf[1024];
    memset(buf, 0, sizeof(buf));

    // 读的时候用sizeof
    ret = read(fd, buf, sizeof(buf));
    printf("read buf:\n%s\nret:%d\n", buf, ret);

    // 关闭
    close(fd);

    return 0;
}
