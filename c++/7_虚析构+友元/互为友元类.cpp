#include <iostream>
using namespace std;

// 前向声明,只是单纯的声明，不是定义！！
class B;
class A;

class A
{
public:
    void show_b(B &b); // 声明

private:
    int a_value = 20;
    friend class B; // 声明 类B 是当前类的友元
};

class B
{
public:
    void show_a(A &a); // 声明

private:
    int b_value = 10;
    friend class A; // 声明 类 A 是当前类的友元
};

/*---------------------在所有类定义完毕后，再去定义这些成员函数-----------------------*/
void A::show_b(B &b)
{
    cout << "b_value = " << b.b_value << endl;
}

void B::show_a(A &a)
{
    cout << "a_value = " << a.a_value << endl;
}

int main()
{
    A a;
    B b;

    b.show_a(a);
    a.show_b(b);
}