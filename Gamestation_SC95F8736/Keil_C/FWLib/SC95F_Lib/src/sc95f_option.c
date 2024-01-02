//************************************************************
//  Copyright (c)
//	文件名称	: sc95f_option.c
//	作者		:
//	模块功能	: Customer Option寄存器配置C文件
//  最后更正日期: 2022/1/28
// 	版本		: V1.10002
//  说明        :该文件仅适用于SC95Fxx1x、SC95Fxx2x系列芯片
//*************************************************************

#include "sc95f_option.h"

/*****************************************************
*函数名称:void OPTION_WDT_Cmd(FunctionalState NewState)
*函数功能:WDT功能开关函数
*入口参数:
FunctionalState:NewState:看门狗功能启动/关闭选择
*出口参数:void
*****************************************************/
void OPTION_WDT_Cmd(FunctionalState NewState)
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

/*****************************************************
*函数名称:void OPTION_XTIPLL_Cmd(FunctionalState NewState)
*函数功能:外部低频晶振使能
*入口参数:
FunctionalState:NewState:外部低频晶振启动/关闭选择
*出口参数:void
*****************************************************/
void OPTION_XTIPLL_Cmd(FunctionalState NewState)
{
  OPINX = 0XC1;

  if (NewState == DISABLE)
  {
    OPREG &= 0XBF;
  }
  else
  {
    OPREG |= 0X40;
  }
}

/*****************************************************
*函数名称:void OPTION_SYSCLK_Init(SYSCLK_PresSel_TypeDef SYSCLK_PresSel)
*函数功能:系统时钟分频初始化
*入口参数:
SYSCLK_PresSel_TypeDef:SYSCLK_PresSel:选择系统时钟分频
*出口参数:void
*****************************************************/
void OPTION_SYSCLK_Init(SYSCLK_PresSel_TypeDef SYSCLK_PresSel)
{
  OPINX = 0XC1;
  OPREG = OPREG & 0XCF | SYSCLK_PresSel;
}

#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx) ||  defined(SC95F8x2x) || defined(SC95F7x2x)
/*****************************************************
*函数名称:void OPTION_RST_PIN_Cmd(FunctionalState NewState)
*函数功能:外部复位管脚使能
*入口参数:
FunctionalState:NewState:外部复位引脚功能使能/关闭选择
*出口参数:void
*****************************************************/
void OPTION_RST_PIN_Cmd(FunctionalState NewState)
{
  OPINX = 0XC1;

  if (NewState == DISABLE)
  {
    OPREG |= 0X08;
  }
  else
  {
    OPREG &= 0XF7;
  }
}
#endif

/*****************************************************
*函数名称:void OPTION_LVR_Init(LVR_Config_TypeDef LVR_Config)
*函数功能:LVR 电压选择
*入口参数:
LVR_Config_TypeDef:LVR_Config:选择LVR电压
*出口参数:void
*****************************************************/
void OPTION_LVR_Init(LVR_Config_TypeDef LVR_Config)
{
  OPINX = 0XC1;
  OPREG = OPREG & 0XF8 | LVR_Config;
}

/*****************************************************
*函数名称:void OPTION_ADC_VrefConfig(ADC_Vref_TypeDef ADC_Vref)
*函数功能:ADC 参考电压选择
*入口参数:
ADC_Vref_TypeDef:ADC_Vref:选择ADC参考电压
*出口参数:void
*****************************************************/
void OPTION_ADC_VrefConfig(ADC_Vref_TypeDef ADC_Vref)
{
  OPINX = 0xC2;

  if (ADC_Vref == ADC_VREF_2_048V)
  {
    OPREG &= 0x3f;
    OPREG |= 0x40; //选择参考内部电压2.048V。
  }

  if (ADC_Vref == ADC_VREF_1_024V)
  {
    OPREG &= 0x3f;
    OPREG |= 0x80; //选择参考内部电压1.024V。
  }

  if (ADC_Vref == ADC_VREF_VDD)
  {
    OPREG &= 0x3f; //选择参考电压VDD。
  }
}

/**************************************************
*函数名称:void OPTION_IAP_SetOperateRange(IAP_OperateRange_TypeDef IAP_OperateRange)
*函数功能:允许IAP操作的范围设置
*入口参数:
IAP_OperateRange_TypeDef:IAP_OperateRange:IAP操作范围
*出口参数:void
**************************************************/
void OPTION_IAP_SetOperateRange(IAP_OperateRange_TypeDef IAP_OperateRange)
{
  OPINX = 0xC2;
  OPREG = (OPREG & 0xF3) | IAP_OperateRange;
}

/**************************************************
*函数名称:void OPTION_JTG_Cmd(FunctionalState NewState)
*函数功能:JTAG/IO口切换控制
*入口参数:
FunctionalState:NewState:烧录口作为正常的IO使用（DISBLE）,烧录口作为tCK/tDIO使用（ENABLE）
*出口参数:void
**************************************************/
void OPTION_JTG_Cmd(FunctionalState NewState)
{
  OPINX = 0xC2;
  if (NewState == DISABLE)
  {
    OPREG |= 0X10;
  }
  else
  {
    OPREG &= 0XEF;
  }
}

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/