### ����˵��
�����ӣ�����ܵ�ʱ��  
����Уʱ

### ����˼��
#### ֻ�����������ж�λ  
�����ĸ���Ҫ����������Ӧ�жϵĹ��ܣ�  
    1.**ʱ�ӵ�ʱ�֣����룬���գ�����ʾ�����л�**
    2.��ת����������ҳ  
    3.��ת�����ҳ  
    4.**�޸�ʱ�䡪��ʱ��Ҫ�޸ģ���������ҲҪ�޸�**
�ж��漰ϵͳ�ȶ��ԣ��жϺ���ִ��ʱ�䲻�˹������������жϷŰ������밴����

#### һ������
��Ҫ���״̬λ�����ڰ����������������ͬ�ж�

#### ״̬λ����
    1.��ʱ����ʾ������л���State��  
        0:ʱ��
        1:����
        2:����
        3:��
    2.λѡ
        1
        2
        3
        4
    3.���ֹ���ҳ�Ľ��루funcState��
        1:ʱ��  
        2:����
        3:���
    4.���ӿ��أ�alarmSwitch����bool��δ����������״̬  
    5.����أ�stopwatchSwitch����unsigned char��ֹͣ������(1)������(2)��ֹͣδ����(3)����״̬
    6.�޸�ʱ�俪�أ�changeSwitch����bool���޸�����δ�޸�����״̬

#### ���ʱ�����ݵĴ洢  
    1.ʱ�ӣ�Min��������  
    2.���ӣ�alarmMin������
    3.���ʱ��(ֻ��ʾ���룬stopwatchMin����)
�����������ʾ��������������ʾ�õ�Sec����ʵ��clockSec�������滻
### ������

����TR = 0,ȷ���жϷ������ڵ������ܹ��ȶ���׼ȷ��ִ�У����ұ�֤��ʱ����ʼֵ����ȷ����
```c#
void timer1_ISR(void) interrupt 3
{
    TR1 = 0;
    Display();
    TL1 = 0x18;				//���ö�ʱ��ʼֵ
	TH1 = 0xFC;
    TR1 = 1;
}
```

### ����ai�ĸĽ���֮���ٿ�
#### �������Լ������һЩ�ظ����߼���װ�ɺ������� decrementAdjust �� adjustUnitDigit �������Դ���ߴ���ĸ����ԺͿɶ��ԡ�
```c#
// �Լ���������
void decrementAdjust(int *value, int maxValue, int step) {
    *value = *value - step;
    if (*value < 0) {
        *value = *value + maxValue;
    }
}

// ��λ��������
void adjustUnitDigit(int *value) {
    int gewei = *value % 10;
    gewei--;
    if (gewei < 0) {
        gewei = 9;
    }
    *value = *value - *value % 10 + gewei;
}

// �ⲿ�ж� 2 ������
void EX1_ISR(void) interrupt 2 {  // �Լ�
    switch (funcState) {
        case 1:  // ʱ����
            switch (State) {
                case 0:  // ʱ��
                    switch (wei) {
                        case 1:
                            decrementAdjust((int *)&clockHour, 24, 10);
                            showRight();
                            break;
                        case 2:
                            adjustUnitDigit((int *)&clockHour);
                            showRight();
                            break;
                        case 3:
                            decrementAdjust((int *)&clockMin, 60, 10);
                            showRight();
                            break;
                        case 4:
                            adjustUnitDigit((int *)&clockMin);
                            showRight();
                            break;
                        default:
                            break;
                    }
                    break;
                case 1:  // ����
                    switch (wei) {
                        case 1:
                            decrementAdjust((int *)&clockMin, 60, 10);
                            showRight();
                            break;
                        case 2:
                            adjustUnitDigit((int *)&clockMin);
                            showRight();
                            break;
                        case 3:
                            decrementAdjust((int *)&clockSec, 60, 10);
                            showRight();
                            break;
                        case 4:
                            adjustUnitDigit((int *)&clockSec);
                            showRight();
                            break;
                        default:
                            break;
                    }
                    break;
                case 2:  // ����
                    switch (wei) {
                        case 1:
                            decrementAdjust((int *)&Mon, 12, 10);
                            showRight();
                            break;
                        case 2:
                            adjustUnitDigit((int *)&Mon);
                            showRight();
                            break;
                        case 3:
                            decrementAdjust((int *)&Day, 30, 10);
                            showRight();
                            break;
                        case 4:
                            adjustUnitDigit((int *)&Day);
                            showRight();
                            break;
                        default:
                            break;
                    }
                    break;
                case 3:  // ��
                    switch (wei) {
                        case 1: {
                            int qianwei = Year / 1000;
                            qianwei--;
                            if (qianwei < 0) {
                                qianwei = 9;
                            }
                            Year = Year - (Year / 1000) * 1000 + qianwei * 1000;
                            showRight();
                            break;
                        }
                        case 2: {
                            int baiwei = (Year / 100) % 10;
                            baiwei--;
                            if (baiwei < 0) {
                                baiwei = 9;
                            }
                            Year = Year - ((Year / 100) % 10) * 100 + baiwei * 100;
                            showRight();
                            break;
                        }
                        case 3: {
                            int shiwei = (Year / 10) % 10;
                            shiwei--;
                            if (shiwei < 0) {
                                shiwei = 9;
                            }
                            Year = Year - ((Year / 10) % 10) * 10 + shiwei * 10;
                            showRight();
                            break;
                        }
                        case 4: {
                            int gewei = Year % 10;
                            gewei--;
                            if (gewei < 0) {
                                gewei = 9;
                            }
                            Year = Year - (Year % 10) + gewei;
                            showRight();
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        case 2:  // �����£�ֻ�ܵ���ʱ��
            alarmSwitch = 1;
            switch (wei) {
                case 1:
                    decrementAdjust((int *)&alarmHour, 24, 10);
                    showRight();
                    break;
                case 2:
                    adjustUnitDigit((int *)&alarmHour);
                    showRight();
                    break;
                case 3:
                    decrementAdjust((int *)&alarmMin, 60, 10);
                    showRight();
                    break;
                case 4:
                    adjustUnitDigit((int *)&alarmMin);
                    showRight();
                    break;
                default:
                    break;
            }
            break;
        case 3:  // �����
            stopwatchSwitch = 1;
            switch (wei) {
                case 1:
                    decrementAdjust((int *)&stopwatchMin, 60, 10);
                    showRight();
                    break;
                case 2:
                    adjustUnitDigit((int *)&stopwatchMin);
                    showRight();
                    break;
                case 3:
                    decrementAdjust((int *)&stopwatchSec, 60, 10);
                    showRight();
                    break;
                case 4:
                    adjustUnitDigit((int *)&stopwatchSec);
                    showRight();
                    break;
                default:
                    break;
            }
            break;
    }
}
```