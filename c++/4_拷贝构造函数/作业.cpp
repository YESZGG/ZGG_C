/*
 * @Description: 8.25作业
 * @version: 1.80.1
 * @Author: ZGG
 * @Date: 2023-08-25 18:52:41
 * @LastEditors: ZGG
 * @LastEditTime: 2023-08-25 19:18:54
 */
#include <iostream>
#include <cstring>

using namespace std;

class Person
{
protected:
    string name;   // 姓名
    int age;       // 年龄
    string gender; // 性别

public:
    Person(const string &name, int age, const string &gender)
        : name(name), age(age), gender(gender) {}

    // 获取姓名
    string getName() const { return name; }
    // 设置姓名
    void setName(const string &newName) { name = newName; }

    // 获取年龄
    int getAge() const { return age; }
    // 设置年龄
    void setAge(int newAge) { age = newAge; }

    // 获取性别
    string getGender() const { return gender; }
    // 设置性别
    void setGender(const string &newGender) { gender = newGender; }
};

class Student : public Person // 公共继承类Person
{
private:
    double score;     // 分数
    string studentId; // 学生ID号

public:
    // 学生类构造函数，初始化Person属性以及自身属性
    Student(const string &name, int age, const string &gender, double score, const string &studentId)
        : Person(name, age, gender), score(score), studentId(studentId) {}

    // 获取分数
    double getScore() const { return score; }
    // 设置分数
    void setScore(double newScore) { score = newScore; }

    // 获取学生的ID号
    string getStudentId() const { return studentId; }
    // 设置学生的ID号
    void setStudentId(const string &newStudentId) { studentId = newStudentId; }
};

class Teacher : public Person
{
private:
    int teachingExperience; // 教龄
    string subject;         // 教授学科

public:
    // Teacher类的构造函数，初始化Person类的属性以及自身的属性
    Teacher(const string &name, int age, const string &gender, int teachingExperience, const string &subject)
        : Person(name, age, gender), teachingExperience(teachingExperience), subject(subject) {}

    // 获取教龄
    int getTeachingExperience() const { return teachingExperience; }
    // 设置教龄
    void setTeachingExperience(int newTeachingExperience) { teachingExperience = newTeachingExperience; }

    // 获取教授学科
    string getSubject() const { return subject; }
    // 设置学科
    void setSubject(const string &newSubject) { subject = newSubject; }
};

int main()
{
    // 创建一个学生对象并设置属性
    Student student("Alice", 18, "Female", 95.5, "S123456");

    // 获取学生对象的属性并输出
    cout << "Name: " << student.getName() << endl;
    cout << "Age: " << student.getAge() << endl;
    cout << "Gender: " << student.getGender() << endl;
    cout << "Score: " << student.getScore() << endl;
    cout << "Student ID: " << student.getStudentId() << endl;

    // 修改学生对象的属性
    student.setScore(88.0);
    student.setStudentId("S654321");

    // 再次获取学生对象的属性并输出
    cout << "\nModified Score: " << student.getScore() << endl;
    cout << "Modified Student ID: " << student.getStudentId() << endl;

    // 创建一个教师对象并设置属性
    Teacher teacher("Bob", 30, "Male", 8, "Mathematics");

    // 获取教师对象的属性并输出
    cout << "\nName: " << teacher.getName() << endl;
    cout << "Age: " << teacher.getAge() << endl;
    cout << "Gender: " << teacher.getGender() << endl;
    cout << "Teaching Experience: " << teacher.getTeachingExperience() << " years" << endl;
    cout << "Subject: " << teacher.getSubject() << endl;

    // 修改教师对象的属性
    teacher.setTeachingExperience(10);
    teacher.setSubject("Physics");

    // 再次获取教师对象的属性并输出
    cout << "\nModified Teaching Experience: " << teacher.getTeachingExperience() << " years" << endl;
    cout << "Modified Subject: " << teacher.getSubject() << endl;

    return 0;
}
