#ifndef __TIME_H
#define __TIME_H

#include "stm32f10x.h"

#define read0 GPIO_ResetBits(GPIOA, GPIO_Pin_6)
#define read1 GPIO_SetBits(GPIOA, GPIO_Pin_6)
#define Read_Data GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)

void DHT11_GPIO_Init_IN(void);
void DHT11_GPIO_Init_OUT(void);
void DHT11_RST(void);
unsigned char DHT11_Rec_Byte(void);
void DH11_REC_Data(void);


#endif
