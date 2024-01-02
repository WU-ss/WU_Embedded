//************************************************************
//  Copyright (c) 
//	�ļ�����: 			sc95f_usci0.c
//	����:					��ԪӦ���Ŷ�
//	ģ�鹦��: 			USCI0�̼��⺯��C�ļ�
//  ����������:	2022��7��20��
// 	�汾: 				V1.10006
//  ˵��: 				���ļ���������SC95Fϵ��оƬ
//*************************************************************

#include "sc95f_usci0.h"

#if !defined (SC95R751) && !defined (SC95F7610B)
/**************************************************
*��������:void USCI0_DeInit(void)
*��������:USCI0��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI0_DeInit(void)
{
  OTCON &= 0XCF;
  US0CON0 = 0X00;
  US0CON1 = 0X00;
  US0CON2 = 0X00;
  US0CON3 = 0X00;
  IE1 &= (~0X01);
  IP1 &= (~0X01);
}

/**************************************************
*��������:void USCI0_SPI_Init(USCI0_SPI_FirstBit_TypeDef FirstBit, USCI0_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler,USCI0_SPI_Mode_TypeDef Mode,
							 USCI0_SPI_ClockPolarity_TypeDef ClockPolarity, USCI0_SPI_ClockPhase_TypeDef ClockPhase,USCI0_SPI_TXE_INT_TypeDef SPI_TXE_INT,USCI0_TransmissionMode_TypeDef TransmissionMode)
*��������:SPI��ʼ�����ú���
*��ڲ���:
USCI0_SPI_FirstBit_TypeDef:FirstBit:���ȴ���λѡ��MSB/LSB��
USCI0_SPI_BaudRatePrescaler_TypeDef:BaudRatePrescaler:SPIʱ��Ƶ��ѡ��
USCI0_SPI_Mode_TypeDef:Mode:SPI����ģʽѡ��
USCI0_SPI_ClockPolarity_TypeDef:ClockPolarity:SPIʱ�Ӽ���ѡ��
USCI0_SPI_ClockPhase_TypeDef:ClockPhase:SPIʱ����λѡ��
USCI0_SPI_TXE_INT_TypeDef:SPI_TXE_INT:���ͻ������ж�����ѡ��,�ù�����SC95FXX1XоƬ����Ч
USCI0_TransmissionMode_TypeDef:TransmissionMode:SPI����ģʽѡ�� 8/16λ
*���ڲ���:void
**************************************************/
void USCI0_SPI_Init(USCI0_SPI_FirstBit_TypeDef FirstBit,
                    USCI0_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, USCI0_SPI_Mode_TypeDef Mode,
                    USCI0_SPI_ClockPolarity_TypeDef ClockPolarity, USCI0_SPI_ClockPhase_TypeDef ClockPhase,
                    USCI0_SPI_TXE_INT_TypeDef SPI_TXE_INT, USCI0_TransmissionMode_TypeDef TransmissionMode)
{

  OTCON = (OTCON & 0XCF) | 0X10;
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx)
  SPI_TXE_INT = USCI0_SPI_TXE_DISINT; //SPI_TXE_INT�ù�����SC95FXX1XоƬ����Ч
  US0CON1 = US0CON1 & (~0X05) | FirstBit | TransmissionMode;
#endif
#if defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95F7619B)
  US0CON1 = US0CON1 & (~0X05) | FirstBit | SPI_TXE_INT | TransmissionMode;
#endif
  US0CON0 = US0CON0 & 0X80 | BaudRatePrescaler | Mode | ClockPolarity | ClockPhase;
}

/**************************************************
*��������:void USCI0_TransmissionMode(USCI0_TransmissionMode_TypeDef TransmissionMode)
*��������:SPI ����ģʽ���ú���
*��ڲ���:
USCI0_TransmissionMode_TypeDef:TransmissionMode:SPI����ģʽѡ�� 8/16eλ
*���ڲ���:void
**************************************************/
void USCI0_TransmissionMode(USCI0_TransmissionMode_TypeDef TransmissionMode)
{
  if (TransmissionMode == USCI0_SPI_DATA8)
  {
    US0CON1 &= 0xFD;
  }
  else
  {
    US0CON1 |= 0x02;
  }
}

