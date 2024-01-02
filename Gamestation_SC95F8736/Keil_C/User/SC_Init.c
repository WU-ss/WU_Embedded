//************************************************************
//  Copyright (c)   
//	FileName	   : SC_Init.c
//	Function	   : Contains the MCU initialization function and its C file
//  Instructions   : 
//*************************************************************

#include "SC_Init.h"	// MCU initialization header file, including all firmware library header files
#include "..\Drivers\SCDriver_list.h"
#include "HeadFiles\SC_itExtern.h"


/***********************user_code_area*********************/
/*<UserCodeStart>*/
/*<UserCodeEnd>*/
/**********************.user_code_area.********************/

/*****************************************************
*函数名称: SC_Init
*函数功能: MCU初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_Init(void)
{
	SC_GPIO_Init();
	SC_OPTION_Init();
	SC_USCI0_Init();
	SC_USCI2_Init();
	SC_USCI3_Init();
	SC_UART0_Init();
	SC_TIM0_Init();
	SC_TIM2_Init();
	SC_TIM3_Init();
	SC_TIM4_Init();
	SC_PWM0_Init();
	/*write initial function here*/	
	EA = 1;	
}

/*****************************************************
*函数名称: SC_OPTION_Init
*函数功能: OPTION配置初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_OPTION_Init(void)
{
	SC95F8736_NIO_Init();
	/*OPTION_Init write here*/		
}

/*****************************************************
*函数名称: SC_GPIO_Init
*函数功能: GPIO初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_GPIO_Init(void)
{
	GPIO_Init(GPIO0, GPIO_PIN_2,GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO0, GPIO_PIN_3,GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO5, GPIO_PIN_1,GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO3, GPIO_PIN_6,GPIO_MODE_IN_PU);
	GPIO_Init(GPIO1, GPIO_PIN_4,GPIO_MODE_IN_PU);
	GPIO_Init(GPIO1, GPIO_PIN_5,GPIO_MODE_IN_PU);
	GPIO_Init(GPIO1, GPIO_PIN_6,GPIO_MODE_IN_PU);
	GPIO_Init(GPIO1, GPIO_PIN_7,GPIO_MODE_IN_PU);
	GPIO_Init(GPIO2, GPIO_PIN_2,GPIO_MODE_IN_PU);
	GPIO_Init(GPIO2, GPIO_PIN_3,GPIO_MODE_IN_PU);
	GPIO_Init(GPIO0, GPIO_PIN_0,GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO0, GPIO_PIN_1,GPIO_MODE_OUT_PP);
	/*GPIO_Init write here*/		
}

/*****************************************************
*函数名称: SC_UART0_Init
*函数功能: UART0初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_UART0_Init(void)
{
	GPIO_Init(GPIO2, GPIO_PIN_0,GPIO_MODE_IN_PU);
	GPIO_Init(GPIO2, GPIO_PIN_1,GPIO_MODE_IN_PU);
	/*模式1初始化*/UART0_Init(32000000,115200,UART0_Mode_10B,UART0_CLOCK_TIMER1,UART0_RX_ENABLE);
	UART0_ITConfig(ENABLE,LOW);
	/*UART0_Init write here*/		
}

/*****************************************************
*函数名称: SC_TIM0_Init
*函数功能: TIMER0初始化函数
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_TIM0_Init(void)
{
	TIM0_TimeBaseInit(TIM0_PRESSEL_FSYS_D1,TIM0_MODE_TIMER);
	TIM0_WorkModeConfig(TIM0_WORK_MODE1,33536, 0);
	TIM0_ITConfig(ENABLE,LOW);
	TIM0_Cmd(ENABLE);
	/*TIM0_Init write here*/		
}

/*****************************************************
*函数名称: SC_TIM1_Init
*函数功能: TIMER1初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_TIM1_Init(void)
{
	/*TIM1_Init write here*/	
}

/*****************************************************
*函数名称: SC_TIM2_Init
*函数功能: TIMER2初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_TIM2_Init(void)
{
	TIM2_TimeBaseInit(TIM2_MODE_TIMER,TIM2_COUNTDIRECTION_UP);
	TIM2_WorkMode1Config(33536);
	TIM2_PrescalerSelection(TIM2_PRESSEL_FSYS_D1);
	TIM2_ITConfig(ENABLE,LOW);
	TIM2_Cmd(ENABLE);
	/*TIM2_Init write here*/	
}

