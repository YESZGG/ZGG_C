#include <stdio.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_IP "192.168.1.148"
#define SERVER_PORT 8888

void sys_err(const char *err)
{
	fprintf(stderr, "%s\n", strerror(errno));
	exit(0);
}
int main()
{
	int ret, max_fd, i = 0, imax = 0;
	int client[FD_SETSIZE]; // 存储所有客户端的文件描述符//该宏系统已经定义好了 文件描述符的总数 1024

	struct sockaddr_in clientAddr; // 存储连接上来的客户端的IP地址和端口号
	int len = sizeof(struct sockaddr_in);

	printf("服务器 Port:%d PID:%d \n", SERVER_PORT, getpid());

	// 1、建立套接字(监听套接字)
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
	{
		sys_err("socket error");
		// perror("bind"); //两种错误条释放作用一样
	}
	// 端口复用
	int optval = 1;
	setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	// 2、绑定自己的IP地址和端口号
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT); // short
	// server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //表示本机任意IP地址
	server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

	ret = bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
	if (ret == -1)
	{
		sys_err("bind error");
	}

	// 3、设置监听
	listen(socket_fd, 128);

	// 定义文件描述符集合
	fd_set rset, allset; // allset是一个中间变量用来存储监听套接字和新加入的客户端套接字，然后将值给到rset
	// 清空集合
	FD_ZERO(&allset);

	FD_SET(socket_fd, &allset); // 把监听套接字 加入到集合中
	// 最大的文件描述符，在没有客户端进来之前，最大的文件描述符最大值就是socket_fd
	max_fd = socket_fd;

	// 初始化为 -1 给存放客户端套接字的数组初始化
	for (int k = 0; k < FD_SETSIZE; k++)
	{
		client[k] = -1;
	}

	// 设置阻塞的时间
	// struct timeval t;
	// t.tv_sec = 5; // 如果使用这个参数那么select这个函数5秒之后就不阻塞
	// t.tv_usec = 0;

	while (1)
	{
		// 设置阻塞的时间
		// struct timeval t;
		// t.tv_sec = 5; // 如果使用这个参数那么select这个函数5秒之后就不阻塞
		// t.tv_usec = 0;

		rset = allset; // 每次循环的时候都需要重新设置select的集合
		// 多路复用 ，同时监听 多个套接字文件描述符的状态  --阻塞监听
		// nready表示的是状态发生变化的文件描述符的总数,(不是里面存放了多少个描述符)
		int nready = select(max_fd + 1, &rset, NULL, NULL, NULL);
		if (nready == -1)
		{
			perror("select error");
			break;
		}

		// printf("nready = %d\n",nready); //每次发生变化时 nready=1
		// 程序走到这里，说明集合中的文件描述符的状态一定发生变化了

		// 如果是监听套接字文件描述符发生变化了，说明一定是有新客户端连接上来了
		if (FD_ISSET(socket_fd, &rset))
		{
			// 接收新的客户端
			int new_clientfd = accept(socket_fd, (struct sockaddr *)&clientAddr, &len);

			printf("有新的客户端连接上来  IP:%s Port:%hu new_clientfd:%d\n",
				   inet_ntoa(clientAddr.sin_addr),
				   ntohs(clientAddr.sin_port),
				   new_clientfd);

			// 把新的客户端文件描述符加入到集合中
			FD_SET(new_clientfd, &allset);
			// 更新文件描述符最大值
			if (new_clientfd > max_fd)
				max_fd = new_clientfd;

			// 将连接上来的客户端文件描述符 加入到 数组中
			for (i = 0; i < FD_SETSIZE; i++)
			{
				if (client[i] < 0)
				{
					client[i] = new_clientfd;
					break;
				}
			}

			// imax = i;//存放客户端套接字数组里面的最大的下标值(可以通过这个值来记录你客户端数目)

			// 说明该集合中只有监听套接字文件描述符发生变化
			if (--nready == 0)
				continue;
		}

		// 程序走到这里，说明有客户端发送数据过来
		for (i = 0; i < FD_SETSIZE; i++)
		{
			if (client[i] < 0)
				continue; // 提高代码的执行效率

			// 说明该客户端发送数据过来了,
			// 客户端套接字的状态就发生变化这句话if(FD_ISSET(client[i], &rset))就成立
			if (FD_ISSET(client[i], &rset))
			{
				char buf[1024] = {0};
				int ret = read(client[i], buf, sizeof(buf));
				if (ret == 0) // 该客户端断开了
				{
					printf("有客户端断开了.....\n");
					close(client[i]); // 关闭文件描述符

					FD_CLR(client[i], &allset); // 指定将该客户端文件描述符 从集合中删除
					client[i] = -1;				// 该文件描述符对应的数组位置置 -1
				}

				printf("recv:%s\n", buf);
				// 说明所有发生变化的文件描述符 已经被我们处理完了，则退出
				if (--nready == 0)
					break;
			}
		}
	}

	// 关闭
	close(socket_fd);

	return 0;
}