/*****************************************************
*��������:void USCI0_SPI_Cmd(FunctionalState NewState)
*��������:SPI���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void USCI0_SPI_Cmd(FunctionalState NewState)
{
  OTCON = (OTCON & 0XCF) | 0X10;

  if (NewState != DISABLE)
  {
    US0CON0 |= 0X80;
  }
  else
  {
    US0CON0 &= (~0X80);
  }
}
/*****************************************************
*��������:void USCI0_SPI_SendData_8(uint8_t Data)
*��������:USCI0 SPI��������
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI0_SPI_SendData_8(uint8_t Data)
{
  US0CON2 = Data;
}

/*****************************************************
*��������:uint8_t USCI0_SPI_ReceiveData_8(void)
*��������:���US0CON2�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�������
*****************************************************/
uint8_t USCI0_SPI_ReceiveData_8(void)
{
  return US0CON2;
}

/*****************************************************
*��������:void USCI0_SPI_SendData_16(uint16_t Data)
*��������:US0CON2 SPI��������
*��ڲ���:
uint16_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI0_SPI_SendData_16(uint16_t Data)
{
  US0CON3 = (uint8_t)(Data >> 8);
  US0CON2 = (uint8_t)Data;
}

/*****************************************************
*��������:uint16_t USCI0_SPI_ReceiveData_16(void)
*��������:���US0CON2�е�ֵ
*��ڲ���:void
*���ڲ���:
uint16_t:���յ�����
*****************************************************/
uint16_t USCI0_SPI_ReceiveData_16(void)
{
  uint16_t SPI_data;
  SPI_data = (uint16_t)((US0CON3 << 8) | US0CON2);
  return SPI_data;
}

/**************************************************
*��������:void USCI0_TWI_Slave_Init(uint8_t TWI_Address)
*��������:USCI0 TWI�ӻ���ʼ�����ú���
*��ڲ���:
uint8_t:TWI_Address:TWI��Ϊ�ӻ�ʱ��7λ�ӻ���ַ
*���ڲ���:void
**************************************************/
void USCI0_TWI_Slave_Init(uint8_t TWI_Address)
{
  OTCON = OTCON & 0XCF | 0X20;
  US0CON2 = TWI_Address << 1;
}

/**************************************************
*��������:void USCI0_TWI_MasterCommunicationRate(USCI0_TWI_MasterCommunicationRate_TypeDef TWI_MasterCommunicationRate)
*��������:USCI0 TWI����ģʽ��ͨѶ�����趨
*��ڲ���:
USCI0_TWI_MasterCommunicationRate_TypeDef:TWI_MasterCommunicationRate:TWI����ģʽ��ͨѶ����
*���ڲ���:void
**************************************************/
void USCI0_TWI_MasterCommunicationRate(USCI0_TWI_MasterCommunicationRate_TypeDef
                                           TWI_MasterCommunicationRate)
{
  OTCON = OTCON & 0XCF | 0X20;
  US0CON1 |= TWI_MasterCommunicationRate;
}

/**************************************************
*��������:void USCI0_TWI_Start(void)
*��������:USCI0 TWI ��ʼλ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI0_TWI_Start(void)
{
  US0CON1 |= 0x20;
}

/**************************************************
*��������:void USCI0_TWI_MasterModeStop(void)
*��������:USCI0 TWI����ģʽֹͣλ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void USCI0_TWI_MasterModeStop(void)
{
  US0CON1 |= 0x10;
}

/**************************************************
*��������:void USCI0_TWI_SlaveClockExtension(void)
*��������:USCI0 TWI�ӻ�ģʽʱ���ӳ�����λ
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
**************************************************/
void USCI0_TWI_SlaveClockExtension(FunctionalState NewState)
{
  OTCON = OTCON & 0XCF | 0X20;

  if (NewState != DISABLE)
  {
    US0CON1 |= 0x40;
  }
  else
  {
    US0CON1 &= 0XBF;
  }
}

