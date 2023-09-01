#include "lcd.h"


using namespace std;

#define BUFFER_SIZE 800 * 480

LCD::LCD() : fd_lcd(-1), addr(NULL), lcdPath("/dev/fb0")
{
}

LCD::~LCD()
{
    unmapMemory();
}

bool LCD::openLcd()
{
    fd_lcd = open(this->lcdPath, O_RDWR);
    if (fd_lcd < 0)
    {
        return false;
    }
    return true;
}

void LCD::closeLcd()
{
    close(fd_lcd);
    fd_lcd = -1;
}

bool LCD::mapMemory()
{
    addr = static_cast<unsigned int *>(mmap(NULL, BUFFER_SIZE * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd_lcd, 0));
    if (addr == MAP_FAILED)
    {
        cerr << "Failed to map memory" << endl;
        return false;
    }
    return true;
}

unsigned int* LCD::getAddr() const
{
    return addr;
}

void LCD::unmapMemory()
{
    munmap(addr, BUFFER_SIZE * 4);
    addr = NULL;
}

void LCD::displayColor(unsigned int color)
{
    for (int y = 0; y < 480; y++)
    {
        for (int x = 0; x < 800; x++)
        {
            *(addr + y * 800 + x) = color;
        }
    }
}
