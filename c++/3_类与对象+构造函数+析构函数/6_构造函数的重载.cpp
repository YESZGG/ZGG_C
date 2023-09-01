#include <iostream>

using namespace std;

/*
创建对象的时候根据不同的参数调用不同的构造函数
*/

class GirlFriend
{
public:
    // 类的构造函数，一般放在public权限下
    //  GirlFriend()
    //  {
    //      cout<<"GirlFriend()"<<endl;
    //  }
    //  GirlFriend(int a)
    //  {
    //      cout<<"GirlFriend(int a)"<<endl;
    //  }
    //  GirlFriend(int a,int b=20)
    //  {
    //      cout<<"GirlFriend(int a,int b )"<<endl;
    //  }
    GirlFriend(int a = 10, int b = 20, int c = 30) //
    {
        _a = a;
        _b = b;
        _c = c;
        cout << "GirlFriend(int a,int b )" << endl;
    }

    void show()
    {
        cout << _a << "\t" << _b << "\t" << _c << endl;
    }

private:
    int _a;
    int _b;
    int _c;
};

int main()
{
    // GirlFriend g1; //对应的构造函数是GirlFriend()

    // GirlFriend g2(10);//对应的构造函数是GirlFriend(int a)

    // GirlFriend g3(10,20);//对应的构造函数是GirlFriend(int a,int b )

    // GirlFriend g4(); //会产生歧义 不要这么用

    GirlFriend g5(11);
    g5.show();

    GirlFriend g6(11, 21);
    g6.show();

    GirlFriend g7(11, 21, 31);
    g7.show();

    return 0;
}