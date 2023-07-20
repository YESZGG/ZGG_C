#include <stdio.h>   //ls /usr/include/stdio.h
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>  //ls /usr/include/linux/input.h

//因为fd_ts是整个系统的唯一值 不会出现第二个fd_ts，可以把它定义成全局变量
int fd_ts = -1; 

//滑动的4种状态+1中单击
enum SLIDE {UP,DOWN,LEFT,RIGHT,CLICK};

/*
    单击：获取x和y的坐标值
*/
int get_xy(int *x,int *y)
{
    //定义一个存储触摸屏信息的结构体
    struct input_event ts; // 由内核提供额接口
    memset(&ts,0,sizeof(struct input_event));

    //读触摸屏信息
    while(1)
    {
        //此处的read是一个带阻塞属性的函数
        read(fd_ts,&ts,sizeof(struct input_event));
        if(ts.type == EV_ABS && ts.code == ABS_X) //x轴坐标值
        {
            // printf("x=%d ",ts.value); //蓝色的板子分辨率800*480
            // printf("x=%d ",(int)(ts.value*0.78)); //黑色的板子分辨率1024*600--->800*480
            // printf("x=%d ",ts.value*800/1024); 
            *x = ts.value;
        }
        if(ts.type == EV_ABS && ts.code == ABS_Y) //y轴坐标值
        {
            // printf("y=%d\n",ts.value);//蓝色的板子分辨率800*480
            // printf("y=%d\n",ts.value*0.8);
            // printf("y=%d\n",ts.value*480/600);//黑色的板子分辨率1024*600--->800*480
            *y = ts.value;
        }   

        if(ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 1) //按下去的坐标
        {
            // printf("down x=%d y=%d\n",x,y);
            break;
        }              
    }    
}

/*
    滑动：
*/
int get_slide()
{
    //定义一个存储触摸屏信息的结构体
    struct input_event ts; // 由内核提供额接口
    memset(&ts,0,sizeof(struct input_event));

    int x1=0,y1=0; //(x1,y1)按下去的坐标值
    int x2=0,y2=0; //(x2,y2)松手后的坐标值

    while(1)
    {
        //获取按下去的坐标值
        while(1)
        {
            //此处的read是一个带阻塞属性的函数
            read(fd_ts,&ts,sizeof(struct input_event));
            if(ts.type == EV_ABS && ts.code == ABS_X) //x轴坐标值
            {
                // printf("x=%d ",ts.value); //蓝色的板子分辨率800*480
                // printf("x=%d ",(int)(ts.value*0.78)); //黑色的板子分辨率1024*600--->800*480
                // printf("x=%d ",ts.value*800/1024); 
                x1 = ts.value;
            }
            if(ts.type == EV_ABS && ts.code == ABS_Y) //y轴坐标值
            {
                // printf("y=%d\n",ts.value);//蓝色的板子分辨率800*480
                // printf("y=%d\n",ts.value*0.8);
                // printf("y=%d\n",ts.value*480/600);//黑色的板子分辨率1024*600--->800*480
                y1 = ts.value;
            }   

            if(ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 1) //按下去的坐标
            {
                printf("down x1=%d y1=%d\n",x1,y1);
                break;
            }            
        }    

        while(1)
        {
            //此处的read是一个带阻塞属性的函数
            read(fd_ts,&ts,sizeof(struct input_event));
            if(ts.type == EV_ABS && ts.code == ABS_X) //x轴坐标值
            {
                // printf("x=%d ",ts.value); //蓝色的板子分辨率800*480
                // printf("x=%d ",(int)(ts.value*0.78)); //黑色的板子分辨率1024*600--->800*480
                // printf("x=%d ",ts.value*800/1024); 
                x2 = ts.value;
            }
            if(ts.type == EV_ABS && ts.code == ABS_Y) //y轴坐标值
            {
                // printf("y=%d\n",ts.value);//蓝色的板子分辨率800*480
                // printf("y=%d\n",ts.value*0.8);
                // printf("y=%d\n",ts.value*480/600);//黑色的板子分辨率1024*600--->800*480
                y2 = ts.value;
            }   

            if(ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 0) //松手后坐标值
            {
                printf("up x2=%d y2=%d\n",x2,y2);
                break;
            }            
        }  

        if((x2-x1) > 50)
            return RIGHT;
        if((x2-x1) < -50)
            return LEFT;
        if((y2-y1) > 50)
            return DOWN;
        if((y2-y1) < -50)
            return UP;
                                
    }    
} 

