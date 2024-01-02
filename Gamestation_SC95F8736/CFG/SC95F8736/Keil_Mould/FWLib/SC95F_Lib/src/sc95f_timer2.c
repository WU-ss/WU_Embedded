//************************************************************
//  Copyright (c) 
//	文件名称:			sc95f_timer2.c
//	作者:					赛元应用团队
//	模块功能:			TIMER2固件库函数C文件
//  最后更正日期:	2022年7月20日
// 	版本: 				V1.10000
//  说明: 
//*************************************************************

#include "sc95f_timer2.h"

/**************************************************
*函数名称:void TIM2_DeInit(void)
*函数功能:TIMER2相关寄存器复位至初始值
*入口参数:void
*出口参数:void
**************************************************/
void TIM2_DeInit()
{
  TXINX = 0x02; //TIMER2选择
  TXCON = 0X00;
  TXMOD = 0X00;
  RCAPXH = 0X00;
  RCAPXL = 0X00;
  THX = 0X00;
  TLX = 0X00;
  IE1 &= 0X3F;
  IP1 &= 0X3F;
  ET2 = 0;
  IPT2 = 0;
}

/**************************************************
*函数名称:void TIM2_PrescalerSelection(TIM2_PresSel_TypeDef TIM2_PrescalerSelection)
*函数功能:TIMER2 预分频选择
*入口参数:
TIM2_PresSel_TypeDef:TIM2_PrescalerSelection:预分频选择
*出口参数:void
**************************************************/
void TIM2_PrescalerSelection(TIM2_PresSel_TypeDef TIM2_PrescalerSelection)
{
  TXINX = 0x02;

  if (TIM2_PrescalerSelection == TIM2_PRESSEL_FSYS_D12)
  {
    TXMOD &= 0X7F;
  }
  else if (TIM2_PrescalerSelection == TIM2_PRESSEL_FSYS_D1)
  {
    TXMOD |= 0X80;
  }
}

/**************************************************
*函数名称:void TIM2_TimeBaseInit(TIM2_CountMode_TypeDef TIM2_CountMode, TIM2_CountDirection_TypeDef TIM2_CountDirection)
*函数功能:TIM2基本设置配置函数
*入口参数:
TIM2_CountMode_TypeDef:TIM2_CountMode:计数/定时模式选择
TIM2_CountDirection_TypeDef:TIM2_CountDirection:计数方向选择
*出口参数:void
**************************************************/
void TIM2_TimeBaseInit(TIM2_CountMode_TypeDef TIM2_CountMode,
                       TIM2_CountDirection_TypeDef TIM2_CountDirection)
{
  TXINX = 0x02;

  if (TIM2_CountMode == TIM2_MODE_TIMER)
  {
    TXCON &= 0XFD;
  }
  else if (TIM2_CountMode == TIM2_MODE_COUNTER)
  {
    TXCON |= 0X02;
  }
  if (TIM2_CountDirection == TIM2_COUNTDIRECTION_UP)
  {
    TXMOD &= 0XFE;
  }
  else if (TIM2_CountDirection == TIM2_COUNTDIRECTION_DOWN_UP)
  {
    TXMOD |= 0X01;
  }
}

/**************************************************
*函数名称:void TIM2_WorkMode0Config(uint16_t TIM2_SetCounter)
*函数功能:TIMER2工作模式0配置函数
*入口参数:
uint16_t:TIM2_SetCounter:配置计数初值
*出口参数:void
**************************************************/
void TIM2_WorkMode0Config(uint16_t TIM2_SetCounter)
{
  TXINX = 0x02;
  CP = 1;
  TLX = TIM2_SetCounter % 256;
  THX = TIM2_SetCounter / 256;
}

/**************************************************
*函数名称:void TIM2_WorkMode1Config(uint16_t TIM2_SetCounter)
*函数功能:TIMER2工作模式1配置函数
*入口参数:
uint16_t:TIM2_SetCounter:配置计数初值
*出口参数:void
**************************************************/
void TIM2_WorkMode1Config(uint16_t TIM2_SetCounter)
{
  TXINX = 0x02;
  RCAPXL = TIM2_SetCounter % 256;
  RCAPXH = TIM2_SetCounter / 256;

  TLX = RCAPXL;
  THX = RCAPXH;
}

