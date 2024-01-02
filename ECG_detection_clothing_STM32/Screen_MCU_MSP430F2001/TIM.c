/*
 * TIM.c
 *
 *  Created on: 2022��10��10��
 *      Author: WU
 */

#include <msp430.h>
#include "TIM.h"

void TimerA_Init(void)
{
    TACTL = TASSEL_1+ID_3+MC_2+TACLR; //ѡ��ʱ��ԴΪACLK��8��Ƶ ��f=8192/8=1024Hz������ģʽ��Timer A counter clear
    TACCR0 = 1024;      // ����ʱ�䣬1sһ��
    TACCTL0 |= CCIE;    // TACCR0�ж�ʹ��
}
