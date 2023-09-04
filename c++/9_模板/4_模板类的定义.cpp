#include <iostream>
using namespace std;

template <class T>
class base
{
public:
    base(T v) : value(v) {}

private:
    T value;
};

int main()
{
    //<不会> 根据用户传递的 100 推导模板类型为 int !!
    base tmp(100); // 错误的，没有实例化，无法定义对象

    base<int> tmp2(10); // 指定模板类的通用类型，实例化
}
