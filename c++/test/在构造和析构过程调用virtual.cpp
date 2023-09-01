#include <iostream>
using namespace std;

class Base
{
public:
    Base()
    {
        std::cout << "Base constructor\n";
        virtualFunc();
    }

    virtual ~Base()
    {
        std::cout << "Base destructor\n";
        virtualFunc();
    }

    virtual void virtualFunc()
    {
        std::cout << "Base virtual function\n";
    }
};

class Derived : public Base
{
public:
    Derived()
    {
        std::cout << "Derived constructor\n";
        virtualFunc();
    }

    ~Derived()
    {
        std::cout << "Derived destructor\n";
        virtualFunc();
    }

    void virtualFunc() override
    {
        std::cout << "Derived virtual function\n";
    }
};

int main()
{
    Derived derivedObj;
    return 0;
}
