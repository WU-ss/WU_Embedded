//************************************************************
//  Copyright (c) 
//	�ļ�����:			sc95f_timer2.c
//	����:					��ԪӦ���Ŷ�
//	ģ�鹦��:			TIMER2�̼��⺯��C�ļ�
//  ����������:	2022��7��20��
// 	�汾: 				V1.10000
//  ˵��: 
//*************************************************************

#include "sc95f_timer2.h"

/**************************************************
*��������:void TIM2_DeInit(void)
*��������:TIMER2��ؼĴ�����λ����ʼֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void TIM2_DeInit()
{
  TXINX = 0x02; //TIMER2ѡ��
  TXCON = 0X00;
  TXMOD = 0X00;
  RCAPXH = 0X00;
  RCAPXL = 0X00;
  THX = 0X00;
  TLX = 0X00;
  IE1 &= 0X3F;
  IP1 &= 0X3F;
  ET2 = 0;
  IPT2 = 0;
}

/**************************************************
*��������:void TIM2_PrescalerSelection(TIM2_PresSel_TypeDef TIM2_PrescalerSelection)
*��������:TIMER2 Ԥ��Ƶѡ��
*��ڲ���:
TIM2_PresSel_TypeDef:TIM2_PrescalerSelection:Ԥ��Ƶѡ��
*���ڲ���:void
**************************************************/
void TIM2_PrescalerSelection(TIM2_PresSel_TypeDef TIM2_PrescalerSelection)
{
  TXINX = 0x02;

  if (TIM2_PrescalerSelection == TIM2_PRESSEL_FSYS_D12)
  {
    TXMOD &= 0X7F;
  }
  else if (TIM2_PrescalerSelection == TIM2_PRESSEL_FSYS_D1)
  {
    TXMOD |= 0X80;
  }
}

/**************************************************
*��������:void TIM2_TimeBaseInit(TIM2_CountMode_TypeDef TIM2_CountMode, TIM2_CountDirection_TypeDef TIM2_CountDirection)
*��������:TIM2�����������ú���
*��ڲ���:
TIM2_CountMode_TypeDef:TIM2_CountMode:����/��ʱģʽѡ��
TIM2_CountDirection_TypeDef:TIM2_CountDirection:��������ѡ��
*���ڲ���:void
**************************************************/
void TIM2_TimeBaseInit(TIM2_CountMode_TypeDef TIM2_CountMode,
                       TIM2_CountDirection_TypeDef TIM2_CountDirection)
{
  TXINX = 0x02;

  if (TIM2_CountMode == TIM2_MODE_TIMER)
  {
    TXCON &= 0XFD;
  }
  else if (TIM2_CountMode == TIM2_MODE_COUNTER)
  {
    TXCON |= 0X02;
  }
  if (TIM2_CountDirection == TIM2_COUNTDIRECTION_UP)
  {
    TXMOD &= 0XFE;
  }
  else if (TIM2_CountDirection == TIM2_COUNTDIRECTION_DOWN_UP)
  {
    TXMOD |= 0X01;
  }
}

