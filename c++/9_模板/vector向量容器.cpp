#include <iostream>
using namespace std;

// 添加向量容器头文件
#include <vector>

int main()
{
    // 定义一个向量容器 ,存储的数据是什么？？？？
    vector<float> v;

    // 往向量容器中添加数据
    v.push_back(3.2);
    v.push_back(3.3);
    v.push_back(4.15);
    v.push_back(5.16);

    // 输出容量
    cout << "最大元素个数" << v.max_size() << endl;
    // 输出元素个数
    cout << "元素" << v.size() << endl;

    cout << v.front() << endl;

    // 遍历向量容器的所有数据
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << endl;
    }
}