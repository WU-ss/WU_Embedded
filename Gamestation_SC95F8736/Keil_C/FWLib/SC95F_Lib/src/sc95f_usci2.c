//************************************************************
//  Copyright (c) 
//	文件名称:			sc95f_usci2.c
//	作者:
//	模块功能:			USCI2固件库函数C文件
//  最后更正日期:	2022年7月22日
// 	版本:					V1.10006
//  说明:					该文件仅适用于SC95Fxx1x、SC95Fxx2x系列芯片
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
*函数名称:void USCI2_SPI_Init(USCI2_SPI_FirstBit_TypeDef FirstBit, USCI2_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler,USCI2_SPI_Mode_TypeDef Mode,
							 USCI2_SPI_ClockPolarity_TypeDef ClockPolarity, USCI2_SPI_ClockPhase_TypeDef ClockPhase,USCI2_SPI_TXE_INT_TypeDef SPI_TXE_INT,USCI2_TransmissionMode_TypeDef TransmissionMode)
*函数功能:SPI初始化配置函数
*入口参数:
USCI2_SPI_FirstBit_TypeDef:FirstBit:优先传送位选择（MSB/LSB）
USCI2_SPI_BaudRatePrescaler_TypeDef:BaudRatePrescaler:SPI时钟频率选择
USCI2_SPI_Mode_TypeDef:Mode:SPI工作模式选择
USCI2_SPI_ClockPolarity_TypeDef:ClockPolarity:SPI时钟极性选择
USCI2_SPI_ClockPhase_TypeDef:ClockPhase:SPI时钟相位选择
USCI2_SPI_TXE_INT_TypeDef:SPI_TXE_INT:发送缓存器中断允许选择,该功能在SC95FXX1X芯片上无效
USCI2_TransmissionMode_TypeDef:TransmissionMode:SPI传输模式选择 8/16位
*出口参数:void
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
*函数名称:void USCI2_TransmissionMode(USCI2_TransmissionMode_TypeDef TransmissionMode)
*函数功能:SPI 传输模式配置函数
*入口参数:
USCI2_TransmissionMode_TypeDef:TransmissionMode:SPI传输模式选择 8/16e位
*出口参数:void
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
*函数名称:void USCI2_SPI_Cmd(FunctionalState NewState)
*函数功能:SPI功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
*****************************************************/
void USCI2_SPI_Cmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
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
*函数名称:void USCI2_SPI_SendData_8(uint8_t Data)
*函数功能:USCI2 SPI发送数据
*入口参数:
uint8_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI2_SPI_SendData_8(uint8_t Data)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
  USXINX |= 0X02;
  USXCON2 = Data;
}

/*****************************************************
*函数名称:uint8_t USCI2_SPI_ReceiveData_8(void)
*函数功能:获得USXCON2中的值
*入口参数:void
*出口参数:
uint8_t:接收的数据
*****************************************************/
uint8_t USCI2_SPI_ReceiveData_8(void)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
  USXINX |= 0X02;
  return USXCON2;
}

/*****************************************************
*函数名称:void USCI2_SPI_SendData_16(uint16_t Data)
*函数功能:USXCON2 SPI发送数据
*入口参数:
uint16_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI2_SPI_SendData_16(uint16_t Data)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
  USXINX |= 0X02;
  USXCON3 = (uint8_t)(Data >> 8);
  USXCON2 = (uint8_t)Data;
}

/*****************************************************
*函数名称:uint16_t USCI2_SPI_ReceiveData_16(void)
*函数功能:获得USXCON2中的值
*入口参数:void
*出口参数:
uint16_t:接收的数据
*****************************************************/
uint16_t USCI2_SPI_ReceiveData_16(void)
{
  uint16_t SPI_data;
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
  USXINX |= 0X02;
  SPI_data = (uint16_t)((USXCON3 << 8) | USXCON2);
  return SPI_data;
}

