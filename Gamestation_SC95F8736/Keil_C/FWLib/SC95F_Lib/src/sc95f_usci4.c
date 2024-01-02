//************************************************************
//  Copyright (c) 
//	�ļ�����: 		sc95f_USCI4.c
//	����:
//	ģ�鹦��: 		USCI4�̼��⺯��C�ļ�
//  ����������: 2022/01/07
// 	�汾: 				V1.10005
//  ˵��:					���ļ���������SC95Fϵ��оƬ
//*************************************************************

#include "sc95f_USCI4.h"

#if defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)
#if defined(SC95F8x3x) || defined(SC95F7x3x) 
void USCI4_DeInit(void)
{
  USXINX &= 0xF8;
  USXINX |= 0X04;
  TMCON &= 0XF3;
  USXCON0 = 0X00;
  USXCON1 = 0X00;
  USXCON2 = 0X00;
  USXCON3 = 0X00;
  IE2 &= (~0X08);
  IP2 &= (~0X08);
}

/**************************************************
*��������:void USCI4_SPI_Init(USCI4_SPI_FirstBit_TypeDef FirstBit, USCI4_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler,USCI4_SPI_Mode_TypeDef Mode,
							 USCI4_SPI_ClockPolarity_TypeDef ClockPolarity, USCI4_SPI_ClockPhase_TypeDef ClockPhase,USCI4_SPI_TXE_INT_TypeDef SPI_TXE_INT,USCI4_TransmissionMode_TypeDef TransmissionMode)
*��������:SPI��ʼ�����ú���
*��ڲ���:
USCI4_SPI_FirstBit_TypeDef:FirstBit:���ȴ���λѡ��MSB/LSB��
USCI4_SPI_BaudRatePrescaler_TypeDef:BaudRatePrescaler:SPIʱ��Ƶ��ѡ��
USCI4_SPI_Mode_TypeDef:Mode:SPI����ģʽѡ��
USCI4_SPI_ClockPolarity_TypeDef:ClockPolarity:SPIʱ�Ӽ���ѡ��
USCI4_SPI_ClockPhase_TypeDef:ClockPhase:SPIʱ����λѡ��
USCI4_SPI_TXE_INT_TypeDef:SPI_TXE_INT:���ͻ������ж�����ѡ��,�ù�����SC95FXX1XоƬ����Ч
USCI4_TransmissionMode_TypeDef:TransmissionMode:SPI����ģʽѡ�� 8/16λ
*���ڲ���:void
**************************************************/
void USCI4_SPI_Init(USCI4_SPI_FirstBit_TypeDef FirstBit,
                    USCI4_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, USCI4_SPI_Mode_TypeDef Mode,
                    USCI4_SPI_ClockPolarity_TypeDef ClockPolarity, USCI4_SPI_ClockPhase_TypeDef ClockPhase,
                    USCI4_SPI_TXE_INT_TypeDef SPI_TXE_INT, USCI4_TransmissionMode_TypeDef TransmissionMode)
{
  USXINX &= 0xF8;
  USXINX |= 0X04;
  TMCON = (TMCON & 0XF3) | 0X04;
  USXCON1 = USXCON1 & (~0X05) | FirstBit | SPI_TXE_INT | TransmissionMode;
  USXCON0 = USXCON0 & 0X80 | BaudRatePrescaler | Mode | ClockPolarity | ClockPhase;
}

/**************************************************
*��������:void USCI4_TransmissionMode(USCI4_TransmissionMode_TypeDef TransmissionMode)
*��������:SPI ����ģʽ���ú���
*��ڲ���:
USCI4_TransmissionMode_TypeDef:TransmissionMode:SPI����ģʽѡ�� 8/16eλ
*���ڲ���:void
**************************************************/
void USCI4_TransmissionMode(USCI4_TransmissionMode_TypeDef TransmissionMode)
{
  USXINX &= 0xF8;
  USXINX |= 0X04;
  TMCON = (TMCON & 0XF3) | 0X04;
  if (TransmissionMode == USCI4_SPI_DATA8)
  {
    USXCON1 &= 0xFD;
  }
  else
  {
    USXCON1 |= 0x02;
  }
}

