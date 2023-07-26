#include "menu.h"
#include "linkedlist.h"
#include "led_control.h"
#include "slideshow.h"
#include "mp3.h"
#include "autoplay.h"
#include "open_file.h"
#include "admin.h"
#include "font.h"

// 开机动画显示
void show_start(int *addr)
{
    FILE *fp_start1 = fopen("start1.bmp", "r+");
    if (fp_start1 == NULL)
    {
        perror("fopen bmp fail.");
        return;
    }
    FILE *fp_start2 = fopen("start2.bmp", "r+");
    if (fp_start2 == NULL)
    {
        perror("fopen bmp fail.");
        return;
    }
    FILE *fp_start3 = fopen("start3.bmp", "r+");
    if (fp_start3 == NULL)
    {
        perror("fopen bmp fail.");
        return;
    }

    // 清空LCD显示
    memset(addr, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);

    fseek(fp_start1, 18, SEEK_SET);
    int width, height;
    if (fread(&width, sizeof(width), 1, fp_start1) != 1 ||
        fread(&height, sizeof(height), 1, fp_start1) != 1)
    {
        fprintf(stderr, "Failed to read image width and height.\n");
        return;
    }

    int offset_x = (SCREEN_WIDTH - width) / 2;
    int offset_y = (SCREEN_HEIGHT - height) / 2;

    show_bmp_image(addr, fp_start1, offset_x, offset_y);
    fclose(fp_start1);
    sleep(1);
    show_bmp_image(addr, fp_start2, offset_x, offset_y);
    fclose(fp_start2);
    sleep(1);
    show_bmp_image(addr, fp_start3, offset_x, offset_y);
    fclose(fp_start3);
    sleep(1);
}

int main(int argc, char *argv[])
{
    struct Node *head = init_head();
    if (head == (Node *)-1)
    {
        perror("init head fail.");
        return -1;
    }
    read_path_list(head);
    // 测试是否插入成功
    // printLink(head);

    // 创建管理员列表
    struct admin *admin_head = init_admin_head();
    if (admin_head == NULL)
    {
        printf("Failed to initialize the admin list.\n");
        return -1;
    }

    // 从txt文件中读取信息到管理员列表
    if (read_to_admin(admin_head) != 0)
    {
        printf("Failed to read data from txt files.\n");
        free_adminlist(admin_head);
        return -1;
    }
    // 打印管理员链表信息
    // print_adminlist(admin_head);

    // 字库初始化
    Init_Font();

    // 打开LCD文件
    int fd_lcd = fd_lcd_open();
    if (fd_lcd == -1)
    {
        perror("open lcd fail");
        return -1;
    }

    // 打开EVENT0事件文件
    int fd_ts = open(INPUT_PATH, O_RDONLY);
    if (fd_ts == -1)
    {
        perror("open event0 fail");
        close(fd_lcd);
        return -1;
    }

    // 打开待显示图片文件 --- 主菜单界面
    FILE *fp_menu = fopen("desktop.bmp", "r+");
    if (fp_menu == NULL)
    {
        perror("fopen bmp fail.");
        close(fd_lcd);
        close(fd_ts);
        return -1;
    }

    // 映射LCD内存
    int *addr = mmap(NULL, BUFFER_SIZE * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd_lcd, 0);
    if (addr == MAP_FAILED)
    {
        perror("mmap fail");
        fclose(fp_menu);
        close(fd_lcd);
        close(fd_ts);
        return -1;
    }

    // 显示开机动画
    show_start(addr);

    // 显示主菜单界面
    if (show_return_menu(addr, fp_menu) != 0)
    {
        fclose(fp_menu);
        munmap(addr, BUFFER_SIZE * 4);
        close(fd_lcd);
        close(fd_ts);
        return -1;
    }

    // 关闭图片文件
    fclose(fp_menu);

    // 定义一个存储触摸屏信息的结构体
    struct input_event ts;
    memset(&ts, 0, sizeof(struct input_event));

    int touchX, touchY;
    int startX, startY;
    int endX, endY;
    struct Node *current = head;
    struct admin *admin_c = admin_head;
    // 读取触摸屏信息
    while (1)
    {
        read(fd_ts, &ts, sizeof(struct input_event));

        // 处理触摸事件
        if (ts.type == EV_ABS && ts.code == ABS_X)
        {
            touchX = ts.value * SCREEN_WIDTH / 1024;
        }
        else if (ts.type == EV_ABS && ts.code == ABS_Y)
        {
            touchY = ts.value * SCREEN_HEIGHT / 600;
        }
        else if (ts.type == EV_KEY && ts.code == BTN_TOUCH)
        {
            if (ts.value == 1)
            {
                // 触摸开始时的处理
                startX = touchX;
                startY = touchY;
            }
            else if (ts.value == 0)
            {
                // 触摸结束时的处理
                endX = touchX;
                endY = touchY;

                // 处理不同的屏幕状态
                switch (currentScreen)
                {
                case MainMenu:
                    // MainMenu屏幕下的逻辑处理
                    handleMainMenuTouch(addr, fp_menu, startX, startY, endX, endY);
                    break;
                case MP3Screen:
                    // MP3Screen屏幕下的逻辑处理
                    handleMP3ScreenTouch(addr, startX, startY, endX, endY);
                    break;
                case SlideshowScreen:
                    // 手动图片放映功能
                    playSlideshow(head, &current, addr, startX, startY, endX, endY);
                    break;
                case AutoplayScreen:
                    // 自动播放图片功能
                    playAutoshow(head, &current, addr, startX, startY, endX, endY);
                    break;
                case AdminScreen:
                    // 管理员界面功能
                    admin_Info(admin_head, &admin_c, addr, startX, startY, endX, endY);
                    break;
                default:
                    break;
                }
            }
        }
    }

    // 解除映射关系
    munmap(addr, BUFFER_SIZE * 4);

    UnInit_Font(); // 关闭字库
    // 释放存储管理员的双向循环链表
    free_adminlist(admin_head);
    // 释放存储图片的双向循环链表
    freeLinkedList(head);

    // 关闭文件描述符
    close(fd_lcd);
    close(fd_ts);

    return 0;
}
