/***********************
时间：2025.02.20
内容：一些不知道怎么归类的东西
        对闹钟操作
版本：V1.1
************************/

#include "Timer.h"

/***********************
名字：alarm_Init()
时间：2025.02.20
内容：闹钟匹配与开启
类型：void
************************/
void alarm_Init()
{
    if(alarmMin == 0 && alarmHour == 0)
    {
        alarmSwitch = 1;
        if(clockHour == alarmHour && clockMin == alarmMin)
        {
            alarmRing = 1;
        }
    }
    else
    {
        alarmSwitch = 0;
    }

}