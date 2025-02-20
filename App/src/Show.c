/***********************
时间：2025.02.20
内容：与数码管能够显示的时间有关的函数
版本：V1.1
************************/

#include "Timer.h"

void showRight()
{
    switch(funcState)
    {
        case 1://时钟界面下啊
        {   
            showClock2Right();
            switch (state)//判断当前界面
           {
            case 0:showNum0();break;
            case 1:showNum1();break;
            case 2:showNum2();break;
            case 3:showNum3();break;
            default:break;
            }
            break;
        }
        case 2://闹钟界面下
        {
            showAlarm2Right();
            break;
        }
        case 3://秒表界面下
        {
            showStopwatch2Right();
            break;
        }
        default:break;
    }
}

void showClock2Right()
{
    Sec = clockSec;
    Min = clockMin;
    Hour = clockHour;
}

void showAlarm2Right()
{
    Min = alarmMin;
    Hour = alarmHour;
}

void showStopwatch2Right()
{
    Sec = stsec;
    Min = stmin;
}