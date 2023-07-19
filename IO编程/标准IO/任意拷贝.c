/*
 * @Description:任意拷贝
 * @version:
 * @Author: ZGG
 * @Date: 2023-07-17 20:40:25
 * @LastEditors: ZGG
 * @LastEditTime: 2023-07-19 10:25:37
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFF_SIZE 1024

void print_progress(double percentage)
{
    int bar_width = 50;
    int filled_width = bar_width * percentage;
    printf("[");
    for (int i = 0; i < bar_width; i++)
    {
        if (i < filled_width)
            printf("=");
        else
            printf(" ");
    }
    printf("] %.2f%%\r", percentage * 100);
    fflush(stdout);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Uage:%s <src> <dst>\n", argv[0]);
        return -1;
    }

    char *source_file = argv[1]; // 源文件
    char *target_file = argv[2]; // 目标文件

    // 创建源文件指针
    FILE *source_fp = fopen(source_file, "r+");
    if (source_fp == NULL)
    {
        perror("fopen source_file fail.");
        return -1;
    }
    // 创建目标文件指针
    FILE *target_fp = fopen(target_file, "w+");
    if (target_fp == NULL)
    {
        perror("fopen or create target_file fail.");
        fclose(source_fp);
        return -1;
    }

    // 计算文件大小
    /*     fseek函数
    成功：返回0     失败：返回-1
           ftell函数
    成功：返回当前的偏移量  失败：返回-1
    */
    fseek(source_fp, 0, SEEK_END);
    long fileSize = ftell(source_fp);
    if (fileSize == -1)
    {
        perror("获取源文件大小失败");
        fclose(source_fp);
        fclose(target_fp);
        return -1;
    }

    // 将文件光标位置移回文件开头
    // 这个无法确认是否成功移回     fseek(source_fp,0,SEEK_SET);
    // rewind “一键”返回文件开头
    rewind(source_fp);

    // 创建缓冲区
    char buf[BUFF_SIZE];
    memset(buf, 0, sizeof(BUFF_SIZE));
    printf("\n");
    int freadBytes, fwriteBytes, totalBytes = 0;
    while (freadBytes = fread(buf, 1, sizeof(buf), source_fp))
    {
        fwriteBytes = fwrite(buf, 1, freadBytes, target_fp);
        if (freadBytes != fwriteBytes)
        {
            perror("拷贝失败.");
            fclose(source_fp);
            fclose(target_fp);
            return -1;
        }
        totalBytes += fwriteBytes;
        double progress = (double)totalBytes / fileSize;
        print_progress(progress);
    }
    if (ferror(source_fp))
    {
        perror("写入目标文件失败.");
        fclose(source_fp);
        fclose(target_fp);
        return -1;
    }

    printf("成功将 %s 拷贝到 %s\n", source_file, target_file);

    if (fclose(source_fp) == EOF)
    {
        perror("fclose source_file fail.");
        return -1;
    }

    if (fclose(target_fp) == EOF)
    {
        perror("fclose target_file fail.");
        return -1;
    }

    return 0;
}
