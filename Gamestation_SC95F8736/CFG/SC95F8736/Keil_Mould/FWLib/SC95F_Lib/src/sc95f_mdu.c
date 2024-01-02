//************************************************************
//  Copyright (c) 
//	文件名称:			sc95f_mdu.c
//	作者:
//	模块功能:			MDU固件库函数C文件
//  最后更正日期:	2020/8/13
// 	版本: 				V1.0
//  说明: 				该文件仅适用于SC95F系列芯片
//*************************************************************

#include "sc95f_mdu.h"

/**************************************************
*函数名称:void MDU_DeInit(void)
*函数功能:MDU相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
**************************************************/
void MDU_DeInit(void)
{
  OPERCON &= 0X3F;
  EXA0 = 0X00;
  EXA1 = 0X00;
  EXA2 = 0X00;
  EXA3 = 0X00;
  EXBL = 0X00;
  EXBH = 0X00;
}

/**************************************************
*函数名称:void MDU_MultiplicationConfig(uint16_t Multiplicand, uint16_t Multiplier)
*函数功能:MDU乘法运算配置函数
*入口参数:
uint16_t:Multiplicand:被乘数
uint16_t:Multiplier:乘数
*出口参数:void
**************************************************/
void MDU_MultiplicationConfig(uint16_t Multiplicand, uint16_t Multiplier)
{
  OPERCON &= 0XBF;
  EXBL = Multiplier;
  EXBH = Multiplier >> 8;
  EXA0 = Multiplicand;
  EXA1 = Multiplicand >> 8;
}

/**************************************************
*函数名称:void MDU_DivisionConfig(uint32_t Dividend, uint16_t Divisor)
*函数功能:MDU除法运算配置函数
*入口参数:
uint32_t:Dividend:被除数
uint16_t:Divisor:除数
*出口参数:void
**************************************************/
void MDU_DivisionConfig(uint32_t Dividend, uint16_t Divisor)
{
  MDU_Temp_Union MDU_DivisionTemp;
  MDU_DivisionTemp.MDU_Temp = Dividend;

  OPERCON |= 0X40;
  EXA0 = MDU_DivisionTemp.MDU_EXAxReg.MDU_EXA0Reg;
  EXA1 = MDU_DivisionTemp.MDU_EXAxReg.MDU_EXA1Reg;
  EXA2 = MDU_DivisionTemp.MDU_EXAxReg.MDU_EXA2Reg;
  EXA3 = MDU_DivisionTemp.MDU_EXAxReg.MDU_EXA3Reg;
  EXBL = Divisor;
  EXBH = Divisor >> 8;
}

/**************************************************
*函数名称:void MDU_StartOperation(void)
*函数功能:MDU启动一次运算
*入口参数:void
*出口参数:void
**************************************************/
void MDU_StartOperation(void)
{
  OPERCON |= 0x80;

  while(OPERCON & 0x80);
}

/**************************************************
*函数名称:uint32_t MDU_GetProduct(void)
*函数功能:获取乘积
*入口参数:void
*出口参数:
uint32_t:乘积
**************************************************/
uint32_t MDU_GetProduct(void)
{
  MDU_Temp_Union MDU_ProductTemp;
  MDU_ProductTemp.MDU_EXAxReg.MDU_EXA0Reg = EXA0;
  MDU_ProductTemp.MDU_EXAxReg.MDU_EXA1Reg = EXA1;
  MDU_ProductTemp.MDU_EXAxReg.MDU_EXA2Reg = EXA2;
  MDU_ProductTemp.MDU_EXAxReg.MDU_EXA3Reg = EXA3;
  return MDU_ProductTemp.MDU_Temp;
}

/**************************************************
*函数名称:uint32_t MDU_GetQuotient(void)
*函数功能:获取商
*入口参数:void
*出口参数:
uint32_t:商
**************************************************/
uint32_t MDU_GetQuotient(void)
{
  MDU_Temp_Union MDU_QuotientTemp;
  MDU_QuotientTemp.MDU_EXAxReg.MDU_EXA0Reg = EXA0;
  MDU_QuotientTemp.MDU_EXAxReg.MDU_EXA1Reg = EXA1;
  MDU_QuotientTemp.MDU_EXAxReg.MDU_EXA2Reg = EXA2;
  MDU_QuotientTemp.MDU_EXAxReg.MDU_EXA3Reg = EXA3;
  return MDU_QuotientTemp.MDU_Temp;
}

/**************************************************
*函数名称:uint16_t MDU_GetRemainder(void)
*函数功能:获取余数
*入口参数:void
*出口参数:
uint16_t:余数
**************************************************/
uint16_t MDU_GetRemainder(void)
{
  uint16_t MDU_RemainderTemp;
  MDU_RemainderTemp = EXBH * 256 + EXBL;
  return MDU_RemainderTemp;
}

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/