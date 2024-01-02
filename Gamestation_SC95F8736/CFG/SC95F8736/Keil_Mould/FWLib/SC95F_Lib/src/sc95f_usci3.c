//************************************************************
//  Copyright (c) 
//	�ļ�����: 		sc95f_USCI3.c
//	����:
//	ģ�鹦��: 		USCI3�̼��⺯��C�ļ�
//  ����������: 2022/01/07
// 	�汾: 				V1.10005
//  ˵��:					���ļ���������SC95Fϵ��оƬ
//*************************************************************

#include "sc95f_USCI3.h"

#if defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)\
		 || defined (SC95R751) || defined (SC95F7619B)
#if defined(SC95F8x3x) || defined(SC95F7x3x) 
void USCI3_DeInit(void)
{
  USXINX &= 0xF8;
  USXINX |= 0X03;
  TMCON &= 0XCF;
  USXCON0 = 0X00;
  USXCON1 = 0X00;
  USXCON2 = 0X00;
  USXCON3 = 0X00;
  IE2 &= (~0X04);
  IP2 &= (~0X04);
}

/**************************************************
*��������:void USCI3_SPI_Init(USCI3_SPI_FirstBit_TypeDef FirstBit, USCI3_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler,USCI3_SPI_Mode_TypeDef Mode,
							 USCI3_SPI_ClockPolarity_TypeDef ClockPolarity, USCI3_SPI_ClockPhase_TypeDef ClockPhase,USCI3_SPI_TXE_INT_TypeDef SPI_TXE_INT,USCI3_TransmissionMode_TypeDef TransmissionMode)
*��������:SPI��ʼ�����ú���
*��ڲ���:
USCI3_SPI_FirstBit_TypeDef:FirstBit:���ȴ���λѡ��MSB/LSB��
USCI3_SPI_BaudRatePrescaler_TypeDef:BaudRatePrescaler:SPIʱ��Ƶ��ѡ��
USCI3_SPI_Mode_TypeDef:Mode:SPI����ģʽѡ��
USCI3_SPI_ClockPolarity_TypeDef:ClockPolarity:SPIʱ�Ӽ���ѡ��
USCI3_SPI_ClockPhase_TypeDef:ClockPhase:SPIʱ����λѡ��
USCI3_SPI_TXE_INT_TypeDef:SPI_TXE_INT:���ͻ������ж�����ѡ��,�ù�����SC95FXX1XоƬ����Ч
USCI3_TransmissionMode_TypeDef:TransmissionMode:SPI����ģʽѡ�� 8/16λ
*���ڲ���:void
**************************************************/
void USCI3_SPI_Init(USCI3_SPI_FirstBit_TypeDef FirstBit,
                    USCI3_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, USCI3_SPI_Mode_TypeDef Mode,
                    USCI3_SPI_ClockPolarity_TypeDef ClockPolarity, USCI3_SPI_ClockPhase_TypeDef ClockPhase,
                    USCI3_SPI_TXE_INT_TypeDef SPI_TXE_INT, USCI3_TransmissionMode_TypeDef TransmissionMode)
{
  USXINX &= 0xF8;
  USXINX |= 0X03;
  TMCON = (TMCON & 0XCF) | 0x10;
  USXCON1 = USXCON1 & (~0X05) | FirstBit | SPI_TXE_INT | TransmissionMode;
  USXCON0 = USXCON0 & 0X80 | BaudRatePrescaler | Mode | ClockPolarity | ClockPhase;
}

/**************************************************
*��������:void USCI3_TransmissionMode(USCI3_TransmissionMode_TypeDef TransmissionMode)
*��������:SPI ����ģʽ���ú���
*��ڲ���:
USCI3_TransmissionMode_TypeDef:TransmissionMode:SPI����ģʽѡ�� 8/16eλ
*���ڲ���:void
**************************************************/
void USCI3_TransmissionMode(USCI3_TransmissionMode_TypeDef TransmissionMode)
{
  USXINX &= 0xF8;
  USXINX |= 0X03;
  TMCON = (TMCON & 0XCF) | 0x10;
  if (TransmissionMode == USCI3_SPI_DATA8)
  {
    USXCON1 &= 0xFD;
  }
  else
  {
    USXCON1 |= 0x02;
  }
}

