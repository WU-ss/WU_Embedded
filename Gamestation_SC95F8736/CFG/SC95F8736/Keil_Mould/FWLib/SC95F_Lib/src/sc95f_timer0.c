//************************************************************
//  Copyright (c) 
//	�ļ�����:			sc95f_timer0.c
//	����:					��ԪӦ���Ŷ�
//	ģ�鹦��:			TIMER0�̼��⺯��C�ļ�
//  ����������:	2022��7��20��
// 	�汾: 				V1.10001
//  ˵��: 
//*************************************************************

#include "sc95f_timer0.h"

/**************************************************
*��������:void TIM0_DeInit(void)
*��������:TIMER0��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void TIM0_DeInit(void)
{
  TMOD &= 0XF0;
  TCON &= 0XCD;
  TMCON &= 0XFE;
  TH0 = 0X00;
  TL0 = 0X00;
  ET0 = 0;
  IPT0 = 0;
}

/**************************************************
*��������:void TIM0_TimeBaseInit(TIM0_PresSel_TypeDef TIM0_PrescalerSelection, TIM0_CountMode_TypeDef TIM0_CountMode)
*��������:TIMER0�����������ú���
*��ڲ���:
TIM0_PresSel_TypeDef:TIM0_PrescalerSelection:Ԥ��Ƶѡ��
TIM0_CountMode_TypeDef:TIM0_CountMode:����/��ʱģʽѡ��
*���ڲ���:void
**************************************************/
void TIM0_TimeBaseInit(TIM0_PresSel_TypeDef TIM0_PrescalerSelection,
                       TIM0_CountMode_TypeDef TIM0_CountMode)
{
  if (TIM0_PrescalerSelection == TIM0_PRESSEL_FSYS_D12)
  {
    TMCON &= 0XFE;
  }
  else if (TIM0_PrescalerSelection == TIM0_PRESSEL_FSYS_D1)
  {
    TMCON |= 0X01;
  }

  /************************************************************/
  if (TIM0_CountMode == TIM0_MODE_TIMER)
  {
    TMOD &= 0xFB;
  }
  else if (TIM0_CountMode == TIM0_MODE_COUNTER)
  {
    TMOD |= 0x04;
  }
}

/**************************************************
*��������:void TIM0_WorkMode0Config(uint16_t TIM0_SetCounter)
*��������:TIMER0����ģʽ0���ú���
*��ڲ���:
uint16_t:TIM0_SetCounter:���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM0_WorkMode0Config(uint16_t TIM0_SetCounter)
{
  TMOD &= 0XFC;
  TL0 = (uint8_t)TIM0_SetCounter;
  TH0 = (TIM0_SetCounter >> 5);
}

/**************************************************
*��������:void TIM0_WorkMode1Config(uint16_t TIM0_SetCounter)
*��������:TIMER0����ģʽ1���ú���
*��ڲ���:
uint16_t:TIM0_SetCounter:���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM0_WorkMode1Config(uint16_t TIM0_SetCounter)
{
  TMOD &= 0XFC;
  TMOD |= 0X01;
  TL0 = TIM0_SetCounter % 256;
  TH0 = TIM0_SetCounter / 256;
}

/**************************************************
*��������:void TIM0_WorkMode2Config(uint8_t TIM0_SetCounter)
*��������:TIMER0����ģʽ2���ú���
*��ڲ���:
uint8_t:TIM0_SetCounter:���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM0_WorkMode2Config(uint8_t TIM0_SetCounter)
{
  TMOD &= 0XFC;
  TMOD |= 0X02;
  TL0 = TIM0_SetCounter;
  TH0 = TIM0_SetCounter;
}

/**************************************************
*��������:void TIM0_WorkModeConfig(TIM0_WorkMode_TypeDef TIM0_WorkMode, uint16_t TIM0_SetCounter1, uint16_t TIM0_SetCounter2)
*��������:TIMER0����ģʽ���ú���
*��ڲ���:
TIM0_WorkMode:TypeDef TIM0_WorkMode:TIMER0����ģʽѡ��
uint16_t:TIM0_SetCounter1:TIMER0������ֵ����1
uint16_t:TIM0_SetCounter2:TIMER0������ֵ����2
*���ڲ���:void
**************************************************/
void TIM0_WorkModeConfig(TIM0_WorkMode_TypeDef TIM0_WorkMode, uint16_t TIM0_SetCounter1,
                         uint16_t TIM0_SetCounter2)
{
  switch (TIM0_WorkMode)
  {
  case TIM0_WORK_MODE0:
    TIM0_WorkMode0Config(TIM0_SetCounter1);
    break;

  case TIM0_WORK_MODE1:
    TIM0_WorkMode1Config(TIM0_SetCounter1);
    break;

  case TIM0_WORK_MODE2:
    TIM0_WorkMode2Config(TIM0_SetCounter1);
    break;

  case TIM0_WORK_MODE3:
    TIM0_WorkMode3Config(TIM0_SetCounter1, TIM0_SetCounter2);
    break;

  default:
    break;
  }
}

