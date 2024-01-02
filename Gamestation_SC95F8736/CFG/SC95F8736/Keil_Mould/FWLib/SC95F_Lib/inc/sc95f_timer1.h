//************************************************************
//  Copyright (c) 
//	�ļ�����:			sc95f_timer1.h
//	����:					��ԪӦ���Ŷ�
//	ģ�鹦��:			TIMER1�̼��⺯��H�ļ�
//  ����������:	2022��7��20��
// 	�汾: 				V1.10002
//  ˵��: 
//*************************************************************

#ifndef _sc95f_TIMER1_H_
#define _sc95f_TIMER1_H_

#include "sc95f.h"

typedef enum
{
  TIM1_PRESSEL_FSYS_D12 = ((uint8_t)0x00), //TIMER1����Դ����ϵͳʱ��12��Ƶ
  TIM1_PRESSEL_FSYS_D1 = ((uint8_t)0x01)   //TIMER1����Դ����ϵͳʱ��
} TIM1_PresSel_TypeDef;

typedef enum
{
  TIM1_MODE_TIMER = ((uint8_t)0x01),  //TIMER1����ʱ��
  TIM1_MODE_COUNTER = ((uint8_t)0x02) //TIMER1��������
} TIM1_CountMode_TypeDef;

typedef enum
{
  TIM1_WORK_MODE0 = ((uint8_t)0x00), //TIMER1ѡ����ģʽ0
  TIM1_WORK_MODE1 = ((uint8_t)0x01), //TIMER1ѡ����ģʽ1
  TIM1_WORK_MODE2 = ((uint8_t)0x02), //TIMER1ѡ����ģʽ2
} TIM1_WorkMode_TypeDef;

/*******************************�꺯��*******************************/
/*****************************************************
*��������:FlagStatus TIM1_GetFlagStatus(void)
*��������:���TIMER1�жϱ�־״̬
*��ڲ���:void
*���ڲ���:
FlagStatus:TIMER1�жϱ�־״̬
*****************************************************/
#define TIM1_GetFlagStatus() (TF1)

/*****************************************************
*��������:void TIM1_ClearFlag(void)
*��������:���TIMER1�жϱ�־״̬
*��ڲ���:void
*���ڲ���:void
*****************************************************/
#define TIM1_ClearFlag() (TF1 = 0)


void TIM1_DeInit(void);
void TIM1_TimeBaseInit(TIM1_PresSel_TypeDef TIM1_PrescalerSelection,
                       TIM1_CountMode_TypeDef TIM1_CountMode);
void TIM1_WorkMode0Config(uint16_t TIM1_SetCounter);
void TIM1_WorkMode1Config(uint16_t TIM1_SetCounter);
void TIM1_WorkMode2Config(uint8_t TIM1_SetCounter);
void TIM1_Mode0SetReloadCounter(uint16_t TIM1_SetCounter);
void TIM1_Mode1SetReloadCounter(uint16_t TIM1_SetCounter);
void TIM1_Cmd(FunctionalState NewState);
void TIM1_ITConfig(FunctionalState NewState, PriorityStatus Priority);
void TIM1_WorkModeConfig(TIM1_WorkMode_TypeDef TIM1_WorkMode, uint16_t TIM1_SetCounter);

#endif

/******************* (C) COPYRIGHT 2018 SinOne Microelectronics *****END OF FILE****/