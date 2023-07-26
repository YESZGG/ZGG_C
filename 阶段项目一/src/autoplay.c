#include "autoplay.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// 处理自动播放界面的input事件
int playAutoshow(Node *head, Node **current, int *addr, int startX, int startY, int endX, int endY)
{
    // EXIT: 退出到主界面
    if ((startX > 600 && endX < 800) && (startY > 420 && endY < 480))
    {
        currentScreen = MainMenu;

        FILE *fp_menu = fopen("desktop.bmp", "r+");
        if (fp_menu == NULL)
        {
            perror("fopen bmp fail.");
            return -1;
        }

        if (show_return_menu(addr, fp_menu) != 0)
        {
            fclose(fp_menu);
            return -1;
        }
        fclose(fp_menu);
        return -1;
    }

    while (1)
    {
        // 使用不同模式显示当前BMP图像
        if ((*current)->type == 'b')
        {
            // 根据图像的编号获取显示模式
            int mode = (*current)->num % 5;

            switch (mode)
            {
            case 0:
                displayBMPImageBlinds((*current)->filename, addr); // 百叶窗模式显示
                break;
            case 1:
                displayBMPImageExpandingInward((*current)->filename, addr); // 从侧面向中心展开
                break;
            case 2:
                displayBMPImageExpandingOutward((*current)->filename, addr); // 从中心向两侧扩展
                break;
            case 3:
                displayBMPImage_openScreen1((*current)->filename, addr); // 将宽度分成了6份，1，3，5向右展示，2，4，6向左展示
                break;
            case 4:
                displayBMPImage_openScreen2((*current)->filename, addr); // 实现将图片高度分割成6份，1，3，5从左边向右显示，2，4，6从右向左显示
                break;
            default:
                displayBMPImage((*current)->filename, addr); // 默认显示没有任何效果
                break;
            }
        }
        else if ((*current)->type == 'j')
        {
            displayJPEGImage((*current)->filename);
        }

        sleep(2); // 等待2秒

        *current = (*current)->next; // 移动到下一张图片

        // 如果到了链表尾，则跳出循环
        if (*current == head)
        {
            break;
        }
    }
    return 0;
}

// 显示自动动播放界面
int show_Auto_play(int *addr, FILE *fp_auto_play)
{
    if (fp_auto_play == NULL)
    {
        fprintf(stderr, "File pointer is null.\n");
        return -1;
    }

    // 清空LCD显示
    memset(addr, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);

    fseek(fp_auto_play, 18, SEEK_SET);
    int width, height;
    if (fread(&width, sizeof(width), 1, fp_auto_play) != 1 ||
        fread(&height, sizeof(height), 1, fp_auto_play) != 1)
    {
        fprintf(stderr, "Failed to read image width and height.\n");
        return -1;
    }

    int offset_x = (SCREEN_WIDTH - width) / 2;
    int offset_y = (SCREEN_HEIGHT - height) / 2;

    show_bmp_image(addr, fp_auto_play, offset_x, offset_y);

    return 0;
}

