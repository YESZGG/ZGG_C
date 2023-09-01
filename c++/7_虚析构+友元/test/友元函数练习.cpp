/* 定义个学生类，包含姓名，学号。年龄。定义一个类外函数初始化这些值，一个类外函数显示这些值。 */
#include <iostream>
#include <cstring>

using namespace std;

class student
{
private:
    char name[10];
    char stuNumber[10];
    int age;

public:
    friend void set_student(student &tmp);          // 声明友元函数
    friend void show_student_info(student tmp);     // 声明友元函数
};

void set_student(student &tmp)
{
    strcpy(tmp.name, "张三");
    strcpy(tmp.stuNumber, "123456");
    tmp.age = 18;
}

void show_student_info(student tmp)
{
    cout << "姓名:" << tmp.name <<" "<< "学号:" << tmp.stuNumber <<" "<< "年龄:" << tmp.age << endl;
}

int main()
{
    student temp;
    set_student(temp);
    show_student_info(temp);
}