#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    char *source_file = "jige1.jpeg";
    char *target_file = "jige2.jpeg";

    // 打开源文件和目标文件
    int sourceFd = open(source_file, O_RDONLY);
    if (sourceFd == -1)
    {
        perror("无法打开源文件");
        return -1;
    }

    int targetFd = open(target_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (targetFd == -1)
    {
        perror("无法创建目标文件");
        return -1;
    }

    // 获取源文件的大小
    int fileSize = lseek(sourceFd, 0, SEEK_END);
    if (fileSize == -1)
    {
        perror("获取源文件大小失败");
        return -1;
    }

    // 将文件指针调回文件开头
    if (lseek(sourceFd, 0, SEEK_SET) == -1)
    {
        perror("无法调回文件开头");
        return -1;
    }

    // 创建缓冲区
    char buf[BUFFER_SIZE];

    unsigned int readbytes, writebytes; // 读取数据 和 写入数据
    while ((readbytes = read(sourceFd, buf, sizeof(buf))) > 0)
    {
        writebytes = write(targetFd, buf, readbytes);
        if (readbytes != writebytes)
        {
            perror("拷贝失败");
            return -1;
        }
    }
    if (readbytes == -1)
    {
        perror("读取源文件失败");
        return -1;
    }

    printf("成功将 %s 拷贝到 %s\n", source_file, target_file);

    // 关闭文件
    if (close(sourceFd) == -1)
    {
        perror("关闭源文件失败");
        return -1;
    }

    if (close(targetFd) == -1)
    {
        perror("关闭目标文件失败");
        return -1;
    }
}