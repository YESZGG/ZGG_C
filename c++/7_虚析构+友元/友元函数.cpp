#include <iostream>
using namespace std;
class base
{
public:
    int a;

protected:
    int b;

private:
    int c;
    // 声明set_base 是当前类的友元函数  （好朋友）
    friend void set_base(base &tmp);
    friend void show_base(base tmp);
};

void set_base(base &tmp)
{
    // cout << this << endl;  友元函数不是类的成员函数，无法使用 this 指针

    tmp.a = 10;
    tmp.b = 20;
    tmp.c = 30;
}

void show_base(base tmp)
{
    cout << tmp.a << endl;
    cout << tmp.b << endl;
    cout << tmp.c << endl;
}

int main()
{
    base tmp;
    set_base(tmp);
    show_base(tmp);
}