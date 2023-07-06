#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dlink
{
    /*数据域*/
    int num;

    /*指针域*/
    struct dlink *prev; // 前驱指针
    struct dlink *next; // 后驱指针
};
struct dlink *init_head();
struct dlink *init_node();
void insertHead(struct dlink *head);
void insertTail(struct dlink *head);
void printLink(struct dlink *head);
void displayPrev(struct dlink *head);
void release(struct dlink *head);

// 初始化头结点
struct dlink *init_head()
{
    struct dlink *head = (struct dlink *)malloc(sizeof(struct dlink));
    if (head == NULL)
    {
        printf("head malloc failed.\n");
        return (struct dlink *)-1;
    }
    // 赋值
    head->num = 0;
    head->prev = NULL;
    head->next = NULL;
}

struct dlink *init_node()
{
    struct dlink *node = (struct dlink *)malloc(sizeof(struct dlink));
    if (node == NULL)
    {
        printf("node malloc failed.\n");
        return (struct dlink *)-1;
    }

    // 数据域赋值
    memset(node, 0, sizeof(struct dlink));
    node->prev = NULL; // 双向非循环链表的标志
    node->next = NULL;

    return node;
}

/*-----插入-----*/
// 头插
void insertHead(struct dlink *head)
{
    printf("------头插------\n");
    struct dlink *new_node = init_node();
    if (new_node == (struct dlink *)-1)
    {
        perror("init node failed");
        return;
    }
    printf("请输入要添加的数据：");
    scanf("%d", &new_node->num);
    while(getchar() != '\n');// 清除缓冲区
    // 空链表必须要考虑
    if (head->next == NULL)
    {
        head->next = new_node;
        new_node->prev = head;
    }
    else
    {
        // 先建立新结点的连接  1线和2线
        // 1、2线没有先后之分  可以换（建议先前再后）
        new_node->prev = head;       // 1
        new_node->next = head->next; // 2
        // 3、4线不能换否则会导致head->next 丢失
        head->next->prev = new_node; // 3
        head->next = new_node;       // 4
    }
    printf("添加成功%d.\n", new_node->num);
}

// 尾插
void insertTail(struct dlink *head)
{
    printf("------尾插------\n");
    struct dlink *end_node = head; // 必须是head 否则不知道 head->next 是否未空
    struct dlink *new_node = init_node();
    if (new_node == (struct dlink *)-1)
    {
        perror("init node failed");
        return;
    }
    printf("请输入要添加的数据：");
    scanf("%d", &new_node->num);
    while(getchar() != '\n');// 清除缓冲区
    while (end_node->next != NULL)
    {
        end_node = end_node->next;
    }
    end_node->next = new_node;
    new_node->prev = end_node;

    printf("添加成功%d.\n", new_node->num);
}

/*-----删除-----*/
// 头删
void deleteHead(struct dlink *head)
{
    printf("------头删------\n");
    if (head->next == NULL)
    {
        printf("该双向非循环链表未存储任何信息.\n");
        return;
    }

    struct dlink *p = head->next;
    head->next = p->next; // 修改头结点的next指针
    // 当要删除的节点不是最后一个节点时，修改后继结点的prev指针
    if (p->next != NULL)
    {
        p->next->prev = head;
    }
    else
    {
        // 如果只有一个节点，则直接将head->next置为NULL
        head->next = NULL;
    }
    // 确保被删除节点与链表彻底断开连接
    p->next = NULL;
    p->prev = NULL;
    free(p);
    printf("头结点删除成功.\n");
}

// 尾删
void deleteTail(struct dlink *head)
{
    printf("------尾删------\n");
    if (head->next == NULL)
    {
        printf("该双向非循环链表未存储任何信息.\n");
        return;
    }

    struct dlink *p = head;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->prev->next = NULL;
    p->prev =NULL;
    p->next = NULL;
    free(p);
    printf("尾删成功.\n");
}



// 打印双向非循环链表----从头结点的下一个结点开始遍历
void printLink(struct dlink *head)
{
    struct dlink *p = head->next;
    while (p != NULL)
    {
        printf("%d ", p->num);
        p = p->next;
    }
    printf("\n");
}

// 打印双向非循环链表----从尾结点通过prev向前开始遍历
void displayPrev(struct dlink *head)
{
    struct dlink *p = head;
    // 找到链表最后一个结点 两种方法:1.while 2.for
    while (p->next != NULL)
    {
        p = p->next;
    }
    // for (p = head; p->nex != NULL; p->next);
    // 从尾结点通过prev向前遍历并打印
    while (p != head) // p != head 就代表已经到了第一个结点 头结点不需要打印
    {
        printf("%d ", p->num);
        p = p->prev;
    }
    printf("\n");
}

// 释放链表
void release(struct dlink *head)
{
    struct dlink *curr = head->next;
    struct dlink *temp;

    while (curr != NULL)
    {
        temp = curr->next;
        free(curr);
        curr = temp;
    }
    free(head);
    printf("release success.\n");
}

int main()
{
    struct dlink *head = init_head();
    if (head == (struct dlink *)-1)
    {
        perror("init head failed.");
        return -1;
    }
    // 头插
    insertHead(head);
    insertHead(head);
    printLink(head);

    // 尾插
    insertTail(head);
    insertTail(head);
    printLink(head);

    // 头删
    deleteHead(head);
    printLink(head);

    //尾删
    deleteTail(head);
    printLink(head);

    // displayPrev(head);

    release(head);
    return 0;
}