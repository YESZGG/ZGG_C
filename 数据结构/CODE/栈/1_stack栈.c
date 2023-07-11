#include <stdio.h>
#include <stdlib.h>


/*
栈--->单向非循环链表
*/

//设计栈里面结点的结构体
struct node
{
    int num;
    struct node *next;
};

//管理栈的结构体
struct stack
{
    struct node *top;//指向栈顶元素的指针
    int size; //栈里面结点的个数
};

struct stack *init_stack()
{
    //给栈申请堆空间
    struct stack *s = malloc(sizeof(struct stack));
    if(s == NULL)
    {
        printf("malloc s fail\n");
        return NULL;
    }

    //给栈赋值
    s->size = 0;
    s->top = NULL;

    return s;
}

/*压栈-->头插*/
void push_stack(struct stack *s,int data)
{
    //初始化新节点
    struct node *new = malloc(sizeof(struct node));
    if(new == NULL)
    {
        printf("malloc new fail\n");
        return ;        
    }
    //给新节点赋值
    new->num = data;
    new->next = NULL;

    //将新节点头插入到链表中
    
    //空链表(这两种情况可以合二为一成非空链表的代码)
    // if(s->top == NULL)
    // {
    //     new->next = NULL;
    //     s->top = new;
    // }
    //非空链表
    new->next= s->top;//先建立1线
    s->top = new;//再建立2线
    
    //栈里面结点的个数+1
    s->size++;    
}

/*弹栈--头删*/
void pop_stack(struct stack *s)
{
    //空链表
    if(s->top == NULL)
    {
        return;
    }

    //非空链表
    struct node *tmp = NULL;
    //1.先存储要删除的结点
    tmp = s->top;
    //2.建立新的连接
    s->top = s->top->next; //如果是空链表这句话会段错误
    //3.释放存储的结点
    free(tmp);
    //4.size个数要减一
    s->size--;
}

/*遍历栈*/
void display(struct stack *s)
{
    if(s->top == NULL)
        return;

    struct node *p =NULL;
    for(p=s->top;p!=NULL;p=p->next)
    {
        printf("%d<-",p->num);
    }
    printf("\n");
}

/*销毁栈(释放栈)*/
void destroy(struct stack *s)
{
    struct node *p=NULL,*tmp=NULL;
    //先销毁其它结点
    for(p=s->top;p!=NULL;)
    {
        tmp = p;
        p=p->next;
        free(tmp);
    }

    //再销毁s
    free(s);
}

int main()
{
    //初始化栈
    struct stack *s = init_stack();
    if(s == NULL)
    {
        printf("init stack fail\n");
        return -1;
    } 

    //压栈
    push_stack(s,30);
    push_stack(s,20);
    push_stack(s,10);
    display(s);

    //弹栈
    // pop_stack(s);
    // pop_stack(s);
    // pop_stack(s);
    // pop_stack(s);

    //遍历栈
    display(s);

    //销毁栈(释放栈)
    destroy(s);

    return 0;
}