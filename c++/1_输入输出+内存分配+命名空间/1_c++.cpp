/*
 * @Description: c++第一天
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-08-22 14:35:40
 * @LastEditors: ZGG
 * @LastEditTime: 2023-08-22 15:28:23
 */
#include <iostream>// c++的头文件
// 在c++中使用标准c库 cstdio 把标准的c库头文件去掉.h在前面添加c
// 但是并不是都是需要这样子 有一些跟C库头文件一样 没有改变
#include <cstdio>

int main()
{
    // std::cout 相当于C语言的标准输出
    // std::endl 相当于C语言的 \n 换行符
    std::cout<<"hello world"<<std::endl;
    // 提问：c++中可不可以调用C库函数或者写C语言代码？？可以
    printf("hello world\n");

    return 0;
}