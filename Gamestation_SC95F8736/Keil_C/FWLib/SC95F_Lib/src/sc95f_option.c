//************************************************************
//  Copyright (c)
//	�ļ�����	: sc95f_option.c
//	����		:
//	ģ�鹦��	: Customer Option�Ĵ�������C�ļ�
//  ����������: 2022/1/28
// 	�汾		: V1.10002
//  ˵��        :���ļ���������SC95Fxx1x��SC95Fxx2xϵ��оƬ
//*************************************************************

#include "sc95f_option.h"

/*****************************************************
*��������:void OPTION_WDT_Cmd(FunctionalState NewState)
*��������:WDT���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:���Ź���������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void OPTION_WDT_Cmd(FunctionalState NewState)
{
  OPINX = 0XC1;

  if (NewState == DISABLE)
  {
    OPREG &= 0X7F;
  }
  else
  {
    OPREG |= 0X80;
  }
}

/*****************************************************
*��������:void OPTION_XTIPLL_Cmd(FunctionalState NewState)
*��������:�ⲿ��Ƶ����ʹ��
*��ڲ���:
FunctionalState:NewState:�ⲿ��Ƶ��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void OPTION_XTIPLL_Cmd(FunctionalState NewState)
{
  OPINX = 0XC1;

  if (NewState == DISABLE)
  {
    OPREG &= 0XBF;
  }
  else
  {
    OPREG |= 0X40;
  }
}

/*****************************************************
*��������:void OPTION_SYSCLK_Init(SYSCLK_PresSel_TypeDef SYSCLK_PresSel)
*��������:ϵͳʱ�ӷ�Ƶ��ʼ��
*��ڲ���:
SYSCLK_PresSel_TypeDef:SYSCLK_PresSel:ѡ��ϵͳʱ�ӷ�Ƶ
*���ڲ���:void
*****************************************************/
void OPTION_SYSCLK_Init(SYSCLK_PresSel_TypeDef SYSCLK_PresSel)
{
  OPINX = 0XC1;
  OPREG = OPREG & 0XCF | SYSCLK_PresSel;
}

#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx) ||  defined(SC95F8x2x) || defined(SC95F7x2x)
/*****************************************************
*��������:void OPTION_RST_PIN_Cmd(FunctionalState NewState)
*��������:�ⲿ��λ�ܽ�ʹ��
*��ڲ���:
FunctionalState:NewState:�ⲿ��λ���Ź���ʹ��/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void OPTION_RST_PIN_Cmd(FunctionalState NewState)
{
  OPINX = 0XC1;

  if (NewState == DISABLE)
  {
    OPREG |= 0X08;
  }
  else
  {
    OPREG &= 0XF7;
  }
}
#endif

/*****************************************************
*��������:void OPTION_LVR_Init(LVR_Config_TypeDef LVR_Config)
*��������:LVR ��ѹѡ��
*��ڲ���:
LVR_Config_TypeDef:LVR_Config:ѡ��LVR��ѹ
*���ڲ���:void
*****************************************************/
void OPTION_LVR_Init(LVR_Config_TypeDef LVR_Config)
{
  OPINX = 0XC1;
  OPREG = OPREG & 0XF8 | LVR_Config;
}

/*****************************************************
*��������:void OPTION_ADC_VrefConfig(ADC_Vref_TypeDef ADC_Vref)
*��������:ADC �ο���ѹѡ��
*��ڲ���:
ADC_Vref_TypeDef:ADC_Vref:ѡ��ADC�ο���ѹ
*���ڲ���:void
*****************************************************/
void OPTION_ADC_VrefConfig(ADC_Vref_TypeDef ADC_Vref)
{
  OPINX = 0xC2;

  if (ADC_Vref == ADC_VREF_2_048V)
  {
    OPREG &= 0x3f;
    OPREG |= 0x40; //ѡ��ο��ڲ���ѹ2.048V��
  }

  if (ADC_Vref == ADC_VREF_1_024V)
  {
    OPREG &= 0x3f;
    OPREG |= 0x80; //ѡ��ο��ڲ���ѹ1.024V��
  }

  if (ADC_Vref == ADC_VREF_VDD)
  {
    OPREG &= 0x3f; //ѡ��ο���ѹVDD��
  }
}

/**************************************************
*��������:void OPTION_IAP_SetOperateRange(IAP_OperateRange_TypeDef IAP_OperateRange)
*��������:����IAP�����ķ�Χ����
*��ڲ���:
IAP_OperateRange_TypeDef:IAP_OperateRange:IAP������Χ
*���ڲ���:void
**************************************************/
void OPTION_IAP_SetOperateRange(IAP_OperateRange_TypeDef IAP_OperateRange)
{
  OPINX = 0xC2;
  OPREG = (OPREG & 0xF3) | IAP_OperateRange;
}

/**************************************************
*��������:void OPTION_JTG_Cmd(FunctionalState NewState)
*��������:JTAG/IO���л�����
*��ڲ���:
FunctionalState:NewState:��¼����Ϊ������IOʹ�ã�DISBLE��,��¼����ΪtCK/tDIOʹ�ã�ENABLE��
*���ڲ���:void
**************************************************/
void OPTION_JTG_Cmd(FunctionalState NewState)
{
  OPINX = 0xC2;
  if (NewState == DISABLE)
  {
    OPREG |= 0X10;
  }
  else
  {
    OPREG &= 0XEF;
  }
}

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/