//************************************************************
//  Copyright (c) 
//	文件名称	: sc95f_USCI1.c
//	作者		:
//	模块功能	: USCI1固件库函数C文件
//  最后更正日期: 2022/01/24
// 	版本		: V1.10004
//  说明        :该文件仅适用于SC95F系列芯片
//*************************************************************

#include "sc95f_usci1.h"

/**************************************************
*函数名称:void USCI1_DeInit(void)
*函数功能:USCI1相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
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
*函数名称:void USCI1_SPI_Init(USCI1_SPI_FirstBit_TypeDef FirstBit, USCI1_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler,USCI1_SPI_Mode_TypeDef Mode,
							 USCI1_SPI_ClockPolarity_TypeDef ClockPolarity, USCI1_SPI_ClockPhase_TypeDef ClockPhase,USCI1_SPI_TXE_INT_TypeDef SPI_TXE_INT,USCI1_TransmissionMode_TypeDef TransmissionMode)
*函数功能:SPI初始化配置函数
*入口参数:
USCI1_SPI_FirstBit_TypeDef:FirstBit:优先传送位选择（MSB/LSB）
USCI1_SPI_BaudRatePrescaler_TypeDef:BaudRatePrescaler:SPI时钟频率选择
USCI1_SPI_Mode_TypeDef:Mode:SPI工作模式选择
USCI1_SPI_ClockPolarity_TypeDef:ClockPolarity:SPI时钟极性选择
USCI1_SPI_ClockPhase_TypeDef:ClockPhase:SPI时钟相位选择
USCI1_SPI_TXE_INT_TypeDef:SPI_TXE_INT:发送缓存器中断允许选择,该功能在SC95FXX1X芯片上无效
USCI1_TransmissionMode_TypeDef:TransmissionMode:SPI传输模式选择 8/16位
*出口参数:void
**************************************************/
void USCI1_SPI_Init(USCI1_SPI_FirstBit_TypeDef FirstBit,
                    USCI1_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, USCI1_SPI_Mode_TypeDef Mode,
                    USCI1_SPI_ClockPolarity_TypeDef ClockPolarity, USCI1_SPI_ClockPhase_TypeDef ClockPhase,
                    USCI1_SPI_TXE_INT_TypeDef SPI_TXE_INT, USCI1_TransmissionMode_TypeDef TransmissionMode)
{

  OTCON = (OTCON & 0X3F) | 0X40;
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx)
  SPI_TXE_INT = USCI1_SPI_TXE_DISINT; //SPI_TXE_INT该功能在SC95FXX1X芯片上无效
  US1CON1 = US1CON1 & (~0X05) | FirstBit | TransmissionMode;
#endif
#if defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
	|| defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)
  US1CON1 = US1CON1 & (~0X05) | FirstBit | SPI_TXE_INT | TransmissionMode;
#endif
  US1CON0 = US1CON0 & 0X80 | BaudRatePrescaler | Mode | ClockPolarity | ClockPhase;
}

/**************************************************
*函数名称:void USCI1_TransmissionMode(USCI1_TransmissionMode_TypeDef TransmissionMode)
*函数功能:SPI 传输模式配置函数
*入口参数:
USCI1_TransmissionMode_TypeDef:TransmissionMode:SPI传输模式选择 8/16e位
*出口参数:void
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
*函数名称:void USCI1_SPI_Cmd(FunctionalState NewState)
*函数功能:SPI功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
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
*函数名称:void USCI1_SPI_SendData_8(uint8_t Data)
*函数功能:USCI1 SPI发送数据
*入口参数:
uint8_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI1_SPI_SendData_8(uint8_t Data)
{
  US1CON2 = Data;
}

/*****************************************************
*函数名称:uint8_t USCI1_SPI_ReceiveData_8(void)
*函数功能:获得US1CON2中的值
*入口参数:void
*出口参数:
uint8_t:接收的数据
*****************************************************/
uint8_t USCI1_SPI_ReceiveData_8(void)
{
  return US1CON2;
}

