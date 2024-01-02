//************************************************************
//  Copyright (c) 
//	文件名称	: sc95f_timerx.c
//	作者		:
//	模块功能	: TIMER3固件库函数C文件
//  最后更正日期: 2022/01/24
// 	版本		: V1.10001
//  说明        :该文件仅适用于SC95Fxx1x、SC95Fxx2x系列芯片
//*************************************************************

#include "sc95f_timer3.h"

/**************************************************
*函数名称:void TIMX_DeInit(void)
*函数功能:TIMER3相关寄存器复位至初始值
*入口参数:void
*出口参数:void
**************************************************/
void TIM3_DeInit()
{
  TXINX = 0x03;    //TIMER3 选择
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
*函数名称:void TIM3_PrescalerSelection(TIMX_TimerSelect_TypeDef TIMX_TimerSelect, TIMX_PresSel_TypeDef TIMX_PrescalerSelection)
*函数功能:TIMER3 预分频选择
*入口参数:
TIM3_PresSel_TypeDef:TIM3_PrescalerSelection:预分频选择
*出口参数:void
**************************************************/
void TIM3_PrescalerSelection(TIM3_PresSel_TypeDef TIM3_PrescalerSelection)
{
  TXINX = 0x03;

  if(TIM3_PrescalerSelection == TIM3_PRESSEL_FSYS_D12)
  {
    TXMOD &= 0X7F;
  }
  else
    if(TIM3_PrescalerSelection == TIM3_PRESSEL_FSYS_D1)
    {
      TXMOD |= 0X80;
    }
}

/**************************************************
*函数名称:void TIM3_WorkMode1Config(uint16_t TIM3_SetCounter)
*函数功能:TIMER3工作模式1配置函数
*入口参数:
uint16_t TIM3_SetCounter	配置计数初值
*出口参数:void
**************************************************/
void TIM3_WorkMode1Config(uint16_t TIM3_SetCounter)
{
  TXINX = 0x03;
  RCAPXL = TIM3_SetCounter % 256;
  RCAPXH = TIM3_SetCounter / 256;

  TLX = RCAPXL;
  THX = RCAPXH;
}

/*****************************************************
*函数名称:void TIM3_Cmd(FunctionalState NewState)
*函数功能:TIMER3功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
*****************************************************/
void TIM3_Cmd(FunctionalState NewState)
{
  TXINX = 0x03;

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
*函数名称:void TIM3_ITConfig(TIM3_TimerSelect_TypeDef TIM3_TimerSelect, FunctionalState NewState, PriorityStatus Priority)
*函数功能:TIMER3中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
*****************************************************/
void TIM3_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  TXINX = 0x03;

  if(NewState == DISABLE)
  {
    IE1 &= 0XBF;
  }
  else
  {
    IE1 |= 0X40;
  }

  if(Priority == LOW)
  {
    IP1 &= 0XBF;
  }
  else
  {
    IP1 |= 0X40;
  }
}

/*****************************************************
*函数名称:FlagStatus TIM3_GetFlagStatus(void)
*函数功能:获得TIMER3中断标志状态
*入口参数:
TIM3_Flag_TypeDef:TIM3_Flag:TIMER3标志选择
*出口参数:
FlagStatus:TIMER3中断标志状态
*****************************************************/
FlagStatus TIM3_GetFlagStatus(TIM3_Flag_TypeDef TIM3_Flag)
{
  FlagStatus status = RESET;
  TXINX = 0x03;

  if((TIM3_Flag & TXCON) != (uint8_t)RESET)
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
*函数名称:void TIM3_ClearFlag(TIM3_Flag_TypeDef TIM3_Flag)
*函数功能:清除TIMER3中断标志状态
*入口参数:
TIM3_Flag_TypeDef:TIM3_Flag:TIMER3标志选择
*出口参数:void
*****************************************************/
void TIM3_ClearFlag(TIM3_Flag_TypeDef TIM3_Flag)
{
  TXINX = 0x03;
  TXCON &= (~TIM3_Flag);
}

#if defined (SC95F8x2x) || defined (SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)
/**************************************************
*函数名称:void TIM3_TimeBaseInit(TIM3_CountMode_TypeDef TIM3_CountMode, TIM3_CountDirection_TypeDef TIM3_CountDirection)
*函数功能:TIM3基本设置配置函数
*入口参数:
TIM3_CountMode_TypeDef:TIM3_CountMode:计数/定时模式选择
TIM3_CountDirection_TypeDef:TIM3_CountDirection:计数方向选择
*出口参数:void
**************************************************/
void TIM3_TimeBaseInit(TIM3_CountMode_TypeDef TIM3_CountMode,
                       TIM3_CountDirection_TypeDef TIM3_CountDirection)
{
  TXINX = 0x03;

  if(TIM3_CountMode == TIM3_MODE_TIMER)
  {
    TXCON &= 0XFD;
  }
  else
    if(TIM3_CountMode == TIM3_MODE_COUNTER)
    {
      TXCON |= 0X02;
    }

  /************************************************************/
  if(TIM3_CountDirection == TIM3_COUNTDIRECTION_UP)
  {
    TXMOD &= 0XFE;
  }
  else
    if(TIM3_CountDirection == TIM3_COUNTDIRECTION_DOWN_UP)
    {
      TXMOD |= 0X01;
    }
}

/**************************************************
*函数名称:void TIM3_WorkMode0Config(uint16_t TIM3_SetCounter)
*函数功能:TIMER3工作模式0配置函数
*入口参数:
uint16_t:TIM3_SetCounter:配置计数初值
*出口参数:void
**************************************************/
void TIM3_WorkMode0Config(uint16_t TIM3_SetCounter)
{
  TXINX = 0x03;
	CP = 1;
  TLX = TIM3_SetCounter % 256;
  THX = TIM3_SetCounter / 256;
}
/**************************************************
*函数名称:void TIM3_WorkMode3Config(uint16_t TIM3_SetCounter)
*函数功能:TIMER3工作模式3配置函数
*入口参数:
uint16_t:TIM3_SetCounter:配置计数初值
*出口参数:void
**************************************************/
void TIM3_WorkMode3Config(uint16_t TIM3_SetCounter)
{
  TXINX = 0x03;
  RCAPXL = TIM3_SetCounter % 256;
  RCAPXH = TIM3_SetCounter / 256;
  TXMOD |= 0X02;
}
/**************************************************
*函数名称:void TIM3_WorkModeConfig(TIM3_WorkMode_TypeDef TIM3_WorkMode, uint16_t TIM3_SetCounter)
*函数功能:TIMER3工作模式配置函数
*入口参数:
TIM3_WorkMode_TypeDef:TIM3_WorkMode:TIMER3工作模式选择
uint16_t:TIM3_SetCounter:TIMER3计数初值配置
*出口参数:void
**************************************************/
void TIM3_WorkModeConfig(TIM3_WorkMode_TypeDef TIM3_WorkMode, uint16_t TIM3_SetCounter)
{
  switch (TIM3_WorkMode)
  {
    case TIM3_WORK_MODE0:
      TIM3_WorkMode0Config(TIM3_SetCounter);
      break;

    case TIM3_WORK_MODE1:
      TIM3_WorkMode1Config(TIM3_SetCounter);
      break;

    case TIM3_WORK_MODE3:
      TIM3_WorkMode3Config(TIM3_SetCounter);
      break;

    default:
      break;
  }
}
/*****************************************************
*函数名称:void TIM3_SetEXEN3(FunctionalState NewState)
*函数功能:TIMER3_EXEN3配置函数
*入口参数:
FunctionalState:NewState:EXEN3使能选择
*出口参数:void
*****************************************************/
void TIM3_SetEXEN3(FunctionalState NewState)
{
  TXINX = 0x03;

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