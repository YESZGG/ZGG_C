#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#if 0
// 自己定义的消息队列的数据结构体
struct my_message
{
    long mtype;      // 消息类型
    char mtext[100]; // 消息内容
};

int main()
{
    // 1、确定 文件路径名 ---获取消息队列的key值
    key_t key = ftok(".", 100);
    /* 2.根据文件路径名，打开文件，不存在则创建。 --- 得到文件描述符
    根据key值，获取消息队列的ID，如果消息队列不存在则创建 */
    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1)
    {
        perror("msgget");
        return 1;
    }
    printf("消息队列 key:%#x msgid:%d\n", key, msgid);

    struct my_message msg;
    memset(&msg, 0, sizeof(msg)); // 清空整个结构体的空间
    /*
        &msg:是整个结构体的地址
        sizeof(msg.mtext)：是结构体里面数据正文的大小不是结构体的大小  sizeof(struct my_message) - sizeof(long)
    */
    if (msgrcv(msgid, &msg, sizeof(struct my_message) - sizeof(long), 1, 0) == -1)
    {
        perror("msgrcv");
        return 1;
    }

    printf("Received message: %s\n", msg.mtext);

    // 4、最后不需要 使用到这条消息队列的时候，删除即可
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
#endif


#if 1
// 自定义的消息队列的数据结构体
struct my_message
{
    long mtype;      // 消息类型
    char mtext[100]; // 消息内容
};

int main()
{
    // 1、确定文件路径名，获取消息队列的key值
    key_t key = ftok(".", 100);

    // 2、根据key值获取消息队列的ID，如果消息队列不存在则创建
    int msgid = msgget(key, IPC_CREAT | 0666);

    if (msgid == -1)
    {
        perror("msgget");
        return 1;
    }
    printf("消息队列 key:%#x msgid:%d\n", key, msgid);

    struct my_message msg;

    while (1)
    {
        memset(&msg, 0, sizeof(msg)); // 清空整个结构体的空间

        if (msgrcv(msgid, &msg, sizeof(struct my_message) - sizeof(long), 1, 0) == -1)
        {
            perror("msgrcv");
            return 1;
        }

        printf("Received message: %s\n", msg.mtext);
    }

    return 0;
}

#endif