#ifndef __KEY_H
#define __KEY_H

#include "REG52.H"

sbit S3 = P3^5;//���ӹ���
sbit S4 = P3^6;//�����
sbit S5 = P3^4;//Уʱλѡ
sbit S6 = P3^2;//��ֵ��//EX0
sbit S7 = P3^3;//��ֵ��//EX1
sbit S8 = P3^7;//�л�����

void S3_Init(void);
void S4_Init(void);
void S5_Init(void);
void S8_Init(void);

#endif
