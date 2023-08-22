#include <iostream>
/* 
标准输入(standard input)与预定义的istream对象cin对应
标准输出(standard output)与预定义的ostream对象cout对应
标准出错(standard error)与预定义的的ostream对象cerr对应

c++ 输入输出流特点：
自适应数据类型(不像C语言需要通过格式控制符来区分)
可以连续操作(可以连续输入输出，自动区分数据类型)

字节对齐头文件 
#include <iomanip>
左对齐5个字节
std::cout<<std::setw(5)<<std::left<<str
右对齐5个字节
std::cout<<std::setw(5)<<std::right<<str 
*/

int main()
{
    char name[256] = {0};
    int age;
    float score;
    for (int i = 0; i < 3; i++)
    {
        std::cout << "请输入姓名 年龄 分数:" << std::endl;
        std::cin >> name >> age >> score;
        std::cout << "姓名：" << name << " "
                  << "年龄：" << age << " "
                  << "分数：" << score << std::endl;
    }
    return 0;
}