//************************************************************
//  Copyright (c) 
//	�ļ�����:			sc95f_timer1.c
//	����:					��ԪӦ���Ŷ�
//	ģ�鹦��:			TIMER1�̼��⺯��C�ļ�
//  ����������:	2022��7��20��
// 	�汾: 				V1.10001
//  ˵��: 
//*************************************************************

#include "sc95f_timer1.h"

/**************************************************
*��������:void TIM1_DeInit(void)
*��������:TIMER1��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void TIM1_DeInit(void)
{
  TMOD &= 0X0F;
  TCON &= 0X37;
  TMCON &= 0XFD;
  TH1 = 0X00;
  TL1 = 0X00;
  ET1 = 0;
  IPT1 = 0;
}

/**************************************************
*��������:void TIM1_TimeBaseInit(TIM1_PresSel_TypeDef TIM1_PrescalerSelection, TIM1_CountMode_TypeDef TIM1_CountMode)
*��������:TIMER1�����������ú���
*��ڲ���:
TIM1_PresSel_TypeDef:TIM1_PrescalerSelection:Ԥ��Ƶѡ��
TIM1_CountMode_TypeDef:TIM1_CountMode:����/��ʱģʽѡ��
*���ڲ���:void
**************************************************/
void TIM1_TimeBaseInit(TIM1_PresSel_TypeDef TIM1_PrescalerSelection,
                       TIM1_CountMode_TypeDef TIM1_CountMode)
{
  if(TIM1_PrescalerSelection == TIM1_PRESSEL_FSYS_D12)
  {
    TMCON &= 0xFD;
  }
  else if(TIM1_PrescalerSelection == TIM1_PRESSEL_FSYS_D1)
  {
    TMCON |= 0x02;
  }

  /************************************************************/
  if(TIM1_CountMode == TIM1_MODE_TIMER)
  {
    TMOD &= 0xBF;
  }
  else if(TIM1_CountMode == TIM1_MODE_COUNTER)
  {
    TMOD |= 0x40;
  }
}

/**************************************************
*��������:void TIM1_WorkMode0Config(uint16_t TIM1_SetCounter)
*��������:TIMER1����ģʽ0���ú���
*��ڲ���:
uint16_t:TIM1_SetCounter:���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM1_WorkMode0Config(uint16_t TIM1_SetCounter)
{
  TMOD &= 0XCF;
  TL1 = (uint8_t)TIM1_SetCounter;
  TH1 = (TIM1_SetCounter >> 5);
}

/**************************************************
*��������:void TIM1_WorkMode1Config(uint16_t TIM1_SetCounter)
*��������:TIMER1����ģʽ1���ú���
*��ڲ���:
uint16_t:TIM1_SetCounter:���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM1_WorkMode1Config(uint16_t TIM1_SetCounter)
{
  TMOD &= 0XCF;
  TMOD |= 0X10;
  TL1 = TIM1_SetCounter % 256;
  TH1 = TIM1_SetCounter / 256;
}

/**************************************************
*��������:void TIM1_WorkMode2Config(uint8_t TIM1_SetCounter)
*��������:TIMER1����ģʽ2���ú���
*��ڲ���:
uint8_t:TIM1_SetCounter:���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM1_WorkMode2Config(uint8_t TIM1_SetCounter)
{
  TMOD &= 0XCF;
  TMOD |= 0X20;
  TL1 = TIM1_SetCounter;
  TH1 = TIM1_SetCounter;
}

/**************************************************
*��������:void TIM1_WorkModeConfig(TIM1_WorkMode_TypeDef TIM1_WorkMode, uint16_t TIM1_SetCounter)
*��������:TIMER1����ģʽ���ú���
*��ڲ���:
TIM1_WorkMode_TypeDef:TIM1_WorkMode:TIMER1����ģʽѡ��
uint16_t:TIM1_SetCounter:TIMER1������ֵ����
*���ڲ���:void
**************************************************/
void TIM1_WorkModeConfig(TIM1_WorkMode_TypeDef TIM1_WorkMode, uint16_t TIM1_SetCounter)
{
  switch(TIM1_WorkMode)
  {
    case TIM1_WORK_MODE0:
      TIM1_WorkMode0Config(TIM1_SetCounter);
      break;

    case TIM1_WORK_MODE1:
      TIM1_WorkMode1Config(TIM1_SetCounter);
      break;

    case TIM1_WORK_MODE2:
      TIM1_WorkMode2Config(TIM1_SetCounter);
      break;

    default:
      break;
  }
}

/**************************************************
*��������:void TIM1_Mode0SetReloadCounter(uint16_t TIM1_SetCounter)
*��������:TIMER1����ģʽ0��ֵ���غ���
*��ڲ���:
uint16_t:TIM1_SetCounter:����TIMER1����ֵ
*���ڲ���:void
**************************************************/
void TIM1_Mode0SetReloadCounter(uint16_t TIM1_SetCounter)
{
  TL1 = (uint8_t)TIM1_SetCounter;
  TH1 = (TIM1_SetCounter >> 5);
}

/**************************************************
*��������:void TIM1_Mode1SetReloadCounter(uint16_t TIM1_SetCounter)
*��������:TIMER1����ģʽ1��ֵ���غ���
*��ڲ���:
uint16_t:TIM1_SetCounter:����TIMER1����ֵ
*���ڲ���:void
**************************************************/
void TIM1_Mode1SetReloadCounter(uint16_t TIM1_SetCounter)
{
  TL1 = TIM1_SetCounter % 256;
  TH1 = TIM1_SetCounter / 256;
}

/*****************************************************
*��������:void TIM1_Cmd(FunctionalState NewState)
*��������:TIMER1���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void TIM1_Cmd(FunctionalState NewState)
{
  if(NewState == DISABLE)
  {
    TR1 = 0;
  }
  else
  {
    TR1 = 1;
  }
}

/*****************************************************
*��������:void TIM1_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:TIMER1�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void TIM1_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  if(NewState == DISABLE)
  {
    ET1 = 0;
  }
  else
  {
    ET1 = 1;
  }

  /************************************************************/
  if(Priority == LOW)
  {
    IPT1 = 0;
  }
  else
  {
    IPT1 = 1;
  }
}


/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/