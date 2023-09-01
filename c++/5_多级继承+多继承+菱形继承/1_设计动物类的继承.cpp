#include <iostream>
#include <cstring>

using namespace std;

/*
    设计一个基类动物类(属性︰体重，颜色，年龄     行为︰跑，吃，睡)，构造方法初始化属性
    设计一个猫类继承动物类(属性︰体重，颜色，年龄，品种  行为︰跑吃睡，抓老鼠，叫声)
    定义一个猫对象--咖菲猫，调用猫的叫，抓老鼠，输出猫的属性
*/

class Animal
{
protected:
    int weight;
    char color[10];
    int age;

public:
    Animal(int weight, const char *color, int age) : weight(weight), age(age)
    {
        strcpy(this->color, color);
    }
    void show_animal()
    {
        cout << "体重：" << weight << "kg，颜色：" << color << "，年龄：" << age << "岁";
    }
    void run()
    {
        // 运动的行为实现
        cout << "运动" << endl;
    }

    void eat()
    {
        // 进食的行为实现
        cout << "进食" << endl;
    }

    void sleep()
    {
        // 睡眠的行为实现
        cout << "睡觉" << endl;
    }
};
class Cat : public Animal
{
private:
    char breed[10]; // 品种

public:
    Cat(int weight, const char *color, int age, const char *breed) : Animal(weight, color, age)
    {
        strcpy(this->breed, breed);
    }
    void show_cat()
    {
        Animal::show_animal();
        cout << ", 品种：" << breed << endl;
    }

    void catchMouse()
    {
        // 抓老鼠的行为实现
        cout << breed << "在抓老鼠" << endl;
    }

    void meow()
    {
        // 叫的行为实现
        cout << breed << "喵喵喵" << endl;
    }
};

int main()
{
    Cat kitty(4, "白色", 2, "咖菲猫");
    kitty.meow();
    kitty.run();
    kitty.eat();
    kitty.sleep();
    kitty.catchMouse();
    kitty.show_cat();
}