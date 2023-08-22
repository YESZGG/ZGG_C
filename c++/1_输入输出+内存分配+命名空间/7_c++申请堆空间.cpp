#include <iostream>
#include <cstdlib>

int main()
{
    // int *p = malloc(sizeof(int)); //error
    int *p = (int *)malloc(sizeof(int)); // OK
    free(p);                             // 释放单个对象

    // 申请堆空间
    int *p1 = new int;
    *p1 = 10;
    std::cout << "*p1:" << *p1 << std::endl;
    delete p1;

    // 申请堆空间同时赋值
    int *p2 = new int(20);
    std::cout << "*p2:" << *p2 << std::endl;
    delete p2;

    // 申请连续的堆空间相当于数组 == int arr[5]
    int *p3 = new int[5];
    *p3 = 30; // 指针偏移赋值
    *(p3 + 1) = 31;
    *(p3 + 2) = 32;
    std::cout << *p3 << " " << *(p3 + 1) << " " << *(p3 + 2) << std::endl;

    p3[0] = 300; // 数组下标赋值
    p3[1] = 301;
    p3[2] = 302;
    std::cout << p3[0] << " " << p3[1] << " " << p3[2] << std::endl;
    delete[] p3; // 释放连续的多个对象

    int arr[2][3] = {10, 20, 30,
                     40, 50, 60};

    // 数值指针
    // 给指针p申请了3个int[5]类型的数组
    int(*p5)[5] = new int[3][5]; // 二维数组
    delete[] p5;

    return 0;
}



