#include <iostream>
using namespace std;

class base
{
public:
    base(int d) : data(d) {}
    bool operator<(base &other)
    {
        if (this->data < other.data)
        {
            return true;
        }
        else
            return false;
    }
    bool operator==(base &other)
    {
        if (this->data == other.data)
        {
            return true;
        }
        else
            return false;
    }
    bool operator!=(base &other)
    {
        if (this->data != other.data)
        {
            return true;
        }
        else
            return false;
    }

private:
    int data;

    friend bool operator>(base a, base b);
};

// 重载返回值的确定是完全由用户自定义的！
bool operator>(base a, base b)
{
    if (a.data > b.data)
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
    base a(10);

    base b(20);

    // 比较对象 a 和 b 的大小
    if (a > b)
    {
        cout << "对象a 大于 对象b" << endl;
    }
    else
    {
        cout << "对象a 小于 对象b" << endl;
    }

    // 实现关系运算符的 <  ==  !=  重载操作
    if (a < b)
    {
        cout << "对象a 小于 对象b " << endl;
    }
    else
    {
        cout << "对象a 大于 对象b " << endl;
    }
    base c(30);
    base d(30);

    cout << (c == d ? "对象c 等于 对象d" : "对象c 不等于 对象 d") << endl;
    cout << (a != c ? "对象a 不等于 对象c " : "对象a 等于 对象c ") << endl;
}