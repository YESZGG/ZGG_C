#include <iostream>

using namespace std;

#if 0
class MyClass {
public:
    int num;
    double value;
    char ch;
};

int main() {
    std::cout << "Size of MyClass: " << sizeof(MyClass) << " bytes" << std::endl;
    return 0;
}
#endif

#if 0
class MyClass {
public:
    int num;
    double value;

    // 默认构造函数
    MyClass() {
        num = 0;
        value = 0.0;
    }

    // 带参数的构造函数
    MyClass(int n, double v) {
        num = n;
        value = v;
    }
};

int main() {
    // 创建类对象时自动调用构造函数进行初始化
    MyClass obj1;              // 调用默认构造函数
    MyClass obj2(10, 3.14);     // 调用带参数的构造函数

    std::cout << "obj1: num - " << obj1.num << ", value - " << obj1.value << std::endl;
    std::cout << "obj2: num - " << obj2.num << ", value - " << obj2.value << std::endl;

    return 0;
}

#endif

#if 0
 
class Line
{
   public:
      int getLength( void );
      Line( int len );             // 简单的构造函数
      Line( const Line &obj);      // 拷贝构造函数
      ~Line();                     // 析构函数
 
   private:
      int *ptr;
};
 
// 成员函数定义，包括构造函数
Line::Line(int len)
{
    cout << "调用构造函数" << endl;
    // 为指针分配内存
    ptr = new int;
    *ptr = len;
}
 
Line::Line(const Line &obj)
{
    cout << "调用拷贝构造函数并为指针 ptr 分配内存" << endl;
    ptr = new int;
    *ptr = *obj.ptr; // 拷贝值
}
 
Line::~Line(void)
{
    cout << "释放内存" << endl;
    delete ptr;
}
int Line::getLength( void )
{
    return *ptr;
}
 
void display(Line obj)
{
   cout << "line 大小 : " << obj.getLength() <<endl;
}
 
// 程序的主函数
int main( )
{
   Line line(10);
 
   display(line);
 
   return 0;
}
#endif

#if 1
// 祖先类：交通工具
class Vehicle
{
    string trade;

public:
    Vehicle(string t = "null") : trade(t) {}
    void company() const { cout << "生产厂商：" << trade << endl; }
};
// 汽车，虚继承了交通工具
// 确保汽车类作为后代多重继承的父类之一时不再自动构建Vehicle类组件
class Car : virtual public Vehicle
{
    int x;

public:
    // 汽车类的初始化列表中，调用了Vehicle的构造函数
    // 此构造函数在汽车类作为后代多重继承的父类之一时不会被自动调用
    Car(int x = 0, string t = "null") : Vehicle(t), x(x) {}
    void show() { cout << x << endl; }
};

// 船只，虚继承了交通工具
// 确保船只类作为后代多重继承的父类之一时不再自动构建Vehicle类组件
class Boat : virtual public Vehicle
{
    float y;

public:
    // 船只类的初始化列表中，调用了Vehicle的构造函数
    // 此构造函数在船只类作为后代多重继承的父类之一时不会被自动调用
    Boat(float y = 0.0, string t = "null") : Vehicle(t), y(y) {}
    void show() { cout << y << endl; }
};

class AmphibiousVehicle : public Car, public Boat
{
public:
    AmphibiousVehicle(string t = "null", int x = 0, float y = 0.0)
        : Vehicle(t), Car(x), Boat(y)
    {
    }
};

int main(int argc, char const *argv[])
{
    AmphibiousVehicle v("中国兵器工业集团有限公司", 100, 1.23);
    v.company();

    return 0;
}
#endif