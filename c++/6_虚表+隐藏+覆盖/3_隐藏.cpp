#include <iostream>
using namespace std;

// 基类
class base
{
public:
    void show(int v)
    {
        cout << "base::show()" << v << endl;
    }
};

// 派生类
class derived : public base
{
public:
    void show() // 隐藏基类的show方法
    {
        cout << "derived::show()" << endl;
    }
};

int main()
{
    derived d;

    // d.show(1000);

    // 派生类想调用基类的同名函数时，才会用到
    // 1.利用域操作符 显示 隐藏后接口
    d.base::show(1000);

    // 2.利用基类的引用 显示  隐藏后的接口
    base &b = d;
    b.show(1234);

    // 3.利用基类的指针  显示 隐藏后的接口
    base *p = &d;
    p->show(2333);
}


