#ifndef __HEAD_H_
#define __HEAD_H_

#define MAN_NUM		10  //数组的元素个数的最大值


//登录的状态值
enum ret_stat{OK,ERROR};

//可以使用结构体数组注册多个账号
struct reg_info 
{
	char usrname[20]; //注册的账号
	char passward[20];//注册的密码
};


//定义一个学生的数据类型
struct stu
{
	char name[20];
	char sex;
	int height;
	float score;
};

extern int register_login();

extern void menu_main();
extern void add_info(struct stu s[10],int index);
extern void show_info(struct stu s[10]);
extern void find_info(struct stu s[10]);
extern void sort_info(struct stu s[10]);

#endif