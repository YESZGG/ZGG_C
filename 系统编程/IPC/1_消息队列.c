#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#if 1
/*
    头文件：
    #include <sys/types.h>
    #include <sys/ipc.h>
    函数原型：
    key_t ftok(const char *pathname, int proj_id);
    功能：ftok函数用于生成一个唯一的System V IPC（Inter-Process Communication，进程间通信）键值。
    返回值：如果成功，返回生成的键值；如果失败，返回-1。
    使用 ftok 函数时，需要提供一个存在的文件路径名（pathname）和一个非零整数（proj_id）。
    ftok函数将根据这两个参数生成一个唯一的键值，用于标识 System V IPC 结构（如共享内存、信号量、消息队列等）。
 */

/*
    msgctl 函数用于对消息队列进行控制操作，例如删除消息队列或修改权限等。
    #include <sys/types.h>
    #include <sys/ipc.h>
    #include <sys/msg.h>

    int msgctl(int msqid, int cmd, struct msqid_ds *buf);
    参数说明：

    msqid：要进行控制的消息队列标识符。
    cmd：控制命令，用于指定要执行的操作，可以是以下之一：
        IPC_RMID：删除消息队列。
        IPC_SET：设置消息队列的属性，需要传递 struct msqid_ds 结构体指针作为 buf 参数。
        IPC_STAT：获取消息队列的属性，将结果存储在 struct msqid_ds 结构体中。
    buf：指向 struct msqid_ds 结构体的指针，用于传递或获取消息队列的属性。

    返回值：

        如果成功，返回 0。
        如果失败，返回 -1，并设置相应的错误码。

 */
int main(int argc, char argv[])
{
    // 1.确定文件路径名
    key_t key = ftok(".", 100);
    /* 2.根据文件路径名，打开文件，不存在则创建。 --- 得到文件描述符
      根据key值，获取消息队列的ID，如果消息队列不存在则创建 */
    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1)
    {
        perror("msgget error.");
        return -1;
    }
    // # 会在输出结果前添加 0x 前缀，表示十六进制形式
    printf("消息队列 key:%#x msgid:%d.\n", key, msgid);

    // 3.删除消息队列的ID号
    // 删除消息队列
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        return 1;
    }

    printf("Message queue deleted.\n");

    return 0;
}
#endif
