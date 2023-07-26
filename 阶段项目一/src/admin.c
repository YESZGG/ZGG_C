#include "admin.h"
#include "menu.h"
#include "mp3.h"
#include "font.h"
#include "slideshow.h"

struct admin *init_admin_head()
{
    struct admin *head = (struct admin *)malloc(sizeof(struct admin));
    if (head == NULL)
    {
        perror("Failed to allocate memory for head.");
        return NULL;
    }
    strcpy(head->name, "");
    memset(head->admin_no, 0, sizeof(head->admin_no));
    memset(head->file_path, 0, sizeof(head->file_path));
    memset(head->sex, 0, sizeof(head->sex));
    memset(head->birth, 0, sizeof(head->birth));
    memset(head->live, 0, sizeof(head->live));
    head->next = head;
    head->previous = head;

    return head;
}

struct admin *init_admin_node()
{
    struct admin *node = (struct admin *)malloc(sizeof(struct admin));
    if (node == NULL)
    {
        perror("Failed to allocate memory for node.");
        return NULL;
    }

    memset(node, 0, sizeof(struct admin));
    node->next = NULL;
    node->previous = NULL;

    return node;
}

void insert_admin(struct admin *head, char admin_no[], char name[], char sex[], char birth[], char live[], char file_path[])
{
    struct admin *newNode = init_admin_node();
    if (newNode == NULL)
    {
        perror("Failed to create a new node.");
        return;
    }
    strcpy(newNode->admin_no, admin_no);
    strcpy(newNode->name, name);
    strcpy(newNode->file_path, file_path);
    strcpy(newNode->sex, sex);
    strcpy(newNode->birth, birth);
    strcpy(newNode->live, live);

    newNode->next = head;
    newNode->previous = head->previous;
    head->previous->next = newNode;
    head->previous = newNode;
}

void print_adminlist(struct admin *head)
{
    if (head == NULL || head->next == head)
    {
        printf("List is empty\n");
        return;
    }

    struct admin *current = head->next;
    while (current != head)
    {
        printf("Admin_no: %s Name: %s, Sex: %s, Birth: %s, Live: %s , File Path: %s\n",
               current->admin_no, current->name, current->sex, current->birth, current->live, current->file_path);
        current = current->next;
    }
}

void free_adminlist(struct admin *head)
{
    if (head == NULL)
        return;

    struct admin *current = head->next;
    while (current != head)
    {
        struct admin *temp = current;
        current = current->next;
        free(temp);
    }
    free(head);
}

int read_to_admin(struct admin *head)
{
    DIR *dp = opendir("./admin");
    if (dp == NULL)
    {
        perror("open dir fail");
        return -1;
    }

    chdir("./admin");
    struct dirent *ep = NULL;

    char path[100] = {0};

    while (1)
    {
        ep = readdir(dp);
        if (ep == NULL)
            break;

        if (ep->d_name[0] == '.' || strcmp(ep->d_name, "..") == 0)
            continue;

        if (strstr(ep->d_name, ".txt") != NULL)
        {
            FILE *file = fopen(ep->d_name, "r");
            if (file != NULL)
            {
                char admin_no[10];
                char name[50];
                char sex[10];
                char birth[20];
                char live[100];

                char line[200]; // 假设每行最多200个字符
                fgets(line, sizeof(line), file);
                sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^\n]", admin_no, name, sex, birth, live);
                sprintf(path, "./admin/%s", ep->d_name);
                insert_admin(head, admin_no, name, sex, birth, live, path);

                fclose(file);
            }
        }
    }

    chdir("..");
    closedir(dp);

    return 0;
}

int show_Admin(int *addr, FILE *fp_admin)
{
    if (fp_admin == NULL)
    {
        fprintf(stderr, "File pointer is null.\n");
        return -1;
    }

    // 清空LCD显示
    memset(addr, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);

    fseek(fp_admin, 18, SEEK_SET);
    int width, height;
    if (fread(&width, sizeof(width), 1, fp_admin) != 1 ||
        fread(&height, sizeof(height), 1, fp_admin) != 1)
    {
        fprintf(stderr, "Failed to read image width and height.\n");
        return -1;
    }

    int offset_x = (SCREEN_WIDTH - width) / 2;
    int offset_y = (SCREEN_HEIGHT - height) / 2;

    show_bmp_image(addr, fp_admin, offset_x, offset_y);

    return 0;
}

