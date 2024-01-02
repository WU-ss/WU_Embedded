//************************************************************
//  Copyright (c) 
//	文件名称: 		sc95f_btm.c
//	作者:					赛元应用团队
//	模块功能: 		BTM固件库函数C文件
//  最后更正日期: 2022年3月23日
// 	版本: 				V1.10001
//  说明: 
//*************************************************************

#include "sc95f_btm.h"

/**************************************************
*函数名称:void BTM_Init(BTM_Timebase_TypeDef BTM_Timebase)
*函数功能:BTM初始化配置函数
*入口参数:
BTM_Timebase_TypeDef:BTM_Timebase:BTM溢出时间选择
*出口参数:void
**************************************************/
void BTM_Init(BTM_Timebase_TypeDef BTM_Timebase)
{
  BTMCON = (BTMCON & 0xF0) | BTM_Timebase;
}

/*****************************************************
*函数名称:void BTM_Cmd(FunctionalState NewState)
*函数功能:BTM功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
*****************************************************/
void BTM_Cmd(FunctionalState NewState)
{
  if (NewState == DISABLE)
  {
    BTMCON &= 0x7f;
  }
  else
  {
    BTMCON |= 0x80;
  }
}

/*****************************************************
*函数名称:void BTM_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:BTM中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
*****************************************************/
void BTM_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  //中断使能设置
  if (NewState == DISABLE)
  {
    IE1 &= 0xfb;
  }
  else
  {
    IE1 |= 0x04;
  }

  //中断优先级设置
  if (Priority == LOW)
  {
    IP1 &= 0xfb;
  }
  else
  {
    IP1 |= 0x04;
  }
}

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/