/***********************
时间：2025.02.20
内容：与定时中断，按键中断有关的函数
版本：V1.1
************************/

#include <reg51.h>
#include "led.h"
#include "show.h"
#include "timer.h"

////////////////////////中断与定时器初始化//////////////////////////////
void Timer0_Init()		//50毫秒@12.000MHz
{
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0xB0;				//设置定时初始值
	TH0 = 0x3C;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
    ET0 = 1;
    EA = 1;//总中断开关放在这了！
	TR0 = 1;				//定时器0开始计时
}

void Timer1_Init()		//1毫秒@12.000MHz
{
	TMOD &= 0x0F;			//设置定时器模式
	TMOD |= 0x10;			//设置定时器模式
	TL1 = 0x18;				//设置定时初始值
	TH1 = 0xFC;				//设置定时初始值
	TF1 = 0;				//清除TF1标志
    ET1 = 1;
	TR1 = 1;				//定时器1开始计时
}

void EX0_Init()//时钟页面切换
{
    IT0 = 1;
    EX0 = 1;
}

void EX1_Init()//数值修改
{
    IT1 = 1;
    EX1 = 1;
}

////////////////////////中断服务函数//////////////////////////////

/***********************
名字：timer0_ISR()
时间：2025.02.20
内容：定时中断，用来计时，让sec等变量同步变化
类型：void
************************/
void timer0_ISR(void) interrupt 1
{
    timerCnt++;

    if(timerCnt >= 20)//1s
    {
        timerCnt = 0;
        clockSec++;
        
        if(clockSec >= 60)
        {
            clockSec = 0;
            clockMin++;
            if(clockSec >= 60)
            {
                clockMin = 0;
                clockHour++;
                if(clockHour >= 24)
                {
                    clockHour = 0;
                    Day++;
                    if(Day >= 30)
                    {
                        Day = 0;
                        Mon++;
                        if(Mon >= 12)
                        {
                            Mon = 0;
                            Year++;
                        }
                    }
                }
            }
        }
        else if(stopwatchSwitch == 2 && funcState == 3)
        {
            stopwatchSec++;
            if(stopwatchSec >= 60)
            {
                stopwatchSec = 0;
                showRight();//显示秒表
                stopwatchMin++;
                if(stopwatchMin >= 60)
                {
                    stopwatchSwitch = 0;
                }
            }
        }
        else if(changeSwitch && !alarmRing)//未响铃时
        {
            switch(wei)
            {
                case 1:L1 = ~L1;L2 = 1;L3 = 1;L4 = 1;break;
                case 2:L1 = 1;L2 = ~L2;L3 = 1;L4 = 1;break;
                case 3:L1 = 1;L2 = 1;L3 = ~L3;L4 = 1;break;
                case 4:L1 = 1;L2 = 1;L3 = 1;L4 = ~L4;break;
                default:break;
            }
        }
        else if(alarmRing)//响铃时，1s关
        {
            L1 = 1;L2 = 1;L3 = 1;L4 = 1;
        }
    }
    else if(alarmRing)//响铃时，50ms开
        {
             L1 = 0;L2 = 0;L3 = 0;L4 = 0;
        }
    TL0 = 0xB0;				//设置定时初始值
	TH0 = 0x3C;	
}

void timer1_ISR(void) interrupt 3//刷新数码管
{
    TR1 = 0;
    Display();
    TL1 = 0x18;				//设置定时初始值
	TH1 = 0xFC;
    TR1 = 1;
}

