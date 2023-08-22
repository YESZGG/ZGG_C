#include <stdio.h>
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

typedef struct
{
	int fd;
	struct sockaddr_in addr;
} ClientInfo;

int main()
{
	int ret, max_fd, i = 0;
	ClientInfo client[FD_SETSIZE]; // 存储所有客户端的文件描述符和地址信息

	printf("[Port:%d] [PID:%d] 服务器 \n", SERVER_PORT, getpid());

	// 1、建立套接字(监听套接字)
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
	{
		sys_err("socket error");
	}
	// 端口复用
	int optval = 1;
	setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	// 2、绑定自己的IP地址和端口号
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT); // short
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
		client[k].fd = -1;
	}
	int len = sizeof(struct sockaddr_in);
	int imax = 0;
	while (1)
	{
		rset = allset; // 每次循环的时候都需要重新设置select的集合
		int nready = select(max_fd + 1, &rset, NULL, NULL, NULL);
		if (nready == -1)
		{
			perror("select error");
			break;
		}

		if (FD_ISSET(socket_fd, &rset))
		{
			// 接收新的客户端
			int new_clientfd = accept(socket_fd, (struct sockaddr *)&(client[imax].addr), &len);

			printf("[IP:%s] [Port:%hu] 新的客户端上线 new_clientfd:%d\n",
				   inet_ntoa(client[imax].addr.sin_addr),
				   ntohs(client[imax].addr.sin_port),
				   new_clientfd);

			client[imax].fd = new_clientfd;
			FD_SET(new_clientfd, &allset);
			if (new_clientfd > max_fd)
				max_fd = new_clientfd;

			imax++; // 下一个空闲位置的索引

			if (--nready == 0)
				continue;
		}

		for (i = 0; i < imax; i++)
		{
			if (client[i].fd < 0)
				continue;

			if (FD_ISSET(client[i].fd, &rset))
			{
				char buf[1024] = {0};
				int ret = read(client[i].fd, buf, sizeof(buf));
				if (ret <= 0) // 该客户端断开了或出错
				{
					printf("[IP:%s] [Port:%hu] 客户端已下线\n", inet_ntoa(client[i].addr.sin_addr),
						   ntohs(client[i].addr.sin_port));
					close(client[i].fd);
					// 清空指定客户端套接字
					FD_CLR(client[i].fd, &allset);
					client[i].fd = -1;
				}
				else
				{
					printf("[IP:%s] [Port:%hu] recv from : %s\n",
						   inet_ntoa(client[i].addr.sin_addr),
						   ntohs(client[i].addr.sin_port),
						   buf);
				}

				if (--nready == 0)
					break;
			}
		}
	}

	close(socket_fd);

	return 0;
}

