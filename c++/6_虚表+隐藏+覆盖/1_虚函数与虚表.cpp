#include <iostream>
using namespace std;

class base
{
public:
    int a;
    int b;
    virtual void show()  //分配一个虚表指针，存储在当前类的首地址
    {
        cout << "show base" << endl;
    }
     virtual void show1()  //分配一个虚表指针，存储在当前类的首地址
    {
        cout << "show1 base" << endl;
    }
     virtual void show2()  //分配一个虚表指针，存储在当前类的首地址
    {
        cout << "show2 base" << endl;
    }
};

class v_base
{
public:
    virtual void show() // 包含一个虚函数，分配一个指向虚表的指针。
    {
        cout << "show base" << endl;
    }
};

int main()
{
    base tmp;

    // &tmp ==  &tmp.a  ??? 相等的 ，空间从上往下依次分配   int arry[10];    &arry == arry[0]

    cout << "&tmp=" << &tmp << endl;
    cout << "&tmp.a=" << &tmp.a << endl;
}