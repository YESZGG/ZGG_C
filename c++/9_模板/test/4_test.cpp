/* 定义一个模板类，包含姓名和学号，通过模板类定义一个学生对象，并输出信息。 */
#include <iostream>
#include <cstring>
using namespace std;

template <class Name, typename ID>

class base
{
private:
    Name name;
    ID stuNo;

public:
    base(Name name, ID stuNo) : name(name), stuNo(stuNo) {}


    void displayInfo()
    {
        cout << "姓名: " << name << endl;
        cout << "学号: " << stuNo << endl;
    }
};

int main()
{
    base<string, int> student("张三", 123124);
    student.displayInfo();

    return 0;
}
