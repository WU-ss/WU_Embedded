//************************************************************
//  Copyright (c) 
//	�ļ�����	: sc95f_timerx.h
//	����		:
//	ģ�鹦��	: TIMER3�̼��⺯��ͷ�ļ�
//  ����������: 2022/01/24
// 	�汾		: V1.10002
//  ˵��        :���ļ���������SC95Fϵ��оƬ
//*************************************************************

#ifndef _sc95f_TIMER3_H_
#define _sc95f_TIMER3_H_

#include "sc95f.H"

typedef enum
{
  TIM3_PRESSEL_FSYS_D12 = ((uint8_t)0x00), //TIMER3����Դ����ϵͳʱ��12��Ƶ
  TIM3_PRESSEL_FSYS_D1 = ((uint8_t)0x01)   //TIMER3����Դ����ϵͳʱ��
} TIM3_PresSel_TypeDef;

#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx)
typedef enum
{
  TIM3_FLAG_TF3 = (uint8_t)0x80, //�жϱ�־λTF3
} TIM3_Flag_TypeDef;
#endif

#if defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)
typedef enum
{
  TIM3_MODE_TIMER = ((uint8_t)0x01),  //TIMER3����ʱ��
  TIM3_MODE_COUNTER = ((uint8_t)0x02) //TIMER3��������
} TIM3_CountMode_TypeDef;

typedef enum
{
  TIM3_COUNTDIRECTION_UP = ((uint8_t)0x00),     //���ϼ���ģʽ
  TIM3_COUNTDIRECTION_DOWN_UP = ((uint8_t)0x10) //����/���¼���ģʽ
} TIM3_CountDirection_TypeDef;

typedef enum
{
  TIM3_FLAG_TF3 = (uint8_t)0x80, //�жϱ�־λTF3
  TIM3_FLAG_EXF3 = (uint8_t)0x40 //�жϱ�־λEXF3
} TIM3_Flag_TypeDef;

typedef enum
{
  TIM3_WORK_MODE0 = ((uint8_t)0x00), //TIMER3ѡ����ģʽ0
  TIM3_WORK_MODE1 = ((uint8_t)0x01), //TIMER3ѡ����ģʽ1
  TIM3_WORK_MODE3 = ((uint8_t)0x03), //TIMER3ѡ����ģʽ3
} TIM3_WorkMode_TypeDef;
#endif

void TIM3_DeInit();
void TIM3_PrescalerSelection(TIM3_PresSel_TypeDef TIM3_PrescalerSelection);
void TIM3_WorkMode1Config(uint16_t TIM3_SetCounter);
void TIM3_Cmd(FunctionalState NewState);
void TIM3_ITConfig(FunctionalState NewState, PriorityStatus Priority);
FlagStatus TIM3_GetFlagStatus(TIM3_Flag_TypeDef TIM3_Flag);
void TIM3_ClearFlag(TIM3_Flag_TypeDef TIM3_Flag);

#if defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)
void TIM3_TimeBaseInit(TIM3_CountMode_TypeDef TIM3_CountMode,
                       TIM3_CountDirection_TypeDef TIM3_CountDirection);
void TIM3_WorkMode0Config(uint16_t TIM3_SetCounter);
void TIM3_WorkMode3Config(uint16_t TIM3_SetCounter);
void TIM3_WorkModeConfig(TIM3_WorkMode_TypeDef TIM3_WorkMode, uint16_t TIM3_SetCounter);
void TIM3_SetEXEN3(FunctionalState NewState);
#endif

#endif
/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/