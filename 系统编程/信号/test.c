#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <wait.h>

#if 0
/* 
alarm(5)//定时5秒自己给自己发送SIGALRM
练习告诉自己10秒之后，把手机扔掉，搞学习 
*/
int global_pid;

void alarmClock(int signum)
{
    printf("扔掉手机，学习.\n");
    // kill(global_pid, SIGINT);
}

int main(int argc, char *argv[])
{
    int pid = getpid();
    global_pid = pid; // 将 pid 保存到全局变量中
    printf("[%d]\n", getpid());
    
    signal(SIGALRM, alarmClock);

    /* 
        alarm也称为闹钟函数，它可以在进程中设置一个定时器，当定时器指定的时间到时，它向进程发送SIGALRM信号。
        可以设置忽略或者不捕获此信号，如果采用默认方式其动作是终止调用该alarm函数的进程。
    */
    alarm(5);// 5秒之后 会受到SIGALRM信号 不再挂起继续执行 同时SIGALRM是终止属性信号，进程结束

    pause(); // 充当 1.while 循环  2.for(;;)

    return 0;
}
#endif

#if 0
/* 使用raise实现如下效果：一直打印"我在打游戏"，每隔10秒闹钟一次打印，"放下游戏出来搞学习"。 */
void handle_alarm(int signum) // signum 为信号量
{
    printf("放下游戏出来搞学习\n");
    // kill(getpid(), SIGKILL);
}

int main()
{
    signal(SIGALRM, handle_alarm);

    int count = 1;
    while (1)
    {
        printf("我在打游戏\n");
        sleep(1); // 每隔1秒打印一次
        count++;
        if (count == 10)
        {
            // 用 法: int raise(int sig);
            // 功 能: 向正在执行的程序发送一个信号
            raise(SIGALRM); // 手动触发SIGALRM信号
            count = 0;
        }
    }

    return 0;
}
#endif

#if 0
/* 验证一下子进程退出的时候，是否给父进程发出了SIGCHILD信号 */
void sigchld_handler(int signum)
{
    printf("收到SIGCHLD信号\n");
}

int main()
{
    pid_t pid;
    int status;

    signal(SIGCHLD, sigchld_handler); // 注册SIGCHLD信号处理函数

    pid = fork();
    if (pid == 0)
    {
        // 子进程
        printf("子进程运行\n");
        sleep(2); // 子进程睡眠2秒后退出
        _exit(0); // 子进程退出会给父进程发送SIGCHLD
    }
    else if (pid > 0)
    {
        // 父进程
        printf("父进程等待子进程退出\n");
        wait(&status); // 等待子进程退出
        printf("子进程退出\n");
    }
    else
    {
        // fork失败
        perror("fork失败");
        return 1;
    }

    return 0;
}
#endif

#if 0
/* 设置信号集 */
int main(int argc, char *argv[])
{
    /* sigemptyset（）、sigfillset（）、sigaddset（）和sigdelset（）在成功时返回0，在错误时返回-1。 */
    // 1.先定义一个信号集
    sigset_t set;
    // 2.初始化信号集
    sigemptyset(&set);
    // 3.将信号添加到信号集中
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGUSR2);

    sigdelset(&set,SIGUSR1);
    // 4.判断 某某信号是否添加到集合中
    /* 如果signum是集合的成员，则sigismember（）返回1，如果signum不是集合的成员则返回0，如果出现错误则返回-1。 */
    if (sigismember(&set, SIGUSR1))
    {
        printf("yes.\n");
    }
    else
    {
        printf("no.\n");
    }
    return 0;
}

#endif

#if 0
/* 信号集的阻塞函数 */
void signalHandle(int signum)
{
    printf("捕捉到%d信号，执行中----\n", signum);
    int count = 5;
    while (count--)
    {
        sleep(1);
        fprintf(stderr, " ======= %d =======%c", count, count == 0 ? '\n' : '\r');
    }
    printf("执行完成\n");
}

void handle(int signum)
{
    printf("捕捉到%d信号，执行中----\n", signum);
    int count = 5;
    while (count--)
    {
        sleep(1);
        fprintf(stderr, " ======= %d =======%c", count, count == 0 ? '\n' : '\r');
    }
    printf("执行完成\n");
}

int main(int argc, char *argv[])
{
    // 将信号设置信号响应
    signal(SIGUSR2, signalHandle);
    signal(SIGRTMAX - 4, signalHandle);
    signal(SIGINT, handle);
    /* sigemptyset（）、sigfillset（）、sigaddset（）和sigdelset（）在成功时返回0，在错误时返回-1。 */
    // 1.先定义一个信号集
    sigset_t set;
    // 2.初始化信号集
    sigemptyset(&set);
    // 3.将信号添加到信号集中
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGUSR2);
    sigaddset(&set, SIGRTMAX - 4);

    sigdelset(&set, SIGUSR1); // 删除SIGUSR1
    // 将上面的信号集合中的所有信号     设置为阻塞状态
    sigprocmask(SIG_BLOCK, &set, NULL);
    /* 在此期间set集合中所有信号挂起 */
    int cnt = 5;
    while (cnt--)
    {
        sleep(1);
        printf("[%d]:主进程正在执行中......\n", getpid());
    }

    // 解除阻塞状态
    sigprocmask(SIG_UNBLOCK, &set, NULL);
    raise(SIGUSR2);
    raise(SIGINT);

    return 0;
}

#endif


#if 0
/* 验证父子进程的阻塞属性 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void sigusr1_handler(int signum) {
    printf("收到SIGUSR1信号\n");
}

int main() {
    pid_t child_pid;
    sigset_t set;

    // 初始化信号集
    sigemptyset(&set);

    // 将SIGUSR1加入信号集
    sigaddset(&set, SIGUSR1);

    // 设置信号集为阻塞状态
    sigprocmask(SIG_BLOCK, &set, NULL);

    // 注册SIGUSR1信号处理函数
    signal(SIGUSR1, sigusr1_handler);

    child_pid = fork();
    if (child_pid == 0) {
        // 子进程
        sleep(5); // 等待5秒钟，确保父进程已经将信号设置为阻塞状态
        kill(getppid(), SIGUSR1); // 向父进程发送SIGUSR1信号
        return 0;
    } else if (child_pid > 0) {
        // 父进程
        printf("父进程开始阻塞SIGUSR1信号\n");
        sleep(10); // 阻塞信号持续10秒钟
        printf("解除对SIGUSR1信号的阻塞\n");
        sigprocmask(SIG_UNBLOCK, &set, NULL); // 解除对SIGUSR1信号的阻塞
    } else {
        // fork失败
        perror("fork失败");
        return 1;
    }

    return 0;
}

#endif


#if 1
/* 验证获取IPC的key值是否相同 */
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
#endif