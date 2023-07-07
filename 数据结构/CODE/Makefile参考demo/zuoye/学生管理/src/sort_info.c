#include <stdio.h>
#include <string.h>

#include "head.h"


/*
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
*/


void sort_info(struct stu s[10])
{
	struct stu tmp = {0};
	int i=0,j=0;
	for(i=0;i<(MAN_NUM-1);i++)
	{
		for(j=0;j<(MAN_NUM-1-i);j++)
		{
			if(s[j].height > s[j+1].height)
			{
				//方式一: //直接赋值
				#if 0
				tmp = s[j];
				s[j] = s[j+1];
				s[j+1] = tmp;
				#endif
				
				//方式二：//内存拷贝
				memcpy(&tmp,&(s[j]),sizeof(struct stu));
				memcpy(&(s[j]),&(s[j+1]),sizeof(struct stu));
				memcpy(&(s[j+1]),&tmp,sizeof(struct stu));	
			}
		}
	}
	
}