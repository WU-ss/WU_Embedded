//************************************************************
//  Copyright (c) 
//	文件名称: 			sc95f_usci0.c
//	作者:					赛元应用团队
//	模块功能: 			USCI0固件库函数C文件
//  最后更正日期:	2022年7月20日
// 	版本: 				V1.10006
//  说明: 				该文件仅适用于SC95F系列芯片
//*************************************************************

#include "sc95f_usci0.h"

#if !defined (SC95R751) && !defined (SC95F7610B)
/**************************************************
*函数名称:void USCI0_DeInit(void)
*函数功能:USCI0相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
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
*函数名称:void USCI0_SPI_Init(USCI0_SPI_FirstBit_TypeDef FirstBit, USCI0_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler,USCI0_SPI_Mode_TypeDef Mode,
							 USCI0_SPI_ClockPolarity_TypeDef ClockPolarity, USCI0_SPI_ClockPhase_TypeDef ClockPhase,USCI0_SPI_TXE_INT_TypeDef SPI_TXE_INT,USCI0_TransmissionMode_TypeDef TransmissionMode)
*函数功能:SPI初始化配置函数
*入口参数:
USCI0_SPI_FirstBit_TypeDef:FirstBit:优先传送位选择（MSB/LSB）
USCI0_SPI_BaudRatePrescaler_TypeDef:BaudRatePrescaler:SPI时钟频率选择
USCI0_SPI_Mode_TypeDef:Mode:SPI工作模式选择
USCI0_SPI_ClockPolarity_TypeDef:ClockPolarity:SPI时钟极性选择
USCI0_SPI_ClockPhase_TypeDef:ClockPhase:SPI时钟相位选择
USCI0_SPI_TXE_INT_TypeDef:SPI_TXE_INT:发送缓存器中断允许选择,该功能在SC95FXX1X芯片上无效
USCI0_TransmissionMode_TypeDef:TransmissionMode:SPI传输模式选择 8/16位
*出口参数:void
**************************************************/
void USCI0_SPI_Init(USCI0_SPI_FirstBit_TypeDef FirstBit,
                    USCI0_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, USCI0_SPI_Mode_TypeDef Mode,
                    USCI0_SPI_ClockPolarity_TypeDef ClockPolarity, USCI0_SPI_ClockPhase_TypeDef ClockPhase,
                    USCI0_SPI_TXE_INT_TypeDef SPI_TXE_INT, USCI0_TransmissionMode_TypeDef TransmissionMode)
{

  OTCON = (OTCON & 0XCF) | 0X10;
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx)
  SPI_TXE_INT = USCI0_SPI_TXE_DISINT; //SPI_TXE_INT该功能在SC95FXX1X芯片上无效
  US0CON1 = US0CON1 & (~0X05) | FirstBit | TransmissionMode;
#endif
#if defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95F7619B)
  US0CON1 = US0CON1 & (~0X05) | FirstBit | SPI_TXE_INT | TransmissionMode;
#endif
  US0CON0 = US0CON0 & 0X80 | BaudRatePrescaler | Mode | ClockPolarity | ClockPhase;
}

/**************************************************
*函数名称:void USCI0_TransmissionMode(USCI0_TransmissionMode_TypeDef TransmissionMode)
*函数功能:SPI 传输模式配置函数
*入口参数:
USCI0_TransmissionMode_TypeDef:TransmissionMode:SPI传输模式选择 8/16e位
*出口参数:void
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
*函数名称:void USCI0_SPI_Cmd(FunctionalState NewState)
*函数功能:SPI功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
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
*函数名称:void USCI0_SPI_SendData_8(uint8_t Data)
*函数功能:USCI0 SPI发送数据
*入口参数:
uint8_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI0_SPI_SendData_8(uint8_t Data)
{
  US0CON2 = Data;
}

/*****************************************************
*函数名称:uint8_t USCI0_SPI_ReceiveData_8(void)
*函数功能:获得US0CON2中的值
*入口参数:void
*出口参数:
uint8_t:接收到的数据
*****************************************************/
uint8_t USCI0_SPI_ReceiveData_8(void)
{
  return US0CON2;
}

