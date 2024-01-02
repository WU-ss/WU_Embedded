//************************************************************
//  Copyright (c) 
//	�ļ�����:			sc95f_usci2.c
//	����:
//	ģ�鹦��:			USCI2�̼��⺯��C�ļ�
//  ����������:	2022��7��22��
// 	�汾:					V1.10006
//  ˵��:					���ļ���������SC95Fxx1x��SC95Fxx2xϵ��оƬ
//*************************************************************

#include "sc95f_usci2.h"

#if defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)\
 || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)
void USCI2_DeInit(void)
{
  USXINX &= 0xF8;
  USXINX |= 0X02;
  TMCON &= 0X3F;
  USXCON0 = 0X00;
  USXCON1 = 0X00;
  USXCON2 = 0X00;
  USXCON3 = 0X00;
  IE2 &= (~0X02);
  IP2 &= (~0X02);
}

/**************************************************
*��������:void USCI2_SPI_Init(USCI2_SPI_FirstBit_TypeDef FirstBit, USCI2_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler,USCI2_SPI_Mode_TypeDef Mode,
							 USCI2_SPI_ClockPolarity_TypeDef ClockPolarity, USCI2_SPI_ClockPhase_TypeDef ClockPhase,USCI2_SPI_TXE_INT_TypeDef SPI_TXE_INT,USCI2_TransmissionMode_TypeDef TransmissionMode)
*��������:SPI��ʼ�����ú���
*��ڲ���:
USCI2_SPI_FirstBit_TypeDef:FirstBit:���ȴ���λѡ��MSB/LSB��
USCI2_SPI_BaudRatePrescaler_TypeDef:BaudRatePrescaler:SPIʱ��Ƶ��ѡ��
USCI2_SPI_Mode_TypeDef:Mode:SPI����ģʽѡ��
USCI2_SPI_ClockPolarity_TypeDef:ClockPolarity:SPIʱ�Ӽ���ѡ��
USCI2_SPI_ClockPhase_TypeDef:ClockPhase:SPIʱ����λѡ��
USCI2_SPI_TXE_INT_TypeDef:SPI_TXE_INT:���ͻ������ж�����ѡ��,�ù�����SC95FXX1XоƬ����Ч
USCI2_TransmissionMode_TypeDef:TransmissionMode:SPI����ģʽѡ�� 8/16λ
*���ڲ���:void
**************************************************/
void USCI2_SPI_Init(USCI2_SPI_FirstBit_TypeDef FirstBit,
                    USCI2_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, USCI2_SPI_Mode_TypeDef Mode,
                    USCI2_SPI_ClockPolarity_TypeDef ClockPolarity, USCI2_SPI_ClockPhase_TypeDef ClockPhase,
                    USCI2_SPI_TXE_INT_TypeDef SPI_TXE_INT, USCI2_TransmissionMode_TypeDef TransmissionMode)
{
  USXINX &= 0xF8;
  USXINX |= 0X02;
  TMCON = (TMCON & 0X3F) | 0X40;
  USXCON1 = USXCON1 & (~0X05) | FirstBit | SPI_TXE_INT | TransmissionMode;

  USXCON0 = USXCON0 & 0X80 | BaudRatePrescaler | Mode | ClockPolarity | ClockPhase;
}

/**************************************************
*��������:void USCI2_TransmissionMode(USCI2_TransmissionMode_TypeDef TransmissionMode)
*��������:SPI ����ģʽ���ú���
*��ڲ���:
USCI2_TransmissionMode_TypeDef:TransmissionMode:SPI����ģʽѡ�� 8/16eλ
*���ڲ���:void
**************************************************/
void USCI2_TransmissionMode(USCI2_TransmissionMode_TypeDef TransmissionMode)
{
  USXINX &= 0xF8;
  USXINX |= 0X02;
  TMCON = (TMCON & 0X3F) | 0X40;
  if (TransmissionMode == USCI2_SPI_DATA8)
  {
    USXCON1 &= 0xFD;
  }
  else
  {
    USXCON1 |= 0x02;
  }
}

