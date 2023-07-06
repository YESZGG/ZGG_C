#include "bookmanagement.h"

int main()
{
    struct bookList *head = init_head();
    if(head == (struct bookList *)-1)
    {
        perror("head init failed.");
        return -1;
    }


    Function_Select(head);

    return 0;
}