/**************************************************
*��������:void USCI0_TWI_AcknowledgeConfig(FunctionalState NewState)
*��������:TWI����Ӧ��ʹ�ܺ���
*��ڲ���:
FunctionalState:NewState:����Ӧ��ʹ��/ʧ��ѡ��
*���ڲ���:void
**************************************************/
void USCI0_TWI_AcknowledgeConfig(FunctionalState NewState)
{
  OTCON = OTCON & 0XCF | 0X20;

  if (NewState != DISABLE)
  {
    US0CON0 |= 0X08;
  }
  else
  {
    US0CON0 &= 0XF7;
  }
}

/**************************************************
*��������:void USCI0_TWI_GeneralCallCmd(FunctionalState NewState)
*��������:TWIͨ�õ�ַ��Ӧʹ�ܺ���
*��ڲ���:
FunctionalState:NewState:ͨ�õ�ַ��Ӧʹ��/ʧ��ѡ��
*���ڲ���:void
**************************************************/
void USCI0_TWI_GeneralCallCmd(FunctionalState NewState)
{
  OTCON = OTCON & 0XCF | 0X20;

  if (NewState != DISABLE)
  {
    US0CON2 |= 0X01;
  }
  else
  {
    US0CON2 &= 0XFE;
  }
}

/*****************************************************
*��������:FlagStatus USCI0_GetTWIStatus(USCI0_TWIState_TypeDef USCI0_TWIState)
*��������:��ȡTWI״̬
*��ڲ���:
USCI0_TWIState_TypeDef:USCI0_TWIState:TWI״̬����
*���ڲ���:
FlagStatus:USCI0_SC��־״̬	
*****************************************************/
FlagStatus USCI0_GetTWIStatus(USCI0_TWIState_TypeDef USCI0_TWIState)
{
  if ((US0CON0 & 0x07) == USCI0_TWIState)
    return SET;
  else
    return RESET;
}

/*****************************************************
*��������:void USCI0_TWI_Cmd(FunctionalState NewState)
*��������:TWI���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void USCI0_TWI_Cmd(FunctionalState NewState)
{
  OTCON = OTCON & 0XCF | 0X20;

  if (NewState != DISABLE)
  {
    US0CON0 |= 0X80;
  }
  else
  {
    US0CON0 &= (~0X80);
  }
}

/*****************************************************
*��������:void USCI0_TWI_SendData(uint8_t Data)
*��������:TWI��������
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI0_TWI_SendData(uint8_t Data)
{
  US0CON3 = Data;
}

/*****************************************************
*��������:uint8_t USCI0_TWI_SendData(void)
*��������:���US0CON3�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI0_TWI_ReceiveData(void)
{
  return US0CON3;
}

/**************************************************
*��������:void USCI0_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI0_UART_Mode_TypeDef Mode, USCI0_UART_RX_TypeDef RxMode)
*��������:UART��ʼ�����ú���
*��ڲ���:
uint32_t:UARTFsys:ϵͳʱ��Ƶ��
uint32_t:BaudRate:������
USCI0_UART_Mode_TypeDef:Mode:UART1����ģʽ
USCI0_UART_RX_TypeDef:RxMode:��������ѡ��
*���ڲ���:void
**************************************************/
void USCI0_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI0_UART_Mode_TypeDef Mode,
                     USCI0_UART_RX_TypeDef RxMode)
{
  OTCON |= 0x30;
  US0CON0 = US0CON0 & 0X0F | Mode | RxMode;

  if (Mode == USCI0_UART_Mode_8B)
  {
    if (BaudRate == USCI0_UART_BaudRate_FsysDIV12)
    {
      US0CON0 &= 0XDF;
    }
    else if (BaudRate == USCI0_UART_BaudRate_FsysDIV4)
    {
      US0CON0 |= 0X20;
    }
  }
  else
  {
    US0CON2 = UARTFsys / BaudRate / 256;
    US0CON1 = UARTFsys / BaudRate % 256;
  }
}

