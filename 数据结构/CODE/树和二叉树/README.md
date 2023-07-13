首先是头文件： head4tree.h、head4queue.h、commonheader.h、drawtree.h


在BST.C中
    draw(root); // 将BST用网页的形式直观地展现出来
使用了draw()函数，可以将BST 形象地画在一个网页上
该函数的头文件为drawtree.h

typedef struct _tree_node
{
	int data;
	struct _tree_node *lchild;
	struct _tree_node *rchild;

#ifdef AVL
	int height;
#endif

#ifdef RB
	struct _tree_node *parent;
	int color;
#endif
}_treenode, *_linktree;

其中已经定义了二叉树的结构体,只需创建该结构体类型的节点即可调用。
 _linktree root = init_tree();