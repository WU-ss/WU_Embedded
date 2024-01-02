//************************************************************
//  Copyright (c) 
//	文件名称	: sc95f_usci0.h
//	作者		:
//	模块功能	: USCI0固件库函数头文件
//  最后更正日期: 2022/01/24
// 	版本		: V1.10003
//  说明        :该文件仅适用于SC95F系列芯片
//*************************************************************

#ifndef _sc95f_USCI0_H_
#define _sc95f_USCI0_H_

#include "sc95f.h"

#if !defined (SC95R751) && !defined (SC95F7610B)

#define USCI0_UART_BaudRate_FsysDIV12 0X00 //仅模式0可用，串行端口在系统时钟的1/12下运行
#define USCI0_UART_BaudRate_FsysDIV4 0X01  //仅模式0可用，串行端口在系统时钟的1/4下运行

#if defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)
typedef enum
{
  USCI0_Mode_SC = (uint8_t)0x00,  //SmartCard
  USCI0_Mode_SPI = (uint8_t)0x01, //SPI
  USCI0_Mode_TWI = (uint8_t)0x02, //TWI
  USCI0_Mode_UART = (uint8_t)0x03 //UART
} USCI0_CommunicationMode_TypeDef;
#else
typedef enum
{
  USCI0_Mode_SPI = (uint8_t)0x01, //SPI
  USCI0_Mode_TWI = (uint8_t)0x02, //TWI
  USCI0_Mode_UART = (uint8_t)0x03 //UART
} USCI0_CommunicationMode_TypeDef;
#endif

typedef enum
{
  USCI0_SPI_FIRSTBIT_MSB = (uint8_t)0x00, //MSB优先发送
  USCI0_SPI_FIRSTBIT_LSB = (uint8_t)0x04  //LSB优先发送
} USCI0_SPI_FirstBit_TypeDef;

typedef enum
{
  USCI0_SPI_BAUDRATEPRESCALER_1 = (uint8_t)0x00,  //SPI时钟速率为系统时钟除以1
  USCI0_SPI_BAUDRATEPRESCALER_2 = (uint8_t)0x01,  //SPI时钟速率为系统时钟除以2
  USCI0_SPI_BAUDRATEPRESCALER_4 = (uint8_t)0x02,  //SPI时钟速率为系统时钟除以4
  USCI0_SPI_BAUDRATEPRESCALER_8 = (uint8_t)0x03,  //SPI时钟速率为系统时钟除以8
  USCI0_SPI_BAUDRATEPRESCALER_16 = (uint8_t)0x04, //SPI时钟速率为系统时钟除以16
  USCI0_SPI_BAUDRATEPRESCALER_32 = (uint8_t)0x05, //SPI时钟速率为系统时钟除以32
  USCI0_SPI_BAUDRATEPRESCALER_64 = (uint8_t)0x06, //SPI时钟速率为系统时钟除以64
  USCI0_SPI_BAUDRATEPRESCALER_128 = (uint8_t)0x07 //SPI时钟速率为系统时钟除以128
} USCI0_SPI_BaudRatePrescaler_TypeDef;

typedef enum
{
  USCI0_SPI_MODE_MASTER = (uint8_t)0x20, //SPI为主设备
  USCI0_SPI_MODE_SLAVE = (uint8_t)0x00   //SPI为从设备
} USCI0_SPI_Mode_TypeDef;

typedef enum
{
  USCI0_SPI_CLOCKPOLARITY_LOW = (uint8_t)0x00, //SCK在空闲状态下为低电平
  USCI0_SPI_CLOCKPOLARITY_HIGH = (uint8_t)0x10 //SCK在空闲状态下为高电平
} USCI0_SPI_ClockPolarity_TypeDef;

typedef enum
{
  USCI0_SPI_CLOCKPHASE_1EDGE = (uint8_t)0x00, //SCK的第一沿采集数据
  USCI0_SPI_CLOCKPHASE_2EDGE = (uint8_t)0x08  //SCK的第二沿采集数据
} USCI0_SPI_ClockPhase_TypeDef;

