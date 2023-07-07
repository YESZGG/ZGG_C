#include "dclink.h"

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
    node2 = init_node(20);
    node3 = init_node(30);
    node4 = init_node(40);
    node5 = init_node(50);
    node6 = init_node(60);

    #if 0 //插入的另一种写法
    insert_head_data(head,30);
    insert_head_data(head,20);
    insert_head_data(head,10);
    insert_tail_data(head,40);
    insert_tail_data(head,50);
    #endif

    #if 1
    //头插                  //-------------------增
    printf("[insert_head]\n");
    insert_head(head,node3);
    insert_head(head,node2);
    insert_head(head,node1);
    display_next(head);
    printf("\n");
    #endif

    #if 1
    //尾插
    printf("[insert_tail]\n");
    insert_tail(head,node4);
    insert_tail(head,node5);
    display_next(head);
    printf("\n");
    #endif

    #if 0
    //万能插入
    printf("[insert_node]\n");
    insert_node(node2,node6,node3);
    display_next(head);
    printf("\n");
    #endif    

    #if 0
    //头删                  //-------------------删
    printf("[delete_head]\n");
    delete_head(head);
    display_next(head);
    printf("\n");
    #endif

    #if 0
    //尾删                  //-------------------删
    printf("[delete_tail]\n");
    delete_tail(head);
    delete_tail(head);
    delete_tail(head);
    delete_tail(head);
    display_next(head);
    printf("\n");
    #endif

    #if 1
    //任意删                 //-------------------删
    printf("[delete_node]\n");
    delete_node(head,10);
    display_next(head);    
    printf("\n");
    #endif

    #if 1
    //前遍历
    printf("[display_prev]\n");
    display_prev(head);
    printf("\n");
    #endif

    #if 1
    //查找结点                  ---------------查
    printf("[find_node]\n");
    find_node(head,20);
    display_next(head);
    printf("\n");
    #endif    

    #if 1
    //修改结点                  ---------------改
    printf("[change_node]\n");
    change_node(head,20,200);
    display_next(head);
    printf("\n");
    #endif    

    #if 1
    //释放
    printf("[release]\n");
    release(head);
    printf("\n");   
    #endif

    return 0;
}