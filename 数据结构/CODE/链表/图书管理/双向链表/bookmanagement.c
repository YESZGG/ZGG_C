#include "bookmanagement.h"

/*初始化头结点*/
struct bookLink *init_head()
{
    /*给头结点申请空间*/
    struct bookLink *head = (struct bookLink *)malloc(sizeof(struct bookLink));
    if (head == NULL)
    {
        printf("malloc head fail\n");
        return (struct bookLink *)-1;
    }

    /*给头结点赋值*/
    // 数据域赋值
    memset(head, 0, sizeof(struct bookLink));

    // 指针域赋值
    head->prev = NULL;
    head->next = NULL;

    return head;
}

/*初始化其他结点*/
struct bookLink *init_node()
{
    /*给其他结点申请空间*/
    struct bookLink *node = (struct bookLink *)malloc(sizeof(struct bookLink));
    if (node == NULL)
    {
        printf("malloc node failed.\n");
        return (struct bookLink *)-1;
    }

    // 数据域初始化
    memset(node, 0, sizeof(struct bookLink));
    // 指针域初始化
    node->prev = NULL;
    node->next = NULL;

    return node;
}

// 头插
void insertHead(struct bookLink *head)
{
    struct bookLink *new_node = init_node();
    if (new_node == (struct bookLink *)-1)
    {
        perror("new_node init failed.");
        return;
    }
    printf("--------头插--------\n");
    printf("请输入:书籍号\t书籍封面颜色\t作者名字\t图书页数\t图书名\n");
    scanf("%d %s %s %d %[^\n]", &new_node->bookno, new_node->color, new_node->authorSName, &new_node->page, new_node->title);
    while (getchar() != '\n')
        ; // 清除缓冲区

    if (head->next == NULL)
    {
        head->next = new_node;
        new_node->prev = head;
    }
    else
    {
        // 先建立新结点的连接 1线和2线
        new_node->prev = head;
        new_node->next = head->next;
        // 3、4线不能交换位置 否则导致head->next 数据丢失
        head->next->prev = new_node;
        head->next = new_node;
    }

    printf("添加成功.\n");
}

// 尾插
void insertTail(struct bookLink *head)
{
    struct bookLink *new_node = init_node();
    if (new_node == (struct bookLink *)-1)
    {
        perror("new_node init failed.");
        return;
    }
    struct bookLink *p = head;
    while (p->next != NULL)
    {
        p = p->next;
    }
    printf("--------尾插--------\n");
    printf("请输入:书籍号\t书籍封面颜色\t作者名字\t图书页数\t图书名\n");
    scanf("%d %s %s %d %[^\n]", &new_node->bookno, new_node->color, new_node->authorSName, &new_node->page, new_node->title);
    while (getchar() != '\n')
        ; // 清除缓冲区

    p->next = new_node;
    new_node->prev = p;

    printf("添加成功.\n");
}

// 删除
void deleteBook(struct bookLink *head)
{
    int del_target;
    printf("请输入要删除的图书书籍号：");
    scanf("%d", &del_target);
    while (getchar() != '\n')
        ; // 清除缓冲区

    struct bookLink *del_node = init_node();
    if (del_node == (struct bookLink *)-1)
    {
        perror("init node failed.");
        return;
    }
    del_node = head->next;
    if (del_node == NULL)
    {
        printf("未存储图书信息.\n");
        return;
    }
    // 找到要删除的结点
    while (del_node != NULL)
    {
        if (del_node->bookno == del_target)
        {
            // 判断是否为尾结点
            if (del_node->next == NULL)
            {
                del_node->prev->next = NULL;
            }
            // 判断是否为头结点
            else if (del_node->prev == head)
            {
                head->next = del_node->next;
                del_node->next->prev = head;
            }
            // 删除中间的结点
            else
            {
                del_node->prev->next = del_node->next;
                del_node->next->prev = del_node->prev;
            }
            del_node->next = NULL;
            del_node->prev = NULL;
            free(del_node);
            printf("删除成功!\n");
            return;
        }
        del_node = del_node->next;
    }

    printf("要删除的结点不存在。\n");
}

// 遍历双向链表
void printLink(struct bookLink *head)
{
    struct bookLink *p = head->next;
    if (head->next == NULL)
    {
        printf("图书管理系统未存储任何信息.\n");
        return;
    }
    int count = 1;
    printf("\t书籍号\t书籍封面颜色\t作者名字\t图书页数\t图书名\n");
    while (p != NULL)
    {
        printf("[%d]:\t%-5d\t%-10s\t%-15s\t%-5d\t\t%-20s\n", count, p->bookno, p->color, p->authorSName, p->page, p->title);
        p = p->next;
        count++;
    }

    printf("\n");
}

