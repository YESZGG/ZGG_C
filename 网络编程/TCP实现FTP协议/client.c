#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_IP_LENGTH 16 // 最大IP地址长度（包括终止符）
#define BUFFER_SIZE 1024

// 获取时间函数
const char *get_formatted_time(int type);
// 进度条显示
// void print_progress(double percentage);

// 结构体用于传递参数给线程
struct ThreadArgs
{
    int sockfd;
    char *path_name;
};

// 线程函数，用于发送文件内容
void *sendFileContent(void *args)
{
    struct ThreadArgs *threadArgs = (struct ThreadArgs *)args;
    int sockfd = threadArgs->sockfd;
    char *path_name = threadArgs->path_name;

    FILE *file = fopen(path_name, "r");
    if (file == NULL)
    {
        perror("文件打开失败");
        exit(1);
    }
    // 获取文件大小
    fseek(file, 0, SEEK_SET);
    long filesize = ftell(file);
    if (filesize == -1)
    {
        printf("[%s] 获取源文件大小失败.\n", get_formatted_time(2));
        fclose(file);
        return NULL;
    }
    // 重置文件光标位置
    fseek(file, 0, SEEK_SET);

    printf("[%s] 文件打开成功，文件正在传输...\n", get_formatted_time(2));
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    ssize_t totalBytes = 0;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0)
    {
        // 发送数据块给服务器
        ssize_t bytesSent = send(sockfd, buffer, bytesRead, 0);
        if (bytesSent == -1)
        {
            perror("发送数据块出错");
            exit(1);
        }
        // totalBytes += bytesSent;
        // double progress = (double)totalBytes / filesize;
        // print_progress(progress);
        printf("[%s] 已发送数据块大小: %zd 字节\n", get_formatted_time(2), bytesSent);
        totalBytes += bytesSent;
    }
    // printf("\n");
    fclose(file);
    printf("[%s] 文件传输完成\n", get_formatted_time(2));

    return NULL;
}

int main()
{
    // 创建TCP socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("创建socket失败");
        exit(1);
    }

    // 输入服务器的IP地址
    char server_ip[MAX_IP_LENGTH];
    printf("Enter the server IP address: ");
    scanf("%s", server_ip);

    // 输入服务器的端口号
    unsigned short server_port;
    printf("Enter the server port: ");
    scanf("%hu", &server_port);

    // 防止端口复用
    int optval = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址和端口
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0)
    {
        perror("无效的IP地址");
        exit(1);
    }

    // 连接到服务器
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("连接到服务器失败");
        exit(1);
    }

    int choice;
    printf("请选择显示的目录：\n");
    printf("1. 当前目录\n");
    printf("2. 上一级目录\n");
    printf("请输入选项：");
    scanf("%d", &choice);

    DIR *dir;
    struct dirent *entry;
    if (choice == 1)
    {
        dir = opendir(".");
        if (dir == NULL)
        {
            perror("打开目录失败");
            exit(1);
        }

        printf("当前目录的文件列表：\n");
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_type == DT_REG) // 只处理普通文件
            {
                printf("- %s\n", entry->d_name);
            }
        }

        closedir(dir);
    }
    else if (choice == 2)
    {
        char parent_dir[2] = "..";
        dir = opendir(parent_dir);
        if (dir == NULL)
        {
            perror("打开上一级目录失败");
            exit(1);
        }

        printf("上一级目录的文件列表：\n");
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_type == DT_REG) // 只处理普通文件
            {
                printf("- %s\n", entry->d_name);
            }
        }

        closedir(dir);
    }
    else
    {
        printf("无效的选项！\n");
        exit(1);
    }

    char path_name[BUFFER_SIZE];
    printf("请输入要上传的文件名：");
    scanf("%s", path_name);

    char *file_name = strrchr(path_name, '/');
    if (file_name != NULL)
    {
        file_name++;
        printf("[%s] 发送文件名：%s 至服务器\n", get_formatted_time(2), file_name);
    }

    // 发送文件名给服务器
    if (send(sockfd, path_name, strlen(path_name), 0) == -1)
    {
        perror("发送文件名出错");
        exit(1);
    }
    // 获取文件大小
    fseek(file, 0, SEEK_SET);
    long filesize = ftell(file);
    if (filesize == -1)
    {
        printf("[%s] 获取源文件大小失败.\n", get_formatted_time(2));
        fclose(file);
        return NULL;
    }
    // 重置文件光标位置
    fseek(file, 0, SEEK_SET);

    if (send(sockfd, &filesize, sizeof(long), 0) == -1)
    {
        printf("[%s] 发送文件大小失败.\n", get_formatted_time(2))
    }
    printf("[%s] 发送文件大小:%d 完成.",get_formatted_time(2),filesize);
    
    // 创建一个线程来发送文件内容
    pthread_t sendThread;
    struct ThreadArgs args;
    args.sockfd = sockfd;
    args.path_name = path_name;

    if (pthread_create(&sendThread, NULL, sendFileContent, (void *)&args) != 0)
    {
        perror("创建发送线程失败");
        exit(1);
    }

    // 等待发送线程结束
    pthread_join(sendThread, NULL);

    // 关闭socket
    close(sockfd);

    return 0;
}

// 获取时间，传入type来获取各种时间
const char *get_formatted_time(int type)
{
    time_t current_time;
    struct tm *time_info;

    time(&current_time);
    time_info = localtime(&current_time);

    static char formatted_time[20] = {};

    if (type == 0)
    {
        snprintf(formatted_time, sizeof(formatted_time), " ");
    }
    else if (type == 1)
    {
        snprintf(formatted_time, sizeof(formatted_time), "%04d-%02d-%02d",
                 (1900 + time_info->tm_year), (1 + time_info->tm_mon), time_info->tm_mday);
        // 年  月  日
    }
    else if (type == 2)
    {
        snprintf(formatted_time, sizeof(formatted_time), "%04d-%02d-%02d %02d:%02d:%02d",
                 (1900 + time_info->tm_year), (1 + time_info->tm_mon), time_info->tm_mday,
                 time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
        // 年  月  日  时  分  秒
    }
    // else if (type == 3)
    // {
    //     snprintf(formatted_time, sizeof(formatted_time), "%04d-%02d-%02d_%02d:%02d:%02d",
    //              (1900 + time_info->tm_year), (1 + time_info->tm_mon), time_info->tm_mday,
    //              time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
    // }
    else
    {
        // Handle invalid type here (e.g., set default value for formatted_time)
    }

    return formatted_time;
}

// void print_progress(double percentage)
// {
//     int bar_width = 50;
//     int filled_width = bar_width * percentage;
//     printf("[");
//     for (int i = 0; i < bar_width; i++)
//     {
//         if (i < filled_width)
//             printf("=");
//         else
//             printf(" ");
//     }
//     printf("] %.2f%%\r", percentage * 100);
//     fflush(stdout);
// }
