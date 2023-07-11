#include <stdio.h>
#include <stdlib.h>


/*
队列--->单向非循环链表
*/

/*设计队列里面结点结构体*/
struct node
{
    int num;
    struct node *next;
};

/*设计管理队列的结构体*/
struct queue
{
    int size; //记录队列结点的个数
    struct node *head; //指向链表的首结点
    struct node *tail;  //指向链表的尾结点
};

/*初始化队列*/
struct queue *init_queue()
{
    //申请堆空间
    struct queue *q = malloc(sizeof(struct queue));
    if(q == NULL)
    {
        printf("malloc queue fail\n");
        return NULL;
    }
    //给管理队的指针赋值
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;

    return q;
}

/*入队-->尾插*/
void in_queue(struct queue *q,int data)
{
    //初始化结点
    struct node *new = malloc(sizeof(struct node));
    if(new == NULL)
    {
        printf("malloc new fail\n");
        return;
    }
    //给结点赋值
    new->num = data;
    new->next = NULL;

    /*入队（尾插）*/
    //空链表(这两种情况不能合二为一)
    if(q->tail == NULL)
    {
        q->head = new;
        q->tail = new;
    }
    else
    {
        //非空链表
        q->tail->next = new; //1 线（如果空队列这句话会段错误）
        q->tail= new; //2线 
    }

    q->size++; //队列结点的个数+1
}

/*出队-->头删*/
void out_queue(struct queue *q)
{
    struct node *tmp=NULL;

    //空链表
    if(q->head == NULL) //if(q->tail == NULL) if(q->size==0)
    {
        return;
    }
    //有1个结点的时候
    else if(q->head->next == NULL)
    {
        tmp = q->head;
        q->head = NULL; //只有一个结点的时候head和tail要清空
        q->tail = NULL;

        free(tmp);
    }
    //有多个结点（在这种情况下只有一个结点它只是清空了head没有清空tail）
    else
    {
        tmp = q->head;
        q->head = q->head->next;
        free(tmp);
    }

    //队列结点的个数要减1
    q->size--;

} 

/*遍历队列*/
void display(struct queue *q)
{
    struct node *p=NULL;
    for(p=q->head;p!=NULL;p=p->next) //for(i=0;i<q->size;i++)
    {
        printf("%d<-",p->num);
    }
    printf(" [%d]\n",q->size);

}

int main()
{
    /*初始化队列*/
    struct queue *q = init_queue();
    if(q == NULL)
    {
        printf("init queue fail\n");
        return -1;
    }

    /*入队*/
    in_queue(q,10);
    in_queue(q,20);
    in_queue(q,30);
    display(q);

    /*出队*/
    out_queue(q);
    out_queue(q);
    out_queue(q);
    out_queue(q);

    //如果不判断1个结点的情况 那么下面这个功能无法实现
    if(q->tail == NULL)
    {
        printf("ok\n");
    }

    /*遍历队列*/
    display(q);

    /*销毁队列*/
    // destroy_queue(q);

    return 0;
}