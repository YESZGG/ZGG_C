#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "linkedlist.h"

struct Node *init_head()
{
    struct Node *head = (Node *)malloc(sizeof(struct Node));
    if (head == NULL)
    {
        perror("malloc head fail.");
        return (struct Node *)-1;
    }
    strcpy(head->filename, "\0"); // 无效值
    head->type = '\0';
    memset(head, 0, sizeof(struct Node));
    head->previous = head->next = head;

    return head;
}

struct Node *init_node()
{
    struct Node *node = (Node *)malloc(sizeof(struct Node));
    if (node == NULL)
    {
        printf("malloc node fail\n");
        return (struct Node *)-1;
    }

    memset(node, 0, sizeof(struct Node));
    node->previous = NULL;
    node->next = NULL;

    return node;
}

// void initLinkedList(Node *head)
// {
//     addNode(head, "1.bmp");
//     addNode(head, "2.jpg");
//     addNode(head, "3.bmp");
//     addNode(head, "4.jpg");
//     addNode(head, "5.bmp");
//     addNode(head, "6.jpg");
// }

// void addNode(struct Node *head, char *filename)
// {
//     Node *newNode = init_node();
//     strcpy(newNode->filename, filename);

//     newNode->next = head;
//     newNode->previous = head->previous;
//     head->previous->next = newNode;
//     head->previous = newNode;
// }

void printLink(struct Node *head)
{
    printf("<<<<<<<\t\t 遍历 \t\t>>>>>>>\n");
    struct Node *p = head->next;
    while (p != head)
    {
        printf("%s ", p->filename);
        p = p->next;
    }
    printf("\n");
}

void freeLinkedList(Node *head)
{
    if (head == NULL)
    {
        return;
    }

    Node *current = head->next;
    while (current != head)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    free(head);
    head = NULL;
}

void tail_insert(Node *head, char *filename, int num, char type)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        perror("Failed to create a new Node.");
        return;
    }

    strcpy(newNode->filename, filename);
    newNode->num = num;
    newNode->type = type;
    newNode->next = NULL;
    newNode->previous = NULL;

    newNode->next = head;
    newNode->previous = head->previous;
    head->previous->next = newNode;
    head->previous = newNode;
}

int read_path_list(Node *head)
{
    // 1. 打开当前目录
    DIR *dp = opendir("./image");
    if (dp == NULL)
    {
        perror("open dir fail");
        return -1;
    }
    // 跳转到image
    chdir("./image");
    struct dirent *ep = NULL; // 定义目录流指针

    char path[30] = {0};
    int num = 0;
    char type = 0;

    // 读取文件
    while (1)
    {
        // 2. 读取文件名
        ep = readdir(dp);
        // 退出条件
        if (ep == NULL)
            break;
        // 跳过“.” 和 “..” 隐藏文件
        if (ep->d_name[0] == '.' || strcmp(ep->d_name, "..") == 0)
        {
            continue;
        }
        // 拼接文件路径名
        sprintf(path, "./image/%s", ep->d_name);

        // 文件类型
        /* char *strrchr(const char *str, int c) 在参数 str 所指向的字符串中搜索最后一次出现字符 c（一个无符号字符）的位置。 */
        char *p = strrchr(ep->d_name, '.');
        if (p != NULL)
        {
            if (strcmp(p, ".bmp") == 0)
                type = 'b'; // bmp
            else if (strcmp(p, ".jpg") == 0)
                type = 'j'; // jpg
            else
                continue; // 跳过其他类型文件
        }
        else
        {
            continue; // Skip files without extensions
        }

        // 每找到一张bmp和jpg就++
        ++num;

        // 尾插
        tail_insert(head, path, num, type);
    }

    // 关闭目录流指针
    closedir(dp);
    chdir("..");
    return 0;
}