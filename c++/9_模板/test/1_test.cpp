/* 定义一个模板函数，可以实现3个不同的数据类型相加 */
#include <iostream>
using namespace std;

template <typename T1, typename T2, typename T3>
T3 add(T1 a, T2 b, T3 c)
{
    return (a + b + c);
}

int main()
{
    int a = 10;
    short b = 20;
    double c = 3.1415;

    cout << add(a, b, c) << endl;
}