#ifndef __KEY_H
#define __KEY_H

#include "REG52.H"

sbit S3 = P3^5;//闹钟功能
sbit S4 = P3^6;//秒表功能
sbit S5 = P3^4;//校时位选
sbit S6 = P3^2;//数值加//EX0
sbit S7 = P3^3;//数值减//EX1
sbit S8 = P3^7;//切换功能

void S3_Init(void);
void S4_Init(void);
void S5_Init(void);
void S8_Init(void);

#endif
