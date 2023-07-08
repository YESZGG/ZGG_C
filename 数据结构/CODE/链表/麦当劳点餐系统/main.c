#include "order.h"

#include "order.h"

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
                    // Snacks
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
                    // Drinks
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
            // Administrator interface
            int adminChoice;
            do
            {
                printAdminMenu(); // Print administrator sub-menu
                scanf("%d", &adminChoice);

                switch (adminChoice)
                {
                case 1:
                {
                    // Add information to menus
                    int addChoice;
                    do
                    {
                        printAddMenu(); // Print add menu sub-options
                        printf("请输入您的选择：");
                        scanf("%d", &addChoice);

                        switch (addChoice)
                        {
                            // Add functionality...
                        }
                    } while (addChoice != 0);
                    break;
                }
                case 2:
                {
                    // Delete information from menus
                    int deleteChoice;
                    do
                    {
                        printDeleteMenu(); // Print delete menu sub-options
                        printf("请输入您的选择：");
                        scanf("%d", &deleteChoice);

                        switch (deleteChoice)
                        {
                            // Delete functionality...
                        }
                    } while (deleteChoice != 0);
                    break;
                }
                case 3:
                {
                    // Modify information in menus
                    int modifyChoice;
                    do
                    {
                        printModifyMenu(); // Print modify menu sub-options
                        printf("请输入您的选择：");
                        scanf("%d", &modifyChoice);

                        switch (modifyChoice)
                        {
                            // Modify functionality...
                        }
                    } while (modifyChoice != 0);
                    break;
                }
                case 4:
                {
                    // Traverse menu information
                    int traverseChoice;
                    do
                    {
                        printTraverseMenu(); // Print traverse menu sub-options
                        printf("请输入您的选择：");
                        scanf("%d", &traverseChoice);

                        switch (traverseChoice)
                        {
                            // Traverse functionality...
                        }
                    } while (traverseChoice != 0);
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
