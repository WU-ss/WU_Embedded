//************************************************************
//  Copyright (c) 
//	文件名称: 		sc95f_wdt.c
//	作者:					赛元应用团队
//	模块功能: 		BTM固件库函数C文件
//  最后更正日期: 2022年3月23日
// 	版本: 				V1.10001
//  说明: 
//*************************************************************

#include "sc95f_wdt.h"
/**************************************************
*函数名称:void WDT_DeInit(void)
*函数功能:WDT相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
**************************************************/
void WDT_DeInit(void)
{
    WDTCON = 0X00;
}

/**************************************************
*函数名称:void WDT_Init(WDT_OverflowTime_TypeDef OverflowTime)
*函数功能:WDT初始化配置函数
*入口参数:
WDT_OverflowTime_TypeDef:OverflowTime:WDT溢出时间选择
*出口参数:void
**************************************************/
void WDT_Init(WDT_OverflowTime_TypeDef OverflowTime)
{
    WDTCON = (WDTCON & 0XF8) | OverflowTime;
}

/*****************************************************
*函数名称:void WDT_Cmd(FunctionalState NewState)
*函数功能:WDT功能开关函数
*入口参数:
FunctionalState:NewState:看门狗功能启动/关闭选择
*出口参数:void
*****************************************************/
void WDT_Cmd(FunctionalState NewState)
{
  OPINX = 0XC1;

  if (NewState == DISABLE)
  {
    OPREG &= 0X7F;
  }
  else
  {
    OPREG |= 0X80;
  }
}
/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/