#include <iostream>
using namespace std;

template <class T>
bool isBig(T a, T b)
{
    if (a > b)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 定义用户自定义数据类型
class base
{
public:
    base(int v) : value(v) {}

    // // 重载当前类的运算符
    // bool operator>(base &b)
    // {
    //     if (this->value > b.value)
    //     {
    //         return true;
    //     }
    //     else
    //     {
    //         return false;
    //     }
    // }

private:
    int value;
    friend bool isBig(base a, base b);
};

// 编写一个处理自定义数据类型的普通函数
bool isBig(base a, base b)
{
    if (a.value > b.value)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    // 基本的数据类型
    // int a = 10;
    // int b = 20;
    base a(10);
    base b(20);

    if (isBig(a, b))
    {
        cout << "a is bigger than b" << endl;
    }
    else
    {
        cout << "b is bigger than a" << endl;
    }
}