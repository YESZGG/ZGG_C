#include <iostream>
using namespace std;

class ClassB; // 前置声明ClassB

// 定义ClassA类
class ClassA
{
private:
    int privateDataA;

public:
    ClassA() : privateDataA(20) {}

    void displayPrivateDataB(ClassB &b);
    // {
    //     cout << "ClassA: Accessing private data B from ClassB: " << b.privateDataB << endl;
    // }
    // 声明ClassB为友元类，可以访问其私有成员
    friend class ClassB;
};

// 定义ClassB类
class ClassB
{
private:
    int privateDataB;

public:
    ClassB() : privateDataB(12) {}

    void displayPrivateDataA(ClassA &a);
    // {
    //     cout << "ClassB: Accessing private data A from ClassA: " << a.privateDataA << endl;
    // }
    // 声明ClassA为友元类，可以访问其私有成员
    friend class ClassA;
};

void ClassA::displayPrivateDataB(ClassB &b)
{
    cout << "ClassA: Accessing private data B from ClassB: " << b.privateDataB << endl;
}

void ClassB::displayPrivateDataA(ClassA &a)
{
    cout << "ClassB: Accessing private data A from ClassA: " << a.privateDataA << endl;
}

int main()
{
    ClassA objA;
    ClassB objB;

    objB.displayPrivateDataA(objA); // ClassB访问ClassA的私有成员值
    objA.displayPrivateDataB(objB); // ClassB访问ClassA的私有成员值

    return 0;
}

/*
友元类的练习.cpp: In member function ‘void ClassA::displayPrivateDataB(ClassB&)’:
友元类的练习.cpp:17:69: error: invalid use of incomplete type ‘class ClassB’
   17 |         cout << "ClassA: Accessing private data B from ClassB: " << b.privateDataB << endl;
      |                                                                     ^
友元类的练习.cpp:4:7: note: forward declaration of ‘class ClassB’
    4 | class ClassB; // 前置声明ClassB
      |       ^~~~~~

解决方法：
    在所有类定义完毕后，再去定义这些访问友元类的成员函数

*/