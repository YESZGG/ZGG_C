#include "table.h"

Table::Table()
{
    cout << m_length << " " << m_width << " " << m_height << " " << m_color << endl;
}
Table::Table(double length, double width, double height, int color)
{
    m_length = length;
    m_width = width;
    m_height = height;
    m_color = color;
}

Table::~Table()
{
}

void Table::setLength(double &length)
{
    m_length = length;
}

void Table::setColor(Table::Color c)
{
    m_color = c;
}

void Table::setPrice(Table::Price p)
{
    price = p;
}

int Table::getColor()
{
    return m_color;
}

void Table::printfInfo()
{
    cout << "长度：" << m_length << "\t宽度：" << m_width << "\t高度：" << m_height << "价格：" << price << endl;

    switch (m_color)
    {
    case Table::GREEN:
        cout << "绿色" << endl;
        break;
    case Table::RED:
        cout << "红色" << endl;
        break;

    default:
        break;
    }
}