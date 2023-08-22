#include <iostream>
#include <cstring>

int main()
{
    int val = 10; //C语言赋值 通常自己定义变量的时候用这种
    int val1(20);//C++也可以这样赋值 这种赋值在参数列表中用的表较多

    char c = 'a';
    char c1('b');

    float f = 3.14;
    float f1(3.14);


    char str[1024] = {0};
    strcpy(str,"hello");

    return 0;
}    