//************************************************************
//  Copyright (c) 
//	�ļ�����	: sc95f_timerx.c
//	����		:
//	ģ�鹦��	: TIMER3�̼��⺯��C�ļ�
//  ����������: 2022/01/24
// 	�汾		: V1.10001
//  ˵��        :���ļ���������SC95Fxx1x��SC95Fxx2xϵ��оƬ
//*************************************************************

#include "sc95f_timer3.h"

/**************************************************
*��������:void TIMX_DeInit(void)
*��������:TIMER3��ؼĴ�����λ����ʼֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void TIM3_DeInit()
{
  TXINX = 0x03;    //TIMER3 ѡ��
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
*��������:void TIM3_PrescalerSelection(TIMX_TimerSelect_TypeDef TIMX_TimerSelect, TIMX_PresSel_TypeDef TIMX_PrescalerSelection)
*��������:TIMER3 Ԥ��Ƶѡ��
*��ڲ���:
TIM3_PresSel_TypeDef:TIM3_PrescalerSelection:Ԥ��Ƶѡ��
*���ڲ���:void
**************************************************/
void TIM3_PrescalerSelection(TIM3_PresSel_TypeDef TIM3_PrescalerSelection)
{
  TXINX = 0x03;

  if(TIM3_PrescalerSelection == TIM3_PRESSEL_FSYS_D12)
  {
    TXMOD &= 0X7F;
  }
  else
    if(TIM3_PrescalerSelection == TIM3_PRESSEL_FSYS_D1)
    {
      TXMOD |= 0X80;
    }
}

/**************************************************
*��������:void TIM3_WorkMode1Config(uint16_t TIM3_SetCounter)
*��������:TIMER3����ģʽ1���ú���
*��ڲ���:
uint16_t TIM3_SetCounter	���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM3_WorkMode1Config(uint16_t TIM3_SetCounter)
{
  TXINX = 0x03;
  RCAPXL = TIM3_SetCounter % 256;
  RCAPXH = TIM3_SetCounter / 256;

  TLX = RCAPXL;
  THX = RCAPXH;
}

/*****************************************************
*��������:void TIM3_Cmd(FunctionalState NewState)
*��������:TIMER3���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void TIM3_Cmd(FunctionalState NewState)
{
  TXINX = 0x03;

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
*��������:void TIM3_ITConfig(TIM3_TimerSelect_TypeDef TIM3_TimerSelect, FunctionalState NewState, PriorityStatus Priority)
*��������:TIMER3�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void TIM3_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  TXINX = 0x03;

  if(NewState == DISABLE)
  {
    IE1 &= 0XBF;
  }
  else
  {
    IE1 |= 0X40;
  }

  if(Priority == LOW)
  {
    IP1 &= 0XBF;
  }
  else
  {
    IP1 |= 0X40;
  }
}

/*****************************************************
*��������:FlagStatus TIM3_GetFlagStatus(void)
*��������:���TIMER3�жϱ�־״̬
*��ڲ���:
TIM3_Flag_TypeDef:TIM3_Flag:TIMER3��־ѡ��
*���ڲ���:
FlagStatus:TIMER3�жϱ�־״̬
*****************************************************/
FlagStatus TIM3_GetFlagStatus(TIM3_Flag_TypeDef TIM3_Flag)
{
  FlagStatus status = RESET;
  TXINX = 0x03;

  if((TIM3_Flag & TXCON) != (uint8_t)RESET)
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
*��������:void TIM3_ClearFlag(TIM3_Flag_TypeDef TIM3_Flag)
*��������:���TIMER3�жϱ�־״̬
*��ڲ���:
TIM3_Flag_TypeDef:TIM3_Flag:TIMER3��־ѡ��
*���ڲ���:void
*****************************************************/
void TIM3_ClearFlag(TIM3_Flag_TypeDef TIM3_Flag)
{
  TXINX = 0x03;
  TXCON &= (~TIM3_Flag);
}

#if defined (SC95F8x2x) || defined (SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)
/**************************************************
*��������:void TIM3_TimeBaseInit(TIM3_CountMode_TypeDef TIM3_CountMode, TIM3_CountDirection_TypeDef TIM3_CountDirection)
*��������:TIM3�����������ú���
*��ڲ���:
TIM3_CountMode_TypeDef:TIM3_CountMode:����/��ʱģʽѡ��
TIM3_CountDirection_TypeDef:TIM3_CountDirection:��������ѡ��
*���ڲ���:void
**************************************************/
void TIM3_TimeBaseInit(TIM3_CountMode_TypeDef TIM3_CountMode,
                       TIM3_CountDirection_TypeDef TIM3_CountDirection)
{
  TXINX = 0x03;

  if(TIM3_CountMode == TIM3_MODE_TIMER)
  {
    TXCON &= 0XFD;
  }
  else
    if(TIM3_CountMode == TIM3_MODE_COUNTER)
    {
      TXCON |= 0X02;
    }

  /************************************************************/
  if(TIM3_CountDirection == TIM3_COUNTDIRECTION_UP)
  {
    TXMOD &= 0XFE;
  }
  else
    if(TIM3_CountDirection == TIM3_COUNTDIRECTION_DOWN_UP)
    {
      TXMOD |= 0X01;
    }
}

/**************************************************
*��������:void TIM3_WorkMode0Config(uint16_t TIM3_SetCounter)
*��������:TIMER3����ģʽ0���ú���
*��ڲ���:
uint16_t:TIM3_SetCounter:���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM3_WorkMode0Config(uint16_t TIM3_SetCounter)
{
  TXINX = 0x03;
	CP = 1;
  TLX = TIM3_SetCounter % 256;
  THX = TIM3_SetCounter / 256;
}
/**************************************************
*��������:void TIM3_WorkMode3Config(uint16_t TIM3_SetCounter)
*��������:TIMER3����ģʽ3���ú���
*��ڲ���:
uint16_t:TIM3_SetCounter:���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM3_WorkMode3Config(uint16_t TIM3_SetCounter)
{
  TXINX = 0x03;
  RCAPXL = TIM3_SetCounter % 256;
  RCAPXH = TIM3_SetCounter / 256;
  TXMOD |= 0X02;
}
/**************************************************
*��������:void TIM3_WorkModeConfig(TIM3_WorkMode_TypeDef TIM3_WorkMode, uint16_t TIM3_SetCounter)
*��������:TIMER3����ģʽ���ú���
*��ڲ���:
TIM3_WorkMode_TypeDef:TIM3_WorkMode:TIMER3����ģʽѡ��
uint16_t:TIM3_SetCounter:TIMER3������ֵ����
*���ڲ���:void
**************************************************/
void TIM3_WorkModeConfig(TIM3_WorkMode_TypeDef TIM3_WorkMode, uint16_t TIM3_SetCounter)
{
  switch (TIM3_WorkMode)
  {
    case TIM3_WORK_MODE0:
      TIM3_WorkMode0Config(TIM3_SetCounter);
      break;

    case TIM3_WORK_MODE1:
      TIM3_WorkMode1Config(TIM3_SetCounter);
      break;

    case TIM3_WORK_MODE3:
      TIM3_WorkMode3Config(TIM3_SetCounter);
      break;

    default:
      break;
  }
}
/*****************************************************
*��������:void TIM3_SetEXEN3(FunctionalState NewState)
*��������:TIMER3_EXEN3���ú���
*��ڲ���:
FunctionalState:NewState:EXEN3ʹ��ѡ��
*���ڲ���:void
*****************************************************/
void TIM3_SetEXEN3(FunctionalState NewState)
{
  TXINX = 0x03;

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