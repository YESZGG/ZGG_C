#include "order.h"

// 创建新的套餐节点
struct valuemeal *createFood(char name[], int price)
{
    // 分配内存空间以存储 struct valuemeal 结构体
    struct valuemeal *food = (struct valuemeal *)malloc(sizeof(struct valuemeal));
    // 将传入的 name 复制到 food->food_name
    strcpy(food->food_name, name);
    // 设置 food 的价格为传入的 price
    food->price = price;
    // 将 food 的 next 和 prev 指针都指向自身，创建一个双向循环链表
    food->next = food->prev = food;
    // 返回创建的 food 指针
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
    menu->f_valuemeal = createFood("", 0); // 初始化头结点
    menu->f_snack = createSnack("", 0);
    menu->f_drink = createDrink("", 0);
    menu->next = menu->prev = NULL; // 双向循环链表的头尾指针都指向自身
    return menu;
}

// 添加套餐到菜单
void addValuemealToMenu(struct menu *menu, struct valuemeal *food)
{
    // 获取当前菜单中最后一个节点
    struct valuemeal *last = menu->f_valuemeal->prev;
    // 将最后一个节点的 next 指针指向要添加的 food
    last->next = food;
    // 将 food 的 prev 指针指向最后一个节点
    food->prev = last;
    // 将 food 的 next 指针指向菜单的第一个节点（即原来的头节点）
    food->next = menu->f_valuemeal;
    // 将菜单的头节点的 prev 指针指向 food
    menu->f_valuemeal->prev = food;
}

// 添加小吃到菜单
void addSnackToMenu(struct menu *menu, struct snack *snack)
{
    struct snack *last = menu->f_snack->prev; // 获取最后一个节点
    last->next = snack;
    snack->prev = last;
    snack->next = menu->f_snack;
    menu->f_snack->prev = snack;
}

// 添加饮品到菜单
void addDrinkToMenu(struct menu *menu, struct drink *drink)
{
    struct drink *last = menu->f_drink->prev; // 获取最后一个节点
    last->next = drink;
    drink->prev = last;
    drink->next = menu->f_drink;
    menu->f_drink->prev = drink;
}

// 创建菜单和食物数据
struct menu *createMenuData()
{
    // 超值套餐菜单
    struct menu *menu1 = createMenu(1, "超值套餐");
    struct valuemeal *food1 = createFood("经典麦辣鸡腿汉堡套餐", 23);
    struct valuemeal *food2 = createFood("原味板烧鸡腿汉堡套餐", 27);
    struct valuemeal *food3 = createFood("巨无霸汉堡套餐", 28);
    addValuemealToMenu(menu1, food1);
    addValuemealToMenu(menu1, food2);
    addValuemealToMenu(menu1, food3);

    // 小吃菜单
    struct menu *menu2 = createMenu(2, "小吃");
    struct snack *snack1 = createSnack("麦乐鸡", 10);
    struct snack *snack2 = createSnack("薯条", 8);
    struct snack *snack3 = createSnack("麦辣鸡翅", 2);

    addSnackToMenu(menu2, snack1);
    addSnackToMenu(menu2, snack2);
    addSnackToMenu(menu2, snack3);

    // 饮品菜单
    struct menu *menu3 = createMenu(3, "饮品");
    struct drink *drink1 = createDrink("冰镇可乐", 5);
    struct drink *drink2 = createDrink("雪碧", 5);
    struct drink *drink3 = createDrink("优品豆浆", 10);

    addDrinkToMenu(menu3, drink1);
    addDrinkToMenu(menu3, drink2);
    addDrinkToMenu(menu3, drink3);

