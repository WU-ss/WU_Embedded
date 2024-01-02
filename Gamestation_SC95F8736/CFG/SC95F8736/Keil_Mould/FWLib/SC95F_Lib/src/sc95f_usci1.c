//************************************************************
//  Copyright (c) 
//	�ļ�����	: sc95f_USCI1.c
//	����		:
//	ģ�鹦��	: USCI1�̼��⺯��C�ļ�
//  ����������: 2022/01/24
// 	�汾		: V1.10004
//  ˵��        :���ļ���������SC95Fϵ��оƬ
//*************************************************************

#include "sc95f_usci1.h"

/**************************************************
*��������:void USCI1_DeInit(void)
*��������:USCI1��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI1_DeInit(void)
{
  OTCON &= 0X3F;
  US1CON0 = 0X00;
  US1CON1 = 0X00;
  US1CON2 = 0X00;
  US1CON3 = 0X00;
  IE2 &= (~0X01);
  IP2 &= (~0X01);
}

/**************************************************
*��������:void USCI1_SPI_Init(USCI1_SPI_FirstBit_TypeDef FirstBit, USCI1_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler,USCI1_SPI_Mode_TypeDef Mode,
							 USCI1_SPI_ClockPolarity_TypeDef ClockPolarity, USCI1_SPI_ClockPhase_TypeDef ClockPhase,USCI1_SPI_TXE_INT_TypeDef SPI_TXE_INT,USCI1_TransmissionMode_TypeDef TransmissionMode)
*��������:SPI��ʼ�����ú���
*��ڲ���:
USCI1_SPI_FirstBit_TypeDef:FirstBit:���ȴ���λѡ��MSB/LSB��
USCI1_SPI_BaudRatePrescaler_TypeDef:BaudRatePrescaler:SPIʱ��Ƶ��ѡ��
USCI1_SPI_Mode_TypeDef:Mode:SPI����ģʽѡ��
USCI1_SPI_ClockPolarity_TypeDef:ClockPolarity:SPIʱ�Ӽ���ѡ��
USCI1_SPI_ClockPhase_TypeDef:ClockPhase:SPIʱ����λѡ��
USCI1_SPI_TXE_INT_TypeDef:SPI_TXE_INT:���ͻ������ж�����ѡ��,�ù�����SC95FXX1XоƬ����Ч
USCI1_TransmissionMode_TypeDef:TransmissionMode:SPI����ģʽѡ�� 8/16λ
*���ڲ���:void
**************************************************/
void USCI1_SPI_Init(USCI1_SPI_FirstBit_TypeDef FirstBit,
                    USCI1_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, USCI1_SPI_Mode_TypeDef Mode,
                    USCI1_SPI_ClockPolarity_TypeDef ClockPolarity, USCI1_SPI_ClockPhase_TypeDef ClockPhase,
                    USCI1_SPI_TXE_INT_TypeDef SPI_TXE_INT, USCI1_TransmissionMode_TypeDef TransmissionMode)
{

  OTCON = (OTCON & 0X3F) | 0X40;
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx)
  SPI_TXE_INT = USCI1_SPI_TXE_DISINT; //SPI_TXE_INT�ù�����SC95FXX1XоƬ����Ч
  US1CON1 = US1CON1 & (~0X05) | FirstBit | TransmissionMode;
#endif
#if defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
	|| defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)
  US1CON1 = US1CON1 & (~0X05) | FirstBit | SPI_TXE_INT | TransmissionMode;
#endif
  US1CON0 = US1CON0 & 0X80 | BaudRatePrescaler | Mode | ClockPolarity | ClockPhase;
}

/**************************************************
*��������:void USCI1_TransmissionMode(USCI1_TransmissionMode_TypeDef TransmissionMode)
*��������:SPI ����ģʽ���ú���
*��ڲ���:
USCI1_TransmissionMode_TypeDef:TransmissionMode:SPI����ģʽѡ�� 8/16eλ
*���ڲ���:void
**************************************************/
void USCI1_TransmissionMode(USCI1_TransmissionMode_TypeDef TransmissionMode)
{
  if (TransmissionMode == USCI1_SPI_DATA8)
  {
    US1CON1 &= 0xFD;
  }
  else
  {
    US1CON1 |= 0x02;
  }
}

