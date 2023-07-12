#include <stdio.h>
#include <stdlib.h>

/** 二叉树增删改查 **/

// 二叉树节点
struct node
{
	int data;			 // 数据域
	struct node *lchild; // 指向左孩子(left child)
	struct node *rchild; // 指向右孩子(right child)
};

// 队列节点
struct q_node
{
	int data;			 // 队列数据域
	struct q_node *next; // 队列指针域
};

// 队列管理结构体
struct queue
{
	struct q_node *head; // 指向队头
	struct q_node *tail; // 指向队尾
	int size;			 // 统计元素个数
};

struct node *init_new_node(int num)
{
	// 1. 为新节点申请空间。
	struct node *new = malloc(sizeof(struct node));
	if (new == NULL)
		printf("malloc new error!\n");

	// 2. 为新节点赋值。
	new->data = num;
	new->lchild = NULL;
	new->rchild = NULL;

	return new;
}

struct node *insert_new_node(struct node *new, struct node *root)
{
	// 1. 如果这棵树连根节点都没有
	if (root == NULL)
	{
		return new; // 那么这个新插入的节点就作为根节点。
	}

	// 2. 如果这棵树是正常的，则正常插入节点。
	if (new->data > root->data) // 则节点应该放在根节点的右边
	{
		root->rchild = insert_new_node(new, root->rchild);
	}
	else if (new->data < root->data) // 则节点应该放在根节点的左边
	{
		root->lchild = insert_new_node(new, root->lchild);
	}
	else
	{
		printf(" %d node already exists!\n", new->data);
	}
	return root;
}

struct node *find_node(struct node *root, int num)
{
	if (root == NULL) // 找到底，都没有找到你。
	{
		return NULL;
	}

	if (num < root->data)
	{
		return find_node(root->lchild, num);
	}
	else if (num > root->data)
	{
		return find_node(root->rchild, num);
	}
	else
	{ // 如果不大不小，那么这个root就是你想要的人了。
		return root;
	}
}

// 前序遍历
void show_node_first(struct node *root)
{
	if (root == NULL)
		return;

	printf("%d ", root->data);	   // 根
	show_node_first(root->lchild); // 左
	show_node_first(root->rchild); // 右
	return;
}

// 中序遍历
void show_node_middle(struct node *root)
{
	if (root == NULL)
		return;

	show_node_middle(root->lchild); // 左
	printf("%d ", root->data);		// 根
	show_node_middle(root->rchild); // 右
	return;
}

// 后序遍历
void show_node_last(struct node *root)
{
	if (root == NULL)
		return;

	show_node_last(root->lchild); // 左
	show_node_last(root->rchild); // 右
	printf("%d ", root->data);	  // 根
	return;
}

struct queue *init_queue()
{
	// 1. 为队列管理结构体申请空间。
	struct queue *q = malloc(sizeof(struct queue));
	if (q == NULL)
		printf("malloc q error!\n");

	// 2. 为管理结构体赋值。
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;

	return q;
}

void in_queue(struct queue *q, int num)
{
	// 1. 为新节点申请空间。
	struct q_node *new = malloc(sizeof(struct q_node));
	if (new == NULL)
		printf("malloc new error!\n");

	// 2. 为新节点赋值。
	new->data = num;
	new->next = NULL;

	// 3. 分情况讨论。
	if (q->size == 0)
	{
		q->head = new;
		q->tail = new;
	}
	else
	{
		q->tail->next = new;
		q->tail = new;
	}

	// 4. 元素个数+1
	q->size++;

	return;
}

int out_queue(struct queue *q)
{
	// 1. 先判断一下是否为空队。
	if (q->size == 0)
		return -1; // 出队失败

	// 2. 让tmp指向那个将要出队的节点。
	struct q_node *tmp = q->head;
	int ret = tmp->data;

	// 3. 分情况讨论。
	if (q->size == 1)
	{
		q->head = NULL;
		q->tail = NULL;
	}
	else
	{
		q->head = q->head->next;
	}

	// 3. 释放tmp
	free(tmp);

	// 4. 元素个数-1
	q->size--;

	// 5. 返回ret
	return ret;
}

