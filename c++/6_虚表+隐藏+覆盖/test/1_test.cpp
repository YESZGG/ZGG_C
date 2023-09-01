#include <iostream>
#include <cstring>

using namespace std;

/*
练习：设计一个运动会函数，不同的运动员，参加的运动项目不一样。
         void   do_sport(  sportsman *p  )  //运动会函数
        sportsman - >  派生田径，游泳，跳远 ..
*/

class sportsman
{
public:
    sportsman(const char *name = "无人")
    {
        strcpy(this->name, name);
    }
    virtual void do_sport()
    {
        cout << "无人参加运动会项目" << this->name << endl;
    }
    char name[20];
};

class athlete : public sportsman
{
public:
    athlete(const char *name = "无人") : sportsman(name) {}
    void do_sport() override
    {
        // 实现田径选手的运动项目
        cout << "田径运动项目--" << this->name << " 参赛 " << endl;
    }
};

class swimmer : public sportsman
{
public:
    swimmer(const char *name = "无人") : sportsman(name) {}
    void do_sport() override
    {
        // 实现游泳选手的运动项目
        cout << "游泳运动项目--" << this->name << " 参赛 " << endl;
    }
};

class long_jumper : public sportsman
{
public:
    long_jumper(const char *name = "无人") : sportsman(name) {}
    void do_sport() override
    {
        // 实现跳远选手的运动项目
        cout << "跳远运动项目--" << this->name << " 参赛 " << endl;
    }
};

void do_sport(sportsman *p)
{
    p->do_sport(); // 多态性：根据实际指向的对象类型调用相应的函数
}

int main()
{
    sportsman *s1 = new athlete("张三");
    sportsman *s2 = new swimmer("李四");
    sportsman *s3 = new long_jumper("王五");

    do_sport(s1); // 田径运动项目--张三 参赛
    do_sport(s2); // 游泳运动项目--李四 参赛
    do_sport(s3); // 跳远运动项目--王五 参赛

    delete s1;
    delete s2;
    delete s3;

    return 0;
}
