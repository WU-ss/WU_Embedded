//************************************************************
//  Copyright (c) 
//	�ļ�����:			sc95f_mdu.c
//	����:
//	ģ�鹦��:			MDU�̼��⺯��C�ļ�
//  ����������:	2020/8/13
// 	�汾: 				V1.0
//  ˵��: 				���ļ���������SC95Fϵ��оƬ
//*************************************************************

#include "sc95f_mdu.h"

/**************************************************
*��������:void MDU_DeInit(void)
*��������:MDU��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
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
*��������:void MDU_MultiplicationConfig(uint16_t Multiplicand, uint16_t Multiplier)
*��������:MDU�˷��������ú���
*��ڲ���:
uint16_t:Multiplicand:������
uint16_t:Multiplier:����
*���ڲ���:void
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
*��������:void MDU_DivisionConfig(uint32_t Dividend, uint16_t Divisor)
*��������:MDU�����������ú���
*��ڲ���:
uint32_t:Dividend:������
uint16_t:Divisor:����
*���ڲ���:void
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
*��������:void MDU_StartOperation(void)
*��������:MDU����һ������
*��ڲ���:void
*���ڲ���:void
**************************************************/
void MDU_StartOperation(void)
{
  OPERCON |= 0x80;

  while(OPERCON & 0x80);
}

/**************************************************
*��������:uint32_t MDU_GetProduct(void)
*��������:��ȡ�˻�
*��ڲ���:void
*���ڲ���:
uint32_t:�˻�
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
*��������:uint32_t MDU_GetQuotient(void)
*��������:��ȡ��
*��ڲ���:void
*���ڲ���:
uint32_t:��
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
*��������:uint16_t MDU_GetRemainder(void)
*��������:��ȡ����
*��ڲ���:void
*���ڲ���:
uint16_t:����
**************************************************/
uint16_t MDU_GetRemainder(void)
{
  uint16_t MDU_RemainderTemp;
  MDU_RemainderTemp = EXBH * 256 + EXBL;
  return MDU_RemainderTemp;
}

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/