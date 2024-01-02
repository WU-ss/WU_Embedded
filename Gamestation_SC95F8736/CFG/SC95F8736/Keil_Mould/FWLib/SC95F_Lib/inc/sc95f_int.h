//************************************************************
//  Copyright (c) 
//	文件名称	: sc95f_INT.h
//	作者		:
//	模块功能	: INT固件库函数头文件
//  最后更正日期: 2022/01/07
// 	版本		: V1.10001
//  说明        :该文件仅适用于SC95F系列芯片
//*************************************************************

#ifndef _sc95f_INT_H_
#define _sc95f_INT_H_

#include "sc95f.h"

//外部中断触发方式选择枚举
typedef enum
{
  INT_TRIGGER_RISE_ONLY = (uint8_t)0x01, //外部中断触发方式为上升沿
  INT_TRIGGER_FALL_ONLY = (uint8_t)0x02, //外部中断触发方式为下降沿
  INT_TRIGGER_RISE_FALL = (uint8_t)0x03, //外部中断触发方式为上升沿与下降沿
  INT_TRIGGER_DISABLE = (uint8_t)0x04    //关闭外部中断触发
} INT_TriggerMode_Typedef;

//外部中断类型选择枚举
typedef enum
{
  INT0 = (uint8_t)0x00, //外部中断0
  INT1 = (uint8_t)0x01, //外部中断1
  INT2 = (uint8_t)0x02  //外部中断2
} INTx_Typedef;

#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95F7619B)
//外部中断0输入口选择枚举
typedef enum
{
  INT04 = (uint8_t)0x10, //将P04设置为外部中断脚
  INT05 = (uint8_t)0x20, //将P05设置为外部中断脚
  INT06 = (uint8_t)0x40, //将P06设置为外部中断脚
  INT07 = (uint8_t)0x80  //将P07设置为外部中断脚
} INT0x_Typedef;

//外部中断1输入口选择枚举
typedef enum
{
  INT10 = (uint8_t)0x01, //将P40设置为外部中断脚
  INT11 = (uint8_t)0x02, //将P41设置为外部中断脚
  INT12 = (uint8_t)0x04, //将P42设置为外部中断脚
  INT13 = (uint8_t)0x08, //将P43设置为外部中断脚
  INT14 = (uint8_t)0x10, //将P14设置为外部中断脚
  INT15 = (uint8_t)0x20, //将P15设置为外部中断脚
  INT16 = (uint8_t)0x40, //将P16设置为外部中断脚
  INT17 = (uint8_t)0x80  //将P17设置为外部中断脚
} INT1x_Typedef;

//外部中断2输入口选择枚举
typedef enum
{
  INT20 = (uint8_t)0x01, //将P20设置为外部中断脚
  INT21 = (uint8_t)0x02, //将P21设置为外部中断脚
  INT22 = (uint8_t)0x04, //将P22设置为外部中断脚
  INT23 = (uint8_t)0x08  //将P23设置为外部中断脚
} INT2x_Typedef;
#endif

#if defined(SC95F8x2x) || defined(SC95F7x2x)
//外部中断0输入口选择枚举
typedef enum
{
  INT01 = (uint8_t)0x02, //将P11设置为INT0脚
  INT02 = (uint8_t)0x04, //将P12设置为INT0脚
  INT03 = (uint8_t)0x08  //将P13设置为INT0脚
} INT0x_Typedef;

//外部中断1输入口选择枚举
typedef enum
{
  INT10 = (uint8_t)0x01, //将P14设置为INT1脚
  INT11 = (uint8_t)0x02, //将P15设置为INT1脚
  INT12 = (uint8_t)0x04, //将P16设置为INT1脚
  INT13 = (uint8_t)0x08  //将P17设置为INT1脚
} INT1x_Typedef;

//外部中断2输入口选择枚举
typedef enum
{
  INT20 = (uint8_t)0x01, //将P04设置为INT2脚
  INT21 = (uint8_t)0x02, //将P05设置为INT2脚
  INT22 = (uint8_t)0x04, //将P06设置为INT2脚
  INT23 = (uint8_t)0x08, //将P07设置为INT2脚
  INT24 = (uint8_t)0x10, //将P20设置为INT2脚
  INT25 = (uint8_t)0x20  //将P21设置为INT2脚
} INT2x_Typedef;
#endif

#if defined (SC95R751)
//外部中断0输入口选择枚举
typedef enum
{
  INT06 = (uint8_t)0x40, //将P06设置为外部中断脚
  INT07 = (uint8_t)0x80  //将P07设置为外部中断脚
} INT0x_Typedef;

//外部中断1输入口选择枚举
typedef enum
{
  INT11 = (uint8_t)0x02, //将P41设置为外部中断脚
  INT12 = (uint8_t)0x04, //将P42设置为外部中断脚
  INT13 = (uint8_t)0x08, //将P43设置为外部中断脚
  INT14 = (uint8_t)0x10, //将P14设置为外部中断脚
  INT15 = (uint8_t)0x20, //将P15设置为外部中断脚
  INT16 = (uint8_t)0x40, //将P16设置为外部中断脚
  INT17 = (uint8_t)0x80  //将P17设置为外部中断脚
} INT1x_Typedef;
#endif

#if defined (SC95F7610B)
//外部中断0输入口选择枚举
typedef enum
{
  INT06 = (uint8_t)0x40, //将P06设置为外部中断脚
  INT07 = (uint8_t)0x80  //将P07设置为外部中断脚
} INT0x_Typedef;

//外部中断1输入口选择枚举
typedef enum
{
  INT10 = (uint8_t)0x01, //将P40设置为外部中断脚
  INT11 = (uint8_t)0x02, //将P41设置为外部中断脚
  INT12 = (uint8_t)0x04, //将P42设置为外部中断脚
  INT13 = (uint8_t)0x08, //将P43设置为外部中断脚
  INT14 = (uint8_t)0x10, //将P14设置为外部中断脚
} INT1x_Typedef;

//外部中断2输入口选择枚举
typedef enum
{
  INT20 = (uint8_t)0x01, //将P20设置为外部中断脚
  INT21 = (uint8_t)0x02, //将P21设置为外部中断脚
  INT22 = (uint8_t)0x04, //将P22设置为外部中断脚
} INT2x_Typedef;
#endif


void INT_DeInit(INTx_Typedef INTx);
void INT0_SetTriggerMode(uint8_t INT0x, INT_TriggerMode_Typedef TriggerMode);
void INT1_SetTriggerMode(uint8_t INT1x, INT_TriggerMode_Typedef TriggerMode);
#if !defined (SC95R751)
void INT2_SetTriggerMode(uint8_t INT2x, INT_TriggerMode_Typedef TriggerMode);
#endif
void INT0_ITConfig(FunctionalState NewState, PriorityStatus Priority);
void INT1_ITConfig(FunctionalState NewState, PriorityStatus Priority);
#if !defined (SC95R751)
void INT2_ITConfig(FunctionalState NewState, PriorityStatus Priority);
#endif

#endif

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/