// 实现百叶窗效果
void displayBMPImageBlinds(const char *filename, int *addr)
{
    int screen_width = 800;
    int screen_height = 420;

    FILE *fp_bmp = fopen(filename, "r");
    if (fp_bmp == NULL)
    {
        perror("fopen bmp fail.");
        return;
    }

    // 获取图片的宽度和高度
    fseek(fp_bmp, 18, SEEK_SET);
    int width = 0, height = 0;
    if (fread(&width, sizeof(width), 1, fp_bmp) != 1 ||
        fread(&height, sizeof(height), 1, fp_bmp) != 1)
    {
        fprintf(stderr, "Failed to read image width and height.\n"); // 标准出错
        fclose(fp_bmp);
        return;
    }

    int offset_x = (screen_width - width) / 2;
    int offset_y = (screen_height - height) / 2;

    fseek(fp_bmp, 54, SEEK_SET);

    unsigned char buf[width * height * 3];
    memset(buf, 0, sizeof(buf));
    if (fread(buf, 1, sizeof(buf), fp_bmp) != sizeof(buf))
    {
        fprintf(stderr, "Failed to read image data.\n"); // 标准出错
        fclose(fp_bmp);
        return;
    }
    int blinds_count = 3;
    int blinds_height = height / blinds_count;
    int remaining_rows = height % blinds_count;

    for (int i = 0; i < blinds_count; i++)
    {
        int pid = fork();
        if (pid == -1)
        {
            // 进程报错
            perror("Fork error.");
            fclose(fp_bmp);
            return;
        }
        else if (pid == 0)
        {
            int start_row = i * blinds_height;
            int end_row = start_row + blinds_height;
            if (i == blinds_count - 1)
            {
                end_row += remaining_rows;
            }

            for (int y = start_row; y < end_row; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    *(addr + (offset_y + height - 1 - y) * screen_width + offset_x + x) =
                        buf[(y * width + x) * 3] |
                        buf[(y * width + x) * 3 + 1] << 8 |
                        buf[(y * width + x) * 3 + 2] << 16;
                }
                usleep(10000);
            }

            // 退出子进程
            exit(0);
        }
    }

    // 等待所有子进程完成
    while (wait(NULL) > 0)
        ;

    fclose(fp_bmp);
}

// 实现图片从中间向两边显示
void displayBMPImageExpandingOutward(const char *filename, int *addr)
{
    // 清空目标内存
    memset(addr, 0, 800 * 420 * 4);

    // 打开 BMP 文件
    FILE *fp_bmp = fopen(filename, "r");
    if (fp_bmp == NULL)
    {
        perror("fopen bmp fail.");
        return;
    }

    // 获取图片宽度和高度
    fseek(fp_bmp, 18, SEEK_SET);
    int width = 0, height = 0;
    if (fread(&width, sizeof(width), 1, fp_bmp) != 1 ||
        fread(&height, sizeof(height), 1, fp_bmp) != 1)
    {
        fprintf(stderr, "Failed to read image width and height.\n");
        fclose(fp_bmp);
        return;
    }

    // 计算图片在屏幕上的偏移量
    int offset_x = (SCREEN_WIDTH - width) / 2;
    int offset_y = (SCREEN_HEIGHT - 60 - height) / 2;

    fseek(fp_bmp, 54, SEEK_SET);

    // 读取图片数据
    unsigned char buf[width * height * 3];
    memset(buf, 0, sizeof(buf));
    if (fread(buf, 1, sizeof(buf), fp_bmp) != sizeof(buf))
    {
        fprintf(stderr, "Failed to read image data.\n");
        fclose(fp_bmp);
        return;
    }

    int mid_x = offset_x + width / 2; // 中心位置
    int left_x = mid_x - 1;           // 左边界位置
    int right_x = mid_x + width % 2;  // 右边界位置

    while (left_x >= offset_x && right_x < offset_x + width)
    {
        for (int y = 0; y < height; y++)
        {
            // 复制像素到屏幕上（左右对称）
            *(addr + (offset_y + height - 1 - y) * SCREEN_WIDTH + left_x) =
                buf[y * width * 3 + (left_x - offset_x) * 3] |
                buf[y * width * 3 + (left_x - offset_x) * 3 + 1] << 8 |
                buf[y * width * 3 + (left_x - offset_x) * 3 + 2] << 16;

            *(addr + (offset_y + height - 1 - y) * SCREEN_WIDTH + right_x) =
                buf[y * width * 3 + (right_x - offset_x) * 3] |
                buf[y * width * 3 + (right_x - offset_x) * 3 + 1] << 8 |
                buf[y * width * 3 + (right_x - offset_x) * 3 + 2] << 16;
        }

        left_x--;
        right_x++;

        usleep(10000); // 延迟10毫秒
    }

    fclose(fp_bmp);
}

