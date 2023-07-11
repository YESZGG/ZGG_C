#include <stdio.h>

#define MAX_SIZE 100

struct Stack
{
    int data[MAX_SIZE];
    int top;
};

void initStack(struct Stack *stack)
{
    stack->top = -1;
}

/*
比较栈顶指针 top 是否等于 MAX_SIZE - 1 来判断栈是否已满。
如果 top 等于 MAX_SIZE - 1，则说明栈已经达到当前容量的最大限制，返回非零值表示栈已满；
否则返回0，表示栈未满。
*/
int isFull(struct Stack *stack)
{
    return stack->top == MAX_SIZE - 1;
}

int isEmpty(struct Stack *stack)
{
    return stack->top == -1;
}

// 入栈
void push(struct Stack *stack, int item)
{
    if (isFull(stack))
    {
        printf("Stack Overflow\n");
        return;
    }
    stack->data[++stack->top] = item;
}

// 出栈
int pop(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack Underflow\n");
        return -1; // 返回一个默认值表示栈为空
    }
    return stack->data[stack->top--];
}

// 显示
void display(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack content:\n");
    for (int i = stack->top; i >= 0; i--)
    {
        printf("%d\n", stack->data[i]);
    }
}

int main()
{
    struct Stack stack;
    initStack(&stack);

    push(&stack, 10); // 压入元素到栈中
    push(&stack, 20);
    push(&stack, 30);

    display(&stack); // 显示栈的存储内容

    int popped = pop(&stack); // 弹出栈顶元素
    printf("Popped element: %d\n", popped);

    display(&stack); // 再次显示栈的存储内容

    return 0;
}