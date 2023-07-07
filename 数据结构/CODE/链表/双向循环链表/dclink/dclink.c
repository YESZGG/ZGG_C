#include "dclink.h"

/*初始化头结点*/
struct dclink *init_head()
{
    struct dclink *head = malloc(sizeof(struct dclink));
    if(head == NULL)
    {
        printf("malloc head fail\n");
        return NULL;
    }

    //数据域
    head->num = 0;

    //指针域
    head->prev = head; //前驱指针指向自己
    head->next = head; //后驱指针指向自己

    return head;
}

/*初始化其它结点*/
struct dclink *init_node(int data)
{
    struct dclink *node = malloc(sizeof(struct dclink));
    if(node == NULL)
    {
        printf("malloc node fail\n");
        return NULL;
    }

    //数据域
    node->num = data;

    //指针域
    node->prev = NULL; 
    node->next = NULL; 

    return node;
}

#if 1
/*头插*/
void insert_head(struct dclink *head,struct dclink *node)
{
    // if(head->next == head) //空链表的情况可以合在下面的代码中
    // {
    //     node->prev = head;
    //     node->next = head;
    //     head->prev = node;
    //     head->next = node;
    // }

    node->prev = head; //1线
    node->next = head->next; //2线
    head->next->prev = node;  //3线  如果是空链表 这句话断错需要额外判断
    head->next = node;  //4线
}

/*尾插*/
void insert_tail(struct dclink *head,struct dclink *node)
{
    node->prev = head->prev; //1
    node->next = head;  //2
    head->prev->next = node; //3 -->3线和4线不能交换
    head->prev = node; //4
}

/*头插+新建结点*/
void insert_head_data(struct dclink *head,int data)
{
    struct dclink *node = malloc(sizeof(struct dclink));
    if(node == NULL)
    {
        printf("malloc node fail\n");
        return;
    }
    //数据域
    node->num = data;
    //指针域
    node->prev = NULL; 
    node->next = NULL;    

    //头插 
    node->prev = head; //1线
    node->next = head->next; //2线
    head->next->prev = node;  //3线  如果是空链表 这句话断错需要额外判断
    head->next = node;  //4线
}

/*尾插+新建结点*/
void insert_tail_data(struct dclink *head,int data)
{
    struct dclink *node = malloc(sizeof(struct dclink));
    if(node == NULL)
    {
        printf("malloc node fail\n");
        return;
    }
    //数据域
    node->num = data;
    //指针域
    node->prev = NULL; 
    node->next = NULL;   

    //尾插    
    node->prev = head->prev; //1
    node->next = head;  //2
    head->prev->next = node; //3 -->3线和4线不能交换
    head->prev = node; //4
}
#else
/*万能插入 --->内核链表的思想*/
void insert_node(struct dclink *prev_node,struct dclink *node,struct dclink *next_node)
{
    node->prev = prev_node;
    node->next = next_node;
    next_node->prev = node;
    prev_node->next = node;
}
void insert_head(struct dclink *head,struct dclink *node)  //头插
{
    //head  ----  node  ----  head->next
    insert_node(head,node,head->next);
}
void insert_tail(struct dclink *head,struct dclink *node)   //尾插
{
    //head->prev  ----  node  -----  head
    insert_node(head->prev,node,head);
}
#endif


/*头删*/
void delete_head(struct dclink *head)
{
    if(head->next == head)
        return;

    //不需要考虑空链表和一个结点 因为没有NULL指针
    struct dclink *tmp=NULL;
    tmp = head->next;

    head->next->next->prev = head; //1线
    head->next = head->next->next; //2线

    free(tmp);
}

/*尾删*/
void delete_tail(struct dclink *head)
{

    if(head->next == head)
        return;

    //空链表的时候不会出现段错误
    struct dclink *tmp=NULL;
    tmp = head->prev;

    head->prev->prev->next = head; //1线
    head->prev = head->prev->prev; //2线

    free(tmp);
}

/*任意删*/
void delete_node(struct dclink *head,int data)
{
    //不需要考虑空链表和一个结点
    struct dclink *p=NULL,*tmp=NULL;
    for(p=head;p->next!=head;p=p->next)
    {
        //1.先找到结点
        if(p->next->num == data)
        {
            //2.存删除的结点
            tmp = p->next;
            //3.建立新的链接
            p->next->next->prev = p;
            p->next = p->next->next;
            //4.释放存储的结点
            free(tmp);
        }
    }
}


/*遍历链表-->next*/
void display_next(struct dclink *head)
{
    struct dclink *p = NULL;
    for(p=head->next;p!=head;p=p->next)
    {
        printf("%d<-",p->num);
    }
    printf("\n");
}

/*遍历链表-->prev*/
void display_prev(struct dclink *head)
{
    struct dclink *p = NULL;
    for(p=head->prev;p!=head;p=p->prev)
    {
        printf("%d<-",p->num);
    }
    printf("\n");
}

/*释放链表*/
void release(struct dclink *head)
{
    struct dclink *p=NULL,*tmp=NULL;
    for(p=head->next;p!=head;)
    {
        tmp = p;
        p=p->next;
        free(tmp);
    }
    free(head);
    printf("release list ok\n");
}

/*查找结点*/
void find_node(struct dclink *head,int data)
{
    struct dclink *p = NULL;
    for(p=head->next;p!=head;p=p->next)
    {
        if(p->num == data)
            printf("find it ok %d<-\n",p->num);
    }
    //printf("find no %d<-\n",data);
}

/*修改结点*/
void change_node(struct dclink *head,int data,int new_data)
{
    struct dclink *p = NULL;
    for(p=head->next;p!=head;p=p->next)
    {
        if(p->num == data)
        {
            p->num = new_data;
            printf("change it %d to %d\n",data,new_data);
        }
    }
    printf("\n");
}

