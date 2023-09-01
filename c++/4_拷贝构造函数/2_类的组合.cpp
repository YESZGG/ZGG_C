#include <iostream>
#include <cstring>
using namespace std;

// 手机类
class Phone
{
public:
    Phone()
    {
        strcpy(this->p_name, p_name);
        cout << "Phone() 构造函数" << endl;
    }
    Phone(const char *p_name)
    {
        strcpy(this->p_name, p_name);
        cout << "Phone(const char*p_name) 构造函数" << endl;
    }

    ~Phone()
    {
        cout << "~Phone() 析构函数" << endl;
    }

    void setName(const char *name)
    {
        strcpy(this->p_name, name);
    }
    char *getName()
    {
        return this->p_name;
    }

private:
    char p_name[256];
};

// 饭卡类
class Card
{
public:
    Card(int n)
    {
        this->n = n;
        cout << "Card() 构造函数" << endl;
    }
    Card(int n, int m)
    {
        this->n = n;
        cout << "Card() 构造函数" << endl;
    }
    ~Card()
    {
        cout << "~Card() 析构函数" << endl;
    }

private:
    int n;
};


// 类的组合构造顺序问题: 构造顺序只和定义对象顺序的有关，和初始化参数列表无关 
// 学生类
class Student
{
public:
    // 在参数列表中指定 内嵌对象的构造函数
    Student(const char *name) :myPhone("华为mate60"), myCard(100)
    {
        strcpy(this->name, name);
        cout << "Student() 构造函数" << endl;
    }
    ~Student()
    {
        cout << "~Student() 析构函数" << endl;
    }
    void player()
    {
        cout << this->name << "正在玩手机,手机的牌子是" << myPhone.getName() << endl;
    }
    void setPhone(const char *p_name)
    {
        myPhone.setName(p_name);
    }

private:
    char name[256];// 学生姓名
    int age;// 年龄
    // 类的数据成员 中 有 另一个类的对象  --内嵌对象
    // 构造函数执行次序： 内嵌对象----》本类对象

    Phone myPhone; // 手机类的对象
    Card myCard;   // 饭卡
};

int main()
{
    // 实例化学生类的对象
    Student s1("张3");
    s1.player();
    s1.setPhone("华为");
    s1.player();

    return 0;
}