typedef enum
{
  USCI0_SPI_TXE_DISINT = (uint8_t)0x00, //TBIE为0时不允许发送中断
  USCI0_SPI_TXE_ENINT = (uint8_t)0x01   //TBIE为1时允许发送中断
} USCI0_SPI_TXE_INT_TypeDef;

typedef enum
{
  USCI0_SPI_DATA8 = (uint8_t)0x00, //SPI 8位传输模式
  USCI0_SPI_DATA16 = (uint8_t)0x02 //SPI 16位传输模式
} USCI0_TransmissionMode_TypeDef;

typedef enum
{
  USCI0_TWI_1024 = (uint8_t)0x00, //TWI通信速率 Fhrc/1024
  USCI0_TWI_512 = (uint8_t)0x01,  //TWI通信速率 Fhrc/512
  USCI0_TWI_256 = (uint8_t)0x02,  //TWI通信速率 Fhrc/256
  USCI0_TWI_128 = (uint8_t)0x03,  //TWI通信速率 Fhrc/128
  USCI0_TWI_64 = (uint8_t)0x04,   //TWI通信速率 Fhrc/64
  USCI0_TWI_32 = (uint8_t)0x05,   //TWI通信速率 Fhrc/32
  USCI0_TWI_16 = (uint8_t)0x06,   //TWI通信速率 Fhrc/16
} USCI0_TWI_MasterCommunicationRate_TypeDef;

typedef enum
{
  USCI0_TWI_SlaveBusy = 0x00, //作为从机
  USCI0_TWI_SlaveReceivedaAddress = 0x01,
  USCI0_TWI_SlaveReceivedaData = 0x02,
  USCI0_TWI_SlaveSendData = 0x03,
  USCI0_TWI_SlaveReceivedaUACK = 0x04,
  USCI0_TWI_SlaveDisableACK = 0x05,
  USCI0_TWI_SlaveAddressError = 0x06,
  USCI0_TWI_MasterBusy = 0x00, //作为主机
  USCI0_TWI_MasterSendAddress = 0x01,
  USCI0_TWI_MasterSendData = 0x02,
  USCI0_TWI_MasterReceivedaData = 0x03,
  USCI0_TWI_MasterReceivedaUACK = 0x04,
} USCI0_TWIState_TypeDef;

typedef enum
{
  USCI0_UART_Mode_8B = 0X00,  //UART设置为8位模式
  USCI0_UART_Mode_10B = 0X40, //UART设置为10位模式
  USCI0_UART_Mode_11B = 0X80  //UART设置为11位模式
} USCI0_UART_Mode_TypeDef;

typedef enum
{
  USCI0_UART_RX_ENABLE = 0X10, //UART允许接收
  USCI0_UART_RX_DISABLE = 0X00 //UART禁止接收
} USCI0_UART_RX_TypeDef;

typedef enum
{
  USCI0_SPI_FLAG_SPIF = (uint8_t)0x80, //SPI数据传送标志位SPIF
  USCI0_SPI_FLAG_WCOL = (uint8_t)0x50, //SPI写入冲突标志位WCOL
  USCI0_SPI_FLAG_TXE = (uint8_t)0x08,  //SPI发送缓存器空标志TXE
  USCI0_TWI_FLAG_TWIF = (uint8_t)0x40, //TWI中断标志位TWIF
  USCI0_TWI_FLAG_GCA = (uint8_t)0x10,  //TWI通用地址响应标志位GCA
  USCI0_TWI_FLAG_MSTR = (uint8_t)0x20, //TWI主从标志位MSTR
  USCI0_TWI_FLAG_TXRXnE = (uint8_t)0x80,
  USCI0_UART_FLAG_RI = (uint8_t)0x01, //UART接收中断标志位RI
  USCI0_UART_FLAG_TI = (uint8_t)0x02, //UART发送中断标志位TI
} USCI0_Flag_TypeDef;

typedef enum
{
  USCI0_TWI_Write = 0x00, //写操作
  USCI0_TWI_Read = 0x01,  //读操作
} USCI0_TWI_RWType;

