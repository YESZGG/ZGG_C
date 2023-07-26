#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>
#include "lcdjpg.h"
#include "jpeglib.h"
#include <sys/stat.h>
#include <string.h>

static char g_color_buf[FB_SIZE] = {0};

static int g_fb_fd;
static int *g_pfb_memory;

/* video_chat.c ?-?D?-??ê?μ?×?±ê */
volatile int g_jpg_in_jpg_x;
volatile int g_jpg_in_jpg_y;

unsigned long file_size_get(const char *pfile_path)
{
	unsigned long filesize = -1;
	struct stat statbuff;

	if (stat(pfile_path, &statbuff) < 0)
	{
		return filesize;
	}
	else
	{
		filesize = statbuff.st_size;
	}

	return filesize;
}
// LCD?-μ?
void lcd_draw_point(unsigned int x, unsigned int y, unsigned int color)
{
	*(g_pfb_memory + y * 800 + x) = color;
}

int lcd_draw_jpg(unsigned x, unsigned y, const char *pjpg_path, char *pjpg_buf, unsigned int jpg_buf_size, unsigned int jpg_half)
{
	// 打开LCD
	g_fb_fd = open("/dev/fb0", O_RDWR);

	if (g_fb_fd < 0)
	{
		printf("open lcd error\n");
		return -1;
	}

	g_pfb_memory = (int *)mmap(NULL,				   // ó3é???μ??aê?μ??·￡?éè???aNULLê±±íê?óé?μí3???¨ó3é???μ??eê?μ??·
							   FB_SIZE,				   // ó3é???μ?3¤?è
							   PROT_READ | PROT_WRITE, //?úèY?éò?±??áè?oíD′è?
							   MAP_SHARED,			   // 12?í?ú′?
							   g_fb_fd,				   // óDD§μ????t?èê?′ê
							   0					   // ±?ó3é????ó?úèYμ??eμ?
	);

	/*?¨ò??a?????ó￡?′í?ó′|àí???ó*/
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	char *pcolor_buf = g_color_buf;
	char *pjpg;

	unsigned int i = 0;
	unsigned int color = 0;
	unsigned int count = 0;

	unsigned int x_s = x;
	unsigned int x_e;
	unsigned int y_e;

	int jpg_fd;
	unsigned int jpg_size;

	unsigned int jpg_width;
	unsigned int jpg_height;
	memset(g_pfb_memory, 0, 800 * 480 * 4);
	if (pjpg_path != NULL)
	{
		/* éê??jpg×ê?′￡?è¨?T?é?á?éD′ */
		jpg_fd = open(pjpg_path, O_RDWR);

		if (jpg_fd == -1)
		{
			printf("open %s error\n", pjpg_path);

			return -1;
		}

		// 获取jpg文件大小
		jpg_size = file_size_get(pjpg_path);

		// 为jpg分配内存空间
		pjpg = malloc(jpg_size);

		// 读取jpg文件内容
		read(jpg_fd, pjpg, jpg_size);
	}
	else
	{
		jpg_size = jpg_buf_size;

		pjpg = pjpg_buf;
	}

	// 初始化jpeg解压对象
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	// 设置输入源
	jpeg_mem_src(&cinfo, pjpg, jpg_size);

	// 读取jpg头信息
	jpeg_read_header(&cinfo, TRUE);

	// 开始解压
	jpeg_start_decompress(&cinfo);
	if (jpg_half)
	{
		x_e = x_s + (cinfo.output_width / 2);
		y_e = y + (cinfo.output_height / 2);

		// 解压并绘制图片
		while (cinfo.output_scanline < cinfo.output_height)
		{
			pcolor_buf = g_color_buf;

			// 读取jpg的一行数据到rgb缓冲区
			jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&pcolor_buf, 1);

			// 读取jpg的一行数据到rgb缓冲区
			jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&pcolor_buf, 1);

			for (i = 0; i < (cinfo.output_width / 2); i++)
			{
				// 提取rgb颜色值
				color = *(pcolor_buf + 2);
				color = color | *(pcolor_buf + 1) << 8;
				color = color | *(pcolor_buf) << 16;

				// 绘制像素点
				lcd_draw_point(x, y, color);
				pcolor_buf += 6;
				x++;
			}
			/* ??DD */
			y++;
			x = x_s;
		}
	}
	else
	{
		x_e = x_s + cinfo.output_width;
		y_e = y + cinfo.output_height;

		// 解压并绘制图片
		while (cinfo.output_scanline < cinfo.output_height)
		{
			pcolor_buf = g_color_buf;

			// 读取jpg的一行数据到rgb缓冲区
			jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&pcolor_buf, 1);

			for (i = 0; i < cinfo.output_width; i++)
			{
				/* ??è?rgb?μ */
				color = *(pcolor_buf + 2);
				color = color | *(pcolor_buf + 1) << 8;
				color = color | *(pcolor_buf) << 16;

				/* ??ê?????μ? */
				lcd_draw_point(x, y, color);
				pcolor_buf += 3;
				x++;
			}
			/* ??DD */
			y++;
			x = x_s;
		}
	}

	/*?a??íê3é*/
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	if (pjpg_path != NULL)
	{
		/* 1?±?jpg???t */
		close(jpg_fd);

		/* êí·?jpg???t?ú′????? */
		free(pjpg);
	}
	// LCD1?±?
	/* è????ú′?ó3é? */
	munmap(g_pfb_memory, FB_SIZE);

	/* 1?±?LCDéè±? */
	close(g_fb_fd);
	return 0;
}

