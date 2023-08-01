#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_FILE "/home/gec/fifo1"

int main()
{
    // 先判断文件是否存在，如果存在则不用创建了
    if (access(FIFO_FILE, F_OK) == -1) // access 判断文件是否存在，如果不存在则返回 -1
    {
        // 所以是不存在的时候才进来创建
        if (mkfifo(FIFO_FILE, 0777) == -1) // 创建一个有名管道文件
        {
            perror("mkfifo error");
            return -1;
        }
    }

    // 打开管道
    int fd = open(FIFO_FILE, O_RDWR);
    if (fd < 0)
    {
        printf("open %s fail\n", FIFO_FILE);
        return -1;
    }

    // 写管道----write
    int ret = 0;
    while (1)
    {
        char buf[1024];
        memset(buf, 0, sizeof(buf));
        printf("Enter a message to send to FIFO (or enter 'exit' to quit):\n ");
        scanf("%s", buf);
        ret = write(fd, buf, strlen(buf));
        printf("write %s ret:%d\n", buf, ret);
        if (strcmp(buf, "exit") == 0)
        {
            break;
        }
    }

    // 关闭管道
    close(fd);

    return 0;
}

