#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
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

struct list *init_head();
struct list *init_node();
void insertHeadNode(struct list *head);     // 头插法
void insertTailNode(struct list *head);     // 尾插法
void printList(struct list *head);          // 打印数据
void traverseLinkedList(struct list *head); // 查找
void deleteNode(struct list *head);         // 删除
void modifyNodes(struct list *head);        // 修改
void moveNodes(struct list *head);          // 移动
void freeList(struct list *head);           // 释放

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
struct list *init_node()
{
    struct list *node = (struct list *)malloc(sizeof(struct list));
    if (node == NULL)
    {
        printf("malloc node failed.\n");
        return (struct list *)-1;
    }
    // 数据域赋值
    // node->stuno = stuno;
    // strcpy(node->name, name);
    // node->sex = sex;
    // node->height = height;
    // node->score = score;
    memset(node, 0, sizeof(struct list));
    // 指针域赋值
    node->next = NULL;
    // 返回节点
    return node;
}
// 在链表头插入新节点
void insertHeadNode(struct list *head)
{
    printf("----------头插----------\n");
    int stuno, height, score;
    char name[20];
    char sex;
    struct list *node = init_node();
    if (node == (struct list *)-1)
    {
        printf("creat new node failed.\n");
    }
    printf("请输入学生信息：学号 姓名 性别 身高 成绩\n");
    scanf("%d %s %c %d %d", &stuno, name, &sex, &height, &score);
    // 判断学号是否重复 学号为主键 不能相同
    struct list *p = head->next;
    while (p != NULL)
    {
        if (p->stuno == stuno)
        {
            printf("已有该学号的学生，若想添加新的学生，请重新输入学号.\n");
            return;
        }
        p = p->next;
    }
    // 赋值
    node->stuno = stuno;
    strcpy(node->name, name);
    node->sex = sex;
    node->height = height;
    node->score = score;
    // 头插
    node->next = head->next;
    head->next = node;
    printf("添加成功.\n");
}

// 在链表尾插入新节点
void insertTailNode(struct list *head)
{
    printf("----------尾插----------\n");
    struct list *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    int stuno, height, score;
    char name[20];
    char sex;
    struct list *node = init_node();
    if (node == (struct list *)-1)
    {
        printf("creat new node failed.\n");
    }
    printf("请输入学生信息：学号 姓名 性别 身高 成绩\n");
    scanf("%d %s %c %d %d", &stuno, name, &sex, &height, &score);
    // 判断学号是否重复 学号为主键 不能相同
    struct list *p = head->next;
    while (p != NULL)
    {
        if (p->stuno == stuno)
        {
            printf("已有该学号的学生，若想添加新的学生，请重新输入学号.\n");
            return;
        }
        p = p->next;
    }
    // 赋值
    node->stuno = stuno;
    strcpy(node->name, name);
    node->sex = sex;
    node->height = height;
    node->score = score;

    current->next = node;
    printf("添加成功.\n");
}

