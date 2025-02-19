#ifndef __LED_H
#define __LED_H

#define GPIO_DIG P0//段码IO
#define GPIO_PLACE P3//位选IO
#define N          4//数码管个数

void LED_Light(void);
void Display(void);
unsigned char code leddata[];
extern unsigned char LEDBuf[];//在头文件extern，因为不止在LED.c里用，在main,c里也用//让它成为全局数组

#endif
