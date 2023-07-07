#include <stdio.h>
#include <string.h>

#include "head.h"

int register_login()
{
	//可以使用结构体数组注册多个账号
	//struct reg_info info[3] = {0}
	struct reg_info info; //存储注册的账号和密码
	
	//menu_register(); //注册的菜单
	char name[20] = {0};
	char passward[20] = {0};
	
	//注册用户账号和密码
	printf("please register\n");	
	printf("please input your usrname:");
	scanf("%s",name);
	strcpy(info.usrname,name);
	
	printf("please input your passward:");
	scanf("%s",passward);
	strcpy(info.passward,passward); //字符串数组赋值函数	
	printf("usrname=%s passward=%s\n",info.usrname,info.passward);
	printf("register success\n");
	
	//登录账号和密码
	//menu_login(); //登录的菜单
	//如果使用的是同一个字符串变量，多次scanf输入的时候，每次scanf输入的时候一定要清零
 	memset(name,0,sizeof(name)); //清零
	printf("please login\n");
	printf("please input your login name:");
	scanf("%s",name);
	
	memset(passward,0,sizeof(passward)); //清零
	printf("please input your login passward:");
	scanf("%s",passward);
	printf("loginname=%s passward=%s\n",name,passward);

	//判断登录是否成功
	if((strcmp(info.usrname,name)==0) && (strcmp(info.passward,passward)==0))	
	{	
		printf("login success\n"); 
		return OK;
	}	
	return ERROR;
}
