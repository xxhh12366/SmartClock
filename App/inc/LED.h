#ifndef __LED_H
#define __LED_H

#define GPIO_DIG P0//����IO
#define GPIO_PLACE P3//λѡIO
#define N          4//����ܸ���

void LED_Light(void);
void Display(void);
unsigned char code leddata[];
extern unsigned char LEDBuf[];//��ͷ�ļ�extern����Ϊ��ֹ��LED.c���ã���main,c��Ҳ��//������Ϊȫ������

#endif
