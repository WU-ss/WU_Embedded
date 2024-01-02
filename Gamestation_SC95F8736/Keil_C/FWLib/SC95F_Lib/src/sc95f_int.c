//************************************************************
//  Copyright (c) 
//	文件名称: 		sc95f_int.c
//	作者:				赛元应用团队
//	模块功能: 		INT固件库函数C文件
//  最后更正日期:2022年7月20日
// 	版本: 			V1.10001
//  说明:				该文件仅适用于SC95F系列芯片
//*************************************************************

#include "sc95f_int.h"

/**************************************************
*函数名称:void INT_DeInit(INTx_Typedef INTx)
*函数功能:INTx相关寄存器复位至缺省值
*入口参数:
INTx_Typedef:INTx:INTx选择
*出口参数:void
**************************************************/
void INT_DeInit(INTx_Typedef INTx)
{
  switch (INTx)
  {
  case INT0:
    INT0R = 0x00;
    INT0F = 0x00;
    IE &= (~0X01);
    IP &= ~0X01;
    TCON &= (~0X02);
    break;

  case INT1:
    INT1R = 0x00;
    INT1F = 0x00;
    IE &= (~0X04);
    IP &= ~0X04;
    TCON &= (~0X08);
    break;

  case INT2:
    INT2R = 0x00;
    INT2F = 0x00;
    IE1 &= (~0X08);
    IP1 &= ~0X08;
    break;

  default:
    break;
  }
}

/**************************************************
*函数名称:void INT0_SetTriggerMode(uint8_t INT0x, INT_TriggerMode_Typedef TriggerMode)
*函数功能:INT0x中断触发方式配置函数
*入口参数:
	INT0x_Typedef:INT0x:INT0x选择（uint8_t作为入参，方便进行位或操作）
	INT_TriggerMode_Typedef:TriggerMode:中断触发方式选择
*出口参数:void
**************************************************/
void INT0_SetTriggerMode(uint8_t INT0x, INT_TriggerMode_Typedef TriggerMode)
{
  switch (TriggerMode)
  {
  case INT_TRIGGER_RISE_ONLY:
    INT0R |= INT0x;
    INT0F &= (~INT0x);
    break;

  case INT_TRIGGER_FALL_ONLY:
    INT0R &= (~INT0x);
    INT0F |= INT0x;
    break;

  case INT_TRIGGER_RISE_FALL:
    INT0R |= INT0x;
    INT0F |= INT0x;
    break;

  case INT_TRIGGER_DISABLE:
    INT0R &= (~INT0x);
    INT0F &= (~INT0x);

  default:
    break;
  }
}

/**************************************************
*函数名称:void INT1_SetTriggerMode(uint8_t INT1x, INT_TriggerMode_Typedef TriggerMode)
*函数功能:INT1x中断触发方式配置函数
*入口参数:
INT1x_Typedef:INT1x:INT1x选择（uint8_t作为入参，方便进行位或操作）
INT_TriggerMode_Typedef:TriggerMode:中断触发方式选择
*出口参数:void
**************************************************/
void INT1_SetTriggerMode(uint8_t INT1x, INT_TriggerMode_Typedef TriggerMode)
{
  switch (TriggerMode)
  {
  case INT_TRIGGER_RISE_ONLY:
    INT1R |= INT1x;
    INT1F &= (~INT1x);
    break;

  case INT_TRIGGER_FALL_ONLY:
    INT1R &= (~INT1x);
    INT1F |= INT1x;
    break;

  case INT_TRIGGER_RISE_FALL:
    INT1R |= INT1x;
    INT1F |= INT1x;
    break;

  case INT_TRIGGER_DISABLE:
    INT1R &= (~INT1x);
    INT1F &= (~INT1x);

  default:
    break;
  }
}

#if !defined (SC95R751)
/**************************************************
*函数名称:void INT2_SetTriggerMode(uint8_t INT2x, INT_TriggerMode_Typedef TriggerMode)
*函数功能:INT2x中断触发方式配置函数
*入口参数:
INT2x_Typedef:INT2x:INT2x选择（uint8_t作为入参，方便进行位或操作）
INT_TriggerMode_Typedef:TriggerMode:中断触发方式选择
*出口参数:void
**************************************************/
void INT2_SetTriggerMode(uint8_t INT2x, INT_TriggerMode_Typedef TriggerMode)
{
  switch (TriggerMode)
  {
  case INT_TRIGGER_RISE_ONLY:
    INT2R |= INT2x;
    INT2F &= (~INT2x);
    break;

  case INT_TRIGGER_FALL_ONLY:
    INT2R &= (~INT2x);
    INT2F |= INT2x;
    break;

  case INT_TRIGGER_RISE_FALL:
    INT2R |= INT2x;
    INT2F |= INT2x;
    break;

  case INT_TRIGGER_DISABLE:
    INT2R &= (~INT2x);
    INT2F &= (~INT2x);

  default:
    break;
  }
}
#endif

/*****************************************************
*函数名称:void INT0_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:INT0中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
*****************************************************/
void INT0_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  if (NewState != DISABLE)
  {
    IE |= 0X01;
  }
  else
  {
    IE &= (~0X01);
  }

  if (Priority == LOW)
  {
    IP &= ~0X01;
  }
  else
  {
    IP |= 0X01;
  }
}

/*****************************************************
*函数名称:void INT1_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:INT1中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
*****************************************************/
void INT1_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  if (NewState != DISABLE)
  {
    IE |= 0X04;
  }
  else
  {
    IE &= (~0X04);
  }

  if (Priority == LOW)
  {
    IP &= ~0X04;
  }
  else
  {
    IP |= 0X04;
  }
}

/*****************************************************
*函数名称:void INT2_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:INT0中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
*****************************************************/
void INT2_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  if (NewState != DISABLE)
  {
    IE1 |= 0X08;
  }
  else
  {
    IE1 &= (~0X08);
  }

  if (Priority == LOW)
  {
    IP1 &= ~0X08;
  }
  else
  {
    IP1 |= 0X08;
  }
}

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/