/*****************************************************
*��������:void USCI1_SPI_Cmd(FunctionalState NewState)
*��������:SPI���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void USCI1_SPI_Cmd(FunctionalState NewState)
{
  OTCON = (OTCON & 0X3F) | 0X40;

  if (NewState != DISABLE)
  {
    US1CON0 |= 0X80;
  }
  else
  {
    US1CON0 &= (~0X80);
  }
}
/*****************************************************
*��������:void USCI1_SPI_SendData_8(uint8_t Data)
*��������:USCI1 SPI��������
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI1_SPI_SendData_8(uint8_t Data)
{
  US1CON2 = Data;
}

/*****************************************************
*��������:uint8_t USCI1_SPI_ReceiveData_8(void)
*��������:���US1CON2�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI1_SPI_ReceiveData_8(void)
{
  return US1CON2;
}

/*****************************************************
*��������:void USCI1_SPI_SendData_16(uint16_t Data)
*��������:US1CON2 SPI��������
*��ڲ���:
uint16_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI1_SPI_SendData_16(uint16_t Data)
{
  US1CON3 = (uint8_t)(Data >> 8);
  US1CON2 = (uint8_t)Data;
}

/*****************************************************
*��������:uint16_t USCI1_SPI_ReceiveData_16(void)
*��������:���US1CON2�е�ֵ
*��ڲ���:void
*���ڲ���:
uint16_t:���յ�����
*****************************************************/
uint16_t USCI1_SPI_ReceiveData_16(void)
{
  uint16_t SPI_data;
  SPI_data = (uint16_t)((US1CON3 << 8) | US1CON2);
  return SPI_data;
}

/**************************************************
*��������:void USCI1_TWI_Slave_Init(uint8_t TWI_Address)
*��������:USCI1 TWI�ӻ���ʼ�����ú���
*��ڲ���:
uint8_t:TWI_Address:TWI��Ϊ�ӻ�ʱ��7λ�ӻ���ַ
*���ڲ���:void
**************************************************/
void USCI1_TWI_Slave_Init(uint8_t TWI_Address)
{
  OTCON = OTCON & 0X3F | 0X80;
  US1CON2 = TWI_Address << 1;
}

/**************************************************
*��������:void USCI1_TWI_MasterCommunicationRate(USCI1_TWI_MasterCommunicationRate_TypeDef TWI_MasterCommunicationRate)
*��������:USCI1 TWI����ģʽ��ͨѶ�����趨
*��ڲ���:
USCI1_TWI_MasterCommunicationRate_TypeDef:TWI_MasterCommunicationRate:TWI����ģʽ��ͨѶ����
*���ڲ���:void
**************************************************/
void USCI1_TWI_MasterCommunicationRate(USCI1_TWI_MasterCommunicationRate_TypeDef
                                           TWI_MasterCommunicationRate)
{
  OTCON = OTCON & 0X3F | 0X80;
  US1CON1 |= TWI_MasterCommunicationRate;
}

/**************************************************
*��������:void USCI1_TWI_Start(void)
*��������:USCI1 TWI ��ʼλ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI1_TWI_Start(void)
{
  US1CON1 |= 0x20;
}

/**************************************************
*��������:void USCI1_TWI_MasterModeStop(void)
*��������:USCI1 TWI����ģʽֹͣλ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI1_TWI_MasterModeStop(void)
{
  US1CON1 |= 0x10;
}

/**************************************************
*��������:void USCI1_TWI_SlaveClockExtension(FunctionalState NewState)
*��������:USCI1 TWI�ӻ�ģʽʱ���ӳ�����λ
*��ڲ���:
FunctionalState:NewState:ʹ��/ʧ��ѡ��
*���ڲ���:void
**************************************************/
void USCI1_TWI_SlaveClockExtension(FunctionalState NewState)
{
  OTCON = OTCON & 0X3F | 0X80;

  if (NewState != DISABLE)
  {
    US1CON1 |= 0x40;
  }
  else
  {
    US1CON1 &= 0XBF;
  }
}

/**************************************************
*��������:void USCI1_TWI_AcknowledgeConfig(FunctionalState NewState)
*��������:TWI����Ӧ��ʹ�ܺ���
*��ڲ���:
FunctionalState:NewState:����Ӧ��ʹ��/ʧ��ѡ��
*���ڲ���:void
**************************************************/
void USCI1_TWI_AcknowledgeConfig(FunctionalState NewState)
{
  OTCON = OTCON & 0X3F | 0X80;

  if (NewState != DISABLE)
  {
    US1CON0 |= 0X08;
  }
  else
  {
    US1CON0 &= 0XF7;
  }
}

