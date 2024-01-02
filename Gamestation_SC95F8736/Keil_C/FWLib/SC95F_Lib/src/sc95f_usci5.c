//************************************************************
//  Copyright (c) 
//	�ļ�����	: sc95f_USCI5.c
//	����		:
//	ģ�鹦��	: USCI5�̼��⺯��C�ļ�
//  ����������:	2022��7��22��
// 	�汾:					V1.10002
//  ˵��        :���ļ���������SC95Fϵ��оƬ
//*************************************************************

#include "sc95f_USCI5.h"

#if defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95F7619B)
void USCI5_DeInit(void)
{
  USXINX &= 0xF8;
  USXINX |= 0X05;
  TMCON &= 0X3F;
  USXCON0 = 0X00;
  USXCON1 = 0X00;
  USXCON2 = 0X00;
  USXCON3 = 0X00;
  IE2 &= (~0X04);
  IP2 &= (~0X04);
}

/**************************************************
*��������:void USCI5_SPI_Init(USCI5_SPI_FirstBit_TypeDef FirstBit, USCI5_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler,USCI5_SPI_Mode_TypeDef Mode,
							 USCI5_SPI_ClockPolarity_TypeDef ClockPolarity, USCI5_SPI_ClockPhase_TypeDef ClockPhase,USCI5_SPI_TXE_INT_TypeDef SPI_TXE_INT,USCI5_TransmissionMode_TypeDef TransmissionMode)
*��������:SPI��ʼ�����ú���
*��ڲ���:
USCI5_SPI_FirstBit_TypeDef:FirstBit:���ȴ���λѡ��MSB/LSB��
USCI5_SPI_BaudRatePrescaler_TypeDef:BaudRatePrescaler:SPIʱ��Ƶ��ѡ��
USCI5_SPI_Mode_TypeDef:Mode:SPI����ģʽѡ��
USCI5_SPI_ClockPolarity_TypeDef:ClockPolarity:SPIʱ�Ӽ���ѡ��
USCI5_SPI_ClockPhase_TypeDef:ClockPhase:SPIʱ����λѡ��
USCI5_SPI_TXE_INT_TypeDef:SPI_TXE_INT:���ͻ������ж�����ѡ��,�ù�����SC95FXX1XоƬ����Ч
USCI5_TransmissionMode_TypeDef:TransmissionMode:SPI����ģʽѡ�� 8/16λ
*���ڲ���:void
**************************************************/
void USCI5_SPI_Init(USCI5_SPI_FirstBit_TypeDef FirstBit,
                    USCI5_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, USCI5_SPI_Mode_TypeDef Mode,
                    USCI5_SPI_ClockPolarity_TypeDef ClockPolarity, USCI5_SPI_ClockPhase_TypeDef ClockPhase,
                    USCI5_SPI_TXE_INT_TypeDef SPI_TXE_INT, USCI5_TransmissionMode_TypeDef TransmissionMode)
{
  USXINX &= 0xF8;
  USXINX |= 0X05;
  TMCON = (TMCON & 0X3F) | 0X40;
	
  USXCON1 = USXCON1 & (~0X05) | FirstBit | SPI_TXE_INT | TransmissionMode;
  USXCON0 = USXCON0 & 0X80 | BaudRatePrescaler | Mode | ClockPolarity | ClockPhase;
}

/**************************************************
*��������:void USCI5_TransmissionMode(USCI5_TransmissionMode_TypeDef TransmissionMode)
*��������:SPI ����ģʽ���ú���
*��ڲ���:
USCI5_TransmissionMode_TypeDef:TransmissionMode:SPI����ģʽѡ�� 8/16eλ
*���ڲ���:void
**************************************************/
void USCI5_TransmissionMode(USCI5_TransmissionMode_TypeDef TransmissionMode)
{

  USXINX &= 0xF8;
  USXINX |= 0X05;
  TMCON = (TMCON & 0X3F) | 0X40;
	
  if (TransmissionMode == USCI5_SPI_DATA8)
  {
    USXCON1 &= 0xFD;
  }
  else
  {
    USXCON1 |= 0x02;
  }
}

/*****************************************************
*��������:void USCI5_SPI_Cmd(FunctionalState NewState)
*��������:SPI���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void USCI5_SPI_Cmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
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

/*****************************************************
*��������:void USCI5_SPI_SendData_8(uint8_t Data)
*��������:USCI5 SPI��������
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI5_SPI_SendData_8(uint8_t Data)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
  USXCON2 = Data;
}

/*****************************************************
*��������:uint8_t USCI5_SPI_ReceiveData_8(void)
*��������:���USXCON2�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI5_SPI_ReceiveData_8(void)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
  return USXCON2;
}

/*****************************************************
*��������:void USCI5_SPI_SendData_16(uint16_t Data)
*��������:USXCON2 SPI��������
*��ڲ���:
uint16_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI5_SPI_SendData_16(uint16_t Data)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
  USXCON3 = (uint8_t)(Data >> 8);
  USXCON2 = (uint8_t)Data;
}

/*****************************************************
*��������:uint16_t USCI5_SPI_ReceiveData_16(void)
*��������:���USXCON2�е�ֵ
*��ڲ���:void
*���ڲ���:
uint16_t:���յ�����
*****************************************************/
uint16_t USCI5_SPI_ReceiveData_16(void)
{
  uint16_t SPI_data;
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
  SPI_data = (uint16_t)((USXCON3 << 8) | USXCON2);
  return SPI_data;
}

