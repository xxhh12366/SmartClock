### 功能说明
有闹钟，秒表功能的时钟  
可以校时

### 代码思考
#### 只有两个按键中断位  
而有四个需要发生按键响应中断的功能：  
    1.**时钟的时分，分秒，月日，年显示界面切换**
    2.跳转到闹钟设置页  
    3.跳转到秒表页  
    4.**修改时间——时钟要修改，闹钟设置也要修改**
中断涉及系统稳定性，中断函数执行时间不宜过长，于是在中断放按键增与按键减

#### 一键多义
需要结合状态位，对于按键按下情况做出不同判断

#### 状态位创建
    1.在时钟显示界面的切换（State）  
        0:时分
        1:分秒
        2:月日
        3:年
    2.位选
        1
        2
        3
        4
    3.各种功能页的进入（funcState）
        1:时钟  
        2:闹钟
        3:秒表
    4.闹钟开关（alarmSwitch），bool，未响与响两种状态  
    5.秒表开关（stopwatchSwitch），unsigned char，停止已清零(1)，开启(2)，停止未清零(3)三种状态
    6.修改时间开关（changeSwitch），bool，修改中与未修改两种状态

#### 多个时间数据的存储  
    1.时钟（Min，，，）  
    2.闹钟（alarmMin，，）
    3.秒表时间(只显示分秒，stopwatchMin，，)
由于数码管显示函数，则设立显示用的Sec与真实的clockSec，方便替换
### 代码解读

调用TR = 0,确保中断服务函数内的任务能够稳定、准确地执行，并且保证定时器初始值的正确设置
```c#
void timer1_ISR(void) interrupt 3
{
    TR1 = 0;
    Display();
    TL1 = 0x18;				//设置定时初始值
	TH1 = 0xFC;
    TR1 = 1;
}
```

### 来自ai的改进，之后再看
#### 在自增自减那里。把一些重复的逻辑封装成函数，像 decrementAdjust 和 adjustUnitDigit 函数，以此提高代码的复用性和可读性。
```c#
// 自减调整函数
void decrementAdjust(int *value, int maxValue, int step) {
    *value = *value - step;
    if (*value < 0) {
        *value = *value + maxValue;
    }
}

// 个位调整函数
void adjustUnitDigit(int *value) {
    int gewei = *value % 10;
    gewei--;
    if (gewei < 0) {
        gewei = 9;
    }
    *value = *value - *value % 10 + gewei;
}

// 外部中断 2 服务函数
void EX1_ISR(void) interrupt 2 {  // 自减
    switch (funcState) {
        case 1:  // 时钟下
            switch (State) {
                case 0:  // 时分
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
                case 1:  // 分秒
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
                case 2:  // 月日
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
                case 3:  // 年
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
        case 2:  // 闹钟下，只能调整时分
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
        case 3:  // 秒表下
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