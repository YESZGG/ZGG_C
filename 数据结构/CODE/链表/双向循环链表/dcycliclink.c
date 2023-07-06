#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct dcycliclink
{
    // 数据域
    int num;

    // 指针域
    struct dcycliclink *prev;//前驱指针
    struct dcycliclink *next;//后驱指针
};

struct dcycliclink *init_head();
struct dcycliclink *init_node();


/*初始化头结点*/
struct dcycliclink *init_head()
{
    struct dcycliclink *head = malloc(sizeof(struct dcycliclink));
    if(head == NULL)
    {
        printf("malloc head fail\n");
        return NULL;
    }

    //数据域
    memset(head,0,sizeof(struct dcycliclink));
    //指针域
    head->prev = head; //前驱指针指向自己
    head->next = head; //后驱指针指向自己

    return head;
}

/*初始化其它结点*/
struct dcycliclink *init_node()
{
    struct dcycliclink *node = malloc(sizeof(struct dcycliclink));
    if(node == NULL)
    {
        printf("malloc node fail\n");
        return NULL;
    }

    //数据域
    memset(node,0,sizeof(struct dcycliclink));

    //指针域
    node->prev = NULL; 
    node->next = NULL; 

    return node;
}

int main()
{

}