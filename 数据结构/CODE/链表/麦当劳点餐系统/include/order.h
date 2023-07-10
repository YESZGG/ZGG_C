#ifndef __ORDER_H__
#define __ORDER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct valuemeal
{
    char food_name[50];     // 食物名字
    int price;              // 价格
    struct valuemeal *prev; // 前驱指针
    struct valuemeal *next; // 后驱指针
};

struct snack
{
    char snack_name[50]; // 小吃名字
    int price;           // 价格
    struct snack *prev;  // 前驱指针
    struct snack *next;  // 后驱指针
};

struct drink
{
    char drink_name[50]; // 饮品名字
    int price;           // 饮品价格
    struct drink *prev;  // 前驱指针
    struct drink *next;  // 后驱指针
};

struct menu
{
    int num;            // 序号
    char menu_name[50]; // 菜单名字

    struct valuemeal *f_valuemeal; // 指向套餐链表头结点
    struct snack *f_snack;         // 指向小吃链表头结点
    struct drink *f_drink;         // 指向饮品链表头结点

    struct menu *next; // 后继指针
    struct menu *prev; // 前驱指针
};

extern struct menu *createMenu(int num, char name[]);                                      // 创建菜单项函数声明
extern struct valuemeal *createFood(char name[], int price);                               // 创建套餐函数声明
extern struct snack *createSnack(char name[], int price);                                  // 创建小吃函数声明
extern struct drink *createDrink(char name[], int price);                                  // 创建饮品函数声明
extern struct menu *createMenuData();                                                      // 创建菜单链表函数声明
extern void addValuemealToMenu(struct menu *menu, struct valuemeal *food);                 // 将套餐添加到菜单中函数声明
extern void addSnackToMenu(struct menu *menu, struct snack *snack);                        // 将小吃添加到菜单中函数声明
extern void addDrinkToMenu(struct menu *menu, struct drink *drink);                        // 将饮品添加到菜单中函数声明
extern void printUserMainMenu();                                                           // 打印用户主菜单函数声明
extern int calculateTotalPrice(struct menu *menu, int num);                                // 计算总价格函数声明
extern void printOrderMenu(struct menu *menu, int userChoice);                             // 打印订单菜单函数声明
extern int orderFood(struct menu *menu,int userChoice);                                   // 点餐函数声明
extern void freeValuemeal(struct menu *menu);                                              // 释放套餐内存函数声明
extern void freeSnack(struct menu *menu);                                                  // 释放小吃内存函数声明
extern void freeDrink(struct menu *menu);                                                  // 释放饮品内存函数声明
extern void freeMenu(struct menu *menu);                                                   // 释放菜单链表内存函数声明
#endif