#include <iostream>
#include <cstring>

using namespace std;

class Student
{
public:
    Student() {}
    Student(const char *name, int age)
    {
        this->name = new char[256]; // 在构造函数中申请空间
        strcpy(this->name, name);
        this->age = age;

        cout << "Student(const char*name,int age)" << endl;
    }
    ~Student() // 析构 浅拷贝析构的时候会出现double free的情况
    {
        cout << "~Student()" << endl;
        delete[] name;
    }
// 如果我们没有自己定义拷贝构造函数，编译器默认就会为我们生成 一个 值的拷贝构造函数
#if 0
    Student(const Student &other)  //Student &other = s1
    {
        //值的拷贝
        this->name = other.name;
        this->age = other.age;

        cout<<"Student(const Student &other)"<<endl;
    }
#endif

    // 如果此时 该类中 有指针成员 ，需要申请内存空间的时候  需要自己定义一个 深拷贝构造函数
    // 深度拷贝：不仅仅 拷贝 对象的内存空间的数据 ，也为指针成员申请内存空间
    Student(const Student &other)
    {
        this->name = new char[256];

        strcpy(this->name, other.name);
        this->age = other.age;

        cout << "Student(const Student &other)" << endl;
    }

    void printInfo()
    {
        // cout<<"name:"<<name<<endl; //static_cast<const void *>显示类型转换
        cout << "name: " << name << "\t"
             << "addr: " << static_cast<const void *>(name) << endl;
    }

    void setName(const char *name)
    {
        strcpy(this->name, name);
    }

private:
    char *name; // 指针变量
    int age;
};

int main()
{
    // 实例化一个对象
    Student s1("张3", 22);
    s1.printInfo();

    // 当创建对象的时候 ，通过另一个对象来初始化 调用拷贝构造函数
    Student s2(s1); // 拷贝构造函数的作用
    s2.printInfo();

    // s2.setName("li4");
    // s2.printInfo();

    return 0;
}
