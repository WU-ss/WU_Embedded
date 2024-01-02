//************************************************************
//  Copyright (c) 
//	文件名称:			sc95f_timer0.c
//	作者:					赛元应用团队
//	模块功能:			TIMER0固件库函数C文件
//  最后更正日期:	2022年7月20日
// 	版本: 				V1.10001
//  说明: 
//*************************************************************

#include "sc95f_timer0.h"

/**************************************************
*函数名称:void TIM0_DeInit(void)
*函数功能:TIMER0相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
**************************************************/
void TIM0_DeInit(void)
{
  TMOD &= 0XF0;
  TCON &= 0XCD;
  TMCON &= 0XFE;
  TH0 = 0X00;
  TL0 = 0X00;
  ET0 = 0;
  IPT0 = 0;
}

/**************************************************
*函数名称:void TIM0_TimeBaseInit(TIM0_PresSel_TypeDef TIM0_PrescalerSelection, TIM0_CountMode_TypeDef TIM0_CountMode)
*函数功能:TIMER0基本设置配置函数
*入口参数:
TIM0_PresSel_TypeDef:TIM0_PrescalerSelection:预分频选择
TIM0_CountMode_TypeDef:TIM0_CountMode:计数/定时模式选择
*出口参数:void
**************************************************/
void TIM0_TimeBaseInit(TIM0_PresSel_TypeDef TIM0_PrescalerSelection,
                       TIM0_CountMode_TypeDef TIM0_CountMode)
{
  if (TIM0_PrescalerSelection == TIM0_PRESSEL_FSYS_D12)
  {
    TMCON &= 0XFE;
  }
  else if (TIM0_PrescalerSelection == TIM0_PRESSEL_FSYS_D1)
  {
    TMCON |= 0X01;
  }

  /************************************************************/
  if (TIM0_CountMode == TIM0_MODE_TIMER)
  {
    TMOD &= 0xFB;
  }
  else if (TIM0_CountMode == TIM0_MODE_COUNTER)
  {
    TMOD |= 0x04;
  }
}

/**************************************************
*函数名称:void TIM0_WorkMode0Config(uint16_t TIM0_SetCounter)
*函数功能:TIMER0工作模式0配置函数
*入口参数:
uint16_t:TIM0_SetCounter:配置计数初值
*出口参数:void
**************************************************/
void TIM0_WorkMode0Config(uint16_t TIM0_SetCounter)
{
  TMOD &= 0XFC;
  TL0 = (uint8_t)TIM0_SetCounter;
  TH0 = (TIM0_SetCounter >> 5);
}

/**************************************************
*函数名称:void TIM0_WorkMode1Config(uint16_t TIM0_SetCounter)
*函数功能:TIMER0工作模式1配置函数
*入口参数:
uint16_t:TIM0_SetCounter:配置计数初值
*出口参数:void
**************************************************/
void TIM0_WorkMode1Config(uint16_t TIM0_SetCounter)
{
  TMOD &= 0XFC;
  TMOD |= 0X01;
  TL0 = TIM0_SetCounter % 256;
  TH0 = TIM0_SetCounter / 256;
}

/**************************************************
*函数名称:void TIM0_WorkMode2Config(uint8_t TIM0_SetCounter)
*函数功能:TIMER0工作模式2配置函数
*入口参数:
uint8_t:TIM0_SetCounter:配置计数初值
*出口参数:void
**************************************************/
void TIM0_WorkMode2Config(uint8_t TIM0_SetCounter)
{
  TMOD &= 0XFC;
  TMOD |= 0X02;
  TL0 = TIM0_SetCounter;
  TH0 = TIM0_SetCounter;
}

