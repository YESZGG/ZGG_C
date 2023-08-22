#include <iostream>
#include <unistd.h>
// 定义一个结构体存储学生信息
struct Student
{
    std::string name;
    int age;
};

int main()
{
    // 动态分配内存来存储学生信息 --- 相当于结构体数组
    Student *students = new Student[20];
    int count = 0; // 计数器变量，用于跟踪实际存储的学生数量
    int mode = 0;

    while (mode != 3)
    { 
        system("clear");
        // 输入3时退出循环
        std::cout << "请输入（1-添加，2-显示，3-退出）:";
        std::cin >> mode;

        switch (mode)
        {
        case 1:
            if (count < 20)
            { // 防止数组越界
                std::cout << "请输入学生姓名：";
                std::cin >> students[count].name;
                std::cout << "请输入学生年龄:";
                std::cin >> students[count].age;
                count++; // 增加计数器
            }
            else
            {
                std::cout << "已达到最大学生数量！" << std::endl;
            }
            break;

        case 2:
            std::cout << "学生信息列表：" << std::endl;
            for (int i = 0; i < count; i++)
            { // 只遍历存在信息的学生
                std::cout << "姓名：" << students[i].name << std::endl;
                std::cout << "年龄：" << students[i].age << std::endl;
            }
            break;

        case 3:
            std::cout << "退出程序" << std::endl;
            break;

        default:
            std::cout << "输入命令有误" << std::endl;
            break;
        }
        sleep(2);
    }

    // 释放动态分配的内存
    delete[] students;

    return 0;
}
