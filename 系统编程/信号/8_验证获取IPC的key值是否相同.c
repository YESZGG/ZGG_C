#include<stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main()
{
    key_t key;

    //获取key值
    key = ftok(".", 10);
    printf("key1:%x\n",key);

    //获取key值
    key = ftok("..", 10);
    printf("key2:%x\n",key);

    //获取key值
    key = ftok(".", 20);
    printf("key3:%x\n",key);

    //获取key值
    key = ftok(".", 10);
    printf("key4:%x\n",key);

    return 0;
}