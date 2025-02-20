#ifndef __TIMER_H
#define __TIMER_H

typedef unsigned char timerCnt;
typedef unsigned char Sec;      // ��ʾ
typedef unsigned char Min;      // ��ʾ
typedef unsigned char Hour;     // ��ʾ
typedef unsigned char Day;
typedef unsigned char Mon;
typedef unsigned int YearType;  // ���� Year �����ͱ���

typedef char clockSec;          // ��ʵ
typedef char clockMin;          // ��ʵ
typedef char clockHour;         // ��ʵ

typedef char alarmMin;
typedef char alarmHour;

typedef char stopwatchSec;
typedef char stopwatchMin;

// �����������ʼ��
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