/**************************************************
*��������:void TIM2_WorkMode0Config(uint16_t TIM2_SetCounter)
*��������:TIMER2����ģʽ0���ú���
*��ڲ���:
uint16_t:TIM2_SetCounter:���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM2_WorkMode0Config(uint16_t TIM2_SetCounter)
{
  TXINX = 0x02;
  CP = 1;
  TLX = TIM2_SetCounter % 256;
  THX = TIM2_SetCounter / 256;
}

/**************************************************
*��������:void TIM2_WorkMode1Config(uint16_t TIM2_SetCounter)
*��������:TIMER2����ģʽ1���ú���
*��ڲ���:
uint16_t:TIM2_SetCounter:���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM2_WorkMode1Config(uint16_t TIM2_SetCounter)
{
  TXINX = 0x02;
  RCAPXL = TIM2_SetCounter % 256;
  RCAPXH = TIM2_SetCounter / 256;

  TLX = RCAPXL;
  THX = RCAPXH;
}

/**************************************************
*��������:void TIM2_WorkMode3Config(uint16_t TIM2_SetCounter)
*��������:TIMER2����ģʽ3���ú���
*��ڲ���:
uint16_t:TIM2_SetCounter:���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM2_WorkMode3Config(uint16_t TIM2_SetCounter)
{
  TXINX = 0x02;
  RCAPXL = TIM2_SetCounter % 256;
  RCAPXH = TIM2_SetCounter / 256;
  TXMOD |= 0X02;
}
/**************************************************
*��������:void TIM2_WorkModeConfig(TIM2_WorkMode_TypeDef TIM2_WorkMode, uint16_t TIM2_SetCounter)
*��������:TIMER2����ģʽ���ú���
*��ڲ���:
TIM2_WorkMode_TypeDef:TIM2_WorkMode:TIMER2����ģʽѡ��
uint16_t:TIM2_SetCounter:TIMER2������ֵ����
*���ڲ���:void
**************************************************/
void TIM2_WorkModeConfig(TIM2_WorkMode_TypeDef TIM2_WorkMode, uint16_t TIM2_SetCounter)
{
  switch (TIM2_WorkMode)
  {
  case TIM2_WORK_MODE0:
    TIM2_WorkMode0Config(TIM2_SetCounter);
    break;

  case TIM2_WORK_MODE1:
    TIM2_WorkMode1Config(TIM2_SetCounter);
    break;

  case TIM2_WORK_MODE3:
    TIM2_WorkMode3Config(TIM2_SetCounter);
    break;

  default:
    break;
  }
}
/*****************************************************
*��������:void TIM2_SetEXEN2(FunctionalState NewState)
*��������:TIMER2_EXEN2���ú���
*��ڲ���:
FunctionalState:NewState:EXEN2ʹ��ѡ��
*���ڲ���:void
*****************************************************/
void TIM2_SetEXEN2(FunctionalState NewState)
{
  TXINX = 0x02;

  if (NewState == DISABLE)
  {
    EXENX = 0;
  }
  else
  {
    EXENX = 1;
  }
}

/*****************************************************
*��������:void TIM2_Cmd(FunctionalState NewState)
*��������:TIMER2���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void TIM2_Cmd(FunctionalState NewState)
{
  TXINX = 0x02;

  if (NewState == DISABLE)
  {
    TRX = 0;
  }
  else
  {
    TRX = 1;
  }
}

/*****************************************************
*��������:void TIM2_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:TIMER2
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void TIM2_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  TXINX = 0x02;

  if (NewState == DISABLE)
  {
    ET2 = 0;
  }
  else
  {
    ET2 = 1;
  }

  if (Priority == LOW)
  {
    IPT2 = 0;
  }
  else
  {
    IPT2 = 1;
  }
}

/*****************************************************
*��������:FlagStatus TIM2_GetFlagStatus(void)
*��������:���TIMER2�жϱ�־״̬
*��ڲ���:
TIM2_Flag_TypeDef:TIM2_Flag:TIMER2��־ѡ��
*���ڲ���:
FlagStatus:TIMER2�жϱ�־״̬
*****************************************************/
FlagStatus TIM2_GetFlagStatus(TIM2_Flag_TypeDef TIM2_Flag)
{
  FlagStatus status = RESET;
  TXINX = 0x02;

  if ((TIM2_Flag & TXCON) != (uint8_t)RESET)
  {
    status = SET;
  }
  else
  {
    status = RESET;
  }

  return status;
}

/*****************************************************
*��������:void TIMX_ClearFlag(void)
*��������:���TIMER2�жϱ�־״̬
*��ڲ���:
TIM2_Flag_TypeDef:TIM2_Flag:TIMER2��־ѡ��
*���ڲ���:void
*****************************************************/
void TIM2_ClearFlag(TIM2_Flag_TypeDef TIM2_Flag)
{
  TXINX = 0x02;
  TXCON &= (~TIM2_Flag);
}

/******************* (C) COPYRIGHT 2021 SinOne Microelectronics *****END OF FILE****/