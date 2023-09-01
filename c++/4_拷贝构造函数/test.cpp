/*
 * @Description: 一台电脑和一台打印机两个独立的类，电脑有显示、算数，
                打印机有打印功能，当组合在一起后，对于电脑类就可以调用打印机的打印功能。
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-08-25 16:19:05
 * @LastEditors: ZGG
 * @LastEditTime: 2023-08-25 16:40:18
 */
#if 1
#include <iostream>

using namespace std;


class Printer {
public:
    void print(int& message) const {
        cout << "打印机正在打印: " << message << endl;
    }
};

class Computer {
private:
    Printer printer;

public:
    void display() const {
        cout << "电脑正在显示内容" << endl;
    }

    int calculate(int a, int b) const {
        return a + b; // 假设这里进行加法运算
    }

    void usePrinter(int& message) const {
        printer.print(message);
    }
};

int main() {
    Computer computer;

    computer.display();
    int result = computer.calculate(3, 4);
    cout << "计算结果为: " << result << endl;

    computer.usePrinter(result);

    return 0;
}
#endif


/*
 * @Description: 设计一个圆形类（Circle），和一个点类（Point），计算点和圆的关系(判断该点是在圆内、圆外还是圆上)。
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-08-25 16:19:05
 * @LastEditors: ZGG
 * @LastEditTime: 2023-08-25 16:23:11
 */
#if 0
#include <iostream>
#include <cmath>

class Point
{
private:
    double x;// x 坐标值
    double y;// y 坐标值

public:
    Point(double _x, double _y) : x(_x), y(_y) {}

    double getX() const
    {
        return x;
    }

    double getY() const
    {
        return y;
    }
};

class Circle
{
private:
    Point center;
    double radius;// 半径

public:
    Circle(const Point &_center, double _radius) : center(_center), radius(_radius) {}

    double getRadius() const
    {
        return radius;
    }

    bool containsPoint(const Point &point) const
    {
        // 计算点到圆心的距离
        double distance = std::sqrt(std::pow(point.getX() - center.getX(), 2) + std::pow(point.getY() - center.getY(), 2));

        // 判断距离与半径的关系
        if (distance > radius)
        {
            return false; // 点在圆外
        }
        else if (distance < radius)
        {
            return true; // 点在圆内
        }
        else
        {
            return true; // 点在圆上
        }
    }
};

int main()
{
    // 创建一个圆对象
    Circle circle(Point(0, 0), 5.0);

    // 创建一个点对象
    Point point(5, 3);

    // 判断点和圆的关系
    if (circle.containsPoint(point))
    {
        std::cout << "点在圆内或在圆上" << std::endl;
    }
    else
    {
        std::cout << "点在圆外" << std::endl;
    }

    return 0;
}
#endif