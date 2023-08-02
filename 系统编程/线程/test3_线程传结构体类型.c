#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

//自定义一个结构体数据类型性（写在函数外面，不要写在函数里面）
typedef struct stu
{
    char name[20];
    char sex;
    int height;
    float score;
}stu_t,*stu_p;


//子线程的返回值一定是void * 它的参数一定是 void *
void *routine(void *arg)
{
    struct stu s = *((struct stu *)arg);
    printf("%-10s %-5c %-5d %-10.2f\n",s.name,s.sex,s.height,s.score);

    return NULL;
}

void *routine1(void *arg)
{
    struct stu *s = (struct stu *)arg;
    printf("%-10s %-5c %-5d %-10.2f\n",s->name,s->sex,s->height,s->score);

    return NULL;
}

int main(int argc,char **argv)
{
    /*
        单进程代码
    */
    int ret = 0;

    //1.定义一个结构体变量
    struct stu s;
    // struct stu s = {"bling",'M',188,99.5}; //定义就初始化

    //2.初始化结构体变量
    //1.定义的时候可以一次性初始化;（过了这个村就没有机会一次性赋值）
    //2.如果不在定义的时候初始化，那么只能一个一个初始化
    strcpy(s.name,"bling");
    s.sex = 'M';
    s.height = 188;
    s.score = 99.5; 

    pthread_t tid;
    ret = pthread_create(&tid,NULL,routine,(void *)&s);
    if(ret != 0)
    {
        perror("pthread_create fail");
        return -1;
    }



    //1.定义一个结构体指针变量
    struct stu ss;
    memset(&ss,0,sizeof(ss));
    // struct stu *s1 = &ss; //一定要给指针变量申请空间---栈空间
    struct stu *s1 = malloc(sizeof(struct stu)); //使用malloc申请堆空间
    // struct stu s = {"bling",'M',188,99.5}; //定义就初始化

    //2.初始化结构体变量
    //1.定义的时候可以一次性初始化;（过了这个村就没有机会一次性赋值）
    //2.如果不在定义的时候初始化，那么只能一个一个初始化
    strcpy(s1->name,"bling1");
    s1->sex = 'W';
    s1->height = 190;
    s1->score = 99.8; 

    pthread_t tid1;
    ret = pthread_create(&tid1,NULL,routine1,(void *)s1);
    if(ret != 0)
    {
        perror("pthread_create fail");
        return -1;
    }


    //不要让主线程结束，否者子线程还没有来得及工作，整个进程已经结束啦
    // while(1);
    pause(); //挂起进程

    //malloc之后一定要free
    free(s1);

    return 0;
}