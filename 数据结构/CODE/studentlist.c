#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct list
{
    // 数据域
    int stuno;     // 学号
    char name[20]; // 姓名
    char sex;      // 性别
    int height;    // 身高
    int score;     // 成绩
    // 指针域
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
    memset(head, 0, sizeof(struct list)); // 无效值

    // 指针域赋值
    head->next = NULL;

    return head;
}

/*初始化其他节点*/
struct list *init_node(int stuno, char name[], char sex, int height, int score)
{
    struct list *node = (struct list *)malloc(sizeof(struct list));
    if (node == NULL)
    {
        printf("malloc node failed.\n");
        return NULL;
    }
    // 数据域赋值
    node->stuno = stuno;
    strcpy(node->name, name);
    node->sex = sex;
    node->height = height;
    node->score = score;

    // 指针域赋值
    node->next = NULL;
    // 返回节点
    return node;
}
// 在链表头插入新节点
void insertHeadNode(struct list *head, struct list *node)
{
    node->next = head->next;
    head->next = node;
}

// 在链表尾插入新节点
void insertTailNode(struct list *head, struct list *node)
{
    struct list *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = node;
}

// 查找
void traverseLinkedList(struct list *head)
{
    int target;
    printf("请输入您想要查找的学生的学号：");
    scanf("%d", &target);
    if (head->next == NULL)
    {
        printf("该链表是空链表，没有数据.\n");
        }
    struct list *current = head->next;
    while (current != NULL)
    {
        if (current->stuno == target)
        {
            printf("StuNo:%d\n", current->stuno);
            printf("Name: %s\n", current->name);
            printf("Sex: %c\n", current->sex);
            printf("Height: %d\n", current->height);
            printf("Score: %d\n\n", current->score);
        }
        current = current->next;
    }
}

// 打印链表中的节点内容
void printList(struct list *head)
{
    struct list *current = head->next;
    while (current != NULL)
    {
        printf("StuNo:%d\n", current->stuno);
        printf("Name: %s\n", current->name);
        printf("Sex: %c\n", current->sex);
        printf("Height: %d\n", current->height);
        printf("Score: %d\n\n", current->score);
        current = current->next;
    }
}

//删除
void deleteNode(struct list *head)
{
    struct list *current = head;
    int deletestuNo;
    printf("请输入要删除的学生的学号：");
    scanf("%d", &deletestuNo);
    while (current->next != NULL)
    {
        if(current->next->stuno == deletestuNo)
        {
            struct list *temp = current->next;
            current->next = temp->next;
            free(temp);
            printf("删除成功.\n");
            return;
        }
        current = current->next;
    }
    printf("未找到学号为%d的学生\n", deletestuNo);
}
// 释放链表内存
void freeList(struct list *head)
{
    struct list *current = head;
    while (current != NULL)
    {
        struct list *temp = current;
        current = current->next;
        free(temp);
    }
}

int main()
{
    struct list *head = init_head();
    if (head == NULL)
    {
        printf("init head fail\n");
        return -1;
    }

    struct list *node1, *node2, *node3, *node4;
    node1 = init_node(1001, "Alice", 'F', 170, 85);
    node2 = init_node(1002, "寄你太美", 'M', 180, 92);
    node3 = init_node(1003, "Cathy", 'F', 165, 78);
    node4 = init_node(1004, "贞德士尼鸭", 'M', 175, 100);
    // 插入节点
    // insertHeadNode(head, node3);
    insertHeadNode(head, node2);
    insertHeadNode(head, node1);
    // insertTailNode(head, node2);
    insertTailNode(head, node3);
    insertTailNode(head, node4);
    // 打印链表内容
    printList(head);
    traverseLinkedList(head);
    deleteNode(head);
    // 释放链表内存
    freeList(head);
    return 0;
}