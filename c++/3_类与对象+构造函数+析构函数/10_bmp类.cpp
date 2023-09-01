#include <iostream>

extern "C"
{
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
}

using namespace std;

class Bmp
{
public:
    Bmp(const char *name)
    {
        strcpy(bmpName, name);
    }
    ~Bmp() {}

    void setBmpName(const char *name)
    {
        strcpy(bmpName, name);
    }
    // 打开bmp图片
    int openBmp()
    {
        fd_bmp = open(bmpName, O_RDWR);
        if (fd_bmp < 0)
        {
            perror("open bmp fail");
            return -1;
        }
    }

    // 得到图片的宽度
    int getWidth()
    {
        // 读出任意bmp图片的宽度和高度
        lseek(fd_bmp, 18, SEEK_SET);
        read(fd_bmp, &width, 4); // 读出它的宽度
        printf("bmp width:%d\n", width);
        return width;
    }

    // 图片的高度
    int getHeight()
    {
        lseek(fd_bmp, 22, SEEK_SET);
        read(fd_bmp, &height, 4); // 读出它的高度
        printf("bmp height:%d\n", height);
        return height;
    }

    void showBmp(int x1,int y1)
    {
        //图片显示的坐标位置(offset_x,offset_y)
        offset_x = x1;
        offset_y = y1;

        // 打开lcd
        int fd_lcd = open("/dev/fb0", O_RDWR);
        if (fd_lcd < 0)
        {
            perror("open lcd fail");
        }
        // lcd的映射--mmap(相当于malloc了堆空间)
        int *addr = (int *)mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd_lcd, 0);
        if (addr == NULL)
        {
            perror("mmap fail");
        }
        // 去除掉bmp图片的头54个字节
        lseek(fd_bmp, 54, SEEK_SET);

        // 读取鸡哥图片信息
        char buf[width * height * 3];
        read(fd_bmp, buf, width * height * 3);


        // 将读取到的鸡哥图片信息写入到LCD中
        int x = 0; // 横轴
        int y = 0; // 纵轴
        for (y = 0; y < height; y++)
        {
            for (x = 0; x < width; x++)
            {

                *(addr + (offset_y + height - 1 - y) * 800 + offset_x + x) = buf[(y * width + x) * 3] |
                                                                             buf[(y * width + x) * 3 + 1] << 8 |
                                                                             buf[(y * width + x) * 3 + 2] << 16;
            }
        }

        // lcd映射的释放
        munmap(addr, 800 * 480 * 4); // 此条件一定要有
    }

private:
    char bmpName[10]; // bmp的文件名
    int fd_bmp;       // 文件描述符
    int width;        // bmp宽度
    int height;       // 高度

    int offset_x; //图片偏移 x轴坐标
    int offset_y; //图片偏移 y轴坐标  
};

int main()
{
    // 实例化一个对象
    Bmp b1("jige.bmp");

    //打开bmp图    
    b1.openBmp();

    //获取bmp图的宽度和高度
    cout <<"width:" <<b1.getWidth() << endl;
    cout <<"height:"<< b1.getHeight() << endl;

    //显示bmp图片
    b1.showBmp(0,0);

    return 0;
}