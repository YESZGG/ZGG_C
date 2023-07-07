#ifndef __HEAD_H_
#define __HEAD_H_

#define MAN_NUM		10  //数组的元素个数的最大值

//定义一个学生的数据类型
struct stu
{
	char name[20];
	char sex;
	int height;
	float score;
};


extern void menu_main();
extern void register_info(struct stu s[10],int index);
extern void show_info(struct stu s[10]);
extern void find_info(struct stu s[10]);

#endif