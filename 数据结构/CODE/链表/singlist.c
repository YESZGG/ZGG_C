#include <stdio.h>
#include <stdlib.h>

/*
	带头结点的单向链表
*/

// 设计一个结点模型
struct list
{
	/*数据域*/
	int num;

	/*指针域*/
	struct list *next; // 结构体指针(本身的结构体类型)
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
	if (head == NULL)
	{
		printf("malloc head fail\n");
		return NULL;
	}

	/*给头结点赋值*/
	// 数据域赋值
	head->num = 0; // 无效值

	// 指针域赋值
	head->next = NULL;

	return head;
}

/*初始化其它结点*/
struct list *init_node(int data)
{
	/*给其它结点申请空间*/
	struct list *node = malloc(sizeof(struct list));
	if (node == NULL)
	{
		printf("malloc node fail\n");
		return NULL;
	}

	// 数据域赋值
	node->num = data; // 有效值

	// 指针域赋值
	node->next = NULL;

	// 返回结点
	return node;
}

/*插入结点*/
// 头插
void insert_head(struct list *head, struct list *node)
{
	// 讨论
	// if (head->next == NULL)
	// {
	// 	//node->next = NULL; 就相当于 node->next = head->next;
	// 	head->next = node;
	// }
	// else
	// {
	// 	node->next = head->next;
	// 	head->next = node;
	// }
	// 可以把上面两个条件合二为一
	/*正确的做法*/
	// 先建立1线
	node->next = head->next;
	// 再建立2线
	head->next = node;

	/*错误的做法*/
	// 先建立2线
	// head->next = node;//如果先建立2线那么head->next直接丢失找不到了
	// 再建立1线
	// node->next = head->next;
}
// 尾插
void insert_tail(struct list *head, struct list *node)
{
	// 找到尾结点
	struct list *p = NULL;
	// 这个for循环结束的条件是p->next==NULL
	for (p = head; p->next != NULL; p = p->next)
		;
	// 代码跑到这里的时候p->next=NULL,此时p就是尾结点
	p->next = node;
}

/*头插的另一种写法*/
void insert_head_data(struct list *head, int data)
{
	// 初始化新节点
	struct list *node = malloc(sizeof(struct list));
	if (node == NULL)
	{
		printf("malloc node fail\n");
	}
	node->num = data; // 有效值
	node->next = NULL;

	// 新节点头插
	node->next = head->next;
	head->next = node;
}

/*头删*/
void delete_head(struct list *head)
{
	// 如果是空链表不删除直接返回
	// 否者head->next->next会出现段错误应为NULL->next(访问空指针会出现段错误)
	if (head->next == NULL)
		return;

	struct list *tmp = NULL;
	tmp = head->next;
	head->next = head->next->next; // NULL->next
	free(tmp);
}

/*尾删*/
void delete_tail(struct list *head, struct list *node)
{
	if (head->next == NULL)
		return;
	struct list *p = head;
	struct list *tmp = NULL;
	while (p->next->next != NULL)
	{
		p = p->next;
	}
	tmp = p->next;
	p->next = NULL;
	free(tmp);
}

/*任意删除*/
void delete_node(struct list *head, struct list *node)
{
	struct list *p = NULL, *tmp = NULL;
	// for(p=head->next;p->next!=NULL;p=p->next)//如果从head->next开始那么node1无法删除因为找不到它
	for (p = head; p->next != NULL; p = p->next)
	{
		// 1.找到要删除的结点
		if (p->next->num == node->num)
		{
			tmp = p->next;

			// 2.建立新的链接
			p->next = p->next->next;

			// 3.释放存储的结点
			free(tmp);

			// 删除尾结点会出现段错误,所以此处要加判断
			tmp->next = NULL;
			// if(p->next == NULL)
			break;
		}
	}
}

/*查找结点*/
void find_node(struct list *head, int data)
{
	// 通过遍历来找结点
	struct list *p = NULL;
	for (p = head->next; p != NULL; p = p->next)
	{
		if (p->num == data)
		{
			printf("find %d success.\n", p->num);
			return;
		}
	}
	printf("find %d failed.\n", data);
}

// 修改结点 
void change_node(struct list *head, int data, int new_data)
{
	// 通过遍历来找结点
	struct list *p = NULL;
	for (p = head->next; p != NULL; p = p->next)
	{
		if (p->num == data)
		{
			p->num = new_data;
			printf("change %d to %d success.\n", data, p->num);
			return;
		}
	}
	printf("change data %d failed.\n", data);
}
/*遍历链表*/
void display(struct list *head)
{
	struct list *p = NULL;

	for (p = head->next; p != NULL; p = p->next)
	{
		printf("%d ", p->num);
	}
	printf("\n");
}

int main()
{
	/*初始化头结点*/
	struct list *head = init_head();
	if (head == NULL)
	{
		printf("init head fail\n");
		return -1;
	}

	/*初始化其它结点*/
	struct list *node1, *node2, *node3, *node4, *node5;
	node1 = init_node(10);
	node2 = init_node(20);
	node3 = init_node(30);
	node4 = init_node(40);
	node5 = init_node(50);

	/*插入结点*/
	// 头插 //-->10-->20-->30
	printf("[insert_head]:\n");
	insert_head(head, node3);
	insert_head(head, node2);
	insert_head(head, node1);
	// 尾插
	printf("[insert_tail]:\n");
	insert_tail(head, node4);
	insert_tail(head, node5);
	display(head);

	// 头插的另一种写法
	//  insert_head_data(head,50);
	//  insert_head_data(head,60);
	//  display(head);

	// 查找				//-----------查
	printf("[find_node]:\n");
	find_node(head, 20);
	find_node(head, 60);

	// 修改				//-----------改
	printf("[change_node]:\n");
	change_node(head, 20, 200);
	display(head);

	// 头删
	printf("[delete_head]:\n"); //----------删
	// delete_head(head);
	// delete_head(head);
	display(head);

	// 尾删
	printf("[delete_tail]:\n");
	delete_tail(head, node5);
	display(head);

	// 任意删
	printf("[delete_node]:\n");
	delete_node(head, node2);

	display(head);

	return 0;
}