/**************************************************
*��������:void TIM0_WorkMode3Config(uint8_t TIM0_SetCounter, uint8_t TIM1_SetCounter)
*��������:TIMER0����ģʽ3���ú���
*��ڲ���:
uint8_t:TIM0_SetCounter:����TIMER0_TL0������ֵ
uint8_t:TIM1_SetCounter:����TIMER0_TH0������ֵ
*���ڲ���:void
**************************************************/
void TIM0_WorkMode3Config(uint8_t TIM0_SetCounter, uint8_t TIM1_SetCounter)
{
  TMOD |= 0X03;
  TL0 = TIM0_SetCounter;
  TH0 = TIM1_SetCounter;
}

/**************************************************
*��������:void TIM0_Mode0SetReloadCounter(uint16_t TIM0_SetCounter)
*��������:TIMER0����ģʽ0��ֵ���غ���
*��ڲ���:
uint16_t:TIM0_SetCounter:����TIMER0����ֵ
*���ڲ���:void
**************************************************/
void TIM0_Mode0SetReloadCounter(uint16_t TIM0_SetCounter)
{
  TL0 = (uint8_t)TIM0_SetCounter;
  TH0 = (TIM0_SetCounter >> 5);
}

/**************************************************
*��������:void TIM0_Mode1SetReloadCounter(uint16_t TIM0_SetCounter)
*��������:TIMER0����ģʽ1��ֵ���غ���
*��ڲ���:
uint16_t:TIM0_SetCounter:����TIMER0����ֵ
*���ڲ���:void
**************************************************/
void TIM0_Mode1SetReloadCounter(uint16_t TIM0_SetCounter)
{
  TL0 = TIM0_SetCounter % 256;
  TH0 = TIM0_SetCounter / 256;
}

/*****************************************************
*��������:void TIM0_Cmd(FunctionalState NewState)
*��������:TIMER0���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void TIM0_Cmd(FunctionalState NewState)
{
  if (NewState == DISABLE)
  {
    TR0 = 0;
  }
  else
  {
    TR0 = 1;
  }
}

/**************************************************
*��������:void TIM0_SetTL0Counter(uint8_t TIM0_SetCounter)
*��������:TIMER0 TL0��ֵ����
*��ڲ���:
uint8_t:TIM0_SetCounter:����TL0
*���ڲ���:void
**************************************************/
void TIM0_SetTL0Counter(uint8_t TIM0_SetCounter)
{
  TL0 = TIM0_SetCounter;
}

/**************************************************
*��������:void TIM0_SetTH0Counter(uint8_t TIM0_SetCounter)
*��������:TIMER0 TH0��ֵ����
*��ڲ���:
uint8_t:TIM0_SetCounter:����TH0
*���ڲ���:void
**************************************************/
void TIM0_SetTH0Counter(uint8_t TIM0_SetCounter)
{
  TH0 = TIM0_SetCounter;
}

/*****************************************************
*��������:void TIM0_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:TIMER0�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void TIM0_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  if (NewState == DISABLE)
  {
    ET0 = 0;
  }
  else
  {
    ET0 = 1;
  }

  /************************************************************/
  if (Priority == LOW)
  {
    IPT0 = 0;
  }
  else
  {
    IPT0 = 1;
  }
}


/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/