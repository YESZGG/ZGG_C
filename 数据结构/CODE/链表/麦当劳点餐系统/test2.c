#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct valuemeal
{
    char food_name[50];
    int price;
    struct valuemeal *prev;
    struct valuemeal *next;
};

struct snack
{
    char snack_name[50];
    int price;
    struct snack *prev;
    struct snack *next;
};

struct drink
{
    char drink_name[50];
    int price;
    struct drink *prev;
    struct drink *next;
};

struct menu
{
    int num;
    char menu_name[50];

    struct valuemeal *f_valuemeal;
    struct snack *f_snack;
    struct drink *f_drink;

    struct menu *next;
    struct menu *prev;
};

// 创建新的食物节点
struct valuemeal *createFood(char name[], int price)
{
    struct valuemeal *food = (struct valuemeal *)malloc(sizeof(struct valuemeal));

    strcpy(food->food_name, name);
    food->price = price;

    food->next = food->prev = food;

    return food;
}

// 创建新的小吃节点
struct snack *createSnack(char name[], int price)
{
    struct snack *snack = (struct snack *)malloc(sizeof(struct snack));
    strcpy(snack->snack_name, name);
    snack->price = price;
    snack->next = snack->prev = snack;
    return snack;
}

// 创建新的饮品节点
struct drink *createDrink(char name[], int price)
{
    struct drink *drink = (struct drink *)malloc(sizeof(struct drink));
    strcpy(drink->drink_name, name);
    drink->price = price;
    drink->next = drink->prev = drink;
    return drink;
}

// 创建菜单节点
struct menu *createMenu(int num, char name[])
{
    struct menu *menu = (struct menu *)malloc(sizeof(struct menu));
    menu->num = num;
    strcpy(menu->menu_name, name);
    menu->f_valuemeal = createFood("", 0);
    menu->f_snack = createSnack("", 0);
    menu->f_drink = createDrink("", 0);
    menu->next = menu->prev = menu;
    return menu;
}

// 添加套餐到菜单
void addValuemealToMenu(struct menu *menu, struct valuemeal *food)
{
    struct valuemeal *last = menu->f_valuemeal->prev;
    last->next = food;
    food->prev = last;
    food->next = menu->f_valuemeal;
    menu->f_valuemeal->prev = food;
}

// 添加小吃到菜单
void addSnackToMenu(struct menu *menu, struct snack *snack)
{
    struct snack *last = menu->f_snack->prev;
    last->next = snack;
    snack->prev = last;
    snack->next = menu->f_snack;
    menu->f_snack->prev = snack;
}

// 添加饮品到菜单
void addDrinkToMenu(struct menu *menu, struct drink *drink)
{
    struct drink *last = menu->f_drink->prev;
    last->next = drink;
    drink->prev = last;
    drink->next = menu->f_drink;
    menu->f_drink->prev = drink;
}

// 释放套餐内存
void freeValuemeal(struct menu *menu)
{
    struct valuemeal *current = menu->f_valuemeal->next;
    while (current != menu->f_valuemeal)
    {
        struct valuemeal *temp = current;
        current = current->next;

        free(temp);
    }
    free(menu->f_valuemeal);
}

// 释放小吃内存
void freeSnack(struct menu *menu)
{
    struct snack *current = menu->f_snack->next;
    while (current != menu->f_snack)
    {
        struct snack *temp = current;
        current = current->next;

        free(temp);
    }
    free(menu->f_snack);
}

// 释放饮品内存
void freeDrink(struct menu *menu)
{
    struct drink *current = menu->f_drink->next;
    while (current != menu->f_drink)
    {
        struct drink *temp = current;
        current = current->next;

        free(temp);
    }
    free(menu->f_drink);
}

// 释放菜单链表内存
void freeMenu(struct menu *head)
{
    struct menu *current = head;
    while (current != head)
    {
        struct menu *temp = current;
        current = current->next;

        freeValuemeal(temp);
        freeSnack(temp);
        freeDrink(temp);

        temp->f_valuemeal = NULL;
        temp->f_snack = NULL;
        temp->f_drink = NULL;
        
        free(temp);
    }
}

// 创建菜单和食物数据
struct menu *createMenuData()
{
    struct menu *menu1 = createMenu(1, "超值套餐");
    struct valuemeal *food1 = createFood("经典麦辣鸡腿汉堡套餐", 23);
    struct valuemeal *food2 = createFood("原味板烧鸡腿汉堡套餐", 27);
    struct valuemeal *food3 = createFood("巨无霸汉堡套餐", 28);
    addValuemealToMenu(menu1, food1);
    addValuemealToMenu(menu1, food2);
    addValuemealToMenu(menu1, food3);

    struct menu *menu2 = createMenu(2, "小吃");
    struct snack *snack1 = createSnack("麦乐鸡", 10);
    struct snack *snack2 = createSnack("薯条", 8);
    struct snack *snack3 = createSnack("麦辣鸡翅", 2);

    addSnackToMenu(menu2, snack1);
    addSnackToMenu(menu2, snack2);
    addSnackToMenu(menu2, snack3);

    struct menu *menu3 = createMenu(3, "饮品");
    struct drink *drink1 = createDrink("冰镇可乐", 5);
    struct drink *drink2 = createDrink("雪碧", 5);
    struct drink *drink3 = createDrink("优品豆浆", 10);

    addDrinkToMenu(menu3, drink1);
    addDrinkToMenu(menu3, drink2);
    addDrinkToMenu(menu3, drink3);

    struct menu *head = menu1;
    menu1->next = menu2;
    menu2->prev = menu1;
    menu2->next = menu3;
    menu3->prev = menu2;

    return head;
}

// 打印用户主菜单界面
void printUserMainMenu()
{
    printf("\t------欢迎使用麦乐送点餐系统------\n");
    printf("\t\t  1. 超值套餐\n");
    printf("\t\t  2. 小吃   \n");
    printf("\t\t  3. 饮品   \n");
    printf("\t\t  0. 退出系统\n");
}

int main()
{
    struct menu *menuData = createMenuData();
    printUserMainMenu();
    freeMenu(menuData);
    return 0;
}