/*****************************************************
*��������:void USCI2_SPI_Cmd(FunctionalState NewState)
*��������:SPI���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void USCI2_SPI_Cmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
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
*��������:void USCI2_SPI_SendData_8(uint8_t Data)
*��������:USCI2 SPI��������
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI2_SPI_SendData_8(uint8_t Data)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
  USXCON2 = Data;
}

/*****************************************************
*��������:uint8_t USCI2_SPI_ReceiveData_8(void)
*��������:���USXCON2�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI2_SPI_ReceiveData_8(void)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
  return USXCON2;
}

/*****************************************************
*��������:void USCI2_SPI_SendData_16(uint16_t Data)
*��������:USXCON2 SPI��������
*��ڲ���:
uint16_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI2_SPI_SendData_16(uint16_t Data)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
  USXCON3 = (uint8_t)(Data >> 8);
  USXCON2 = (uint8_t)Data;
}

/*****************************************************
*��������:uint16_t USCI2_SPI_ReceiveData_16(void)
*��������:���USXCON2�е�ֵ
*��ڲ���:void
*���ڲ���:
uint16_t:���յ�����
*****************************************************/
uint16_t USCI2_SPI_ReceiveData_16(void)
{
  uint16_t SPI_data;
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
  SPI_data = (uint16_t)((USXCON3 << 8) | USXCON2);
  return SPI_data;
}

/**************************************************
*��������:void USCI2_TWI_Slave_Init(uint8_t TWI_Address)
*��������:USCI2 TWI �ӻ���ʼ�����ú���
*��ڲ���:
uint8_t:TWI_Address:TWI��Ϊ�ӻ�ʱ��7λ�ӻ���ַ
*���ڲ���:void
**************************************************/
void USCI2_TWI_Slave_Init(uint8_t TWI_Address)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
  TMCON = TMCON & 0X3F | 0X80;
  USXCON2 = TWI_Address << 1;
}

/**************************************************
*��������:void USCI2_TWI_MasterCommunicationRate(USCI2_TWI_MasterCommunicationRate_TypeDef TWI_MasterCommunicationRate)
*��������:USCI2 TWI����ģʽ��ͨѶ�����趨
*��ڲ���:
USCI2_TWI_MasterCommunicationRate_TypeDef:TWI_MasterCommunicationRate:TWI����ģʽ��ͨѶ����
*���ڲ���:void
**************************************************/
void USCI2_TWI_MasterCommunicationRate(USCI2_TWI_MasterCommunicationRate_TypeDef
                                           TWI_MasterCommunicationRate)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
  TMCON = TMCON & 0X3F | 0X80; //ѡ��usci2ΪTWI

  USXCON1 = TWI_MasterCommunicationRate;
}

