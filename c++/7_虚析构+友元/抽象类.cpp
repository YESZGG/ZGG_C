#include <iostream>

using namespace std;

// 抽象一个电脑类
// 预留接口提供派生类去覆盖，方便实现动态多态。

/*  
1.提高代码重用性:实现动态多态，就是提高复用性。
2.类型安全性:抽象无法创建对象，这样对于一些不复合常理的类，就不能创建。
3.代码可读性和可维护性:抽象类提供了一个基类，子类可以继承这个基类，从而简化代码的编写过程。
*/

class computer // 类中有纯虚函数，则类为抽象类
{
public:
    /* 纯虚函数 提供接口，提高代码的可读性和可维护性 */
    virtual void buy_jixiang() = 0;
    virtual void buy_zhuban() = 0;
    virtual void buy_cpu() = 0;
    virtual void buy_neicun() = 0;
    virtual void buy_yinpan() = 0;
    virtual void buy_dianyuan() = 0;

    // 设计一个装电脑的接口
    void make_computer()
    {
        this->buy_jixiang();
        this->buy_zhuban();
        this->buy_cpu();
        this->buy_neicun();
        this->buy_yinpan();
        this->buy_dianyuan();
    }
};

// 实例化电脑的配置
class myComputer : public computer // 公共继承computer抽象类，则要重写基类的纯虚函数
{
public:
    void buy_jixiang() override
    {
        cout << "购买机箱：Tt Level 20 GT RGB Plus" << endl;
    }

    void buy_zhuban() override
    {
        cout << "购买主板：华硕ROG Dominus Extreme" << endl;
    }

    void buy_cpu() override
    {
        cout << "购买CPU：AMD Ryzen ThreadRipper Pro 5995WX" << endl;
    }

    void buy_neicun() override
    {
        cout << "购买内存：芝奇皇家戟 256GB（8×32GB）DDR4 3600（F4-3600C18Q2-256GTRG）" << endl;
    }

    void buy_yinpan() override
    {
        cout << "购买硬盘：希捷银河Exos X16 16TB 7200转 256MB SAS（ST16000NM002G）" << endl;
    }

    void buy_dianyuan() override
    {
        cout << "购买电源：美商海盗船ax1600i ax1600i+h150i 精英散热" << endl;
    }
};

int main()
{
    computer *cptr = new myComputer();
    cptr->make_computer();

    delete cptr;

    return 0;
}