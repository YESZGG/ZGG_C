// child.c

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/wait.h> 

int main(int argc, char **argv)
{
    // 倒数 n 秒
    for(int i=atoi(argv[1]); i>0; i--)
    {
        fprintf(stderr, " ======= %d =======%c", i, i==0?'\n':'\r');
        sleep(1);
    }

    // 程序退出，返回 n
    exit(atoi(argv[1]));
}