#if defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)
typedef enum
{
  USCI0_SC_FLAG_TC = (uint8_t)0x40,    //发送完成标志位，发送完成硬件置1，需软件清零
  USCI0_SC_FLAG_RC = (uint8_t)0x20,    //接收完成标志位，接收完成硬件置1，需软件清零
  USCI0_SC_FLAG_WTRT = (uint8_t)0x10,  //等待数据重发标志位
  USCI0_SC_FLAG_TBUSY = (uint8_t)0x08, //数据发送忙标志位
  USCI0_SC_FLAG_RBUSY = (uint8_t)0x04, //数据接收忙标志位
  USCI0_SC_FLAG_WTER = (uint8_t)0x02,  //等待超时标志位
  USCI0_SC_FLAG_FER = (uint8_t)0x01,   //接收帧错误标志位
  USCI0_SC_FLAG_TPER = (uint8_t)0x88,  //发送数据奇偶校验错误标志位
  USCI0_SC_FLAG_RPER = (uint8_t)0x84,  //接收数据奇偶校验错误标志位
  USCI0_SC_FLAG_ROVF = (uint8_t)0x81   //接收溢出标志位
} USCI0_SC_Flag_TypeDef;

typedef enum
{
  USCI0_SC_RECE = (uint8_t)0x00, //接收使能，发送禁止
  USCI0_SC_SEND = (uint8_t)0x20, //发送使能，接收禁止
} USCI0_SC_TREN_TypeDef;

typedef enum
{
  USCI0_SC_Cons_Forward = (uint8_t)0x00, //正向约定方式，逻辑电平与实际一致
  USCI0_SC_Cons_Reverse = (uint8_t)0x04  //反向约定方式，逻辑电平与实际相反
} USCI0_SC_CONS_TypeDef;

typedef enum
{
  USCI0_SC_PRESSEL_FSYS_D2 = (uint8_t)0x00,  //智能卡时钟源来自系统时钟2分频
  USCI0_SC_PRESSEL_FSYS_D4 = (uint8_t)0x01,  //智能卡时钟源来自系统时钟4分频
  USCI0_SC_PRESSEL_FSYS_D6 = (uint8_t)0x02,  //智能卡时钟源来自系统时钟6分频
  USCI0_SC_PRESSEL_FSYS_D8 = (uint8_t)0x03,  //智能卡时钟源来自系统时钟8分频
  USCI0_SC_PRESSEL_FSYS_D10 = (uint8_t)0x04, //智能卡时钟源来自系统时钟10分频
  USCI0_SC_PRESSEL_FSYS_D12 = (uint8_t)0x05, //智能卡时钟源来自系统时钟12分频
  USCI0_SC_PRESSEL_FSYS_D14 = (uint8_t)0x06, //智能卡时钟源来自系统时钟14分频
  USCI0_SC_PRESSEL_FSYS_D16 = (uint8_t)0x07, //智能卡时钟源来自系统时钟16分频
  USCI0_SC_PRESSEL_FSYS_D18 = (uint8_t)0x08, //智能卡时钟源来自系统时钟18分频
  USCI0_SC_PRESSEL_FSYS_D20 = (uint8_t)0x09, //智能卡时钟源来自系统时钟20分频
  USCI0_SC_PRESSEL_FSYS_D22 = (uint8_t)0x0a, //智能卡时钟源来自系统时钟22分频
  USCI0_SC_PRESSEL_FSYS_D24 = (uint8_t)0x0b, //智能卡时钟源来自系统时钟24分频
  USCI0_SC_PRESSEL_FSYS_D26 = (uint8_t)0x0c, //智能卡时钟源来自系统时钟26分频
  USCI0_SC_PRESSEL_FSYS_D28 = (uint8_t)0x0d, //智能卡时钟源来自系统时钟28分频
  USCI0_SC_PRESSEL_FSYS_D30 = (uint8_t)0x0e, //智能卡时钟源来自系统时钟30分频
  USCI0_SC_PRESSEL_FSYS_D32 = (uint8_t)0x0f  //智能卡时钟源来自系统时钟32分频
} USCI0_SC_PresSel_TypeDef;

typedef enum
{
  USCI0_SC_ERS_2_ETU = 0x00,   //Stop及Error Signal长度均为2个ETU
  USCI0_SC_ERS_1P5_ETU = 0x02, //Stop及Error Signal长度均为1.5个ETU
  USCI0_SC_ERS_1_ETU = 0x03    //Stop及Error Signal长度均为1个ETU
} USCI0_SC_ERS_TypeDef;

