#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/*
argc:argument count 参数个数
argv:argument value 参数的值
char argv[]，是个字符串的数组，每个元素都是一个字符指针，指向一个字符串，即命令行中的每一个参数。
char envp[]，也是一个字符串的数组，这个数组的每一个元素是指向一个环境变量的字符指针。
*/
int main(int argc, char *argv[])
{
    /*
     *O_RDONLY,只读
     *O_WRONLY,只写
     *O_RDWR.可读可写
     *O_APPEND    文件以追加模式打开
     *O_TRUNC     清零
     */
    int fd = open("a.txt", O_CREAT | O_TRUNC | O_WRONLY, 0664);
    if (fd < 0)
    {
        perror("open file fail.");
        return -1;
    }
    printf("open success!.\n");
    /*  fd:3
    因为0、1、2三个描述符在程序一开始运行就已经被默认打开了分别代表了标准输入、标准输出、标准出错。
    经常使用STDIN_FILENO、STDOUT_FILENO、STDERR_FILENO来替代0、1、2.
    */
    printf("fd:%d\n", fd);

    close(fd);

    return 0;
}
