#if 0
/*
    练习1:编写C++风格的程序，建立swap()函数，重载该函数，分别用引用和指针做形参，实现两个整型数据的互换。
*/
#include <iostream>

using namespace std;
// 函数参数是地址
void swap(int *a, int *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}
// 函数参数是引用
void swap(int &a, int &b)
{
    a = a + b;
    b = a - b;
    a = a - b;
}

int main()
{
    int a = 10, b = 20;

    swap(&a, &b);// 函数参数是地址
    cout << "a = " << a << "\t"
         << "b = " << b << endl;
    swap(a, b);// 函数参数是引用
    cout << "a = " << a << "\t"
         << "b = " << b << endl;

    return 0;
}
#endif

#if 0
/*
    练习2:编写一个C++风格的程序，建立sroot()函数，返回其参数的立方。
    重载sroot()函数3次，让它返回整数、长整数与双精度的立方，用cout输出时系统自动会根据数据大小选择小数或指数形式输出。
    (int long double-->3个函数)
*/
#include <iostream>

using namespace std;

int sroot(int num)
{
    return num * num * num;
}

long int sroot(long int num)
{
    return num * num * num;
}

double sroot(double num)
{
    return num * num * num;
}

int main()
{
    int intResult = sroot(3);
    long int longIntResult = sroot(4);
    double doubleResult = sroot(5.5);

    cout << "Integer result: " << intResult << endl;
    cout << "Long integer result: " << longIntResult << endl;
    cout << "Double result: " << doubleResult << endl;

    return 0;
}
#endif

#if 0
/*
    练习3:设计一个重载函数add，该函数有两个参数，可以实现两个类型的参数相加的操作，函数返回相加的结果。
    两个参数可以是整数、实数，但必须保证传参的时候两个参数类型分别相同。add(int,int) add(float float) add(int,double)
*/
#include <iostream>

using namespace std;

int add(int a, int b)
{
    return a + b;
}

float add(float a, float b)
{
    return a + b;
}

// double add(int a, double b)
// {
//     return a + b;
// }

double add(const int &a ,const double &b)
{
    cout<<__LINE__<<__FUNCTION__<<endl;
    return a+b;
}


int main()
{
    int intResult = add(3, 4);
    float floatResult = add(2.5f, 3.7f);
    double doubleResult = add(5, 6.8);

    cout << add(4, 5.12) << endl;
    cout << "Integer result: " << intResult << endl;
    cout << "Float result: " << floatResult << endl;
    cout << "Double result: " << doubleResult << endl;

    return 0;
}

#endif

#if 1
/*
    练习4：使用链表设计一个录入学生信息的函数（参数为学生信息）(输入信息有个学号，姓名，年龄，班级 参数顺序自定)，
    结合函数重载和默认参数的特点，设计的时候使后期使用更方便
*/
#include <iostream>
#include <string>

using namespace std;

struct Student
{
    int id;
    string name;
    int age;
    string className;
    Student *next;
};

void addStudent(Student *&head, int id, string name, int age, string className)
{
    Student *newStudent = new Student;
    newStudent->id = id;
    newStudent->name = name;
    newStudent->age = age;
    newStudent->className = className;
    newStudent->next = nullptr;

    if (head == nullptr)
    {
        head = newStudent;
    }
    else
    {
        Student *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newStudent;
    }
}

void addStudent(Student *&head, int id, string name)
{
    addStudent(head, id, name, 0, "");
}

void addStudent(Student *&head, int id, string name, int age)
{
    addStudent(head, id, name, age, "");
}

void display(Student *&head)
{
    // 打印学生信息
    cout << "学生信息：" << endl;
    Student *current = head;
    while (current != nullptr)
    {
        cout << "学号: " << current->id << ", 姓名: " << current->name
             << ", 年龄: " << current->age << ", 班级: " << current->className << endl;
        current = current->next;
    }
}

void destory(Student *&head)
{
    Student *current = head;
    // 释放链表内存
    current = head;
    while (current != nullptr)
    {
        Student *temp = current;
        current = current->next;
        delete temp;
    }
}

int main()
{
    Student *head = nullptr;

    addStudent(head, 1, "Alice", 20, "Class A");
    addStudent(head, 2, "Bob", 21);
    addStudent(head, 3, "Charlie");

    display(head);

    destory(head);

    return 0;
}

#endif