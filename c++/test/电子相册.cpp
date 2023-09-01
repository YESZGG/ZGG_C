#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/input.h> //添加输入结构体
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

using namespace std;

/*
cat  /usr/include/linux/input.h

//Linux 事件输入结构体
struct input_event {
        struct timeval time; //事件输入的时间
        __u16 type; //输入的事件 ： 例如： 键盘，鼠标，触摸屏
        __u16 code; //输入的子事件 ： 例如: 触摸屏的 X 或 Y 轴
        __s32 value; //输入事件的值 ：例如：触摸屏的坐标
};
 */

/*
 cat  /usr/include/linux/input-event-codes.h  #查看输入的事件号


#define EV_SYN                  0x00  //
#define EV_KEY                  0x01  //键盘
#define EV_REL                  0x02 //鼠标
#define EV_ABS                  0x03 //触摸屏


#define ABS_X                   0x00
#define ABS_Y                   0x01
*/

// 设计一个触摸屏类
class touch
{
public:
    // 构造函数
    touch()
    {

        // 1.打开触摸屏设备文件
        this->fd = open("/dev/input/event0", O_RDWR);
        if (this->fd < 0)
        {
            cout << "初始化触摸屏失败" << endl;
            exit(0); // 退出进程
        }
        else
        {
            cout << "初始化触摸屏成功" << endl;
        }
    }

    // 析构函数
    ~touch()
    {
        close(this->fd);
    }

    // 获取滑动方向  1 上 2 下 3 左  4 右
    int get_slide()
    {
        // 定义按下坐标
        int t_x = 0, t_y = 0;

        // 定义松开坐标
        int r_x = 0, r_y = 0;

        while (1)
        {
            // 1.读取触摸屏的坐标点
            struct input_event ts = {0};

            read(this->fd, &ts, sizeof(ts));

            // 判断是否为 X 轴的坐标
            if (ts.type == EV_ABS && ts.code == ABS_X)
            {
                r_x = ts.value; // 保存当前的坐标
            }

            // 判断是否为 Y 轴的坐标
            if (ts.type == EV_ABS && ts.code == ABS_Y)
            {
                r_y = ts.value; // 保存当前的坐标
            }

            // 判断手指是否松开
            if (ts.type == EV_KEY && ts.code == BTN_TOUCH)
            {
                if (ts.value == 0) // 松开
                {
                    break;
                }

                if (ts.value == 1) // 按下
                {
                    // 保存按下的坐标
                    t_x = r_x;
                    t_y = r_y;
                }
            }
        }

        // cout << "r_x = " << r_x << endl;
        // cout << "r_y = " << r_y << endl;
        // cout << "t_x = " << t_x << endl;
        // cout << "t_y = " << t_y << endl;

        // 判断滑动方向
        if (t_x - r_x < -100) // 设置滑动的范围必须大于100
        {
            cout << "右滑动" << endl;
            return 4;
        }

        // 判断滑动方向
        if (t_x - r_x > 100)
        {
            cout << "左滑动" << endl;
            return 3;
        }

        if (t_y - r_y > 100)
        {
            cout << "上滑动" << endl;
            return 1;
        }

        if (t_y - r_y < -100)
        {
            cout << "下滑动" << endl;
            return 2;
        }
    }

private:
    int fd;
};

// 设计一个lcd显示类
class Display
{
public:
    // 构造函数初始化映射地址
    Display()
    {

        // 1.打开LCD 设备
        int fd = open("/dev/fb0", O_RDWR);
        if (fd < 0)
        {
            cout << "open LCD  error" << endl;
            exit(0);
        }

        // 2.进行内存映射
        lcd = (unsigned int *)mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

        if (lcd == (void *)-1)
        {

            cout << "mmap error" << endl;
        }

        // 3.关闭LCD 设备
        close(fd);
    }

    // 析构函数解除映射
    ~Display()
    {
        munmap(this->lcd, 800 * 480 * 4);
    }

