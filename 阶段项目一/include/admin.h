#ifndef ADMIN_H_
#define ADMIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

typedef struct admin
{
    char admin_no[10];       // 管理员编号
    char name[50];      // 管理员姓名
    char sex[10];       // 管理员性别
    char birth[20];     // 管理员出生日期
    char live[100];     // 管理员的住址
    char file_path[50]; // 管理员存储信息的路径
    struct admin *next;
    struct admin *previous;
} Admin;
extern struct admin *init_admin_head();
extern struct admin *init_admin_node();
extern void insert_admin(struct admin *head, char admin_no[], char name[], char sex[], char birth[], char live[], char file_path[]);
extern void print_adminlist(struct admin *head);
extern void free_adminlist(struct admin *head);
extern int read_to_admin(struct admin *head);
extern int show_Admin(int *addr, FILE *fp_admin);
extern int admin_Info(Admin *admin_head, Admin **admin_c, int *addr, int startX, int startY, int endX, int endY);
extern void display_Avatar(int *addr, char filepath[]);
extern void changeAvatar(int *addr, char *filename);
#endif