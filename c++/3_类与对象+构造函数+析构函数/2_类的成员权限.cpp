#include <iostream>

using namespace std;

class Data
{

    // 不写上面这些关键字，默认都是私有的。
    //  char a;
    //  short b;
    //  int c;

public: // 共有权限
    int a;
    void setVal(int num)
    {
        a = num;
        b = num;//类内部
        c = num;
    }

protected: // 保护权限
    int b;
    void setB(int num)
    {
        b = num;
        a = num; //类内部---直接访问
        c = num;
    }

private: // 私有权限
    int c;
    void setC(int num)
    {
        c = num;
        a = num;//类内部
        b = num;
    }
};

int main()
{
    //调用不写关键字的默认成员
    // Data d1;
    // cout << d1.a << endl; // error: ‘char Data::a’ is private

    //公有权限---内的外部
    Data d1;
    d1.setVal(10); //通过对象才能访问

    //保护权限---内的外部
    Data d2; 
    //d2.setB(20); //‘void Data::setB(int)’ is protected

    //私有权限---内的外部
    Data d3;
    // cout<<d3.c<<endl; // error: ‘int Data::c’ is private
    //d3.setC(30); //error: ‘void Data::setC(int)’ is private

    return 0;
}