/**************************************************
*函数名称:void USCI2_TWI_Slave_Init(uint8_t TWI_Address)
*函数功能:USCI2 TWI 从机初始化配置函数
*入口参数:
uint8_t:TWI_Address:TWI作为从机时的7位从机地址
*出口参数:void
**************************************************/
void USCI2_TWI_Slave_Init(uint8_t TWI_Address)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
  USXINX |= 0X02;
  TMCON = TMCON & 0X3F | 0X80;
  USXCON2 = TWI_Address << 1;
}

/**************************************************
*函数名称:void USCI2_TWI_MasterCommunicationRate(USCI2_TWI_MasterCommunicationRate_TypeDef TWI_MasterCommunicationRate)
*函数功能:USCI2 TWI主机模式下通讯速率设定
*入口参数:
USCI2_TWI_MasterCommunicationRate_TypeDef:TWI_MasterCommunicationRate:TWI主机模式下通讯速率
*出口参数:void
**************************************************/
void USCI2_TWI_MasterCommunicationRate(USCI2_TWI_MasterCommunicationRate_TypeDef
                                           TWI_MasterCommunicationRate)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
  USXINX |= 0X02;
  TMCON = TMCON & 0X3F | 0X80; //选择usci2为TWI

  USXCON1 = TWI_MasterCommunicationRate;
}

/**************************************************
*函数名称:void USCI2_TWI_Start(void)
*函数功能:USCI2 TWI 起始位
*入口参数:void
*出口参数:void
**************************************************/
void USCI2_TWI_Start(void)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
  USXINX |= 0X02;
  USXCON1 |= 0x20;
}

/**************************************************
*函数名称:void USCI2_TWI_MasterModeStop(void)
*函数功能:USCI2 TWI主机模式停止位
*入口参数:void
*出口参数:void
**************************************************/
void USCI2_TWI_MasterModeStop(void)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
  USXINX |= 0X02;
  USXCON1 |= 0x10;
}

/**************************************************
*函数名称:void USCI2_TWI_SlaveClockExtension(void)
*函数功能:USCI2 TWI从机模式时钟延长功能位
*入口参数:
FunctionalState:NewState:使能/失能选择
*出口参数:void
**************************************************/
void USCI2_TWI_SlaveClockExtension(FunctionalState NewState)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
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
*函数名称:void USCI2_TWI_AcknowledgeConfig(FunctionalState NewState)
*函数功能:TWI接收应答使能函数
*入口参数:
FunctionalState:NewState:接收应答使能/失能选择
*出口参数:void
**************************************************/
void USCI2_TWI_AcknowledgeConfig(FunctionalState NewState)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
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
*函数名称:void USCI2_TWI_GeneralCallCmd(FunctionalState NewState)
*函数功能:TWI通用地址响应使能函数
*入口参数:
FunctionalState:NewState:通用地址响应使能/失能选择
*出口参数:void
**************************************************/
void USCI2_TWI_GeneralCallCmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
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
*函数名称:FlagStatus USCI2_GetTWIStatus(USCI2_TWIState_TypeDef USCI2_TWIState)
*函数功能:读取TWI状态
*入口参数:
USCI2_TWIState_TypeDef:USCI2_TWIState:TWI状态类型
*出口参数:
FlagStatus:USCI2_TWI标志状态	
*****************************************************/
FlagStatus USCI2_GetTWIStatus(USCI2_TWIState_TypeDef USCI2_TWIState)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
  USXINX |= 0X02;
  if ((USXCON0 & 0x07) == USCI2_TWIState)
    return SET;
  else
    return RESET;
}

