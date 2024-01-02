//************************************************************
//  Copyright (c) 
//	文件名称: 		sc95f_wdt.h
//	作者:					赛元应用团队
//	模块功能: 		BTM固件库函数C文件
//  最后更正日期: 2022年3月23日
// 	版本: 				V1.10002
//  说明: 
//*************************************************************

#ifndef _sc95f_WDT_H_
#define _sc95f_WDT_H_

#include "sc95f.h"

typedef enum
{
  WDT_OverflowTime_500MS = (uint8_t)0x00,   //看门狗溢出时间为500MS
  WDT_OverflowTime_250MS = (uint8_t)0x01,   //看门狗溢出时间为250MS
  WDT_OverflowTime_125MS = (uint8_t)0x02,   //看门狗溢出时间为125MS
  WDT_OverflowTime_62_5MS = (uint8_t)0x03,  //看门狗溢出时间为62.5MS
  WDT_OverflowTime_31_5MS = (uint8_t)0x04,  //看门狗溢出时间为31.5MS
  WDT_OverflowTime_15_75MS = (uint8_t)0x05, //看门狗溢出时间为15.75MS
  WDT_OverflowTime_7_88MS = (uint8_t)0x06,  //看门狗溢出时间为7.88MS
  WDT_OverflowTime_3_94MS = (uint8_t)0x07   //看门狗溢出时间为3.94MS
} WDT_OverflowTime_TypeDef;

/************************宏函数************************/
/*****************************************************
*函数名称:void WDT_SetReload(void)
*函数功能:WDT喂狗
*入口参数:void
*出口参数:void
*****************************************************/
#define WDT_SetReload() SET_BIT(WDTCON,0x10)


void WDT_DeInit(void);
void WDT_Init(WDT_OverflowTime_TypeDef OverflowTime);
void WDT_Cmd(FunctionalState NewState);

#endif

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/