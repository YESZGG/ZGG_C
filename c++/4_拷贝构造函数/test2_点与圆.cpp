#include <iostream>

using namespace std;

/*
    圆心 <----> 点
设计思路：
    在圆的类里面 通过点的对象来给它的圆心初始化
*/

// 点类
class Point
{
public:
    Point(){}
    ~Point(){}

    // 设置X坐标
    void setX(int x)
    {
        m_x = x;
    }
    // 获取X坐标
    int getX()
    {
        return m_x;
    }
    // 设置Y坐标
    void setY(int y)
    {
        m_y = y;
    }
    // 获取Y坐标
    int getY()
    {
        return m_y;
    }

private:
    int m_x;
    int m_y;
};

// 设置一个圆类Circle
class Circle
{
public:
    Circle(){}
    ~Circle(){}

    // 设置半径
    void setR(int r)
    {
        m_R = r;
    }
    // 获取半径
    int getR()
    {
        return m_R;
    }
    // 设置圆心
    void setCenter(Point center)
    {
        m_center = center;
    }
    // 获取圆心
    Point getCenter() // m_center是Piont类的数据
    {
        return m_center;
    }

private:
    int m_R;
    // 在类中可以让另一个类 作为本类中的成员--与结构体相似
    Point m_center; //圆心点
};

// 判断点和圆的关系---子函数
//c.getCenter() --->点的对象
//c.getCenter().getX()--->点的对象里面获取x轴的公有方法getX()
void isInCircle(Circle &c, Point &p)
{
    if ((p.getX() - c.getCenter().getX()) * (p.getX() - c.getCenter().getX()) + (p.getY() - c.getCenter().getY()) * (p.getY() - c.getCenter().getY()) == c.getR() * c.getR())
        cout << "点在圆上" << endl;
    else if ((p.getX() - c.getCenter().getX()) * (p.getX() - c.getCenter().getX()) + (p.getY() - c.getCenter().getY()) * (p.getY() - c.getCenter().getY()) > c.getR() * c.getR())
        cout << "点在圆外" << endl;
    else
        cout << "点在圆内" << endl;
}

int main()
{
    // 创建并设置点P1 (P1使用来判断是否在圆内和圆外的点) (10,9)
    Point P1;
    P1.setX(10);
    P1.setY(9);

    // 创建并设置点P2--(P2是用来作为圆的圆心)  (10,0)
    Point P2;
    P2.setX(10);
    P2.setY(0);

    // 设置圆C1  r=10
    Circle C1;
    C1.setR(10);
    C1.setCenter(P2); //设置圆心

    isInCircle(C1, P1);

    // system("pause");
    return 0;
}


