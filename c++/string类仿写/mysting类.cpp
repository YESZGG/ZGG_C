#include "string.h"

using namespace std;

int main()
{
    int loc = 0;
    Mystring str("Hello World");
    cout << "普通构造函数: " << str << endl;
    cout << endl;
#if 0
    Mystring str1 = str;
    cout << "深拷贝: " << str1 << endl;
    cout << endl;

    Mystring str2("Hello World", 2);
    cout << "将指定长度的字符从 str 中复制到字符串对象中:" << str2 << endl;
    cout << endl;

    cout << "== 关系运算符重载: " << (str == str1 ? "str 与 str1 字符串相等" : "str 与 str1 字符串不相等") << endl;
    cout << endl;

    // cout << (str < str2 ? "str 小于 str2  " : "str 不小于 str2") << endl;
    cout << "> 关系运算符重载: " << (str > str2 ? "str 大于 str2  " : "str 小于 str2") << endl;
    cout << endl;

    Mystring str3(str, 6, 5);
    cout << "从给定的索引位置开始，连续复制指定长度的字符到字符串对象中: " << str3 << endl;
    cout << endl;

    Mystring str4(5, 'A');
    cout << "将指定的字符 str 重复 length 次赋值给该字符串: " << str4 << endl;
    cout << endl;

    cout << "源字符串：" << str4 << endl;
    str4.append("world");
    cout << "追加: " << str4 << endl;
    cout << endl;
#endif
#if 0
    const char *cstring = str.c_str();
    cout << "返回一个指向正规C字符串的指针: " << cstring << endl;
    cout << endl;

    char dest[11];
    size_t numCopied = str.copy(dest, 5, 6);
    dest[numCopied] = '\0';
    cout << "拷贝自己的num个字符到str中（从索引index开始）: " << dest << endl; // 输出：World
    cout << endl;

    cout << "源字符串：" << str << endl;
    str.erase(6, 5);
    cout << "删除后的字符串：" << str << endl;
    cout << endl;

    cout << "源字符串: " << str << endl;
    str.insert(2, "World!");
    cout << "插入后的字符串：" << str << endl;
    cout << endl;

    loc = str.find("Wo", 0);
    cout << "size_type find(const char *str, size_type index) " << loc << endl;
    cout << endl;

    loc = str.find(str2, 0);
    cout << "size_type find(const Mystring &str, size_type index) " << loc << endl;
    cout << endl;
#endif

    Mystring str5("abcd ABCD sdsd ab EBcds dsc");
    loc = str5.rfind("ab", 20);
    cout << "size_type rfind(const char *str, size_type index) " << loc << endl;
    cout << endl;

    Mystring s = "They say he carved it himself...from a BIGGER spoon";
    Mystring s2 = "find your soul-mate, Homer.";

    s.replace(32, 19, s2);
    cout << s << endl;
    
    Mystring s3 = s.substr(32);
    cout << s3 << endl;    

    Mystring s4 = str + s3;
    cout << s4 << endl;

    cout << s4[1] << endl;
}