#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	/*
	int execl(const char *path, const char *arg, ...)：
	第一种方法：将参数以列表的形式在后面展开
	*/

	// execl("./a.out", "./a.out", "gz2308", "niubi", NULL);
	// 分析：第一个"./a.out"是文件的绝对路径  第二个"./a.out"是argv[]第0个参数 "gz2308"是argv[]第1个参数

	/*
	int execv(const char *path, char *const argv[])：
	第二种方法：将参数放在整个数组里面*argv[]
	*/
	// char *const arr[] = {"./hello", "gz2308", "niubi", NULL};
	// execv("./a.out", arr);
	// 分析：定义一个指针数组来存储execv的参数,找到目录中符合"./a.out"去执行程序。

	/*
	int execvp(const char *file, char *const argv[])：
	第三种方法：
	execvp()会从PATH环境变量所指的目录中查找符合参数 file 的文件名, 找到后便执行该文件, 然后将第二个参数argv传给该欲执行的文件.
	*/
	// char *const arr[] = {"ls", "-l", "hello.c", NULL};
	// int ret = execvp("ls", arr);
	// if (ret == -1)
	// {
	// 	perror("execvp error");
	// }

	// int execvpe(const char *file, char *const argv[], char *const envp[])：
	// 第四种方法：execvpe 不仅仅会去PATH环境变量路径下寻找程序，还会去指定的路径envp下寻找
	char *const arr[ ] = {"hello","饿了","要吃饭",NULL};
	char *const envp[ ] = {"./"};
	execvpe("./a.out",arr,envp);//也可以不加./直接execvpe("hello",arr,envp);
	// 说明：execvpe这一个函数有个小bug会警告（是由编译版本产生）

	return 0;
}