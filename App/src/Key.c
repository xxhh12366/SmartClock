/***********************
时间：2025.01.010
内容：三个按键
版本：V1.0
************************/

#include "REG52.H"
#include <intrins.h>
#include "KEY.H"
#include "TIMER.H"

/***********************
名字：S3_Init()
时间：2025.02.20
内容：进入闹钟状态；退出（启动）闹钟状态；
类型：void
************************/
void S3_Init()
{
	if (!S3)//进入闹钟功能
        {
           if(funcState = 2)
            {
                funcState = 0;
                showRight();
            }
            else
            {
                funcState = 2;
                showRight();
            }
        }
}

/***********************
名字：S4_Init()
时间：2025.02.20
内容：进入与退出秒表功能
类型：void
************************/
void S4_Init()
{
	if (!S4)//进入秒表功能
        {
            if(funcState = 3)
            {
                funcState = 0;
                showRight();
            }
            else
            {
                funcState = 3;
                showRight();
            }
        }
}

/***********************
名字：S5_Init()
时间：2025.02.20
内容：进入校时功能，就是可以选择位置
类型：void
************************/
void S5_Init()
{
	if (!S5)//进入校时功能
        {
            if (!changeSwitch)//若不在校时状态
            {
                changeSwitch = 1;
                wei++;
                if (wei > 4)
                {
                    wei = 1;
                }
            }
            else
            {
                changeSwitch = 0;
				wei = 1;
            }
        }
}

/***********************
名字：S8_Init()
时间：2025.02.20
内容：秒表时控制计时开始，停止与清零；
	 闹钟响时退出提醒（alarmRing）;
	 时钟状态下切换时钟显示状态
类型：void
************************/
void S8_Init()
{
	if(!S8)
        {
            switch (funcState)
            {
            case 3://秒表状态下S8开关计时
                switch(stopwatchSwitch)
                {
                    case 1:stopwatchSwitch = 2;showRight();break;
                    case 2:stopwatchSwitch = 3;break;
                    case 3:stopwatchSwitch = 1;stopwatchSec = 0;stopwatchMin = 0;showRight();break;
                    default:break;
                }
                break;
            case 0://在时钟状态下切换时钟页面
                State++;//切换时钟显示状态
                if(State >= 4)
                {
                    State = 0;
                }
                break;
            default:break;
            }
			if(alarmSwitch && alarmRing)
			{
				alarmRing = 0;
			}
        }
}

