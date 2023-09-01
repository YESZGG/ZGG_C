#include <stdio.h>

/*
    C语言,结构体里面不能写函数,但是可以通过函数指针访问函数
*/

// 女朋友
struct GirlFriend
{
    // 属性
    char name[20];
    int age;
    int money;

    // 行为
    void (*eat)(struct GirlFriend *p);
    int (*sleep)(void);
    void (*play)(int);
};

void eat(struct GirlFriend *p)
{
    printf("void eat(void) %s\n",p->name);
}

int sleep(void)
{
    printf("int sleep(void)\n");
}

void play(int a)
{
    printf("void play(int)\n");
}

int main()
{
    //函数名就是指针
    struct GirlFriend g1 = {"ahua",18,520,eat,sleep,play};
    g1.eat(&g1);
    g1.sleep();

    struct GirlFriend g2 = {"axia",18,520,eat,sleep,play};
    printf("%s\n",g2.name);

    return 0;
}