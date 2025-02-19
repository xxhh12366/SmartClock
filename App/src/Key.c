/***********************
ʱ�䣺2025.01.010
���ݣ�����Ӧ��
�汾��V1.0
************************/

#include <reg51.h>
#include <intrins.h>
#include "delay.h"
#include "Key.h"
#include "LED.h"

void Key_Set(unsigned char OutPin, unsigned char *KeyNum)
{
	KEYOUT1 = (OutPin == 1)? 0:1;
	KEYOUT2 = (OutPin == 2)? 0:1;
	KEYOUT3 = (OutPin == 3)? 0:1;
	KEYOUT4 = (OutPin == 4)? 0:1;
	
	if(!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4)
	{
		DelayXms(10);
			if(!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4)
			{
				if(KEYIN1 == 0)*KeyNum = 10 + OutPin;
				if(KEYIN2 == 0)*KeyNum = 20 + OutPin;
				if(KEYIN3 == 0)*KeyNum = 30 + OutPin;
				if(KEYIN4 == 0)*KeyNum = 40 + OutPin;
			}
	}while (!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4);
}

unsigned char Key_Scan()
{
	unsigned char temp, temp2, KeyNum = 0;
	unsigned char *ptr_KEYPORT;
	*ptr_KEYPORT = 0xf0;
	temp = *ptr_KEYPORT;
	if(temp != 0xf0)//ָ�а������£�P2�յ������ݲ���
	{
		DelayXms(10);
		if(temp != 0xf0)//1111 0000 ȥ�����
		{
			temp = *ptr_KEYPORT & 0xf0;//ͨ����λ��,ȡ����λ,������õ��������к�
			*ptr_KEYPORT = 0x0f;//0000 1111  ȥ�����
			temp2 = *ptr_KEYPORT & 0x0f;	//ͨ����λ��,ȡ����λ,������õ��������к�	
		}

	}while(temp != 0xf0);//ֻһ���������£���Ȼ�������򶼽����жϣ�����������������ֻ����һ��
	
	switch(temp + temp2)
	{
		case 0xee:KeyNum = 1;break;//1110 1110
		case 0xdd:KeyNum = 2;break;//1101 1101
	}

	return KeyNum;
}

//void Key_Service()
//{
//		switch(Key_Scan())
//		{
//			case 0:break;
//			case 1:Startflag = 1;break;
//			case 2:Startflag = 0;break;
//			case 3:UpDownflag = 1;break;
//			case 4:UpDownflag = 0;break;
//			default:break;
//		}
//		if(Startflag)
//		{
//		P1 = temp;
//			if(UpDownflag)
//			{
//				temp = _crol_(temp,1);
//			}
//			else
//			{
//				temp = _cror_(temp,1);
//			}
//			DelayXms(500);
//		}

//}
