#include <iostream>
#include <cstring>
#include <strings.h>

using namespace std;

/*  
    1、析构函数与构造函数名字相同，但它前面必须加波浪号（~）。

    2、析构函数既可以在类内部定义，也可以在类外部定义。

    3、析构函数没有参数，没有返回值，不能重载。也就是说，一个类中只能有一个析构函数，原因是不能释放同一块内存空间两次。

    4、当撤销对象时，系统会自动调用析构函数，无需调用。

    5、具有static属性的对象和全局对象只在main函数结束时，其生存周期才结束，这时才调用析构函数。

    6、析构函数的作用并不是删除对象。

    7、若一个对象是使用new运算符动态创建的，在使用delete1运算符释放它时，delete会自动调用析构函数。

    8、若没有定义析构函数，系统会自动生成一个析构函数，这个析构函数不做任何事情。
*/

class Data
{
public:
    Data(int val) // 构造函数
    {
        cout << "Data()" << endl;
        a = val;
        cout<<"val:" << a <<endl;
        name = new char[1024]; // 在构造函数中给指针变量申请空间
        bzero(name, 1024);
    }
    ~Data() // 析构函数
    {
        cout << "~Data()" << endl;

        // 在销毁该类对象之前，先把 该类对象 之前的所有 申请的资源 释放
        delete[] name; // 在析构函数中释放申请的空间
    }

private: // 私有属性
    int a;
    // char name[20];
    char *name; // 指针
};

void test()
{
    // Data类的实例化对象 mya
    Data mya(10);
}

int main()
{
    // test()函数结束之后，它里面的对象空间被释放，同样会调用析构函数
    test();

    //实例化一种
    Data d1(10);

    //实例化另一种
    Data *d2 = new Data(20);
    delete d2;

    return 0;
}
/* 
    1.在函数内部实例化对象且构造函数内部使用new申请了堆空间，在函数结束之后，就会自动调用析构函数，释放申请的内存空间 
    2.在主函数中实例化对象
*/