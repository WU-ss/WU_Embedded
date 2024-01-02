//************************************************************
//  Copyright (c) 
//	文件名称:			sc95f_timer1.c
//	作者:					赛元应用团队
//	模块功能:			TIMER1固件库函数C文件
//  最后更正日期:	2022年7月20日
// 	版本: 				V1.10001
//  说明: 
//*************************************************************

#include "sc95f_timer1.h"

/**************************************************
*函数名称:void TIM1_DeInit(void)
*函数功能:TIMER1相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
**************************************************/
void TIM1_DeInit(void)
{
  TMOD &= 0X0F;
  TCON &= 0X37;
  TMCON &= 0XFD;
  TH1 = 0X00;
  TL1 = 0X00;
  ET1 = 0;
  IPT1 = 0;
}

/**************************************************
*函数名称:void TIM1_TimeBaseInit(TIM1_PresSel_TypeDef TIM1_PrescalerSelection, TIM1_CountMode_TypeDef TIM1_CountMode)
*函数功能:TIMER1基本设置配置函数
*入口参数:
TIM1_PresSel_TypeDef:TIM1_PrescalerSelection:预分频选择
TIM1_CountMode_TypeDef:TIM1_CountMode:计数/定时模式选择
*出口参数:void
**************************************************/
void TIM1_TimeBaseInit(TIM1_PresSel_TypeDef TIM1_PrescalerSelection,
                       TIM1_CountMode_TypeDef TIM1_CountMode)
{
  if(TIM1_PrescalerSelection == TIM1_PRESSEL_FSYS_D12)
  {
    TMCON &= 0xFD;
  }
  else if(TIM1_PrescalerSelection == TIM1_PRESSEL_FSYS_D1)
  {
    TMCON |= 0x02;
  }

  /************************************************************/
  if(TIM1_CountMode == TIM1_MODE_TIMER)
  {
    TMOD &= 0xBF;
  }
  else if(TIM1_CountMode == TIM1_MODE_COUNTER)
  {
    TMOD |= 0x40;
  }
}

/**************************************************
*函数名称:void TIM1_WorkMode0Config(uint16_t TIM1_SetCounter)
*函数功能:TIMER1工作模式0配置函数
*入口参数:
uint16_t:TIM1_SetCounter:配置计数初值
*出口参数:void
**************************************************/
void TIM1_WorkMode0Config(uint16_t TIM1_SetCounter)
{
  TMOD &= 0XCF;
  TL1 = (uint8_t)TIM1_SetCounter;
  TH1 = (TIM1_SetCounter >> 5);
}

/**************************************************
*函数名称:void TIM1_WorkMode1Config(uint16_t TIM1_SetCounter)
*函数功能:TIMER1工作模式1配置函数
*入口参数:
uint16_t:TIM1_SetCounter:配置计数初值
*出口参数:void
**************************************************/
void TIM1_WorkMode1Config(uint16_t TIM1_SetCounter)
{
  TMOD &= 0XCF;
  TMOD |= 0X10;
  TL1 = TIM1_SetCounter % 256;
  TH1 = TIM1_SetCounter / 256;
}

/**************************************************
*函数名称:void TIM1_WorkMode2Config(uint8_t TIM1_SetCounter)
*函数功能:TIMER1工作模式2配置函数
*入口参数:
uint8_t:TIM1_SetCounter:配置计数初值
*出口参数:void
**************************************************/
void TIM1_WorkMode2Config(uint8_t TIM1_SetCounter)
{
  TMOD &= 0XCF;
  TMOD |= 0X20;
  TL1 = TIM1_SetCounter;
  TH1 = TIM1_SetCounter;
}

/**************************************************
*函数名称:void TIM1_WorkModeConfig(TIM1_WorkMode_TypeDef TIM1_WorkMode, uint16_t TIM1_SetCounter)
*函数功能:TIMER1工作模式配置函数
*入口参数:
TIM1_WorkMode_TypeDef:TIM1_WorkMode:TIMER1工作模式选择
uint16_t:TIM1_SetCounter:TIMER1计数初值配置
*出口参数:void
**************************************************/
void TIM1_WorkModeConfig(TIM1_WorkMode_TypeDef TIM1_WorkMode, uint16_t TIM1_SetCounter)
{
  switch(TIM1_WorkMode)
  {
    case TIM1_WORK_MODE0:
      TIM1_WorkMode0Config(TIM1_SetCounter);
      break;

    case TIM1_WORK_MODE1:
      TIM1_WorkMode1Config(TIM1_SetCounter);
      break;

    case TIM1_WORK_MODE2:
      TIM1_WorkMode2Config(TIM1_SetCounter);
      break;

    default:
      break;
  }
}

/**************************************************
*函数名称:void TIM1_Mode0SetReloadCounter(uint16_t TIM1_SetCounter)
*函数功能:TIMER1工作模式0初值重载函数
*入口参数:
uint16_t:TIM1_SetCounter:配置TIMER1重载值
*出口参数:void
**************************************************/
void TIM1_Mode0SetReloadCounter(uint16_t TIM1_SetCounter)
{
  TL1 = (uint8_t)TIM1_SetCounter;
  TH1 = (TIM1_SetCounter >> 5);
}

/**************************************************
*函数名称:void TIM1_Mode1SetReloadCounter(uint16_t TIM1_SetCounter)
*函数功能:TIMER1工作模式1初值重载函数
*入口参数:
uint16_t:TIM1_SetCounter:配置TIMER1重载值
*出口参数:void
**************************************************/
void TIM1_Mode1SetReloadCounter(uint16_t TIM1_SetCounter)
{
  TL1 = TIM1_SetCounter % 256;
  TH1 = TIM1_SetCounter / 256;
}

/*****************************************************
*函数名称:void TIM1_Cmd(FunctionalState NewState)
*函数功能:TIMER1功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
*****************************************************/
void TIM1_Cmd(FunctionalState NewState)
{
  if(NewState == DISABLE)
  {
    TR1 = 0;
  }
  else
  {
    TR1 = 1;
  }
}

/*****************************************************
*函数名称:void TIM1_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:TIMER1中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
*****************************************************/
void TIM1_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  if(NewState == DISABLE)
  {
    ET1 = 0;
  }
  else
  {
    ET1 = 1;
  }

  /************************************************************/
  if(Priority == LOW)
  {
    IPT1 = 0;
  }
  else
  {
    IPT1 = 1;
  }
}


/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/