/**************************************************
*��������:void USCI2_TWI_Start(void)
*��������:USCI2 TWI ��ʼλ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI2_TWI_Start(void)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
  USXCON1 |= 0x20;
}

/**************************************************
*��������:void USCI2_TWI_MasterModeStop(void)
*��������:USCI2 TWI����ģʽֹͣλ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI2_TWI_MasterModeStop(void)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
  USXCON1 |= 0x10;
}

/**************************************************
*��������:void USCI2_TWI_SlaveClockExtension(void)
*��������:USCI2 TWI�ӻ�ģʽʱ���ӳ�����λ
*��ڲ���:
FunctionalState:NewState:ʹ��/ʧ��ѡ��
*���ڲ���:void
**************************************************/
void USCI2_TWI_SlaveClockExtension(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
  TMCON = TMCON & 0X3F | 0X80;

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
*��������:void USCI2_TWI_AcknowledgeConfig(FunctionalState NewState)
*��������:TWI����Ӧ��ʹ�ܺ���
*��ڲ���:
FunctionalState:NewState:����Ӧ��ʹ��/ʧ��ѡ��
*���ڲ���:void
**************************************************/
void USCI2_TWI_AcknowledgeConfig(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
  TMCON = TMCON & 0X3F | 0X80;

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
*��������:void USCI2_TWI_GeneralCallCmd(FunctionalState NewState)
*��������:TWIͨ�õ�ַ��Ӧʹ�ܺ���
*��ڲ���:
FunctionalState:NewState:ͨ�õ�ַ��Ӧʹ��/ʧ��ѡ��
*���ڲ���:void
**************************************************/
void USCI2_TWI_GeneralCallCmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
  TMCON = TMCON & 0X3F | 0X80;

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
*��������:FlagStatus USCI2_GetTWIStatus(USCI2_TWIState_TypeDef USCI2_TWIState)
*��������:��ȡTWI״̬
*��ڲ���:
USCI2_TWIState_TypeDef:USCI2_TWIState:TWI״̬����
*���ڲ���:
FlagStatus:USCI2_TWI��־״̬	
*****************************************************/
FlagStatus USCI2_GetTWIStatus(USCI2_TWIState_TypeDef USCI2_TWIState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
  if ((USXCON0 & 0x07) == USCI2_TWIState)
    return SET;
  else
    return RESET;
}

/*****************************************************
*��������:void USCI2_TWI_Cmd(FunctionalState NewState)
*��������:TWI���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void USCI2_TWI_Cmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
  TMCON = TMCON & 0X3F | 0X80;

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
*��������:void USCI2_TWI_SendData(uint8_t Data)
*��������:TWI��������
*��ڲ���:
uint8_t:Data:���͵�����/��ַ
*���ڲ���:void
*****************************************************/
void USCI2_TWI_SendData(uint8_t Data)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
  USXCON3 = Data;
}
/*****************************************************
*��������:void USCI2_TWI_SendAddr(uint8_t Addr,USCI2_TWI_RWType RW)
*��������:TWI���͵�ַ����д����
*��ڲ���:
uint8_t:Addr:���͵ĵ�ַ
USCI2_TWI_RWType:RW:��д����
*���ڲ���:void
*****************************************************/
void USCI2_TWI_SendAddr(uint8_t Addr, USCI2_TWI_RWType RW)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
  USXCON3 = (Addr << 1) | RW;
}
/*****************************************************
*��������:uint8_t USCI2_TWI_ReceiveData(void)
*��������:���USXCON3�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI2_TWI_ReceiveData(void)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
  return USXCON3;
}

/**************************************************
*��������:void USCI2_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI2_UART_Mode_TypeDef Mode, USCI2_UART_RX_TypeDef RxMode)
*��������:UART��ʼ�����ú���
*��ڲ���:
uint32_t:UARTFsys:ϵͳʱ��Ƶ��
uint32_t:BaudRate:������
USCI2_UART_Mode_TypeDef:Mode:UART����ģʽ
USCI2_UART_RX_TypeDef:RxMode:��������ѡ��
*���ڲ���:void
**************************************************/
void USCI2_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI2_UART_Mode_TypeDef Mode,
                     USCI2_UART_RX_TypeDef RxMode)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
  TMCON = TMCON & 0X3F | 0XC0; //ѡ��USCI2ΪUART
  USXCON0 = USXCON0 & 0X0F | Mode | RxMode;

  if (Mode == USCI2_UART_Mode_8B)
  {
    if (BaudRate == USCI2_UART_BaudRate_FsysDIV12)
    {
      USXCON0 &= 0XDF;
    }
    else if (BaudRate == USCI2_UART_BaudRate_FsysDIV4)
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
*��������:void USCI2_UART_SendData8(uint8_t Data)
*��������:USCI2_UART����8λ����
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI2_UART_SendData8(uint8_t Data)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
  USXCON3 = Data;
}