/*****************************************************
*函数名称: SC_TIM3_Init
*函数功能: TIMER3初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_TIM3_Init(void)
{
	TIM3_TimeBaseInit(TIM3_MODE_TIMER,TIM3_COUNTDIRECTION_UP);
	TIM3_WorkMode1Config(33536);
	TIM3_PrescalerSelection(TIM3_PRESSEL_FSYS_D1);
	TIM3_ITConfig(ENABLE,LOW);
	TIM3_Cmd(ENABLE);
	/*TIM3_Init write here*/	
}

/*****************************************************
*函数名称: SC_TIM4_Init
*函数功能: TIMER4初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_TIM4_Init(void)
{
	TIM4_TimeBaseInit(TIM4_MODE_TIMER,TIM4_COUNTDIRECTION_UP);
	TIM4_WorkMode1Config(38869);
	TIM4_PrescalerSelection(TIM4_PRESSEL_FSYS_D12);
	TIM4_ITConfig(ENABLE,HIGH);
	TIM4_Cmd(ENABLE);
	/*TIM4_Init write here*/	
}

/*****************************************************
*函数名称: SC_PWM_Init
*函数功能: PWM初始化函数
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_PWM_Init(void)
{
	/*PWM_Init write here*/	
}

/*****************************************************
*函数名称: SC_PWM0_Init
*函数功能: PWM0初始化函数
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_PWM0_Init(void)
{
	/*PWM0独立模式*/PWM_Init(PWM0_PRESSEL_FHRC_D4,1000);
	/*PWM03 独立模式*/PWM_IndependentModeConfigEX(PWM03,0, PWM_OUTPUTSTATE_ENABLE);
	/*PWM0*/PWM_Aligned_Mode_Select(PWM0_Edge_Aligned_Mode);
	/*PWM0*/PWM_FaultDetectionConfigEX(PWM0_Type,DISABLE);
	/*PWM0*/PWM_FaultDetectionModeConfigEX(PWM0_Type,PWM0_Immediate_Mode,PWM0_FaultDetectionVoltage_Low,PWM0_WaveFilteringTime_0us);
	/*PWM0中断使能*/PWM_ITConfigEX(PWM0_Type,DISABLE,LOW);
	/*PWM0开关*/PWM_CmdEX(PWM0_Type,ENABLE);
	/*PWM0_Init write here*/	
}

/*****************************************************
*函数名称: SC_PWM1_Init
*函数功能: PWM1初始化函数
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_PWM1_Init(void)
{
	/*PWM1_Init write here*/	
}

/*****************************************************
*函数名称: SC_PWM2_Init
*函数功能: PWM1初始化函数
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_PWM2_Init(void)
{
	/*PWM2_Init write here*/	
}

/*****************************************************
*函数名称: SC_PWM3_Init
*函数功能: PWM1初始化函数
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_PWM3_Init(void)
{
	/*PWM3_Init write here*/	
}

/*****************************************************
*函数名称: SC_PWM4_Init
*函数功能: PWM1初始化函数
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_PWM4_Init(void)
{
	/*PWM4_Init write here*/	
}
/*****************************************************
*函数名称: SC_INT_Init
*函数功能: INT初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_INT_Init(void)
{
	/*INT_Init write here*/	
}

/*****************************************************
*函数名称: SC_ADC_Init
*函数功能: ADC初始化函数
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_ADC_Init(void)
{
	/*ADC_Init write here*/
}

/*****************************************************
*函数名称: SC_PGA_Init
*函数功能: PGA初始化函数
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_PGA_Init(void)
{
	/*PGA_Init write here*/
}

/*****************************************************
*函数名称: SC_IAP_Init
*函数功能: IAP初始化函数
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_IAP_Init(void)
{
	/*IAP_Init write here*/		
}

/*****************************************************
*函数名称: SC_USCI0_Init
*函数功能: USCI0初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_USCI0_Init(void)
{
	GPIO_Init(GPIO0, GPIO_PIN_5,GPIO_MODE_IN_PU);
	GPIO_Init(GPIO0, GPIO_PIN_6,GPIO_MODE_IN_PU);
	USCI0_SPI_Init(USCI0_SPI_FIRSTBIT_MSB,USCI0_SPI_BAUDRATEPRESCALER_1,USCI0_SPI_MODE_MASTER,USCI0_SPI_CLOCKPOLARITY_LOW,USCI0_SPI_CLOCKPHASE_1EDGE,USCI0_SPI_TXE_DISINT,USCI0_SPI_DATA8);
	USCI0_ITConfig(ENABLE,LOW);
	USCI0_SPI_Cmd(ENABLE);
	/*USCI0_Init write here*/		
}