/*****************************************************
*函数名称:void USCI0_SPI_SendData_16(uint16_t Data)
*函数功能:US0CON2 SPI发送数据
*入口参数:
uint16_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI0_SPI_SendData_16(uint16_t Data)
{
  US0CON3 = (uint8_t)(Data >> 8);
  US0CON2 = (uint8_t)Data;
}

/*****************************************************
*函数名称:uint16_t USCI0_SPI_ReceiveData_16(void)
*函数功能:获得US0CON2中的值
*入口参数:void
*出口参数:
uint16_t:接收的数据
*****************************************************/
uint16_t USCI0_SPI_ReceiveData_16(void)
{
  uint16_t SPI_data;
  SPI_data = (uint16_t)((US0CON3 << 8) | US0CON2);
  return SPI_data;
}

/**************************************************
*函数名称:void USCI0_TWI_Slave_Init(uint8_t TWI_Address)
*函数功能:USCI0 TWI从机初始化配置函数
*入口参数:
uint8_t:TWI_Address:TWI作为从机时的7位从机地址
*出口参数:void
**************************************************/
void USCI0_TWI_Slave_Init(uint8_t TWI_Address)
{
  OTCON = OTCON & 0XCF | 0X20;
  US0CON2 = TWI_Address << 1;
}

/**************************************************
*函数名称:void USCI0_TWI_MasterCommunicationRate(USCI0_TWI_MasterCommunicationRate_TypeDef TWI_MasterCommunicationRate)
*函数功能:USCI0 TWI主机模式下通讯速率设定
*入口参数:
USCI0_TWI_MasterCommunicationRate_TypeDef:TWI_MasterCommunicationRate:TWI主机模式下通讯速率
*出口参数:void
**************************************************/
void USCI0_TWI_MasterCommunicationRate(USCI0_TWI_MasterCommunicationRate_TypeDef
                                           TWI_MasterCommunicationRate)
{
  OTCON = OTCON & 0XCF | 0X20;
  US0CON1 |= TWI_MasterCommunicationRate;
}

/**************************************************
*函数名称:void USCI0_TWI_Start(void)
*函数功能:USCI0 TWI 起始位
*入口参数:void
*出口参数:void
**************************************************/
void USCI0_TWI_Start(void)
{
  US0CON1 |= 0x20;
}

/**************************************************
*函数名称:void USCI0_TWI_MasterModeStop(void)
*函数功能:USCI0 TWI主机模式停止位
*入口参数:void
*出口参数:void
**************************************************/
void USCI0_TWI_MasterModeStop(void)
{
  US0CON1 |= 0x10;
}

/**************************************************
*函数名称:void USCI0_TWI_SlaveClockExtension(void)
*函数功能:USCI0 TWI从机模式时钟延长功能位
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
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
*函数名称:void USCI0_TWI_AcknowledgeConfig(FunctionalState NewState)
*函数功能:TWI接收应答使能函数
*入口参数:
FunctionalState:NewState:接收应答使能/失能选择
*出口参数:void
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
*函数名称:void USCI0_TWI_GeneralCallCmd(FunctionalState NewState)
*函数功能:TWI通用地址响应使能函数
*入口参数:
FunctionalState:NewState:通用地址响应使能/失能选择
*出口参数:void
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
*函数名称:FlagStatus USCI0_GetTWIStatus(USCI0_TWIState_TypeDef USCI0_TWIState)
*函数功能:读取TWI状态
*入口参数:
USCI0_TWIState_TypeDef:USCI0_TWIState:TWI状态类型
*出口参数:
FlagStatus:USCI0_SC标志状态	
*****************************************************/
FlagStatus USCI0_GetTWIStatus(USCI0_TWIState_TypeDef USCI0_TWIState)
{
  if ((US0CON0 & 0x07) == USCI0_TWIState)
    return SET;
  else
    return RESET;
}

