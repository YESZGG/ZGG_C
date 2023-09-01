#include <iostream>

using namespace std;

class Base
{
private:
    int value;

public:
    void set_value(int val)
    {
        value = val;
    }
    void show_value()
    {
        cout << "Base::value = " << value << endl;
    }
};

class P_base : public Base
{
private:
    int value;

public:
    void set_value(int val)
    {
        value = val;
    }
    void show_value()
    {
        cout << "P_base::value = " << value << endl;
    }
};

int main(int argc, char *argv[])
{
    P_base temp;
    // 1.利用域操作符
    cout << "利用域操作符" << endl;
    temp.P_base::set_value(10);
    temp.P_base::show_value();

    temp.Base::set_value(20);
    temp.Base::show_value();

    // 2.利用基类的引用 显示隐藏的接口
    cout << "利用基类的引用 显示隐藏的接口" << endl;
    Base &a = temp;
    a.set_value(30);
    a.show_value();

    // 3.利用基类的指针 显示隐藏的接口
    cout << "利用基类的指针 显示隐藏的接口" << endl;
    Base *p = &temp;
    p->set_value(40);
    p->show_value();

}