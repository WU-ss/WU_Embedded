//************************************************************
//  Copyright (c) 
//	�ļ�����: 		sc95f_wdt.h
//	����:					��ԪӦ���Ŷ�
//	ģ�鹦��: 		BTM�̼��⺯��C�ļ�
//  ����������: 2022��3��23��
// 	�汾: 				V1.10002
//  ˵��: 
//*************************************************************

#ifndef _sc95f_WDT_H_
#define _sc95f_WDT_H_

#include "sc95f.h"

typedef enum
{
  WDT_OverflowTime_500MS = (uint8_t)0x00,   //���Ź����ʱ��Ϊ500MS
  WDT_OverflowTime_250MS = (uint8_t)0x01,   //���Ź����ʱ��Ϊ250MS
  WDT_OverflowTime_125MS = (uint8_t)0x02,   //���Ź����ʱ��Ϊ125MS
  WDT_OverflowTime_62_5MS = (uint8_t)0x03,  //���Ź����ʱ��Ϊ62.5MS
  WDT_OverflowTime_31_5MS = (uint8_t)0x04,  //���Ź����ʱ��Ϊ31.5MS
  WDT_OverflowTime_15_75MS = (uint8_t)0x05, //���Ź����ʱ��Ϊ15.75MS
  WDT_OverflowTime_7_88MS = (uint8_t)0x06,  //���Ź����ʱ��Ϊ7.88MS
  WDT_OverflowTime_3_94MS = (uint8_t)0x07   //���Ź����ʱ��Ϊ3.94MS
} WDT_OverflowTime_TypeDef;

/************************�꺯��************************/
/*****************************************************
*��������:void WDT_SetReload(void)
*��������:WDTι��
*��ڲ���:void
*���ڲ���:void
*****************************************************/
#define WDT_SetReload() SET_BIT(WDTCON,0x10)


void WDT_DeInit(void);
void WDT_Init(WDT_OverflowTime_TypeDef OverflowTime);
void WDT_Cmd(FunctionalState NewState);

#endif

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/