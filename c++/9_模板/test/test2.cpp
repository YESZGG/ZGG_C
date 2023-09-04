#include <iostream>
using namespace std;

// 数组遍历模板
template <class T>
void show_arry(T &arry, int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << arry[i] << " ";
    }
    cout << endl;
}

// 交换模板
template <class T>
void Swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

// 排序模板
template <class T>
void sort(T &arry, int len)
{
    for (int j = 0; j < len; j++)
    {
        for (int i = 0; i < len - 1 - j; i++)
        {
            if (arry[i] > arry[i + 1]) // 前后比较，前面比后面的大
            {
                // 交换
                Swap(arry[i], arry[i + 1]);
            }
        }
    }
}

class base
{
public:
    base(int a) : a(a) {}

    bool operator>(base &tmp)
    {
        if (this->a > tmp.a)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

private:
    int a;

    friend ostream &operator<<(ostream &out, base &tmp)
    {
        cout << tmp.a;
        return cout;
    }
};

int main()
{
    char str[] = {"asdklasdkasldjklasj"};
    int arry[] = {13, 212, 355, 14, 5, 51, 3, 12, 5};
    show_arry(arry, sizeof(arry) / sizeof(int));
    show_arry(str, sizeof(str) / sizeof(char));

    // 排序
    sort(arry, sizeof(arry) / sizeof(int));
    sort(str, sizeof(str) / sizeof(char));

    show_arry(arry, sizeof(arry) / sizeof(int));
    show_arry(str, sizeof(str) / sizeof(char));

    // 定义一个对象数组
    base arr[] = {1, 5, 12, 56, 1, 6, 12, 6, 12, 4};
    show_arry(arr, sizeof(arr) / sizeof(base));
    sort(arr, sizeof(arr) / sizeof(base));
    show_arry(arr, sizeof(arr) / sizeof(base));
}