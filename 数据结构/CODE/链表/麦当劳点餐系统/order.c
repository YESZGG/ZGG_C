#include "order.h"

// 创建新的食物节点
struct valuemeal* createFood(char name[], int price) {
    struct valuemeal* food = (struct valuemeal*)malloc(sizeof(struct valuemeal));
    strcpy(food->food_name, name);
    food->price = price;
    food->next = NULL;
    food->prev = NULL;
    return food;
}

// 创建新的小吃节点
struct snack* createSnack(char name[], int price) {
    struct snack* snack = (struct snack*)malloc(sizeof(struct snack));
    strcpy(snack->snack_name, name);
    snack->price = price;
    snack->next = NULL;
    snack->prev = NULL;
    return snack;
}


// 创建新的饮品节点
struct drink* createDrink(char name[], int price) {
    struct drink* drink = (struct drink*)malloc(sizeof(struct drink));
    strcpy(drink->drink_name, name);
    drink->price = price;
    drink->next = NULL;
    drink->prev = NULL;
    return drink;
}

// 创建新的菜单节点
struct meun* createMenu(int num, char name[]) {
    struct meun* menu = (struct meun*)malloc(sizeof(struct meun));
    menu->num = num;
    strcpy(menu->meun_name, name);
    menu->f_valuemeal = NULL;
    menu->f_snack = NULL;
    menu->f_drink = NULL;
    menu->next = NULL;
    menu->prev = NULL;
    return menu;
}

// 添加食物到菜单的食物链表中
void addFoodToMenu(struct meun* menu, struct valuemeal* food) {
    if (menu->f_valuemeal == NULL) {
        menu->f_valuemeal = food;
    } else {
        struct valuemeal* cur = menu->f_valuemeal;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = food;
        food->prev = cur;
    }
}

// 添加小吃到菜单的小吃链表中
void addSnackToMenu(struct meun* menu, struct snack* snack) {
    if (menu->f_snack == NULL) {
        menu->f_snack = snack;
    } else {
        struct snack* cur = menu->f_snack;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = snack;
        snack->prev = cur;
    }
}

// 添加饮品到菜单的饮品链表中
void addDrinkToMenu(struct meun* menu, struct drink* drink) {
    if (menu->f_drink == NULL) {
        menu->f_drink = drink;
    } else {
        struct drink* cur = menu->f_drink;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = drink;
        drink->prev = cur;
    }
}

// 打印菜单内容
void printMenu(struct meun* menu) {
    printf("菜单编号：%d\n", menu->num);
    printf("菜单名称：%s\n", menu->meun_name);

    printf("食物列表：\n");
    struct valuemeal* curFood = menu->f_valuemeal;
    while (curFood != NULL) {
        printf("%s - ￥%d\n", curFood->food_name, curFood->price);
        curFood = curFood->next;
    }

    printf("小吃列表：\n");
    struct snack* curSnack = menu->f_snack;
    while (curSnack != NULL) {
        printf("%s - ￥%d\n", curSnack->snack_name, curSnack->price);
        curSnack = curSnack->next;
    }

    printf("饮品列表：\n");
    struct drink* curDrink = menu->f_drink;
    while (curDrink != NULL) {
        printf("%s - ￥%d\n", curDrink->drink_name, curDrink->price);
        curDrink = curDrink->next;
    }
}


