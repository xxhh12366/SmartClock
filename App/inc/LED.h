#ifndef __LED_H
#define __LED_H

#define GPIO_DIG P0//段码IO
#define GPIO_PLACE P3//位选IO
#define N          4//数码管个数

sbit LED = P0^5;
sbit L1 = P2^0;
sbit L2 = P2^1;
sbit L3 = P2^2;
sbit L4 = P2^3;

void LED_Init(void)
void Display(void);

void showNum0(void);
void showNum1(void);
void showNum2(void);
void showNum3(void);

unsigned char code leddata[];
unsigned char LEDBuf[];

#endif