typedef enum
{
  USCI0_SC_NoCheck = 0x00,  //无校验
  USCI0_SC_EvenCheck = 0x01 //偶校验
} USCI0_SC_Check_TypeDef;

#endif

void USCI0_DeInit(void);
void USCI0_SPI_Init(USCI0_SPI_FirstBit_TypeDef FirstBit,
                    USCI0_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, USCI0_SPI_Mode_TypeDef Mode,
                    USCI0_SPI_ClockPolarity_TypeDef ClockPolarity, USCI0_SPI_ClockPhase_TypeDef ClockPhase,
                    USCI0_SPI_TXE_INT_TypeDef SPI_TXE_INT, USCI0_TransmissionMode_TypeDef TransmissionMode);
void USCI0_TransmissionMode(USCI0_TransmissionMode_TypeDef TransmissionMode);
void USCI0_SPI_Cmd(FunctionalState NewState);
void USCI0_SPI_SendData_8(uint8_t Data);
uint8_t USCI0_SPI_ReceiveData_8(void);
void USCI0_SPI_SendData_16(uint16_t Data);
uint16_t USCI0_SPI_ReceiveData_16(void);
void USCI0_TWI_Slave_Init(uint8_t TWI_Address);
void USCI0_TWI_MasterCommunicationRate(USCI0_TWI_MasterCommunicationRate_TypeDef
                                           TWI_MasterCommunicationRate);
void USCI0_TWI_Start(void);
void USCI0_TWI_MasterModeStop(void);
void USCI0_TWI_SendAddr(uint8_t Addr, USCI0_TWI_RWType RW);
void USCI0_TWI_SlaveClockExtension(FunctionalState NewState);
void USCI0_TWI_AcknowledgeConfig(FunctionalState NewState);
void USCI0_TWI_GeneralCallCmd(FunctionalState NewState);
FlagStatus USCI0_GetTWIStatus(USCI0_TWIState_TypeDef USCI0_TWIState);
void USCI0_TWI_Cmd(FunctionalState NewState);
void USCI0_TWI_SendData(uint8_t Data);
uint8_t USCI0_TWI_ReceiveData(void);
void USCI0_UART_Init(uint32_t UART1Fsys, uint32_t BaudRate, USCI0_UART_Mode_TypeDef Mode,
                     USCI0_UART_RX_TypeDef RxMode);
void USCI0_UART_SendData8(uint8_t Data);
uint8_t USCI0_UART_ReceiveData8(void);
void USCI0_UART_SendData9(uint16_t Data);
uint16_t USCI0_UART_ReceiveData9(void);
void USCI0_ITConfig(FunctionalState NewState, PriorityStatus Priority);
FlagStatus USCI0_GetFlagStatus(USCI0_Flag_TypeDef USCI0_FLAG);
void USCI0_ClearFlag(USCI0_Flag_TypeDef USCI0_FLAG);

#if defined(SC95F8x2x) || defined(SC95F7x2x)
void USCI0_SC_Init(FunctionalState ClockEnable,
                   USCI0_SC_ERS_TypeDef ErrorSignal,
                   USCI0_SC_TREN_TypeDef TrenMode,
                   USCI0_SC_CONS_TypeDef ConsMode,
                   FunctionalState ReSend,
                   USCI0_SC_Check_TypeDef CheckType);
void USCI0_SC_EGT(uint8_t EgtCount);
void USCI0_SC_Cmd(FunctionalState NewState);
void USCI0_SC_ETU_SET(USCI0_SC_PresSel_TypeDef SC_PrescalerSelection, uint16_t EtuCk);
FlagStatus USCI0_SC_GetFlagStatus(USCI0_SC_Flag_TypeDef USCI0_SC_FLAG);
void USCI0_SC_SendData(uint8_t Data);
uint8_t USCI0_SC_ReceiveData(void);
#endif
#if defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)
uint8_t USCI0_SPI_WriteFIFO(uint16_t *sbuf, uint8_t length);
#endif
#endif

#endif

/******************* (C) COPYRIGHT 2022 SinOne Microelectronics *****END OF FILE****/