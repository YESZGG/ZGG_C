#include "myvector.h"
#include "myvector.cpp"

#include <iostream>
using namespace std;

int main()
{
    // 默认构造函数
    Myvector<int> vec1;

    // 从尾部添加元素
    vec1.push_back(10);
    vec1.push_back(20);
    vec1.push_back(30);
    for (size_t i = 0; i < vec1.getSize(); i++)
    {
        cout << vec1[i] << " ";
    }
    cout << endl;

    // 获取size大小
    cout << "vec1的大小: " << vec1.getSize() << endl; // 输出: 3

    // 获取Capacity容量
    cout << "vec1的容量: " << vec1.getCapacity() << endl; // 输出: 4 (default capacity)

    // 调整size
    vec1.resize(5);                                             // 增加大小，新元素初始化为默认值
    cout << "调整大小后vec1的大小: " << vec1.getSize() << endl; // 输出: 5

    // Test empty
    cout << "vec1是空的吗?" << (vec1.empty() ? "Yes" : "No") << endl; // 输出: No

    // 获取vector里第一个元素和最后一个元素
    cout << "vec1的前元素: " << vec1.front() << endl; // 输出: 10
    cout << "vec1的后元素: " << vec1.back() << endl;  // 输出: 0 (default value)

    // 运算符[]
    cout << "索引为2的元素: " << vec1[2] << endl; // 输出: 30

    // 删除最后一个元素
    vec1.pop_back();
    cout << "pop_back后vec1的大小: " << vec1.getSize() << endl; // 输出: 4
    for (size_t i = 0; i < vec1.getSize(); i++)
    {
        cout << vec1[i] << " ";
    }
    cout << endl;

    // 清除所有元素
    vec1.clear();
    cout << "清除后vec1的大小: " << vec1.getSize() << endl; // 输出: 0

    // 拷贝构造函数和操作符=
    Myvector<int> vec2(vec1); // 拷贝构造函数
    vec2 = vec1;              // 操作符 =
    for (size_t i = 0; i < vec2.getSize(); i++)
    {
        cout << vec1[i] << " ";
    }
    cout << endl;

    // 测试比较运算符
    Myvector<int> vec3;
    vec3.push_back(10);
    vec3.push_back(20);
    cout << "vec2 > vec3? " << (vec2 > vec3 ? "Yes" : "No") << endl;   // 输出: No
    cout << "vec2 == vec3? " << (vec2 == vec3 ? "Yes" : "No") << endl; // 输出: No

    return 0;
}
