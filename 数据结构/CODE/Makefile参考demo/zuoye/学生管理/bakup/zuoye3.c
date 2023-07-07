#include <stdio.h>
#include <string.h>

#define MAN_NUM		10  //数组的元素个数的最大值

/*
比较字符串函数
#include <string.h>
int strcmp(const char *s1, const char *s2);
*/

struct reg
{
	char usr[20]; //注册的账号
	char passward[20]//注册的密码
};
	
//定义一个学生的数据类型
struct stu
{
	char name[20];
	char sex;
	int height;
	float score;
};

/*
	菜单
*/
void menu_main()
{
	printf("1-register 2-show 3-find 4-del\n");
}

/*
注册学生信息
*/
void register_info(struct stu s[10],int index)
{
	char name[20] = {0};
	char sex = 0;
	int height = 0;
	float score = 0;	
	
	printf("please input the name:");  //姓名
	scanf("%s",name);
	strcpy(s[index].name,name);
	
	while(getchar()!='\n'); //清空缓冲区(将\n拿掉)
		
	printf("please input the sex:");  //性别
	scanf("%c",&sex);
	s[index].sex = sex;
	
	printf("please input the height:"); //身高
	scanf("%d",&height);
	s[index].height = height;
	
	printf("please input the score:"); //分数
	scanf("%f",&score);
	s[index].score = score;
	
	printf("input OK\n");
}

/*
显示学生信息
*/
void show_info(struct stu s[10])
{
	printf("=================================\n");
	printf("%-10s%-5s%-10s%-10s\n","name","sex","height","score");
	printf("=================================\n");	
	int i = 0;
	for(i = 0;i < MAN_NUM;i++)
		printf("%-10s%-5c%-10d%-10.2f\n",s[i].name,s[i].sex,s[i].height,s[i].score);	
}

void find_info(struct stu s[10])
{
	//menu_find(); //查找菜单
	int flag = 0; //查找的标志量
	scanf("please input the find name:"); //查找名字	
	char name[20] = {0};
	scanf("%s",name);
	int i= 0;
	for(i=0;i< MAN_NUM;i++)
	{
		if(strcmp(s[i].name,name) == 0) //如果两个字符串相等
		{
			printf("find ok\n");
			flag = 1;
			printf("%-10s%-5c%-10d%-10.2f\n",s[i].name,s[i].sex,s[i].height,s[i].score);
		}
	}
	
	if(flag != 1)
		printf("sorry, no find\n");
}

/*
void register_login();
{
	//做一个注册登录的界面
	//struct reg reg_info[2];
	//if(strcmp(账号) && strcmp(密码))
}
*/

/*
	main函数 --- 简单明了
*/
int main(int argc,char **argv)
{
	//定义一个结构体数组来存储学生的信息
	struct stu s[10] = {0};
	
	//register_login();
	//注册账号和密码
	//1.先注册 -- 填账号和密码
	//2.登录 -- 将你新输入的账号和密码 与 你之前注册的账号和密码相比较
	//if(strcmp(账号) && strcmp(密码))
	//如果登录成功代码继续往下走;如果登录不成功代码over或者继续登录
	
	//选择功能
	int function = 0;
	int index = 0; //数组下标==哪一个学生
	
	while(1)
	{
		//功能选择菜单 -- 主菜单
		menu_main();
		scanf("%d",&function);
		switch(function)
		{
			case 1:
				register_info(s,index); //注册学生信息
				index++;
				if(index >=10) //防止数组越界
					index = 0;
				break;
			case 2:
				show_info(s);//显示学生信息
				break;
			case 3:
				find_info(s);//查找
				break;	
			case 4:
				//删除
				break;
			default:
				break;
		}
	}
	
	return 0;
}