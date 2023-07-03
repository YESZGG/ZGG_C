#include <stdio.h>
#include <stdlib.h>

/*
	带头结点的单向链表
*/


//设计一个结点模型
struct list
{
	/*数据域*/
	int num;
	
	/*指针域*/
	struct list *next; //结构体指针(本身的结构体类型)
};


// typedef struct list
// {
// 	/*数据域*/
// 	int num;
	
// 	/*指针域*/
// 	struct list *next; //结构体指针(本身的结构体类型)
// }list_t,*list_P;
// //给结构体类型struct list取了一个别名list_t
// //给结构体指针类型struct list *取了一个别名list_p


/*初始化头结点*/
struct list *init_head()
{
	/*给头结点申请空间*/
	struct list *head = malloc(sizeof(struct list));
	if(head == NULL)
	{
		printf("malloc head fail\n");
		return NULL;
	}
	
	/*给头结点赋值*/
	//数据域赋值
	head->num = 0; //无效值
	
	//指针域赋值
	head->next = NULL;
	
	return head;
}

/*初始化其它结点*/
struct list *init_node(int data)
{
	/*给其它结点申请空间*/
	struct list *node = malloc(sizeof(struct list));
	if(node == NULL)
	{
		printf("malloc node fail\n");
		return NULL;
	}
	
	//数据域赋值
	node->num = data; //有效值
	
	//指针域赋值
	node->next = NULL;
	
	//返回结点
	return node;
}

/*插入结点*/ 
//头插 
void insert_head(struct list *head,struct list *node)
{
	/*正确的做法*/
	//先建立1线
	node->next = head->next;
	//再建立2线
	head->next = node;
	
	
	/*错误的做法*/
	//先建立2线
	//head->next = node;//如果先建立2线那么head->next直接丢失找不到了	
	//再建立1线
	//node->next = head->next;	

}

/*遍历链表*/
void display(struct list *head)
{
    struct list *p = NULL;

    for(p = head->next; p!=NULL;p=p->next)
    {
        printf("%d ",p->num);
    }
    printf("\n");
}
int main()
{
	/*初始化头结点*/
	struct list *head = init_head();
	if(head == NULL)
	{
		printf("init head fail\n");
		return -1;
	}
	
	/*初始化其它结点*/
	struct list *node1,*node2,*node3;
	node1 = init_node(10);
	node2 = init_node(20);
	node3 = init_node(30);
	
	/*插入结点*/ 
	//头插 //-->10-->20-->30
	insert_head(head,node3);
	insert_head(head,node2);
	insert_head(head,node1);

	display(head);
    return 0;
}