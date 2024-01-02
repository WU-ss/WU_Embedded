//************************************************************
//  Copyright (c)
//	FileName	: SC_Init.h
//	Function	: Contains the MCU initialization function and its H file
//  Instructions        :  
//*************************************************************

/***********************user_code_area*********************/
/*<UserCodeStart>*/
/*<UserCodeEnd>*/
/**********************.user_code_area.********************/


#ifndef _SC_INIT_H_
#define _SC_INIT_H_

#if defined (SC95F8x1x) || defined (SC95F7x1x) || defined (SC95F8x2x)  || defined (SC95F7x2x)  || defined (SC95F8x3x)  || defined (SC95F7x3x) \
 || defined (SC95F8x6x)  || defined (SC95F7x6x)  || defined (SC95F8x1xB)  || defined (SC95F7x1xB)  || defined (SC95R751)  || defined (SC95F7610B)|| defined (SC95F7619B)
#include "sc95f_conf.h"
#else
#include "sc92f_conf.h"
#endif

void SC_Init(void);

void SC_OPTION_Init(void);
void SC_GPIO_Init(void);
void SC_UART0_Init(void);
void SC_TIM0_Init(void);
void SC_TIM1_Init(void);
void SC_TIM2_Init(void);
void SC_TIM3_Init(void);
void SC_TIM4_Init(void);
void SC_PWM_Init(void);
void SC_PWM0_Init(void);
void SC_PWM1_Init(void);
void SC_INT_Init(void);
void SC_ADC_Init(void);
void SC_IAP_Init(void);
void SC_USCI0_Init(void);
void SC_USCI1_Init(void);
void SC_USCI2_Init(void);
void SC_BTM_Init(void);
void SC_CRC_Init(void);
void SC_WDT_Init(void);
void SC_PWR_Init(void);
void SC_DDIC_Init(void);
void SC_MDU_Init(void);
void SC_ACMP_Init(void);
void SC_USCI3_Init(void);
void SC_USCI4_Init(void);
void SC_USCI5_Init(void);
void SC_PWM2_Init(void);
void SC_PWM3_Init(void);
void SC_PWM4_Init(void);

void SC_PGA_Init(void);
void SC_SSI_Init(void);
void SC_SSI0_Init(void);
void SC_SSI1_Init(void);
void SC_CHKSUM_Init(void);
void SC_LPD_Init(void);
#endif

