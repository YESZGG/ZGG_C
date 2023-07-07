1.版本号
===================
ver: v0.0.1
date:20221202
author:bling
E-mail: 1137252884@qq.com

ver: v0.0.2
date:
author:
E-mail: 1137252884@qq.com


2.编译方法：
gec@ubuntu:/mnt/hgfs/GZ2273/2_linux基础/02/code/zuoye2$
gcc main/main.c src/add_info.c src/find_info.c src/show_info.c src/register_login.c -I ./head/

gec@ubuntu:/mnt/hgfs/GZ2273/2_linux基础/02/code/zuoye2$ 
gcc main/main.c src/*.c -I ./head


3.目录说明：
├── a.out
├── bakup     //备份文件夹
├── bin	      //目标文件
│   └── target
├── include      //头文件
│   └── head.h
├── main		//main程序
│   └── main.c
├── Makefile
├── README.txt     //说明文档
└── src		//其它功能文件
    ├── add_info.c
    ├── find_info.c
    ├── register_login.c
    ├── show_info.c
    └── sort_info.c

/*
   函数功能：
   参数说明：	
*/
extern void add_info(struct stu s[10],int index);
extern void show_info(struct stu s[10]);
extern void find_info(struct stu s[10]);
extern void sort_info(struct stu s[10]);


4.知识点

      	//字符串长度
       #include <string.h>
       size_t strlen(const char *s);

	//字符串拷贝	
       #include <string.h>
       char *strcpy(char *dest, const char *src);
       char *strncpy(char *dest, const char *src, size_t n);
	   	
	   //字符串比较函数，如果相等返回值是0
       #include <string.h>
       int strcmp(const char *s1, const char *s2);
       int strncmp(const char *s1, const char *s2, size_t n);
	   
	   //查找字符串函数 //将haystack这个字符串在needle里面查找
       #include <string.h>
       char *strstr(const char *haystack, const char *needle);
	   strstr("hello","hello world")!=NULL
	   
	   //内存拷贝，将src指向的内存拷贝到dest指向的内存,拷贝的大小是n个字节
       #include <string.h>
       void *memcpy(void *dest, const void *src, size_t n);  

