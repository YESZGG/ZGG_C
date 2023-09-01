#include <iostream>

using namespace std;

void test(int) // 占位参数
{
}
void test1(char) // 占位参数
{
}
int main()
{
    int b = 10;
    test(b); // 带占位参数的函数调用时，要传入对应类型的参数值
    return 0;
}