/**************************************************
*��������:void USCI1_TWI_GeneralCallCmd(FunctionalState NewState)
*��������:TWIͨ�õ�ַ��Ӧʹ�ܺ���
*��ڲ���:
FunctionalState:NewState:����Ӧ��ʹ��/ʧ��ѡ��
*���ڲ���:void
**************************************************/
void USCI1_TWI_GeneralCallCmd(FunctionalState NewState)
{
  OTCON = OTCON & 0X3F | 0X80;

  if (NewState != DISABLE)
  {
    US1CON2 |= 0X01;
  }
  else
  {
    US1CON2 &= 0XFE;
  }
}

/*****************************************************
*��������:FlagStatus USCI1_GetTWIStatus(USCI1_TWIState_TypeDef USCI1_TWIState)
*��������:��ȡTWI״̬
*��ڲ���:
USCI1_TWIState_TypeDef:USCI1_TWIState:TWI״̬����
*���ڲ���:
FlagStatus:USCI1_TWI��־״̬	
*****************************************************/
FlagStatus USCI1_GetTWIStatus(USCI1_TWIState_TypeDef USCI1_TWIState)
{
  if ((US1CON0 & 0x07) == USCI1_TWIState)
    return SET;
  else
    return RESET;
}

/*****************************************************
*��������:void USCI1_TWI_Cmd(FunctionalState NewState)
*��������:TWI���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void USCI1_TWI_Cmd(FunctionalState NewState)
{
  OTCON = OTCON & 0X3F | 0X80;

  if (NewState != DISABLE)
  {
    US1CON0 |= 0X80;
  }
  else
  {
    US1CON0 &= (~0X80);
  }
}

/*****************************************************
*��������:void USCI1_TWI_SendData(uint8_t Data)
*��������:TWI��������
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI1_TWI_SendData(uint8_t Data)
{
  US1CON3 = Data;
}

/*****************************************************
*��������:uint8_t USCI1_TWI_SendData(void)
*��������:���US1CON3�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI1_TWI_ReceiveData(void)
{
  return US1CON3;
}

/**************************************************
*��������:void USCI1_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI1_UART_Mode_TypeDef Mode, USCI1_UART_RX_TypeDef RxMode)
*��������:UART��ʼ�����ú���
*��ڲ���:
uint32_t:UARTFsys:ϵͳʱ��Ƶ��
uint32_t:BaudRate:������
USCI1_UART_Mode_TypeDef:Mode:UART1����ģʽ
USCI1_UART_RX_TypeDef:RxMode:��������ѡ��
*���ڲ���:void
**************************************************/
void USCI1_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI1_UART_Mode_TypeDef Mode,
                     USCI1_UART_RX_TypeDef RxMode)
{
  OTCON |= 0xC0;
  US1CON0 = US1CON0 & 0X0F | Mode | RxMode;

  if (Mode == USCI1_UART_Mode_8B)
  {
    if (BaudRate == USCI1_UART_BaudRate_FsysDIV12)
    {
      US1CON0 &= 0XDF;
    }
    else if (BaudRate == USCI1_UART_BaudRate_FsysDIV4)
    {
      US1CON0 |= 0X20;
    }
  }
  else
  {
    US1CON2 = UARTFsys / BaudRate / 256;
    US1CON1 = UARTFsys / BaudRate % 256;
  }
}

/*****************************************************
*��������:void USCI1_UART_SendData8(uint8_t Data)
*��������:USCI1 UART1����8λ����
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI1_UART_SendData8(uint8_t Data)
{	
	US1CON3 = Data;
}

/*****************************************************
*��������:uint8_t USCI1_UART_ReceiveData8(void)
*��������:���US1CON3�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI1_UART_ReceiveData8(void)
{
  return US1CON3;
}

/*****************************************************
*��������:void USCI1_UART_SendData9(uint16_t Data)
*��������:UART1����9λ����
*��ڲ���:
uint16_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI1_UART_SendData9(uint16_t Data)
{
  uint8_t Data_9Bit;
  Data_9Bit = (Data >> 8);

  if (Data_9Bit)
  {
    US1CON0 |= 0x08;
  }
  else
  {
    US1CON0 &= 0xf7;
  }

  US1CON3 = (uint8_t)Data;
}

/*****************************************************
*��������:uint16_t USCI1_UART_ReceiveData9(void)
*��������:���US1CON3�е�ֵ���ھ�λ��ֵ
*��ڲ���:void
*���ڲ���:
uint16_t:���յ�����
*****************************************************/
uint16_t USCI1_UART_ReceiveData9(void)
{
  uint16_t Data9;
  Data9 = US1CON3 + ((uint16_t)(US1CON0 & 0X04) << 6);
  return Data9;
}

