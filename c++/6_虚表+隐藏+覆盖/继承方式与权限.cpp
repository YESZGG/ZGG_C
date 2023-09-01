#include <iostream>
using namespace std;
/*共有继承和保护继承的区别: 1.共有继承，派生类对象可以访问基类的公有成员。
                          2.保护继承，派生类对象  无法  访问基类的公有成员。

*/
// 爷爷
class yeye
{
public:
    int money = 10000000;
};

// 爸爸
class baba : private yeye
{
public:
    void take_money()
    {
        money -= 10000; // 花掉 1万块

        cout << money << endl;
    }
};

// 孙子
class sunzi : public baba
{
public:
    void take_yeye_money()
    {
        money -= 100000; // 花掉 10 万块

        cout << money << endl;
    }
};

int main()
{
    sunzi xm;

    xm.take_yeye_money();
}