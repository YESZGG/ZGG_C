#include <stdio.h>
#include <string.h>

#include "head.h"

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