#include <iostream>
#include <cstring>

using namespace std;

class base
{
public:
    base(const char *str, char a) : a(a)
    {
        strcpy(this->str, str);
    }
    void show_base()
    {
        cout << "base：" << str << " " << a << endl;
    }

private:
    char str[1024];
    char a;
};

class base_a : public base
{
public:
    base_a(const char *str, char a, float b) : base(str, a), b(b)
    {
    }
    void show_base_a()
    {
        base::show_base();
        cout << "base_a：" << b << endl;
    }

private:
    float b;
};

class base_b : public base_a
{
public:
    base_b(const char *str, char a, float b, int c, short d) : base_a(str, a, b), c(c), d(d)
    {
    }
    void show_base_b()
    {
        base_a::show_base_a();
        cout << "base_b：" << c << " " << d << endl;
    }

private:
    int c;
    short d;
};

int main()
{
    base_b temp("张三", 'M', 170.5, 34, 112);
    temp.show_base_b();

    return 0;
}
