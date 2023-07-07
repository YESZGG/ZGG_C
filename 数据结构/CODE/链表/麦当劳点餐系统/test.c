#include "order.h"

// 创建新的食物节点
struct valuemeal *createFood(char name[], int price)
{
    struct valuemeal *food = (struct valuemeal *)malloc(sizeof(struct valuemeal));
    strcpy(food->food_name, name);
    food->price = price;
    food->next = NULL;
    food->prev = NULL;
    return food;
}

// 创建新的小吃节点
struct snack *createSnack(char name[], int price)
{
    struct snack *snack = (struct snack *)malloc(sizeof(struct snack));
    strcpy(snack->snack_name, name);
    snack->price = price;
    snack->next = NULL;
    snack->prev = NULL;
    return snack;
}

// 创建新的饮品节点
struct drink *createDrink(char name[], int price)
{
    struct drink *drink = (struct drink *)malloc(sizeof(struct drink));
    strcpy(drink->drink_name, name);
    drink->price = price;
    drink->next = NULL;
    drink->prev = NULL;
    return drink;
}

// 创建菜单节点
struct menu *createMenu(int num, char name[])
{
    struct menu *menu = (struct menu *)malloc(sizeof(struct menu));
    menu->num = num;
    strcpy(menu->menu_name, name);
    menu->f_valuemeal = NULL;
    menu->f_snack = NULL;
    menu->f_drink = NULL;
    menu->next = NULL;
    menu->prev = NULL;
    return menu;
}

// 添加套餐到菜单
void addValuemealToMenu(struct menu *menu, struct valuemeal *food)
{
    if (menu->f_valuemeal == NULL)
    {
        menu->f_valuemeal = food;
    }
    else
    {
        struct valuemeal *cur = menu->f_valuemeal;
        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = food;
        food->prev = cur;
    }
}

// 添加小吃到菜单
void addSnackToMenu(struct menu *menu, struct snack *snack)
{
    if (menu->f_snack == NULL)
    {
        menu->f_snack = snack;
    }
    else
    {
        struct snack *cur = menu->f_snack;
        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = snack;
        snack->prev = cur;
    }
}

// 添加饮品到菜单
void addDrinkToMenu(struct menu *menu, struct drink *drink)
{
    if (menu->f_drink == NULL)
    {
        menu->f_drink = drink;
    }
    else
    {
        struct drink *cur = menu->f_drink;
        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = drink;
        drink->prev = cur;
    }
}

// 计算套餐总价
int calculateTotalPrice(struct menu *menu, int num)
{
    struct valuemeal *food = menu->f_valuemeal;
    int totalPrice = 0;

    while (food != NULL && num > 0)
    {
        totalPrice += food->price;
        food = food->next;
        num--;
    }

    return totalPrice;
}

// 打印用户点餐菜单界面
void printOrderMenu(struct menu *menu)
{
    printf("请选择您要点的菜品（输入编号，0返回主菜单）：\n");
    if (menu->f_valuemeal != NULL)
    {
        printf("  套餐：\n");
        struct valuemeal *food = menu->f_valuemeal;
        int i = 1;
        while (food != NULL)
        {
            printf("\t%d.%-10s\t\t价格：%d\n", i, food->food_name, food->price);
            food = food->next;
            i++;
        }
    }

    if (menu->f_snack != NULL)
    {
        printf("  小吃：\n");
        struct snack *snack = menu->f_snack;
        int i = 1;
        while (snack != NULL)
        {
            printf("\t%d.%-10s   \t价格：%2d\n", i, snack->snack_name, snack->price);
            snack = snack->next;
            i++;
        }
    }

    if (menu->f_drink != NULL)
    {
        printf("  饮品：\n");
        struct drink *drink = menu->f_drink;
        int i = 1;
        while (drink != NULL)
        {
            printf("\t%d.%-10s   \t价格：%2d\n", i, drink->drink_name, drink->price);
            drink = drink->next;
            i++;
        }
    }
}