#if 1
// 实现图片从两边往中间展开显示
void displayBMPImageExpandingInward(const char *filename, int *addr)
{
    // 清空目标内存
    memset(addr, 0, 800 * 420 * 4);

    // 打开 BMP 文件
    FILE *fp_bmp = fopen(filename, "r");
    if (fp_bmp == NULL)
    {
        perror("fopen bmp fail.");
        return;
    }

    // 获取图片宽度和高度
    fseek(fp_bmp, 18, SEEK_SET);
    int width = 0, height = 0;
    if (fread(&width, sizeof(width), 1, fp_bmp) != 1 ||
        fread(&height, sizeof(height), 1, fp_bmp) != 1)
    {
        fprintf(stderr, "Failed to read image width and height.\n");
        fclose(fp_bmp);
        return;
    }

    // 计算图片在屏幕上的偏移量
    int offset_x = (SCREEN_WIDTH - width) / 2;
    int offset_y = (SCREEN_HEIGHT - 60 - height) / 2;

    fseek(fp_bmp, 54, SEEK_SET);

    // 读取图片数据
    unsigned char buf[width * height * 3];
    memset(buf, 0, sizeof(buf));
    if (fread(buf, 1, sizeof(buf), fp_bmp) != sizeof(buf))
    {
        fprintf(stderr, "Failed to read image data.\n");
        fclose(fp_bmp);
        return;
    }

    int left_x = offset_x;              // 左边界位置
    int right_x = offset_x + width - 1; // 右边界位置

    while (left_x <= right_x)
    {
        for (int y = 0; y < height; y++)
        {
            // 复制左边像素到屏幕上
            *(addr + (offset_y + height - 1 - y) * SCREEN_WIDTH + left_x) =
                buf[y * width * 3 + (left_x - offset_x) * 3] |
                buf[y * width * 3 + (left_x - offset_x) * 3 + 1] << 8 |
                buf[y * width * 3 + (left_x - offset_x) * 3 + 2] << 16;

            // 复制右边像素到屏幕上
            *(addr + (offset_y + height - 1 - y) * SCREEN_WIDTH + right_x) =
                buf[y * width * 3 + (right_x - offset_x) * 3] |
                buf[y * width * 3 + (right_x - offset_x) * 3 + 1] << 8 |
                buf[y * width * 3 + (right_x - offset_x) * 3 + 2] << 16;
        }

        left_x++;
        right_x--;

        usleep(10000); // 延迟10毫秒
    }

    fclose(fp_bmp);
}
#endif

#if 1

