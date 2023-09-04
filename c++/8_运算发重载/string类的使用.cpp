#include <iostream>
using namespace std;

int main()
{
#if 0   
    string s = "hello";
    string s2 = "world";
    // 比较
    if (s == s2)
    {
        cout << "字符串相等" << endl;
    }
    else
    {
        cout << "字符串不相等" << endl;
    }

    // 拼接
    string s3 = s + s2;
    cout << s3 << endl;

    // 追加
    s += "你好";
    cout << s << endl;

    // 取下标
    cout << s[2] << endl;
#endif
#if 0
    string s = "hello";

    // 追加
    s.append("world");
    cout << s << endl; // helloworld

    // 转换为char *
    const char *p = s.c_str();
    cout << p << endl; // helloworld

    // 拷贝
    char buf[1024];
    s.copy(buf, 3, 2);
    cout << buf << endl; // llo

    // 删除
    s.erase(2, 3);
    cout << s << endl; // heworld

    // 查找
    int loc = s.find("wor", 0);
    cout << loc << endl;

    s.append("wor"); // heworldwor
    // 逆向查找
    loc = s.rfind("or");
    cout << loc << endl;

    // 插入
    s.insert(1, "ABC"); // hABCeworldwor
    cout << s << endl;

    // 计算字符串长度
    cout << s.length() << endl;

    // 替换
    s.replace(5, 3, "123");
    cout << s << endl;

    //提取内容
    cout << s.substr(2, 3) << endl;
#endif

    string s = "They say he carved it himself...from a BIGGER spoon";
    string s2 = "find your soul-mate, Homer.";

    cout << s.length() << endl;
    cout << s2.length() << endl;
    s.replace(32, 10, s2);

    cout << s << endl;
    cout << s.length() << endl;
}