/*****************************************************
*函数名称:void USCI2_TWI_Cmd(FunctionalState NewState)
*函数功能:TWI功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
*****************************************************/
void USCI2_TWI_Cmd(FunctionalState NewState)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
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
*函数名称:void USCI2_TWI_SendData(uint8_t Data)
*函数功能:TWI发送数据
*入口参数:
uint8_t:Data:发送的数据/地址
*出口参数:void
*****************************************************/
void USCI2_TWI_SendData(uint8_t Data)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
  USXINX |= 0X02;
  USXCON3 = Data;
}
/*****************************************************
*函数名称:void USCI2_TWI_SendAddr(uint8_t Addr,USCI2_TWI_RWType RW)
*函数功能:TWI发送地址，读写类型
*入口参数:
uint8_t:Addr:发送的地址
USCI2_TWI_RWType:RW:读写类型
*出口参数:void
*****************************************************/
void USCI2_TWI_SendAddr(uint8_t Addr, USCI2_TWI_RWType RW)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
  USXINX |= 0X02;
  USXCON3 = (Addr << 1) | RW;
}
/*****************************************************
*函数名称:uint8_t USCI2_TWI_ReceiveData(void)
*函数功能:获得USXCON3中的值
*入口参数:void
*出口参数:
uint8_t:接收的数据
*****************************************************/
uint8_t USCI2_TWI_ReceiveData(void)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
  USXINX |= 0X02;
  return USXCON3;
}

/**************************************************
*函数名称:void USCI2_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI2_UART_Mode_TypeDef Mode, USCI2_UART_RX_TypeDef RxMode)
*函数功能:UART初始化配置函数
*入口参数:
uint32_t:UARTFsys:系统时钟频率
uint32_t:BaudRate:波特率
USCI2_UART_Mode_TypeDef:Mode:UART工作模式
USCI2_UART_RX_TypeDef:RxMode:接收允许选择
*出口参数:void
**************************************************/
void USCI2_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI2_UART_Mode_TypeDef Mode,
                     USCI2_UART_RX_TypeDef RxMode)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
  USXINX |= 0X02;
  TMCON = TMCON & 0X3F | 0XC0; //选择USCI2为UART
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
*函数名称:void USCI2_UART_SendData8(uint8_t Data)
*函数功能:USCI2_UART发送8位数据
*入口参数:
uint8_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI2_UART_SendData8(uint8_t Data)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
  USXINX |= 0X02;
  USXCON3 = Data;
}

/*****************************************************
*函数名称:uint8_t USCI2_UART_ReceiveData8(void)
*函数功能:获得USXCON3中的值
*入口参数:void
*出口参数:
uint8_t:接收的数据
*****************************************************/
uint8_t USCI2_UART_ReceiveData8(void)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
  USXINX |= 0X02;
  return USXCON3;
}

/*****************************************************
*函数名称:void USCI2_UART_SendData9(uint16_t Data)
*函数功能:UART发送9位数据
*入口参数:
uint16_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI2_UART_SendData9(uint16_t Data)
{
  uint8_t Data_9Bit;
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
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
*函数名称:uint16_t USCI2_UART_ReceiveData9(void)
*函数功能:获得USXCON3中的值及第九位的值
*入口参数:void
*出口参数:
uint16_t:接收的数据
*****************************************************/
uint16_t USCI2_UART_ReceiveData9(void)
{
  uint16_t Data9;
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
  USXINX |= 0X02;

  Data9 = USXCON3 + ((uint16_t)(USXCON0 & 0X04) << 6);
  return Data9;
}

/*****************************************************
*函数名称:void USCI2_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:USCI2中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
*****************************************************/
void USCI2_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
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
*函数名称:FlagStatus USCI2_GetFlagStatus(USCI2_Flag_TypeDef USCI2_FLAG)
*函数功能:获得USCI2标志状态
*入口参数:
USCI2_Flag_Typedef:USCI2_Flag:中断标志位选择
*出口参数:
FlagStatus:USCI2标志状态
*****************************************************/
FlagStatus USCI2_GetFlagStatus(USCI2_Flag_TypeDef USCI2_FLAG)
{
  FlagStatus bitstatus = RESET;
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
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
*函数名称:void USCI2_ClearFlag(USCI2_Flag_TypeDef USCI2_FLAG)
*函数功能:清除USCI2标志状态
*入口参数:
USCI2_Flag_TypeDef:USCI2_FLAG:所需清除的标志位
*出口参数:void
*****************************************************/
void USCI2_ClearFlag(USCI2_Flag_TypeDef USCI2_FLAG)
{
  USXINX &= 0xF8; //把USCIX寄存器指向USCI2
  USXINX |= 0X02;
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx)

  if ((USCI2_FLAG == USCI2_SPI_FLAG_SPIF) || (USCI2_FLAG == USCI2_SPI_FLAG_WCOL) || (USCI2_FLAG == USCI2_TWI_FLAG_TXRXnE))

#elif defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
	|| defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)

  if ((USCI2_FLAG == USCI2_SPI_FLAG_SPIF) || (USCI2_FLAG == USCI2_SPI_FLAG_WCOL) || (USCI2_FLAG == USCI2_SPI_FLAG_TXE) || (USCI2_FLAG == USCI2_TWI_FLAG_TXRXnE))

