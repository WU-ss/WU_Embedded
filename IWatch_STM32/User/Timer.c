#include "stm32f10x.h"                  // Device header
#include "blood.h"
#include "RTC.h" 
#include "mpu_user_api.h"
#include "AT.h"

unsigned long  STEPS;
extern BloodData g_blooddata;
extern const char* pubtopic;	//配置参数，发布消息

void mpu_Loop(void)
{
mpu_set_dmp_state(1);
dmp_get_pedometer_step_count(&STEPS);
}

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 5000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		blood_Loop();
		
		RTC_Get();
		OLED_Printf_EN(1,0,"%d:%d",calendar.hour,calendar.min);
		
		mpu_Loop();
		OLED_Printf_EN(1,70,"step:%d",STEPS);
		
		printf("AT+MQTTPUB=0,\"%s\",\"{\\\"method\\\":\\\"thing.event.property.post\\\"\\,\\\"params\\\":{\\\"%s\\\":%d\\,\\\"%s\\\":%f\\,\\\"%s\\\":%d\\}}\",0,0\r\n",pubtopic,"totalStep",(int)STEPS,"SpO2",g_blooddata.SpO2,"heartRate",g_blooddata.heart);

		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
