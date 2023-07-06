#include <stdio.h>
#include <stdlib.h>

/*设计一个双向循环链表的结点模型*/
struct dclink
{
    /*数据域*/
    int num;

    /*指针域*/
    struct dclink *prev; //前驱指针
    struct dclink *next; //后驱指针
};


#if 0
typedef struct dclink
{
    /*数据域*/
    int num;

    /*指针域*/
    struct dclink *prev; //前驱指针
    struct dclink *next; //后驱指针
}dclink_t,*dclink_p;
#endif

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
struct dclink *init_node()
{
    struct dclink *node = malloc(sizeof(struct dclink));
    if(node == NULL)
    {
        printf("malloc node fail\n");
        return NULL;
    }

    //数据域
    node->num = 0;

    //指针域
    node->prev = NULL; 
    node->next = NULL; 

    return node;
}



int main()
{
    //初始化头结点
    struct dclink *head = init_head();
    if(head == NULL)
    {
        printf("init head fail\n");
        return -1;
    }

    //初始化其它结点
    struct dclink *node1,*node2,*node3,*node4,*node5,*node6;
    node1 = init_node(10);
    node1 = init_node(20);
    node1 = init_node(30);
    node1 = init_node(40);
    node1 = init_node(50);
    node1 = init_node(60);

    //头插


    //尾插


    //遍历


    //释放

    return 0;
}