/*****************************************************
*��������:void USCI4_SPI_Cmd(FunctionalState NewState)
*��������:SPI���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void USCI4_SPI_Cmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  TMCON = (TMCON & 0XF3) | 0X04;

  if (NewState != DISABLE)
  {
    USXCON0 |= 0X80;
  }
  else
  {
    USXCON0 &= (~0X80);
  }
}

#else
void USCI4_DeInit(void)
{
  USXINX &= 0xF8;
  USXINX |= 0X04;
  TMCON &= 0X3F;
  USXCON0 = 0X00;
  USXCON1 = 0X00;
  USXCON2 = 0X00;
  USXCON3 = 0X00;
  IE2 &= (~0X04);
  IP2 &= (~0X04);
}

/**************************************************
*��������:void USCI4_SPI_Init(USCI4_SPI_FirstBit_TypeDef FirstBit, USCI4_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler,USCI4_SPI_Mode_TypeDef Mode,
							 USCI4_SPI_ClockPolarity_TypeDef ClockPolarity, USCI4_SPI_ClockPhase_TypeDef ClockPhase,USCI4_SPI_TXE_INT_TypeDef SPI_TXE_INT,USCI4_TransmissionMode_TypeDef TransmissionMode)
*��������:SPI��ʼ�����ú���
*��ڲ���:
USCI4_SPI_FirstBit_TypeDef:FirstBit:���ȴ���λѡ��MSB/LSB��
USCI4_SPI_BaudRatePrescaler_TypeDef:BaudRatePrescaler:SPIʱ��Ƶ��ѡ��
USCI4_SPI_Mode_TypeDef:Mode:SPI����ģʽѡ��
USCI4_SPI_ClockPolarity_TypeDef:ClockPolarity:SPIʱ�Ӽ���ѡ��
USCI4_SPI_ClockPhase_TypeDef:ClockPhase:SPIʱ����λѡ��
USCI4_SPI_TXE_INT_TypeDef:SPI_TXE_INT:���ͻ������ж�����ѡ��,�ù�����SC95FXX1XоƬ����Ч
USCI4_TransmissionMode_TypeDef:TransmissionMode:SPI����ģʽѡ�� 8/16λ
*���ڲ���:void
**************************************************/
void USCI4_SPI_Init(USCI4_SPI_FirstBit_TypeDef FirstBit,
                    USCI4_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, USCI4_SPI_Mode_TypeDef Mode,
                    USCI4_SPI_ClockPolarity_TypeDef ClockPolarity, USCI4_SPI_ClockPhase_TypeDef ClockPhase,
                    USCI4_SPI_TXE_INT_TypeDef SPI_TXE_INT, USCI4_TransmissionMode_TypeDef TransmissionMode)
{
  USXINX &= 0xF8;
  USXINX |= 0X04;
  TMCON = (TMCON & 0X3F) | 0X40;
	
  USXCON1 = USXCON1 & (~0X05) | FirstBit | SPI_TXE_INT | TransmissionMode;
  USXCON0 = USXCON0 & 0X80 | BaudRatePrescaler | Mode | ClockPolarity | ClockPhase;
}

/**************************************************
*��������:void USCI4_TransmissionMode(USCI4_TransmissionMode_TypeDef TransmissionMode)
*��������:SPI ����ģʽ���ú���
*��ڲ���:
USCI4_TransmissionMode_TypeDef:TransmissionMode:SPI����ģʽѡ�� 8/16eλ
*���ڲ���:void
**************************************************/
void USCI4_TransmissionMode(USCI4_TransmissionMode_TypeDef TransmissionMode)
{
  USXINX &= 0xF8;
  USXINX |= 0X04;
  TMCON = (TMCON & 0X3F) | 0X40;
	
  if (TransmissionMode == USCI4_SPI_DATA8)
  {
    USXCON1 &= 0xFD;
  }
  else
  {
    USXCON1 |= 0x02;
  }
}