/**************************************************
*函数名称:void TIM2_WorkMode3Config(uint16_t TIM2_SetCounter)
*函数功能:TIMER2工作模式3配置函数
*入口参数:
uint16_t:TIM2_SetCounter:配置计数初值
*出口参数:void
**************************************************/
void TIM2_WorkMode3Config(uint16_t TIM2_SetCounter)
{
  TXINX = 0x02;
  RCAPXL = TIM2_SetCounter % 256;
  RCAPXH = TIM2_SetCounter / 256;
  TXMOD |= 0X02;
}
/**************************************************
*函数名称:void TIM2_WorkModeConfig(TIM2_WorkMode_TypeDef TIM2_WorkMode, uint16_t TIM2_SetCounter)
*函数功能:TIMER2工作模式配置函数
*入口参数:
TIM2_WorkMode_TypeDef:TIM2_WorkMode:TIMER2工作模式选择
uint16_t:TIM2_SetCounter:TIMER2计数初值配置
*出口参数:void
**************************************************/
void TIM2_WorkModeConfig(TIM2_WorkMode_TypeDef TIM2_WorkMode, uint16_t TIM2_SetCounter)
{
  switch (TIM2_WorkMode)
  {
  case TIM2_WORK_MODE0:
    TIM2_WorkMode0Config(TIM2_SetCounter);
    break;

  case TIM2_WORK_MODE1:
    TIM2_WorkMode1Config(TIM2_SetCounter);
    break;

  case TIM2_WORK_MODE3:
    TIM2_WorkMode3Config(TIM2_SetCounter);
    break;

  default:
    break;
  }
}
/*****************************************************
*函数名称:void TIM2_SetEXEN2(FunctionalState NewState)
*函数功能:TIMER2_EXEN2配置函数
*入口参数:
FunctionalState:NewState:EXEN2使能选择
*出口参数:void
*****************************************************/
void TIM2_SetEXEN2(FunctionalState NewState)
{
  TXINX = 0x02;

  if (NewState == DISABLE)
  {
    EXENX = 0;
  }
  else
  {
    EXENX = 1;
  }
}

/*****************************************************
*函数名称:void TIM2_Cmd(FunctionalState NewState)
*函数功能:TIMER2功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
*****************************************************/
void TIM2_Cmd(FunctionalState NewState)
{
  TXINX = 0x02;

  if (NewState == DISABLE)
  {
    TRX = 0;
  }
  else
  {
    TRX = 1;
  }
}

/*****************************************************
*函数名称:void TIM2_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:TIMER2
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
*****************************************************/
void TIM2_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  TXINX = 0x02;

  if (NewState == DISABLE)
  {
    ET2 = 0;
  }
  else
  {
    ET2 = 1;
  }

  if (Priority == LOW)
  {
    IPT2 = 0;
  }
  else
  {
    IPT2 = 1;
  }
}

/*****************************************************
*函数名称:FlagStatus TIM2_GetFlagStatus(void)
*函数功能:获得TIMER2中断标志状态
*入口参数:
TIM2_Flag_TypeDef:TIM2_Flag:TIMER2标志选择
*出口参数:
FlagStatus:TIMER2中断标志状态
*****************************************************/
FlagStatus TIM2_GetFlagStatus(TIM2_Flag_TypeDef TIM2_Flag)
{
  FlagStatus status = RESET;
  TXINX = 0x02;

  if ((TIM2_Flag & TXCON) != (uint8_t)RESET)
  {
    status = SET;
  }
  else
  {
    status = RESET;
  }

  return status;
}

/*****************************************************
*函数名称:void TIMX_ClearFlag(void)
*函数功能:清除TIMER2中断标志状态
*入口参数:
TIM2_Flag_TypeDef:TIM2_Flag:TIMER2标志选择
*出口参数:void
*****************************************************/
void TIM2_ClearFlag(TIM2_Flag_TypeDef TIM2_Flag)
{
  TXINX = 0x02;
  TXCON &= (~TIM2_Flag);
}

/******************* (C) COPYRIGHT 2021 SinOne Microelectronics *****END OF FILE****/