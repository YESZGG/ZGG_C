#include "bookmanagement.h"

/*初始化头结点*/
struct bookList *init_head()
{
    /*给头结点申请空间*/
    struct bookList *head = (struct bookList *)malloc(sizeof(struct bookList));
    if (head == NULL)
    {
        printf("malloc head fail\n");
        return (struct bookList *)-1;
    }

    /*给头结点赋值*/
    // 数据域赋值
    memset(head, 0, sizeof(struct bookList));

    // 指针域赋值
    head->next = head; // 如果指向head自己就是循环链表,如果指向的是NULL就是非循环链表

    return head;
}

/*初始化其他结点*/
struct bookList *init_node()
{
    /*给其他结点申请空间*/
    struct bookList *node = (struct bookList *)malloc(sizeof(struct bookList));
    if (node == NULL)
    {
        printf("malloc node failed.\n");
        return (struct bookList *)-1;
    }
    memset(node, 0, sizeof(struct bookList));
    node->next = NULL;
    return node;
}

// 头插
void insertHead(struct bookList *head)
{
    struct bookList *new_node = init_node();
    if (new_node == (struct bookList *)-1)
    {
        perror("new_node init failed.");
        return;
    }
    printf("--------头插--------\n");
    printf("请输入:书籍号\t书籍封面颜色\t作者名字\t图书页数\t图书名\n");
    scanf("%d %s %s %d %[^\n]", &new_node->bookno, new_node->color, new_node->authorSName, &new_node->page, new_node->title);
    while (getchar() != '\n');// 清除缓冲区
    new_node->next = head->next;
    head->next = new_node;
    printf("添加成功.\n");
}

// 尾插
void insertTail(struct bookList *head)
{
    struct bookList *new_node = init_node();
    if (new_node == (struct bookList *)-1)
    {
        perror("new_node init failed.");
        return;
    }
    struct bookList *p = head;
    while (p->next != head)
    {
        p = p->next;
    }
    printf("--------尾插--------\n");
    printf("请输入:书籍号\t书籍封面颜色\t作者名字\t图书页数\t图书名\n");
    scanf("%d %s %s %d %[^\n]", &new_node->bookno, new_node->color, new_node->authorSName, &new_node->page, new_node->title);
    while (getchar() != '\n');// 清除缓冲区
    new_node->next = head;
    p->next = new_node;
    printf("添加成功.\n");
}

// 打印单向循环链表
void printList(struct bookList *head)
{
    struct bookList *p = head->next;
    if (head->next == NULL)
    {
        printf("图书管理系统未存储任何信息.\n");
        return;
    }
    int count = 1;
    printf("\t书籍号\t书籍封面颜色\t作者名字\t图书页数\t图书名\n");
    while (p != head)
    {
        printf("[%d]:\t%-5d\t%-10s\t%-15s\t%-5d\t\t%-20s\n", count, p->bookno, p->color, p->authorSName, p->page, p->title);
        p = p->next;
        count++;
    }

    printf("\n");
}

// 检索图书信息
void findBook(struct bookList *head)
{
    struct bookList *p = head->next;
    // 1.输出所有红色封面的图书
    int count = 1;
    printf("红色封面的图书：\n");
    while (p != head) // 遍历链表直到回到头节点
    {
        if (strcmp(p->color, "red") == 0) // 检查当前节点的封面颜色是否为红色
        {
            printf("\t书籍号\t书籍封面颜色\t作者名字\t图书页数\t图书名\n");
            printf("[%d]:\t%-5d\t%-10s\t%-15s\t%-5d\t\t%-20s\n", count, p->bookno, p->color, p->authorSName, p->page, p->title);
        }
        count++;
        p = p->next;
    }
    // 2.输出页数高于250的图书所有信息
    printf("页数高于250的图书：\n");
    p = head->next; // 重新从第一个结点开始遍历
    count = 1;
    while (p != head)
    {
        if (p->page > 250) // 检查当前节点的页数是否高于250
        {
            printf("\t书籍号\t书籍封面颜色\t作者名字\t图书页数\t图书名\n");
            printf("[%d]:\t%-5d\t%-10s\t%-15s\t%-5d\t\t%-20s\n", count, p->bookno, p->color, p->authorSName, p->page, p->title);
        }
        count++;
        p = p->next; // 移动到下一个节点
    }
}

// 功能界面
int Function_Select(struct bookList *head)
{
    int select_num;
    while (1)
    {
        system("clear");
        printf("<<<<<<<\t\t1 头插添加图书信息\t>>>>>>>\n");
        printf("<<<<<<<\t\t2 尾插添加图书信息\t>>>>>>>\n");
        printf("<<<<<<<\t\t3 指定位置图书信息\t>>>>>>>\n");
        printf("<<<<<<<\t\t4 删除指定图书信息\t>>>>>>>\n");
        printf("<<<<<<<\t\t5 检索指定图书信息\t>>>>>>>\n");
        printf("<<<<<<<\t\t6 修改指定图书信息\t>>>>>>>\n");
        printf("<<<<<<<\t\t7 移动指定图书信息\t>>>>>>>\n");
        printf("<<<<<<<\t\t8 遍历链表图书信息\t>>>>>>>\n");
        printf("<<<<<<<\t\t9 退出单向链表\t\t>>>>>>>\n");
        scanf("%d", &select_num);
        while (getchar() != '\n');// 清除缓冲区
        switch (select_num)
        {
        case 1:
            insertHead(head);
            break;
        case 2:
            insertTail(head);
            break;
        // case 3:
        //     arbitraryInsert(head);
        //     break;
        // case 4:
        //     deleteNode(head);
        //     break;
        case 5:
            findBook(head);
            break;
        // case 6:
        //     modifyNodes(head);
        //     break;
        // case 7:
        //     moveNodes(head);
        //     break;
        case 8:
            printList(head);
            break;
        case 9:
            printf("退出成功!\n");
            return 0;
            break;
        default:
            printf("无该指令，请重新输入！\n");
            break;
        }
        sleep(2);
    }
}
