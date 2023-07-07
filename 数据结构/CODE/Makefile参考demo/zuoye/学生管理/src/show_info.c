#include <stdio.h>
#include <string.h>

#include "head.h"

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
	{
		if(s[i].height !=0)	//屏蔽掉无效的数据值
			printf("%-10s%-5c%-10d%-10.2f\n",s[i].name,s[i].sex,s[i].height,s[i].score);
	}	
	printf("\n");
}