// 初始化食物、小吃、饮品 列表
void init_menu()
{
    // 创建菜单
    struct meun* menu1 = createMenu(1, "菜单1");
    struct meun* menu2 = createMenu(2, "菜单2");

    // 创建食物
    struct valuemeal* food1_menu1 = createFood("食物1", 20);
    struct valuemeal* food2_menu1 = createFood("食物2", 30);
    struct valuemeal* food1_menu2 = createFood("食物3", 25);
    struct valuemeal* food2_menu2 = createFood("食物4", 35);

    // 创建小吃
    struct snack* snack1_menu1 = createSnack("小吃1", 10);
    struct snack* snack2_menu1 = createSnack("小吃2", 15);
    struct snack* snack1_menu2 = createSnack("小吃3", 12);
    struct snack* snack2_menu2 = createSnack("小吃4", 18);

    // 创建饮品
    struct drink* drink1_menu1 = createDrink("饮品1", 5);
    struct drink* drink2_menu1 = createDrink("饮品2", 8);
    struct drink* drink1_menu2 = createDrink("饮品3", 6);
    struct drink* drink2_menu2 = createDrink("饮品4", 9);

    // 添加食物到菜单的食物链表中
    addFoodToMenu(menu1, food1_menu1);
    addFoodToMenu(menu1, food2_menu1);
    addFoodToMenu(menu2, food1_menu2);
    addFoodToMenu(menu2, food2_menu2);

    // 添加小吃到菜单的小吃链表中
    addSnackToMenu(menu1, snack1_menu1);
    addSnackToMenu(menu1, snack2_menu1);
    addSnackToMenu(menu2, snack1_menu2);
    addSnackToMenu(menu2, snack2_menu2);

    // 添加饮品到菜单的饮品链表中
    addDrinkToMenu(menu1, drink1_menu1);
    addDrinkToMenu(menu1, drink2_menu1);
    addDrinkToMenu(menu2, drink1_menu2);
    addDrinkToMenu(menu2, drink2_menu2);
}


void userMenuInterface() {
    int choice = -1;
    int subChoice = -1;
    
    while (choice != 0) {
        printf("欢迎使用麦乐送点餐系统\n");
        printf("      1. 超值套餐\n");
        printf("      2. 小吃\n");
        printf("      3. 饮品\n");
        printf("      0. 退出系统\n");
        
        printf("请输入要进入的菜单序号：");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                // 进入超值套餐菜单
                printf("超值套餐 菜单\n");
                printf("1. 经典麦辣鸡腿汉堡   冰镇可乐  薯条(麦乐鸡)\n");
                printf("2. 原味板烧鸡腿汉堡   冰镇可乐  薯条(麦乐鸡)\n");
                printf("0. 退出到用户主菜单界面\n");
                
                while (subChoice != 0) {
                    printf("请输入要点餐的序号：");
                    scanf("%d", &subChoice);
                    
                    switch(subChoice) {
                        case 1:
                            printf("您选择了经典麦辣鸡腿汉堡、冰镇可乐和薯条(麦乐鸡)。\n");
                            // 执行点餐相关操作
                            break;
                        case 2:
                            printf("您选择了原味板烧鸡腿汉堡、冰镇可乐和薯条(麦乐鸡)。\n");
                            // 执行点餐相关操作
                            break;
                        case 0:
                            printf("退出到用户主菜单界面\n");
                            break;
                        default:
                            printf("无效的选项，请重新输入。\n");
                            break;
                    }
                }
                
                subChoice = -1;
                break;
            case 2:
                // 进入小吃菜单
                printf("小吃 菜单\n");
                // 小吃菜单项
                break;
            case 3:
                // 进入饮品菜单
                printf("饮品 菜单\n");
                // 饮品菜单项
                break;
            case 0:
                printf("退出系统\n");
                break;
            default:
                printf("无效的选项，请重新输入。\n");
                break;
        }
    }
}

void adminMenuInterface() {
    int choice = -1;
    
    while (choice != 0) {
        printf("欢迎使用麦乐送点餐系统（管理员界面）\n");
        printf("      1. 超值套餐管理\n");
        printf("      2. 小吃管理\n");
        printf("      3. 饮品管理\n");
        printf("      0. 返回用户主菜单\n");
        
        printf("请输入要进入的菜单序号：");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                // 进入超值套餐管理界面
                printf("超值套餐 管理界面\n");
                // 超值套餐管理功能
                break;
            case 2:
                // 进入小吃管理界面
                printf("小吃 管理界面\n");
                // 小吃管理功能
                break;
            case 3:
                // 进入饮品管理界面
                printf("饮品 管理界面\n");
                // 饮品管理功能
                break;
            case 0:
                printf("返回用户主菜单\n");
                break;
            default:
                printf("无效的选项，请重新输入。\n");
                break;
        }
    }
}

int main() {
    int userType = -1;
    
    printf("请选择用户类型：\n");
    printf("      1. 用户\n");
    printf("      2. 管理员\n");
    printf("请输入用户类型序号：");
    scanf("%d", &userType);
    
    switch(userType) {
        case 1:
            userMenuInterface();
            break;
        case 2:
            adminMenuInterface();
            break;
        default:
            printf("无效的用户类型。\n");
            break;
    }
    
    return 0;
}
