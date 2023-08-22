#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/fb.h>
#include <linux/un.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#include "common.h"
#include "cJSON.h"

char *httprequest()
{
	printf("你要查哪个城市天气？（输入中文或拼音）\n");
	char city[20];	
	bzero(city, 20);
	fgets(city, 20, stdin);

	static char request[1024];

	snprintf(request, 1024, "GET /v3/weather/now.json?key=SAewqnjWlC7dvMLfL&location=%s&language=zh-Hans&unit=c HTTP/1.1\r\n"
			        "Host:api.seniverse.com\r\n\r\n", strtok(city, "\n"));

	return request;
}

void parse(char *res, int *ok, int *len)
{
	char *retcode = res + strlen("HTTP/1.x ");

	switch(atoi(retcode))
	{
	case 200 ... 299:
			*ok = 1;
			printf("查询成功\n");
			break;

	case 400 ... 499:
			*ok = 0;
			printf("客户端错误\n");
			exit(0);

	case 500 ... 599:
			*ok = 0;
			printf("服务端错误\n");
			exit(0);
	}

	char *p;
	if(p = strstr(res, "Content-Length: "))
	{
		*len = atoi(p + strlen("Content-Length: "));
	}
}

////////////////////////////////////////////////////////
//
//  Copyright(C), 2005-2022, GEC Tech. Co., Ltd.
//  www.yueqian.com.cn  ALL RIGHT RESERVED
//
//  文件: forecast.c
//  描述: 基于HTTP协议的天气查询案例
//        本案例使用心知天气提供商的API接口
//        所有数据处理以该提供商的规范为准，若更改API提供商
//        则相应HTTP请求格式、参数、数据解析都应重新设计。
//
///////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	// 利用DNS服务查询指定域名的IP
	struct hostent *he = gethostbyname("api.seniverse.com");
	if(he == NULL)
	{
		perror("DNS查询失败");
		exit(0);
	}

	printf("IP: %s\n", inet_ntoa(*(struct in_addr*)((he->h_addr_list)[0])));

	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	bzero(&addr, len);

	addr.sin_family = AF_INET;
	addr.sin_addr   = *(struct in_addr*)((he->h_addr_list)[0]);
	addr.sin_port   = htons(80);

	// 创建TCP套接字(因为HTTP是基于TCP的)，并发起连接
	int fd = Socket(AF_INET, SOCK_STREAM, 0);
	if(connect(fd, (struct sockaddr *)&addr, len) == 0)
	{
		printf("连接服务器成功！\n");
	}

	// 准备好HTTP的请求报文
	char *s = httprequest();
	write(fd, s, strlen(s));


	// 接收对方的响应头部
	char res[1024];
	int total = 0;
	while(1)
	{
		int n = read(fd, res+total, 1);

		if(n <= 0)
		{
			perror("读取HTTP头部失败");
			exit(0);
		}

		total += n;

		if(strstr(res, "\r\n\r\n"))
			break;
	}

	// 分析响应码，并获取正文的长度
	int ok, jsonlen=0;
	parse(res, &ok, &jsonlen);
	if(!ok || jsonlen == 0)
	{
		exit(0);
	}

	// 接收正文
	char *json = calloc(1, jsonlen);
	total = 0;
	while(jsonlen > 0)
	{
		int n    = read(fd, json+total, jsonlen);
		total   += n;
		jsonlen -= n;
	}

	cJSON *root = cJSON_Parse(json);
	cJSON *body = cJSON_GetObjectItem(root, "results");

	cJSON *a = cJSON_GetArrayItem(body, 0);

	cJSON *now  = cJSON_GetObjectItem(a, "now");

	printf("天气情况: %s\n", cJSON_GetObjectItem(now, "text")->valuestring);
	printf("当前气温: %s°C\n", cJSON_GetObjectItem(now, "temperature")->valuestring);

	return 0;
}

