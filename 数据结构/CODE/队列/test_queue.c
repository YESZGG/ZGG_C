#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 队列中结点的结构体定义
struct queue_node
{
    int num;
    struct queue_node *next;
};
// 队列的结构体定义
struct queue
{
    int size;
    struct queue_node *front; // 队列的头指针
    struct queue_node *rear;  // 队列的尾指针
};

// 队列的初始化
struct queue *init_queue()
{
    struct queue *queue = (struct queue *)malloc(sizeof(struct queue));
    if (queue == NULL)
    {
        perror("malloc queue failed.");
        return NULL;
    }
    // 初始化为null
    memset(queue, 0, sizeof(struct queue));

    return queue;
}

// 入队
void queue_in(struct queue *queue, int num)
{
    struct queue_node *newnode = (struct queue_node *)malloc(sizeof(struct queue_node));
    if (newnode == NULL)
    {
        perror("malloc newnode failed.");
        return;
    }
    // 给新结点赋值
    newnode->num = num;
    newnode->next = NULL;

    if (queue->front == NULL && queue->rear == NULL)
    {
        queue->front = newnode;
        queue->rear = newnode;
    }
    else
    {
        queue->rear->next = newnode;
        queue->rear = newnode;
    }
    // 大小增大
    queue->size++;
}

// 出队
void queue_out(struct queue *queue)
{
    struct queue_node *temp = NULL;
    if (queue->front == NULL && queue->rear == NULL)
    {
        printf("该队列为空.\n");
        return;
    }
    // 非空 但只有一个结点
    else if (queue->front == queue->rear)
    {
        temp = queue->front;
        queue->front = NULL;
        queue->rear = NULL;
    }
    // 非空 且不止有一个结点
    else
    {
        temp = queue->front;
        queue->front = queue->front->next;
    }
    printf("Queue out element:%d\n", temp->num);
    free(temp);
    queue->size--;
}

// 遍历
void display(struct queue *queue)
{
    struct queue_node *p = queue->front;
    printf("Queue content:\n");
    while (p != NULL)
    {
        printf("%d ", p->num);
        p = p->next;
    }
    printf("\nQueue size:%d\n", queue->size);
}

// 销毁队列
void destroyQueue(struct queue *queue)
{
    struct queue_node *temp = NULL;
    while (queue->front != queue->rear)
    {
        temp = queue->front;
        queue->front = queue->front->next;
        free(temp);
    }
    free(queue);
    printf("Destroy queue success.\n");
}

int main()
{
    struct queue *queue = init_queue();
    if (queue == NULL)
    {
        perror("init queue failed.");
        return -1;
    }

    // 入队
    // queue_in(queue, 10);
    // queue_in(queue, 20);
    // queue_in(queue, 30);
    int input, i = 6;
    printf("Please enter the value for joining the queue：");
    while (i)
    {
        scanf("%d", &input);
        // while(getchar()!= '\n'); 用了这个要换行
        if (i == 1)
        {
            while (getchar() != '\n');
        }
        queue_in(queue, input);
        i--;
    }
    display(queue);
    // 出队
    while (queue->size != 0)
    {
        queue_out(queue);
    }

    // display(queue);
    // 释放内存
    destroyQueue(queue);

    return 0;
}
