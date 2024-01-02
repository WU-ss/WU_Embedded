//************************************************************
//  Copyright (c) 
//	文件名称: 			sc95f_acmp.h
//	作者:
//	模块功能: 			ACMP固件库函数头文件
//  最后更正日期: 	2022年7月20日
// 	版本:					V1.0001
//  说明					该文件仅适用于SC95Fxx1x系列芯片
//*************************************************************

#ifndef _sc95f_ACMP_H_
#define _sc95f_ACMP_H_

#include "sc95f.h"

//比较器负端输入电压选择枚举
typedef enum
{
  ACMP_VREF_EXTERNAL = (uint8_t)0X00, //选用CMPR为ACMP的比较电压
  ACMP_VREF_1D16VDD = (uint8_t)0X01,  //选用1/16VDD为ACMP的比较电压
  ACMP_VREF_2D16VDD = (uint8_t)0X02,  //选用2/16VDD为ACMP的比较电压
  ACMP_VREF_3D16VDD = (uint8_t)0X03,  //选用3/16VDD为ACMP的比较电压
  ACMP_VREF_4D16VDD = (uint8_t)0X04,  //选用4/16VDD为ACMP的比较电压
  ACMP_VREF_5D16VDD = (uint8_t)0X05,  //选用5/16VDD为ACMP的比较电压
  ACMP_VREF_6D16VDD = (uint8_t)0X06,  //选用6/16VDD为ACMP的比较电压
  ACMP_VREF_7D16VDD = (uint8_t)0X07,  //选用7/16VDD为ACMP的比较电压
  ACMP_VREF_8D16VDD = (uint8_t)0X08,  //选用8/16VDD为ACMP的比较电压
  ACMP_VREF_9D16VDD = (uint8_t)0X09,  //选用9/16VDD为ACMP的比较电压
  ACMP_VREF_10D16VDD = (uint8_t)0X0A, //选用10/16VDD为ACMP的比较电压
  ACMP_VREF_11D16VDD = (uint8_t)0X0B, //选用11/16VDD为ACMP的比较电压
  ACMP_VREF_12D16VDD = (uint8_t)0X0C, //选用12/16VDD为ACMP的比较电压
  ACMP_VREF_13D16VDD = (uint8_t)0X0D, //选用13/16VDD为ACMP的比较电压
  ACMP_VREF_14D16VDD = (uint8_t)0X0E, //选用14/16VDD为ACMP的比较电压
  ACMP_VREF_15D16VDD = (uint8_t)0X0F  //选用15/16VDD为ACMP的比较电压
} ACMP_Vref_Typedef;

//比较器外部输入通道选择枚举
typedef enum
{
	#if !defined(SC95R751)
  ACMP_CHANNEL_0 = (uint8_t)0x00, //选择CMP0做ACMP输入口
	#endif
  ACMP_CHANNEL_1 = (uint8_t)0x01, //选择CMP1做ACMP输入口
  ACMP_CHANNEL_2 = (uint8_t)0x02, //选择CMP2做ACMP输入口
  ACMP_CHANNEL_3 = (uint8_t)0x03, //选择CMP3做ACMP输入口
	#if defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)|| defined (SC95F8x1xB) || defined (SC95F7x1xB)\
		 || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)
	ACMP_CHANNEL_P = (uint8_t)0x10, //选择CMPP做ACMP输入口，CMPP为基准电压1.5V
	#endif
} ACMP_Channel_TypeDef;

//比较器触发方式枚举
typedef enum
{
  ACMP_TRIGGER_NO = (uint8_t)0x00,        //不产生中断
  ACMP_TRIGGER_RISE_ONLY = (uint8_t)0x04, //模拟比较器触发方式为上升沿
  ACMP_TRIGGER_FALL_ONLY = (uint8_t)0x08, //模拟比较器触发方式为下降沿
  ACMP_TRIGGER_RISE_FALL = (uint8_t)0x0C  //模拟比较器触发方式为上升沿与下降沿
} ACMP_TriggerMode_Typedef;

//比较器标志位枚举
typedef enum
{
  ACMP_FLAG_CMPIF = (uint8_t)0x40, //ACMP中断标志位
  ACMP_FLAG_CMPSTA = (uint8_t)0x20 //ACMP输出状态
} ACMP_Flag_TypeDef;

void ACMP_DeInit(void);
void ACMP_Init(ACMP_Vref_Typedef ACMP_Vref, ACMP_Channel_TypeDef ACMP_Channel);
void ACMP_SetTriggerMode(ACMP_TriggerMode_Typedef ACMP_TriggerMode);
void ACMP_Cmd(FunctionalState NewState);
void ACMP_ITConfig(FunctionalState NewState, PriorityStatus Priority);
FlagStatus ACMP_GetFlagStatus(ACMP_Flag_TypeDef ACMP_Flag);
void ACMP_ClearFlag(void);

#endif

/******************* (C) COPYRIGHT 2022 SinOne Microelectronics *****END OF FILE****/