/*****************************************************
*��������:uint8_t USCI2_UART_ReceiveData8(void)
*��������:���USXCON3�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI2_UART_ReceiveData8(void)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
  return USXCON3;
}

/*****************************************************
*��������:void USCI2_UART_SendData9(uint16_t Data)
*��������:UART����9λ����
*��ڲ���:
uint16_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI2_UART_SendData9(uint16_t Data)
{
  uint8_t Data_9Bit;
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;

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
*��������:uint16_t USCI2_UART_ReceiveData9(void)
*��������:���USXCON3�е�ֵ���ھ�λ��ֵ
*��ڲ���:void
*���ڲ���:
uint16_t:���յ�����
*****************************************************/
uint16_t USCI2_UART_ReceiveData9(void)
{
  uint16_t Data9;
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;

  Data9 = USXCON3 + ((uint16_t)(USXCON0 & 0X04) << 6);
  return Data9;
}

/*****************************************************
*��������:void USCI2_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:USCI2�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void USCI2_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
  if (NewState != DISABLE)
  {
    IE2 |= 0x02;
  }
  else
  {
    IE2 &= 0xFD;
  }

  /************************************************************/
  if (Priority != LOW)
  {
    IP2 |= 0x02;
  }
  else
  {
    IP2 &= 0xFD;
  }
}

/*****************************************************
*��������:FlagStatus USCI2_GetFlagStatus(USCI2_Flag_TypeDef USCI2_FLAG)
*��������:���USCI2��־״̬
*��ڲ���:
USCI2_Flag_Typedef:USCI2_Flag:�жϱ�־λѡ��
*���ڲ���:
FlagStatus:USCI2��־״̬
*****************************************************/
FlagStatus USCI2_GetFlagStatus(USCI2_Flag_TypeDef USCI2_FLAG)
{
  FlagStatus bitstatus = RESET;
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx)
  if ((USCI2_FLAG == USCI2_SPI_FLAG_SPIF) || (USCI2_FLAG == USCI2_SPI_FLAG_WCOL) || (USCI2_FLAG == USCI2_TWI_FLAG_TXRXnE))
#endif
#if defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)
    if ((USCI2_FLAG == USCI2_SPI_FLAG_SPIF) || (USCI2_FLAG == USCI2_SPI_FLAG_WCOL) || (USCI2_FLAG == USCI2_SPI_FLAG_TXE) || (USCI2_FLAG == USCI2_TWI_FLAG_TXRXnE))
#endif
    {
      if ((USCI2_FLAG & USXCON1) != (uint8_t)RESET)
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
      if ((USCI2_FLAG & USXCON0) != (uint8_t)RESET)
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
*��������:void USCI2_ClearFlag(USCI2_Flag_TypeDef USCI2_FLAG)
*��������:���USCI2��־״̬
*��ڲ���:
USCI2_Flag_TypeDef:USCI2_FLAG:��������ı�־λ
*���ڲ���:void
*****************************************************/
void USCI2_ClearFlag(USCI2_Flag_TypeDef USCI2_FLAG)
{
  USXINX &= 0xF8; //��USCIX�Ĵ���ָ��USCI2
  USXINX |= 0X02;
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx)

  if ((USCI2_FLAG == USCI2_SPI_FLAG_SPIF) || (USCI2_FLAG == USCI2_SPI_FLAG_WCOL) || (USCI2_FLAG == USCI2_TWI_FLAG_TXRXnE))

#elif defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
	|| defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)

  if ((USCI2_FLAG == USCI2_SPI_FLAG_SPIF) || (USCI2_FLAG == USCI2_SPI_FLAG_WCOL) || (USCI2_FLAG == USCI2_SPI_FLAG_TXE) || (USCI2_FLAG == USCI2_TWI_FLAG_TXRXnE))

#endif
  {
    USXCON1 &= (~USCI2_FLAG); //�����Ĵ���USXCON1
  }
  else if ((USCI2_FLAG == USCI2_UART_FLAG_TI) || (USCI2_FLAG == USCI2_UART_FLAG_RI))
  {
#if defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)
    USXCON0 = USXCON0  & 0xFC | USCI2_FLAG; //д1����
#else
    USXCON0 &= (~USCI2_FLAG); //д0����
#endif
  }
  else
  {
    USXCON0 &= (~USCI2_FLAG); //�����Ĵ���USXCON0
  }
}
#else