/*****************************************************
*��������:void USCI3_SPI_Cmd(FunctionalState NewState)
*��������:SPI���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void USCI3_SPI_Cmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  TMCON = (TMCON & 0XCF) | 0x10;

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
void USCI3_DeInit(void)
{
  USXINX &= 0xF8;
  USXINX |= 0X03;
  TMCON &= 0X3F;
  USXCON0 = 0X00;
  USXCON1 = 0X00;
  USXCON2 = 0X00;
  USXCON3 = 0X00;
  IE2 &= (~0X04);
  IP2 &= (~0X04);
}

/**************************************************
*��������:void USCI3_SPI_Init(USCI3_SPI_FirstBit_TypeDef FirstBit, USCI3_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler,USCI3_SPI_Mode_TypeDef Mode,
							 USCI3_SPI_ClockPolarity_TypeDef ClockPolarity, USCI3_SPI_ClockPhase_TypeDef ClockPhase,USCI3_SPI_TXE_INT_TypeDef SPI_TXE_INT,USCI3_TransmissionMode_TypeDef TransmissionMode)
*��������:SPI��ʼ�����ú���
*��ڲ���:
USCI3_SPI_FirstBit_TypeDef:FirstBit:���ȴ���λѡ��MSB/LSB��
USCI3_SPI_BaudRatePrescaler_TypeDef:BaudRatePrescaler:SPIʱ��Ƶ��ѡ��
USCI3_SPI_Mode_TypeDef:Mode:SPI����ģʽѡ��
USCI3_SPI_ClockPolarity_TypeDef:ClockPolarity:SPIʱ�Ӽ���ѡ��
USCI3_SPI_ClockPhase_TypeDef:ClockPhase:SPIʱ����λѡ��
USCI3_SPI_TXE_INT_TypeDef:SPI_TXE_INT:���ͻ������ж�����ѡ��,�ù�����SC95FXX1XоƬ����Ч
USCI3_TransmissionMode_TypeDef:TransmissionMode:SPI����ģʽѡ�� 8/16λ
*���ڲ���:void
**************************************************/
void USCI3_SPI_Init(USCI3_SPI_FirstBit_TypeDef FirstBit,
                    USCI3_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, USCI3_SPI_Mode_TypeDef Mode,
                    USCI3_SPI_ClockPolarity_TypeDef ClockPolarity, USCI3_SPI_ClockPhase_TypeDef ClockPhase,
                    USCI3_SPI_TXE_INT_TypeDef SPI_TXE_INT, USCI3_TransmissionMode_TypeDef TransmissionMode)
{
  USXINX &= 0xF8;
  USXINX |= 0X03;
  TMCON = (TMCON & 0X3F) | 0X40;
	
  USXCON1 = USXCON1 & (~0X05) | FirstBit | SPI_TXE_INT | TransmissionMode;
  USXCON0 = USXCON0 & 0X80 | BaudRatePrescaler | Mode | ClockPolarity | ClockPhase;
}

/**************************************************
*��������:void USCI3_TransmissionMode(USCI3_TransmissionMode_TypeDef TransmissionMode)
*��������:SPI ����ģʽ���ú���
*��ڲ���:
USCI3_TransmissionMode_TypeDef:TransmissionMode:SPI����ģʽѡ�� 8/16eλ
*���ڲ���:void
**************************************************/
void USCI3_TransmissionMode(USCI3_TransmissionMode_TypeDef TransmissionMode)
{
  USXINX &= 0xF8;
  USXINX |= 0X03;
  TMCON = (TMCON & 0X3F) | 0X40;
	
  if (TransmissionMode == USCI3_SPI_DATA8)
  {
    USXCON1 &= 0xFD;
  }
  else
  {
    USXCON1 |= 0x02;
  }
}

/*****************************************************
*��������:void USCI3_SPI_Cmd(FunctionalState NewState)
*��������:SPI���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void USCI3_SPI_Cmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
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
*��������:void USCI3_SPI_SendData_8(uint8_t Data)
*��������:USCI3 SPI��������
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI3_SPI_SendData_8(uint8_t Data)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  USXCON2 = Data;
}

/*****************************************************
*��������:uint8_t USCI3_SPI_ReceiveData_8(void)
*��������:���USXCON2�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI3_SPI_ReceiveData_8(void)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  return USXCON2;
}

/*****************************************************
*��������:void USCI3_SPI_SendData_16(uint16_t Data)
*��������:USXCON2 SPI��������
*��ڲ���:
uint16_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI3_SPI_SendData_16(uint16_t Data)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  USXCON3 = (uint8_t)(Data >> 8);
  USXCON2 = (uint8_t)Data;
}

/*****************************************************
*��������:uint16_t USCI3_SPI_ReceiveData_16(void)
*��������:���USXCON2�е�ֵ
*��ڲ���:void
*���ڲ���:
uint16_t:���յ�����
*****************************************************/
uint16_t USCI3_SPI_ReceiveData_16(void)
{
  uint16_t SPI_data;
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  SPI_data = (uint16_t)((USXCON3 << 8) | USXCON2);
  return SPI_data;
}