void show_node_level(struct node *root)
{
	// 1. 判断一下到底了没有？
	if (root == NULL)
		return;

	// 2. 初始化一条空队。
	struct queue *q = NULL;
	q = init_queue();

	// 3. 将根节点入队。
	in_queue(q, root->data);

	int ret;
	struct node *tmp = NULL;
	while (1)
	{
		// 4. 出队
		// 如果出队失败，则结束程序。
		// 如果出队成功，则打印该节点。
		ret = out_queue(q);
		if (ret == -1) // 出队失败
		{
			break;
		}
		else
		{
			printf("%d ", ret);
		}

		// 5. 在二叉树中寻找刚刚出队的那个节点。
		tmp = find_node(root, ret);

		// 6. 判断一下刚刚出队的那个节点有没有左孩子，如果有，则将左孩子入队。
		if (tmp->lchild != NULL) // 说明是有左孩子。
			in_queue(q, tmp->lchild->data);

		// 7. 判断一下刚刚出队的那个节点有没有右孩子，如果有，则将右孩子入队。
		if (tmp->rchild != NULL) // 说明是有右孩子。
			in_queue(q, tmp->rchild->data);
	}
	printf("\n");
	// 8. 释放队列管理结构体空间。
	free(q);
	return;
}

struct node *delete_node(struct node *root, int num)
{
	// 1. 找到底都没有找到该节点，则返回NULL。
	if (root == NULL)
		return NULL;

	// 2. 寻找需要删除的节点。
	if (num < root->data)
	{
		root->lchild = delete_node(root->lchild, num);
	}
	else if (num > root->data)
	{
		root->rchild = delete_node(root->rchild, num);
	}
	else
	{ // 不大不小，现在的root就是你需要删除的节点
		struct node *tmp = NULL;
		if (root->lchild != NULL) // 不为NULL,说明有左子树。
		{
			// 3. 寻找左子树中的最大值。
			for (tmp = root->lchild; tmp->rchild != NULL; tmp = tmp->rchild)
				;
			// 从循环中出来时，tmp就是指向左子树中的最大值

			// 4. 将tmp指向的数据赋值给需要删除的节点。
			root->data = tmp->data;

			// 5. 递归删除这个tmp
			root->lchild = delete_node(root->lchild, tmp->data);
		}
		else if (root->rchild != NULL) // 不为NULL，说明有右子树
		{
			// 3. 寻找右子树中的最小值。
			for (tmp = root->rchild; tmp->lchild != NULL; tmp = tmp->lchild)
				;
			// 从循环中出来时，tmp就是指向右子树中的最小值

			// 4. 将tmp指向的数据赋值给需要删除的节点。
			root->data = tmp->data;

			// 5. 递归删除这个tmp
			root->rchild = delete_node(root->rchild, tmp->data);
		}
		else
		{ // 既没有左子树，又没有右子树，那么就直接删除释放。
			free(root);
			return NULL; // 最后的节点释放了，需要返回一个NULL给最后一个节点的左指针/右指针。
		}
	}

	return root;
}

int main(int argc, char *argv[])
{
	// 1. 初始化一棵二叉树的根节点。
	struct node *root = NULL;
	root = init_new_node(30);

	// 2. 插入节点。
	struct node *new = NULL;
	new = init_new_node(20);
	insert_new_node(new, root);

	new = init_new_node(40);
	insert_new_node(new, root);

	new = init_new_node(15);
	insert_new_node(new, root);

	new = init_new_node(24);
	insert_new_node(new, root);

	new = init_new_node(22);
	insert_new_node(new, root);

	new = init_new_node(28);
	insert_new_node(new, root);

	new = init_new_node(35);
	insert_new_node(new, root);

	new = init_new_node(50);
	insert_new_node(new, root);

	new = init_new_node(23);
	insert_new_node(new, root);

	// 3. 搜索二叉树中的节点。
	//  struct node *tmp = NULL;
	//  tmp = find_node(root,23);
	//  if(tmp != NULL)  //说明已经找到了
	//  {
	//  	printf("find the node:%d\n",tmp->data);
	//  }
	//  else{
	//  	printf("node not exists!\n");
	//  }

	// 4. 遍历二叉树。
	printf("show_node_first:\n");
	show_node_first(root); // 先序遍历
	printf("\n");
	printf("show_node_middle:\n");
	show_node_middle(root); // 中序遍历
	printf("\n");
	printf("show_node_last:\n");
	show_node_last(root); // 后序遍历
	printf("\n");
	printf("show_node_level:\n");
	show_node_level(root); // 按层遍历

	// 5. 删除节点。
	delete_node(root, 24);
	printf("show_node_first:\n");
	show_node_first(root); // 先序遍历
	printf("\n");
	printf("---------------------\n");
	// show_node_level(root);         //按层遍历

	return 0;
}