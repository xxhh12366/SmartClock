/***********************
ʱ�䣺2025.02.20
���ݣ���������ܹ���ʾ��ʱ���йصĺ���
�汾��V1.1
************************/

#include "Timer.h"

void showRight()
{
    switch(funcState)
    {
        case 1://ʱ�ӽ����°�
        {   
            showClock2Right();
            switch (state)//�жϵ�ǰ����
           {
            case 0:showNum0();break;
            case 1:showNum1();break;
            case 2:showNum2();break;
            case 3:showNum3();break;
            default:break;
            }
            break;
        }
        case 2://���ӽ�����
        {
            showAlarm2Right();
            break;
        }
        case 3://��������
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