#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#define TEST_MAGIC 'x'  // 定义幻数

#define LED1 _IO(TEST_MAGIC, 0)
#define LED2 _IO(TEST_MAGIC, 1)
#define LED3 _IO(TEST_MAGIC, 2)
#define LED4 _IO(TEST_MAGIC, 3)

#define LED_ON 0   // 灯亮
#define LED_OFF 1  // 灯灭

void led_on(int fd_led, int leds);
void led_off(int fd_led, int leds);
void ioctl_led(int startX, int startY, int endX, int endY);

#endif