/*****************************************************
*��������:void USCI0_UART_SendData8(uint8_t Data)
*��������:USCI0 UART1����8λ����
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI0_UART_SendData8(uint8_t Data)
{
  US0CON3 = Data;
}

/*****************************************************
*��������:uint8_t USCI0_UART_ReceiveData8(void)
*��������:���US0CON3�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI0_UART_ReceiveData8(void)
{
  return US0CON3;
}

/*****************************************************
*��������:void USCI0_UART_SendData9(uint16_t Data)
*��������:UART1����9λ����
*��ڲ���:
uint16_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI0_UART_SendData9(uint16_t Data)
{
  uint8_t Data_9Bit;
  Data_9Bit = (Data >> 8);

  if (Data_9Bit)
  {
    US0CON0 |= 0x08;
  }
  else
  {
    US0CON0 &= 0xf7;
  }

  US0CON3 = (uint8_t)Data;
}

/*****************************************************
*��������:uint16_t USCI0_UART_ReceiveData9(void)
*��������:���US0CON3�е�ֵ���ھ�λ��ֵ
*��ڲ���:void
*���ڲ���:
uint16_t:���յ�����
*****************************************************/
uint16_t USCI0_UART_ReceiveData9(void)
{
  uint16_t Data9;
  Data9 = US0CON3 + ((uint16_t)(US0CON0 & 0X04) << 6);
  return Data9;
}

/*****************************************************
*��������:void USCI0_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:USCI0�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void USCI0_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  if (NewState != DISABLE)
  {
    IE1 |= 0x01;
  }
  else
  {
    IE1 &= 0xFE;
  }

  /************************************************************/
  if (Priority != LOW)
  {
    IP1 |= 0x01;
  }
  else
  {
    IP1 &= 0xFE;
  }
}

/*****************************************************
*��������:FlagStatus USCI0_GetFlagStatus(USCI0_Flag_TypeDef USCI0_FLAG)
*��������:���USCI0��־״̬
*��ڲ���:
USCI0_Flag_TypeDef:USCI0_FLAG:�����ȡ�ı�־λ
*���ڲ���:
FlagStatus:USCI0��־״̬
*****************************************************/
FlagStatus USCI0_GetFlagStatus(USCI0_Flag_TypeDef USCI0_FLAG)
{
  FlagStatus bitstatus = RESET;
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx)

  if ((USCI0_FLAG == USCI0_SPI_FLAG_SPIF) || (USCI0_FLAG == USCI0_SPI_FLAG_WCOL) || (USCI0_FLAG == USCI0_TWI_FLAG_TXRXnE))
#endif
#if defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95F7619B)
    if ((USCI0_FLAG == USCI0_SPI_FLAG_SPIF) || (USCI0_FLAG == USCI0_SPI_FLAG_WCOL) || (USCI0_FLAG == USCI0_SPI_FLAG_TXE) || (USCI0_FLAG == USCI0_TWI_FLAG_TXRXnE))