int admin_Info(Admin *admin_head, Admin **admin_c, int *addr, int startX, int startY, int endX, int endY)
{
    int white = 0x00ffffff;
    int black = 0x00000000;

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
    Clean_Area(155, 0, 300, 80, black);   // 清屏
    Clean_Area(170, 130, 100, 50, black); // 清屏
    Clean_Area(170, 225, 200, 50, black); // 清屏
    Clean_Area(170, 305, 600, 80, black); // 清屏

    Display_characterX(173, 35, (*admin_c)->name, white, 2);
    Display_characterX(173, 135, (*admin_c)->sex, white, 2);
    Display_characterX(173, 235, (*admin_c)->birth, white, 2);
    Display_characterX(173, 335, (*admin_c)->live, white, 2);


    // 检查编号是否为 "1001"，如果是则更换成对应头像
    if (strcmp((*admin_c)->admin_no, "1001") == 0)
    {
        changeAvatar(addr, "zhangsan.bmp");
    }
    // 检查编号是否为 "1002"，如果是则更换成对应头像
    if (strcmp((*admin_c)->admin_no, "1002") == 0)
    {
        changeAvatar(addr, "Angelababy.bmp");
    }
    // 检查编号是否为 "1003", 如果是则更换对应头像
    if (strcmp((*admin_c)->admin_no, "1003") == 0)
    {
        changeAvatar(addr, "kun.bmp");
    }

    int slideDirection = SlideDirection(startX, startY, endX, endY);

    if (slideDirection == LEFT)
    {
        *admin_c = (*admin_c)->next; // 下一个

        // 如果到达头部节点，则移动到头部之后的第一个节点
        if (*admin_c == admin_head)
        {
            *admin_c = admin_head->next;
        }
    }
    else if (slideDirection == RIGHT)
    {
        *admin_c = (*admin_c)->previous; // 上一个

        // 如果到达头部节点，则移动到头部之前的最后一个节点
        if (*admin_c == admin_head)
        {
            *admin_c = admin_head->previous;
        }
    }

    return 0;
}

void display_Avatar(int *addr, char filepath[])
{
    // printf("进入 display_Avatar() 函数\n"); // 调试输出
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL)
    {
        perror("fopen bmp fail.");
        return;
    }

    fseek(fp, 18, SEEK_SET);
    int width = 0, height = 0;
    if (fread(&width, sizeof(width), 1, fp) != 1 ||
        fread(&height, sizeof(height), 1, fp) != 1)
    {
        fprintf(stderr, "Failed to read image width and height.\n");
        return;
    }

    int offset_x = SCREEN_WIDTH - width;
    int offset_y = 0;

    fseek(fp, 54, SEEK_SET);

    unsigned char buf[width * height * 3];
    memset(buf, 0, sizeof(buf));
    if (fread(buf, 1, sizeof(buf), fp) != sizeof(buf))
    {
        fprintf(stderr, "Failed to read image data.\n");
        return;
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            unsigned char b = buf[(y * width + x) * 3];
            unsigned char g = buf[(y * width + x) * 3 + 1];
            unsigned char r = buf[(y * width + x) * 3 + 2];
            *(addr + (offset_y + height - 1 - y) * SCREEN_WIDTH + offset_x + x) = (r << 16) | (g << 8) | b;
        }
    }
    fclose(fp);
}

void changeAvatar(int *addr, char *filename)
{
    DIR *dir;
    struct dirent *entry;

    // 打开 admin 目录
    dir = opendir("./admin");
    if (dir == NULL)
    {
        perror("opendir failed");
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        // 检查文件是否是 BMP 格式
        if (strstr(entry->d_name, ".bmp") != NULL)
        {
            // 检查文件名是否匹配
            if (strcmp(entry->d_name, filename) == 0)
            {
                char filepath[256] = "admin/";
                strcat(filepath, entry->d_name);
                display_Avatar(addr, filepath);
                break; // 停止遍历，找到匹配的头像文件即可
            }
        }
    }

    closedir(dir);
}