int lcd_draw_jpg_centered(const char *pjpg_path, char *pjpg_buf, unsigned int jpg_buf_size, unsigned int jpg_half)
{
    // 打开LCD
    g_fb_fd = open("/dev/fb0", O_RDWR);

    if (g_fb_fd < 0)
    {
        printf("open lcd error\n");
        return -1;
    }

    g_pfb_memory = (int *)mmap(NULL, FB_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, g_fb_fd, 0);

    // 获取屏幕宽度和高度
    unsigned int screen_width = 800; // 修改为实际屏幕宽度
    unsigned int screen_height = 420; // 修改为实际屏幕高度

    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    char *pcolor_buf = g_color_buf;
    char *pjpg;

    unsigned int i = 0;
    unsigned int color = 0;

    unsigned int x_s, y_s;
    unsigned int x_e, y_e;

    int jpg_fd;
    unsigned int jpg_size;

    memset(g_pfb_memory, 0, screen_width * screen_height * 4);

    if (pjpg_path != NULL)
    {
        /* 打开jpg文件 */
        jpg_fd = open(pjpg_path, O_RDWR);

        if (jpg_fd == -1)
        {
            printf("open %s error\n", pjpg_path);
            return -1;
        }

        // 获取jpg文件大小
        jpg_size = file_size_get(pjpg_path);

        // 为jpg分配内存空间
        pjpg = malloc(jpg_size);

        // 读取jpg文件内容
        read(jpg_fd, pjpg, jpg_size);
    }
    else
    {
        jpg_size = jpg_buf_size;
        pjpg = pjpg_buf;
    }

    // 初始化jpeg解压对象
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    // 设置输入源
    jpeg_mem_src(&cinfo, pjpg, jpg_size);

    // 读取jpg头信息
    jpeg_read_header(&cinfo, TRUE);

    // 开始解压
    jpeg_start_decompress(&cinfo);

    unsigned int jpg_width = cinfo.output_width;
    unsigned int jpg_height = cinfo.output_height;

    // 计算居中显示时的起始坐标
    x_s = (screen_width - jpg_width) / 2;
    y_s = (screen_height - jpg_height) / 2;

    if (jpg_half)
    {
        x_e = x_s + (cinfo.output_width / 2);
        y_e = y_s + (cinfo.output_height / 2);
    }
    else
    {
        x_e = x_s + cinfo.output_width;
        y_e = y_s + cinfo.output_height;
    }

    // 解压并绘制图片
    unsigned int x = x_s;
    unsigned int y = y_s;

    while (cinfo.output_scanline < cinfo.output_height)
    {
        pcolor_buf = g_color_buf;
        jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&pcolor_buf, 1);

        if (jpg_half)
        {
            // 绘制图片的一半宽度
            for (unsigned int i = 0; i < (cinfo.output_width / 2); i++)
            {
                color = *(pcolor_buf + 2);
                color = color | (*(pcolor_buf + 1) << 8);
                color = color | (*(pcolor_buf) << 16);

                lcd_draw_point(x, y, color);
                pcolor_buf += 6;
                x++;
            }
        }
        else
        {
            // 绘制整个图片宽度
            for (unsigned int i = 0; i < cinfo.output_width; i++)
            {
                color = *(pcolor_buf + 2);
                color = color | (*(pcolor_buf + 1) << 8);
                color = color | (*(pcolor_buf) << 16);

                lcd_draw_point(x, y, color);
                pcolor_buf += 3;
                x++;
            }
        }

        y++;
        x = x_s;
    }

    /* 完成解压 */
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    if (pjpg_path != NULL)
    {
        /* 关闭jpg文件 */
        close(jpg_fd);

        /* 释放jpg内存 */
        free(pjpg);
    }

    // 关闭LCD
    munmap(g_pfb_memory, FB_SIZE);
    close(g_fb_fd);
    return 0;
}

