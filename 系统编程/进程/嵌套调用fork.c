#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#if 0
void create_process(int level) {
    pid_t pid = fork();

    if (pid == 0) {
        // 子进程
        printf("子进程ID：%d，父进程ID：%d，层级：%d\n", getpid(), getppid(), level);
        if (level > 0) {
            create_process(level - 1);  // 递归调用创建更多子进程
        }
        sleep(2);
        printf("子进程完成，ID：%d\n", getpid());
        exit(0);
    } else if (pid > 0) {
        // 父进程
        wait(NULL);  // 父进程等待子进程结束
    } else {
        // fork() 失败
        fprintf(stderr, "无法创建子进程\n");
        exit(1);
    }
}

int main() {
    int level = 3;  // 进程嵌套的层级数
    create_process(level);

    return 0;
}
#endif

