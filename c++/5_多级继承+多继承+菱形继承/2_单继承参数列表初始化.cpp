#include <iostream>
using namespace std;

class base
{
public:
    base(int a, float b) : a(a), b(b)
    {
    }
    void show_base()
    {
        cout << a << " " << b << " ";
    }

private:
    int a;
    float b;
};

class xbase : public base
{
public:
    xbase(int a, float b, char c) : base(a, b), c(c)
    {
    }
    void show_xbase()
    {
        base::show_base();
        cout << c << endl;
    }

private:
    char c;
};

int main()
{
    xbase temp(1, 2.1, 'b');
    temp.show_xbase();
}

