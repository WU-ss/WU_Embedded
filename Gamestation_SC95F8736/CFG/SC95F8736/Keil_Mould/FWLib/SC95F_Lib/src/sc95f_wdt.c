//************************************************************
//  Copyright (c) 
//	�ļ�����: 		sc95f_wdt.c
//	����:					��ԪӦ���Ŷ�
//	ģ�鹦��: 		BTM�̼��⺯��C�ļ�
//  ����������: 2022��3��23��
// 	�汾: 				V1.10001
//  ˵��: 
//*************************************************************

#include "sc95f_wdt.h"
/**************************************************
*��������:void WDT_DeInit(void)
*��������:WDT��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void WDT_DeInit(void)
{
    WDTCON = 0X00;
}

/**************************************************
*��������:void WDT_Init(WDT_OverflowTime_TypeDef OverflowTime)
*��������:WDT��ʼ�����ú���
*��ڲ���:
WDT_OverflowTime_TypeDef:OverflowTime:WDT���ʱ��ѡ��
*���ڲ���:void
**************************************************/
void WDT_Init(WDT_OverflowTime_TypeDef OverflowTime)
{
    WDTCON = (WDTCON & 0XF8) | OverflowTime;
}

/*****************************************************
*��������:void WDT_Cmd(FunctionalState NewState)
*��������:WDT���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:���Ź���������/�ر�ѡ��
*���ڲ���:void
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