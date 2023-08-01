#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#if 0
//int a = 100;

int main()
{
    //原本进程的代码(主要是用来验证栈、数据段、堆里面的数据是共享的)
    int a = 100; //a是局部变量，是栈区
    // static int a = 100; //a是静态变量，存放在数据段
    printf("main\n");
    
    //使用vfork创建一个子进程,父进程与子进程共享数据段
    pid_t id = vfork();
    if(id == -1)//出错
    {
        printf("fork error\n");
        return -1;
    }
    else if(id >0)//父进程
    {   
        printf("parent:%d a addr:%p value:%d\n",getpid(),&a,a);  //250   
    }
    else if(id == 0)//子进程
    {       
        a = 250; //子进程修改变量a的值
        printf("child:%d a addr:%p value:%d\n",getpid(),&a,a); //250
        sleep(5);
        //exit(0);//让子进程到这里就结束 
    }
    
    //阻塞等待 子进程退出
    wait(NULL);
    
    return 0;
}
#endif
/* 
特点:
1、子进程与父进程共享内存空间，更加准确来说，子进程在调用exec函数簇或者exit函数之前内存空间是共享的2、一定是子进程先运行，
   而且是等子进程结束之后，父进程才开始运行
3、当子进程调用exit之后，父进程才会往下执行
4、你在引用的时候，最好尽快结束子进程(注意)
5、使用vfork创建出来的子进程，一定要使用exec或者exit退出进程。否则导致程序死锁,程序会出现异常
 */


int global_variable = 100;  // 全局变量，存放在数据段

int main() {
    int stack_variable = 200;  // 局部变量，存放在栈区
    
    int* heap_variable = (int*) malloc(sizeof(int));  // 堆变量，存放在堆区
    *heap_variable = 300;
    
    printf("Main Process\n");
    printf("Global Variable: %d, Address: %p\n", global_variable, &global_variable);
    printf("Stack Variable: %d, Address: %p\n", stack_variable, &stack_variable);
    printf("Heap Variable: %d, Address: %p\n", *heap_variable, heap_variable);
    
    pid_t id = vfork();
    
    if(id == -1) {  // 出错
        printf("vfork error\n");
        return -1;
    }
    else if(id > 0) {  // 父进程
        printf("Parent Process: %d\n", getpid());
        printf("Global Variable: %d, Address: %p\n", global_variable, &global_variable);
        printf("Stack Variable: %d, Address: %p\n", stack_variable, &stack_variable);
        printf("Heap Variable: %d, Address: %p\n", *heap_variable, heap_variable);
        wait(NULL);
    }
    else if(id == 0) {  // 子进程
        printf("Child Process: %d\n", getpid());
        printf("Global Variable: %d, Address: %p\n", global_variable, &global_variable);
        printf("Stack Variable: %d, Address: %p\n", stack_variable, &stack_variable);
        printf("Heap Variable: %d, Address: %p\n", *heap_variable, heap_variable);
        
        stack_variable = 400;
        *heap_variable = 500;
        
        printf("Modified Stack Variable in Child Process: %d, Address: %p\n", stack_variable, &stack_variable);
        printf("Modified Heap Variable in Child Process: %d, Address: %p\n", *heap_variable, heap_variable);
        
        _exit(0);
    }
    
    free(heap_variable);
    
    return 0;
}
