#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main() {
    key_t key = ftok(".", 10);
    printf("进程2的键值为：%d\n", key);
    return 0;
}
