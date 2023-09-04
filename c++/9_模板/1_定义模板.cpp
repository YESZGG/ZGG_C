#include <iostream>

using namespace std;

template <typename T>
void swapValues(T &a, T &b)
{
    // 1.利用变量来存储 进行交换
    // T temp = a;
    // a = b;
    // b = temp;
    // 2.利用加减法 进行交换
    a = a + b;
    b = a - b;
    a = a - b;

    // 3.使用异或运算交换两个数的值  异或运算只适用于整数类型，而不适用于浮点数。
    // a = a ^ b;
    // b = a ^ b;
    // a = a ^ b;
}

int main()
{
    int a = 6, b = 5;
    swapValues(a, b);
    cout << "交换后："
         << "a = " << a << " "
         << "b = " << b << endl;

    float x = 2.5, y = 6.7;
    swapValues(x, y);
    cout << "交换后："
         << "a = " << x << " "
         << "b = " << y << endl;
    // 现在 x 的值为 6.7，y 的值为 2.5

    char c1 = 'A', c2 = 'Z';
    swapValues(c1, c2);
    cout << "交换后："
         << "a = " << c1 << " "
         << "b = " << c2 << endl;
}