// 将宽度分成了6份，1，3，5向右展示，2，4，6向左展示
void displayBMPImage_openScreen1(const char *filename, int *addr)
{
    // 清空目标内存
    memset(addr, 0, 800 * 420 * 4);

    // 打开 BMP 文件
    FILE *fp_bmp = fopen(filename, "rb");
    if (fp_bmp == NULL)
    {
        perror("fopen bmp fail.");
        return;
    }

    // 获取图片宽度和高度
    fseek(fp_bmp, 18, SEEK_SET);
    int width = 0, height = 0;
    if (fread(&width, sizeof(width), 1, fp_bmp) != 1 ||
        fread(&height, sizeof(height), 1, fp_bmp) != 1)
    {
        fprintf(stderr, "Failed to read image width and height.\n");
        fclose(fp_bmp);
        return;
    }

    // 计算图片在屏幕上的偏移量
    int offset_x = (SCREEN_WIDTH - width) / 2;
    int offset_y = (SCREEN_HEIGHT - 60 - height) / 2;

    fseek(fp_bmp, 54, SEEK_SET);

    // 读取图片数据
    unsigned char buf[width * height * 3];
    memset(buf, 0, sizeof(buf));
    if (fread(buf, 1, sizeof(buf), fp_bmp) != sizeof(buf))
    {
        fprintf(stderr, "Failed to read image data.\n");
        fclose(fp_bmp);
        return;
    }

    fclose(fp_bmp);

    int left_x = offset_x;              // 左边界位置
    int right_x = offset_x + width - 1; // 右边界位置

    int segment_width = width / 6; // 切割后每个段的宽度
    int segment_height = height;   // 切割后每个段的高度

    for (int i = 0; i < 6; i++)
    {
        int start_x = offset_x + i * segment_width; // 当前段的起始横坐标
        int end_x = start_x + segment_width - 1;    // 当前段的结束横坐标

        if (i % 2 == 0)
        {
            // 从左边进入
            for (int x = start_x; x <= end_x; x++)
            {
                for (int y = 0; y < segment_height; y++)
                {
                    *(addr + (offset_y + height - 1 - y) * SCREEN_WIDTH + x) =
                        buf[y * width * 3 + (x - offset_x) * 3] |
                        buf[y * width * 3 + (x - offset_x) * 3 + 1] << 8 |
                        buf[y * width * 3 + (x - offset_x) * 3 + 2] << 16;
                }
                usleep(10000);
            }
        }
        else
        {
            // 从右边进入
            for (int x = end_x; x >= start_x; x--)
            {
                for (int y = 0; y < segment_height; y++)
                {
                    *(addr + (offset_y + height - 1 - y) * SCREEN_WIDTH + x) =
                        buf[y * width * 3 + (x - offset_x) * 3] |
                        buf[y * width * 3 + (x - offset_x) * 3 + 1] << 8 |
                        buf[y * width * 3 + (x - offset_x) * 3 + 2] << 16;
                }
                usleep(10000);
            }
        }
    }
}
#endif

#if 1
// 实现将图片高度分割成6份，1，3，5从左边向右显示，2，4，6从右向左显示
void displayBMPImage_openScreen2(const char *filename, int *addr)
{
    // 清空目标内存
    memset(addr, 0, 800 * 420 * 4);

    // 打开 BMP 文件
    FILE *fp_bmp = fopen(filename, "rb");
    if (fp_bmp == NULL)
    {
        perror("fopen bmp fail.");
        return;
    }

    // 获取图片宽度和高度
    fseek(fp_bmp, 18, SEEK_SET);
    int width = 0, height = 0;
    if (fread(&width, sizeof(width), 1, fp_bmp) != 1 ||
        fread(&height, sizeof(height), 1, fp_bmp) != 1)
    {
        fprintf(stderr, "Failed to read image width and height.\n");
        fclose(fp_bmp);
        return;
    }

    // 计算图片在屏幕上的偏移量
    int offset_x = (SCREEN_WIDTH - width) / 2;
    int offset_y = (SCREEN_HEIGHT - height) / 2;

    fseek(fp_bmp, 54, SEEK_SET);

    // 读取图片数据
    unsigned char buf[width * height * 3];
    memset(buf, 0, sizeof(buf));
    if (fread(buf, 1, sizeof(buf), fp_bmp) != sizeof(buf))
    {
        fprintf(stderr, "Failed to read image data.\n");
        fclose(fp_bmp);
        return;
    }

    fclose(fp_bmp);

    int top_y = offset_y;                 // 上边界位置
    int bottom_y = offset_y + height - 1; // 下边界位置

    int segment_width = width;       // 切割后每个段的宽度
    int segment_height = height / 6; // 切割后每个段的高度

    for (int i = 0; i < 6; i++)
    {
        int start_y = offset_y + i * segment_height; // 当前段的起始纵坐标
        int end_y = start_y + segment_height - 1;    // 当前段的结束纵坐标

        if (i % 2 == 0)
        {
            // 从左边进入
            for (int x = 0; x < segment_width; x++)
            {
                for (int y = start_y; y <= end_y; y++)
                {
                    *(addr + (bottom_y - y) * SCREEN_WIDTH + (offset_x + x)) =
                        buf[(y - offset_y) * width * 3 + x * 3] |
                        buf[(y - offset_y) * width * 3 + x * 3 + 1] << 8 |
                        buf[(y - offset_y) * width * 3 + x * 3 + 2] << 16;
                }
                usleep(10000);
            }
        }
        else
        {
            // 从右边进入
            for (int x = width - 1; x >= width - segment_width; x--)
            {
                for (int y = end_y; y >= start_y; y--)
                {
                    *(addr + (bottom_y - y) * SCREEN_WIDTH + (offset_x + x)) =
                        buf[(y - offset_y) * width * 3 + x * 3] |
                        buf[(y - offset_y) * width * 3 + x * 3 + 1] << 8 |
                        buf[(y - offset_y) * width * 3 + x * 3 + 2] << 16;
                }
                usleep(10000);
            }
        }
    }
}
#endif