/**************************************************
*函数名称:void TIM0_WorkModeConfig(TIM0_WorkMode_TypeDef TIM0_WorkMode, uint16_t TIM0_SetCounter1, uint16_t TIM0_SetCounter2)
*函数功能:TIMER0工作模式配置函数
*入口参数:
TIM0_WorkMode:TypeDef TIM0_WorkMode:TIMER0工作模式选择
uint16_t:TIM0_SetCounter1:TIMER0计数初值配置1
uint16_t:TIM0_SetCounter2:TIMER0计数初值配置2
*出口参数:void
**************************************************/
void TIM0_WorkModeConfig(TIM0_WorkMode_TypeDef TIM0_WorkMode, uint16_t TIM0_SetCounter1,
                         uint16_t TIM0_SetCounter2)
{
  switch (TIM0_WorkMode)
  {
  case TIM0_WORK_MODE0:
    TIM0_WorkMode0Config(TIM0_SetCounter1);
    break;

  case TIM0_WORK_MODE1:
    TIM0_WorkMode1Config(TIM0_SetCounter1);
    break;

  case TIM0_WORK_MODE2:
    TIM0_WorkMode2Config(TIM0_SetCounter1);
    break;

  case TIM0_WORK_MODE3:
    TIM0_WorkMode3Config(TIM0_SetCounter1, TIM0_SetCounter2);
    break;

  default:
    break;
  }
}

/**************************************************
*函数名称:void TIM0_WorkMode3Config(uint8_t TIM0_SetCounter, uint8_t TIM1_SetCounter)
*函数功能:TIMER0工作模式3配置函数
*入口参数:
uint8_t:TIM0_SetCounter:配置TIMER0_TL0计数初值
uint8_t:TIM1_SetCounter:配置TIMER0_TH0计数初值
*出口参数:void
**************************************************/
void TIM0_WorkMode3Config(uint8_t TIM0_SetCounter, uint8_t TIM1_SetCounter)
{
  TMOD |= 0X03;
  TL0 = TIM0_SetCounter;
  TH0 = TIM1_SetCounter;
}

/**************************************************
*函数名称:void TIM0_Mode0SetReloadCounter(uint16_t TIM0_SetCounter)
*函数功能:TIMER0工作模式0初值重载函数
*入口参数:
uint16_t:TIM0_SetCounter:配置TIMER0重载值
*出口参数:void
**************************************************/
void TIM0_Mode0SetReloadCounter(uint16_t TIM0_SetCounter)
{
  TL0 = (uint8_t)TIM0_SetCounter;
  TH0 = (TIM0_SetCounter >> 5);
}

/**************************************************
*函数名称:void TIM0_Mode1SetReloadCounter(uint16_t TIM0_SetCounter)
*函数功能:TIMER0工作模式1初值重载函数
*入口参数:
uint16_t:TIM0_SetCounter:配置TIMER0重载值
*出口参数:void
**************************************************/
void TIM0_Mode1SetReloadCounter(uint16_t TIM0_SetCounter)
{
  TL0 = TIM0_SetCounter % 256;
  TH0 = TIM0_SetCounter / 256;
}

/*****************************************************
*函数名称:void TIM0_Cmd(FunctionalState NewState)
*函数功能:TIMER0功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
*****************************************************/
void TIM0_Cmd(FunctionalState NewState)
{
  if (NewState == DISABLE)
  {
    TR0 = 0;
  }
  else
  {
    TR0 = 1;
  }
}

/**************************************************
*函数名称:void TIM0_SetTL0Counter(uint8_t TIM0_SetCounter)
*函数功能:TIMER0 TL0赋值函数
*入口参数:
uint8_t:TIM0_SetCounter:配置TL0
*出口参数:void
**************************************************/
void TIM0_SetTL0Counter(uint8_t TIM0_SetCounter)
{
  TL0 = TIM0_SetCounter;
}

/**************************************************
*函数名称:void TIM0_SetTH0Counter(uint8_t TIM0_SetCounter)
*函数功能:TIMER0 TH0赋值函数
*入口参数:
uint8_t:TIM0_SetCounter:配置TH0
*出口参数:void
**************************************************/
void TIM0_SetTH0Counter(uint8_t TIM0_SetCounter)
{
  TH0 = TIM0_SetCounter;
}

/*****************************************************
*函数名称:void TIM0_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:TIMER0中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
*****************************************************/
void TIM0_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  if (NewState == DISABLE)
  {
    ET0 = 0;
  }
  else
  {
    ET0 = 1;
  }

  /************************************************************/
  if (Priority == LOW)
  {
    IPT0 = 0;
  }
  else
  {
    IPT0 = 1;
  }
}


/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/