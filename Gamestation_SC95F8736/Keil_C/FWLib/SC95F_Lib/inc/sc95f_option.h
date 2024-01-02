//************************************************************
//  Copyright (c) 
//	�ļ�����:			sc95f_option.h
//	����:
//	ģ�鹦��: 		Customer Option�Ĵ�������ͷ�ļ�
//  ����������:	2022��7��20��
// 	�汾: 				V1.10003
//  ˵��:					���ļ���������SC95Fϵ��оƬ
//*************************************************************

#ifndef _sc95f_OPTION_H_
#define _sc95f_OPTION_H_

#include "sc95f.h"

//ϵͳʱ�ӷ�Ƶö��
typedef enum
{
  SYSCLK_PRESSEL_FOSC_D1 = (uint8_t)0x00, //Ԥ��Ƶ Fsys = Fosc/1
  SYSCLK_PRESSEL_FOSC_D2 = (uint8_t)0x10, //Ԥ��Ƶ Fsys = Fosc/2
  SYSCLK_PRESSEL_FOSC_D4 = (uint8_t)0x20, //Ԥ��Ƶ Fsys = Fosc/4
  SYSCLK_PRESSEL_FOSC_D8 = (uint8_t)0x30  //Ԥ��Ƶ Fsys = Fosc/8
} SYSCLK_PresSel_TypeDef;

//�͵�ѹ��λ��λѡ��
typedef enum
{
  LVR_INVALID = (uint8_t)0x04, //LVR��Ч
  LVR_1_9V = (uint8_t)0x00,    //LVR 1.9V��λ
  LVR_2_9V = (uint8_t)0x01,    //LVR 2.9V��λ
  LVR_3_7V = (uint8_t)0x02,    //LVR 3.7V��λ
  LVR_4_3V = (uint8_t)0x03     //LVR 4.3V��λ
} LVR_Config_TypeDef;

//IAP������λö��
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx)
typedef enum
{
  IAP_OPERATERANGE__LAST_1K_CODEREGION = (uint8_t)0x00, //����ROM���1k����IAP����
  IAP_OPERATERANGE__LAST_2K_CODEREGION = (uint8_t)0x04, //����ROM���2k����IAP����
  IAP_OPERATERANGE__LAST_4K_CODEREGION = (uint8_t)0x08, //����ROM���4k����IAP����
  IAP_OPERATERANGE__ALL_CODEREGION = (uint8_t)0x0c      //����ROM�����������IAP����
} IAP_OperateRange_TypeDef;
#endif
#if defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)
typedef enum
{
  IAP_OPERATERANGE__LAST_0K_CODEREGION = (uint8_t)0x00, //���������IAP����
  IAP_OPERATERANGE__LAST_1K_CODEREGION = (uint8_t)0x04, //����ROM���1k����IAP����
  IAP_OPERATERANGE__LAST_2K_CODEREGION = (uint8_t)0x08, //����ROM���2k����IAP����
  IAP_OPERATERANGE__ALL_CODEREGION = (uint8_t)0x0c      //����ROM�����������IAP����
} IAP_OperateRange_TypeDef;
#endif

#if defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751)\
		|| defined (SC95F7610B) || defined (SC95F7619B)
/* ADC�ο���ѹ��λö�� */
typedef enum
{
  ADC_VREF_VDD = 0x00,    //VDD���ο�ADC��ѹ
  ADC_VREF_2_048V = 0x40,	//�ڲ�2.048V��ADC�ο���ѹ
  ADC_VREF_1_024V = 0x80, //�ڲ�1.024V��ADC�ο���ѹ
  ADC_VREF_2_4V = 0xC0  	//�ڲ�2.4V��ADC�ο���ѹ
} ADC_Vref_TypeDef;
#else
/* ADC�ο���ѹ��λö�� */
typedef enum
{
  ADC_VREF_VDD = 0x00,    //VDD���ο�ADC��ѹ
  ADC_VREF_2_048V = 0x40, //�ڲ�2.048V��ADC�ο���ѹ
  ADC_VREF_1_024V = 0x80  //�ڲ�1.024V��ADC�ο���ѹ
} ADC_Vref_TypeDef;
#endif

void OPTION_WDT_Cmd(FunctionalState NewState);
void OPTION_XTIPLL_Cmd(FunctionalState NewState);
void OPTION_SYSCLK_Init(SYSCLK_PresSel_TypeDef SYSCLK_PresSel);
void OPTION_LVR_Init(LVR_Config_TypeDef LVR_Config);
void OPTION_ADC_VrefConfig(ADC_Vref_TypeDef ADC_Vref);
void OPTION_IAP_SetOperateRange(IAP_OperateRange_TypeDef IAP_OperateRange);
void OPTION_JTG_Cmd(FunctionalState NewState);

#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx) ||  defined(SC95F8x2x) || defined(SC95F7x2x)
void OPTION_RST_PIN_Cmd(FunctionalState NewState);
#endif

#endif
