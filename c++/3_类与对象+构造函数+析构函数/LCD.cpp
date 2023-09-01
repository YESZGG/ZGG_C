#include <iostream>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cmath>
extern "C"
{
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <error.h>
}

using namespace std;

#define BUFFER_SIZE 800 * 480


#pragma pack(push, 1) // 确保按照字节对齐方式为1字节对齐
struct BMPHeader
{
    char signature[2];            // 文件标识，必须为 "BM"
    uint32_t fileSize;            // 文件大小（字节）
    uint32_t reserved;            // 保留字，设置为0
    uint32_t dataOffset;          // 数据偏移量（相对于文件头的字节数）
    uint32_t headerSize;          // 位图信息头大小（字节）
    int32_t width;                // 图像宽度（像素）
    int32_t height;               // 图像高度（像素）
    uint16_t colorPlanes;         // 颜色平面数（固定为1）
    uint16_t bitsPerPixel;        // 每像素位数
    uint32_t compressionType;     // 压缩类型
    uint32_t imageSize;           // 图像数据大小（字节）
    int32_t horizontalResolution; // 水平分辨率（像素/米）
    int32_t verticalResolution;   // 垂直分辨率（像素/米）
    uint32_t colorsInPalette;     // 调色板颜色数量
    uint32_t importantColors;     // 紧要颜色数量
};
#pragma pack(pop) // 恢复默认字节对齐方式

class LCD
{
private:
    int fd_lcd;
    unsigned int *addr;
    const char lcdPath[20];

public:
    // 构造函数
    LCD();
    // 析构函数
    ~LCD();
    // 颜色
    enum COLOR
    {
        RED = 0X00FF0000,
        GREEN = 0x0000FF00,
        BLUE = 0x000000FF,
        BLACK = 0x00000000,
        WHITE = 0x00FFFFFF
    };
    bool openLcd();
    bool mapMemory();
    void closeLcd();
    void unmapMemory();
    void displayColor(unsigned int color);
    void showBMP(const char *pathname);
    void showBMP(const char *pathname, int startX, int startY);
};

LCD::LCD() : fd_lcd(-1), addr(NULL), lcdPath("/dev/fb0") // 参数列表初始化
{
}

LCD::~LCD()
{
    unmapMemory();
}

// 打开LCD
bool LCD::openLcd()
{
    fd_lcd = open(this->lcdPath, O_RDWR);
    if (fd_lcd < 0)
    {
        return false;
    }
    return true;
}

// 关闭LCD文件描述符
void LCD::closeLcd()
{
    close(fd_lcd);
    fd_lcd = -1;
}

// 映射mmap
bool LCD::mapMemory()
{
    addr = static_cast<unsigned int *>(mmap(NULL, BUFFER_SIZE * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd_lcd, 0));
    if (addr == MAP_FAILED)
    {
        cerr << "Failed to map memory" << endl;
        return false;
    }
    return true;
}

// 解除映射
void LCD::unmapMemory()
{
    munmap(addr, BUFFER_SIZE * 4);
    addr = NULL;
}

// 显示指定颜色
void LCD::displayColor(unsigned int color)
{
    for (int y = 0; y < 480; y++)
    {
        for (int x = 0; x < 800; x++)
        {
            *(addr + y * 800 + x) = color;
        }
    }
}

