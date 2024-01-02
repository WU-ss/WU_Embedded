//************************************************************
//  Copyright (c) 
//	文件名称:			sc95f_timer1.h
//	作者:					赛元应用团队
//	模块功能:			TIMER1固件库函数H文件
//  最后更正日期:	2022年7月20日
// 	版本: 				V1.10002
//  说明: 
//*************************************************************

#ifndef _sc95f_TIMER1_H_
#define _sc95f_TIMER1_H_

#include "sc95f.h"

typedef enum
{
  TIM1_PRESSEL_FSYS_D12 = ((uint8_t)0x00), //TIMER1计数源来自系统时钟12分频
  TIM1_PRESSEL_FSYS_D1 = ((uint8_t)0x01)   //TIMER1计数源来自系统时钟
} TIM1_PresSel_TypeDef;

typedef enum
{
  TIM1_MODE_TIMER = ((uint8_t)0x01),  //TIMER1做定时器
  TIM1_MODE_COUNTER = ((uint8_t)0x02) //TIMER1做计数器
} TIM1_CountMode_TypeDef;

typedef enum
{
  TIM1_WORK_MODE0 = ((uint8_t)0x00), //TIMER1选择工作模式0
  TIM1_WORK_MODE1 = ((uint8_t)0x01), //TIMER1选择工作模式1
  TIM1_WORK_MODE2 = ((uint8_t)0x02), //TIMER1选择工作模式2
} TIM1_WorkMode_TypeDef;

/*******************************宏函数*******************************/
/*****************************************************
*函数名称:FlagStatus TIM1_GetFlagStatus(void)
*函数功能:获得TIMER1中断标志状态
*入口参数:void
*出口参数:
FlagStatus:TIMER1中断标志状态
*****************************************************/
#define TIM1_GetFlagStatus() (TF1)

/*****************************************************
*函数名称:void TIM1_ClearFlag(void)
*函数功能:清除TIMER1中断标志状态
*入口参数:void
*出口参数:void
*****************************************************/
#define TIM1_ClearFlag() (TF1 = 0)


void TIM1_DeInit(void);
void TIM1_TimeBaseInit(TIM1_PresSel_TypeDef TIM1_PrescalerSelection,
                       TIM1_CountMode_TypeDef TIM1_CountMode);
void TIM1_WorkMode0Config(uint16_t TIM1_SetCounter);
void TIM1_WorkMode1Config(uint16_t TIM1_SetCounter);
void TIM1_WorkMode2Config(uint8_t TIM1_SetCounter);
void TIM1_Mode0SetReloadCounter(uint16_t TIM1_SetCounter);
void TIM1_Mode1SetReloadCounter(uint16_t TIM1_SetCounter);
void TIM1_Cmd(FunctionalState NewState);
void TIM1_ITConfig(FunctionalState NewState, PriorityStatus Priority);
void TIM1_WorkModeConfig(TIM1_WorkMode_TypeDef TIM1_WorkMode, uint16_t TIM1_SetCounter);

#endif

/******************* (C) COPYRIGHT 2018 SinOne Microelectronics *****END OF FILE****/