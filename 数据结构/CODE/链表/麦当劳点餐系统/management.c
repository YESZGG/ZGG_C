#include "order.h"

void printAddMenu()
{
    printf("\n请选择要添加的菜单类别：\n");
    printf("1. 超值套餐\n");
    printf("2. 小吃\n");
    printf("3. 饮品\n");
    printf("0. 返回管理员界面\n");
}

void addMenu(struct menu *head, int num, const char* name, float price)
{
    struct menu *newItem = (struct menu*)malloc(sizeof(struct menu));
    newItem->num = num;
    strcpy(newItem->name, name);
    newItem->price = price;
    newItem->next = NULL;

    struct menu *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newItem;
}