#endif
  {
    USXCON1 &= (~USCI2_FLAG); //操作寄存器USXCON1
  }
  else if ((USCI2_FLAG == USCI2_UART_FLAG_TI) || (USCI2_FLAG == USCI2_UART_FLAG_RI))
  {
#if defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)
    USXCON0 = USXCON0  & 0xFC | USCI2_FLAG; //写1清零
#else
    USXCON0 &= (~USCI2_FLAG); //写0清零
#endif
  }
  else
  {
    USXCON0 &= (~USCI2_FLAG); //操作寄存器USXCON0
  }
}
#else

/**************************************************
*函数名称:void USCI2_DeInit(void)
*函数功能:USCI2相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
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
*函数名称:void USCI2_SPI_Init(USCI2_SPI_FirstBit_TypeDef FirstBit, USCI2_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler,USCI2_SPI_Mode_TypeDef Mode,
							 USCI2_SPI_ClockPolarity_TypeDef ClockPolarity, USCI2_SPI_ClockPhase_TypeDef ClockPhase,USCI2_SPI_TXE_INT_TypeDef SPI_TXE_INT,USCI2_TransmissionMode_TypeDef TransmissionMode)
*函数功能:SPI初始化配置函数
*入口参数:
USCI2_SPI_FirstBit_TypeDef:FirstBit:优先传送位选择（MSB/LSB）
USCI2_SPI_BaudRatePrescaler_TypeDef:BaudRatePrescaler:SPI时钟频率选择
USCI2_SPI_Mode_TypeDef:Mode:SPI工作模式选择
USCI2_SPI_ClockPolarity_TypeDef:ClockPolarity:SPI时钟极性选择
USCI2_SPI_ClockPhase_TypeDef:ClockPhase:SPI时钟相位选择
USCI2_SPI_TXE_INT_TypeDef:SPI_TXE_INT:发送缓存器中断允许选择,该功能在SC95FXX1X芯片上无效
USCI2_TransmissionMode_TypeDef:TransmissionMode:SPI传输模式选择 8/16位
*出口参数:void
**************************************************/
void USCI2_SPI_Init(USCI2_SPI_FirstBit_TypeDef FirstBit,
                    USCI2_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, USCI2_SPI_Mode_TypeDef Mode,
                    USCI2_SPI_ClockPolarity_TypeDef ClockPolarity, USCI2_SPI_ClockPhase_TypeDef ClockPhase,
                    USCI2_SPI_TXE_INT_TypeDef SPI_TXE_INT, USCI2_TransmissionMode_TypeDef TransmissionMode)
{
  TMCON = (TMCON & 0X3F) | 0X40;
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx)
  SPI_TXE_INT = USCI2_SPI_TXE_DISINT; //SPI_TXE_INT该功能在SC95FXX1X芯片上无效
  US2CON1 = US2CON1 & (~0X05) | FirstBit | TransmissionMode;
#endif
#if defined(SC95F8x2x) || defined(SC95F7x2x)
  US2CON1 = US2CON1 & (~0X05) | FirstBit | SPI_TXE_INT | TransmissionMode;
#endif
  US2CON0 = US2CON0 & 0X80 | BaudRatePrescaler | Mode | ClockPolarity | ClockPhase;
}

