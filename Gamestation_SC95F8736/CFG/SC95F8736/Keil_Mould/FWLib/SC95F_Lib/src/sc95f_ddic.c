//************************************************************
//  Copyright (c) 
//	�ļ�����: 			sc95f_ddic.c
//	����:
//	ģ�鹦��:		 	DDIC�̼��⺯��C�ļ�
//  ����������:	2022��7��22��
// 	�汾: 				V1.10003
//  ˵��:					���ļ���������SC95Fϵ��оƬ
//*************************************************************

#include "sc95f_ddic.h"

#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751)	|| defined (SC95F7610B)

#if defined(SC95F8x1x) || defined(SC95F7x1x)
uint8_t xdata LCDRAM[30] _at_ 0x1000;
#elif defined (SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)\
			|| defined (SC95R751)	|| defined (SC95F7610B)
uint8_t xdata LCDRAM[30] _at_ 0x2000;
#endif

/**************************************************
*��������:void DDIC_DeInit(void)
*��������:DDIC��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void DDIC_DeInit(void)
{
  DDRCON = 0X00;
  P0VO = 0X00;
  P1VO = 0X00;
  P2VO = 0X00;
  P3VO = 0X00;
  OTCON &= 0XF0;
}

/**************************************************
*��������:void DDIC_Init(DDIC_DutyCycle_TypeDef DDIC_DutyCylce, uint8_t P0OutputPin, uint8_t P1OutputPin,
               uint8_t P2OutputPin, uint8_t P3OutputPin)
*��������:DDIC��ʼ�����ú���
*��ڲ���:
DDIC_DutyCycle_TypeDef:DDIC_DutyCylce:LCD/LED��ʾռ�ձȿ���
DDIC_Pin_TypeDef:P0OutputPin:����P0������ΪLCD��ѹ�����
DDIC_Pin_TypeDef:P1OutputPin:����P1������ΪLCD��ѹ�����
DDIC_Pin_TypeDef:P2OutputPin:����P2������ΪLCD��ѹ�����
DDIC_Pin_TypeDef:P3OutputPin:����P3������ΪLCD��ѹ����ڣ�uint8_t��Ϊ��Σ��������λ�������
*���ڲ���:void
**************************************************/
void DDIC_Init(DDIC_DutyCycle_TypeDef DDIC_DutyCylce, uint8_t P0OutputPin, uint8_t P1OutputPin,
               uint8_t P2OutputPin, uint8_t P3OutputPin)
{
  DDRCON = DDRCON & 0XCF | DDIC_DutyCylce;
  P0VO = P0OutputPin;
  P1VO = P1OutputPin;
  P2VO = P2OutputPin;
  P3VO = P3OutputPin;
}

/**************************************************
*��������:void DDIC_LEDConfig(void)
*��������:LED���ú���
*��ڲ���:void
*���ڲ���:void
**************************************************/
void DDIC_LEDConfig(void)
{
  DDRCON |= 0X40;
}

/**************************************************
*��������:void DDIC_LCDConfig(DDIC_ResSel_Typedef DDIC_ResSel)
*��������:LCD���ú���
*��ڲ���:
uint8_t:LCDVoltage:LCD��ѹ����
DDIC_ResSel_Typedef:DDIC_ResSel:LCD��ѹ����ڵ���ѡ��
DDIC_BiasVoltage_Typedef:DDIC_BiasVoltage:LCD��ʾ����ƫ�õ�ѹ����
*���ڲ���:void
**************************************************/
void DDIC_LCDConfig(uint8_t LCDVoltage, DDIC_ResSel_Typedef DDIC_ResSel,
                    DDIC_BiasVoltage_Typedef DDIC_BiasVoltage)
{
  DDRCON = DDRCON & 0XB0 | LCDVoltage;
  OTCON = OTCON & 0XF2 | DDIC_ResSel | DDIC_BiasVoltage;
}
/**************************************************
*��������:void DDIC_DMOD_Selcet(DDIC_DMOD_TypeDef DDIC_DMOD)
*��������:��ʾ����ģʽѡ����
*��ڲ���:
DDIC_DMOD_TypeDef:DDIC_DMOD:ѡ����ʾģʽ
*���ڲ���:void
**************************************************/
void DDIC_DMOD_Selcet(DDIC_DMOD_TypeDef DDIC_DMOD)
{
  if (DDIC_DMOD == DMOD_LED)
  {
    DDRCON |= 0X40;
  }
  else
  {
    DDRCON &= 0XBF;
  }
}
/*****************************************************
*��������:void DDIC_OutputPinOfDutycycleD4(DDIC_OutputPin_TypeDef DDIC_OutputPin)
*��������:1/4ռ�ձ�ʱsegment��common���ùܽ�ѡ��
*��ڲ���:
DDIC_OutputPin_TypeDef:DDIC_OutputPin:����ܽ�ѡ��
*���ڲ���:void
*****************************************************/
void DDIC_OutputPinOfDutycycleD4(DDIC_OutputPin_TypeDef DDIC_OutputPin)
{
  if (DDIC_OutputPin == SEG4_27COM0_3)
  {
    OTCON |= 0X02;
  }
  else
  {
    OTCON &= 0Xfd;
  }
}

/*****************************************************
*��������:void DDIC_Cmd(FunctionalState NewState)
*��������:��ʾ�������ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void DDIC_Cmd(FunctionalState NewState)
{
  if (NewState == DISABLE)
  {
    DDRCON &= 0X7F;
  }
  else
  {
    DDRCON |= 0x80;
  }
}
/*****************************************************
*��������:void DDIC_Control(DDIC_Control_SEG_TypeDef DDIC_Seg,uint8_t DDIC_Com,DDIC_Control_Status DDIC_Contr)
*��������:���������SEG��COM�Ŷ�ӦLCD/LED������
*��ڲ���:
DDIC_Control_SEG_TypeDef:DDIC_Seg:ѡ����Ƶ�SEG��
DDIC_Control_COM_TypeDef:DDIC_Com:ѡ����Ƶ�COM�ڣ�uint8_t��Ϊ��Σ��������λ�������
DDIC_Control_Status:DDIC_Contr:����״̬
*���ڲ���:void
*****************************************************/
void DDIC_Control(DDIC_Control_SEG_TypeDef DDIC_Seg, uint8_t DDIC_Com,
                  DDIC_Control_Status DDIC_Contr)
{
  if (DDIC_Contr)
  {
    LCDRAM[DDIC_Seg] |= DDIC_Com;
  }
  else
  {
    LCDRAM[DDIC_Seg] &= (~DDIC_Com);
  }
}

#endif

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/
