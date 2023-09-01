#include <iostream>
using namespace std;
// 设计一个武器类
class Weapon
{
public:
    Weapon(int h = 0) : Harm(h) {}

    // 攻击特效 ,这把武器是什么武器知道吗？ 不知道所以他的攻击特效接口是抽象出来 ，虚构的
    virtual void attack()
    {
        cout << "没有任何效果，伤害" << this->Harm << endl;
    }

    int Harm;
};

// 设计不同的武器
class szz : public Weapon
{
public:
    szz(int h) : Weapon(h) {}

    // 设计双子座武器的攻击效果
    void attack()
    {
        cout << "双子攻击，造成双倍伤害" << this->Harm * 2 << endl;
    }
};

class ksd : public Weapon
{
public:
    ksd(int h) : Weapon(h) {}

    // 设计砍神刀攻击效果
    void attack()
    {
        cout << "神之一击，🌩🌩🌩🌩 咚咚咚，暴击 伤害 X 99999" << this->Harm * 99999 << endl;
    }
};

// 设计一个角色类
class role
{
public:
    role(int a, int l) : Atk(a), Life(l)
    {
    }

    // 设计攻击接口
    void attck(Weapon *p)
    {
        // 拿武器进行攻击
        p->attack();
    }

private:
    int Atk;
    int Life;
};

int main()
{

    // 定义一个角色
    role r(100, 100);

    // 角色进行攻击  ,给他双子座
    r.attck(new szz(1000));

    // 角色进行攻击 ，给他砍神刀
    r.attck(new ksd(100000));

    // 一个角色 拿着不同的武器进行攻击 ！
}