/*****************************************************
*函数名称: SC_USCI1_Init
*函数功能: USCI1初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_USCI1_Init(void)
{
	/*USCI1_Init write here*/		
}

/*****************************************************
*函数名称: SC_USCI2_Init
*函数功能: USCI2初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_USCI2_Init(void)
{
	GPIO_Init(GPIO4, GPIO_PIN_5,GPIO_MODE_IN_PU);
	GPIO_Init(GPIO4, GPIO_PIN_4,GPIO_MODE_IN_PU);
	USCI2_ITConfig(ENABLE,LOW);
	USCI2_UART_Init(32000000,  USCI2_UART_BaudRate_FsysDIV12,  USCI2_UART_Mode_8B,USCI2_UART_RX_ENABLE);
	/*USCI2_Init write here*/		
}

/*****************************************************
*函数名称: SC_USCI3_Init
*函数功能: USCI3初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_USCI3_Init(void)
{
	GPIO_Init(GPIO2, GPIO_PIN_6,GPIO_MODE_IN_PU);
	USCI3_TWI_GeneralCallCmd(DISABLE);
	USCI3_TWI_AcknowledgeConfig(ENABLE);
	USCI3_ITConfig(ENABLE,LOW);
	USCI3_TWI_MasterCommunicationRate(USCI3_TWI_1024);
	USCI3_TWI_SlaveClockExtension(DISABLE);
	USCI3_TWI_Slave_Init(0x00);
	USCI3_TWI_Cmd(ENABLE);
	/*USCI3_Init write here*/		
}

/*****************************************************
*函数名称: SC_USCI4_Init
*函数功能: USCI4初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_USCI4_Init(void)
{
	/*USCI4_Init write here*/		
}

/*****************************************************
*函数名称: SC_USCI5_Init
*函数功能: USCI5初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_USCI5_Init(void)
{
	/*USCI5_Init write here*/		
}

/*****************************************************
*函数名称: SC_SSI_Init
*函数功能: SSI初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_SSI_Init(void)
{
	/*SSI_Init write here*/		
}

/*****************************************************
*函数名称: SC_SSI0_Init
*函数功能: SSI初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_SSI0_Init(void)
{
	/*SSI0_Init write here*/		
}

/*****************************************************
*函数名称: SC_SSI1_Init
*函数功能: SSI初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_SSI1_Init(void)
{
	/*SSI1_Init write here*/		
}

/*****************************************************
*函数名称: SC_BTM_Init
*函数功能: 低频时钟定时器初始化函数
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_BTM_Init(void)
{
	/*BTM_Init write here*/		
}

/*****************************************************
*函数名称: SC_CRC_Init
*函数功能: check sum 初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_CRC_Init(void)
{
	/*CRC_Init write here*/	
}

/*****************************************************
*函数名称: SC_CHKSUM_Init
*函数功能: check sum 初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_CHKSUM_Init(void)
{
	/*CHKSUM_Init write here*/	
}

/*****************************************************
*函数名称: SC_WDT_Init
*函数功能: 看门狗初始化函数
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_WDT_Init(void)
{
	/*WDT_Init write here*/		
}

/*****************************************************
*函数名称: SC_PWR_Init
*函数功能: 电源/功耗控制初始化函数
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_PWR_Init(void)
{
	/*PWR_Init write here*/		
}
/*****************************************************
*函数名称: SC_DDIC_Init
*函数功能: 显示控制初始化函数
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_DDIC_Init(void)
{
	/*DDIC_Init write here*/	
}

/*****************************************************
*函数名称: SC_ACMP_Init
*函数功能: 运放初始化函数
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_ACMP_Init(void)
{
	/*ACMP_Init write here*/	
}

/*****************************************************
*函数名称: SC_MDU_Init
*函数功能: 乘除法器初始化函数
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_MDU_Init(void)
{
	/*MDU_Init write here*/	
}

/*****************************************************
*函数名称: SC_LPD_Init
*函数功能: LPD初始化函数
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_LPD_Init(void)
{
	/*LPD_Init write here*/
}
