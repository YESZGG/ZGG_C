#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

class GirlFriend
{
public: // 共有权限  类的外部可以进行 访问  类的内部也可以进行访问
    // 行为   -对外的接口
    //  void setName(const char*n = "宝贝")
    void setName(const char *n)
    {
        memset(name, 0, sizeof(name));
        strcpy(name, n);
    }
    char *getName()
    {
        return name;
    }
    void setAge(int a)
    { // 可写
        if (a < 0 || a > 150)
        {
            cout << "数据错误" << endl;
        }
        age = a;
    }
    int getAge()
    { // 只读
        return age;
    }

    void eat()
    {
        printf("[%s] 我正在吃饭....\n", name);
    }
    // void player(){
    //     printf("[%s]别说了，上号...\n",name);
    // }

    // 如果只申明不定义：报错
    //  undefined reference to `GirlFriend::player()'
    void player(); // 申明

    void show() // 显示所有的属性信息
    {
    }

private: // 私有权限   类的外部不能访问
    // 属性   将属性设置为 私有权限的好处： 1、可以自己控制 属性的读写权限 ，达到数据的安全性 2、还可以检查数据的正确性
    char name[256];
    int age;
    int money;
};

void GirlFriend::player()
{
    printf("[%s]别说了，上号...\n", name);
}

int main()
{
    // 静态分配内存
    // 实例化一个对象(和C语言里面里面定义一个变量一个意思)
    GirlFriend g1;
    g1.setAge(18);
    cout << g1.getAge() << endl;

    g1.setName("小可爱");
    // g1.setName();
    cout << g1.getName() << endl;

    // 动态分配内存
    GirlFriend *g2 = new GirlFriend;
    g2->setName("阿花");
    cout << g2->getName() << endl;
    g2->player();
    delete g2;

    // 设计类的思想：通过共有的方法访问私有的属性
    // cout<<g1.age<<endl;  //error
    return 0;
}