/*****************************************************
*��������:void USCI4_SPI_Cmd(FunctionalState NewState)
*��������:SPI���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void USCI4_SPI_Cmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  TMCON = (TMCON & 0X3F) | 0X40;

  if (NewState != DISABLE)
  {
    USXCON0 |= 0X80;
  }
  else
  {
    USXCON0 &= (~0X80);
  }
}

#endif

/*****************************************************
*��������:void USCI4_SPI_SendData_8(uint8_t Data)
*��������:USCI4 SPI��������
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI4_SPI_SendData_8(uint8_t Data)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  USXCON2 = Data;
}

/*****************************************************
*��������:uint8_t USCI4_SPI_ReceiveData_8(void)
*��������:���USXCON2�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI4_SPI_ReceiveData_8(void)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;

  return USXCON2;
}

/*****************************************************
*��������:void USCI4_SPI_SendData_16(uint16_t Data)
*��������:USXCON2 SPI��������
*��ڲ���:
uint16_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI4_SPI_SendData_16(uint16_t Data)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;

  USXCON3 = (uint8_t)(Data >> 8);
  USXCON2 = (uint8_t)Data;
}

/*****************************************************
*��������:uint16_t USCI4_SPI_ReceiveData_16(void)
*��������:���USXCON2�е�ֵ
*��ڲ���:void
*���ڲ���:
uint16_t:���յ�����
*****************************************************/
uint16_t USCI4_SPI_ReceiveData_16(void)
{
  uint16_t SPI_data;
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  SPI_data = (uint16_t)((USXCON3 << 8) | USXCON2);
  return SPI_data;
}

#if defined(SC95F8x3x) || defined(SC95F7x3x) 
/**************************************************
*��������:void USCI4_TWI_Slave_Init(uint8_t TWI_Address)
*��������:USCI4 TWI �ӻ���ʼ�����ú���
*��ڲ���:
uint8_t:TWI_Address:TWI��Ϊ�ӻ�ʱ��7λ�ӻ���ַ
*���ڲ���:void
**************************************************/
void USCI4_TWI_Slave_Init(uint8_t TWI_Address)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  TMCON = TMCON & 0xF3 | 0x08;
  USXCON2 = TWI_Address << 1;
}

/**************************************************
*��������:void USCI4_TWI_MasterCommunicationRate(USCI4_TWI_MasterCommunicationRate_TypeDef TWI_MasterCommunicationRate)
*��������:USCI4 TWI����ģʽ��ͨѶ�����趨
*��ڲ���:
USCI4_TWI_MasterCommunicationRate_TypeDef:TWI_MasterCommunicationRate:TWI����ģʽ��ͨѶ����
*���ڲ���:void
**************************************************/
void USCI4_TWI_MasterCommunicationRate(USCI4_TWI_MasterCommunicationRate_TypeDef
                                           TWI_MasterCommunicationRate)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  TMCON = TMCON & 0xF3 | 0x08; //ѡ��USCI4ΪTWI
	
  USXCON1 = TWI_MasterCommunicationRate;
}

/**************************************************
*��������:void USCI4_TWI_SlaveClockExtension(void)
*��������:USCI4 TWI�ӻ�ģʽʱ���ӳ�����λ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI4_TWI_SlaveClockExtension(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  TMCON = TMCON & 0xF3 | 0x08; //ѡ��USCI4ΪTWI

  if (NewState != DISABLE)
  {
    USXCON1 |= 0x40;
  }
  else
  {
    USXCON1 &= 0XBF;
  }
}

/**************************************************
*��������:void USCI4_TWI_AcknowledgeConfig(FunctionalState NewState)
*��������:TWI����Ӧ��ʹ�ܺ���
*��ڲ���:
FunctionalState:NewState:����Ӧ��ʹ��/ʧ��ѡ��
*���ڲ���:void
**************************************************/
void USCI4_TWI_AcknowledgeConfig(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  TMCON = TMCON & 0xF3 | 0x08; //ѡ��USCI4ΪTWI

  if (NewState != DISABLE)
  {
    USXCON0 |= 0X08;
  }
  else
  {
    USXCON0 &= 0XF7;
  }
}

/**************************************************
*��������:void USCI4_TWI_GeneralCallCmd(FunctionalState NewState)
*��������:TWIͨ�õ�ַ��Ӧʹ�ܺ���
*��ڲ���:
FunctionalState:NewState:ͨ�õ�ַ��Ӧʹ��/ʧ��ѡ��
*���ڲ���:void
**************************************************/
void USCI4_TWI_GeneralCallCmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  TMCON = TMCON & 0xF3 | 0x08; //ѡ��USCI4ΪTWI

  if (NewState != DISABLE)
  {
    USXCON2 |= 0X01;
  }
  else
  {
    USXCON2 &= 0XFE;
  }
}

