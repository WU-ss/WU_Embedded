//************************************************************
//  Copyright (c) 
//	�ļ�����	: sc95f_timer4.c
//	����		:
//	ģ�鹦��	: TIMER4�̼��⺯��C�ļ�
//  ����������:	2022��7��22��
// 	�汾:					V1.10004
//  ˵��        :���ļ���������SC95Fϵ��оƬ
//*************************************************************

#include "sc95f_timer4.h"

/**************************************************
*��������:void TIM4_DeInit(void)
*��������:TIMER4��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void TIM4_DeInit()
{
  TXINX = 0x04; //TIMER4 ѡ��
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
*��������:void TIM4_PrescalerSelection(TIM4_PresSel_TypeDef TIM4_PrescalerSelection)
*��������:TIMER4 Ԥ��Ƶѡ��
*��ڲ���:
TIM4_PresSel_TypeDef:TIM4_PrescalerSelection:Ԥ��Ƶѡ��
*���ڲ���:void
**************************************************/
void TIM4_PrescalerSelection(TIM4_PresSel_TypeDef TIM4_PrescalerSelection)
{
  TXINX = 0x04;

  if (TIM4_PrescalerSelection == TIM4_PRESSEL_FSYS_D12)
  {
    TXMOD &= 0X7F;
  }
  else if (TIM4_PrescalerSelection == TIM4_PRESSEL_FSYS_D1)
  {
    TXMOD |= 0X80;
  }
}

/**************************************************
*��������:void TIM4_WorkMode1Config(uint16_t TIM4_SetCounter)
*��������:TIMER4����ģʽ1���ú���
*��ڲ���:
uint16_t:TIM4_SetCounter:���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM4_WorkMode1Config(uint16_t TIM4_SetCounter)
{
  TXINX = 0x04;
  RCAPXL = TIM4_SetCounter % 256;
  RCAPXH = TIM4_SetCounter / 256;

  TLX = RCAPXL;
  THX = RCAPXH;
}

/*****************************************************
*��������:void TIM4_Cmd(FunctionalState NewState)
*��������:TIMER4���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void TIM4_Cmd(FunctionalState NewState)
{
  TXINX = 0x04;

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
*��������:void TIMX_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:TIMER4�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void TIM4_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  TXINX = 0x04;

  if (NewState == DISABLE)
  {
    IE1 &= 0X7F;
  }
  else
  {
    IE1 |= 0X80;
  }

  if (Priority == LOW)
  {
    IP1 &= 0X7F;
  }
  else
  {
    IP1 |= 0X80;
  }
}

/*****************************************************
*��������:FlagStatus TIM4_GetFlagStatus(TIM4_Flag_TypeDef TIM4_Flag)
*��������:���TIMER4�жϱ�־״̬
*��ڲ���:
TIM4_Flag_TypeDef:TIM4_Flag:TIMER4��־ѡ��
*���ڲ���:
FlagStatus:TIMER4�жϱ�־״̬
*****************************************************/
FlagStatus TIM4_GetFlagStatus(TIM4_Flag_TypeDef TIM4_Flag)
{
  FlagStatus status = RESET;
  TXINX = 0x04;

  if ((TIM4_Flag & TXCON) != (uint8_t)RESET)
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
*��������:void TIM4_ClearFlag(TIM4_Flag_TypeDef TIM4_Flag)
*��������:���TIMER4�жϱ�־״̬
*��ڲ���:
TIM4_Flag_TypeDef:TIM4_Flag:TIMER4��־ѡ��
*���ڲ���:void
*****************************************************/
void TIM4_ClearFlag(TIM4_Flag_TypeDef TIM4_Flag)
{
  TXINX = 0x04;
  TXCON &= (~TIM4_Flag);
}

#if defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)
/**************************************************
*��������:void TIM4_TimeBaseInit(TIM4_CountMode_TypeDef TIM4_CountMode, TIM4_CountDirection_TypeDef TIM4_CountDirection)
*��������:TIM4�����������ú���
*��ڲ���:
TIM4_CountMode_TypeDef:TIM4_CountMode:����/��ʱģʽѡ��
TIM4_CountDirection_TypeDef:TIM4_CountDirection:��������ѡ��
*���ڲ���:void
**************************************************/
void TIM4_TimeBaseInit(TIM4_CountMode_TypeDef TIM4_CountMode,
                       TIM4_CountDirection_TypeDef TIM4_CountDirection)
{
  TXINX = 0x04;

  if (TIM4_CountMode == TIM4_MODE_TIMER)
  {
    TXCON &= 0XFD;
  }
  else if (TIM4_CountMode == TIM4_MODE_COUNTER)
  {
    TXCON |= 0X02;
  }

  /************************************************************/
  if (TIM4_CountDirection == TIM4_COUNTDIRECTION_UP)
  {
    TXMOD &= 0XFE;
  }
  else if (TIM4_CountDirection == TIM4_COUNTDIRECTION_DOWN_UP)
  {
    TXMOD |= 0X01;
  }
}

/**************************************************
*��������:void TIM4_WorkMode0Config(uint16_t TIM4_SetCounter)
*��������:TIMER4����ģʽ0���ú���
*��ڲ���:
uint16_t:TIM4_SetCounter:���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM4_WorkMode0Config(uint16_t TIM4_SetCounter)
{
  TXINX = 0x04;
  CP = 1;
  TLX = TIM4_SetCounter % 256;
  THX = TIM4_SetCounter / 256;
}

/**************************************************
*��������:void TIM4_WorkMode3Config(uint16_t TIM4_SetCounter)
*��������:TIMER2����ģʽ3���ú���
*��ڲ���:
uint16_t:TIM2_SetCounter:���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM4_WorkMode3Config(uint16_t TIM4_SetCounter)
{
  TXINX = 0x04;
  RCAPXL = TIM4_SetCounter % 256;
  RCAPXH = TIM4_SetCounter / 256;
  TXMOD |= 0X02;
}

/**************************************************
*��������:void TIM4_WorkModeConfig(TIM4_WorkMode_TypeDef TIM4_WorkMode, uint16_t TIM4_SetCounter)
*��������:TIMER4����ģʽ���ú���
*��ڲ���:
TIM4_WorkMode_TypeDef:TIM4_WorkMode:TIMER2����ģʽѡ��
uint16_t:TIM4_SetCounter:TIMER2������ֵ����
*���ڲ���:void
**************************************************/
void TIM4_WorkModeConfig(TIM4_WorkMode_TypeDef TIM4_WorkMode, uint16_t TIM4_SetCounter)
{
  switch (TIM4_WorkMode)
  {
  case TIM4_WORK_MODE0:
    TIM4_WorkMode0Config(TIM4_SetCounter);
    break;

  case TIM4_WORK_MODE1:
    TIM4_WorkMode1Config(TIM4_SetCounter);
    break;

  case TIM4_WORK_MODE3:
    TIM4_WorkMode3Config(TIM4_SetCounter);
    break;

  default:
    break;
  }
}

/*****************************************************
*��������:void TIM4_SetEXEN4(FunctionalState NewState)
*��������:TIMER4_EXEN4���ú���
*��ڲ���:
FunctionalState:NewState:EXEN4ʹ��ѡ��
*���ڲ���:void
*****************************************************/
void TIM4_SetEXEN4(FunctionalState NewState)
{
  TXINX = 0x04;

  if (NewState == DISABLE)
  {
    EXENX = 0;
  }
  else
  {
    EXENX = 1;
  }
}

#endif

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/