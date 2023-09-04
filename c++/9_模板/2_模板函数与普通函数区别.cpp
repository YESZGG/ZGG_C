#include <iostream>
using namespace std;

// 定义普通函数
int add(int a, int b)
{
    cout << "调用普通函数" << endl;

    return a + b;
}

// 定义模板函数
template <class T>
T add(T a, T b)
{
    cout << "调用模板函数 T" << endl;

    return a + b;
}

// 重载模板函数
template <class T, class T1>
T add(T a, T1 b)
{
    cout << "调用模板函数 T  T1" << endl;

    return a + b;
}

int main()
{
    int a = 10;
    short b = 20;
    int c = 30;
    cout << add<int>(a, c) << endl; // 指定使用模板函数

    cout << add(a, c) << endl; // 调用普通函数

    cout << add(a, b) << endl; // 调用重载模板函数
}