/**************************************************
*��������:void USCI2_DeInit(void)
*��������:USCI2��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI2_DeInit(void)
{
  TMCON &= 0X3F;
  US2CON0 = 0X00;
  US2CON1 = 0X00;
  US2CON2 = 0X00;
  US2CON3 = 0X00;
  IE2 &= (~0X02);
  IP2 &= (~0X02);
}

/**************************************************
*��������:void USCI2_SPI_Init(USCI2_SPI_FirstBit_TypeDef FirstBit, USCI2_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler,USCI2_SPI_Mode_TypeDef Mode,
							 USCI2_SPI_ClockPolarity_TypeDef ClockPolarity, USCI2_SPI_ClockPhase_TypeDef ClockPhase,USCI2_SPI_TXE_INT_TypeDef SPI_TXE_INT,USCI2_TransmissionMode_TypeDef TransmissionMode)
*��������:SPI��ʼ�����ú���
*��ڲ���:
USCI2_SPI_FirstBit_TypeDef:FirstBit:���ȴ���λѡ��MSB/LSB��
USCI2_SPI_BaudRatePrescaler_TypeDef:BaudRatePrescaler:SPIʱ��Ƶ��ѡ��
USCI2_SPI_Mode_TypeDef:Mode:SPI����ģʽѡ��
USCI2_SPI_ClockPolarity_TypeDef:ClockPolarity:SPIʱ�Ӽ���ѡ��
USCI2_SPI_ClockPhase_TypeDef:ClockPhase:SPIʱ����λѡ��
USCI2_SPI_TXE_INT_TypeDef:SPI_TXE_INT:���ͻ������ж�����ѡ��,�ù�����SC95FXX1XоƬ����Ч
USCI2_TransmissionMode_TypeDef:TransmissionMode:SPI����ģʽѡ�� 8/16λ
*���ڲ���:void
**************************************************/
void USCI2_SPI_Init(USCI2_SPI_FirstBit_TypeDef FirstBit,
                    USCI2_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, USCI2_SPI_Mode_TypeDef Mode,
                    USCI2_SPI_ClockPolarity_TypeDef ClockPolarity, USCI2_SPI_ClockPhase_TypeDef ClockPhase,
                    USCI2_SPI_TXE_INT_TypeDef SPI_TXE_INT, USCI2_TransmissionMode_TypeDef TransmissionMode)
{
  TMCON = (TMCON & 0X3F) | 0X40;
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx)
  SPI_TXE_INT = USCI2_SPI_TXE_DISINT; //SPI_TXE_INT�ù�����SC95FXX1XоƬ����Ч
  US2CON1 = US2CON1 & (~0X05) | FirstBit | TransmissionMode;
#endif
#if defined(SC95F8x2x) || defined(SC95F7x2x)
  US2CON1 = US2CON1 & (~0X05) | FirstBit | SPI_TXE_INT | TransmissionMode;
#endif
  US2CON0 = US2CON0 & 0X80 | BaudRatePrescaler | Mode | ClockPolarity | ClockPhase;
}

/**************************************************
*��������:void USCI2_TransmissionMode(USCI2_TransmissionMode_TypeDef TransmissionMode)
*��������:SPI ����ģʽ���ú���
*��ڲ���:
USCI2_TransmissionMode_TypeDef:TransmissionMode:SPI����ģʽѡ�� 8/16eλ
*���ڲ���:void
**************************************************/
void USCI2_TransmissionMode(USCI2_TransmissionMode_TypeDef TransmissionMode)
{

  TMCON = (TMCON & 0X3F) | 0X40;
  if (TransmissionMode == USCI2_SPI_DATA8)
  {
    US2CON1 &= 0xFD;
  }
  else
  {
    US2CON1 |= 0x02;
  }
}

