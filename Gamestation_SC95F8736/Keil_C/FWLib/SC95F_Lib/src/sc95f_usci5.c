//************************************************************
//  Copyright (c) 
//	文件名称	: sc95f_USCI5.c
//	作者		:
//	模块功能	: USCI5固件库函数C文件
//  最后更正日期:	2022年7月22日
// 	版本:					V1.10002
//  说明        :该文件仅适用于SC95F系列芯片
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
*函数名称:void USCI5_SPI_Init(USCI5_SPI_FirstBit_TypeDef FirstBit, USCI5_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler,USCI5_SPI_Mode_TypeDef Mode,
							 USCI5_SPI_ClockPolarity_TypeDef ClockPolarity, USCI5_SPI_ClockPhase_TypeDef ClockPhase,USCI5_SPI_TXE_INT_TypeDef SPI_TXE_INT,USCI5_TransmissionMode_TypeDef TransmissionMode)
*函数功能:SPI初始化配置函数
*入口参数:
USCI5_SPI_FirstBit_TypeDef:FirstBit:优先传送位选择（MSB/LSB）
USCI5_SPI_BaudRatePrescaler_TypeDef:BaudRatePrescaler:SPI时钟频率选择
USCI5_SPI_Mode_TypeDef:Mode:SPI工作模式选择
USCI5_SPI_ClockPolarity_TypeDef:ClockPolarity:SPI时钟极性选择
USCI5_SPI_ClockPhase_TypeDef:ClockPhase:SPI时钟相位选择
USCI5_SPI_TXE_INT_TypeDef:SPI_TXE_INT:发送缓存器中断允许选择,该功能在SC95FXX1X芯片上无效
USCI5_TransmissionMode_TypeDef:TransmissionMode:SPI传输模式选择 8/16位
*出口参数:void
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
*函数名称:void USCI5_TransmissionMode(USCI5_TransmissionMode_TypeDef TransmissionMode)
*函数功能:SPI 传输模式配置函数
*入口参数:
USCI5_TransmissionMode_TypeDef:TransmissionMode:SPI传输模式选择 8/16e位
*出口参数:void
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
*函数名称:void USCI5_SPI_Cmd(FunctionalState NewState)
*函数功能:SPI功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
*****************************************************/
void USCI5_SPI_Cmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
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
*函数名称:void USCI5_SPI_SendData_8(uint8_t Data)
*函数功能:USCI5 SPI发送数据
*入口参数:
uint8_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI5_SPI_SendData_8(uint8_t Data)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
  USXINX |= 0X05;
  USXCON2 = Data;
}

/*****************************************************
*函数名称:uint8_t USCI5_SPI_ReceiveData_8(void)
*函数功能:获得USXCON2中的值
*入口参数:void
*出口参数:
uint8_t:接收的数据
*****************************************************/
uint8_t USCI5_SPI_ReceiveData_8(void)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
  USXINX |= 0X05;
  return USXCON2;
}

/*****************************************************
*函数名称:void USCI5_SPI_SendData_16(uint16_t Data)
*函数功能:USXCON2 SPI发送数据
*入口参数:
uint16_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI5_SPI_SendData_16(uint16_t Data)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
  USXINX |= 0X05;
  USXCON3 = (uint8_t)(Data >> 8);
  USXCON2 = (uint8_t)Data;
}

/*****************************************************
*函数名称:uint16_t USCI5_SPI_ReceiveData_16(void)
*函数功能:获得USXCON2中的值
*入口参数:void
*出口参数:
uint16_t:接收的数据
*****************************************************/
uint16_t USCI5_SPI_ReceiveData_16(void)
{
  uint16_t SPI_data;
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
  USXINX |= 0X05;
  SPI_data = (uint16_t)((USXCON3 << 8) | USXCON2);
  return SPI_data;
}

/**************************************************
*函数名称:void USCI5_TWI_Slave_Init(uint8_t TWI_Address)
*函数功能:USCI5 TWI 从机初始化配置函数
*入口参数:
uint8_t:TWI_Address:TWI作为从机时的7位从机地址
*出口参数:void
**************************************************/
void USCI5_TWI_Slave_Init(uint8_t TWI_Address)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
  USXINX |= 0X05;
  TMCON = (TMCON & 0X3F) | 0X80;
  USXCON2 = TWI_Address << 1;
}