// 显示出800*480的范围内的bmp图片并且居中显示
void LCD::showBMP(const char *pathname)
{
    memset(addr, 0, BUFFER_SIZE * 4);
    // 打开BMP文件
    FILE *bmp_fp = fopen(pathname, "rb");
    if (bmp_fp == NULL)
    {
        perror("Failed to open BMP file");
        return;
    }

    // 读取BMP标头信息
    BMPHeader bmpInfo;
    fread(&bmpInfo, sizeof(BMPHeader), 1, bmp_fp);

    // 检查BMP文件的有效性
    if (memcmp(bmpInfo.signature, "BM", 2) != 0)
    {
        cerr << "Invalid BMP file" << endl;
        fclose(bmp_fp);
        return;
    }

    // 打印图像信息
    cout << "Width: " << bmpInfo.width << endl;
    cout << "Height: " << bmpInfo.height << endl;
    cout << "BMP SIZE: " << bmpInfo.fileSize << endl;
    int width = bmpInfo.width;
    int height = bmpInfo.height;

    // 验证BMP图像和LCD屏幕尺寸之间的兼容性
    if (width > 800 || height > 480)
    {
        cerr << "BMP image dimensions exceed the LCD screen dimensions" << endl;
        fclose(bmp_fp);
        return;
    }

    fseek(bmp_fp, bmpInfo.dataOffset, SEEK_SET);

    unsigned char buf[width * height * 3];
    fread(buf, 1, width * height * 3, bmp_fp);

    int offset_x = (800 - width) / 2;  // 计算图像居中的水平偏移
    int offset_y = (480 - height) / 2; // 计算图像居中的垂直偏移

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // 遇到白色就跳过，不绘画，可将0xffffff修改成不需要的颜色
            //  if (*(addr + (offset_y + height - 1 - y) * 800 + offset_x + x) == 0x00ffffff)
            //  {
            //      continue;
            //  }
            //  将读取出来的图片数据的每个像素点 BGR ---转换成 ARGB
            unsigned char blue = buf[(y * width + x) * 3];
            unsigned char green = buf[(y * width + x) * 3 + 1];
            unsigned char red = buf[(y * width + x) * 3 + 2];

            *(addr + (offset_y + height - 1 - y) * 800 + offset_x + x) =
                (red << 16) | (green << 8) | blue;
        }
    }
    // 关闭文件描述符
    fclose(bmp_fp);
}

// 指定位置显示图片
void LCD::showBMP(const char *pathname, int startX, int startY)
{
    memset(addr, 0, BUFFER_SIZE * 4);
    // 打开BMP文件
    FILE *bmp_fp = fopen(pathname, "rb");
    if (bmp_fp == NULL)
    {
        perror("Failed to open BMP file");
        return;
    }

    // 读取BMP标头信息
    BMPHeader bmpInfo;
    fread(&bmpInfo, sizeof(BMPHeader), 1, bmp_fp);

    // 检查BMP文件的有效性
    if (memcmp(bmpInfo.signature, "BM", 2) != 0)
    {
        cerr << "Invalid BMP file" << endl;
        fclose(bmp_fp);
        return;
    }

    // 打印图像信息
    cout << "Width: " << bmpInfo.width << endl;
    cout << "Height: " << bmpInfo.height << endl;

    int width = bmpInfo.width;
    int height = bmpInfo.height;

    // 验证BMP图像和LCD屏幕尺寸之间的兼容性
    if (width > 800 || height > 480)
    {
        cerr << "BMP image dimensions exceed the LCD screen dimensions" << endl;
        fclose(bmp_fp);
        return;
    }

    fseek(bmp_fp, bmpInfo.dataOffset, SEEK_SET);

    unsigned char buf[width * height * 3];
    fread(buf, 1, width * height * 3, bmp_fp);

    int offset_x = startX; // 指定图像的水平起始位置
    int offset_y = startY; // 指定图像的垂直起始位置

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // 遇到白色就跳过，不绘画，可将0xffffff修改成不需要的颜色
            // if (*(addr + (offset_y + height - 1 - y) * 800 + offset_x + x) == 0x00ffffff)
            // {
            //     continue;
            // }
            unsigned char blue = buf[(y * width + x) * 3];
            unsigned char green = buf[(y * width + x) * 3 + 1];
            unsigned char red = buf[(y * width + x) * 3 + 2];

            *(addr + (offset_y + height - 1 - y) * 800 + offset_x + x) =
                (red << 16) | (green << 8) | blue;
        }
    }
    // 关闭文件描述符
    fclose(bmp_fp);
}

int main()
{
    LCD lcd;

    if (!lcd.openLcd())
    {
        cerr << "Failed to open LCD" << endl;
        return -1;
    }

    if (!lcd.mapMemory())
    {
        lcd.closeLcd();
        return -1;
    }

    lcd.displayColor(LCD::WHITE);

    sleep(2); // 等待5秒钟

    lcd.showBMP("1.bmp");
    sleep(3);
    lcd.showBMP("1.bmp", 0, 0);

    lcd.closeLcd();

    return 0;
}