/*****************************************************
*��������:void USCI2_SPI_Cmd(FunctionalState NewState)
*��������:SPI���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void USCI2_SPI_Cmd(FunctionalState NewState)
{
  TMCON = (TMCON & 0X3F) | 0X40;

  if (NewState != DISABLE)
  {
    US2CON0 |= 0X80;
  }
  else
  {
    US2CON0 &= (~0X80);
  }
}

/*****************************************************
*��������:void USCI2_SPI_SendData_8(uint8_t Data)
*��������:USCI2 SPI��������
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI2_SPI_SendData_8(uint8_t Data)
{
  US2CON2 = Data;
}

/*****************************************************
*��������:uint8_t USCI2_SPI_ReceiveData_8(void)
*��������:���US2CON2�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI2_SPI_ReceiveData_8(void)
{
  return US2CON2;
}

/*****************************************************
*��������:void USCI2_SPI_SendData_16(uint16_t Data)
*��������:US2CON2 SPI��������
*��ڲ���:
uint16_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI2_SPI_SendData_16(uint16_t Data)
{
  US2CON3 = (uint8_t)(Data >> 8);
  US2CON2 = (uint8_t)Data;
}

/*****************************************************
*��������:uint16_t USCI2_SPI_ReceiveData_16(void)
*��������:���US2CON2�е�ֵ
*��ڲ���:void
*���ڲ���:
uint16_t:���յ�����
*****************************************************/
uint16_t USCI2_SPI_ReceiveData_16(void)
{
  uint16_t SPI_data;
  SPI_data = (uint16_t)((US2CON3 << 8) | US2CON2);
  return SPI_data;
}

/**************************************************
*��������:void USCI2_TWI_Slave_Init(uint8_t TWI_Address)
*��������:USCI2 TWI �ӻ���ʼ�����ú���
*��ڲ���:
uint8_t:TWI_Address:TWI��Ϊ�ӻ�ʱ��7λ�ӻ���ַ
*���ڲ���:void
**************************************************/
void USCI2_TWI_Slave_Init(uint8_t TWI_Address)
{
  TMCON = TMCON & 0X3F | 0X80;
  US2CON2 = TWI_Address << 1;
}

/**************************************************
*��������:void USCI2_TWI_MasterCommunicationRate(USCI2_TWI_MasterCommunicationRate_TypeDef TWI_MasterCommunicationRate)
*��������:USCI2 TWI����ģʽ��ͨѶ�����趨
*��ڲ���:
USCI2_TWI_MasterCommunicationRate_TypeDef:TWI_MasterCommunicationRate:TWI����ģʽ��ͨѶ����
*���ڲ���:void
**************************************************/
void USCI2_TWI_MasterCommunicationRate(USCI2_TWI_MasterCommunicationRate_TypeDef
                                           TWI_MasterCommunicationRate)
{
  TMCON = TMCON & 0X3F | 0X80; //ѡ��usci2ΪTWI

  US2CON1 = TWI_MasterCommunicationRate;
}

/**************************************************
*��������:void USCI2_TWI_Start(void)
*��������:USCI2 TWI ��ʼλ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI2_TWI_Start(void)
{
  US2CON1 |= 0x20;
}

/**************************************************
*��������:void USCI2_TWI_MasterModeStop(void)
*��������:USCI2 TWI����ģʽֹͣλ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI2_TWI_MasterModeStop(void)
{
  US2CON1 |= 0x10;
}

/**************************************************
*��������:void USCI2_TWI_SlaveClockExtension(void)
*��������:USCI2 TWI�ӻ�ģʽʱ���ӳ�����λ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI2_TWI_SlaveClockExtension(FunctionalState NewState)
{
  TMCON = TMCON & 0X3F | 0X80;

  if (NewState != DISABLE)
  {
    US2CON1 |= 0x40;
  }
  else
  {
    US2CON1 &= 0XBF;
  }
}

/**************************************************
*��������:void USCI2_TWI_AcknowledgeConfig(FunctionalState NewState)
*��������:TWI����Ӧ��ʹ�ܺ���
*��ڲ���:
FunctionalState:NewState:����Ӧ��ʹ��/ʧ��ѡ��
*���ڲ���:void
**************************************************/
void USCI2_TWI_AcknowledgeConfig(FunctionalState NewState)
{
  TMCON = TMCON & 0X3F | 0X80;

  if (NewState != DISABLE)
  {
    US2CON0 |= 0X08;
  }
  else
  {
    US2CON0 &= 0XF7;
  }
}

