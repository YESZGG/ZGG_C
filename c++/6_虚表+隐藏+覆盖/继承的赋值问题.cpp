#include <iostream>
using namespace std;

class base
{
public:
    base() {}
    base(int v) : value(v) {}

private:
    int value;
};

class test : public base
{
public:
    test(int v) : data(v) {}

private:
    int data;
};

int main()
{
    // base a(100);
    // test b = a; // 基类对象赋值给 派生类 ， 不可以

    test a(100);
    base b = a; // 派生类对象赋值给  基类， 可以

    // 利用基类对派生类作引用  -》 OK
    base &c = a;

    //test &d = b; //错误的  

    // 利用基类指针指向派生类对象  -》 OK
    base *p = &a;  

    test *q = &b;  //派生类的指针，无法指向基类的对象 


    //总结： 派生类 可以 给 基类  ， 基类不能给派生类 
}