#endif
    {
      if ((USCI0_FLAG & US0CON1) != (uint8_t)RESET)
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
      if ((USCI0_FLAG & US0CON0) != (uint8_t)RESET)
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
*��������:void USCI0_ClearFlag(USCI0_Flag_TypeDef USCI0_FLAG)
*��������:���USCI0��־״̬
*��ڲ���:
USCI0_Flag_TypeDef:USCI0_FLAG:��������ı�־λ
*���ڲ���:void
*****************************************************/
void USCI0_ClearFlag(USCI0_Flag_TypeDef USCI0_FLAG)
{
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx)

  if ((USCI0_FLAG == USCI0_SPI_FLAG_SPIF) || (USCI0_FLAG == USCI0_SPI_FLAG_WCOL) || (USCI0_FLAG == USCI0_TWI_FLAG_TXRXnE))

#elif defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
			|| defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95F7619B)

  if ((USCI0_FLAG == USCI0_SPI_FLAG_SPIF) || (USCI0_FLAG == USCI0_SPI_FLAG_WCOL) || (USCI0_FLAG == USCI0_SPI_FLAG_TXE) || (USCI0_FLAG == USCI0_TWI_FLAG_TXRXnE))

#endif
  {
    US0CON1 &= (~USCI0_FLAG); //�����Ĵ���US0CON1
  }
  else if ((USCI0_FLAG == USCI0_UART_FLAG_TI) || (USCI0_FLAG == USCI0_UART_FLAG_RI))
  {
#if defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)
    US0CON0 = US0CON0  & 0xFC | USCI0_FLAG;//д1����
#else
    US0CON0 &= (~USCI0_FLAG); //д0����
#endif
  }
  else
  {
    US0CON0 &= (~USCI0_FLAG); //�����Ĵ���US0CON0
  }
}

/*****************************************************
*��������:void USCI0_TWI_SendAddr(uint8_t Addr,USCI0_TWI_RWType RW)
*��������:TWI���͵�ַ����д����
*��ڲ���:
uint8_t:Addr:���͵ĵ�ַ 0~127
USCI0_TWI_RWType:RW:��д����
*���ڲ���:void
*****************************************************/
void USCI0_TWI_SendAddr(uint8_t Addr, USCI0_TWI_RWType RW)
{
  US0CON3 = (Addr << 1) | RW;
}

#if defined(SC95F8x2x) || defined(SC95F7x2x)
/**************************************************
*��������:void USCI0_SC_Init()
*��������:���ܿ���ʼ�����ú���
*��ڲ���:
FunctionalState:ClockEnable:ʱ�����ʹ��λ
USCI0_SC_ERS_TypeDef:ErrorSignal:ErrorSignal����
USCI0_SC_TREN_TypeDef:TrenMode:����/����ʹ�ܣ����ͺͽ���ֻ�ܶ�ѡһ
USCI0_SC_CONS_TypeDef:ConsMod:���뷽ʽѡ��
FunctionalState:ReSend:���ݷ��ͽ���У������ط�ʹ��λ
USCI0_SC_Check_TypeDef:CheckType:У������
*���ڲ���:void
**************************************************/
void USCI0_SC_Init(FunctionalState ClockEnable,
                   USCI0_SC_ERS_TypeDef ErrorSignal,
                   USCI0_SC_TREN_TypeDef TrenMode,
                   USCI0_SC_CONS_TypeDef ConsMode,
                   FunctionalState ReSend,
                   USCI0_SC_Check_TypeDef CheckType)
{
  if (ClockEnable != DISABLE)
  {
    US0CON0 |= 0x40;
  }
  else
  {
    US0CON0 &= ~0x40;
  }

  US0CON0 &= ~0x3d;
  US0CON0 |= TrenMode | ConsMode | CheckType | (ErrorSignal << 3);

  if (ReSend != DISABLE)
  {
    US0CON0 |= 0x02;
  }
  else
  {
    US0CON0 &= ~0x02;
  }
}
/**************************************************
*��������:void USCI0_SC_EGT(uint8_t EgtCount)
*��������:���ܿ���չ����ʱ������
*��ڲ���:
uint8_t:EgtCount:��չ����ʱ����:EgtCount��ETU
*���ڲ���:void
**************************************************/
void USCI0_SC_EGT(uint8_t EgtCount)
{
  US0CON4 = EgtCount;
}

