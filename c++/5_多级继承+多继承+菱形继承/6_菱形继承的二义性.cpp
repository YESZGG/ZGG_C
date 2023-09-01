#include <iostream>
using namespace std;

class base
{
public:
    void show() // 函数成员
    {
        cout << "show base"
             << " "
             << "value:" << value << endl;
    }
    int value; // 数据成员
};
class base_a : public base
{
};

class base_b : public base
{
};

class base_c : public base_a, public base_b
{
public:
    void show() // 函数成员
    {
        cout << "show base_c "
             << " "
             << "value:" << value << endl;
    }
    int value; // 数据成员
};

int main()
{
    base_c tmp;    
    tmp.base_a::value = 10010;
    tmp.base_a::show();

    tmp.base_b::value = 1221;
    tmp.base_b::show();

    tmp.value = 10010;
    tmp.show(); // show  base_c

}