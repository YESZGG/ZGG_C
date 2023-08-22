/*
 * @Description: 通过动态分配内存分配一个int数组，每个成员的值和它的下标一致，遍历数组并打印每个成员的值。
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-08-22 18:40:15
 * @LastEditors: ZGG
 * @LastEditTime: 2023-08-22 18:46:51
 */

#include <iostream>

int main()
{
    int size;
    std::cout << "请输入数组大小：";
    std::cin >> size;

    // 动态分配内存分配一个int数组
    int *arr = new int[size];

    // 给数组成员赋值
    for (int i = 0; i < size; i++)
    {
        arr[i] = i;
    }

    // 遍历数组并打印每个成员的值
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // 释放动态分配的内存
    delete[] arr;

    return 0;
}
