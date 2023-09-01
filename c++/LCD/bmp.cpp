#include "bmp.h"

using namespace std;

#define BUFFER_SIZE 800 * 480
#define lcdWidth 800
#define lcdHeight 480

BMP::BMP()
{
}

void BMP::showBMP(const char *pathname, unsigned int *addr)
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
    cout << "BMP SIZE: " << (double)bmpInfo.fileSize / 1024.00 << " KB" << endl;
    int bmpWidth = bmpInfo.width;
    int bmpHeight = bmpInfo.height;

    // 验证BMP图像和LCD屏幕尺寸之间的兼容性
    if (bmpWidth > lcdWidth || bmpHeight > lcdHeight)
    {
        cerr << "BMP image dimensions exceed the LCD screen dimensions" << endl;
        fclose(bmp_fp);
        return;
    }

    fseek(bmp_fp, bmpInfo.dataOffset, SEEK_SET);

    unsigned char color[bmpWidth * bmpHeight * 3];
    fread(color, 1, bmpWidth * bmpHeight * 3, bmp_fp);

    int offset_x = (lcdWidth - bmpWidth) / 2;   // 计算图像居中的水平偏移
    int offset_y = (lcdHeight - bmpHeight) / 2; // 计算图像居中的垂直偏移

    // for (int y = 0; y < height; y++)
    // {
    //     for (int x = 0; x < width; x++)
    //     {
    //         // 遇到白色就跳过，不绘画，可将0xffffff修改成不需要的颜色
    //         //  if (*(addr + (offset_y + height - 1 - y) * 800 + offset_x + x) == 0x00ffffff)
    //         //  {
    //         //      continue;
    //         //  }
    //         //  将读取出来的图片数据的每个像素点 BGR ---转换成 ARGB
    //         unsigned char blue = color[(y * width + x) * 3];
    //         unsigned char green = color[(y * width + x) * 3 + 1];
    //         unsigned char red = color[(y * width + x) * 3 + 2];

    //         *(addr + (offset_y + height - 1 - y) * 800 + offset_x + x) =
    //             (red << 16) | (green << 8) | blue;
    //     }
    // }

    char color32[lcdWidth * lcdHeight * 4] = {0};

    for (int y = 0; y < bmpHeight; y++)
    {
        for (int x = 0; x < bmpWidth; x++)
        {
            int sourceIndex = ((bmpHeight - y - 1) * bmpWidth + x) * 3;
            int targetIndex = ((offset_y + y) * lcdWidth + offset_x + x) * 4;
            color32[targetIndex + 0] = color[sourceIndex + 0];
            color32[targetIndex + 1] = color[sourceIndex + 1];
            color32[targetIndex + 2] = color[sourceIndex + 2];
            color32[targetIndex + 3] = 0;
        }
    }

    int(*d_lcd)[lcdWidth] = (int(*)[lcdWidth])addr;
    int(*d_color)[lcdWidth] = (int(*)[lcdWidth])color32;

    for (int y = 0; y < lcdHeight; y++)
    {
        for (int x = 0; x < lcdWidth; x++)
        {
            d_lcd[y][x] = d_color[y][x];
        }
    }

    // 关闭文件描述符
    fclose(bmp_fp);
}

// 指定位置显示图片
void BMP::showBMP(const char *pathname, unsigned int *addr, int startX, int startY)
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
    cout << "BMP SIZE: " << (double)bmpInfo.fileSize / 1024.00 << " KB" << endl;

    int bmpWidth = bmpInfo.width;
    int bmpHeight = bmpInfo.height;

    // 验证BMP图像和LCD屏幕尺寸之间的兼容性
    if (bmpWidth > 800 || bmpHeight > 480)
    {
        cerr << "BMP image dimensions exceed the LCD screen dimensions" << endl;
        fclose(bmp_fp);
        return;
    }

    fseek(bmp_fp, bmpInfo.dataOffset, SEEK_SET);

    unsigned char color[bmpWidth * bmpHeight * 3];
    fread(color, 1, bmpWidth * bmpHeight * 3, bmp_fp);

    int offset_x = startX; // 指定图像的水平起始位置
    int offset_y = startY; // 指定图像的垂直起始位置

#if 0
//  使用指针映射
    for (int y = 0; y < bmpHeight; y++)
    {
        for (int x = 0; x < bmpWidth; x++)
        {
            // 遇到白色就跳过，不绘画，可将0xffffff修改成不需要的颜色
            // if (*(addr + (offset_y + bmpHeight - 1 - y) * 800 + offset_x + x) == 0x00ffffff)
            // {
            //     continue;
            // }
            unsigned char blue = color[(y * bmpWidth + x) * 3];
            unsigned char green = color[(y * bmpWidth + x) * 3 + 1];
            unsigned char red = color[(y * bmpWidth + x) * 3 + 2];

            *(addr + (offset_y + bmpHeight - 1 - y) * 800 + offset_x + x) =
                (red << 16) | (green << 8) | blue;
        }
    }
#endif
    char color32[lcdWidth * lcdHeight * 4] = {0};

    for (int y = 0; y < bmpHeight; y++)
    {
        for (int x = 0; x < bmpWidth; x++)
        {
            int sourceIndex = ((bmpHeight - y - 1) * bmpWidth + x) * 3;
            int targetIndex = ((offset_y + y) * lcdWidth + offset_x + x) * 4;
            color32[targetIndex + 0] = color[sourceIndex + 0];
            color32[targetIndex + 1] = color[sourceIndex + 1];
            color32[targetIndex + 2] = color[sourceIndex + 2];
            color32[targetIndex + 3] = 0;
        }
    }

    int(*d_lcd)[lcdWidth] = (int(*)[lcdWidth])addr;
    int(*d_color)[lcdWidth] = (int(*)[lcdWidth])color32;

    for (int y = 0; y < lcdHeight; y++)
    {
        for (int x = 0; x < lcdWidth; x++)
        {
            d_lcd[y][x] = d_color[y][x];
        }
    }

    // 关闭文件描述符
    fclose(bmp_fp);
}
