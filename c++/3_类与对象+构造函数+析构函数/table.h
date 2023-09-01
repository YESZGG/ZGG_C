/*
 * @Description:
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-08-24 15:01:51
 * @LastEditors: ZGG
 * @LastEditTime: 2023-08-24 15:42:43
 */
#ifndef TABLE_H_
#define TABLE_H_

#include <iostream>

using namespace std;

/*
练习:设计一个桌子类，构造函数使用函数重载和带默认参数，实例化该类的对象，并且调用函数成员属性:长宽高、颜色、价格、....
行为:显示价格、设置颜色、设置长宽高
*/

// 桌子类设计
class Table
{
private:
    double m_length; // 长度
    double m_width;  // 宽度
    double m_height; // 高度
    int m_color;     // 颜色
    int price;       // 价格
public:
    enum Color
    {
        GREEN = 0x0000FF00, // 绿色
        RED = 0x00FF0000    // 红色
    };
    enum Price
    {
        ONE = 100,
        TWO,
        THREE
    };
    // 构造函数
    Table();
    // 构造函数
    Table(double length, double width, double height, int color);
    // 析构函数
    ~Table();

    // 行为
    void setLength(double &length);
    void setColor(enum Color c);
    void setPrice(enum Price p);
    int getColor();
    void printfInfo();
};

#endif