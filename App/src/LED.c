/***********************
时间：2025.01.06
内容：LED灯与数码管显示
版本：V1.0
************************/


#include <reg52.h>
#include <intrins.h>
#include "LED.h"

/***********************
名字：LED_Init()
时间：2025.02.19
内容：点亮那两个灯
类型：void
************************/
void LED_Init()
{
	LED = 0;
}

/***********************
名字：Dispaly()
时间：2025.01.06
内容：数码管刷新
类型：void
************************/
void Display()
{
	static unsigned char i=0;

			GPIO_PLACE = PLACE_CODE[i];
		  GPIO_DIG = leddata[LEDBuf[i]];
			
			DelayXms(1);
		//GPIO_DIG = 0x00;
			i++;
			if(i==N)i=0;

}
////////////////////////////////////////////////////////////////////
/***********************
名字：showNum0()
时间：2025.02.19
内容：更改数码管显示时分
类型：void
************************/
void showNum0()
{
	LEDBuf[0] = hour/10;
	LEDBuf[1] = hour%10;
	LEDBuf[2] = min/10;
	LEDBuf[3] = min%10;
}

/***********************
名字：showNum1()
时间：2025.02.20
内容：更改数码管显示分秒
类型：void
************************/
void showNum1()
{
	LEDBuf[0] = min/10;
	LEDBuf[1] = min%10;
	LEDBuf[2] = sec/10;
	LEDBuf[3] = sec%10;
}

/***********************
名字：showNum2()
时间：2025.02.20
内容：更改数码管显示月日
类型：void
************************/
void showNum2()
{
	LEDBuf[0] = mon/10;
	LEDBuf[1] = mon%10;
	LEDBuf[2] = day/10;
	LEDBuf[3] = day%10;
}

/***********************
名字：showNum3()
时间：2025.02.20
内容：更改数码管显示年
类型：void
************************/
void showNum3()
{
	LEDBuf[0] = year/1000;
	LEDBuf[1] = year/100 - year/1000*10;
	LEDBuf[2] = year/10 - year/100*10;
	LEDBuf[3] = year%10;
}

////////////////////////////////////////////////////////////////////

/***********************
名字：leddata[]
时间：2025.01.06
内容：数码管显字
类型：unsigned char
***********************/

unsigned char code leddata[]={
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

/***********************
名字：LEDBuf[],PLACE_CODE[]
时间：2025.01.06
内容：数码管显字
类型：unsigned char
************************/
unsigned char LEDBuf[] = {8,8,8,8};//显示缓冲区
unsigned char code PLACE_CODE[] = {0xfe,0xfd,0xfb,0xf7};



