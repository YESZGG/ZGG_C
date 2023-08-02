
#if 0
#include <stdio.h>
int add(int a, int b) {
    return a + b;
}

int main() {
    // 声明一个函数指针
    int (*functionPtr)(int, int);

    // 将函数指针指向具体的函数
    functionPtr = add;

    // 使用函数指针调用函数
    int result = functionPtr(3, 4);

    printf("Result: %d\n", result);

    return 0;
}
#endif

#if 0
#include <stdio.h>
typedef int (*OperationFuncPtr)(int, int);

int add(int a, int b) {
    return a + b;
}

int main() {
    // 声明一个别名为 OperationFuncPtr 的函数指针
    OperationFuncPtr operation;

    // 将函数指针指向具体的函数
    operation = add;

    // 使用函数指针调用函数
    int result = operation(3, 4);

    printf("Result: %d\n", result);

    return 0;
}

#endif

#if 0
/* 验证一个进程可以创建多少条线程 */
#include <stdio.h>
#include <pthread.h>

#define MAX_THREAD_COUNT 1000000

void *thread_function(void *arg)
{
    // 任务逻辑
    // while (1)
    // {
    // }
    return NULL;
}

int main()
{
    pthread_t threads[MAX_THREAD_COUNT];
    int thread_count = 0;

    // 创建线程直到达到最大线程数量或创建失败为止
    while (thread_count < MAX_THREAD_COUNT && pthread_create(&threads[thread_count], NULL, thread_function, NULL) == 0)
    {
        printf("线程创建数量：%d\n",thread_count);
        thread_count++;
    }

    printf("最大线程数量：%d\n", thread_count);

    // 等待所有线程结束，实际运行时可以根据需要设置超时时间
    for (int i = 0; i < thread_count; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

#endif

#if 0
/*
练习3：
struct st
{
    char name[20];
    char sex;
    int height;
    float score;
}
使用线程将一个学生信息传递给子线程，然后在子线程中打印该学生的信息。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct st
{
    char name[20];
    char sex;
    int height;
    float score;
};

void *printStudent(void *arg)
{
    // 类型转化为结构体指针
    struct st *student = (struct st *)arg;
    printf("姓名：%s\n", student->name);
    printf("性别：%c\n", student->sex);
    printf("身高：%d\n", student->height);
    printf("分数：%-4.1f\n", student->score);

    return NULL;
}

int main()
{
    // 1.定义一个结构体变量
    struct st student;
    /*  // 定义就初始化
        struct st student ={"小明","M",180,90.5};
    */
    // 结果受到内存对齐的影响，结果为32字节
    printf("结构体大小：%ld 字节\n", sizeof(struct st));
    // 2.初始化结构体变量
    strcpy(student.name, "小明");
    student.sex = 'M';
    student.height = 180;
    student.score = 90.5;

    pthread_t tid;
    pthread_create(&tid, NULL, printStudent, (void *)&student);
    pthread_join(tid, NULL);

    return 0;
}

#endif

#if 1
#include <stdio.h>
#include <pthread.h>

int global_variable = 0; // 全局变量

void *thread_func(void *arg)
{
    int local_variable = 5; // 局部变量

    global_variable = 10; // 修改全局变量的值

    pthread_exit((void *)&local_variable); // 线程退出，返回局部变量的地址
}

int main()
{
    pthread_t thread;
    void *exit_value;

    pthread_create(&thread, NULL, thread_func, NULL);

    pthread_join(thread, &exit_value); // 等待线程结束并获取退出值

    printf("局部变量的退出值: %d\n", *((int *)exit_value));
    printf("全局变量的值: %d\n", global_variable);

    return 0;
}

#endif