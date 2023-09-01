#include <iostream>

using namespace std;

/*
设计一个基类（Shape），表达几何形状，并由它派生出圆（Circle）、矩形（Rectangle）两个子类。

基类包含成员数据：

位置坐标（x, y）
基类包含成员方法：

求面积（area）
求周长（perimeter）
显示相关信息（info）（比如图形的位置、圆的半径、矩形的边长等）

设计一个get_area(Shape *p )；函数实现求出不同图形的面积和周长，并显示当前图型的信息。
*/

class Shape
{
protected:
    double x; // 位置坐标 x
    double y; // 位置坐标 y

public:
    Shape(double x = 0, double y = 0) : x(x), y(y) {}

    virtual double area() // 求面积（纯虚函数）
    {
        cout << "求面积" << endl;
        return 0;
    }
    virtual double perimeter() // 求周长（纯虚函数）
    {
        cout << "求周长" << endl;
        return 0;
    }
    virtual void info() // 显示相关信息（纯虚函数）
    {
        cout << "相关信息" << endl;
    }
};

class Circle : public Shape
{
private:
    double radius; // 圆的半径

public:
    Circle(double x = 0, double y = 0, double radius = 0) : Shape(x, y), radius(radius) {}

    double area() // 求圆形面积
    {
        return 3.14159 * radius * radius;
    }

    double perimeter() // 求圆的周长
    {
        return 2 * 3.14159 * radius;
    }

    void info()
    {
        cout << "圆的位置: (" << x << ", " << y << "), 半径: " << radius << endl;
    }
};

class Rectangle : public Shape
{
private:
    double width;  // 矩形的宽
    double height; // 矩形的高

public:
    Rectangle(double x = 0, double y = 0, double width = 0, double height = 0)
        : Shape(x, y), width(width), height(height) {}

    double area() 
    {
        return width * height;
    }

    double perimeter() 
    {
        return 2 * (width + height);
    }

    void info() 
    {
        cout << "矩形的位置: (" << x << ", " << y << "), 宽度: " << width << ", 高度: " << height << endl;
    }
};

void get_area(Shape *p)
{
    cout << "面积: " << p->area() << endl;
    cout << "周长: " << p->perimeter() << endl;
    p->info();
}

int main()
{
    // Shape *s1 = new Circle(2, 3, 5);
    // Shape *s2 = new Rectangle(-1, -1, 4, 6);

    // get_area(s1); // 打印圆的面积、周长和信息
    // cout << endl;
    // get_area(s2); // 打印矩形的面积、周长和信息

    // delete s1;
    // delete s2;

    get_area(new Circle(2,3,5));
    cout << endl;
    get_area(new Rectangle(1,1,6,4));



    return 0;
}
 