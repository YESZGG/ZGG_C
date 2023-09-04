#include <iostream> 

using namespace std;

class MyClass
{
private:
    int value;

public:
    MyClass(int val) : value(val) {}

    bool operator||(const MyClass &other)
    {
        if(this->value || value)
        {
            return true;
        }
        else
            return false;
    }

    bool operator!()
    {
        if(!this->value)
        {
            return true;
        }
        else
            return false;
    }

    int getValue()
    {
        return value;
    }
};


int main()
{
    MyClass obj1(10);
    MyClass obj2(20);

    cout << (obj1 || obj2 ? "obj1 与 obj2 其中有一个为真" : "obj1 与 obj2 都为假") << endl;
    cout << (!obj1 ? "!obj1 为真" : "!obj1 为假") << endl;
}