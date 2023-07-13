#include <stdio.h>
#include <stdlib.h>
#include "drawtree.h"

// typedef struct tree_node // 二叉树结点F
// {
//     int data;                 // 数据域
//     struct tree_node *lchild; // 左孩子指针
//     struct tree_node *rchild; // 右孩子指针
// } treenode, *linktree;

_linktree init_tree(void)
{
    return NULL;
}

_linktree new_node(int data)
{
    _linktree new = (_linktree)malloc(sizeof(_treenode));
    if (new != NULL)
    {
        new->data = data;
        new->lchild = NULL;
        new->rchild = NULL;
    }
    return new;
}

_linktree bst_insert(_linktree root, _linktree new)
{
    if (new == NULL) // 如果新节点为空，则直接返回原树根指针
        return root;
    else if (root == NULL) // 否则，如果树的没有左右孩子，则返回此新节点作为新的树根
        return new;

    if (new->data > root->data) // 如果新节点比根大，则插入根的右孩子
    {
        root->rchild = bst_insert(root->rchild, new);
    }
    else if (new->data < root->data) // 否则如果新节点比根小，则插入左孩子
    {
        root->lchild = bst_insert(root->lchild, new);
    }
    else // 出现相等的节点则放弃
    {
        printf("%d is already exist.\n", new->data);
    }

    return root;
}

// 在以 root 为根的树中查找节点 data，返回指向节点 data 的指针
_linktree find_node(_linktree root, int data)
{
    if (root == NULL) // 如果树为空，则直接返回NULL
        return NULL;

    if (data < root->data) // 如果比根节点小，则递归地去左孩子树找
    {
        return find_node(root->lchild, data);
    }
    else if (data > root->data) // 如果比根节点大，则递归地去右孩子找
    {
        return find_node(root->lchild, data);
    }
    else // 如果不大不小，则就是要找的节点
    {
        return root;
    }
}

_linktree remove_node(_linktree root, int data)
{
    if (root == NULL) // 如果递归到root为空还找不到data，则返回NULL
        return NULL;

    // 第一步，寻找待删除的节点
    if (data < root->data) // 如果比根节点小，则递归地去左孩子树找
    {
        root->lchild = remove_node(root->lchild, data);
    }
    else if (data > root->data) // 如果比根节点大，则递归地去右孩子找
    {
        root->rchild = remove_node(root->rchild, data);
    }
    else // 如果不大不小，则就是要找的要删除的节点 这时分三种情况
    {
        _linktree temp = NULL;
        if (root->lchild != NULL) // (1)如果root有左子树，则选其最大值来替换
        {
            // 第二步，找到左子树中最大的节点
            for (temp = root->lchild; temp->rchild != NULL; temp = temp->rchild)
                ;
            // 第三步，替换
            root->data = temp->data;
            // 第四步，递归地删除多余的temp
            root->lchild = remove_node(root->lchild, temp->data);
        }
        else if (root->rchild != NULL)
        {
            // 第二步，找到右子树中最小的节点
            for (temp = root->rchild; temp->lchild != NULL; temp = temp->lchild)
                ;
            // 第三步，替换
            root->data = temp->data;
            // 第四步，递归地删除多余的temp
            root->rchild = remove_node(root->rchild, temp->data);
        }
        else //(3)如果没有孩子，则直接释放删除的根节点
        {
            // 第二步，直接删除叶子节点
            free(root);
            return NULL;
        }
    }
    return root;
}

void handler(_linktree root)
{   
    printf("%d ",root->data);
}

// 前序遍历
/* 声明了一个名为handler的函数指针，该指针可以指向一个具有_linktree参数和void返回类型的函数/*  */
void pre_travel(_linktree root,void (*handler)(_linktree))
{
    if(root == NULL)
        return ;
    handler(root);                      // 根
    pre_travel(root->lchild,handler);   // 左
    pre_travel(root->rchild,handler);   // 右
    draw(root);
}

int main(void)
{
    _linktree root = init_tree();

    int n;
    printf("请输入(输入0结束)：");
    while (1)
    {
        scanf("%d", &n); // 从键盘接收一个整数
        if (n > 0)       // 如果是整数，则插入BST中
        {
            _linktree new = new_node(n);
            root = bst_insert(root, new);
        }
        else if (n < 0) // 如果是负整数，则将其对应的绝对值删除
        {
            root = remove_node(root, -n);
        }
        if (n == 0) // 输入0，则跳出循环
        {
            break;
        }
        draw(root); // 将BST用网页的形式直观地展现出来
    }
    printf("前序遍历:\n");
    pre_travel(root,handler);
    printf("\n");
    return 0;
}
