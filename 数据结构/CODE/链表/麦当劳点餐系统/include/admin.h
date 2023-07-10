#ifndef __Administrator_H__ // 条件编译指令：如果 __Administrator_H__ 宏未定义，则编译以下内容
#define __Administrator_H__ // 定义 __Administrator_H__ 宏，防止重复包含头文件

#include "order.h" // 包含 order.h 头文件

extern void printMainMenu();                           // 声明 printMainMenu 函数
extern void printAdminMenu();                          // 声明 printAdminMenu 函数
extern void printAddMenu();                            // 声明 printAddMenu 函数
extern void printDeleteMenu();                         // 声明 printDeleteMenu 函数
extern void printModifyMenu();                         // 声明 printModifyMenu 函数
extern void addValuemeal(struct menu *menu);           // 声明 addValuemeal 函数，参数为指向 menu 结构体的指针
extern void addSnack(struct menu *menu);               // 声明 addSnack 函数，参数为指向 menu 结构体的指针
extern void addDrink(struct menu *menu);               // 声明 addDrink 函数，参数为指向 menu 结构体的指针
extern void deleteValuemeal(struct menu *menu);        // 声明 deleteValuemeal 函数，参数为指向 menu 结构体的指针
extern void deleteSnack(struct menu *menu);            // 声明 deleteSnack 函数，参数为指向 menu 结构体的指针
extern void deleteDrink(struct menu *menu);            // 声明 deleteDrink 函数，参数为指向 menu 结构体的指针
extern void modifyValuemeal(struct menu *currentMenu); // 声明 modifyValuemeal 函数，参数为指向 menu 结构体的指针
extern void modifySnack(struct menu *menu);            // 声明 modifySnack 函数，参数为指向 menu 结构体的指针
extern void modifyDrink(struct menu *menu);            // 声明 modifyDrink 函数，参数为指向 menu 结构体的指针
extern void displayMenu(struct menu *menu);            // 声明 displayMenu 函数，参数为指向 menu 结构体的指针

#endif // 结束条件编译指令
