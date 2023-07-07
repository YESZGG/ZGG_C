#ifndef __ORDER_H__
#define __ORDER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct valuemeal {
    char food_name[50];     // 食物名字
    int price;              // 价格
    struct valuemeal *prev; // 前驱指针    
    struct valuemeal *next; // 后驱指针
};

struct snack {
    char snack_name[50]; // 小吃名字
    int price;           // 价格
    struct snack *prev;  // 前驱指针
    struct snack *next;  // 后驱指针
};

struct drink {
    char drink_name[50];// 饮品名字
    int price;          // 饮品价格
    struct drink *prev; // 前驱指针
    struct drink *next; // 后驱指针
};

struct menu {
    int num;            // 序号
    char menu_name[50]; // 菜单名字

    struct valuemeal *f_valuemeal; // 指向套餐链表头结点
    struct snack *f_snack;         // 指向小吃链表头结点
    struct drink *f_drink;         // 指向饮品链表头结点

    struct menu *next; // 后继指针
    struct menu *prev; // 前驱指针
};

extern struct menu *createMenu(int num, char name[]);
extern struct valuemeal *createFood(char name[], int price);
extern struct snack *createSnack(char name[], int price);
extern struct drink *createDrink(char name[], int price);
extern void printOrderMenu(struct menu *menu);
extern int orderFood(struct menu *menu);
extern int calculateTotalPrice(struct menu *menu, int num);


#endif