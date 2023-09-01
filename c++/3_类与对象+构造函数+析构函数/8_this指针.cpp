#include <iostream>
#include <cstring>

using namespace std;

class Student
{
public:
    Student(const char *name="bling",char sex='M',int height=189)
    {
        cout<<"Student()"<<endl;
        //使用this指针
        //strcpy(this->name,name); //如果是char name[20]这种写法
        this->name = new char[256];
        memset(this->name,0,256);
        strcpy(this->name,name);
        this->sex = sex;
        this->height = height;
    }

    // Student(const char *na="bling",char se='M',int hei=189)
    // {
    //     //不使用this指针
    //     strcpy(name,na);
    //     sex = se;
    //     height = hei;
    // }

    ~Student()
    {
        cout<<"~Student()"<<endl;
        delete []name;    
    }

private:
    //char name[20];
    char *name;
    char sex;
    int height;
};



int main()
{
    Student s1;

    return 0;
}