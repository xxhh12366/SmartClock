#ifndef __KEY_H
#define __KEY_H

#include <reg51.h>

#define KEYPORT P2;

sbit KEYIN1 = P2^0;
sbit KEYIN2 = P2^1;
sbit KEYIN3 = P2^2;
sbit KEYIN4 = P2^3;
sbit KEYOUT1 = P2^4;
sbit KEYOUT2 = P2^5;
sbit KEYOUT3 = P2^6;
sbit KEYOUT4 = P2^7;

void Key_Set(unsigned char, unsigned char);
unsigned char Key_Scan(void);
//void Key_Service(void);

#endif