// 查找
void traverseLinkedList(struct list *head)
{
    int target;
    printf("----------查找----------\n");
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
    printf("----------打印----------\n");
    struct list *current = head->next;
    if (current == NULL)
    {
        printf("该链表未存储任何信息.\n");
    }
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

// 删除
void deleteNode(struct list *head)
{
    printf("----------删除----------\n");
    struct list *current = head;
    if (current->next == NULL)
    {
        printf("未存储任何信息.\n");
        return;
    }
    int deletestuNo;
    printf("请输入要删除的学生的学号：");
    scanf("%d", &deletestuNo);
    while (current->next != NULL)
    {
        if (current->next->stuno == deletestuNo)
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

// 修改节点
void modifyNodes(struct list *head)
{
    printf("----------修改----------\n");
    if (head->next == NULL)
    {
        printf("该链表未存储任何信息.\n");
        return;
    }
    int stuno;
    printf("请输入要修改的学生学号：");
    scanf("%d", &stuno);

    struct list *p = head->next;
    while (p != NULL)
    {
        if (p->stuno == stuno)
        {
            printf("请输入学生新信息:学号 姓名 性别 身高 成绩\n");
            scanf("%d %s %c %d %d", &p->stuno, p->name, &p->sex, &p->height, &p->score);
            printf("学生信息已修改.\n");
            return;
        }
        p = p->next;
    }
    printf("没有找到该学生\n");
}

// 移动节点到指定位置
void moveNodes(struct list *head)
{
    printf("----------移动节点到指定位置----------\n");
    printf("请输入要移动的节点：");
    int position; // 移动位置
    scanf("%d", &position);
    printf("请输入要移动到第几个节点：");
    int targetPosition; // 目标位置
    scanf("%d", &targetPosition);

    struct list *current = head->next;
    struct list *previous = NULL;

    int count = 1;

    // 找到要移动的节点
    while (current != NULL && count < position)
    {
        previous = current;
        current = current->next;
        count++;
    }
    // 如果找到了要移动的节点
    if (current != NULL)
    {
        // 从链表中删除要移动的节点
        if (previous != NULL)
        {
            previous->next = current->next;
        }
        else
        {
            head->next = current->next;
        }

        // 在目标位置之前插入节点
        if (targetPosition == 1)
        {
            current->next = head->next;
            head->next = current;
        }
        // 在目标位置之后插入节点
        else if (targetPosition > 1)
        {
            struct list *target = head->next;
            count = 1;

            // 找到目标位置的节点
            while (target != NULL && count < targetPosition - 1)
            {
                target = target->next;
                count++;
            }

            if (target != NULL)
            {
                current->next = target->next;
                target->next = current;
            }
            else
            {
                printf("无效的目标位置。\n");
                // 将节点重新插入到原来的位置
                if (previous != NULL)
                {
                    previous->next = current;
                }
                else
                {
                    head->next = current;
                }
            }
        }
        else
        {
            printf("无效的目标位置。\n");
            // 将节点重新插入到原来的位置
            if (previous != NULL)
            {
                previous->next = current;
            }
            else
            {
                head->next = current;
            }
        }

        printf("移动成功。\n");
    }
    else
    {
        printf("无效的位置。\n");
    }
}

// 任意插入节点
void arbitraryInsert(struct list *head)
{
    printf("----------任意插入节点----------\n");
    printf("请输入要插入的位置：");
    int position;
    scanf("%d", &position);

    struct list *current = head;
    struct list *previous = NULL;

    // 记录链表节点的位置
    int count = 0;
    // 找到要插入的位置
    while (current != NULL && count < position)
    {
        previous = current;
        current = current->next;
        count++;
    }

    // 创建新的节点
    struct list *new_node = (struct list *)malloc(sizeof(struct list));
    if (new_node == NULL)
    {
        printf("malloc new node failed.\n");
        return;
    }

    // 插入到链表
    printf("请输入要插入的学生信息：\n");
    scanf("%d %s %c %d %d", &new_node->stuno, new_node->name, &new_node->sex, &new_node->height, &new_node->score);
    if (previous != NULL)
    {
        new_node->next = previous->next;
        previous->next = new_node;
    }
    else
    {
        new_node = head->next;
        head->next = new_node;
    }
    printf("插入成功.\n");
}

// 释放链表内存
void freeList(struct list *head)
{
    struct list *current = head;
    // 从头节点开始释放
    while (current != NULL)
    {
        struct list *temp = current; // 先存放要释放的节点
        current = current->next;
        free(temp); // 释放节点
    }
}

// 功能界面
int Function_Select(struct list *head)
{
    int select_num;
    while (1)
    {
        system("clear");
        printf("<<<<<<<\t\t1 头插添加数据节点\t>>>>>>>\n");
        printf("<<<<<<<\t\t2 尾插添加数据节点\t>>>>>>>\n");
        printf("<<<<<<<\t\t3 指定位置数据节点\t>>>>>>>\n");
        printf("<<<<<<<\t\t4 删除指定数据节点\t>>>>>>>\n");
        printf("<<<<<<<\t\t5 检索指定数据节点\t>>>>>>>\n");
        printf("<<<<<<<\t\t6 修改指定数据节点\t>>>>>>>\n");
        printf("<<<<<<<\t\t7 移动指定数据节点\t>>>>>>>\n");
        printf("<<<<<<<\t\t8 遍历链表数据节点\t>>>>>>>\n");
        printf("<<<<<<<\t\t9 退出单向链表\t\t>>>>>>>\n");
        scanf("%d", &select_num);
        while (getchar() != '\n')
            ;
        switch (select_num)
        {
        case 1:
            insertHeadNode(head);
            break;
        case 2:
            insertTailNode(head);
            break;
        case 3:
            arbitraryInsert(head);
            break;
        case 4:
            deleteNode(head);
            break;
        case 5:
            traverseLinkedList(head);
            break;
        case 6:
            modifyNodes(head);
            break;
        case 7:
            moveNodes(head);
            break;
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
int main()
{
    struct list *head = init_head(); // 头节点初始化
    if (head == NULL)
    {
        printf("init head fail\n"); // 头节点初始化失败
        return -1;
    }
    Function_Select(head); // 功能界面

    // 释放链表内存
    freeList(head);
    return 0;
}