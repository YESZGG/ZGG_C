#include <iostream>
#include <cstring>

using namespace std;

//打印机类
class Printer
{
public:
    Printer(int n):page(n)
    {

    }
    ~Printer()
    {

    }

    int print()
    {
        return page;
    }

private:
    int page;    

};

//电脑类
class Computer
{
public:
    Computer(const char *name):pri(10) //内嵌对象的初始化
    {
        strcpy(this->name,name);
    }
    ~Computer()
    {

    }

    void show()
    {

    }

    void count()
    {

    }

    //电脑的打印功能
    void dayin()
    {
        cout<<name<<"电脑正在打印:"<<pri.print()<<endl;
    } 

private:
    char name[20];
    Printer pri; //私有属性
};


int main()
{
    
    Computer c1("拯救者");

    c1.dayin();

    //类的外部不能放问私有属性
    // c1.pri.print(); //error

    return 0;
}