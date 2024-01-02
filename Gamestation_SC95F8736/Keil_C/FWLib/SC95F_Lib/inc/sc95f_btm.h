//************************************************************
//  Copyright (c) 
//	文件名称: 		sc95f_btm.h
//	作者:					赛元应用团队
//	模块功能: 		BTM固件库函数H文件
//  最后更正日期: 2022年3月23日
// 	版本: 				V1.10001
//  说明: 
//*************************************************************
#ifndef _sc95f_BTM_H_
#define _sc95f_BTM_H_

#include "sc95f.h"

//BTM中断时间选择枚举
typedef enum
{
  BTM_TIMEBASE_15_625MS = (uint8_t)0x00, //BTM每15.625MS产生一次中断
  BTM_TIMEBASE_31_25MS = (uint8_t)0x01,  //BTM每31.25MS产生一次中断
  BTM_TIMEBASE_62_5MS = (uint8_t)0x02,   //BTM每62.5MS产生一次中断
  BTM_TIMEBASE_125MS = (uint8_t)0x03,    //BTM每125MS产生一次中断
  BTM_TIMEBASE_250MS = (uint8_t)0x04,    //BTM每0.25S产生一次中断
  BTM_TIMEBASE_500MS = (uint8_t)0x05,    //BTM每0.5S产生一次中断
  BTM_TIMEBASE_1S = (uint8_t)0x06,       //BTM每1S产生一次中断
  BTM_TIMEBASE_2S = (uint8_t)0x07,       //BTM每2S产生一次中断
  BTM_TIMEBASE_4S = (uint8_t)0x08,       //BTM每4S产生一次中断
  BTM_TIMEBASE_8S = (uint8_t)0x09,       //BTM每8S产生一次中断
  BTM_TIMEBASE_16S = (uint8_t)0x0a,      //BTM每16S产生一次中断
  BTM_TIMEBASE_32S = (uint8_t)0x0b       //BTM每32S产生一次中断
} BTM_Timebase_TypeDef;

/*******************************宏函数*******************************/
/**************************************************
*函数名称:void BTM_DeInit(void)
*函数功能:BTM相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
**************************************************/
#define BTM_DeInit() CLEAR_REG(BTMCON)

/*****************************************************
*函数名称:void BTM_GetFlagStatus(void)
*函数功能:获取BTM中断标志状态
*入口参数:void
*出口参数:
FlagStatus:BTM中断标志状态
*****************************************************/
#define BTM_GetFlagStatus() ((READ_BIT(BTMCON,0x40)) ? (SET):(RESET))

/*****************************************************
*函数名称:void BTM_ClearFlag(void)
*函数功能:清除BTM中断标志状态
*入口参数:void
*出口参数:void
*****************************************************/
#define BTM_ClearFlag() CLEAR_BIT(BTMCON,0x40)

void BTM_Init(BTM_Timebase_TypeDef BTM_Timebase);
void BTM_Cmd(FunctionalState NewState);
void BTM_ITConfig(FunctionalState NewState, PriorityStatus Priority);

#endif

/******************* (C) COPYRIGHT 2018 SinOne Microelectronics *****END OF FILE****/