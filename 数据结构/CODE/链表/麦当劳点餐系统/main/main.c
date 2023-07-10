#include "order.h"
#include "admin.h"

int main()
{
    struct menu *head = createMenuData(); // Create menu and food data

    int choice;
    do
    {
        printMainMenu(); // Print main menu
        printf("请输入您的选择：");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            // User interface
            int userChoice;
            do
            {
                printUserMainMenu(); // Print user main menu
                printf("请输入您的选择：");
                scanf("%d", &userChoice);
                switch (userChoice)
                {
                case 1:
                {
                    // Value meals
                    struct menu *menu = head;
                    while (menu != NULL)
                    {
                        if (menu->num == 1)
                        {
                            int totalPrice = orderFood(menu, userChoice);
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
                    // Snacks
                    struct menu *menu = head;
                    while (menu != NULL)
                    {
                        if (menu->num == 2)
                        {
                            int totalPrice = orderFood(menu, userChoice);
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
                    // Drinks
                    struct menu *menu = head;
                    while (menu != NULL)
                    {
                        if (menu->num == 3)
                        {
                            int totalPrice = orderFood(menu, userChoice);
                            printf("总价为：%d\n", totalPrice);
                            printf("\n");
                            break;
                        }
                        menu = menu->next;
                    }
                    break;
                }
                case 0:
                    printf("感谢使用麦乐送点餐系统！\n");
                    break;
                default:
                    printf("无效的选择，请重新输入。\n");
                    break;
                }
            } while (userChoice != 0);
            break;
        }
        case 2:
        {
            int adminChoice;
            do
            {
                printAdminMenu();
                printf("请输入您的选择：");
                scanf("%d", &adminChoice);
                switch (adminChoice)
                {
                case 1:
                {
                    int addChoice;
                    do
                    {
                        printAddMenu();
                        printf("请输入您的选择：");
                        scanf("%d", &addChoice);
                        switch (addChoice)
                        {
                        case 1:
                        {
                            struct menu *menu = head;
                            while (menu != NULL)
                            {
                                if (menu->num == 1)
                                {
                                    addValuemeal(menu);
                                    break;
                                }
                                menu = menu->next;
                            }
                            break;
                        }
                        case 2:
                        {
                            struct menu *menu = head;
                            while (menu != NULL)
                            {
                                if (menu->num == 2)
                                {
                                    addSnack(menu);
                                    break;
                                }
                                menu = menu->next;
                            }
                            break;
                        }
                        case 3:
                        {
                            struct menu *menu = head;
                            while (menu != NULL)
                            {
                                if (menu->num == 3)
                                {
                                    addDrink(menu);
                                    break;
                                }
                                menu = menu->next;
                            }
                            break;
                        }
                        }
                    } while (addChoice != 0);
                    break;
                }
                case 2:
                {
                    int deleteChoice;
                    do
                    {
                        printDeleteMenu();
                        printf("请输入您的选择：");
                        scanf("%d", &deleteChoice);

                        switch (deleteChoice)
                        {
                        case 1:
                        {
                            struct menu *menu = head;
                            while (menu != NULL)
                            {
                                if (menu->num == 1)
                                {
                                    deleteValuemeal(menu);
                                    break;
                                }
                                menu = menu->next;
                            }
                            break;
                        }
                        case 2:
                        {
                            struct menu *menu = head;
                            while (menu != NULL)
                            {
                                if (menu->num == 2)
                                {
                                    deleteSnack(menu);
                                    break;
                                }
                                menu = menu->next;
                            }
                            break;
                        }
                        case 3:
                        {
                            struct menu *menu = head;
                            while (menu != NULL)
                            {
                                if (menu->num == 3)
                                {
                                    deleteDrink(menu);
                                    break;
                                }
                                menu = menu->next;
                            }
                            break;
                        }
                        }
                    } while (deleteChoice != 0);
                    break;
                }
                case 3:
                {
                    int modifyChoice;
                    do
                    {
                        printModifyMenu();
                        printf("请输入您的选择：");
                        scanf("%d", &modifyChoice);
                        switch (modifyChoice)
                        {
                        case 1:
                        {
                            struct menu *menu = head;
                            while (menu != NULL)
                            {
                                if (menu->num == 1)
                                {
                                    modifyValuemeal(menu);
                                    break;
                                }
                                menu = menu->next;
                            }
                            break;
                        }
                        case 2:
                        {
                            struct menu *menu = head;
                            while (menu != NULL)
                            {
                                if (menu->num == 2)
                                {
                                    modifySnack(menu);
                                    break;
                                }
                                menu = menu->next;
                            }
                            break;
                        }
                        case 3:
                        {
                            struct menu *menu = head;
                            while (menu != NULL)
                            {
                                if (menu->num == 3)
                                {
                                    modifyDrink(menu);
                                    break;
                                }
                                menu = menu->next;
                            }
                            break;
                        }
                        }
                    } while (modifyChoice != 0);
                    break;
                }
                case 4:
                {
                    struct menu *menu = head;
                    displayMenu(menu);
                    
                    break;
                }
                case 0:
                    printf("已退出管理员界面。\n");
                    break;
                default:
                    printf("无效的选择，请重新输入。\n");
                    break;
                }
            } while (adminChoice != 0);
            break;
        }
        case 0:
            printf("感谢使用麦乐送点餐系统，再见！\n");
            freeMenu(head); // Free menu memory
            break;
        default:
            printf("无效的选择，请重新输入。\n");
            break;
        }
    } while (choice != 0);

    return 0;
}
