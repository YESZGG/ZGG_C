#include <iostream>
#include <cstring>

using namespace std;

#if 0
class Base
{
public:
    // 构造函数
    Base(const char *s, int size) // s 堆空间存储的字符串 , size 堆空间大小
    {
        this->str = new char[size];
        strcpy(this->str, s);
        this->size = size;
        cout << "堆空间地址：" << (void *)this->str << "\t"
             << "内容:" << str << "\t"
             << "size:" << size << endl;
    }

    // 重写拷贝构造函数 --- 深拷贝
    Base(const Base &tmp)
    {
        this->size = tmp.size;
        this->str = new char[this->size];
        strcpy(this->str, tmp.str);
        cout << "堆空间地址：" << (void *)this->str << "\t"
             << "内容:" << str << "\t"
             << "size:" << size << endl;
    }
    // 析构函数
    ~Base()
    {
        cout << "释放堆空间资源" << endl;
        delete[] str;
    }

private:
    char *str; // 指向一块堆空间
    int size;  // 堆空间大小
};

int main()
{
    Base temp("你好", 10);
    Base t = temp;

    return 0;
}
#endif

struct people
{
    char *name;
    int age;
};

class base
{
public:
    // 构造函数
    base(int v, const char *name, int age)
    {
        this->value = new int(v); // 分配了一块 int 类型的堆空间

        this->p = new struct people;// 分配了一块 struct people 类型的堆空间

        this->p->name = new char[1024];// 分配了 1024 块的 char 类型的堆空间

        this->p->age = age;

        strcpy(this->p->name, name);

        cout << "构造完毕" << endl;

        cout << *value << "\t" << this->p->name << "\t" << this->p->age << endl;
    }

    // 析构函数
    ~base()
    {
        cout << "释放内存空间资源" << endl;
        delete value;
        delete[] p->name;
        delete p;
    }
    // 拷贝构造
    base(const base &tmp) // 防止修改传递进来的 对象的值
    {
        this->value = new int(*(tmp.value));


        this->p = new struct people;

        this->p->name = new char[1024];
        strcpy(this->p->name, tmp.p->name);

        this->p->age = tmp.p->age;

        cout << "构造完毕" << endl;
        cout << *value << "\t" << this->p->name << "\t" << this->p->age << endl;
    }

private:
    int *value;
    struct people *p;
};

int main()
{
    base temp(10, "柱锦哥牛逼", 30);
    base t = temp;
}