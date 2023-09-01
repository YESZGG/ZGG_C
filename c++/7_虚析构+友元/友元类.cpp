#include <iostream>
using namespace std;
// 小明类
class xm
{
public:
    int a;

protected:
    int b;

private:
    int c;
    // 声明小东是我的好朋友
    friend class xd;
};

// 小东类
class xd
{
public:
    void set_xm(xm &x)
    {
        x.a = 10;
        x.b = 20;
        x.c = 30;
    }
    void show_xm(xm x)
    {
        cout << x.a << endl;
        cout << x.b << endl;
        cout << x.c << endl;
    }
};

int main()
{

    // 定义一个小明类对象
    xm x;

    // 定义一个小东类对象
    xd d;

    // 小东类函数成员访问 小明类对象
    d.set_xm(x);
    d.show_xm(x);
}