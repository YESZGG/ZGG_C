#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 栈中结点的结构体定义
struct stack_node
{
    int num;
    struct stack_node *next;
};

// 栈的结构体定义
struct stack
{
    // 栈的结点个数
    int size;
    // 指针域---指向栈顶
    struct stack_node *top;
};

struct stack *init_stack()
{
    struct stack *stack = (struct stack *)malloc(sizeof(struct stack));
    if (stack == NULL)
    {
        perror("malloc stack failed.");
        return NULL;
    }
    bzero(stack, sizeof(struct stack));

    return stack;
}

// 入栈
void push(struct stack *stack, int num)
{
    struct stack_node *newnode = (struct stack_node *)malloc(sizeof(struct stack_node));
    if (newnode == NULL)
    {
        perror("malloc newnode failed.");
        return;
    }
    // 给新结点赋值
    newnode->num = num;
    newnode->next = NULL;

    // 栈空跟栈不为空  入栈一样
    // 先指向原来的头结点
    newnode->next = stack->top;
    // 再把栈顶指针指向新来的结点
    stack->top = newnode;
    // 栈的结点个数增加
    stack->size++;
}

// 弹栈
void pop(struct stack *stack)
{
    if (stack->top == NULL)
    {
        printf("栈为空.\n");
        return;
    }
    struct stack_node *temp = stack->top;
    // 指向栈原来栈顶的下一个结点
    stack->top = stack->top->next;
    // 弹出栈的元素
    printf("Popped element:%d\n", temp->num);
    temp->next = NULL;
    // 释放原来的栈顶
    free(temp);
    stack->size--;
}

// 遍历
void display(struct stack *stack)
{
    if (stack->top == NULL)
    {
        printf("栈为空.\n");
        return;
    }
    struct stack_node *p = stack->top;
    printf("Stack content:\n");
    while (p != NULL)
    {
        printf("%d\n", p->num);
        p = p->next;
    }
}

// 销毁栈
void destroyStack(struct stack *stack)
{
    struct stack_node *p = stack->top, *temp = NULL;
    while (p != NULL)
    {
        // 先存储要删除的结点
        temp = p;
        // 指向新的结点
        p = p->next;
        // 释放原来的结点
        free(temp);
    }
    free(stack);
    printf("Destroy Stack success.\n");
}

int main()
{
    struct stack *stack = init_stack();
    if (stack == NULL)
    {
        perror("init stack failed.");
        return -1;
    }

    // 入栈
    // push(stack, 10);
    // push(stack, 20);
    // push(stack, 30);
    int input,i = 6;
    printf("Please enter the value for stacking：");
    while (i)
    {
        scanf("%d",&input);
        // while(getchar()!= '\n'); 用了这个要换行
        if(i == 1)
        {
            while(getchar() != '\n');
        }
        push(stack,input);
        i--;
    }
    
    display(stack);
    // 出栈
    while (stack->size != 0)
    {
        pop(stack);
    }

    // display(stack);
    destroyStack(stack);

    return 0;
}