    // 显示 bmp 图片
    void show_bmp(const char *path)
    {

        // 1.打开图片文件
        int fd = open(path, O_RDWR);
        if (fd < 0)
        {
            cout << "打开图片文件失败:" << path << endl;
            return;
        }
        else
        {
            cout << "打开图片文件成功" << endl;
        }

        // 2.读取文件头
        char head[54] = {0};
        read(fd, head, 54);

        // 3.读取像素数据
        char color[800 * 480 * 3]; // 24位图
        read(fd, color, 800 * 480 * 3);

        char color32[800 * 480 * 4];

        for (int i = 0; i < 800 * 480; i++)
        {
            color32[i * 4 + 0] = color[i * 3 + 0]; // b
            color32[i * 4 + 1] = color[i * 3 + 1]; // g
            color32[i * 4 + 2] = color[i * 3 + 2]; // r
            color32[i * 4 + 3] = 0;                // a
        }

        // 图片反转显示
        int(*d_lcd)[800] = (int(*)[800])lcd;       // 把一维的LCD 转换为二维
        int(*d_color)[800] = (int(*)[800])color32; //// 把一维的color32 转换为二维

        for (int y = 0; y < 480; y++)
        {
            for (int x = 0; x < 800; x++)
            {
                d_lcd[y][x] = d_color[479 - y][x];
            }
        }
        // 关闭图片
        close(fd);
    }

private:
    unsigned int *lcd; // 映射地址
};

// 设计图片文件管理类
class pic_file
{
public:
    // 设计一个构造函数
    pic_file(const char *path = "/")
    {
        // 检索path 路径下的所有图片文件 ，并存储到 pic_path 中
        char cmd[1024] = {0};
        sprintf(cmd, "find  %s  -name  '*.bmp'", path);

        // 加载一个命令，并通过管道返回
        FILE *fp = popen(cmd, "r");
        if (fp == NULL)
        {
            cout << "查找文件失败" << endl;
        }

        // 读取命令返回的结果
        while (1)
        {
            char buf[1024] = {0};
            char *ret = fgets(buf, 1024, fp); // 自动添加换行符号
            if (ret == NULL)
            {
                cout << "检索完毕" << endl;
                break;
            }

            // 去掉换行符号
            // strstr(buf, "\n")[0] = '\0';
            char *p = strstr(buf, "\n");
            *p = '\0';

            // 存储图片路径名
            strcpy(pic_path[count], buf);

            // 图片数量增加
            count++;
        }

        // 关闭文件流
        pclose(fp);
    }

    // 设计根据下标返回图片路径接口
    char *get_index(int n)
    {
        if (n < 0 || n >= count)
        {
            cout << "越界访问" << endl;
            return NULL;
        }

        return pic_path[n];
    }

    // 返回图片总数
    int get_count()
    {
        return count;
    }

private:
    char pic_path[1024][1024]; // 存储所有图片路径
    int count;                 // 图片的真实数量
};

int main()
{

    // 面向对象: 1 . 设计类    2.利用对象完成功能代码

    // 对象+ 消息 = 程序

    // 定义触摸对象
    touch t;

    // 定义一个LCD 对象
    Display dp;

    // 文件管理器对象
    pic_file f;

    // 让这三个对象完成 电子相册的功能
    int in = 0;

    while (1)
    {
        // 获取滑动方向   1 上 2  下  3 左   4 右
        int direction = t.get_slide();

        // 根据方向切换图片
        if (direction == 2 || direction == 4) // 下一张
        {

            in++;

            if (in >= f.get_count()) // 超出最大图片数
            {
                in = 0;
            }
            // 显示图片
            dp.show_bmp(f.get_index(in));
        }

        // 根据方向切换图片
        if (direction == 1 || direction == 3) // 上一张
        {

            in--;

            if (in < 0) // 超出最大图片数
            {
                in = f.get_count() - 1;
            }
            // 显示图片
            dp.show_bmp(f.get_index(in));
        }
    }
}