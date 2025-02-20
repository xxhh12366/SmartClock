/***********************
ʱ�䣺2025.01.010
���ݣ���������
�汾��V1.0
************************/

#include "REG52.H"
#include <intrins.h>
#include "KEY.H"
#include "TIMER.H"

/***********************
���֣�S3_Init()
ʱ�䣺2025.02.20
���ݣ���������״̬���˳�������������״̬��
���ͣ�void
************************/
void S3_Init()
{
	if (!S3)//�������ӹ���
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
���֣�S4_Init()
ʱ�䣺2025.02.20
���ݣ��������˳������
���ͣ�void
************************/
void S4_Init()
{
	if (!S4)//���������
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
���֣�S5_Init()
ʱ�䣺2025.02.20
���ݣ�����Уʱ���ܣ����ǿ���ѡ��λ��
���ͣ�void
************************/
void S5_Init()
{
	if (!S5)//����Уʱ����
        {
            if (!changeSwitch)//������Уʱ״̬
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
���֣�S8_Init()
ʱ�䣺2025.02.20
���ݣ����ʱ���Ƽ�ʱ��ʼ��ֹͣ�����㣻
	 ������ʱ�˳����ѣ�alarmRing��;
	 ʱ��״̬���л�ʱ����ʾ״̬
���ͣ�void
************************/
void S8_Init()
{
	if(!S8)
        {
            switch (funcState)
            {
            case 3://���״̬��S8���ؼ�ʱ
                switch(stopwatchSwitch)
                {
                    case 1:stopwatchSwitch = 2;showRight();break;
                    case 2:stopwatchSwitch = 3;break;
                    case 3:stopwatchSwitch = 1;stopwatchSec = 0;stopwatchMin = 0;showRight();break;
                    default:break;
                }
                break;
            case 0://��ʱ��״̬���л�ʱ��ҳ��
                State++;//�л�ʱ����ʾ״̬
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

