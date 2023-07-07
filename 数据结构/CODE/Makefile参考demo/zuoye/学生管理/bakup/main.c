#include <stdio.h>
#include <string.h>

#include "head.h"

/*
	main函数 --- 简单明了
编译方法：	
	gcc main.c fun.c -o main
*/
int main(int argc,char **argv)
{
	//定义一个结构体数组来存储学生的信息
	struct stu s[10] = {0};
	
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