    // 创建菜单链表
    struct menu *head = menu1;
    menu1->next = menu2;
    menu2->prev = menu1;
    menu2->next = menu3;
    menu3->prev = menu2;
    menu3->next = menu1;

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

// 计算套餐+小吃+饮料总价
int calculateTotalPrice(struct menu *menu, int num)
{
    struct valuemeal *food = menu->f_valuemeal->next; // 第一个节点
    struct snack *snack = menu->f_snack->next;
    struct drink *drink = menu->f_drink->next;
    int totalPrice = 0;

    while ((food != menu->f_valuemeal || snack != menu->f_snack || drink != menu->f_drink) && num > 0)
    {
        if (food != menu->f_valuemeal)
        {
            totalPrice += food->price;
            food = food->next;
        }
        else if (snack != menu->f_snack)
        {
            totalPrice += snack->price;
            snack = snack->next;
        }
        else if (drink != menu->f_drink)
        {
            totalPrice += drink->price;
            drink = drink->next;
        }

        num--;
    }

    return totalPrice;
}

// 打印用户点餐菜单界面
void printOrderMenu(struct menu *menu, int userChoice)
{
    printf("请选择您要点的菜品（输入编号，0返回主菜单）：\n");

    switch (userChoice)
    {
    case 1:
        if (menu->f_valuemeal->next != menu->f_valuemeal)
        {
            printf("  套餐：\n");
            struct valuemeal *food = menu->f_valuemeal->next; // 第一个节点
            int i = 1;
            while (food != menu->f_valuemeal)
            {
                printf("\t%d.%-10s\t    \t价格：%d\n", i, food->food_name, food->price);
                food = food->next;
                i++;
            }
        }
        break;

    case 2:
        if (menu->f_snack->next != menu->f_snack)
        {
            printf("  小吃：\n");
            struct snack *snack = menu->f_snack->next;
            int i = 1;
            while (snack != menu->f_snack)
            {
                printf("\t%d.%-10s   \t价格：%2d\n", i, snack->snack_name, snack->price);
                snack = snack->next;
                i++;
            }
        }
        break;

    case 3:
        if (menu->f_drink->next != menu->f_drink)
        {
            printf("  饮品：\n");
            struct drink *drink = menu->f_drink->next;
            int i = 1;
            while (drink != menu->f_drink)
            {
                printf("\t%d.%-10s   \t价格：%2d\n", i, drink->drink_name, drink->price);
                drink = drink->next;
                i++;
            }
        }
        break;

    default:
        // Invalid choice, do nothing
        break;
    }
}

// 用户点餐
int orderFood(struct menu *menu,int userChoice)
{
    // printOrderMenu(menu);
    printOrderMenu(menu, userChoice);
    int choice;
    printf("请选择您要点的菜品（输入编号，0返回主菜单）：");
    scanf("%d", &choice);

    if (choice == 0)
    {
        return 0; // 返回主菜单
    }

    int totalPrice = 0;

    switch (menu->num)
    {
    case 1: // 超值套餐
    {
        struct valuemeal *food = menu->f_valuemeal->next; // 第一个节点
        int num = choice;
        while (food != menu->f_valuemeal && num > 1)
        {
            food = food->next;
            num--;
        }

        if (food == menu->f_valuemeal)
        {
            printf("无效的选择，请重新输入。\n");
            return orderFood(menu,userChoice); // 继续点餐
        }

        printf("已添加：%s\n", food->food_name);
        totalPrice += food->price;
        break;
    }
    case 2: // 小吃
    {
        struct snack *snack = menu->f_snack->next; // 第一个节点
        int num = choice;
        while (snack != menu->f_snack && num > 1)
        {
            snack = snack->next;
            num--;
        }

        if (snack == menu->f_snack)
        {
            printf("无效的选择，请重新输入。\n");
            return orderFood(menu,userChoice); // 继续点餐
        }

        printf("已添加：%s\n", snack->snack_name);
        totalPrice += snack->price;
        break;
    }
    case 3: // 饮品
    {
        struct drink *drink = menu->f_drink->next; // 第一个节点
        int num = choice;
        while (drink != menu->f_drink && num > 1)
        {
            drink = drink->next;
            num--;
        }

        if (drink == menu->f_drink)
        {
            printf("无效的选择，请重新输入。\n");
            return orderFood(menu,userChoice); // 继续点餐
        }

        printf("已添加：%s\n", drink->drink_name);
        totalPrice += drink->price;
        break;
    }
    default:
        printf("无效的选择，请重新输入。\n");
        return orderFood(menu,userChoice); // 继续点餐
    }

    int continueOrder = orderFood(menu,userChoice); // 继续点餐
    if (continueOrder == 0)
    {
        return totalPrice; // 返回总价
    }
    else
    {
        return totalPrice + continueOrder; // 继续点餐并返回总价
    }
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