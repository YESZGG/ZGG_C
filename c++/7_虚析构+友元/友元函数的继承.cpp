#include <iostream>
using namespace std;

class base // 爸爸
{
private:
    int a;
    friend void show(); // 声明友元函数,爸爸的朋友  -》 show 叔叔
};

class xbase : public base // 儿子 ，这个show 叔叔 跟我有啥关系？？
{

private:
    int b;
    friend void show(); // 再次介绍 ，show 叔叔给儿子认识
};

void show()
{
    xbase x;
    x.a = 10;
    x.b = 20;

    cout << x.a << " " << x.b << endl;
}

int main()
{
}