/*****************************************************
*��������:void USCI4_TWI_Cmd(FunctionalState NewState)
*��������:TWI���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void USCI4_TWI_Cmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  TMCON = TMCON & 0xF3 | 0x08;

  if (NewState != DISABLE)
  {
    USXCON0 |= 0X80;
  }
  else
  {
    USXCON0 &= (~0X80);
  }
}

#else

/**************************************************
*��������:void USCI4_TWI_Slave_Init(uint8_t TWI_Address)
*��������:USCI4 TWI �ӻ���ʼ�����ú���
*��ڲ���:
uint8_t:TWI_Address:TWI��Ϊ�ӻ�ʱ��7λ�ӻ���ַ
*���ڲ���:void
**************************************************/
void USCI4_TWI_Slave_Init(uint8_t TWI_Address)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  TMCON = (TMCON & 0X3F) | 0X80;
  USXCON2 = TWI_Address << 1;
}

/**************************************************
*��������:void USCI4_TWI_MasterCommunicationRate(USCI4_TWI_MasterCommunicationRate_TypeDef TWI_MasterCommunicationRate)
*��������:USCI4 TWI����ģʽ��ͨѶ�����趨
*��ڲ���:
USCI4_TWI_MasterCommunicationRate_TypeDef:TWI_MasterCommunicationRate:TWI����ģʽ��ͨѶ����
*���ڲ���:void
**************************************************/
void USCI4_TWI_MasterCommunicationRate(USCI4_TWI_MasterCommunicationRate_TypeDef
                                           TWI_MasterCommunicationRate)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  TMCON = (TMCON & 0X3F) | 0X80;

  USXCON1 = TWI_MasterCommunicationRate;
}

/**************************************************
*��������:void USCI4_TWI_SlaveClockExtension(void)
*��������:USCI4 TWI�ӻ�ģʽʱ���ӳ�����λ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI4_TWI_SlaveClockExtension(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  TMCON = (TMCON & 0X3F) | 0X80;

  if (NewState != DISABLE)
  {
    USXCON1 |= 0x40;
  }
  else
  {
    USXCON1 &= 0XBF;
  }
}

/**************************************************
*��������:void USCI4_TWI_AcknowledgeConfig(FunctionalState NewState)
*��������:TWI����Ӧ��ʹ�ܺ���
*��ڲ���:
FunctionalState:NewState:����Ӧ��ʹ��/ʧ��ѡ��
*���ڲ���:void
**************************************************/
void USCI4_TWI_AcknowledgeConfig(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  TMCON = (TMCON & 0X3F) | 0X80;

  if (NewState != DISABLE)
  {
    USXCON0 |= 0X08;
  }
  else
  {
    USXCON0 &= 0XF7;
  }
}

/**************************************************
*��������:void USCI4_TWI_GeneralCallCmd(FunctionalState NewState)
*��������:TWIͨ�õ�ַ��Ӧʹ�ܺ���
*��ڲ���:
FunctionalState:NewState:ͨ�õ�ַ��Ӧʹ��/ʧ��ѡ��
*���ڲ���:void
**************************************************/
void USCI4_TWI_GeneralCallCmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  TMCON = (TMCON & 0X3F) | 0X80;

  if (NewState != DISABLE)
  {
    USXCON2 |= 0X01;
  }
  else
  {
    USXCON2 &= 0XFE;
  }
}

