#if 0
#include <iostream>
#include <cmath>

using namespace std;

class conicalVolume
{
private:
    double r;
    double h;

public:
    void setRadius(double radius);
    void setHeight(double height = 1);
    void circleArea();
    void coneVolume();
};

void conicalVolume::setRadius(double radius)
{
    r = radius;
}

void conicalVolume::setHeight(double height)
{
    h = height;
}

void conicalVolume::circleArea()
{
    double area = 3.14 * r * r;
    cout << "Circle Area = " << area << endl;
}

void conicalVolume::coneVolume()
{
    double volume = (1 / 3.0) * M_PI * pow(r, 2) * h;
    cout << "coneVolume = " << volume << endl;
}

int main()
{
    conicalVolume cone;
    cone.setRadius(2.0);
    cone.setHeight(2.0);
    cone.circleArea();
    cone.coneVolume();

    return 0;
}
#endif

#if 0
#include <iostream>
#include <cmath>

class Cone {
private:
    double radius;
    double height;

public:
    // 构造函数，默认高度为1
    Cone(double r, double h = 1.0)
        : radius(r), height(h) {}

    // 计算圆锥体积
    double getVolume() const {
        return (1.0 / 3.0) * M_PI * pow(radius, 2) * height;
    }
};

int main() {
    double radius, height;
    std::cout << "Enter the radius of the cone: ";
    std::cin >> radius;
    std::cout << "Enter the height of the cone (default is 1): ";
    std::cin >> height;

    Cone cone(radius, height);
    std::cout << "The volume of the cone is: " << cone.getVolume() << std::endl;

    return 0;
}

#endif

#if 1

#include <iostream>

class Time
{
private:
    int hours;
    int minutes;
    int seconds;

public:
    // 构造函数，默认时间为00:00:00
    Time() : hours(0), minutes(0), seconds(0) {}

    // 设置时间
    void setTime(int h, int m, int s)
    {
        if (h >= 0 && h < 24 && m >= 0 && m < 60 && s >= 0 && s < 60)
        {
            hours = h;
            minutes = m;
            seconds = s;
        }
        else
        {
            std::cout << "Invalid time!" << std::endl;
        }
    }

    // 显示时间
    void displayTime() const
    {
        std::cout << "Current time: ";
        if (hours < 10)
            std::cout << "0";
        std::cout << hours << ":";
        if (minutes < 10)
            std::cout << "0";
        std::cout << minutes << ":";
        if (seconds < 10)
            std::cout << "0";
        std::cout << seconds << std::endl;
    }
};
int main()
{
    Time t;
    t.displayTime(); // 输出 Current time: 00:00:00

    t.setTime(12, 34, 56);
    t.displayTime(); // 输出 Current time: 12:34:56

    t.setTime(99, 88, 77); // 输出错误信息：Invalid time!

    return 0;
}

#endif