#if defined(SC95F8x3x) || defined(SC95F7x3x) 
/**************************************************
*��������:void USCI3_TWI_Slave_Init(uint8_t TWI_Address)
*��������:USCI3 TWI �ӻ���ʼ�����ú���
*��ڲ���:
uint8_t:TWI_Address:TWI��Ϊ�ӻ�ʱ��7λ�ӻ���ַ
*���ڲ���:void
**************************************************/
void USCI3_TWI_Slave_Init(uint8_t TWI_Address)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  TMCON = (TMCON & 0XCF) | 0x20;
  USXCON2 = TWI_Address << 1;
}

/**************************************************
*��������:void USCI3_TWI_MasterCommunicationRate(USCI3_TWI_MasterCommunicationRate_TypeDef TWI_MasterCommunicationRate)
*��������:USCI3 TWI����ģʽ��ͨѶ�����趨
*��ڲ���:
USCI3_TWI_MasterCommunicationRate_TypeDef:TWI_MasterCommunicationRate:TWI����ģʽ��ͨѶ����
*���ڲ���:void
**************************************************/
void USCI3_TWI_MasterCommunicationRate(USCI3_TWI_MasterCommunicationRate_TypeDef
                                           TWI_MasterCommunicationRate)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  TMCON = (TMCON & 0XCF) | 0x20;

  USXCON1 = TWI_MasterCommunicationRate;
}

/**************************************************
*��������:void USCI3_TWI_SlaveClockExtension(void)
*��������:USCI3 TWI�ӻ�ģʽʱ���ӳ�����λ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI3_TWI_SlaveClockExtension(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  TMCON = (TMCON & 0XCF) | 0x20;

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
*��������:void USCI3_TWI_AcknowledgeConfig(FunctionalState NewState)
*��������:TWI����Ӧ��ʹ�ܺ���
*��ڲ���:
FunctionalState:NewState:����Ӧ��ʹ��/ʧ��ѡ��
*���ڲ���:void
**************************************************/
void USCI3_TWI_AcknowledgeConfig(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  TMCON = (TMCON & 0XCF) | 0x20;

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
*��������:void USCI3_TWI_GeneralCallCmd(FunctionalState NewState)
*��������:TWIͨ�õ�ַ��Ӧʹ�ܺ���
*��ڲ���:
FunctionalState:NewState:ͨ�õ�ַ��Ӧʹ��/ʧ��ѡ��
*���ڲ���:void
**************************************************/
void USCI3_TWI_GeneralCallCmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  TMCON = (TMCON & 0XCF) | 0x20;

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
*��������:void USCI3_TWI_Cmd(FunctionalState NewState)
*��������:TWI���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void USCI3_TWI_Cmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  TMCON = (TMCON & 0XCF) | 0x20;

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
*��������:void USCI3_TWI_Slave_Init(uint8_t TWI_Address)
*��������:USCI3 TWI �ӻ���ʼ�����ú���
*��ڲ���:
uint8_t:TWI_Address:TWI��Ϊ�ӻ�ʱ��7λ�ӻ���ַ
*���ڲ���:void
**************************************************/
void USCI3_TWI_Slave_Init(uint8_t TWI_Address)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  TMCON = (TMCON & 0X3F) | 0X80;
  USXCON2 = TWI_Address << 1;
}

/**************************************************
*��������:void USCI3_TWI_MasterCommunicationRate(USCI3_TWI_MasterCommunicationRate_TypeDef TWI_MasterCommunicationRate)
*��������:USCI3 TWI����ģʽ��ͨѶ�����趨
*��ڲ���:
USCI3_TWI_MasterCommunicationRate_TypeDef:TWI_MasterCommunicationRate:TWI����ģʽ��ͨѶ����
*���ڲ���:void
**************************************************/
void USCI3_TWI_MasterCommunicationRate(USCI3_TWI_MasterCommunicationRate_TypeDef
                                           TWI_MasterCommunicationRate)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  TMCON = (TMCON & 0X3F) | 0X80;
  USXCON1 = TWI_MasterCommunicationRate;
}

