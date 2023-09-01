#include "lcd.h"
#include "bmp.h"
#include "image.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
    LCD lcd;
    BMP bmp;
    IFM image;

    if (!lcd.openLcd())
    {
        cerr << "Failed to open LCD" << endl;
        return -1;
    }

    if (!lcd.mapMemory())
    {
        lcd.closeLcd();
        return -1;
    }

    lcd.displayColor(LCD::WHITE);

    sleep(2);

    bmp.showBMP(image.get_index(2), lcd.getAddr());
    sleep(2);
    bmp.showBMP(image.get_index(0), lcd.getAddr(), 0, 0);

    // i++;
    // bmp.showBMP(image.get_index(i), lcd.getAddr());

    // bmp.showBMP("1.bmp", lcd.getAddr());
    // sleep(3);
    // bmp.showBMP("1.bmp", lcd.getAddr(), 0, 0);

    lcd.closeLcd();

    return 0;
}
