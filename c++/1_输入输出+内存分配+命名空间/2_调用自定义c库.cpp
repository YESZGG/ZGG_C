#include <iostream>

extern "C"// 必须要大写
{
    // 标准C库函数的头文件
    #include <string.h>
    #include <stdio.h>

    // 也就是你使用的C编译器好的库对应的头文件
    #include "add.h"
    /*
    /usr/bin/ld: /tmp/cckTofc7.o: in function `main':
    2_调用自定义c库.cpp:(.text+0x2e): undefined reference to `add(int, int)'
    collect2: error: ld returned 1 exit status
    */
}
/*  提问：在c++程序中，如何引用C程序 或者 extern "C" 的作用是什么？
    extern "C" 的主要作用就是为了能够正确实现C++代码调用其他C语言代码。
    加上 extern "C" 后，会指示编译器这部分代码按C语言进行编译，而不是c++ 
*/
int main()
{
    std::cout << "add(10,20):" << add(10, 20) << std::endl;

    printf("c++ easy\n");

    char buf[1024] = {0};
    strcpy(buf, "c++ easy");

    return 0;
}

/* gcc -fpic -shared add.c -o libadd.so 编译动态库文件 */