/**************************************************
*��������:void USCI2_TWI_GeneralCallCmd(FunctionalState NewState)
*��������:TWIͨ�õ�ַ��Ӧʹ�ܺ���
*��ڲ���:
FunctionalState:NewState:����Ӧ��ʹ��/ʧ��ѡ��
*���ڲ���:void
**************************************************/
void USCI2_TWI_GeneralCallCmd(FunctionalState NewState)
{
  TMCON = TMCON & 0X3F | 0X80;

  if (NewState != DISABLE)
  {
    US2CON2 |= 0X01;
  }
  else
  {
    US2CON2 &= 0XFE;
  }
}

/*****************************************************
*��������:FlagStatus USCI2_GetTWIStatus(USCI2_TWIState_TypeDef USCI2_TWIState)
*��������:��ȡTWI״̬
*��ڲ���:
USCI2_TWIState_TypeDef:USCI2_TWIState:TWI״̬����
*���ڲ���:
FlagStatus:USCI2_TWI��־״̬	
*****************************************************/
FlagStatus USCI2_GetTWIStatus(USCI2_TWIState_TypeDef USCI2_TWIState)
{
  if ((US2CON0 & 0x07) == USCI2_TWIState)
    return SET;
  else
    return RESET;
}

/*****************************************************
*��������:void USCI2_TWI_Cmd(FunctionalState NewState)
*��������:TWI���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void USCI2_TWI_Cmd(FunctionalState NewState)
{
  TMCON = TMCON & 0X3F | 0X80;

  if (NewState != DISABLE)
  {
    US2CON0 |= 0X80;
  }
  else
  {
    US2CON0 &= (~0X80);
  }
}

/*****************************************************
*��������:void USCI2_TWI_SendData(uint8_t Data)
*��������:TWI��������
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI2_TWI_SendData(uint8_t Data)
{
  US2CON3 = Data;
}
/*****************************************************
*��������:void USCI2_TWI_SendAddr(uint8_t Addr,USCI2_TWI_RWType RW)
*��������:TWI���͵�ַ����д����
*��ڲ���:
uint8_t:Addr:���͵ĵ�ַ
USCI2_TWI_RWType:RW:��д����
*���ڲ���:void
*****************************************************/
void USCI2_TWI_SendAddr(uint8_t Addr, USCI2_TWI_RWType RW)
{
  US2CON3 = (Addr << 1) | RW;
}
/*****************************************************
*��������:uint8_t USCI2_TWI_ReceiveData(void)
*��������:���US2CON3�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI2_TWI_ReceiveData(void)
{
  return US2CON3;
}

/**************************************************
*��������:void USCI2_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI2_UART_Mode_TypeDef Mode, USCI2_UART_RX_TypeDef RxMode)
*��������:UART��ʼ�����ú���
*��ڲ���:
uint32_t:UARTFsys:ϵͳʱ��Ƶ��
uint32_t:BaudRate:������
USCI2_UART_Mode_TypeDef:Mode:UART1����ģʽ
USCI2_UART_RX_TypeDef:RxMode:��������ѡ��
*���ڲ���:void
**************************************************/
void USCI2_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI2_UART_Mode_TypeDef Mode,
                     USCI2_UART_RX_TypeDef RxMode)
{
  TMCON |= 0xC0;
  US2CON0 = US2CON0 & 0X0F | Mode | RxMode;

  if (Mode == USCI2_UART_Mode_8B)
  {
    if (BaudRate == USCI2_UART_BaudRate_FsysDIV12)
    {
      US2CON0 &= 0XDF;
    }
    else if (BaudRate == USCI2_UART_BaudRate_FsysDIV4)
    {
      US2CON0 |= 0X20;
    }
  }
  else
  {
    US2CON2 = UARTFsys / BaudRate / 256;
    US2CON1 = UARTFsys / BaudRate % 256;
  }
}

