//************************************************************
//  Copyright (c) 
//	�ļ�����: 			sc95f_acmp.h
//	����:
//	ģ�鹦��: 			ACMP�̼��⺯��ͷ�ļ�
//  ����������: 	2022��7��20��
// 	�汾:					V1.0001
//  ˵��					���ļ���������SC95Fxx1xϵ��оƬ
//*************************************************************

#ifndef _sc95f_ACMP_H_
#define _sc95f_ACMP_H_

#include "sc95f.h"

//�Ƚ������������ѹѡ��ö��
typedef enum
{
  ACMP_VREF_EXTERNAL = (uint8_t)0X00, //ѡ��CMPRΪACMP�ıȽϵ�ѹ
  ACMP_VREF_1D16VDD = (uint8_t)0X01,  //ѡ��1/16VDDΪACMP�ıȽϵ�ѹ
  ACMP_VREF_2D16VDD = (uint8_t)0X02,  //ѡ��2/16VDDΪACMP�ıȽϵ�ѹ
  ACMP_VREF_3D16VDD = (uint8_t)0X03,  //ѡ��3/16VDDΪACMP�ıȽϵ�ѹ
  ACMP_VREF_4D16VDD = (uint8_t)0X04,  //ѡ��4/16VDDΪACMP�ıȽϵ�ѹ
  ACMP_VREF_5D16VDD = (uint8_t)0X05,  //ѡ��5/16VDDΪACMP�ıȽϵ�ѹ
  ACMP_VREF_6D16VDD = (uint8_t)0X06,  //ѡ��6/16VDDΪACMP�ıȽϵ�ѹ
  ACMP_VREF_7D16VDD = (uint8_t)0X07,  //ѡ��7/16VDDΪACMP�ıȽϵ�ѹ
  ACMP_VREF_8D16VDD = (uint8_t)0X08,  //ѡ��8/16VDDΪACMP�ıȽϵ�ѹ
  ACMP_VREF_9D16VDD = (uint8_t)0X09,  //ѡ��9/16VDDΪACMP�ıȽϵ�ѹ
  ACMP_VREF_10D16VDD = (uint8_t)0X0A, //ѡ��10/16VDDΪACMP�ıȽϵ�ѹ
  ACMP_VREF_11D16VDD = (uint8_t)0X0B, //ѡ��11/16VDDΪACMP�ıȽϵ�ѹ
  ACMP_VREF_12D16VDD = (uint8_t)0X0C, //ѡ��12/16VDDΪACMP�ıȽϵ�ѹ
  ACMP_VREF_13D16VDD = (uint8_t)0X0D, //ѡ��13/16VDDΪACMP�ıȽϵ�ѹ
  ACMP_VREF_14D16VDD = (uint8_t)0X0E, //ѡ��14/16VDDΪACMP�ıȽϵ�ѹ
  ACMP_VREF_15D16VDD = (uint8_t)0X0F  //ѡ��15/16VDDΪACMP�ıȽϵ�ѹ
} ACMP_Vref_Typedef;

//�Ƚ����ⲿ����ͨ��ѡ��ö��
typedef enum
{
	#if !defined(SC95R751)
  ACMP_CHANNEL_0 = (uint8_t)0x00, //ѡ��CMP0��ACMP�����
	#endif
  ACMP_CHANNEL_1 = (uint8_t)0x01, //ѡ��CMP1��ACMP�����
  ACMP_CHANNEL_2 = (uint8_t)0x02, //ѡ��CMP2��ACMP�����
  ACMP_CHANNEL_3 = (uint8_t)0x03, //ѡ��CMP3��ACMP�����
	#if defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)|| defined (SC95F8x1xB) || defined (SC95F7x1xB)\
		 || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)
	ACMP_CHANNEL_P = (uint8_t)0x10, //ѡ��CMPP��ACMP����ڣ�CMPPΪ��׼��ѹ1.5V
	#endif
} ACMP_Channel_TypeDef;

//�Ƚ���������ʽö��
typedef enum
{
  ACMP_TRIGGER_NO = (uint8_t)0x00,        //�������ж�
  ACMP_TRIGGER_RISE_ONLY = (uint8_t)0x04, //ģ��Ƚ���������ʽΪ������
  ACMP_TRIGGER_FALL_ONLY = (uint8_t)0x08, //ģ��Ƚ���������ʽΪ�½���
  ACMP_TRIGGER_RISE_FALL = (uint8_t)0x0C  //ģ��Ƚ���������ʽΪ���������½���
} ACMP_TriggerMode_Typedef;

//�Ƚ�����־λö��
typedef enum
{
  ACMP_FLAG_CMPIF = (uint8_t)0x40, //ACMP�жϱ�־λ
  ACMP_FLAG_CMPSTA = (uint8_t)0x20 //ACMP���״̬
} ACMP_Flag_TypeDef;

void ACMP_DeInit(void);
void ACMP_Init(ACMP_Vref_Typedef ACMP_Vref, ACMP_Channel_TypeDef ACMP_Channel);
void ACMP_SetTriggerMode(ACMP_TriggerMode_Typedef ACMP_TriggerMode);
void ACMP_Cmd(FunctionalState NewState);
void ACMP_ITConfig(FunctionalState NewState, PriorityStatus Priority);
FlagStatus ACMP_GetFlagStatus(ACMP_Flag_TypeDef ACMP_Flag);
void ACMP_ClearFlag(void);

#endif

/******************* (C) COPYRIGHT 2022 SinOne Microelectronics *****END OF FILE****/