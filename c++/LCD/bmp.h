#ifndef BMP_H
#define BMP_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

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
class BMP
{
public:
    BMP();
    void showBMP(const char *pathname, unsigned int *addr);
    void showBMP(const char *pathname, unsigned int *addr, int startX, int startY);
};

#endif // BMP_H
