#include <iostream>
using namespace std;

template <class T>
class base // 定义一个模板类
{
public:
    T a;
};

// // 1.把模板类的类型 ，实例化
// void set_base(base<int> &tmp, int v)
// {
//     tmp.a = v;
// }

// void show_base(base<int> &tmp)
// {
//     cout << tmp.a << endl;
// }

// // 2.把模板类的类型，继续模板化
// template <class T>
// void set_base(base<T> &tmp, T v)
// {
//     cout << "继续模板化" << endl;
//     tmp.a = v;
// }

// template <class T>
// void show_base(base<T> &tmp)
// {
//     cout << "继续模板化" << endl;
//     cout << tmp.a << endl;
// }

template <class T, class T1>
void set_base(T &tmp, T1 v)
{
    tmp.a = v;
}

template <class T>
void show_base(T &tmp)
{
    cout << tmp.a << endl;
}

int main()
{
    base<int> tmp;
    set_base(tmp, 100);
    show_base(tmp);
}

