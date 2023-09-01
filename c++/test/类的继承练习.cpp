#include <iostream>
#include <cstring>

using namespace std;

// 人 类
class People
{
public:
    People(const string &name, int age, const string &gender)
        : name(name), age(age), gender(gender) {}
    string getName()
    {
        return name;
    }
    string getGender()
    {
        return gender;
    }
    int getAge()
    {
        return age;
    }

private:
    string name;   // 姓名
    int age;       // 年龄
    string gender; // 性别
};

// 教师类
class Teacher : public People
{
public:
    Teacher(const string &name, int age, const string &gender, const string &subject, const int &grade)
        : People(name, age, gender), subject(subject), grade(grade) {}

    string getSubject()
    {
        return subject;
    }
    int getGrade()
    {
        return grade;
    }

private:
    int grade;      // 年级
    string subject; // 教授学科
};

// 医生类
class Doctor : public People
{
private:
    string department;
    string title;

public:
    Doctor(const string &name, int age, const string &gender, const string &department, const string &title)
        : People(name, age, gender), department(department), title(title) {}
    string getDepartment()
    {
        return department;
    }
    string getTitle()
    {
        return title;
    }
};

int main()
{
    // 创建一个教师对象并设置属性
    Teacher teacher("Bob", 30, "Male", "Mathematics", 8);
    // 获取教师对象的属性并输出
    cout << "\nName: " << teacher.getName() << endl;
    cout << "Age: " << teacher.getAge() << endl;
    cout << "Gender: " << teacher.getGender() << endl;
    cout << "Teaching Grade: " << teacher.getGrade() << endl;
    cout << "Subject: " << teacher.getSubject() << endl;

    Doctor doctor("Jack", 50, "Male", "外科", "主治医生");
    cout << "\nName: " << doctor.getName() << endl;
    cout << "Age: " << doctor.getAge() << endl;
    cout << "Gender: " << doctor.getGender() << endl;
    cout << "Department: " << doctor.getDepartment() << endl;
    cout << "Title: " << doctor.getTitle() << endl;

    return 0;
}