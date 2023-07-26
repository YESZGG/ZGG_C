#include <stdio.h>
#include <stdlib.h>
#include "led_control.h"

void led_on(int fd_led, int leds)
{
    ioctl(fd_led, leds, LED_ON);
}

void led_off(int fd_led, int leds)
{
    ioctl(fd_led, leds, LED_OFF);
}

void ioctl_led(int startX, int startY, int endX, int endY)
{
    int leds[] = {LED1, LED2, LED3, LED4};
    int num_leds = sizeof(leds) / sizeof(leds[0]);

    int fd_led = open("/dev/Led", O_RDWR);

    if ((startX > 200 && endX < 400) && (startY > 420 && endY < 480))
    {
        for (int i = 0; i < num_leds; i++)
        {
            led_on(fd_led, leds[i]);
            usleep(50000);
        }
    }

    if ((startX > 400 && endX < 600) && (startY > 420 && endY < 480))
    {
        for (int i = 0; i < num_leds; i++)
        {
            led_off(fd_led, leds[i]);
            usleep(50000);
        }
    }

    close(fd_led);
}
