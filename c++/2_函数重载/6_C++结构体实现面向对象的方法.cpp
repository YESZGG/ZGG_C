#include<iostream>
#include <cstdio>

/*
    C++的结构体中可以直接定义函数
*/

using namespace std;

//女朋友是一个整体  对象
//关于对象：   1、属性   关于 这个对象的特征的描述  年龄  姓名    变量
//            2、行为   吃饭、打游戏  玩 、睡觉....             函数 
typedef struct GirlFriend{
    //属性
    char name[256];
    int age;
    int money;
    
    //行为
    void eat(){
        // printf("[%s] 我正在吃饭....\n",this->name);
        printf("[%s] 我正在吃饭....\n",name);
    }
    void player(){
        printf("[%s]别说了，上号...\n",this->name);
    }

    int getAge(){
        return this->age;
    }

}GirlFriend_t; 


int main(){

    //实例化一个对象
    GirlFriend_t s1 = {"zhang3",22};
    GirlFriend_t s2 = {"ruhua",22};
    
    // 通过这个对象来调用它的行为
    s1.eat();
    s2.eat();
 
    cout<<s1.getAge()<<endl;
}
