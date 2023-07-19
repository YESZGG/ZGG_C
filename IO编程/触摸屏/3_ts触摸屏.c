/*
 * @Description: 
 * @version: 
 * @Author: ZGG
 * @Date: 2023-07-18 16:37:02
 * @LastEditors: ZGG
 * @LastEditTime: 2023-07-18 19:24:40
 */
#include <stdio.h>   //ls /usr/include/stdio.h
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>  //ls /usr/include/linux/input.h

/*
    触摸屏、lcd都是设备文件(硬件文件):只能用系统IO打开
*/

int main(int argc,char **argv)
{
    //打开触摸屏
    int fd_ts;
    fd_ts = open("/dev/input/event0",O_RDWR);
    if(fd_ts < 0)
    {
        perror("open ts fail");
        return -1;
    }

    //定义一个存储触摸屏信息的结构体
    struct input_event ts; //有内核提供额接口
    memset(&ts,0,sizeof(struct input_event));

    //读触摸屏信息
    while(1)
    {
        //此处的read是一个带阻塞属性的函数
        read(fd_ts,&ts,sizeof(struct input_event));
        printf("ts.type = %d\n",ts.type);
        printf("ts.code = %d\n",ts.code);
        printf("ts.value = %d\n",ts.value);
    }    


    //关闭触摸屏
    close(fd_ts);

    return 0;
}    