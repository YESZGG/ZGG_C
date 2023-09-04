#if 1
#include <iostream>
using namespace std;
class MyClass
{
private:
    int value;

public:
    MyClass(int val) : value(val) {}

    MyClass operator+(const MyClass &other)
    {
        MyClass result(value + other.value);
        return result;
    }

    MyClass operator-(const MyClass &other)
    {
        MyClass result(value - other.value);
        return result;
    }

    int getValue()
    {
        return value;
    }
};

int main()
{
    MyClass obj1(5);
    MyClass obj2(3);

    MyClass obj3 = obj1 + obj2;                    // 使用重载的+运算符
    cout << "Result: " << obj3.getValue() << endl; // 输出：Result: 8

    MyClass obj4 = obj1 - obj2;                    // 使用重载的-运算符
    cout << "Result: " << obj4.getValue() << endl; // 输出：Result：2

    

    return 0
}
#endif

#if 0

#include <iostream>
using namespace std;

struct data
{
    int a;
};
// 重载 + 号赋予新的功能
struct data operator+(struct data v, struct data v1)
{
    struct data v2;
    v2.a = v.a + v1.a;

    return v2;
}
struct data operator-(struct data v, struct data v1)
{
    struct data v2;
    v2.a = v.a - v1.a;

    return v2;
}
struct data operator*(struct data v, struct data v1)
{
    struct data v2;
    v2.a = v.a * v1.a;

    return v2;
}
struct data operator/(struct data v, struct data v1)
{
    struct data v2;
    v2.a = v.a / v1.a;

    return v2;
}



int main()
{

    struct data v = {10};

    struct data v1 = {20};

    struct data v2 = v + v1;
    cout << v2.a << endl;

    // 重载 -  * /
    struct data v3 = v - v1;
    cout << v3.a << endl;

    struct data v4 = v * v1;
    cout << v4.a << endl;

    struct data v5 = v / v1;
    cout << v5.a << endl;

}
#endif
