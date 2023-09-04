#ifndef MYVECTOR_H_
#define MYVECTOR_H_

#include <iostream>

using namespace std;

#define size_type unsigned long

template <typename TYPE>
class Myvector
{
private:
    TYPE *data;      // 动态数组存储元素
    size_t capacity; // Myvector的容量  容器能存储数据的个数
    size_t size;     // Myvector中当前元素的个数   容器目前存在的元素数
public:
    // 默认构造函数
    Myvector();

    // 重载构造函数
    Myvector(size_type num, const TYPE &val);

    // 深拷贝构造函数
    Myvector(const Myvector &from);

    // 析构函数
    ~Myvector();

    // 在vector的末尾添加一个元素
    void push_back(const TYPE &value);

    // 从vector中移除最后一个元素
    void pop_back();

    // 返回vector中元素的个数
    size_t getSize();

    // 返回vector的当前容量
    size_t getCapacity();

    // 指定容器能存储数据的个数
    void reserve(size_t newCapacity);

    // 重新指定有效元素的个数
    void resize(size_t newSize);

    // 删除当前vector中的所有元素
    void clear();

    // 返回当前vector起始元素的引用
    TYPE front();

    // 返回当前vector最末一个元素的引用
    TYPE back();

    // 如果当前vector没有容纳任何元素,则empty()函数返回true,否则返回false
    bool empty();

    // 交换当前vector与vector from的元素
    void swap(Myvector &from);

    /*
      v1 == v2
      v1 != v2
      v1 <= v2
      v1 >= v2
      v1 < v2
      v1 > v2
      v[]
    */
    // 重载 = 赋值运算符
    Myvector &operator=(const Myvector &other);

    bool operator>(const Myvector &other);
    bool operator<(const Myvector &other);

    bool operator==(const Myvector &other);
    bool operator>=(const Myvector &other);
    bool operator<=(const Myvector &other);

    TYPE &operator[](size_t index);
};

#endif