// 判断数组是否只包含字母字符
bool isStringArray(char arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (!isalpha(arr[i])) // 使用 isalpha 判断字符是否为字母
        {
            return false; // 包含非字母字符，返回 0
        }
    }
    return true; // 字符串只包含字母，返回 1
}

// 检索图书信息
void findBook(struct bookLink *head)
{
    char input[20];
    printf("请输入要查询的图书书籍号、封面颜色、作者、页数或书籍名:");
    scanf("%[^\n]", input);
    while (getchar() != '\n')
        ; // 清除缓冲区

    struct bookLink *p = head->next;

    int count = 1;

    if (isStringArray(input, strlen(input)))
    {
        while (p != NULL) // 遍历链表直到为空
        {
            if (strcmp(p->color, input) == 0 || strcmp(p->authorSName, input) == 0 || strcmp(p->title, input) == 0) // 检查当前节点的封面颜色
            {
                printf("\t书籍号\t书籍封面颜色\t作者名字\t图书页数\t图书名\n");
                printf("[%d]:\t%-5d\t%-10s\t%-15s\t%-5d\t\t%-20s\n", count, p->bookno, p->color, p->authorSName, p->page, p->title);
            }
            count++;
            p = p->next;
        }
    }
    else
    {
        int num = atoi(input); // 通过atoi将字符串转化成整型
        char choice;
        if (num > 1000)
        {
            while (p != NULL)
            {
                if (p->bookno == num)
                {
                    printf("\t书籍号\t书籍封面颜色\t作者名字\t图书页数\t图书名\n");
                    printf("[%d]:\t%-5d\t%-10s\t%-15s\t%-5d\t\t%-20s\n", count, p->bookno, p->color, p->authorSName, p->page, p->title);
                }
                count++;
                p = p->next; // 移动到下一个节点
            }
        }
        else
        {
            printf("查询页数高于%d的图书：(输入H) 查询页数低于%d的图书：(输入L)\n", num, num);
            scanf("%c", &choice);
            while (getchar() != '\n')
                ; // 清除缓冲区
            while (p != NULL)
            {
                if (choice == 'H' || choice == 'h')
                {
                    if (p->page > num)
                    {
                        printf("\t书籍号\t书籍封面颜色\t作者名字\t图书页数\t图书名\n");
                        printf("[%d]:\t%-5d\t%-10s\t%-15s\t%-5d\t\t%-20s\n", count, p->bookno, p->color, p->authorSName, p->page, p->title);
                    }
                    count++;
                    p = p->next; // 移动到下一个节点
                }
                else if (choice == 'L' || choice == 'l')
                {
                    if (p->page <= num && p->page > 0)
                    {
                        printf("\t书籍号\t书籍封面颜色\t作者名字\t图书页数\t图书名\n");
                        printf("[%d]:\t%-5d\t%-10s\t%-15s\t%-5d\t\t%-20s\n", count, p->bookno, p->color, p->authorSName, p->page, p->title);
                    }
                    count++;
                    p = p->next; // 移动到下一个节点
                }
                else
                {
                    printf("没有这个选项，请重新输入.\n");
                    return;
                }
            }
        }
    }
}

// 修改图书信息
void modifyBook(struct bookLink *head)
{
    struct bookLink *modify_node = init_node();
    if (modify_node == (struct bookLink *)-1)
    {
        printf("init modify_node failed.\n");
        return;
    }
    modify_node = head->next;
    int num;
    printf("请输入要修改的图书书籍号：");
    scanf("%d", &num);
    while (getchar() != '\n')
        ; // 清除缓冲区
    while (modify_node != NULL)
    {
        if (modify_node->bookno == num)
        {
            printf("\t书籍号\t书籍封面颜色\t作者名字\t图书页数\t图书名\n");
            scanf("%d %s %s %d %[^\n]", &modify_node->bookno, modify_node->color, modify_node->authorSName, &modify_node->page, modify_node->title);
            printf("修改成功.\n");
            return;
        }
        modify_node = modify_node->next;
    }
    printf("没有该%d书籍号.\n", num);
}

// 释放链表
void release(struct bookLink *head)
{
    struct bookLink *p = head->next, *temp = NULL;
    while (p != NULL)
    {
        // 1.先存起要释放的结点
        temp = p;
        // 2.建立新的连接 指向下一个结点
        p = p->next;
        // 3.释放存起来的结点
        free(temp);
    }
    // 释放头结点
    free(head);

    printf("release success.\n");
}

// 功能界面
int Function_Select(struct bookLink *head)
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
        while (getchar() != '\n')
            ; // 清除缓冲区
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
        case 4:
            deleteBook(head);
            break;
        case 5:
            findBook(head);
            break;
        case 6:
            modifyBook(head);
            break;
        // case 7:
        //     moveNodes(head);
        //     break;
        case 8:
            printLink(head);
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
