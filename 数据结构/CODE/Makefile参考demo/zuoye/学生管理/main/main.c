#include <stdio.h>
#include <string.h>

#include "head.h"


void menu_main()
{
	printf("1-add 2-show 3-find 4-sort\n");
}

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
	int ret;
	ret = register_login();
	if(ret == ERROR) //登录失败程序就结束
	{
		printf("sorry login fail\n");
		return 0;
	}	
	
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
				add_info(s,index); //注册学生信息
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
				//排序
				sort_info(s);
				break;				
			case 5:
				//删除
				break;
			case 6:
				//退出功能
				break;
			default:
				break;
		}
	}
	
	return 0;
}