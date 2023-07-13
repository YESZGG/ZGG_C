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
    int fd = open("1.txt", O_RDWR);
    if (fd < 0)
    {
        perror("open file fail.");
        return -1;
    }
    // printf("open success!.\n");
    // printf("fd:%d\n", fd);

    char read_buf[1024];
    memset(read_buf, 0, sizeof(read_buf));

    char write_buf[] = "1111";
    // 1.先读 再读    结果为 先读完之后，lseek从当前文件指针位置，再读就从当前位置开始读
    // printf("--1.先读   再读--\n");
    // // 读的时候用sizeof
    // ret = read(fd, read_buf, sizeof(read_buf)); // 先读
    // printf("read ret:%d\n", ret);
    // ret = lseek(fd, 0, SEEK_CUR); // 从当前文件的位置
    // printf("lseek ret:%d\n", ret);
    // ret = read(fd, read_buf, sizeof(read_buf)); // 再读
    // printf("read ret:%d\n", ret);

    // printf("--2.先读   再写--\n");
    // ret = read(fd, read_buf, sizeof(read_buf)); // 先读
    // printf("read ret:%d\n", ret);
    // ret = lseek(fd, 0, SEEK_CUR); // 记录当前读完文件的位置
    // printf("lseek ret:%d\n", ret);
    // ret = write(fd, write_buf, strlen(write_buf)); // 再写
    // printf("write ret:%d\n", ret);

    printf("--3.先写   再写--\n");
    ret = write(fd, write_buf, strlen(write_buf)); // 先写
    printf("write ret:%d\n", ret);
    ret = lseek(fd, 0, SEEK_CUR); // 记录当前写完的光标位置
    printf("lseek ret:%d\n", ret);
    ret = write(fd, write_buf, strlen(write_buf)); // 先写
    printf("write ret:%d\n", ret);
    ret = lseek(fd, 0, SEEK_CUR); // 记录当前写完的光标位置
    printf("lseek ret:%d\n", ret);


    // printf("--4.先写   再读--\n");
    // ret = write(fd, write_buf, strlen(write_buf)); // 先写
    // printf("write ret:%d\n", ret);
    // ret = lseek(fd, 0, SEEK_CUR); // 记录当前写完的光标位置
    // printf("lseek ret:%d\n", ret);
    // ret = read(fd, read_buf, sizeof(read_buf)); // 再读
    // printf("read ret:%d\n", ret);
    // ret = lseek(fd, 0, SEEK_CUR); // 记录当前写完的光标位置
    // printf("lseek ret:%d\n", ret);
    // 关闭
    close(fd);

    return 0;
}