void EX0_ISR(void) interrupt 0//自增
{   
    typedef char gewei;//单独提出个位来调整
    typedef char shiwei;//单独提出十位来调整
    typedef char baiwei;//单独提出百位来调整
    typedef char qianwei;//单独提出千位来调整

    switch(funcState)
    {
        case 1://时钟下
            switch(State)
            {
                case 0://时分
                    switch(wei)
                    {//采用的调法是每一位单独加
                        case 1:clockHour = clockHour + 10;if(clockHour/10 >= 3)clockHour = clockHour - clockHour/10 *10;showRight();break;
                        case 2:gewei = clockHour % 10; gewei++;if(gewei >= 10)gewei = 0; clockHour = clockHour + (10-clockHour%10) - 10 + gewei;showRight();break;
                        case 3:clockMin = clockMin + 10;if(clockMin/10 >= 3)clockMin = clockMin - clockMin/10 *10;showRight();break;
                        case 4:gewei = clockMin % 10; gewei++;if(gewei >= 10)gewei = 0; clockMin = clockMin + (10-clockMin%10) - 10 + gewei;showRight();break;
                        default:break;
                    }
                    break;
                case 1://分秒
                
                    switch(wei)
                    {
                        case 1:clockMin = clockMin + 10;if(clockMin/10 >= 3)clockMin = clockMin - clockMin/10 *10;showRight();break;
                        case 2:gewei = clockMin % 10; gewei++;if(gewei >= 10)gewei = 0; clockMin = clockMin + (10-clockMin%10) - 10 + gewei;showRight();break;
                        case 3:clockSec = clockSec + 10;if(clockSec/10 >= 3)clockSec = clockSec - clockSec/10 *10;showRight();break;
                        case 4:gewei = clockSec % 10; gewei++;if(gewei >= 10)gewei = 0; clockSec = clockSec + (10-clockSec%10) - 10 + gewei;showRight();break;
                        default:break;
                    }
                    break;  
                case 2://月日
                {
                    switch(wei)
                    {
                        case 1:Mon = Mon + 10;if(Mon/10 >= 3)Mon = Mon - Mon/10 *10;showRight();break;
                        case 2:gewei = Mon % 10; gewei++;if(gewei >= 10)gewei = 0; Mon = Mon + (10-Mon%10) - 10 + gewei;showRight();break;
                        case 3:Day = Day + 10;if(Day/10 >= 4)Day = Day - Day/10 *10;showRight();break;
                        case 4:gewei = Day % 10; gewei++;if(gewei >= 10)gewei = 0; Day = Day + (10-Day%10) - 10 + gewei;showRight();break;
                        default:break;
                    }
                    break;
                }
                case 3://年
                {
                    switch(wei)
                    {
                        case 1:qianwei = Year / 1000;qianwei++;if(qianwei >= 10)qianwei = 0;Year = Year - (Year / 1000) * 1000 + qianwei * 1000;showRight();break;
                        case 2:baiwei = (Year / 100) % 10;baiwei++;if(baiwei >= 10)baiwei = 0;Year = Year - ((Year / 100) % 10) * 100 + baiwei * 100;showRight();break;
                        case 3:shiwei = (Year / 10) % 10;shiwei++;if(shiwei >= 10)shiwei = 0;Year = Year - ((Year / 10) % 10) * 10 + shiwei * 10;showRight();break;
                        case 4:gewei = Year % 10;gewei++;if(gewei >= 10)gewei = 0;Year = Year - (Year % 10) + gewei;showRight();break;default:break;
                    }
                    break;
                }
                default:break;
                            
            }
            
        case 2://闹钟下，只能调整时分
            alarmSwitch = 1;
            switch(wei)
                    {
                        case 1:alarmHour = alarmHour + 10;if(alarmHour/10 >= 3)alarmHour = alarmHour - alarmHour/10 *10;showRight();break;
                        case 2:gewei = alarmHour % 10; gewei++;if(gewei >= 10)gewei = 0; alarmHour = alarmHour + (10-alarmHour%10) - 10 + gewei;showRight();break;
                        case 3:alarmMin = alarmMin + 10;if(alarmMin/10 >= 3)alarmMin = alarmMin - alarmMin/10 *10;showRight();break;
                        case 4:gewei = alarmMin % 10; gewei++;if(gewei >= 10)gewei = 0; alarmMin = alarmMin + (10-alarmMin%10) - 10 + gewei;showRight();break;
                        default:break;
                    }

            break;
        case 3://秒表下
            stopwatchSwitch = 1;
            switch (wei)
                {
                case 1:stopwatchMin = stopwatchMin + 10;if(stopwatchMin/10 >= 3)stopwatchMin = stopwatchMin - stopwatchMin/10 *10;showRight();break;
                case 2:gewei = stopwatchMin % 10; gewei++;if(gewei >= 10)gewei = 0; stopwatchMin = stopwatchMin + (10-stopwatchMin%10) - 10 + gewei;showRight();break;
                case 3:stopwatchSec = stopwatchSec + 10;if(stopwatchSec/10 >= 3)stopwatchSec = stopwatchSec - stopwatchSec/10 *10;showRight();break;
                case 4:gewei = stopwatchSec % 10; gewei++;if(gewei >= 10)gewei = 0; stopwatchSec = stopwatchSec + (10-stopwatchSec%10) - 10 + gewei;showRight();break;
                default:break;
                }
            break;
        default:break;
    }
}


