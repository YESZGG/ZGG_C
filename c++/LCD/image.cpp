#include "image.h"
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

// IFM 图片文件管理类的构造函数
IFM::IFM(const char *path)
{
    // 检索path 当前路径下的所有 .bmp 格式的图片文件，并存储到 image_path 中
    char cmd[1024];
    memset(cmd, 0, sizeof(cmd));
    sprintf(cmd, "find %s -name '*.bmp'", path);

    // 创建一个文件指针，并通过管道 popen 返回
    FILE *fp = popen(cmd, "r");
    if (fp == NULL)
    {
        cout << "查找文件失败" << endl;
    }

    char buf[1024];
    while (1)
    {
        memset(buf, 0, sizeof(buf));
        char *ret = fgets(buf, 1024, fp);
        if (ret == NULL)
        {
            cout << "检索完毕" << endl;
            break;
        }

        // 去掉换行符号
        // strstr(buf, "\n")[0] = '\0';
        char *p = strstr(buf, "\n");
        *p = '\0';
        // 存储图片路径名
        strcpy(image_path[count], buf);

        cout << "image_path：" << image_path[count] << "\t" << count << endl;
        // 图片数量增加
        count++;
    }

    pclose(fp);
}

// 根据下标返回图片路径接口
char *IFM::get_index(int n)
{
    if (n < 0 || n >= count)
    {
        cout << "越界访问" << endl;
        return NULL;
    }

    return image_path[n];
}

 // 返回图片总数
int IFM::get_count()
{
    return count;
}
