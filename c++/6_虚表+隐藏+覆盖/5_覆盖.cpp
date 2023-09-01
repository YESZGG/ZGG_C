#include <iostream>
using namespace std;

class base
{
public:
    virtual void show() // 虚函数
    {
        cout << "base::show()" << endl;
    }

    void show(int value)
    {
        cout << "base::show(int)" << value << endl;
    }
};

class xbase : public base
{
public:
    void show() // 覆盖基类的虚函数
    {
        cout << "xbase::show()" << endl;
    }
};

int main()
{

    xbase x;
    x.show(); // 调用派生类

    base *p = &x;
    p->show(); // 调用基类 show函数 -> 被派生类的show覆盖

    base &q = x;
    q.show(); // 调用基类的 show 函数-> 被派生类的show覆盖

    // 调用基类的 show 函数 -> 隐藏
    p->show(10010);
    q.show(123456);


    return 0;
}