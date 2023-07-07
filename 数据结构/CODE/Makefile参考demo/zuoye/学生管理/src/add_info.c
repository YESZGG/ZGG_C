#include <stdio.h>
#include <string.h>

#include "head.h"

/*
注册学生信息
*/
void add_info(struct stu s[10],int index)
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