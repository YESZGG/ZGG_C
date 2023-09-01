#include <iostream>
using namespace std;

class base
{
public:
    base() { cout << "base的构造函数" << endl; }
    virtual ~base() { cout << "~base的析构函数" << endl; }

    int base_value;
};

class xbase : public base
{
public:
    xbase()
    {
        cout << "xbase的构造函数" << endl;

        this->q = new int(100);

        cout << "分配堆空间:" << q << endl;
    }
    virtual ~xbase() // 放入虚表，让基类指针，能够访问得到
    {
        cout << "~xbase的析构函数" << endl;

        cout << "释放堆空间:" << q << endl;

        delete this->q;
    }

    int xbase_value;

private:
    int *q;
};

int main()
{
    // 利用基类指针，指向派生类对象 ,为什么要这样做？ 多态都是要用 基类指针或引用指向派生类
    base *p = new xbase; // 堆空间
    /*  
        先使用new操作符在堆上分配了一个存储xbase对象的内存块，构造xbase对象，调用xbase类的构造函数来初始化刚分配的内存块
    */



    // xbase *p = new xbase;

    p->base_value = 100;
    // p->xbase_value = 200;  //只是指向大类中的小类

    delete p; // 释放堆空间 通过基类指针删除对象，自动调用派生类的析构函数
}


/*  
在C++中，当基类的析构函数声明为虚函数（virtual destructor），就可以实现多态的正确析构。

当使用基类指针指向派生类对象并通过基类指针来删除对象时，如果基类的析构函数是非虚函数（non-virtual destructor），
那么只会调用基类的析构函数而不会调用派生类的析构函数。这样可能导致派生类中分配的资源没有正确释放，造成内存泄漏。

而将基类的析构函数声明为虚函数后（添加`virtual ~base() { ... }`），编译器在运行时会根据实际对象的类型动态解析调用正确的析构函数。
这样，通过基类指针删除派生类对象时，会先调用派生类的析构函数，再调用基类的析构函数，确保正确释放所有资源。

总结：将基类的析构函数声明为虚函数是为了实现多态，使得通过基类指针来删除派生类对象时能够正确调用派生类的析构函数。
*/