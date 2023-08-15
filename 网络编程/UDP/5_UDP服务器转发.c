#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MY_IP "192.168.1.148" //目标地址
#define MY_PORT   60000   //目标ip

//发送数据的结构体---协议(要保证和客户端一致)
struct info
{
	char buf[1024]; //转发的内容
	struct sockaddr_in other_addr;//转发的其他人
};

int main()
{
    //创建套接字
    //创建套接字
    int socket_fd;
    //AF_INET-->ipv4地址族 SOCK_DGRAM-->udp协议
    socket_fd = socket(AF_INET,SOCK_DGRAM,0);
    if(socket_fd < 0)
    {
        perror("socket fail");
        return -1;
    }

    /*
        重复绑定本机端口和地址
        //所以设置端口号可以复用,这两条语句放在 绑定bind 之前
    */
    int optval = 1; 
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR,&optval, sizeof(optval));   

    int ret = 0;
    //绑定本机ip
    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET; //地址族
    my_addr.sin_port = htons(MY_PORT); //本机端口转网络端口
    my_addr.sin_addr.s_addr = inet_addr(MY_IP);//本机ip转网络ip
    ret = bind(socket_fd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr_in));
    if(ret < 0)
    {
        perror("bind fail");
        return -1;
    }
    printf("绑定本机ip成功[%s][%d]\n",MY_IP,MY_PORT);

    //直接接收数据recvfrom
    //定义一个接收端的地址，用来存放发送端的地址
    struct sockaddr_in recv_addr;
    socklen_t address_len = sizeof(struct sockaddr_in);
    char buf[1024] = {0};

	struct info recv_info; //接收数据的结构体
	memset(&recv_info,0,sizeof(struct info));
	
    while(1)
    {
        //阻塞等待数据
		memset(&recv_info,0,sizeof(struct info));
        ret = recvfrom(socket_fd,&recv_info,sizeof(struct info),0,(struct sockaddr *)&recv_addr,&address_len);
		
        //解析接收到的客户端地址和端口
        char *ip= inet_ntoa(recv_addr.sin_addr)  ;//将网络字节序转换成本机字节序
        int port = ntohs(recv_addr.sin_port);//将网络端口转换为本机端口
        printf("[%s][%d]recvfrom ok buf:%s ret:%d ohther[%s][%d]\n",
							ip,port,
							recv_info.buf,ret,
							inet_ntoa(recv_info.other_addr.sin_addr),  //解析接收到的buf里面的其它人的地址
							ntohs(recv_info.other_addr.sin_port));//解析接收到的buf里面的其它人的端口号
		
		//转发给other_ip
        ret = sendto(socket_fd,recv_info.buf,strlen(recv_info.buf),0,
                (struct sockaddr *)&recv_info.other_addr,sizeof(struct sockaddr_in));
        printf("转发ok ret:%d\n",ret);        

    }

    //关闭套接字
    close(socket_fd);


    return 0;
}