/**************************************************
*函数名称:void USCI2_TransmissionMode(USCI2_TransmissionMode_TypeDef TransmissionMode)
*函数功能:SPI 传输模式配置函数
*入口参数:
USCI2_TransmissionMode_TypeDef:TransmissionMode:SPI传输模式选择 8/16e位
*出口参数:void
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
*函数名称:void USCI2_SPI_Cmd(FunctionalState NewState)
*函数功能:SPI功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
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
*函数名称:void USCI2_SPI_SendData_8(uint8_t Data)
*函数功能:USCI2 SPI发送数据
*入口参数:
uint8_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI2_SPI_SendData_8(uint8_t Data)
{
  US2CON2 = Data;
}

/*****************************************************
*函数名称:uint8_t USCI2_SPI_ReceiveData_8(void)
*函数功能:获得US2CON2中的值
*入口参数:void
*出口参数:
uint8_t:接收的数据
*****************************************************/
uint8_t USCI2_SPI_ReceiveData_8(void)
{
  return US2CON2;
}

/*****************************************************
*函数名称:void USCI2_SPI_SendData_16(uint16_t Data)
*函数功能:US2CON2 SPI发送数据
*入口参数:
uint16_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI2_SPI_SendData_16(uint16_t Data)
{
  US2CON3 = (uint8_t)(Data >> 8);
  US2CON2 = (uint8_t)Data;
}

/*****************************************************
*函数名称:uint16_t USCI2_SPI_ReceiveData_16(void)
*函数功能:获得US2CON2中的值
*入口参数:void
*出口参数:
uint16_t:接收的数据
*****************************************************/
uint16_t USCI2_SPI_ReceiveData_16(void)
{
  uint16_t SPI_data;
  SPI_data = (uint16_t)((US2CON3 << 8) | US2CON2);
  return SPI_data;
}

/**************************************************
*函数名称:void USCI2_TWI_Slave_Init(uint8_t TWI_Address)
*函数功能:USCI2 TWI 从机初始化配置函数
*入口参数:
uint8_t:TWI_Address:TWI作为从机时的7位从机地址
*出口参数:void
**************************************************/
void USCI2_TWI_Slave_Init(uint8_t TWI_Address)
{
  TMCON = TMCON & 0X3F | 0X80;
  US2CON2 = TWI_Address << 1;
}

/**************************************************
*函数名称:void USCI2_TWI_MasterCommunicationRate(USCI2_TWI_MasterCommunicationRate_TypeDef TWI_MasterCommunicationRate)
*函数功能:USCI2 TWI主机模式下通讯速率设定
*入口参数:
USCI2_TWI_MasterCommunicationRate_TypeDef:TWI_MasterCommunicationRate:TWI主机模式下通讯速率
*出口参数:void
**************************************************/
void USCI2_TWI_MasterCommunicationRate(USCI2_TWI_MasterCommunicationRate_TypeDef
                                           TWI_MasterCommunicationRate)
{
  TMCON = TMCON & 0X3F | 0X80; //选择usci2为TWI

  US2CON1 = TWI_MasterCommunicationRate;
}

/**************************************************
*函数名称:void USCI2_TWI_Start(void)
*函数功能:USCI2 TWI 起始位
*入口参数:void
*出口参数:void
**************************************************/
void USCI2_TWI_Start(void)
{
  US2CON1 |= 0x20;
}

/**************************************************
*函数名称:void USCI2_TWI_MasterModeStop(void)
*函数功能:USCI2 TWI主机模式停止位
*入口参数:void
*出口参数:void
**************************************************/
void USCI2_TWI_MasterModeStop(void)
{
  US2CON1 |= 0x10;
}

/**************************************************
*函数名称:void USCI2_TWI_SlaveClockExtension(void)
*函数功能:USCI2 TWI从机模式时钟延长功能位
*入口参数:void
*出口参数:void
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
*函数名称:void USCI2_TWI_AcknowledgeConfig(FunctionalState NewState)
*函数功能:TWI接收应答使能函数
*入口参数:
FunctionalState:NewState:接收应答使能/失能选择
*出口参数:void
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
*函数名称:void USCI2_TWI_GeneralCallCmd(FunctionalState NewState)
*函数功能:TWI通用地址响应使能函数
*入口参数:
FunctionalState:NewState:接收应答使能/失能选择
*出口参数:void
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
*函数名称:FlagStatus USCI2_GetTWIStatus(USCI2_TWIState_TypeDef USCI2_TWIState)
*函数功能:读取TWI状态
*入口参数:
USCI2_TWIState_TypeDef:USCI2_TWIState:TWI状态类型
*出口参数:
FlagStatus:USCI2_TWI标志状态	
*****************************************************/
FlagStatus USCI2_GetTWIStatus(USCI2_TWIState_TypeDef USCI2_TWIState)
{
  if ((US2CON0 & 0x07) == USCI2_TWIState)
    return SET;
  else
    return RESET;
}