#if 0
void displayBMPImageExpandingInward(const char *filename, int *addr)
{
    // 清空目标内存
    memset(addr, 0, 800 * 420 * 4);

    // 打开 BMP 文件
    FILE *fp_bmp = fopen(filename, "rb");
    if (fp_bmp == NULL)
    {
        perror("fopen bmp fail.");
        return;
    }

    // 获取图片宽度和高度
    fseek(fp_bmp, 18, SEEK_SET);
    int width = 0, height = 0;
    if (fread(&width, sizeof(width), 1, fp_bmp) != 1 ||
        fread(&height, sizeof(height), 1, fp_bmp) != 1)
    {
        fprintf(stderr, "Failed to read image width and height.\n");
        fclose(fp_bmp);
        return;
    }

    // 计算图片在屏幕上的偏移量
    int offset_x = (SCREEN_WIDTH - width) / 2;
    int offset_y = (SCREEN_HEIGHT - height) / 2;

    fseek(fp_bmp, 54, SEEK_SET);

    // 读取图片数据
    unsigned char buf[width * height * 3];
    memset(buf, 0, sizeof(buf));
    if (fread(buf, 1, sizeof(buf), fp_bmp) != sizeof(buf))
    {
        fprintf(stderr, "Failed to read image data.\n");
        fclose(fp_bmp);
        return;
    }

    fclose(fp_bmp);

    int top_y = offset_y;                 // 上边界位置
    int bottom_y = offset_y + height - 1; // 下边界位置

    int segment_width = width;       // 切割后每个段的宽度
    int segment_height = height / 6; // 切割后每个段的高度

    for (int i = 0; i < 6; i++)
    {
        int start_y = offset_y + i * segment_height; // 当前段的起始纵坐标
        int end_y = start_y + segment_height - 1;    // 当前段的结束纵坐标

        if (i % 2 == 0)
        {
            // 从左边进入
            for (int x = 0; x < segment_width; x++)
            {
                for (int y = start_y; y <= end_y; y++)
                {
                    *(addr + (bottom_y - y) * SCREEN_WIDTH + (offset_x + x)) =
                        buf[(y - offset_y) * width * 3 + x * 3] |
                        buf[(y - offset_y) * width * 3 + x * 3 + 1] << 8 |
                        buf[(y - offset_y) * width * 3 + x * 3 + 2] << 16;
                }
                usleep(10000);
            }
        }
        else
        {
            // 从右边进入
            for (int x = width - 1; x >= width - segment_width; x--)
            {
                for (int y = end_y; y >= start_y; y--)
                {
                    *(addr + (bottom_y - y) * SCREEN_WIDTH + (offset_x + x)) =
                        buf[(y - offset_y) * width * 3 + x * 3] |
                        buf[(y - offset_y) * width * 3 + x * 3 + 1] << 8 |
                        buf[(y - offset_y) * width * 3 + x * 3 + 2] << 16;
                }
                usleep(10000);
            }
        }
    }
}
#endif
