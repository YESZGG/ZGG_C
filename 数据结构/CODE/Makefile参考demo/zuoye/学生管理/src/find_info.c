#include <stdio.h>
#include <string.h>

#include "head.h"

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