/*****************************************************
*��������:void USCI4_TWI_Cmd(FunctionalState NewState)
*��������:TWI���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void USCI4_TWI_Cmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  TMCON = (TMCON & 0X3F) | 0X80;

  if (NewState != DISABLE)
  {
    USXCON0 |= 0X80;
  }
  else
  {
    USXCON0 &= (~0X80);
  }
}

#endif

/**************************************************
*��������:void USCI4_TWI_Start(void)
*��������:USCI4 TWI ��ʼλ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI4_TWI_Start(void)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  USXCON1 |= 0x20;
}

/**************************************************
*��������:void USCI4_TWI_MasterModeStop(void)
*��������:USCI4 TWI����ģʽֹͣλ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI4_TWI_MasterModeStop(void)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  USXCON1 |= 0x10;
}

/*****************************************************
*��������:FlagStatus USCI4_GetTWIStatus(USCI4_TWIState_TypeDef USCI4_TWIState)
*��������:��ȡTWI״̬
*��ڲ���:
USCI4_TWIState_TypeDef:USCI4_TWIState:TWI״̬����
*���ڲ���:
FlagStatus:USCI4_TWI��־״̬	
*****************************************************/
FlagStatus USCI4_GetTWIStatus(USCI4_TWIState_TypeDef USCI4_TWIState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  if ((USXCON0 & 0x07) == USCI4_TWIState)
    return SET;
  else
    return RESET;
}

/*****************************************************
*��������:void USCI4_TWI_SendData(uint8_t Data)
*��������:TWI��������
*��ڲ���:
uint8_t:Data:���͵�����/��ַ
*���ڲ���:void
*****************************************************/
void USCI4_TWI_SendData(uint8_t Data)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  USXCON3 = Data;
}

/*****************************************************
*��������:void USCI4_TWI_SendAddr(uint8_t Addr,USCI4_TWI_RWType RW)
*��������:TWI���͵�ַ����д����
*��ڲ���:
uint8_t:Addr:���͵ĵ�ַ
USCI4_TWI_RWType:RW:��д����
*���ڲ���:void
*****************************************************/
void USCI4_TWI_SendAddr(uint8_t Addr, USCI4_TWI_RWType RW)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  USXCON3 = (Addr << 1) | RW;
}

/*****************************************************
*��������:uint8_t USCI4_TWI_SendData(void)
*��������:���USXCON3�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI4_TWI_ReceiveData(void)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  return USXCON3;
}

/**************************************************
*��������:void USCI4_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI4_UART_Mode_TypeDef Mode, USCI4_UART_RX_TypeDef RxMode)
*��������:UART��ʼ�����ú���
*��ڲ���:
uint32_t:UARTFsys:ϵͳʱ��Ƶ��
uint32_t:BaudRate:������
USCI4_UART_Mode_TypeDef:Mode:UART����ģʽ
USCI4_UART_RX_TypeDef:RxMode:��������ѡ��
*���ڲ���:void
**************************************************/
#if defined(SC95F8x3x) || defined(SC95F7x3x)
void USCI4_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI4_UART_Mode_TypeDef Mode,
                     USCI4_UART_RX_TypeDef RxMode)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  TMCON = TMCON & 0XF3 | 0X0C; //ѡ��USCI4ΪUART
  USXCON0 = USXCON0 & 0X0F | Mode | RxMode;

  if (Mode == USCI4_UART_Mode_8B)
  {
    if (BaudRate == USCI4_UART_BaudRate_FsysDIV12)
    {
      USXCON0 &= 0XDF;
    }
    else if (BaudRate == USCI4_UART_BaudRate_FsysDIV4)
    {
      USXCON0 |= 0X20;
    }
  }
  else
  {
    USXCON2 = UARTFsys / BaudRate / 256;
    USXCON1 = UARTFsys / BaudRate % 256;
  }
}

#else
void USCI4_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI4_UART_Mode_TypeDef Mode,
                     USCI4_UART_RX_TypeDef RxMode)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  TMCON = (TMCON & 0X3F) | 0XC0;
  USXCON0 = USXCON0 & 0X0F | Mode | RxMode;

  if (Mode == USCI4_UART_Mode_8B)
  {
    if (BaudRate == USCI4_UART_BaudRate_FsysDIV12)
    {
      USXCON0 &= 0XDF;
    }
    else if (BaudRate == USCI4_UART_BaudRate_FsysDIV4)
    {
      USXCON0 |= 0X20;
    }
  }
  else
  {
    USXCON2 = UARTFsys / BaudRate / 256;
    USXCON1 = UARTFsys / BaudRate % 256;
  }
}

#endif

