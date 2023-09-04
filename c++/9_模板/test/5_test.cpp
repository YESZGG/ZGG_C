// 定义一个学生模板类，包含姓名和年龄，  编写一个接口函数设置模板类的数据  ，一个输出模板类的数据
#include <iostream>
#include <cstring>
using namespace std;

template <class Name, typename ID>
class base
{
public:
    Name name;
    ID stuNo;
};

template <class Name, typename ID>
void set_base(base<string, int> &stu, Name name, ID stuNo)
{
    stu.name = name;
    stu.stuNo = stuNo;
}

void displayInfo(base<string, int> &stu)
{
    cout << "姓名: " << stu.name << endl;
    cout << "学号: " << stu.stuNo << endl;
}

int main()
{
    base<string, int> student;
    set_base(student,"张三",123123);
    displayInfo(student);
}