/*****************************************************
*��������:void USCI1_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:USCI1�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void USCI1_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  if (NewState != DISABLE)
  {
    IE2 |= 0x01;
  }
  else
  {
    IE2 &= 0xFE;
  }

  /************************************************************/
  if (Priority != LOW)
  {
    IP2 |= 0x01;
  }
  else
  {
    IP2 &= 0xFE;
  }
}

/*****************************************************
*��������:FlagStatus USCI1_GetFlagStatus(USCI1_Flag_TypeDef USCI1_FLAG)
*��������:���USCI1��־״̬
*��ڲ���:
USCI1_Flag_Typedef:USCI1_Flag:�жϱ�־λѡ��
*���ڲ���:
FlagStatus:USCI1��־״̬
*****************************************************/
FlagStatus USCI1_GetFlagStatus(USCI1_Flag_TypeDef USCI1_FLAG)
{
  FlagStatus bitstatus = RESET;
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx)

  if ((USCI1_FLAG == USCI1_SPI_FLAG_SPIF) || (USCI1_FLAG == USCI1_SPI_FLAG_WCOL) || (USCI1_FLAG == USCI1_TWI_FLAG_TXRXnE))
#endif
#if defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)
    if ((USCI1_FLAG == USCI1_SPI_FLAG_SPIF) || (USCI1_FLAG == USCI1_SPI_FLAG_WCOL) || (USCI1_FLAG == USCI1_SPI_FLAG_TXE) || (USCI1_FLAG == USCI1_TWI_FLAG_TXRXnE))
#endif
    {
      if ((USCI1_FLAG & US1CON1) != (uint8_t)RESET)
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
      if ((USCI1_FLAG & US1CON0) != (uint8_t)RESET)
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
*��������:void USCI1_ClearFlag(USCI1_Flag_TypeDef USCI1_FLAG)
*��������:���USCI1��־״̬
*��ڲ���:
USCI1_Flag_TypeDef:USCI1_FLAG:��������ı�־λ
*���ڲ���:void
*****************************************************/
void USCI1_ClearFlag(USCI1_Flag_TypeDef USCI1_FLAG)
{
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx)

  if ((USCI1_FLAG == USCI1_SPI_FLAG_SPIF) || (USCI1_FLAG == USCI1_SPI_FLAG_WCOL) || (USCI1_FLAG == USCI1_TWI_FLAG_TXRXnE))

#elif defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
			|| defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)

  if ((USCI1_FLAG == USCI1_SPI_FLAG_SPIF) || (USCI1_FLAG == USCI1_SPI_FLAG_WCOL) || (USCI1_FLAG == USCI1_SPI_FLAG_TXE) || (USCI1_FLAG == USCI1_TWI_FLAG_TXRXnE))

#endif
  {
    US1CON1 &= (~USCI1_FLAG); //�����Ĵ���US1CON1
  }
  else if ((USCI1_FLAG == USCI1_UART_FLAG_TI) || (USCI1_FLAG == USCI1_UART_FLAG_RI))
  {
#if defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)
    US1CON0 = US1CON0  & 0xFC | USCI1_FLAG; //д1����
#else
    US1CON0 &= (~USCI1_FLAG); //д0����
#endif
  }
  else
  {
    US1CON0 &= (~USCI1_FLAG); //�����Ĵ���US1CON0
  }
}

/*****************************************************
*��������:void USCI1_TWI_SendAddr(uint8_t Addr,USCI1_TWI_RWType RW)
*��������:TWI���͵�ַ����д����
*��ڲ���:
uint8_t:Addr:���͵ĵ�ַ 0~127
USCI1_TWI_RWType:RW:��д����
*���ڲ���:void
*****************************************************/
void USCI1_TWI_SendAddr(uint8_t Addr, USCI1_TWI_RWType RW)
{
  US1CON3 = (Addr << 1) | RW;
}

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/