void EX1_ISR(void) interrupt 2//自减
{
    typedef char gewei;//单独提出个位来调整
    typedef char shiwei;//单独提出十位来调整
    typedef char baiwei;//单独提出百位来调整
    typedef char qianwei;//单独提出千位来调整
    switch(funcState)
    {
        case 1://时钟下
            switch(State)
            {
                case 0://时分
                    switch(wei)
                    {//采用的调法是每一位单独加
                        case 1:clockHour = clockHour - 10;if(clockHour < 0)clockHour = clockHour + 24;showRight();break;
                        case 2:gewei = clockHour % 10; gewei--;if(gewei < 0)gewei = 9; clockHour = clockHour - clockHour%10 + gewei;showRight();break;
                        case 3:clockMin = clockMin - 10;if(clockMin < 0)clockMin = clockMin + 60;showRight();break;
                        case 4:gewei = clockMin % 10; gewei--;if(gewei < 0)gewei = 9; clockMin = clockMin - clockMin%10 + gewei;showRight();break;
                        default:break;
                    }
                    break;
                case 1://分秒
                
                    switch(wei)
                    {
                        case 1:clockMin = clockMin - 10;if(clockMin < 0)clockMin = clockMin + 60;showRight();break;
                        case 2:gewei = clockMin % 10; gewei--;if(gewei < 0)gewei = 9; clockMin = clockMin - clockMin%10 + gewei;showRight();break;
                        case 3:clockSec = clockSec - 10;if(clockSec < 0)clockSec = clockSec + 60;showRight();break;
                        case 4:gewei = clockSec % 10; gewei--;if(gewei < 0)gewei = 9; clockSec = clockSec - clockSec%10 + gewei;showRight();break;
                        default:break;
                    }
                    break;  
                case 2://月日
                
                    switch(wei)
                    {
                        case 1:Mon = Mon - 10;if(Mon < 0)Mon = Mon + 12;showRight();break;
                        case 2:gewei = Mon % 10; gewei--;if(gewei < 0)gewei = 9; Mon = Mon - Mon%10 + gewei;showRight();break;
                        case 3:Day = Day - 10;if(Day < 0)Day = Day + 30;showRight();break;
                        case 4:gewei = Day % 10; gewei--;if(gewei < 0)gewei = 9; Day = Day - Day%10 + gewei;showRight();break;
                        default:break;
                    }
                    break;
                case 3://年
                    switch(wei)
                    {
                        case 1:qianwei = Year / 1000;qianwei--;if(qianwei < 0)qianwei = 9;Year = Year - (Year / 1000) * 1000 + qianwei * 1000;showRight();break;
                        case 2:baiwei = (Year / 100) % 10;baiwei--;if(baiwei < 0)baiwei = 9;Year = Year - ((Year / 100) % 10) * 100 + baiwei * 100;showRight();break;
                        case 3:shiwei = (Year / 10) % 10;shiwei--;if(shiwei < 0)shiwei = 9;Year = Year - ((Year / 10) % 10) * 10 + shiwei * 10;showRight();break;
                        case 4:gewei = Year % 10;gewei--;if(gewei < 0)gewei = 9;Year = Year - (Year % 10) + gewei;showRight();break;default:break;
                    }
                    break;
                default:break;
            }
        case 2://闹钟下，只能调整时分
            alarmSwitch = 1;
            switch(wei)
                    {
                        case 1:alarmHour = alarmHour - 10;if(alarmHour < 0)alarmHour = alarmHour + 24;showRight();break;
                        case 2:gewei = alarmHour % 10; gewei--;if(gewei < 0)gewei = 9; alarmHour = alarmHour - alarmHour%10 + gewei;showRight();break;
                        case 3:alarmMin = alarmMin - 10;if(alarmMin < 0)alarmMin = alarmMin + 60;showRight();break;
                        case 4:gewei = alarmMin % 10; gewei--;if(gewei < 0)gewei = 9; alarmMin = alarmMin - alarmMin%10 + gewei;showRight();break;
                        default:break;
                    }

            break;
        case 3://秒表下
            stopwatchSwitch = 1;
            switch (wei)
                {
                case 1:stopwatchMin = stopwatchMin - 10;if(stopwatchMin < 0)stopwatchMin = stopwatchMin + 60;showRight();break;
                case 2:gewei = stopwatchMin % 10; gewei--;if(gewei < 0)gewei = 9; stopwatchMin = stopwatchMin - stopwatchMin%10 + gewei;showRight();break;
                case 3:stopwatchSec = stopwatchSec - 10;if(stopwatchSec < 0)stopwatchSec = stopwatchSec + 60;showRight();break;
                case 4:gewei = stopwatchSec % 10; gewei--;if(gewei < 0)gewei = 9; stopwatchSec = stopwatchSec - stopwatchSec%10 + gewei;showRight();break;
                default:break;
                }
            break;
}

