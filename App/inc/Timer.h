#ifndef __TIMER_H
#define __TIMER_H

typedef unsigned char timerCnt;
typedef unsigned char Sec;      // 显示
typedef unsigned char Min;      // 显示
typedef unsigned char Hour;     // 显示
typedef unsigned char Day;
typedef unsigned char Mon;
typedef unsigned int YearType;  // 定义 Year 的类型别名

typedef char clockSec;          // 真实
typedef char clockMin;          // 真实
typedef char clockHour;         // 真实

typedef char alarmMin;
typedef char alarmHour;

typedef char stopwatchSec;
typedef char stopwatchMin;

// 定义变量并初始化
static YearType Year = 2025;
unsigned char State = 0;
unsigned char wei = 1;
unsigned char funcState = 1;
unsigned char stopwatchSwitch = 1;

bool alarmRing = 0;
bool alarmSwitch = 0;
bool changeSwitch = 0;

/////////////////////////////////////////
void Timer0_Init(void);
void Timer1_Init(void);
void EX0_Init(void);
void EX1_Init(void);
void Timer0_ISR(void) interrupt 1;
void EX1_ISR(void) interrupt 2;
void Timer1_ISR(void) interrupt 3;



#endif