/**************************************************
*��������:void USCI5_TWI_Slave_Init(uint8_t TWI_Address)
*��������:USCI5 TWI �ӻ���ʼ�����ú���
*��ڲ���:
uint8_t:TWI_Address:TWI��Ϊ�ӻ�ʱ��7λ�ӻ���ַ
*���ڲ���:void
**************************************************/
void USCI5_TWI_Slave_Init(uint8_t TWI_Address)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
  TMCON = (TMCON & 0X3F) | 0X80;
  USXCON2 = TWI_Address << 1;
}

/**************************************************
*��������:void USCI5_TWI_MasterCommunicationRate(USCI5_TWI_MasterCommunicationRate_TypeDef TWI_MasterCommunicationRate)
*��������:USCI5 TWI����ģʽ��ͨѶ�����趨
*��ڲ���:
USCI5_TWI_MasterCommunicationRate_TypeDef:TWI_MasterCommunicationRate:TWI����ģʽ��ͨѶ����
*���ڲ���:void
**************************************************/
void USCI5_TWI_MasterCommunicationRate(USCI5_TWI_MasterCommunicationRate_TypeDef
                                           TWI_MasterCommunicationRate)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
  TMCON = (TMCON & 0X3F) | 0X80;

  USXCON1 = TWI_MasterCommunicationRate;
}

/**************************************************
*��������:void USCI5_TWI_SlaveClockExtension(void)
*��������:USCI5 TWI�ӻ�ģʽʱ���ӳ�����λ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI5_TWI_SlaveClockExtension(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
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
*��������:void USCI5_TWI_AcknowledgeConfig(FunctionalState NewState)
*��������:TWI����Ӧ��ʹ�ܺ���
*��ڲ���:
FunctionalState:NewState:����Ӧ��ʹ��/ʧ��ѡ��
*���ڲ���:void
**************************************************/
void USCI5_TWI_AcknowledgeConfig(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
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
*��������:void USCI5_TWI_GeneralCallCmd(FunctionalState NewState)
*��������:TWIͨ�õ�ַ��Ӧʹ�ܺ���
*��ڲ���:
FunctionalState:NewState:ͨ�õ�ַ��Ӧʹ��/ʧ��ѡ��
*���ڲ���:void
**************************************************/
void USCI5_TWI_GeneralCallCmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
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
*��������:void USCI5_TWI_Cmd(FunctionalState NewState)
*��������:TWI���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void USCI5_TWI_Cmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
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

/**************************************************
*��������:void USCI5_TWI_Start(void)
*��������:USCI5 TWI ��ʼλ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI5_TWI_Start(void)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
  USXCON1 |= 0x20;
}

/**************************************************
*��������:void USCI5_TWI_MasterModeStop(void)
*��������:USCI5 TWI����ģʽֹͣλ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI5_TWI_MasterModeStop(void)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
  USXCON1 |= 0x10;
}

/*****************************************************
*��������:FlagStatus USCI5_GetTWIStatus(USCI5_TWIState_TypeDef USCI5_TWIState)
*��������:��ȡTWI״̬
*��ڲ���:
USCI5_TWIState_TypeDef:USCI2_TWIState:TWI״̬����
*���ڲ���:
FlagStatus:USCI5_TWI��־״̬	
*****************************************************/
FlagStatus USCI5_GetTWIStatus(USCI5_TWIState_TypeDef USCI5_TWIState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
  if ((USXCON0 & 0x07) == USCI5_TWIState)
    return SET;
  else
    return RESET;
}

/*****************************************************
*��������:void USCI5_TWI_SendData(uint8_t Data)
*��������:TWI��������
*��ڲ���:
uint8_t:Data:���͵�����/��ַ
*���ڲ���:void
*****************************************************/
void USCI5_TWI_SendData(uint8_t Data)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
  USXCON3 = Data;
}

