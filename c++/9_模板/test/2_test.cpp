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

private:
    int value;
    friend bool operator>(base a, base b);
};

bool operator>(base a, base b)
{
    return a.value > b.value;
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