/**************************************************
*��������:void USCI3_TWI_SlaveClockExtension(void)
*��������:USCI3 TWI�ӻ�ģʽʱ���ӳ�����λ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI3_TWI_SlaveClockExtension(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
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
*��������:void USCI3_TWI_AcknowledgeConfig(FunctionalState NewState)
*��������:TWI����Ӧ��ʹ�ܺ���
*��ڲ���:
FunctionalState:NewState:����Ӧ��ʹ��/ʧ��ѡ��
*���ڲ���:void
**************************************************/
void USCI3_TWI_AcknowledgeConfig(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
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
*��������:void USCI3_TWI_GeneralCallCmd(FunctionalState NewState)
*��������:TWIͨ�õ�ַ��Ӧʹ�ܺ���
*��ڲ���:
FunctionalState:NewState:ͨ�õ�ַ��Ӧʹ��/ʧ��ѡ��
*���ڲ���:void
**************************************************/
void USCI3_TWI_GeneralCallCmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
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
*��������:void USCI3_TWI_Cmd(FunctionalState NewState)
*��������:TWI���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void USCI3_TWI_Cmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
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
*��������:void USCI3_TWI_Start(void)
*��������:USCI3 TWI ��ʼλ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI3_TWI_Start(void)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  USXCON1 |= 0x20;
}

/**************************************************
*��������:void USCI3_TWI_MasterModeStop(void)
*��������:USCI3 TWI����ģʽֹͣλ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI3_TWI_MasterModeStop(void)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  USXCON1 |= 0x10;
}

/*****************************************************
*��������:FlagStatus USCI3_GetTWIStatus(USCI3_TWIState_TypeDef USCI3_TWIState)
*��������:��ȡTWI״̬
*��ڲ���:
USCI3_TWIState_TypeDef:USCI3_TWIState:TWI״̬����
*���ڲ���:
FlagStatus:USCI3_TWI��־״̬	
*****************************************************/
FlagStatus USCI3_GetTWIStatus(USCI3_TWIState_TypeDef USCI3_TWIState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  if ((USXCON0 & 0x07) == USCI3_TWIState)
    return SET;
  else
    return RESET;
}

/*****************************************************
*��������:void USCI3_TWI_SendData(uint8_t Data)
*��������:TWI��������
*��ڲ���:
uint8_t:Data:���͵�����/��ַ
*���ڲ���:void
*****************************************************/
void USCI3_TWI_SendData(uint8_t Data)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  USXCON3 = Data;
}

/*****************************************************
*��������:void USCI3_TWI_SendAddr(uint8_t Addr,USCI3_TWI_RWType RW)
*��������:TWI���͵�ַ����д����
*��ڲ���:
uint8_t:Addr:���͵ĵ�ַ
USCI3_TWI_RWType:RW:��д����
*���ڲ���:void
*****************************************************/
void USCI3_TWI_SendAddr(uint8_t Addr, USCI3_TWI_RWType RW)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  USXCON3 = (Addr << 1) | RW;
}

/*****************************************************
*��������:uint8_t USCI3_TWI_SendData(void)
*��������:���USXCON3�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI3_TWI_ReceiveData(void)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  return USXCON3;
}

/**************************************************
*��������:void USCI3_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI3_UART_Mode_TypeDef Mode, USCI3_UART_RX_TypeDef RxMode)
*��������:UART��ʼ�����ú���
*��ڲ���:
uint32_t:UARTFsys:ϵͳʱ��Ƶ��
uint32_t:BaudRate:������
USCI3_UART_Mode_TypeDef:Mode:UART����ģʽ
USCI3_UART_RX_TypeDef:RxMode:��������ѡ��
*���ڲ���:void
**************************************************/
#if defined(SC95F8x3x) || defined(SC95F7x3x)
void USCI3_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI3_UART_Mode_TypeDef Mode,
                     USCI3_UART_RX_TypeDef RxMode)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  TMCON = (TMCON & 0XCF) | 0x30;
  USXCON0 = USXCON0 & 0X0F | Mode | RxMode;

  if (Mode == USCI3_UART_Mode_8B)
  {
    if (BaudRate == USCI3_UART_BaudRate_FsysDIV12)
    {
      USXCON0 &= 0XDF;
    }
    else if (BaudRate == USCI3_UART_BaudRate_FsysDIV4)
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
void USCI3_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI3_UART_Mode_TypeDef Mode,
                     USCI3_UART_RX_TypeDef RxMode)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  TMCON = (TMCON & 0X3F) | 0XC0;
  USXCON0 = USXCON0 & 0X0F | Mode | RxMode;

  if (Mode == USCI3_UART_Mode_8B)
  {
    if (BaudRate == USCI3_UART_BaudRate_FsysDIV12)
    {
      USXCON0 &= 0XDF;
    }
    else if (BaudRate == USCI3_UART_BaudRate_FsysDIV4)
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
*��������:void USCI3_UART_SendData8(uint8_t Data)
*��������:USCI3 UART����8λ����
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI3_UART_SendData8(uint8_t Data)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  USXCON3 = Data;
}

