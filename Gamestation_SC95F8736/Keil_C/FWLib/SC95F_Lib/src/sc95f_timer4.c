//************************************************************
//  Copyright (c) 
//	文件名称	: sc95f_timer4.c
//	作者		:
//	模块功能	: TIMER4固件库函数C文件
//  最后更正日期:	2022年7月22日
// 	版本:					V1.10004
//  说明        :该文件仅适用于SC95F系列芯片
//*************************************************************

#include "sc95f_timer4.h"

/**************************************************
*函数名称:void TIM4_DeInit(void)
*函数功能:TIMER4相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
**************************************************/
void TIM4_DeInit()
{
  TXINX = 0x04; //TIMER4 选择
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
*函数名称:void TIM4_PrescalerSelection(TIM4_PresSel_TypeDef TIM4_PrescalerSelection)
*函数功能:TIMER4 预分频选择
*入口参数:
TIM4_PresSel_TypeDef:TIM4_PrescalerSelection:预分频选择
*出口参数:void
**************************************************/
void TIM4_PrescalerSelection(TIM4_PresSel_TypeDef TIM4_PrescalerSelection)
{
  TXINX = 0x04;

  if (TIM4_PrescalerSelection == TIM4_PRESSEL_FSYS_D12)
  {
    TXMOD &= 0X7F;
  }
  else if (TIM4_PrescalerSelection == TIM4_PRESSEL_FSYS_D1)
  {
    TXMOD |= 0X80;
  }
}

/**************************************************
*函数名称:void TIM4_WorkMode1Config(uint16_t TIM4_SetCounter)
*函数功能:TIMER4工作模式1配置函数
*入口参数:
uint16_t:TIM4_SetCounter:配置计数初值
*出口参数:void
**************************************************/
void TIM4_WorkMode1Config(uint16_t TIM4_SetCounter)
{
  TXINX = 0x04;
  RCAPXL = TIM4_SetCounter % 256;
  RCAPXH = TIM4_SetCounter / 256;

  TLX = RCAPXL;
  THX = RCAPXH;
}

/*****************************************************
*函数名称:void TIM4_Cmd(FunctionalState NewState)
*函数功能:TIMER4功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
*****************************************************/
void TIM4_Cmd(FunctionalState NewState)
{
  TXINX = 0x04;

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
*函数名称:void TIMX_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:TIMER4中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
*****************************************************/
void TIM4_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  TXINX = 0x04;

  if (NewState == DISABLE)
  {
    IE1 &= 0X7F;
  }
  else
  {
    IE1 |= 0X80;
  }

  if (Priority == LOW)
  {
    IP1 &= 0X7F;
  }
  else
  {
    IP1 |= 0X80;
  }
}

/*****************************************************
*函数名称:FlagStatus TIM4_GetFlagStatus(TIM4_Flag_TypeDef TIM4_Flag)
*函数功能:获得TIMER4中断标志状态
*入口参数:
TIM4_Flag_TypeDef:TIM4_Flag:TIMER4标志选择
*出口参数:
FlagStatus:TIMER4中断标志状态
*****************************************************/
FlagStatus TIM4_GetFlagStatus(TIM4_Flag_TypeDef TIM4_Flag)
{
  FlagStatus status = RESET;
  TXINX = 0x04;

  if ((TIM4_Flag & TXCON) != (uint8_t)RESET)
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
*函数名称:void TIM4_ClearFlag(TIM4_Flag_TypeDef TIM4_Flag)
*函数功能:清除TIMER4中断标志状态
*入口参数:
TIM4_Flag_TypeDef:TIM4_Flag:TIMER4标志选择
*出口参数:void
*****************************************************/
void TIM4_ClearFlag(TIM4_Flag_TypeDef TIM4_Flag)
{
  TXINX = 0x04;
  TXCON &= (~TIM4_Flag);
}

#if defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)
/**************************************************
*函数名称:void TIM4_TimeBaseInit(TIM4_CountMode_TypeDef TIM4_CountMode, TIM4_CountDirection_TypeDef TIM4_CountDirection)
*函数功能:TIM4基本设置配置函数
*入口参数:
TIM4_CountMode_TypeDef:TIM4_CountMode:计数/定时模式选择
TIM4_CountDirection_TypeDef:TIM4_CountDirection:计数方向选择
*出口参数:void
**************************************************/
void TIM4_TimeBaseInit(TIM4_CountMode_TypeDef TIM4_CountMode,
                       TIM4_CountDirection_TypeDef TIM4_CountDirection)
{
  TXINX = 0x04;

  if (TIM4_CountMode == TIM4_MODE_TIMER)
  {
    TXCON &= 0XFD;
  }
  else if (TIM4_CountMode == TIM4_MODE_COUNTER)
  {
    TXCON |= 0X02;
  }

  /************************************************************/
  if (TIM4_CountDirection == TIM4_COUNTDIRECTION_UP)
  {
    TXMOD &= 0XFE;
  }
  else if (TIM4_CountDirection == TIM4_COUNTDIRECTION_DOWN_UP)
  {
    TXMOD |= 0X01;
  }
}

/**************************************************
*函数名称:void TIM4_WorkMode0Config(uint16_t TIM4_SetCounter)
*函数功能:TIMER4工作模式0配置函数
*入口参数:
uint16_t:TIM4_SetCounter:配置计数初值
*出口参数:void
**************************************************/
void TIM4_WorkMode0Config(uint16_t TIM4_SetCounter)
{
  TXINX = 0x04;
  CP = 1;
  TLX = TIM4_SetCounter % 256;
  THX = TIM4_SetCounter / 256;
}

/**************************************************
*函数名称:void TIM4_WorkMode3Config(uint16_t TIM4_SetCounter)
*函数功能:TIMER2工作模式3配置函数
*入口参数:
uint16_t:TIM2_SetCounter:配置计数初值
*出口参数:void
**************************************************/
void TIM4_WorkMode3Config(uint16_t TIM4_SetCounter)
{
  TXINX = 0x04;
  RCAPXL = TIM4_SetCounter % 256;
  RCAPXH = TIM4_SetCounter / 256;
  TXMOD |= 0X02;
}

/**************************************************
*函数名称:void TIM4_WorkModeConfig(TIM4_WorkMode_TypeDef TIM4_WorkMode, uint16_t TIM4_SetCounter)
*函数功能:TIMER4工作模式配置函数
*入口参数:
TIM4_WorkMode_TypeDef:TIM4_WorkMode:TIMER2工作模式选择
uint16_t:TIM4_SetCounter:TIMER2计数初值配置
*出口参数:void
**************************************************/
void TIM4_WorkModeConfig(TIM4_WorkMode_TypeDef TIM4_WorkMode, uint16_t TIM4_SetCounter)
{
  switch (TIM4_WorkMode)
  {
  case TIM4_WORK_MODE0:
    TIM4_WorkMode0Config(TIM4_SetCounter);
    break;

  case TIM4_WORK_MODE1:
    TIM4_WorkMode1Config(TIM4_SetCounter);
    break;

  case TIM4_WORK_MODE3:
    TIM4_WorkMode3Config(TIM4_SetCounter);
    break;

  default:
    break;
  }
}

/*****************************************************
*函数名称:void TIM4_SetEXEN4(FunctionalState NewState)
*函数功能:TIMER4_EXEN4配置函数
*入口参数:
FunctionalState:NewState:EXEN4使能选择
*出口参数:void
*****************************************************/
void TIM4_SetEXEN4(FunctionalState NewState)
{
  TXINX = 0x04;

  if (NewState == DISABLE)
  {
    EXENX = 0;
  }
  else
  {
    EXENX = 1;
  }
}

#endif

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/