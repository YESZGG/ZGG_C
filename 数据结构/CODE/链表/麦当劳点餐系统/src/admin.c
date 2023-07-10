#include "order.h"
#include "admin.h"

// 打印身份主菜单界面
void printMainMenu()
{
    printf("请选择您的身份：\n");
    printf("1. 用户\n");
    printf("2. 管理员\n");
    printf("0. 退出系统\n");
}

// 打印管理员菜单界面
void printAdminMenu()
{
    printf("\n\t------欢迎进入管理员功能界面------\n");
    printf("\t\t  1. 添加\n");
    printf("\t\t  2. 删除\n");
    printf("\t\t  3. 修改\n");
    printf("\t\t  4. 遍历\n");
    printf("\t\t  0. 退出系统\n");
}

// 打印添加功能菜单界面
void printAddMenu()
{
    printf("\n请选择要添加的菜单类别：\n");
    printf("\t1. 超值套餐\n");
    printf("\t2. 小吃\n");
    printf("\t3. 饮品\n");
    printf("\t0. 返回管理员界面\n");
}

// 打印删除功能菜单界面
void printDeleteMenu()
{
    printf("\n请选择要删除的菜单类别：\n");
    printf("\t1. 超值套餐\n");
    printf("\t2. 小吃\n");
    printf("\t3. 饮品\n");
    printf("\t0. 返回管理员界面\n");
}

// 打印修改功能菜单界面
void printModifyMenu()
{
    printf("\n请选择要修改的菜单类别：\n");
    printf("\t1. 超值套餐\n");
    printf("\t2. 小吃\n");
    printf("\t3. 饮品\n");
    printf("\t0. 返回管理员界面\n");
}

