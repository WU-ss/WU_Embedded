//Delay.c	
#include "Delay.h"
#include "SC_it.h"

//int16_t ms_cnt = 0;
//uint8_t delay_begin = 0;

void Delay_ms(int16_t ms)
{
	ms_cnt = ms;
	delay_begin = 1;
	while (delay_begin != 0){}
}
