#include "myvector.h"

#include <iostream>
using namespace std;

// 默认构造函数
template <typename TYPE>
Myvector<TYPE>::Myvector() : data(nullptr), capacity(0), size(0)
{
}

// 析构函数
template <typename TYPE>
Myvector<TYPE>::~Myvector()
{
    delete[] data;
}

// 重载构造函数
template <typename TYPE>
Myvector<TYPE>::Myvector(size_type num, const TYPE &val) : data(new TYPE[num]), capacity(num), size(num)
{
    for (size_t i = 0; i < num; i++)
    {
        data[i] = val;
    }
}

// 深拷贝构造函数
template <typename TYPE>
Myvector<TYPE>::Myvector(const Myvector &from) : data(new TYPE[from.capacity]), capacity(from.capacity), size(from.size)
{
    for (size_t i = 0; i < from.size; i++)
    {
        data[i] = from.data[i];
    }
}

// 在vector的末尾添加一个元素
template <typename TYPE>
void Myvector<TYPE>::push_back(const TYPE &value)
{
    if (size == capacity) // 如果当前存储数据的个数等于容器所能存储的容量
    {
        // 满时增加容量
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
        reserve(newCapacity);
    }
    data[size++] = value;
}

// 从vector中移除最后一个元素
template <typename TYPE>
void Myvector<TYPE>::pop_back()
{
    if (size > 0)
    {
        size--;
    }
}

// 返回vector中元素的个数
template <typename TYPE>
size_t Myvector<TYPE>::getSize()
{
    return size;
}

// 返回vector的当前容量
template <typename TYPE>
size_t Myvector<TYPE>::getCapacity()
{
    return capacity;
}

// 指定容器能存储数据的个数
template <typename TYPE>
void Myvector<TYPE>::reserve(size_t newCapacity)
{
    if (newCapacity > capacity)
    {
        TYPE *newData = new TYPE[newCapacity]; // 使用实例创建容量为指定容量的阵列

        for (size_t i = 0; i < size; i++)
        {
            newData[i] = data[i]; // 将旧数组中的元素复制到新数组中
        }

        delete[] data; // 释放旧数组占用的内存

        data = newData;         // 更新数据指针，使其指向新的数组
        capacity = newCapacity; // 更新容量
    }
}

// 重新指定有效元素的个数
template <typename TYPE>
void Myvector<TYPE>::resize(size_t newSize)
{
    if (newSize > capacity)
    {
        reserve(newSize); // 如果指定的newSize大于当前容量，则为其分配内存
    }

    if (newSize > size)
    {
        for (size_t i = size; i < newSize; i++)
        {
            data[i] = TYPE(); // 将任何新元素初始化为默认值
        }
    }

    size = newSize;
}

// 删除当前vector中的所有元素
template <typename TYPE>
void Myvector<TYPE>::clear()
{
    delete[] data;
    data = nullptr;
    capacity = 0;
    size = 0;
}

// 返回当前vector起始元素的引用
template <typename TYPE>
TYPE Myvector<TYPE>::front()
{
    if (size == 0)
    {
        throw out_of_range("Vector is empty");
    }

    return data[0];
}

// 返回当前vector最末一个元素的引用
template <typename TYPE>
TYPE Myvector<TYPE>::back()
{
    if (size == 0)
    {
        throw out_of_range("Vector is empty");
    }
    return data[size];
}

// 如果当前vector没有容纳任何元素,则empty()函数返回true,否则返回false
template <typename TYPE>
bool Myvector<TYPE>::empty()
{
    if (size == 0)
    {
        return true;
    }
    return false;
}

// 交换当前vector与vector from的元素
template <typename TYPE>
void Myvector<TYPE>::swap(Myvector &from)
{
    // 交换数据指针
    TYPE *tempData = data;
    data = from.data;
    from.data = tempData;

    // 交换vector容量
    size_t tempCapacity = capacity;
    capacity = from.capacity;
    from.capacity = tempCapacity;

    // 交换size有效数据大小
    size_t tempSize = size;
    size = from.size;
    from.size = tempSize;
}


// 重载 = 赋值运算符
template <typename TYPE>
Myvector<TYPE>& Myvector<TYPE>::operator=(const Myvector &other)
{
    if (this != &other)
    {
        delete[] data;
        size = other.size;
        capacity = other.capacity;
        data = new TYPE[capacity];
        for (size_t i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
    }
    return *this;
}


// 重载大于操作符
template <typename TYPE>
bool Myvector<TYPE>::operator>(const Myvector &other)
{
    return size > other.size;
}

// 重载小于操作符
template <typename TYPE>
bool Myvector<TYPE>::operator<(const Myvector &other)
{
    return size < other.size;
}

// 重载下标操作符
template <typename TYPE>
TYPE &Myvector<TYPE>::operator[](size_t index)
{
    if (index >= size)
    {
        throw out_of_range("Index out of range");
    }
    return data[index];
}

// 重载相等运算符
template <typename TYPE>
bool Myvector<TYPE>::operator==(const Myvector &other)
{
    if (size != other.size)
        return false;

    for (size_t i = 0; i < size; i++)
    {
        if (data[i] != other.data[i])
            return false;
    }

    return true;
}

// 重载大于等于运算符
template <typename TYPE>
bool Myvector<TYPE>::operator>=(const Myvector &other)
{
    return (*this == other) || (*this > other);
}

// 重载小于或等于运算符
template <typename TYPE>
bool Myvector<TYPE>::operator<=(const Myvector &other)
{
    return (*this == other) || (*this < other);
}
 