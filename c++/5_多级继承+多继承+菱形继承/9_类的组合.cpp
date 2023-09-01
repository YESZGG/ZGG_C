#include <iostream>
#include <string.h>
using namespace std;

class dog
{
public:
    dog() {}
    dog(const char *n, int age, const char *v) : age(age)
    {
        strcpy(this->name, n);
        strcpy(this->var, v);
    }

    // 显示这条狗
    void show_dog()
    {
        cout << "狗名:" << name << " 年龄:" << age << " 品种:" << var << endl;
    }

private:
    char name[1024];
    int age;
    char var[1024];
};

class person
{
public:
    person(const char *n, int age, dog d) : d(d), age(age)
    {
        strcpy(this->name, n);
    }
    // 显示人的信息
    void show_person()
    {
        cout << "姓名:" << name << " 年龄:" << age << endl;

        // 显示这个人养的狗
        d.show_dog();
    }

private:
    char name[1024];
    int age;
    // 这个人养了一条狗
    dog d;
};

int main()
{                      // dog("旺财", 1, "土狗") 调用dog类的构造函数
    person xm("小明", 18, dog("旺财", 1, "土狗")); //???? 狗呢？？
    xm.show_person();
}