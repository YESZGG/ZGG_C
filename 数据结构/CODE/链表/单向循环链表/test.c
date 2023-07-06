#include <stdio.h>
#include <stdlib.h>

struct list
{
    int num;
    struct list *next;
};

struct list *create_list(int num)
{
    struct list *head = (struct list *)malloc(sizeof(struct list));
    head->num = num;
    head->next = head;
    return head;
}

void print_list(struct list *head)
{
    if (head->next == head)
    {
        printf("该链表未存储任何信息.\n");
        return;
    }
    struct list *p = head->next;
    while (p != head)
    {
        printf("%d ", p->num);
        p = p->next;
    }
    printf("\n");
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
// 更加安全 避免指针悬挂
void delete_advance(struct list *head, struct list *node)
{
    if (head->next == head)
    {
        return;
    }
    struct list *p = head, *temp = NULL;
    while (p->next != head)
    {
        if (p->next->num == node->num)
        {
            temp = p->next;
            p->next = p->next->next;
            temp->next = NULL;
            free(temp);

            return;
        }
        p = p->next;
    }
}
int main()
{
    // 创建一个单向循环链表，包含 1、2、3 三个节点
    struct list *head = create_list(0);
    struct list *node1 = create_list(1);
    struct list *node2 = create_list(2);
    struct list *node3 = create_list(3);

    // 连接链表
    head->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = head;

    // 打印链表
    printf("初始链表：");
    print_list(head);

    // 删除节点2
    delete_node(head, node2);
    printf("delete_node 后的链表：");
    print_list(head);

    // 重新连接链表
    node1->next = node2;
    node2->next = node3;
    node3->next = head;

    // 删除节点2
    delete_advance(head, node2);
    printf("delete_advance 后的链表：");
    print_list(head);


    return 0;
}
