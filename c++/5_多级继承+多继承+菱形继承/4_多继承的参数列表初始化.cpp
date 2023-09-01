#include <iostream>
#include <cstring>

using namespace std;

class base_a
{
public:
    base_a(const char *str)
    {
        strcpy(this->str, str);
        cout << "str: " << str << endl;
    }

private:
    char str[1024];
};

class base_b
{
public:
    base_b(float f) : f(f)
    {
        cout << "f: " << f << endl;
    }

private:
    float f;
};

class base_c : public base_a, public base_b
{
public:
    base_c(const char *str, float b, const char *p, int size) : base_a(str), base_b(b), size(size)
    {
        this->p = new char[size];
        strcpy(this->p, p);
    }
    ~base_c()
    {
        cout << "~base_c 析构函数" << endl;
        delete[] p;
    }
    void show_base_c()
    {
        cout << "p的内容为：" << p << " "
             << "大小：" << size << endl;
    }

private:
    char *p; // 指向大小为size的堆空间
    int size;
};

int main()
{
    base_c temp("你好", 3.14, "ikun", 10);
    temp.show_base_c();
}

