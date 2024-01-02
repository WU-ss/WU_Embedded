/*
 * Delay.c
 *
 *  Created on: 2022Äê10ÔÂ10ÈÕ
 *      Author: WU
 */

#include "Delay.h"

void delay_ms(int delaytime)          // 1ms
{
  int i,j;

    for(i=0; i<delaytime; i++)
        for(j=0; j<200; j++);
}

void delay_20ms(int delaytime)          // 20ms
{
  int i,j;

    for(i=0; i<delaytime; i++)
        for(j=0; j<4000; j++);
}

void delay_s(int delaytime)           // 1s
{
    int i,j,k;

    for(i=0; i<delaytime; i++)
        for(j=0; j<1000; j++)
            for(k=0; k<200; k++);
}