/*
    滑动+点击
*/
int get_slide_click(int *x,int *y)
{
    //定义一个存储触摸屏信息的结构体
    struct input_event ts; // 由内核提供额接口
    memset(&ts,0,sizeof(struct input_event));

    int x1=0,y1=0; //(x1,y1)按下去的坐标值
    int x2=0,y2=0; //(x2,y2)松手后的坐标值

    while(1)
    {
        //获取按下去的坐标值
        while(1)
        {
            //此处的read是一个带阻塞属性的函数
            read(fd_ts,&ts,sizeof(struct input_event));
            if(ts.type == EV_ABS && ts.code == ABS_X) //x轴坐标值
            {
                // printf("x=%d ",ts.value); //蓝色的板子分辨率800*480
                // printf("x=%d ",(int)(ts.value*0.78)); //黑色的板子分辨率1024*600--->800*480
                // printf("x=%d ",ts.value*800/1024); 
                x1 = ts.value;
                *x = x1;
            }
            if(ts.type == EV_ABS && ts.code == ABS_Y) //y轴坐标值
            {
                // printf("y=%d\n",ts.value);//蓝色的板子分辨率800*480
                // printf("y=%d\n",ts.value*0.8);
                // printf("y=%d\n",ts.value*480/600);//黑色的板子分辨率1024*600--->800*480
                y1 = ts.value;
                *y = y1;
            }   

            if(ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 1) //按下去的坐标
            {
                // printf("down x1=%d y1=%d\n",x1,y1);
                break;
            }            
        }    

        while(1)
        {
            //此处的read是一个带阻塞属性的函数
            read(fd_ts,&ts,sizeof(struct input_event));
            if(ts.type == EV_ABS && ts.code == ABS_X) //x轴坐标值
            {
                // printf("x=%d ",ts.value); //蓝色的板子分辨率800*480
                // printf("x=%d ",(int)(ts.value*0.78)); //黑色的板子分辨率1024*600--->800*480
                // printf("x=%d ",ts.value*800/1024); 
                x2 = ts.value;
            }
            if(ts.type == EV_ABS && ts.code == ABS_Y) //y轴坐标值
            {
                // printf("y=%d\n",ts.value);//蓝色的板子分辨率800*480
                // printf("y=%d\n",ts.value*0.8);
                // printf("y=%d\n",ts.value*480/600);//黑色的板子分辨率1024*600--->800*480
                y2 = ts.value;
            }   

            if(ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 0) //松手后坐标值
            {
                // printf("up x2=%d y2=%d\n",x2,y2);
                break;
            }            
        }  

        if(x2 != 0) //滑动的状态
        {
            if((x2-x1) > 50)
                return RIGHT;
            if((x2-x1) < -50)
                return LEFT;
            if((y2-y1) > 50)
                return DOWN;
            if((y2-y1) < -50)
                return UP;
        }
        else //点击的状态
            return CLICK;


        //清空按下去和松手后的值
        x1=0;y1=0;
        x2=0;y2=0;

    }    
} 

int main(int argc,char **argv)
{
    //打开触摸屏(设备文件需要用系统IO)
    fd_ts = open("/dev/input/event0",O_RDWR);
    if(fd_ts < 0)
    {
        perror("open ts fail");
        return -1;
    }

    int x=0,y=0;
    while(1) //主功能
    {
        #if 0
        //单点的代码
        get_xy(&x,&y);
        printf("x=%d y=%d\n",x,y);
        #endif

        #if 0
        //滑动的代码
        switch(get_slide())
        {
            case up:
                printf("up\n");
                break;
            case down:
                printf("down\n");
                break;
            case left:
                printf("left\n");
                break;
            case right:
                printf("right\n");
                break;
            default:
                break;
        }
        #endif

        //滑动+点击
        switch(get_slide_click(&x,&y))
        {
            case UP:
                printf("up\n");
                break;
            case DOWN:
                printf("down\n");
                break;
            case LEFT:
                printf("left\n");
                break;
            case RIGHT:
                printf("right\n");
                break;
            case CLICK: //点击
                printf("click x=%d y=%d\n",x,y);
                break;
            default:
                break;
        }        
    }


    //关闭触摸屏
    close(fd_ts);

    return 0;
}    