/*****************************************************
*函数名称:void USCI0_TWI_Cmd(FunctionalState NewState)
*函数功能:TWI功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
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
*函数名称:void USCI0_TWI_SendData(uint8_t Data)
*函数功能:TWI发送数据
*入口参数:
uint8_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI0_TWI_SendData(uint8_t Data)
{
  US0CON3 = Data;
}

/*****************************************************
*函数名称:uint8_t USCI0_TWI_SendData(void)
*函数功能:获得US0CON3中的值
*入口参数:void
*出口参数:
uint8_t:接收的数据
*****************************************************/
uint8_t USCI0_TWI_ReceiveData(void)
{
  return US0CON3;
}

/**************************************************
*函数名称:void USCI0_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI0_UART_Mode_TypeDef Mode, USCI0_UART_RX_TypeDef RxMode)
*函数功能:UART初始化配置函数
*入口参数:
uint32_t:UARTFsys:系统时钟频率
uint32_t:BaudRate:波特率
USCI0_UART_Mode_TypeDef:Mode:UART1工作模式
USCI0_UART_RX_TypeDef:RxMode:接收允许选择
*出口参数:void
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
*函数名称:void USCI0_UART_SendData8(uint8_t Data)
*函数功能:USCI0 UART1发送8位数据
*入口参数:
uint8_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI0_UART_SendData8(uint8_t Data)
{
  US0CON3 = Data;
}

/*****************************************************
*函数名称:uint8_t USCI0_UART_ReceiveData8(void)
*函数功能:获得US0CON3中的值
*入口参数:void
*出口参数:
uint8_t:接收的数据
*****************************************************/
uint8_t USCI0_UART_ReceiveData8(void)
{
  return US0CON3;
}

/*****************************************************
*函数名称:void USCI0_UART_SendData9(uint16_t Data)
*函数功能:UART1发送9位数据
*入口参数:
uint16_t:Data:发送的数据
*出口参数:void
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
*函数名称:uint16_t USCI0_UART_ReceiveData9(void)
*函数功能:获得US0CON3中的值及第九位的值
*入口参数:void
*出口参数:
uint16_t:接收的数据
*****************************************************/
uint16_t USCI0_UART_ReceiveData9(void)
{
  uint16_t Data9;
  Data9 = US0CON3 + ((uint16_t)(US0CON0 & 0X04) << 6);
  return Data9;
}

/*****************************************************
*函数名称:void USCI0_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:USCI0中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
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
*函数名称:FlagStatus USCI0_GetFlagStatus(USCI0_Flag_TypeDef USCI0_FLAG)
*函数功能:获得USCI0标志状态
*入口参数:
USCI0_Flag_TypeDef:USCI0_FLAG:所需获取的标志位
*出口参数:
FlagStatus:USCI0标志状态
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
*函数名称:void USCI0_ClearFlag(USCI0_Flag_TypeDef USCI0_FLAG)
*函数功能:清除USCI0标志状态
*入口参数:
USCI0_Flag_TypeDef:USCI0_FLAG:所需清除的标志位
*出口参数:void
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
    US0CON1 &= (~USCI0_FLAG); //操作寄存器US0CON1
  }
  else if ((USCI0_FLAG == USCI0_UART_FLAG_TI) || (USCI0_FLAG == USCI0_UART_FLAG_RI))
  {
#if defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)
    US0CON0 = US0CON0  & 0xFC | USCI0_FLAG;//写1清零
#else
    US0CON0 &= (~USCI0_FLAG); //写0清零
#endif
  }
  else
  {
    US0CON0 &= (~USCI0_FLAG); //操作寄存器US0CON0
  }
}

/*****************************************************
*函数名称:void USCI0_TWI_SendAddr(uint8_t Addr,USCI0_TWI_RWType RW)
*函数功能:TWI发送地址，读写类型
*入口参数:
uint8_t:Addr:发送的地址 0~127
USCI0_TWI_RWType:RW:读写类型
*出口参数:void
*****************************************************/
void USCI0_TWI_SendAddr(uint8_t Addr, USCI0_TWI_RWType RW)
{
  US0CON3 = (Addr << 1) | RW;
}

