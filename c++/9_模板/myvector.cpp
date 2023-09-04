#include <iostream>
using namespace std;

// 定义一个模板类
template <class T>
class Myvector
{
public:
    // 默认构造
    Myvector() {}

    // 插入接口
    void push_back(const T &val)
    {
        this->arry[s] = val;
        s++;
    }

    // 重载下标
    T &operator[](int index)
    {
        return this->arry[index];
    }

    // 返回元素
    int size()
    {
        return this->s;
    }

private:
    T arry[4096];
    int s = 0; // 当前元素的个数
};

int main()
{
    // 定义一个my向量容器
    Myvector<int> v;

    // 插入
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    // 输出
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << endl;
    }
}