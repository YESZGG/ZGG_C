#include <iostream>

using namespace std;

// 如果函数的定义和声明分开,默认参数必须写在声明中，定义的时候不能再写了
//void print(const char *name = "bling", int age = 18, const char *classes = "FX2308");

// 函数的定义
// 函数的形参列表 带 默认参数
void print(const char *name = "bling", int age = 18, const char *classes = "FX2308")
{
    cout << "姓名:" << name << "\t年龄:" << age << "\t班级:" << classes << endl;
}

// 如果给某个形参设置了默认值，从这个形参开始，后面所有的形参都要设置默认值
void show(int b, int c = 10, int a = 0)
{
}

void show3(int b, int c, int a = 0)
{
}

void show4(int b=10, int c=20, int a = 30)
{
}

// void show1(int b=10, int c, int a = 0) //error
// {
// }

// void show2(int b=10, int c=20, int a) //error
// {
// }


int main()
{
    print("张3"); // 后面3个参数都定义了 可以只填写1个
    print("li4", 20);
    print("隔壁", 20, "GZ2235");

    return 0;
}

// 函数的定义
// void print(const char *name, int age, const char *classes)
// {
//     cout << "姓名:" << name << "\t年龄:" << age << "\t班级:" << classes << endl;
// }
