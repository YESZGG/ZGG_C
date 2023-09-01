#include <iostream>
using namespace std;

class base
{
private:
    // 所有的虚函数都放在虚表上
    virtual void f()
    {
        cout << "show f" << endl;
    }
    virtual void j()
    {
        cout << "show j" << endl;
    }
    virtual void k()
    {
        cout << "show k" << endl;
    }
};

int main()
{
    base tmp;

    /*
    在VS中，long是4字节，32位。 -2147483648~2147483647
    在Linux中，long是8字节，64位。-9223372036854775808~9223372036854775807
    C++11标准增了long long类型的整数，至少64位，且至少与long一样长。
    在VS中，long long是8字节，64位。-9223372036854775808~9223372036854775807
    在Linux中，long和long long类型都是8字节，64位。
    */
    cout << sizeof(long) << endl;      // 8个字节
    cout << sizeof(long long) << endl; // 8个字节

    // 获取类的首地址 与 虚表指针的地址一样
    cout << "&tmp=" << &tmp << endl;

    // 虚表指针的地址 p  保存 虚表指针的地址
    long long *p = (long long *)&tmp;

    // 取该地址上内容
    long long *v_table = (long long *)*p;

    cout << "虚表地址v_table=" << v_table << endl;

    // 定义一个函数指针
    typedef void (*func)(); //定义了一个名为 func 的函数指针类型

    // 得到第一个虚函数的地址
    func f = (func)v_table[0]; // 给函数指针赋值 函数名字即是函数指针的地址
    // 调用函数
    f();

    f = (func)v_table[1]; // 给函数指针赋值 函数名字即是函数指针的地址
    // 调用函数
    f();

    f = (func)v_table[2]; // 给函数指针赋值 函数名字即是函数指针的地址
    // 调用函数
    f();
}