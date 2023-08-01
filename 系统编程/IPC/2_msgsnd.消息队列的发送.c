#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#if 0
// 自己定义的消息队列的数据结构体
struct my_message
{
    long mtype;      // 消息类型，必须是一个正整数
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

    // 3、往文件中写入数据 --------往消息队列中 发送数据
    struct my_message msg;
    msg.mtype = 1; // 设置消息类型为 1
    sprintf(msg.mtext, "Hello, Message Queue!");
    /*
        &msg:是整个结构体的地址
        strlen(msg.mtext)：是结构体里面数据正文的长度不是结构体的长度 sizeof(struct my_message) - sizeof(long)
    */
    if (msgsnd(msgid, &msg, sizeof(struct my_message) - sizeof(long), 0) == -1)
    {
        perror("msgsnd");
        return 1;
    }

    printf("Message sent.\n");

    return 0;
}
#endif


#if 1
#include <unistd.h>
// 自定义的消息队列的数据结构体
struct my_message
{
    long mtype;      // 消息类型，必须是一个正整数
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

    // 3、循环发送消息
    struct my_message msg;
    msg.mtype = 1; // 设置消息类型为 1

    while (1)
    {
        // 设置消息内容
        sprintf(msg.mtext, "Hello, Message Queue!");

        // 向消息队列发送消息
        if (msgsnd(msgid, &msg, sizeof(struct my_message) - sizeof(long), 0) == -1)
        {
            perror("msgsnd");
            return 1;
        }

        printf("Message sent.\n");

        // 延时一段时间，以便观察结果
        sleep(1);
    }

    return 0;
}

#endif