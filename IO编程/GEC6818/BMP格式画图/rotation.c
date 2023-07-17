#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

// 打开LCD
int open_lcd() {
    int fd_lcd = open("/dev/fb0", O_RDWR);
    if (fd_lcd < 0) {
        perror("open lcd fail");
        return -1;
    }
    return fd_lcd;
}

// LCD的映射
int* mmap_lcd(int fd_lcd) {
    int* addr = mmap(
        NULL,
        800 * 480 * 4,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fd_lcd,
        0
    );
    if (addr == NULL) {
        perror("mmap fail");
        return NULL;
    }
    return addr;
}

// 关闭LCD的映射
void unmap_lcd(int* addr) {
    munmap(addr, 800 * 480 * 4);
}

// 关闭LCD
void close_lcd(int fd_lcd) {
    close(fd_lcd);
}

// 读取BMP图片的宽度和高度
int read_bmp_size(int fd_bmp, int* width, int* height) {
    lseek(fd_bmp, 18, SEEK_SET);
    read(fd_bmp, width, 4);
    read(fd_bmp, height, 4);
    printf("bmp width:%d height:%d\n", *width, *height);
    return 0;
}

// 读取BMP图片信息
int read_bmp_data(int fd_bmp, int width, int height, char* buf) {
    lseek(fd_bmp, 54, SEEK_SET);
    memset(buf, 0, width * height * 3);
    read(fd_bmp, buf, width * height * 3);
    return 0;
}

// 在LCD上显示BMP图片
void show_bmp_on_lcd(int* addr, int offset_x, int offset_y, int width, int height, char* buf) {
    int x, y;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            *(addr + (offset_y + height - 1 - y) * 800 + offset_x + x) = buf[(y * width + x) * 3] |
                                                                          buf[(y * width + x) * 3 + 1] << 8 |
                                                                          buf[(y * width + x) * 3 + 2] << 16;
        }
    }
}

int main(int argc, char *argv[]) {
    // 打开LCD
    int fd_lcd = open_lcd();
    if (fd_lcd < 0) {
        return -1;
    }

    // LCD的映射
    int* addr = mmap_lcd(fd_lcd);
    if (addr == NULL) {
        close_lcd(fd_lcd);
        return -1;
    }

    // 将BMP文件名保存在数组中
    char* bmp_files[] = {"1.bmp", "2.bmp", "3.bmp", "4.bmp", "5.bmp"};
    int bmp_size = sizeof(bmp_files) / sizeof(bmp_files[0]);

    while (1) {
        for (int i = 0; i < bmp_size; i++) {
            // 打开BMP图片文件
            int fd_bmp = open(bmp_files[i], O_RDWR);
            if (fd_bmp < 0) {
                perror("open bmp fail.");
                unmap_lcd(addr);
                close_lcd(fd_lcd);
                return -1;
            }

            // 读取BMP图片的宽度和高度
            int width, height;
            if (read_bmp_size(fd_bmp, &width, &height) != 0) {
                close(fd_bmp);
                unmap_lcd(addr);
                close_lcd(fd_lcd);
                return -1;
            }

            // 读取BMP图片信息
            char buf[width * height * 3];
            
            if (read_bmp_data(fd_bmp, width, height, buf) != 0) {
                close(fd_bmp);
                unmap_lcd(addr);
                close_lcd(fd_lcd);
                return -1;
            }

            // 计算图片在LCD上的起始坐标，使之居中显示
            int offset_x = (800 - width) / 2;
            int offset_y = (480 - height) / 2;

            // 在LCD上显示BMP图片
            show_bmp_on_lcd(addr, offset_x, offset_y, width, height, buf);

            // 关闭当前BMP文件
            close(fd_bmp);

            // 延时一定时间后清空屏幕
            sleep(4);
            memset(addr, 0, 800 * 480 * 4);
        }
    }

    // 关闭LCD的映射
    unmap_lcd(addr);

    // 关闭LCD
    close_lcd(fd_lcd);

    return 0;
}
