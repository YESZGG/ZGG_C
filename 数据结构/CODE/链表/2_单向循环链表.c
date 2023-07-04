#include <stdio.h>
#include <stdlib.h>

/*
    单向循环链表--->里面的每一个结点都没有NULL指针
*/

// 设计一个结点模型
struct list
{
    /*数据域*/
    int num;

    /*指针域*/
    struct list *next;
};

/*初始化头结点*/
struct list *init_head()
{
    /*给头结点申请空间*/
    struct list *head = malloc(sizeof(struct list));
    if (head == NULL)
    {
        printf("malloc head fail\n");
        return NULL;
    }

    /*给头结点赋值*/
    // 数据域赋值
    head->num = 0; // 无效值

    // 指针域赋值
    head->next = head; // 如果指向head自己就是循环链表,如果指向的是NULL就是非循环链表

    return head;
}

/*初始化其它结点*/
struct list *init_node(int data)
{
    /*给其它结点申请空间*/
    struct list *node = malloc(sizeof(struct list));
    if (node == NULL)
    {
        printf("malloc node fail\n");
        return NULL;
    }

    // 数据域赋值
    node->num = data; // 有效值

    // 指针域赋值
    node->next = NULL;

    // 返回结点
    return node;
}

/*插入结点*/
// 头插
void insert_head(struct list *head, struct list *node)
{
#if 0 // 两种情况可以合二为一
    /*空链表*/
    if(head->next == head)
    {
        node->next = head;
        head->next = node;
    }
    else
    {
        /*非空链表*/
        //先建立1线
        node->next = head->next; //如果是空链表 这句话等价于node->next=head;
        //再建立2线
        head->next = node;
    }
#endif

    // 先建立1线
    node->next = head->next;
    // 再建立2线
    head->next = node;
}

/*尾插*/
void insert_tail(struct list *head, struct list *node)
{
    struct list *p = NULL;
    for (p = head; p->next != head; p = p->next)
        ;
    node->next = head;
    p->next = node;
}

/*头删*/
void delete_head(struct list *head, struct list *node)
{
    // 如果链表没有存储任何信息，直接返回
    if (head->next == head)
        return;
    struct list *tmp = NULL;
    tmp = head->next;
    head->next = head->next->next;
    free(tmp);
}

/*尾删*/
void delete_tail(struct list *head)
{
    if (head->next == head)
        return;
    struct list *p = head;
    struct list *tmp = NULL;
    // 特殊处理头节点即为尾节点的情况
    if (head->next->next == head)
    {
        tmp = head->next;
        head->next = head;
        free(tmp);
        return;
    }
    while (p->next->next != head)
    {
        p = p->next;
    }
    tmp = p->next;
    p->next = head;
    free(tmp);
}

/*任意删*/
void delete_node(struct list *head, struct list *node)
{
    if (head->next == head)
    {
        printf("该单向循环链表未存储任何信息.\n");
        return;
    }
    struct list *p = NULL, *tmp = NULL;
    for (p = head; p->next != head; p = p->next)
    {
        // 找到要删除的节点
        if (p->next->num == node->num)
        {
            // 建立新的连接
            tmp = p->next;
            p->next = p->next->next;

            // 释放存储的节点
            free(tmp);
            return;
        }
    }
    printf("未找到要删除的目标节点.\n");
}

/*查找结点*/
void find_node(struct list *head)
{
    int target;
    printf("----------查找----------\n");
    printf("请输入您想要查找的数字：");
    scanf("%d", &target);
    if (head->next == head)
    {
        printf("该链表是空链表，没有数据.\n");
    }
    struct list *p = NULL;
    int count = 1;
    for (p = head->next; p != head; p = p->next)
    {
        if (p->num == target)
        {
            printf("查找成功,在第%d个.\n", count);
            return;
        }
        count++;
    }
    printf("查找失败，未找到%d.", target);
}

/*修改结点*/
void change_node(struct list *head)
{
    printf("----------修改----------\n");
    if (head->next == head)
    {
        printf("该链表未存储任何信息.\n");
        return;
    }
    int num;
    printf("请输入要修改的数字：");
    scanf("%d", &num);
    struct list *p = NULL;
    for (p = head->next; p != head; p = p->next)
    {
        if (p->num == num)
        {
            printf("请输入修改后的数字：");
            scanf("%d", &p->num);
            printf("修改成功.\n");
            return;
        }
    }
    printf("修改失败.\n");
}

/*遍历链表*/
void display(struct list *head)
{
    struct list *p = NULL;
    for (p = head->next; p != head; p = p->next)
    {
        printf("%d ", p->num);
    }
    printf("\n");
}

/*释放链表*/
void relase(struct list *head)
{
    struct list *p = NULL, *tmp = NULL;
    for (p = head->next; p != head;)
    {
        // 先存起来
        tmp = p;
        // 再建立新连接
        p = p->next;
        // 最后释放
        free(tmp);
    }
    // 再释放头结点
    free(head);
}
int main()
{
    // 初始化头结点
    struct list *head = init_head();
    if (head == NULL)
    {
        printf("init head fail\n");
        return 0;
    }

    struct list *node1, *node2, *node3, *node4, *node5;
    node1 = init_node(10);
    node2 = init_node(20);
    node3 = init_node(30);
    node4 = init_node(40);
    node5 = init_node(50);

    /*插入*/
    // 头插
    printf("[insert_head]:\n");
    insert_head(head, node3);
    insert_head(head, node2);
    insert_head(head, node1);
    display(head);

    // 尾插
    printf("[insert_tail]:\n");
    insert_tail(head, node4);
    insert_tail(head, node5);
    display(head);

    /*删除*/
    // 头删
    printf("[delete_head]:\n");
    delete_head(head, node1);
    display(head);

    // 尾删
    printf("[delete_tail]:\n");
    delete_tail(head);
    display(head);

    // 任意删
    printf("[delete node]:\n");
    delete_node(head, node3);
    display(head);

    // 查找
    find_node(head);
    display(head);

    // 修改
    change_node(head);
    display(head);

    // 释放
    printf("relase\n");
    relase(head);
    return 0;
}