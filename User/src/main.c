#include "REG52.H"
#include "intrins.h"
#include "led.h"
#include "key.h"
#include "timer.h"
#include "show.h"
#include "service.h"

void main()
{
    Timer0_Init();
    Timer1_Init();
    EX0_Init();
    EX1_Init();
    LED_Init()
    while(1)
    {
        S3_Init();
        S4_Init();
        S5_Init();
        S8_Init();
        alarm_Init();
    }
            