/**************************************************
*函数名称:void USCI5_TWI_MasterCommunicationRate(USCI5_TWI_MasterCommunicationRate_TypeDef TWI_MasterCommunicationRate)
*函数功能:USCI5 TWI主机模式下通讯速率设定
*入口参数:
USCI5_TWI_MasterCommunicationRate_TypeDef:TWI_MasterCommunicationRate:TWI主机模式下通讯速率
*出口参数:void
**************************************************/
void USCI5_TWI_MasterCommunicationRate(USCI5_TWI_MasterCommunicationRate_TypeDef
                                           TWI_MasterCommunicationRate)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
  USXINX |= 0X05;
  TMCON = (TMCON & 0X3F) | 0X80;

  USXCON1 = TWI_MasterCommunicationRate;
}

/**************************************************
*函数名称:void USCI5_TWI_SlaveClockExtension(void)
*函数功能:USCI5 TWI从机模式时钟延长功能位
*入口参数:void
*出口参数:void
**************************************************/
void USCI5_TWI_SlaveClockExtension(FunctionalState NewState)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
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
*函数名称:void USCI5_TWI_AcknowledgeConfig(FunctionalState NewState)
*函数功能:TWI接收应答使能函数
*入口参数:
FunctionalState:NewState:接收应答使能/失能选择
*出口参数:void
**************************************************/
void USCI5_TWI_AcknowledgeConfig(FunctionalState NewState)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
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
*函数名称:void USCI5_TWI_GeneralCallCmd(FunctionalState NewState)
*函数功能:TWI通用地址响应使能函数
*入口参数:
FunctionalState:NewState:通用地址响应使能/失能选择
*出口参数:void
**************************************************/
void USCI5_TWI_GeneralCallCmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
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
*函数名称:void USCI5_TWI_Cmd(FunctionalState NewState)
*函数功能:TWI功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
*****************************************************/
void USCI5_TWI_Cmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
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
*函数名称:void USCI5_TWI_Start(void)
*函数功能:USCI5 TWI 起始位
*入口参数:void
*出口参数:void
**************************************************/
void USCI5_TWI_Start(void)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
  USXINX |= 0X05;
  USXCON1 |= 0x20;
}

/**************************************************
*函数名称:void USCI5_TWI_MasterModeStop(void)
*函数功能:USCI5 TWI主机模式停止位
*入口参数:void
*出口参数:void
**************************************************/
void USCI5_TWI_MasterModeStop(void)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
  USXINX |= 0X05;
  USXCON1 |= 0x10;
}

/*****************************************************
*函数名称:FlagStatus USCI5_GetTWIStatus(USCI5_TWIState_TypeDef USCI5_TWIState)
*函数功能:读取TWI状态
*入口参数:
USCI5_TWIState_TypeDef:USCI2_TWIState:TWI状态类型
*出口参数:
FlagStatus:USCI5_TWI标志状态	
*****************************************************/
FlagStatus USCI5_GetTWIStatus(USCI5_TWIState_TypeDef USCI5_TWIState)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
  USXINX |= 0X05;
  if ((USXCON0 & 0x07) == USCI5_TWIState)
    return SET;
  else
    return RESET;
}

/*****************************************************
*函数名称:void USCI5_TWI_SendData(uint8_t Data)
*函数功能:TWI发送数据
*入口参数:
uint8_t:Data:发送的数据/地址
*出口参数:void
*****************************************************/
void USCI5_TWI_SendData(uint8_t Data)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
  USXINX |= 0X05;
  USXCON3 = Data;
}

/*****************************************************
*函数名称:void USCI5_TWI_SendAddr(uint8_t Addr,USCI5_TWI_RWType RW)
*函数功能:TWI发送地址，读写类型
*入口参数:
uint8_t:Addr:发送的地址
USCI5_TWI_RWType:RW:读写类型
*出口参数:void
*****************************************************/
void USCI5_TWI_SendAddr(uint8_t Addr, USCI5_TWI_RWType RW)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
  USXINX |= 0X05;
  USXCON3 = (Addr << 1) | RW;
}
/*****************************************************
*函数名称:uint8_t USCI5_TWI_SendData(void)
*函数功能:获得USXCON3中的值
*入口参数:void
*出口参数:
uint8_t:接收的数据
*****************************************************/
uint8_t USCI5_TWI_ReceiveData(void)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
  USXINX |= 0X05;
  return USXCON3;
}