// 添加套餐功能
void addValuemeal(struct menu *menu)
{
    struct valuemeal *newValuemeal = (struct valuemeal *)malloc(sizeof(struct valuemeal));

    printf("请输入新套餐的名称：");
    scanf("%s", newValuemeal->food_name);
    printf("请输入新套餐的价格：");
    scanf("%d", &(newValuemeal->price));

    newValuemeal->prev = NULL;
    newValuemeal->next = NULL;

    if (menu->f_valuemeal == NULL)
    {
        newValuemeal->prev = newValuemeal;
        newValuemeal->next = newValuemeal;
        menu->f_valuemeal = newValuemeal;
    }
    else
    {
        // 将新套餐添加到链表末尾
        struct valuemeal *first = menu->f_valuemeal;
        struct valuemeal *last = first->prev;

        newValuemeal->prev = last;
        newValuemeal->next = first;
        first->prev = newValuemeal;
        last->next = newValuemeal;
    }

    printf("添加套餐成功！\n");
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

// 添加小吃功能
void addSnack(struct menu *menu)
{
    struct snack *newSnack = (struct snack *)malloc(sizeof(struct snack));
    if (newSnack == NULL)
    {
        perror("addSnack malloc newSnack failed.\n");
        return;
    }
    newSnack->prev = NULL;
    newSnack->next = NULL;

    printf("请输入新小吃的名称：");
    scanf("%s", newSnack->snack_name);
    printf("请输入新小吃的价格：");
    scanf("%d", &(newSnack->price));

    if (menu->f_snack == NULL)
    {
        newSnack->prev = newSnack;
        newSnack->next = newSnack;
        menu->f_snack->next = newSnack;
    }
    else
    {
        // 将新小吃添加到链表末尾
        struct snack *first = menu->f_snack;
        struct snack *last = first->prev;

        newSnack->prev = last;
        newSnack->next = first;
        first->prev = newSnack;
        last->next = newSnack;
    }

    printf("添加小吃成功！\n");
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

// 添加饮品功能
void addDrink(struct menu *menu)
{
    struct drink *newDrink = (struct drink *)malloc(sizeof(struct drink));

    printf("请输入新饮品的名称：");
    scanf("%s", newDrink->drink_name);
    printf("请输入新饮品的价格：");
    scanf("%d", &(newDrink->price));

    newDrink->prev = NULL;
    newDrink->next = NULL;

    if (menu->f_drink == NULL)
    {
        newDrink->prev = newDrink;
        newDrink->next = newDrink;
        menu->f_drink = newDrink;
    }
    else
    {
        // 将新饮品添加到链表末尾
        struct drink *first = menu->f_drink;
        struct drink *last = first->prev;

        newDrink->prev = last;
        newDrink->next = first;
        first->prev = newDrink;
        last->next = newDrink;
    }

    printf("添加饮品成功！\n");
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

// 删除套餐功能
void deleteValuemeal(struct menu *menu)
{
    if (menu->f_valuemeal == NULL)
    {
        printf("套餐列表为空，无法删除套餐。\n");
        return;
    }

    char foodname[50];
    printf("请输入要删除的套餐名称：");
    scanf("%s", foodname);

    struct valuemeal *curr = menu->f_valuemeal;
    while (1)
    {
        if (strcmp(curr->food_name, foodname) == 0)
        {
            // Found the valuemeal to delete
            if (curr == menu->f_valuemeal)
            {
                menu->f_valuemeal = curr->next;
            }

            if (curr->prev != NULL)
            {
                curr->prev->next = curr->next;
            }
            if (curr->next != NULL)
            {
                curr->next->prev = curr->prev;
            }

            free(curr);
            printf("套餐删除成功！\n");
            return;
        }

        curr = curr->next;
        if (curr == menu->f_valuemeal)
        {
            break;
        }
    }

    printf("找不到该名称的套餐，删除失败。\n");
}

// 删除小吃功能
void deleteSnack(struct menu *menu)
{
    if (menu->f_snack == NULL)
    {
        printf("小吃列表为空，无法删除小吃。\n");
        return;
    }

    char snackname[50];
    printf("请输入要删除的小吃名称：");
    scanf("%s", snackname);

    struct snack *curr = menu->f_snack->next;
    while (curr != menu->f_snack)
    {
        if (strcmp(curr->snack_name, snackname) == 0)
        {
            // Found the snack to delete
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;

            free(curr);
            printf("小吃删除成功！\n");
            return;
        }

        curr = curr->next;
    }

    printf("找不到该名称的小吃，删除失败。\n");
}

// 删除饮品功能
void deleteDrink(struct menu *menu)
{
    if (menu->f_drink == NULL)
    {
        printf("饮品列表为空，无法删除饮品。\n");
        return;
    }

    char drinkname[50];
    printf("请输入要删除的饮品名称：");
    scanf("%s", drinkname);

    struct drink *curr = menu->f_drink->next;
    while (curr != menu->f_drink)
    {
        if (strcmp(curr->drink_name, drinkname) == 0)
        {
            // Found the drink to delete
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;

            free(curr);
            printf("饮品删除成功！\n");
            return;
        }

        curr = curr->next;
    }

    printf("找不到该名称的饮品，删除失败。\n");
}

// 修改套餐功能
void modifyValuemeal(struct menu *menu)
{
    char foodName[50];
    bool found = false;

    printf("请输入要修改的套餐名称：");
    scanf("%s", foodName);

    struct valuemeal *temp = menu->f_valuemeal;
    while (temp != NULL)
    {
        if (strcmp(temp->food_name, foodName) == 0)
        {
            printf("请输入新的套餐名称：");
            scanf("%s", temp->food_name);
            printf("请输入新的套餐价格：");
            scanf("%d", &(temp->price));

            found = true;
            printf("修改套餐成功！\n");
            break;
        }

        temp = temp->next;
    }

    if (!found)
    {
        printf("未找到该套餐！\n");
    }
}

// 修改小吃功能
void modifySnack(struct menu *menu)
{
    char snackName[50];
    bool found = false;

    printf("请输入要修改的小吃名称：");
    scanf("%s", snackName);

    struct snack *temp = menu->f_snack;
    while (temp != NULL)
    {
        if (strcmp(temp->snack_name, snackName) == 0)
        {
            printf("请输入新的小吃名称：");
            scanf("%s", temp->snack_name);
            printf("请输入新的小吃价格：");
            scanf("%d", &(temp->price));

            found = true;
            printf("修改小吃成功！\n");
            break;
        }

        temp = temp->next;
    }

    if (!found)
    {
        printf("未找到该小吃！\n");
    }
}

// 修改饮品功能
void modifyDrink(struct menu *menu)
{
    char drinkName[50];
    bool found = false;

    printf("请输入要修改的饮品名称：");
    scanf("%s", drinkName);

    struct drink *temp = menu->f_drink;
    while (temp != NULL)
    {
        if (strcmp(temp->drink_name, drinkName) == 0)
        {
            printf("请输入新的饮品名称：");
            scanf("%s", temp->drink_name);
            printf("请输入新的饮品价格：");
            scanf("%d", &(temp->price));

            found = true;
            printf("修改饮品成功！\n");
            break;
        }

        temp = temp->next;
    }

    if (!found)
    {
        printf("未找到该饮品！\n");
    }
}

// 遍历显示所有的套餐、小吃、饮品等信息
void displayMenu(struct menu *menu)
{
    while (menu != NULL)
    {
        if (menu->num == 1)
        {
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
        }
        if (menu->num == 2)
        {
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
        }
        if (menu->num == 3)
        {

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
        }
        menu = menu->next;
    }
}
