//******* 蜂鸣器驱动占用资源说明 **************************************
//  蜂鸣器可使用IO口直推或PWM驱动
//  使用IO口驱动蜂鸣器时，需占用TIMER1资源
//  使用PWM驱动蜂鸣器时，因各路PWM共用周期，建议PWM只作蜂鸣器用，不作其他用途
//*********************************************************************

#include"..\H\SCDriver_Buzzer_TIM1.h"
#include "SC_Init.h"

#define  SCD_BZ_TIM1_IDLE_LOW		3				//空闲时驱动管脚为低电平
#define  SCD_BZ_TIM1_IDLE_HIGH		4				//空闲时驱动管脚为高电平
#define  SCD_BZ_TIM1_IDLE			SCD_BZ_TIM1_IDLE_HIGH	 //选择SCD_BZ_IDLE_LOW或SCD_BZ_IDLE_HIGH

#define  IO_NULL 		   0xFF00//空设置
#define  SCD_IO_PORT(IO)    (uint8_t)(IO>>8)
#define  SCD_IO_PIN(IO)	    (uint8_t)(IO)

#define  SCD_BZ_TIM1_CLOCK_SOURCE	16000000			//使用IO口驱动，此处填写值与系统时钟
#define  SCD_BZ_TIM1_CLOCK_DIVIDER	TIM1_PRESSEL_FSYS_D12   //分频系数，使用IO口驱动，此处选择TIMER1分频系数（TIM1_PresSel_TypeDef）

FlagStatus SCD_BZ_TIM1_RunFlag = RESET;
unsigned int SCD_BZ_TIM1_HoldTime;
unsigned int SCD_BZ_TIM1_Count = 0;
unsigned int SCD_BZ_TIM1_FREG;
//{
//函数名  #SCD_BZ_TIM1_Init#
//函数功能#该函数用于蜂鸣器驱动的初始化，设定驱动蜂鸣器的频率与时间#
//输入参数#
//			unsigned int BuzzerFreg	     蜂鸣器频率
//			unsigned int BuzzerHoldTime	 蜂鸣器鸣响时间设置，蜂鸣器鸣响时间 = BuzzerHoldTime * SCD_BZ_Scan（）函数调用周期
//		  #
//输出参数#void#
//}
void SCD_BZ_TIM1_Init(unsigned int BuzzerFreg, unsigned int BuzzerHoldTime)
{
	SCD_BZ_TIM1_FREG = SCD_BZ_TIM1_CLOCK_SOURCE/12/2/BuzzerFreg;
	SCD_BZ_TIM1_HoldTime = BuzzerHoldTime;

	GPIO_Init(SCD_IO_PORT(SCD_BZ_TIM1_INIT), SCD_IO_PIN(SCD_BZ_TIM1_INIT), GPIO_MODE_OUT_PP);
	if(SCD_BZ_TIM1_IDLE == SCD_BZ_TIM1_IDLE_LOW)
	{
		GPIO_WriteLow(SCD_IO_PORT(SCD_BZ_TIM1_INIT), SCD_IO_PIN(SCD_BZ_TIM1_INIT));	
	}
	else
	{
		GPIO_WriteHigh(SCD_IO_PORT(SCD_BZ_TIM1_INIT), SCD_IO_PIN(SCD_BZ_TIM1_INIT));
	}

	TIM1_TimeBaseInit(SCD_BZ_TIM1_CLOCK_DIVIDER, TIM1_MODE_TIMER);
	TIM1_WorkMode1Config(65536 - SCD_BZ_TIM1_FREG);

	TIM1_Cmd(ENABLE);
	TIM1_ITConfig(ENABLE, HIGH);
	enableInterrupts();	
	
}
//{
//函数名  #SCD_BZ_TIM1_Scan#
//函数功能#用于IO方波生成，当使用IO驱动蜂鸣器时，需在TIMER1中断中调用该函数#
//输入参数#void#
//输出参数#void#
//}
void SCD_BZ_TIM1_Scan(void)
{										
	TIM1_Mode1SetReloadCounter(65536 - SCD_BZ_TIM1_FREG);	
	//SCD_BZ_TIM1_Scan(); //更新蜂鸣器计数器
	/*****************************************/
	if(SCD_BZ_TIM1_RunFlag == SET)					
	{													
		SCD_BZ_TIM1_Count++;
								
		if(SCD_BZ_TIM1_Count >= SCD_BZ_TIM1_HoldTime)
		{
			if(SCD_BZ_TIM1_IDLE == SCD_BZ_TIM1_IDLE_LOW)
			{
				GPIO_WriteLow(SCD_IO_PORT(SCD_BZ_TIM1_INIT), SCD_IO_PIN(SCD_BZ_TIM1_INIT));	
			}
			else
			{
				GPIO_WriteHigh(SCD_IO_PORT(SCD_BZ_TIM1_INIT), SCD_IO_PIN(SCD_BZ_TIM1_INIT));
			}
			SCD_BZ_TIM1_Count = 0;
			SCD_BZ_TIM1_RunFlag = RESET;
		}	
	}	
	/*****************************************/

	if(SCD_BZ_TIM1_RunFlag == SET)					
	{
		SCD_BZ_TIM1 = ~SCD_BZ_TIM1;												
					
	}
}
//{
//函数名  #SCD_BZ_TIM1_Run#
//函数功能#该函数用于启动蜂鸣器，调用后蜂鸣器鸣响一段时间#
//输入参数#void#
//输出参数#void#
//}
void SCD_BZ_TIM1_Run(void)
{
	SCD_BZ_TIM1_RunFlag = SET;	
}