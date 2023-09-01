#include <iostream>

using namespace std;

/*
public：公共。该类或非该类均可访问
private：私有的。只有在类的主体中才可以访问。只能修饰属性和方法，不能修饰类
protected：受保护。该类及子类的成员均可以访问，同一个包中的类也可以访问。只能修饰属性和方法，不能修饰类
            默认：不使用修饰符。只有相同包中的类才可以访问

*/
#if 1
class Student
{

private:// 私有数据成员
    std::string name;      // 学生姓名
    int age;               // 年龄
    std::string gender;    // 性别
    std::string studentID; // 学生学号

public:
    // 构造函数
    Student(const std::string &n, int a, const std::string &g, const std::string &id)
        : name(n), age(a), gender(g), studentID(id) {}

    // 获取姓名
    std::string getName() const
    {
        return name;
    }

    // 获取年龄
    int getAge() const
    {
        return age;
    }

    // 获取性别
    std::string getGender() const
    {
        return gender;
    }

    // 获取学号
    std::string getStudentID() const
    {
        return studentID;
    }

    // 设置姓名
    void setName(const std::string &n)
    {
        name = n;
    }

    // 设置年龄
    void setAge(int a)
    {
        age = a;
    }

    // 设置性别
    void setGender(const std::string &g)
    {
        gender = g;
    }

    // 设置学号
    void setStudentID(const std::string &id)
    {
        studentID = id;
    }
};

int main()
{
    Student student1("Alice", 18, "Female", "S001");
    std::cout << "Name: " << student1.getName() << std::endl;
    std::cout << "Age: " << student1.getAge() << std::endl;
    std::cout << "Gender: " << student1.getGender() << std::endl;
    std::cout << "Student ID: " << student1.getStudentID() << std::endl;
}
#endif

#if 0
class Player
{
private:
    std::string name;
    int level;
    int health;
    int attackPower;

public:
    // 构造函数
    Player(const std::string &n, int l, int h, int ap)
        : name(n), level(l), health(h), attackPower(ap) {}

    // 获取姓名
    std::string getName() const
    {
        return name;
    }

    // 获取等级
    int getLevel() const
    {
        return level;
    }

    // 获取健康值
    int getHealth() const
    {
        return health;
    }

    // 获取攻击力
    int getAttackPower() const
    {
        return attackPower;
    }

    // 设置姓名
    void setName(const std::string &n)
    {
        name = n;
    }

    // 设置等级
    void setLevel(int l)
    {
        level = l;
    }

    // 设置健康值
    void setHealth(int h)
    {
        health = h;
    }

    // 设置攻击力
    void setAttackPower(int ap)
    {
        attackPower = ap;
    }

    // 玩家攻击另一个玩家
    void attack(Player &target)
    {
        // 根据自己的攻击力减少目标玩家的健康值
        target.health -= attackPower;
    }
};
int main()
{
    Player player1("Player 1", 10, 100, 20);
    std::cout << "Name: " << player1.getName() << std::endl;
    std::cout << "Level: " << player1.getLevel() << std::endl;
    std::cout << "Health: " << player1.getHealth() << std::endl;
    std::cout << "Attack Power: " << player1.getAttackPower() << std::endl;

    Player player2("Player 2", 8, 120, 15);
    player1.attack(player2);
    std::cout << "Player 2 Health after attack: " << player2.getHealth() << std::endl;

    return 0;
}
#endif

#if 0
class Hero
{
private:
    std::string name;
    int health;
    int damage;

public:
    // 构造函数
    Hero(const std::string &n, int h, int d)
        : name(n), health(h), damage(d) {}

    // 获取姓名
    std::string getName() const
    {
        return name;
    }

    // 获取健康值
    int getHealth() const
    {
        return health;
    }

    // 获取攻击力
    int getDamage() const
    {
        return damage;
    }

    // 设置姓名
    void setName(const std::string &n)
    {
        name = n;
    }

    // 设置健康值
    void setHealth(int h)
    {
        health = h;
    }

    // 设置攻击力
    void setDamage(int d)
    {
        damage = d;
    }

    // 英雄进行攻击
    void attack(Hero &target)
    {
        // 根据自己的攻击力减少目标英雄的健康值
        target.health -= damage;
    }
};
int main()
{
    Hero luBan("鲁班", 100, 20);
    std::cout << "Name: " << luBan.getName() << std::endl;
    std::cout << "Health: " << luBan.getHealth() << std::endl;
    std::cout << "Damage: " << luBan.getDamage() << std::endl;

    Hero hanBing("寒冰", 120, 15);
    luBan.attack(hanBing);
    std::cout << "寒冰 Health after attack: " << hanBing.getHealth() << std::endl;
    return 0;
}

#endif