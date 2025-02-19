/***********************
时间：2025.01.06
内容：LED数码管
版本：V1.0
************************/


#include <reg51.h>
#include <intrins.h>
#include "delay.h"
#include "LED.h"

/***********************
名字：LED_Light()
时间：2025.01.06
内容：LED灯亮
类型：void
************************/
void LED_Light(){//LED灯亮
	P1=~P1;
}

unsigned char code leddata[]={//显示数字
	0x3F,//"0"
	0X06,//"1"
	0X5B,//"2"
	0X4F,//"3"
	0X66,//"4"
	0X6D,//"5"
	0X7D,//"6"
	0X07,//"7"
	0X7F,//"8"
	0X6F,//"9"
	0X77,//"A"
	0X7C,//"B"
	0X39,//"C"
	0x40,//"-"
	0x00,//熄灭
};

unsigned char LEDBuf[] = {8,8,8,8};//显示缓冲区
unsigned char code PLACE_CODE[] = {0xfe,0xfd,0xfb,0xf7};

/***********************
名字：Dispaly()
时间：2025.01.06
内容：显示内容
类型：void
************************/
void Dispaly()
{
	static unsigned char i=0;

			GPIO_PLACE = PLACE_CODE[i];//选中第几个数码管
		  GPIO_DIG = leddata[LEDBuf[i]];//让被选中数码管显示什么符号
			
			DelayXms(1);
		//GPIO_DIG = 0x00;
			i++;
			if(i==N)i=0;

}