/*****************************************************
*函数名称:void USCI1_SPI_SendData_16(uint16_t Data)
*函数功能:US1CON2 SPI发送数据
*入口参数:
uint16_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI1_SPI_SendData_16(uint16_t Data)
{
  US1CON3 = (uint8_t)(Data >> 8);
  US1CON2 = (uint8_t)Data;
}

/*****************************************************
*函数名称:uint16_t USCI1_SPI_ReceiveData_16(void)
*函数功能:获得US1CON2中的值
*入口参数:void
*出口参数:
uint16_t:接收的数据
*****************************************************/
uint16_t USCI1_SPI_ReceiveData_16(void)
{
  uint16_t SPI_data;
  SPI_data = (uint16_t)((US1CON3 << 8) | US1CON2);
  return SPI_data;
}

/**************************************************
*函数名称:void USCI1_TWI_Slave_Init(uint8_t TWI_Address)
*函数功能:USCI1 TWI从机初始化配置函数
*入口参数:
uint8_t:TWI_Address:TWI作为从机时的7位从机地址
*出口参数:void
**************************************************/
void USCI1_TWI_Slave_Init(uint8_t TWI_Address)
{
  OTCON = OTCON & 0X3F | 0X80;
  US1CON2 = TWI_Address << 1;
}

/**************************************************
*函数名称:void USCI1_TWI_MasterCommunicationRate(USCI1_TWI_MasterCommunicationRate_TypeDef TWI_MasterCommunicationRate)
*函数功能:USCI1 TWI主机模式下通讯速率设定
*入口参数:
USCI1_TWI_MasterCommunicationRate_TypeDef:TWI_MasterCommunicationRate:TWI主机模式下通讯速率
*出口参数:void
**************************************************/
void USCI1_TWI_MasterCommunicationRate(USCI1_TWI_MasterCommunicationRate_TypeDef
                                           TWI_MasterCommunicationRate)
{
  OTCON = OTCON & 0X3F | 0X80;
  US1CON1 |= TWI_MasterCommunicationRate;
}

/**************************************************
*函数名称:void USCI1_TWI_Start(void)
*函数功能:USCI1 TWI 起始位
*入口参数:void
*出口参数:void
**************************************************/
void USCI1_TWI_Start(void)
{
  US1CON1 |= 0x20;
}

/**************************************************
*函数名称:void USCI1_TWI_MasterModeStop(void)
*函数功能:USCI1 TWI主机模式停止位
*入口参数:void
*出口参数:void
**************************************************/
void USCI1_TWI_MasterModeStop(void)
{
  US1CON1 |= 0x10;
}

/**************************************************
*函数名称:void USCI1_TWI_SlaveClockExtension(FunctionalState NewState)
*函数功能:USCI1 TWI从机模式时钟延长功能位
*入口参数:
FunctionalState:NewState:使能/失能选择
*出口参数:void
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
*函数名称:void USCI1_TWI_AcknowledgeConfig(FunctionalState NewState)
*函数功能:TWI接收应答使能函数
*入口参数:
FunctionalState:NewState:接收应答使能/失能选择
*出口参数:void
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
*函数名称:void USCI1_TWI_GeneralCallCmd(FunctionalState NewState)
*函数功能:TWI通用地址响应使能函数
*入口参数:
FunctionalState:NewState:接收应答使能/失能选择
*出口参数:void
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
*函数名称:FlagStatus USCI1_GetTWIStatus(USCI1_TWIState_TypeDef USCI1_TWIState)
*函数功能:读取TWI状态
*入口参数:
USCI1_TWIState_TypeDef:USCI1_TWIState:TWI状态类型
*出口参数:
FlagStatus:USCI1_TWI标志状态	
*****************************************************/
FlagStatus USCI1_GetTWIStatus(USCI1_TWIState_TypeDef USCI1_TWIState)
{
  if ((US1CON0 & 0x07) == USCI1_TWIState)
    return SET;
  else
    return RESET;
}