/*****************************************************
*��������:void USCI5_TWI_SendAddr(uint8_t Addr,USCI5_TWI_RWType RW)
*��������:TWI���͵�ַ����д����
*��ڲ���:
uint8_t:Addr:���͵ĵ�ַ
USCI5_TWI_RWType:RW:��д����
*���ڲ���:void
*****************************************************/
void USCI5_TWI_SendAddr(uint8_t Addr, USCI5_TWI_RWType RW)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
  USXCON3 = (Addr << 1) | RW;
}
/*****************************************************
*��������:uint8_t USCI5_TWI_SendData(void)
*��������:���USXCON3�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI5_TWI_ReceiveData(void)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
  return USXCON3;
}

/**************************************************
*��������:void USCI5_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI5_UART_Mode_TypeDef Mode, USCI5_UART_RX_TypeDef RxMode)
*��������:UART��ʼ�����ú���
*��ڲ���:
uint32_t:UARTFsys:ϵͳʱ��Ƶ��
uint32_t:BaudRate:������
USCI5_UART_Mode_TypeDef:Mode:UART����ģʽ
USCI5_UART_RX_TypeDef:RxMode:��������ѡ��
*���ڲ���:void
**************************************************/
void USCI5_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI5_UART_Mode_TypeDef Mode,
                     USCI5_UART_RX_TypeDef RxMode)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
  TMCON = (TMCON & 0X3F) | 0XC0;
  USXCON0 = USXCON0 & 0X0F | Mode | RxMode;

  if (Mode == USCI5_UART_Mode_8B)
  {
    if (BaudRate == USCI5_UART_BaudRate_FsysDIV12)
    {
      USXCON0 &= 0XDF;
    }
    else if (BaudRate == USCI5_UART_BaudRate_FsysDIV4)
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

/*****************************************************
*��������:void USCI5_UART_SendData8(uint8_t Data)
*��������:USCI5 UART����8λ����
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI5_UART_SendData8(uint8_t Data)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
  USXCON3 = Data;
}

/*****************************************************
*��������:uint8_t USCI5_UART_ReceiveData8(void)
*��������:���USXCON3�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI5_UART_ReceiveData8(void)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
  return USXCON3;
}

/*****************************************************
*��������:void USCI5_UART_SendData9(uint16_t Data)
*��������:UART����9λ����
*��ڲ���:
uint16_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI5_UART_SendData9(uint16_t Data)
{
  uint8_t Data_9Bit;
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;

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
*��������:uint16_t USCI5_UART_ReceiveData9(void)
*��������:���USXCON3�е�ֵ���ھ�λ��ֵ
*��ڲ���:void
*���ڲ���:
uint16_t:���յ�����
*****************************************************/
uint16_t USCI5_UART_ReceiveData9(void)
{
  uint16_t Data9;
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;

  Data9 = USXCON3 + ((uint16_t)(USXCON0 & 0X04) << 6);
  return Data9;
}

/*****************************************************
*��������:void USCI5_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:USCI5�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void USCI5_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  if (NewState != DISABLE)
  {
    IE2 |= 0x10;
  }
  else
  {
    IE2 &= 0xEF;
  }

  /************************************************************/
  if (Priority != LOW)
  {
    IP2 |= 0x10;
  }
  else
  {
    IP2 &= 0xEF;
  }
}

/*****************************************************
*��������:FlagStatus USCI5_GetFlagStatus(USCI5_Flag_TypeDef USCI5_FLAG)
*��������:���USCI5��־״̬
*��ڲ���:
USCI5_Flag_Typedef:USCI5_Flag:�жϱ�־λѡ��
*���ڲ���:
FlagStatus:USCI5��־״̬
*****************************************************/
FlagStatus USCI5_GetFlagStatus(USCI5_Flag_TypeDef USCI5_FLAG)
{
  FlagStatus bitstatus = RESET;
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
  if ((USCI5_FLAG == USCI5_SPI_FLAG_SPIF) || (USCI5_FLAG == USCI5_SPI_FLAG_WCOL) || (USCI5_FLAG == USCI5_SPI_FLAG_TXE) || (USCI5_FLAG == USCI5_TWI_FLAG_TXRXnE))
  {
    if ((USCI5_FLAG & USXCON1) != (uint8_t)RESET)
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
    if ((USCI5_FLAG & USXCON0) != (uint8_t)RESET)
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
*��������:void USCI5_ClearFlag(USCI5_Flag_TypeDef USCI5_FLAG)
*��������:���USCI5��־״̬
*��ڲ���:
USCI5_Flag_TypeDef:USCI5_FLAG:��������ı�־λ
*���ڲ���:void
*****************************************************/
void USCI5_ClearFlag(USCI5_Flag_TypeDef USCI5_FLAG)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI5
  USXINX |= 0X05;
  if ((USCI5_FLAG == USCI5_SPI_FLAG_SPIF) || (USCI5_FLAG == USCI5_SPI_FLAG_WCOL) || (USCI5_FLAG == USCI5_SPI_FLAG_TXE) || (USCI5_FLAG == USCI5_TWI_FLAG_TXRXnE))
  {
    USXCON1 &= (~USCI5_FLAG); //�����Ĵ���USXCON1
  }
  else if ((USCI5_FLAG == USCI5_UART_FLAG_TI) || (USCI5_FLAG == USCI5_UART_FLAG_RI))
  {
#if defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)
    USXCON0 = USXCON0  & 0xFC | USCI5_FLAG; //д1����
#else
    USXCON0 &= (~USCI5_FLAG); //д0����
#endif
  }
  else
  {
    USXCON0 &= (~USCI5_FLAG); //�����Ĵ���USXCON0
  }
}

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/

#endif
