/***********************
ʱ�䣺2025.02.20
���ݣ�һЩ��֪����ô����Ķ���
        �����Ӳ���
�汾��V1.1
************************/

#include "Timer.h"

/***********************
���֣�alarm_Init()
ʱ�䣺2025.02.20
���ݣ�����ƥ���뿪��
���ͣ�void
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