/*****************************************************
*函数名称:void USCI1_TWI_Cmd(FunctionalState NewState)
*函数功能:TWI功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
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
*函数名称:void USCI1_TWI_SendData(uint8_t Data)
*函数功能:TWI发送数据
*入口参数:
uint8_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI1_TWI_SendData(uint8_t Data)
{
  US1CON3 = Data;
}

/*****************************************************
*函数名称:uint8_t USCI1_TWI_SendData(void)
*函数功能:获得US1CON3中的值
*入口参数:void
*出口参数:
uint8_t:接收的数据
*****************************************************/
uint8_t USCI1_TWI_ReceiveData(void)
{
  return US1CON3;
}

/**************************************************
*函数名称:void USCI1_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI1_UART_Mode_TypeDef Mode, USCI1_UART_RX_TypeDef RxMode)
*函数功能:UART初始化配置函数
*入口参数:
uint32_t:UARTFsys:系统时钟频率
uint32_t:BaudRate:波特率
USCI1_UART_Mode_TypeDef:Mode:UART1工作模式
USCI1_UART_RX_TypeDef:RxMode:接收允许选择
*出口参数:void
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
*函数名称:void USCI1_UART_SendData8(uint8_t Data)
*函数功能:USCI1 UART1发送8位数据
*入口参数:
uint8_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI1_UART_SendData8(uint8_t Data)
{	
	US1CON3 = Data;
}

/*****************************************************
*函数名称:uint8_t USCI1_UART_ReceiveData8(void)
*函数功能:获得US1CON3中的值
*入口参数:void
*出口参数:
uint8_t:接收的数据
*****************************************************/
uint8_t USCI1_UART_ReceiveData8(void)
{
  return US1CON3;
}

/*****************************************************
*函数名称:void USCI1_UART_SendData9(uint16_t Data)
*函数功能:UART1发送9位数据
*入口参数:
uint16_t:Data:发送的数据
*出口参数:void
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
*函数名称:uint16_t USCI1_UART_ReceiveData9(void)
*函数功能:获得US1CON3中的值及第九位的值
*入口参数:void
*出口参数:
uint16_t:接收的数据
*****************************************************/
uint16_t USCI1_UART_ReceiveData9(void)
{
  uint16_t Data9;
  Data9 = US1CON3 + ((uint16_t)(US1CON0 & 0X04) << 6);
  return Data9;
}

/*****************************************************
*函数名称:void USCI1_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:USCI1中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
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
*函数名称:FlagStatus USCI1_GetFlagStatus(USCI1_Flag_TypeDef USCI1_FLAG)
*函数功能:获得USCI1标志状态
*入口参数:
USCI1_Flag_Typedef:USCI1_Flag:中断标志位选择
*出口参数:
FlagStatus:USCI1标志状态
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
*函数名称:void USCI1_ClearFlag(USCI1_Flag_TypeDef USCI1_FLAG)
*函数功能:清除USCI1标志状态
*入口参数:
USCI1_Flag_TypeDef:USCI1_FLAG:所需清除的标志位
*出口参数:void
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
    US1CON1 &= (~USCI1_FLAG); //操作寄存器US1CON1
  }
  else if ((USCI1_FLAG == USCI1_UART_FLAG_TI) || (USCI1_FLAG == USCI1_UART_FLAG_RI))
  {
#if defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)
    US1CON0 = US1CON0  & 0xFC | USCI1_FLAG; //写1清零
#else
    US1CON0 &= (~USCI1_FLAG); //写0清零
#endif
  }
  else
  {
    US1CON0 &= (~USCI1_FLAG); //操作寄存器US1CON0
  }
}

/*****************************************************
*函数名称:void USCI1_TWI_SendAddr(uint8_t Addr,USCI1_TWI_RWType RW)
*函数功能:TWI发送地址，读写类型
*入口参数:
uint8_t:Addr:发送的地址 0~127
USCI1_TWI_RWType:RW:读写类型
*出口参数:void
*****************************************************/
void USCI1_TWI_SendAddr(uint8_t Addr, USCI1_TWI_RWType RW)
{
  US1CON3 = (Addr << 1) | RW;
}

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/
