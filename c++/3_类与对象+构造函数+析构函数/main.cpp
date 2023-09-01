#include "table.h"

int main()
{
    Table t(6,3,0.7,Table::GREEN);
    t.setColor(Table::RED);
    t.setPrice(Table::ONE);
    t.printfInfo();

    return 0;
}