/**************************************************
*函数名称:void USCI5_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI5_UART_Mode_TypeDef Mode, USCI5_UART_RX_TypeDef RxMode)
*函数功能:UART初始化配置函数
*入口参数:
uint32_t:UARTFsys:系统时钟频率
uint32_t:BaudRate:波特率
USCI5_UART_Mode_TypeDef:Mode:UART工作模式
USCI5_UART_RX_TypeDef:RxMode:接收允许选择
*出口参数:void
**************************************************/
void USCI5_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI5_UART_Mode_TypeDef Mode,
                     USCI5_UART_RX_TypeDef RxMode)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
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
*函数名称:void USCI5_UART_SendData8(uint8_t Data)
*函数功能:USCI5 UART发送8位数据
*入口参数:
uint8_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI5_UART_SendData8(uint8_t Data)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
  USXINX |= 0X05;
  USXCON3 = Data;
}

/*****************************************************
*函数名称:uint8_t USCI5_UART_ReceiveData8(void)
*函数功能:获得USXCON3中的值
*入口参数:void
*出口参数:
uint8_t:接收的数据
*****************************************************/
uint8_t USCI5_UART_ReceiveData8(void)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
  USXINX |= 0X05;
  return USXCON3;
}

/*****************************************************
*函数名称:void USCI5_UART_SendData9(uint16_t Data)
*函数功能:UART发送9位数据
*入口参数:
uint16_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI5_UART_SendData9(uint16_t Data)
{
  uint8_t Data_9Bit;
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
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
*函数名称:uint16_t USCI5_UART_ReceiveData9(void)
*函数功能:获得USXCON3中的值及第九位的值
*入口参数:void
*出口参数:
uint16_t:接收的数据
*****************************************************/
uint16_t USCI5_UART_ReceiveData9(void)
{
  uint16_t Data9;
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
  USXINX |= 0X05;

  Data9 = USXCON3 + ((uint16_t)(USXCON0 & 0X04) << 6);
  return Data9;
}

/*****************************************************
*函数名称:void USCI5_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:USCI5中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
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
*函数名称:FlagStatus USCI5_GetFlagStatus(USCI5_Flag_TypeDef USCI5_FLAG)
*函数功能:获得USCI5标志状态
*入口参数:
USCI5_Flag_Typedef:USCI5_Flag:中断标志位选择
*出口参数:
FlagStatus:USCI5标志状态
*****************************************************/
FlagStatus USCI5_GetFlagStatus(USCI5_Flag_TypeDef USCI5_FLAG)
{
  FlagStatus bitstatus = RESET;
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
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
*函数名称:void USCI5_ClearFlag(USCI5_Flag_TypeDef USCI5_FLAG)
*函数功能:清除USCI5标志状态
*入口参数:
USCI5_Flag_TypeDef:USCI5_FLAG:所需清除的标志位
*出口参数:void
*****************************************************/
void USCI5_ClearFlag(USCI5_Flag_TypeDef USCI5_FLAG)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI5
  USXINX |= 0X05;
  if ((USCI5_FLAG == USCI5_SPI_FLAG_SPIF) || (USCI5_FLAG == USCI5_SPI_FLAG_WCOL) || (USCI5_FLAG == USCI5_SPI_FLAG_TXE) || (USCI5_FLAG == USCI5_TWI_FLAG_TXRXnE))
  {
    USXCON1 &= (~USCI5_FLAG); //操作寄存器USXCON1
  }
  else if ((USCI5_FLAG == USCI5_UART_FLAG_TI) || (USCI5_FLAG == USCI5_UART_FLAG_RI))
  {
#if defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)
    USXCON0 = USXCON0  & 0xFC | USCI5_FLAG; //写1清零
#else
    USXCON0 &= (~USCI5_FLAG); //写0清零
#endif
  }
  else
  {
    USXCON0 &= (~USCI5_FLAG); //操作寄存器USXCON0
  }
}

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/

#endif