/*****************************************************
*函数名称:void USCI2_TWI_Cmd(FunctionalState NewState)
*函数功能:TWI功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
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
*函数名称:void USCI2_TWI_SendData(uint8_t Data)
*函数功能:TWI发送数据
*入口参数:
uint8_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI2_TWI_SendData(uint8_t Data)
{
  US2CON3 = Data;
}
/*****************************************************
*函数名称:void USCI2_TWI_SendAddr(uint8_t Addr,USCI2_TWI_RWType RW)
*函数功能:TWI发送地址，读写类型
*入口参数:
uint8_t:Addr:发送的地址
USCI2_TWI_RWType:RW:读写类型
*出口参数:void
*****************************************************/
void USCI2_TWI_SendAddr(uint8_t Addr, USCI2_TWI_RWType RW)
{
  US2CON3 = (Addr << 1) | RW;
}
/*****************************************************
*函数名称:uint8_t USCI2_TWI_ReceiveData(void)
*函数功能:获得US2CON3中的值
*入口参数:void
*出口参数:
uint8_t:接收的数据
*****************************************************/
uint8_t USCI2_TWI_ReceiveData(void)
{
  return US2CON3;
}

/**************************************************
*函数名称:void USCI2_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI2_UART_Mode_TypeDef Mode, USCI2_UART_RX_TypeDef RxMode)
*函数功能:UART初始化配置函数
*入口参数:
uint32_t:UARTFsys:系统时钟频率
uint32_t:BaudRate:波特率
USCI2_UART_Mode_TypeDef:Mode:UART1工作模式
USCI2_UART_RX_TypeDef:RxMode:接收允许选择
*出口参数:void
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
*函数名称:void USCI2_UART_SendData8(uint8_t Data)
*函数功能:USCI2 UART1发送8位数据
*入口参数:
uint8_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI2_UART_SendData8(uint8_t Data)
{
  US2CON3 = Data;
}

/*****************************************************
*函数名称:uint8_t USCI2_UART_ReceiveData8(void)
*函数功能:获得US2CON3中的值
*入口参数:void
*出口参数:
uint8_t:接收的数据
*****************************************************/
uint8_t USCI2_UART_ReceiveData8(void)
{
  return US2CON3;
}

/*****************************************************
*函数名称:void USCI2_UART_SendData9(uint16_t Data)
*函数功能:UART发送9位数据
*入口参数:
uint16_t:Data:发送的数据
*出口参数:void
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
*函数名称:uint16_t USCI2_UART_ReceiveData9(void)
*函数功能:获得US2CON3中的值及第九位的值
*入口参数:void
*出口参数:
uint16_t:接收的数据
*****************************************************/
uint16_t USCI2_UART_ReceiveData9(void)
{
  uint16_t Data9;
  Data9 = US2CON3 + ((uint16_t)(US2CON0 & 0X04) << 6);
  return Data9;
}

/*****************************************************
*函数名称:void USCI2_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:USCI2中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
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
*函数名称:FlagStatus USCI2_GetFlagStatus(USCI2_Flag_TypeDef USCI2_FLAG)
*函数功能:获得USCI2标志状态
*入口参数:
USCI2_Flag_Typedef:USCI2_Flag:所需获取的标志位
*出口参数:
FlagStatus:USCI2标志状态
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
*函数名称:void USCI2_ClearFlag(USCI2_Flag_TypeDef USCI2_FLAG)
*函数功能:清除USCI2标志状态
*入口参数:
USCI2_Flag_TypeDef:USCI2_FLAG:所需清除的标志位
*出口参数:void
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
