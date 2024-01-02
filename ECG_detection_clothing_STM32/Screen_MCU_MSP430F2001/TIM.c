/*
 * TIM.c
 *
 *  Created on: 2022年10月10日
 *      Author: WU
 */

#include <msp430.h>
#include "TIM.h"

void TimerA_Init(void)
{
    TACTL = TASSEL_1+ID_3+MC_2+TACLR; //选择时钟源为ACLK，8分频 即f=8192/8=1024Hz，连续模式，Timer A counter clear
    TACCR0 = 1024;      // 驱动时间，1s一次
    TACCTL0 |= CCIE;    // TACCR0中断使能
}
