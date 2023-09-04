#ifndef STRING_H_
#define STRING_H_

#include <iostream>
using namespace std;

#define size_type unsigned long

static const size_type npos = -1;

class Mystring
{
private:
    char *str;
    size_type length;
    size_type num;
    size_type index;

public:
    // 默认构造函数
    Mystring() {}
    // 拷贝构造函数
    Mystring(const Mystring &other);
    // 构造函数重载
    Mystring(const char *str);
    Mystring(size_type length, const char str);
    Mystring(const char *str, size_type length);
    Mystring(Mystring &str, unsigned index, unsigned length);
    ~Mystring()
    {
        delete[] str;
    }

    /*-----------------------------工具---------------------------------*/
    // 计算字符串类的长度
    size_type mystrlen(const char *str);

    /*----------------------------成员函数-------------------------------*/
    // 返回以 NULL 字符('\0') 结尾的 C 风格字符串指针
    const char *c_str();

    /*
        size_type copy(char* str, size_type num, size_type index)

        str：指向将存储复制字符的目标字符数组的指针。
        num：要从字符串复制的最大字符数。它表示目标字符数组的长度。
        index：字符串中应从复制过程开始的起始位置。
        返回值：
            返回从字符串复制的实际字符数。
    */
    size_type copy(char *str, size_type num, size_type index);

    // 以追加方式添加字符串到字符串对象中
    Mystring &append(const char *str);

    // 插入 从 index 位置插入 str 字符串
    Mystring &insert(size_type index, const char *str);

    // 删除从 index 索引开始的 num 个字符，返回 *this
    Mystring &erase(size_type index = 0, size_type num = npos);

    // 返回str在字符串中第一次出现的位置(从index开始查找)，如果没有找到则返回
    size_type find(const char *str, size_type index);
    // 在从指定索引位置开始的子字符串中搜索另一个字符串对象，并返回第一次出现的位置索引。
    size_type find(const Mystring &str, size_type index);

    // 返回最后一个与str中的某个字符匹配的字符，从index开始查找。如果没找到就返回string::npos
    size_type rfind(const char *str, size_type index);

    // 在从指定索引位置的子字符串中从后往前搜索另一个字符串对象，并返回第一次出现的位置索引。
    size_type rfind(const Mystring &str, size_type index);

    // 用str中的num个字符（从index开始）替换本字符串中的字符
    Mystring &replace(size_type index, size_type num, const char *str);

    // 用str对象中的num个字符（从index开始）替换本字符串中的字符
    Mystring &replace(size_type index, size_type num, const Mystring &str);

    // 返回本字符串的一个子串，从index开始，长num个字符。如果没有指定，将是默认值 string::npos。
    Mystring substr(size_type index, size_type num = npos);

    /*--------------------------重载运算符--------------------------------*/
    // 重载 < 关系运算符
    friend bool operator<(const Mystring ch1, const Mystring ch2);

    // 重载 > 关系运算符
    friend bool operator>(const Mystring ch1, const Mystring ch2);

    // 重载 == 关系运算符
    friend bool operator==(const Mystring ch1, const Mystring ch2);

    // 重载 += 赋值运算符
    Mystring &operator+=(const Mystring &ch1);

    // 重载 += 赋值运算符
    Mystring &operator+=(const char *str);

    // 重载 + 双目运算符
    friend Mystring operator+(const Mystring &ch1, const Mystring &ch2);

    char &operator[](size_type index);

    // 重载 输出流运算符
    friend ostream &operator<<(ostream &os, const Mystring &mystr);
};
#endif