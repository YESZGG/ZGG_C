#include <iostream>
#include <cstring>
using namespace std;

/* /定义一个狗类，包含品种，颜色，年龄，重载狗的输出函数!*/
class dog
{
public:
    dog(const char *dog_name, const char *color, const int age, const char *variety) : age(age)
    {
        strcpy(this->dog_name, dog_name);
        strcpy(this->color, color);
        strcpy(this->variety, variety);
    }
    friend ostream &operator<<(ostream &os, const dog &obj);
    friend istream &operator>>(istream &ci,dog &obj);

private:
    char dog_name[10];
    char color[10];
    int age;
    char variety[10];
};

ostream &operator<<(ostream &os, const dog &obj)
{
    os << "🐕名:" << obj.dog_name << " "
       << "🐕颜色:" << obj.color << " "
       << "年龄:" << obj.age << " "
       << "品种:" << obj.variety << endl;
    return os;
}

istream &operator>>(istream &is,dog &obj)
{
    is >> obj.dog_name >> obj.color >> obj.age >> obj.variety;
    return is;
}


int main()
{

    dog obj("旺财", "黄色", 2, "土狗");

    // 在c++中，cout 对象是不允许产生 临时副本的！ 但是可以取别名，使用引用
    cout << obj << endl;
    cin >> obj;
    cout << obj << endl;

}


#if 0
#include <iostream>

class MyClass {
private:
    int value;

public:
    MyClass() : value(0) {}

    friend std::istream& operator>>(std::istream& is, MyClass& obj) {
        is >> obj.value;
        return is;
    }

    int getValue() const {
        return value;
    }
};

int main() {
    MyClass obj;

    std::cout << "请输入一个整数: ";
    std::cin >> obj;

    std::cout << "输入的值为: " << obj.getValue() << std::endl;

    return 0;
}
#endif