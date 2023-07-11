#include <stdio.h>

#define MAX_SIZE 100

struct Queue
{
    int data[MAX_SIZE]; // data数组用于存储队列元素
    int front;          // front表示队列的前端
    int rear;           // rear表示队列的后端
};

void initQueue(struct Queue *queue)
{
    queue->front = -1;
    queue->rear = -1;
}

// queue->rear == MAX_SIZE - 1 && queue->front == 0：
// 表明队列已经填满所有元素，且队列头部是数组的第一个位置。
// queue->rear + 1 == queue->front：
// 表明队列已经环绕回到了数组的起始位置，而队列尾部位于数组的最后一个位置。
int isFull(struct Queue *queue)
{
    return (queue->rear == MAX_SIZE - 1 && queue->front == 0) || (queue->rear + 1 == queue->front);
}

int isEmpty(struct Queue *queue)
{
    return queue->front == -1;
}

// 入队
void enqueue(struct Queue *queue, int item)
{
    if (isFull(queue))
    {
        printf("Queue Overflow\n");
        return;
    }

    if (queue->front == -1)
    {
        queue->front = 0;
    }
    // 模运算 % MAX_SIZE 来保持 rear 在有效范围内
    // 保持在 0 到 MAX_SIZE-1 的范围内，防止越界
    queue->rear = (queue->rear + 1) % MAX_SIZE;
    queue->data[queue->rear] = item;
}

// 出队
int dequeue(struct Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue Underflow\n");
        return -1; // 返回一个默认值表示队列为空
    }

    int item = queue->data[queue->front];

    if (queue->front == queue->rear)
    {
        queue->front = -1;
        queue->rear = -1;
    }
    else
    {
        queue->front = (queue->front + 1) % MAX_SIZE;
    }

    return item;
}

void display(struct Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue content:\n");

    int i = queue->front;
    while (i != queue->rear)
    {
        printf("%d\n", queue->data[i]);
        i = (i + 1) % MAX_SIZE;
    }
    // 因为上面循环不能打印最后一个值 在打印一次
    printf("%d\n", queue->data[queue->rear]);
}

int main()
{
    struct Queue queue;
    initQueue(&queue);

    enqueue(&queue, 10); // 进队列
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    display(&queue); // 显示队列内容

    int dequeued = dequeue(&queue); // 出队列
    printf("Dequeued element: %d\n", dequeued);

    display(&queue); // 再次显示队列内容

    return 0;
}
