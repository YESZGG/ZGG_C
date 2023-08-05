#ifndef POOL_H__
#define POOL_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <errno.h>

#define MAX_ACTIVE_THREADS 20
#define MAX_WAITING_TASKS 20
// 任务链表节点
struct task
{
    void *(*do_task)(void *arg);
    void *arg;
    // 指针域
    struct task *next;
};

// 线程池的结构体
typedef struct thread_pool
{
    pthread_mutex_t lock;       // 互斥锁
    pthread_cond_t cond;        // 条件变量
    bool shutdown;              // 当前线程池的标志位 0 为开启线程池，1 为关闭线程池
    struct task *task_list;     // 任务链表的头结点
    pthread_t *tids;            // 存储所有线程的ID号
    unsigned max_waiting_tasks; // 最大等待处理的任务数
    unsigned waiting_tasks;     // 当前等待处理的任务数
    unsigned active_threads;    // 表示当前线程池中活跃的线程数
} thread_pool;

// 线程函数
void *routine(void *arg);
// 初始化线程池
bool init_pool(thread_pool *pool,unsigned int threads_number);
// 添加任务节点
bool add_task(thread_pool *pool, void *(*do_task)(void *arg), void *arg);
// 添加线程
int add_thread(thread_pool *pool, unsigned additional_threads);
// 删除线程
int remove_thread(thread_pool *pool, unsigned int removing_threads);
// 销毁线程池
bool destroy_pool(thread_pool *pool);

#endif