#include <iostream>
#include <cstring>

using namespace std;
/*
    构造函数：
        1.的函数名和类一致
        2.没有返回值
        3.一般是放在public权限下
*/

//空类
class GirlFriend
{
public: //公有方法
    //类的构造函数，一般放在public权限下，除非是特殊的设计模式
    GirlFriend() //自定义的构造函数
    {
        /*
            自定义构造函数的函数体一般存放初始化信息
        */
        strcpy(name,"阿花");
        age = 18;
        height = 168;
        cout<<"GirlFriend()"<<endl;
    }

    void setName(char *na) //方法
    {
        strcpy(name,na);
    }
    char *getName()
    {
        return name;
    }

    int getHeight()
    {
        return height;
    }

private://私有属性
    char name[20];
    int age;
    int height;
};


int main()
{
    //实例化一个对象,会自动调用构造函数
    GirlFriend g1;
    // cout<<"sizeof(GirlFriend) = "<<sizeof(GirlFriend)<<endl;
    cout<<g1.getName()<<endl;

    GirlFriend g2;
    cout<<g2.getHeight()<<endl;

    // 这里有问题   编译可能会报错  ()要么不写，要么写参数进去
    // GirlFriend g3(); //不要这么写

    return 0;
}