/*****************************************************
*��������:void USCI4_UART_SendData8(uint8_t Data)
*��������:USCI4 UART1����8λ����
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI4_UART_SendData8(uint8_t Data)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  USXCON3 = Data;
}

/*****************************************************
*��������:uint8_t USCI4_UART_ReceiveData8(void)
*��������:���USXCON3�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI4_UART_ReceiveData8(void)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;
  return USXCON3;
}

/*****************************************************
*��������:void USCI4_UART_SendData9(uint16_t Data)
*��������:UART����9λ����
*��ڲ���:
uint16_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI4_UART_SendData9(uint16_t Data)
{
  uint8_t Data_9Bit;
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;

  Data_9Bit = (Data >> 8);

  if (Data_9Bit)
  {
    USXCON0 |= 0x08;
  }
  else
  {
    USXCON0 &= 0xf7;
  }

  USXCON3 = (uint8_t)Data;
}

/*****************************************************
*��������:uint16_t USCI4_UART_ReceiveData9(void)
*��������:���USXCON3�е�ֵ���ھ�λ��ֵ
*��ڲ���:void
*���ڲ���:
uint16_t:���յ�����
*****************************************************/
uint16_t USCI4_UART_ReceiveData9(void)
{
  uint16_t Data9;
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI4
  USXINX |= 0X04;

  Data9 = USXCON3 + ((uint16_t)(USXCON0 & 0X04) << 6);
  return Data9;
}

/*****************************************************
*��������:void USCI4_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:USCI4�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void USCI4_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  if (NewState != DISABLE)
  {
    IE2 |= 0x08;
  }
  else
  {
    IE2 &= 0xF7;
  }

  /************************************************************/
  if (Priority != LOW)
  {
    IP2 |= 0x08;
  }
  else
  {
    IP2 &= 0xF7;
  }
}

/*****************************************************
*��������:FlagStatus USCI4_GetFlagStatus(USCI4_Flag_TypeDef USCI4_FLAG)
*��������:���USCI4��־״̬
*��ڲ���:
USCI4_Flag_Typedef:USCI4_Flag:�жϱ�־λѡ��
*���ڲ���:
FlagStatus:USCI4��־״̬
*****************************************************/
FlagStatus USCI4_GetFlagStatus(USCI4_Flag_TypeDef USCI4_FLAG)
{
  FlagStatus bitstatus = RESET;
	/* ��USCIX�Ĵ���ָ��USCI4 */
  USXINX &= 0xF8;
  USXINX |= 0X04;

	
  if ((USCI4_FLAG == USCI4_SPI_FLAG_SPIF) || (USCI4_FLAG == USCI4_SPI_FLAG_WCOL) || (USCI4_FLAG == USCI4_SPI_FLAG_TXE) || (USCI4_FLAG == USCI4_TWI_FLAG_TXRXnE))
  {
    if ((USCI4_FLAG & USXCON1) != (uint8_t)RESET)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
  else
  {
    if ((USCI4_FLAG & USXCON0) != (uint8_t)RESET)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }

  return bitstatus;
}

/*****************************************************
*��������:void USCI4_ClearFlag(USCI4_Flag_TypeDef USCI4_FLAG)
*��������:���USCI4��־״̬
*��ڲ���:
USCI4_Flag_TypeDef:USCI4_FLAG:��������ı�־λ
*���ڲ���:void
*****************************************************/
void USCI4_ClearFlag(USCI4_Flag_TypeDef USCI4_FLAG)
{
	/* ��USCIX�Ĵ���ָ��USCI4 */
  USXINX &= 0xF8;
  USXINX |= 0X04;

  if ((USCI4_FLAG == USCI4_SPI_FLAG_SPIF) || (USCI4_FLAG == USCI4_SPI_FLAG_WCOL) || (USCI4_FLAG == USCI4_SPI_FLAG_TXE) || (USCI4_FLAG == USCI4_TWI_FLAG_TXRXnE))
  {
    USXCON1 &= (~USCI4_FLAG); //�����Ĵ���USXCON1
  }
  else if ((USCI4_FLAG == USCI4_UART_FLAG_TI) || (USCI4_FLAG == USCI4_UART_FLAG_RI))
  {
    USXCON0 = USXCON0  & 0xFC | USCI4_FLAG; //д1����
  }
  else
  {
    USXCON0 &= (~USCI4_FLAG); //�����Ĵ���USXCON0
  }
}

#endif
/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/