/*****************************************************
*��������:void USCI2_UART_SendData8(uint8_t Data)
*��������:USCI2 UART1����8λ����
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI2_UART_SendData8(uint8_t Data)
{
  US2CON3 = Data;
}

/*****************************************************
*��������:uint8_t USCI2_UART_ReceiveData8(void)
*��������:���US2CON3�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI2_UART_ReceiveData8(void)
{
  return US2CON3;
}

/*****************************************************
*��������:void USCI2_UART_SendData9(uint16_t Data)
*��������:UART����9λ����
*��ڲ���:
uint16_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI2_UART_SendData9(uint16_t Data)
{
  uint8_t Data_9Bit;
  Data_9Bit = (Data >> 8);

  if (Data_9Bit)
  {
    US2CON0 |= 0x08;
  }
  else
  {
    US2CON0 &= 0xf7;
  }

  US2CON3 = (uint8_t)Data;
}

/*****************************************************
*��������:uint16_t USCI2_UART_ReceiveData9(void)
*��������:���US2CON3�е�ֵ���ھ�λ��ֵ
*��ڲ���:void
*���ڲ���:
uint16_t:���յ�����
*****************************************************/
uint16_t USCI2_UART_ReceiveData9(void)
{
  uint16_t Data9;
  Data9 = US2CON3 + ((uint16_t)(US2CON0 & 0X04) << 6);
  return Data9;
}

/*****************************************************
*��������:void USCI2_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:USCI2�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void USCI2_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  if (NewState != DISABLE)
  {
    IE2 |= 0x02;
  }
  else
  {
    IE2 &= 0xFD;
  }

  /************************************************************/
  if (Priority != LOW)
  {
    IP2 |= 0x02;
  }
  else
  {
    IP2 &= 0xFD;
  }
}

/*****************************************************
*��������:FlagStatus USCI2_GetFlagStatus(USCI2_Flag_TypeDef USCI2_FLAG)
*��������:���USCI2��־״̬
*��ڲ���:
USCI2_Flag_Typedef:USCI2_Flag:�����ȡ�ı�־λ
*���ڲ���:
FlagStatus:USCI2��־״̬
*****************************************************/
FlagStatus USCI2_GetFlagStatus(USCI2_Flag_TypeDef USCI2_FLAG)
{
  FlagStatus bitstatus = RESET;

#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx)

  if ((USCI2_FLAG == USCI2_SPI_FLAG_SPIF) || (USCI2_FLAG == USCI2_SPI_FLAG_WCOL))
#endif
#if defined(SC95F8x2x) || defined(SC95F7x2x)
    if ((USCI2_FLAG == USCI2_SPI_FLAG_SPIF) || (USCI2_FLAG == USCI2_SPI_FLAG_WCOL) || (USCI2_FLAG == USCI2_SPI_FLAG_TXE))
#endif
    {
      if ((USCI2_FLAG & US2CON1) != (uint8_t)RESET)
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
      if ((USCI2_FLAG & US2CON0) != (uint8_t)RESET)
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
*��������:void USCI2_ClearFlag(USCI2_Flag_TypeDef USCI2_FLAG)
*��������:���USCI2��־״̬
*��ڲ���:
USCI2_Flag_TypeDef:USCI2_FLAG:��������ı�־λ
*���ڲ���:void
*****************************************************/
void USCI2_ClearFlag(USCI2_Flag_TypeDef USCI2_FLAG)
{
  if ((USCI2_FLAG == USCI2_SPI_FLAG_SPIF) || (USCI2_FLAG == USCI2_SPI_FLAG_WCOL))
  {
    US2CON1 &= (~USCI2_FLAG);
  }
  else
  {
    US2CON0 &= (~USCI2_FLAG);
  }
}
#endif
/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/
