#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main() {
    pid_t child_pid;
    sigset_t set;

    // 阻塞的信号
    int blocked_signal = SIGUSR1;

    // 初始化信号集
    sigemptyset(&set);

    // 将信号加入到信号集
    sigaddset(&set, blocked_signal);

    // 设置信号集为阻塞状态
    sigprocmask(SIG_BLOCK, &set, NULL);

    // 创建子进程
    child_pid = fork();
    if (child_pid == 0) {
        // 子进程
        printf("子进程发送信号给父进程\n");
        sleep(1); // 等待1秒，确保父进程已经阻塞信号

        // 尝试发送信号给父进程
        if (kill(getppid(), blocked_signal) == -1) {
            perror("无法发送信号给父进程");
            exit(1);
        }

        printf("子进程发送信号成功\n");
        exit(0);
    } else if (child_pid > 0) {
        // 父进程
        printf("父进程阻塞信号\n");
        sleep(5); // 阻塞5秒，等待子进程发送信号

        // 检查是否收到信号
        sigpending(&set);
        if (sigismember(&set, blocked_signal)) {
            printf("父进程依然阻塞信号\n");
        } else {
            printf("父进程解除阻塞信号\n");
        }
    } else {
        perror("fork失败");
        return 1;
    }

    return 0;
}


   