/**************************************************
*��������:void USCI0_SC_ETU_SET(USCI0_SC_Pres	Sel_TypeDef SC_PrescalerSelection,uint8_t EtuCk)
*��������:ETU���ã�һ��ETUʱ�䳤������
*��ڲ���:
USCI0_SC_PresSel_TypeDef:SC_PrescalerSelection:SC Clock ʱ����Դ
uint16_t:EtuCk:һ��ETUΪ(EtuCk+1)��SC Clock���������0x004
*���ڲ���:void
**************************************************/
void USCI0_SC_ETU_SET(USCI0_SC_PresSel_TypeDef SC_PrescalerSelection, uint16_t EtuCk)
{
  US0CON2 = (EtuCk >> 8);
  US0CON1 = (uint8_t)EtuCk;
  US0CON2 = (SC_PrescalerSelection << 4);
}
/*****************************************************
*��������:void USCI0_SC_Cmd(FunctionalState NewState)
*��������:���ܿ����ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void USCI0_SC_Cmd(FunctionalState NewState)
{
  if (NewState == DISABLE)
  {
    US0CON0 &= 0X7F;
  }
  else
  {
    US0CON0 |= 0x80;
  }
}
/*****************************************************
*��������:FlagStatus USCI0_SC_GetFlagStatus(USCI0_SC_Flag_TypeDef USCI0_SC_FLAG)
*��������:���SC��־״̬
*��ڲ���:
USCI0_SC_Flag_TypeDef:USCI0_SC_FLAG:�����ȡ�ı�־λ
*���ڲ���:
FlagStatus:USCI0_SC��־״̬
*****************************************************/
FlagStatus USCI0_SC_GetFlagStatus(USCI0_SC_Flag_TypeDef USCI0_SC_FLAG)
{
  //	  �Ĵ����л�����λ:
  //	  0 :US0CON5 (B7H)Ϊ��д״̬�Ĵ���
  //	  1 :US0CON5 (B7H)Ϊ��д������Ϣ�Ĵ���
  US0CON5 |= (USCI0_SC_FLAG & 0X80);
  return USCI0_SC_FLAG & US0CON5;
}
/*****************************************************
*��������:void USCI0_UART_SendData(uint8_t Data)
*��������:USCI0 SC����8λ����
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void USCI0_SC_SendData(uint8_t Data)
{
  US0CON3 = Data;
}
/*****************************************************
*��������:uint8_t USCI0_SC_ReceiveData(void)
*��������:��ý��ջ����е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
*****************************************************/
uint8_t USCI0_SC_ReceiveData(void)
{
  return US0CON3;
}

#endif

#if defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)
/**********************************************************************************************************
*��������:uint8_t USCI0_SPI_WriteFIFO(uint16_t *sbuf,uint8_t length)
*��������:SPI0д��FIFO
*��ڲ���:
uint16_t:*sbuf:����buffer
uint8_t:length:�������ݳ���
*���ڲ���:
uint8_t:(0:�Ƿ�������1:д��FIFO����ɹ�)
**********************************************************************************************************/
uint8_t USCI0_SPI_WriteFIFO(uint16_t *sbuf, uint8_t length)
{
  if (length > 8 || length < 1)
  {
    return 0;
  }
  else
  {
    uint8_t i = 0;
    US0CON1 &= ~0x01; //�ر�TBIE

    for (i = 0; i < length; i++)
    {
      US0CON3 = *(sbuf + i) >> 8; //д����������ݵĸ��ֽ�
      US0CON2 = *(sbuf + i);      //д����������ݵĵ��ֽ�
    }

    if (length != 0x01) //���ǵ���д�룬�����TXE
    {
      US0CON1 &= (~0x08); //��TXE
    }

    US0CON1 |= 0x01; //����TBIE
    return 1;
  }
}
#endif

#endif

/******************* (C) COPYRIGHT 2022 SinOne Microelectronics *****END OF FILE****/
