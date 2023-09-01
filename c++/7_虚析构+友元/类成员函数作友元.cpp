#include <iostream>
using namespace std;
// 前向声明  value
class value;

class base
{
public:
    void set_value(value &v);

    void show_value(value &v);
};

class value
{
private:
    int v;
    // friend class base; // 声明base是当前类友元,base类的有函数都可以访问 value的私有成员
    friend void base::set_value(value &v); // 只声明了 set_value
};

// 所有类定义完毕后编写函数 定义函数
void base::set_value(value &v)
{
    v.v = 10;
}

void base::show_value(value &v)
{
    cout << v.v << endl; // 未声明为友元，不能访问私有
}

int main()
{
    value v;

    base b;
    b.set_value(v);
    b.show_value(v);
}