/*****************************************************
*��������:uint8_t USCI3_UART_ReceiveData8(void)
*��������:���USXCON3�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI3_UART_ReceiveData8(void)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  return USXCON3;
}

/*****************************************************
*��������:void USCI3_UART_SendData9(uint16_t Data)
*��������:UART����9λ����
*��ڲ���:
uint16_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI3_UART_SendData9(uint16_t Data)
{
  uint8_t Data_9Bit;
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;

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
*��������:uint16_t USCI3_UART_ReceiveData9(void)
*��������:���USXCON3�е�ֵ���ھ�λ��ֵ
*��ڲ���:void
*���ڲ���:
uint16_t:���յ�����
*****************************************************/
uint16_t USCI3_UART_ReceiveData9(void)
{
  uint16_t Data9;
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;

  Data9 = USXCON3 + ((uint16_t)(USXCON0 & 0X04) << 6);
  return Data9;
}

/*****************************************************
*��������:void USCI3_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:USCI3�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void USCI3_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  if (NewState != DISABLE)
  {
    IE2 |= 0x04;
  }
  else
  {
    IE2 &= 0xFB;
  }

  /************************************************************/
  if (Priority != LOW)
  {
    IP2 |= 0x04;
  }
  else
  {
    IP2 &= 0xFB;
  }
}

/*****************************************************
*��������:FlagStatus USCI3_GetFlagStatus(USCI3_Flag_TypeDef USCI3_FLAG)
*��������:���USCI3��־״̬
*��ڲ���:
USCI3_Flag_Typedef:USCI3_Flag:�жϱ�־λѡ��
*���ڲ���:
FlagStatus:USCI3��־״̬
*****************************************************/
FlagStatus USCI3_GetFlagStatus(USCI3_Flag_TypeDef USCI3_FLAG)
{
  FlagStatus bitstatus = RESET;
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  if ((USCI3_FLAG == USCI3_SPI_FLAG_SPIF) || (USCI3_FLAG == USCI3_SPI_FLAG_WCOL) || (USCI3_FLAG == USCI3_SPI_FLAG_TXE) || (USCI3_FLAG == USCI3_TWI_FLAG_TXRXnE))
  {
    if ((USCI3_FLAG & USXCON1) != (uint8_t)RESET)
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
    if ((USCI3_FLAG & USXCON0) != (uint8_t)RESET)
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
*��������:void USCI3_ClearFlag(USCI3_Flag_TypeDef USCI3_FLAG)
*��������:���USCI3��־״̬
*��ڲ���:
USCI3_Flag_TypeDef:USCI3_FLAG:��������ı�־λ
*���ڲ���:void
*****************************************************/
void USCI3_ClearFlag(USCI3_Flag_TypeDef USCI3_FLAG)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI3
  USXINX |= 0X03;
  if ((USCI3_FLAG == USCI3_SPI_FLAG_SPIF) || (USCI3_FLAG == USCI3_SPI_FLAG_WCOL) || (USCI3_FLAG == USCI3_SPI_FLAG_TXE) || (USCI3_FLAG == USCI3_TWI_FLAG_TXRXnE))
  {
    USXCON1 &= (~USCI3_FLAG); //�����Ĵ���USXCON1
  }
  else if ((USCI3_FLAG == USCI3_UART_FLAG_TI) || (USCI3_FLAG == USCI3_UART_FLAG_RI))
  {
#if defined(SC95F8x3x) || defined(SC95F7x3x)
    USXCON0 = USXCON0  & 0xFC | USCI3_FLAG; //д1����
#else
    USXCON0 &= (~USCI3_FLAG); //д0����
#endif
  }
  else
  {
    USXCON0 &= (~USCI3_FLAG); //�����Ĵ���USXCON0
  }
}

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/

#endif
