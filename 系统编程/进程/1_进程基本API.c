#include <stdio.h>

#if 0
#include <unistd.h>

int main(int argc,char argv[])
{
    int i = 1;
    while (i != 11)
    {
        printf("%d: helloc world!\n",i);
        sleep(1);
        i++;
    }
    

    return 0;
}
#endif

#if 0

/*
    void assert(int expression);
    assert函数接受一个表达式作为参数，如果表达式为假（即0），则会触发断言失败，并输出一条错误消息，最后终止程序的执行。
    断言是一种用于调试和诊断程序错误的工具。它允许程序员在代码中插入一些预期为真的条件，如果这些条件不满足，就表示程序出现了错误。
    注意，正式发布的程序中通常会关闭断言功能，可以通过在编译时定义NDEBUG宏来实现。例如，在gcc编译器中，可以使用-DNDEBUG选项关闭断言：

    gcc -DNDEBUG example.c -o example

    这样，所有的assert语句都会被忽略，不会影响程序的执行。
    因此，断言适用于调试和开发阶段，用于检查常常认为是真实的条件是否满足，以帮助程序员发现潜在的错误。

*/

#include <assert.h>

int divide(int dividend, int divisor)
{
    assert(divisor != 0); // 断言确保除数不为0
    return dividend / divisor;
}

int main()
{
    int result = divide(10, 2);
    printf("Result: %d\n", result);

    result = divide(10, 0);         // 触发断言失败
    printf("Result: %d\n", result); // 这行代码不会被执行

    return 0;
}
#endif

#if 0
/*
    #include <sys/types.h>
    #include <sys/wait.h>

    pid_t wait(int *wstatus);

主要功能：
    阻塞当前进程。
    等待其子进程退出并回收其系统资源

接口解析：
    如果当前进程没有子进程，则该函数立即返回。
    如果当前进程有不止1个子进程，则该函数会回收第一个变成僵尸态的子进程的系统资源。
    子进程的退出状态（包括退出值、终止信号等）将被放入wstatus所指示的内存中，
    若wstatus指针为NULL，则代表当前进程放弃其子进程的退出状态。

    参数可以设为以下两种情况之一：
    1.int* wstatus：传递一个指向整型变量的指针，用于存储子进程的退出状态。父进程将通过这个指针获取子进程的退出状态信息。
    2.NULL：表示父进程放弃获取子进程的退出状态，不关心子进程的结束状态和相关信息。

    需要注意的是，wait()函数在等待子进程结束时会阻塞父进程，直到有一个子进程结束或被信号中断。
    如果父进程有多个子进程，可以通过多次调用wait()函数来依次处理每个子进程的退出状态。
 */

#include <unistd.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char argv[])
{
    pid_t pid = fork();
    assert(pid != -1); // 如果触发断言，则下面这行代码不会被执行
    // 在父进程中，pid将是子进程的PID
    // 在子进程中，pid将是0
    // 加上如下语句，确保子进程先退出
    wait(NULL);
    printf("[%d]:Process pid = %d.\n", getpid(), pid); // 函数 getpid() 的功能是获取自身进程的PID
    return 0;
}

#endif

#if 0
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    
    if (pid == -1) {
        // 创建子进程失败
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // 子进程执行的代码
        printf("Child process\n");
        return 0;
    } else {
        // 父进程执行的代码
        printf("Parent process\n");
        
        int wstatus;
        pid_t child_pid = wait(&wstatus);
        
        if (child_pid == -1) {
            // 等待子进程失败
            perror("wait");
            return 1;
        }
        
        if (WIFEXITED(wstatus)) {
            // 子进程正常退出
            int exit_status = WEXITSTATUS(wstatus);
            printf("Child process exited with status: %d\n", exit_status);
        } else {
            // 子进程异常退出
            printf("Child process terminated abnormally\n");
        }
        
        return 0;
    }
}
#endif

#if 1
/*
#include <sys/types.h>
#include <sys/wait.h>

pid_t waitpid(pid_t pid, int *wstatus, int options);

    pid：要等待的进程ID。有几种特殊取值：
        -1：等待任意子进程；
        0：等待与调用进程在同一个进程组的任意子进程；
        正整数：等待进程ID等于pid的子进程。
    wstatus：保存进程状态信息的指针，如果不关心进程的终止状态可以传入NULL。
    options：选项，用于指定等待的类型和行为。

与wait()的区别：

    可以通过参数 pid 用来指定想要回收的子进程。
    可以通过 options 来指定非阻塞等待。



    pid 	            作用 	                            options 	            作用
    <-1 	等待组ID等于pid绝对值的进程组中的任意一个子进程 	    0 	            阻塞等待子进程的退出
    -1 	    等待任意一个子进程 	                              WNOHANG 	        若没有僵尸子进程，则函数立即返回
    0 	    等待本进程所在的进程组中的任意一个子进程 	         WUNTRACED 	       当子进程暂停时函数返回
    >0 	    等待指定pid的子进程 	                         WCONTINUED 	   当子进程收到信号SIGCONT继续运行时函数返回

注意：
options的取值，可以是0，也可以是上表中各个不同的宏的位或运算取值。
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t child_pid;
    int status;

    // 创建子进程
    child_pid = fork();

    if (child_pid == 0)
    {
        // 在子进程中执行任务
        printf("Child process: PID=%d\n", getpid());
        sleep(2);
        exit(123); // 子进程退出，返回状态码123
    }
    else if (child_pid > 0)
    {
        // 在父进程中等待子进程结束
        printf("Parent process: Child PID=%d\n", child_pid);

        // 使用waitpid等待子进程
        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status))
        {
            // 子进程正常终止
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            // 子进程被信号终止
            printf("Child process terminated by signal: %d\n", WTERMSIG(status));
        }
    }
    else
    {
        perror("fork error");
        exit(1);
    }

    return 0;
}

#endif

// getpid() 获取自己的进程号    getppid() 获取父进程的进程号
#if 0
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid == -1)
    {
        // 创建子进程失败
        perror("fork");
        return 1;
    }
    else if (pid == 0)
    {
        // 子进程执行的代码
        printf("[%d]:Child process. Parent pid = %d.\n", getpid(), getppid());
    }
    else
    {
        // 父进程执行的代码
        printf("[%d]:Parent process. Child pid = %d.\n", getpid(), pid);
    }

    return 0;
}

#endif

// 进程的回收
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 

int main()
{
    if(fork() == 0)
    {
        printf("[%d]: 我将在3秒后正常退出，退出值是88\n", getpid());

        for(int i=3; i>=0; i--)
        {
            fprintf(stderr, " ======= %d =======%c", i, i==0?'\n':'\r');
            sleep(1);
        }

        exit(88);
    }

    else
    {
        printf("[%d]: 我正在试图回收子进程的资源...\n", getpid());

        int status;
        wait(&status);

        if(WIFEXITED(status))
        {
            printf("[%d]: 子进程正常退出了，其退出值是：%d\n", getpid(), WEXITSTATUS(status));
        }
    }
}

#endif
