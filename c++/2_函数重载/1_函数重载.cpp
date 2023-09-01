#include <iostream>

using namespace std;

/*
    函数重载，函数名相同，但是参数列表不同(参数个数不同、参数类型不同、参数的排列顺序不同)
    函数的返回类型可以相同也可以不相同
*/
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

void swap(float *a, float *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void swap(char *a, char *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void swap(bool *a, bool *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
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