// 用户点餐
// 用户点餐
int orderFood(struct menu *menu)
{
    printOrderMenu(menu);

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
            struct valuemeal *food = menu->f_valuemeal;
            int num = choice;
            while (food != NULL && num > 1)
            {
                food = food->next;
                num--;
            }

            if (food == NULL)
            {
                printf("无效的选择，请重新输入。\n");
                return orderFood(menu); // 继续点餐
            }

            printf("已添加：%s\n", food->food_name);
            totalPrice += food->price;
            break;
        }
        case 2: // 小吃
        {
            struct snack *snack = menu->f_snack;
            int num = choice;
            while (snack != NULL && num > 1)
            {
                snack = snack->next;
                num--;
            }

            if (snack == NULL)
            {
                printf("无效的选择，请重新输入。\n");
                return orderFood(menu); // 继续点餐
            }

            printf("已添加：%s\n", snack->snack_name);
            totalPrice += snack->price;
            break;
        }
        case 3: // 饮品
        {
            struct drink *drink = menu->f_drink;
            int num = choice;
            while (drink != NULL && num > 1)
            {
                drink = drink->next;
                num--;
            }

            if (drink == NULL)
            {
                printf("无效的选择，请重新输入。\n");
                return orderFood(menu); // 继续点餐
            }

            printf("已添加：%s\n", drink->drink_name);
            totalPrice += drink->price;
            break;
        }
        default:
            printf("无效的选择，请重新输入。\n");
            return orderFood(menu); // 继续点餐
    }

    int continueOrder = orderFood(menu); // 继续点餐
    if (continueOrder == 0)
    {
        return totalPrice; // 返回总价
    }
    else
    {
        return totalPrice + continueOrder; // 继续点餐并返回总价
    }
}


// 打印用户主菜单界面
void printUserMainMenu()
{
    printf("欢迎使用麦乐送点餐系统\n");
    printf("  1. 超值套餐\n");
    printf("  2. 小吃\n");
    printf("  3. 饮品\n");
    printf("  0. 退出系统\n");
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

    return head;
}

int main()
{
    struct menu *head = createMenuData(); // 创建菜单和食物数据

    int choice;
    do
    {
        printUserMainMenu(); // 打印用户主菜单界面
        printf("请输入您的选择：");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            // 超值套餐
            struct menu *menu = head;
            while (menu != NULL)
            {
                if (menu->num == 1)
                {
                    int totalPrice = orderFood(menu);
                    printf("总价为：%d\n", totalPrice);
                    printf("\n");
                    break;
                }
                menu = menu->next;
            }
            break;
        }
        case 2:
        {
            // 小吃
            struct menu *menu = head;
            while (menu != NULL)
            {
                if (menu->num == 2)
                {
                    int totalPrice = orderFood(menu);
                    printf("总价为：%d\n", totalPrice);
                    printf("\n");
                    break;
                }
                menu = menu->next;
            }
            break;
        }
        case 3:
        {
            // 饮品
            struct menu *menu = head;
            while (menu != NULL)
            {
                if (menu->num == 3)
                {
                    int totalPrice = orderFood(menu);
                    printf("总价为：%d\n", totalPrice);
                    printf("\n");
                    break;
                }
                menu = menu->next;
            }
            break;
        }
        case 0:
            printf("感谢使用麦乐送点餐系统，再见！\n");
            break;
        default:
            printf("无效的选择，请重新输入。\n");
            break;
        }
    } while (choice != 0);

    // 释放内存
    struct menu *cur = head;
    while (cur != NULL)
    {
        struct menu *temp = cur;
        cur = cur->next;

        struct valuemeal *food = temp->f_valuemeal;
        while (food != NULL)
        {
            struct valuemeal *food_temp = food;
            food = food->next;
            free(food_temp);
        }

        struct snack *snack = temp->f_snack;
        while (snack != NULL)
        {
            struct snack *snack_temp = snack;
            snack = snack->next;
            free(snack_temp);
        }

        struct drink *drink = temp->f_drink;
        while (drink != NULL)
        {
            struct drink *drink_temp = drink;
            drink = drink->next;
            free(drink_temp);
        }

        free(temp);
    }
    return 0;
}
