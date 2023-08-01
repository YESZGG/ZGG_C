#include <stdio.h>
#include <stdlib.h>
extern char **environ;
int main(int argc, char *argv[])
{
    int i;
    /* 打印进程的环境变量 */
    for (i = 0; NULL != environ[i]; i++)
        puts(environ[i]);
    exit(0);
}