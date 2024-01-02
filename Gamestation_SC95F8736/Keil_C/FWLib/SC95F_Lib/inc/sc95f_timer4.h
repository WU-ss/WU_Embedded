//************************************************************
//  Copyright (c) 
//	�ļ�����	: sc95f_timerx.h
//	����		:
//	ģ�鹦��	: TIMER4�̼��⺯��ͷ�ļ�
//  ����������:	2022��7��22��
// 	�汾:					V1.10003
//  ˵��        :���ļ���������SC95Fϵ��оƬ
//*************************************************************

#ifndef _sc95f_TIMER4_H_
#define _sc95f_TIMER4_H_

#include "sc95f.H"

typedef enum
{
  TIM4_PRESSEL_FSYS_D12 = ((uint8_t)0x00), //TIMER4����Դ����ϵͳʱ��12��Ƶ
  TIM4_PRESSEL_FSYS_D1 = ((uint8_t)0x01)   //TIMER4����Դ����ϵͳʱ��
} TIM4_PresSel_TypeDef;

#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx)
typedef enum
{
  TIM4_FLAG_TF4 = (uint8_t)0x80, //�жϱ�־λTF4
} TIM4_Flag_TypeDef;
#endif

#if defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB)  || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)
typedef enum
{
  TIM4_MODE_TIMER = ((uint8_t)0x01),  //TIMER2����ʱ��
  TIM4_MODE_COUNTER = ((uint8_t)0x02) //TIMER2��������
} TIM4_CountMode_TypeDef;

typedef enum
{
  TIM4_COUNTDIRECTION_UP = ((uint8_t)0x00),     //���ϼ���ģʽ
  TIM4_COUNTDIRECTION_DOWN_UP = ((uint8_t)0x10) //����/���¼���ģʽ
} TIM4_CountDirection_TypeDef;

typedef enum
{
  TIM4_FLAG_TF4 = (uint8_t)0x80, //�жϱ�־λTF4
  TIM4_FLAG_EXF4 = (uint8_t)0x40 //�жϱ�־λEXF4
} TIM4_Flag_TypeDef;

typedef enum
{
  TIM4_WORK_MODE0 = ((uint8_t)0x00), //TIMER4ѡ����ģʽ0
  TIM4_WORK_MODE1 = ((uint8_t)0x01), //TIMER4ѡ����ģʽ1
  TIM4_WORK_MODE3 = ((uint8_t)0x03), //TIMER4ѡ����ģʽ3
} TIM4_WorkMode_TypeDef;
#endif

void TIM4_DeInit();
void TIM4_PrescalerSelection(TIM4_PresSel_TypeDef TIM4_PrescalerSelection);
void TIM4_WorkMode1Config(uint16_t TIM4_SetCounter);
void TIM4_Cmd(FunctionalState NewState);
void TIM4_ITConfig(FunctionalState NewState, PriorityStatus Priority);
FlagStatus TIM4_GetFlagStatus(TIM4_Flag_TypeDef TIM4_Flag);
void TIM4_ClearFlag(TIM4_Flag_TypeDef TIM4_Flag);

#if defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)
void TIM4_TimeBaseInit(TIM4_CountMode_TypeDef TIM4_CountMode,
                       TIM4_CountDirection_TypeDef TIM4_CountDirection);
void TIM4_WorkMode0Config(uint16_t TIM4_SetCounter);
void TIM4_WorkMode3Config(uint16_t TIM4_SetCounter);
void TIM4_WorkModeConfig(TIM4_WorkMode_TypeDef TIM4_WorkMode, uint16_t TIM4_SetCounter);
void TIM4_SetEXEN4(FunctionalState NewState);
#endif

#endif