#if defined(SC95F8x2x) || defined(SC95F7x2x)
/**************************************************
*函数名称:void USCI0_SC_Init()
*函数功能:智能卡初始化配置函数
*入口参数:
FunctionalState:ClockEnable:时钟输出使能位
USCI0_SC_ERS_TypeDef:ErrorSignal:ErrorSignal长度
USCI0_SC_TREN_TypeDef:TrenMode:发送/接收使能，发送和接收只能二选一
USCI0_SC_CONS_TypeDef:ConsMod:编码方式选择
FunctionalState:ReSend:数据发送接收校验出错重发使能位
USCI0_SC_Check_TypeDef:CheckType:校验类型
*出口参数:void
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
*函数名称:void USCI0_SC_EGT(uint8_t EgtCount)
*函数功能:智能卡拓展保护时间设置
*入口参数:
uint8_t:EgtCount:拓展保护时间数:EgtCount个ETU
*出口参数:void
**************************************************/
void USCI0_SC_EGT(uint8_t EgtCount)
{
  US0CON4 = EgtCount;
}

/**************************************************
*函数名称:void USCI0_SC_ETU_SET(USCI0_SC_Pres	Sel_TypeDef SC_PrescalerSelection,uint8_t EtuCk)
*函数功能:ETU设置，一个ETU时间长度设置
*入口参数:
USCI0_SC_PresSel_TypeDef:SC_PrescalerSelection:SC Clock 时钟来源
uint16_t:EtuCk:一个ETU为(EtuCk+1)个SC Clock。必须大于0x004
*出口参数:void
**************************************************/
void USCI0_SC_ETU_SET(USCI0_SC_PresSel_TypeDef SC_PrescalerSelection, uint16_t EtuCk)
{
  US0CON2 = (EtuCk >> 8);
  US0CON1 = (uint8_t)EtuCk;
  US0CON2 = (SC_PrescalerSelection << 4);
}
/*****************************************************
*函数名称:void USCI0_SC_Cmd(FunctionalState NewState)
*函数功能:智能卡功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
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
*函数名称:FlagStatus USCI0_SC_GetFlagStatus(USCI0_SC_Flag_TypeDef USCI0_SC_FLAG)
*函数功能:获得SC标志状态
*入口参数:
USCI0_SC_Flag_TypeDef:USCI0_SC_FLAG:所需获取的标志位
*出口参数:
FlagStatus:USCI0_SC标志状态
*****************************************************/
FlagStatus USCI0_SC_GetFlagStatus(USCI0_SC_Flag_TypeDef USCI0_SC_FLAG)
{
  //	  寄存器切换控制位:
  //	  0 :US0CON5 (B7H)为读写状态寄存器
  //	  1 :US0CON5 (B7H)为读写错误信息寄存器
  US0CON5 |= (USCI0_SC_FLAG & 0X80);
  return USCI0_SC_FLAG & US0CON5;
}
/*****************************************************
*函数名称:void USCI0_UART_SendData(uint8_t Data)
*函数功能:USCI0 SC发送8位数据
*入口参数:
uint8_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI0_SC_SendData(uint8_t Data)
{
  US0CON3 = Data;
}
/*****************************************************
*函数名称:uint8_t USCI0_SC_ReceiveData(void)
*函数功能:获得接收缓存中的值
*入口参数:void
*出口参数:
uint8_t:接收的数据
*****************************************************/
uint8_t USCI0_SC_ReceiveData(void)
{
  return US0CON3;
}

#endif

#if defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)
/**********************************************************************************************************
*函数名称:uint8_t USCI0_SPI_WriteFIFO(uint16_t *sbuf,uint8_t length)
*函数功能:SPI0写入FIFO
*入口参数:
uint16_t:*sbuf:发送buffer
uint8_t:length:发送数据长度
*出口参数:
uint8_t:(0:非法操作；1:写入FIFO缓存成功)
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
    US0CON1 &= ~0x01; //关闭TBIE

    for (i = 0; i < length; i++)
    {
      US0CON3 = *(sbuf + i) >> 8; //写入待发送数据的高字节
      US0CON2 = *(sbuf + i);      //写入待发送数据的低字节
    }

    if (length != 0x01) //若非单次写入，需清除TXE
    {
      US0CON1 &= (~0x08); //清TXE
    }

    US0CON1 |= 0x01; //开启TBIE
    return 1;
  }
}
#endif

#endif

/******************* (C) COPYRIGHT 2022 SinOne Microelectronics *****END OF FILE****/
