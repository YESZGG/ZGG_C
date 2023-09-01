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

// 封装一个LCD的类
class Lcd
{
public:
    Lcd(const char *lcdPath) // 构造函数
    {
        cout<<"Lcd(const char *lcdPath) "<<endl;
        strcpy(this->lcdPath, lcdPath);
    }

    // 带参数列表的构造函数
    //  Lcd(const char *lcdPath):lcdPath("/dev/fb0")
    //  {
    //  }
    ~Lcd() //析构函数
    {
        cout<<" ~Lcd()"<<endl;
        // lcd映射的释放
        munmap(addr, 800 * 480 * 4); // 此条件一定要有

    } 

    //枚举
    enum COLOR{RED = 0x00ff0000,GREEN = 0x0000ff00,BLUE = 0x000000ff};

    // lcd的初始化
    void initLcd()
    {
        // 打开lcd
        fd_lcd = open("/dev/fb0", O_RDWR);
        if (fd_lcd < 0)
        {
            perror("open lcd fail");
        }
        // lcd的映射--mmap(相当于malloc了堆空间)
        addr = (int *)mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd_lcd, 0);
        if (addr == NULL)
        {
            perror("mmap fail");
        }
    }

    // 显示颜色
    void showColor(int color)
    {
        int x = 0; // 横轴
        int y = 0; // 纵轴
        for (y = 0; y < 480; y++)
        {
            for (x = 0; x < 800; x++)
            {
                // addr+y*800+x -->地址偏移
                //*(addr+y*800+x) -->解引用（给地址指向那个像素点赋值）
                *(addr + y * 800 + x) = color;
            }
        }
    }

    // 关闭lcd
    void closeLcd()
    {
        close(fd_lcd);
    }

private:
    char lcdPath[20]; //"/dev/fb0"
    int fd_lcd;       // 文件描述符
    int *addr;        // lcd映射地址
};

int main()
{
    //实例化一个lcd的对象
    Lcd lcdDvice("/dev/fb0");

    //初始化lcd --fd_lcd和addr
    lcdDvice.initLcd();

    //显示颜色
    lcdDvice.showColor(Lcd::GREEN); //注意在ubuntu里面次代码无法执行需要在开发板中跑代码

    //关闭lcd
    lcdDvice.closeLcd();

    return 0;
}
