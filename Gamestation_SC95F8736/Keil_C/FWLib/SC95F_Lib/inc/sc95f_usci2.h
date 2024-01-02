//************************************************************
//  Copyright (c) 
//	文件名称	: sc95f_usci2.h
//	作者		:
//	模块功能	: USCI2固件库函数头文件
//  最后更正日期: 2021/7/14
// 	版本		: V1.1000
//  说明        :该文件仅适用于SC95F系列芯片
//*************************************************************

#ifndef _sc95f_USCI2_H_
#define _sc95f_USCI2_H_

#include "sc95f.h"

#define USCI2_UART_BaudRate_FsysDIV12 0X00 //仅模式0可用，串行端口在系统时钟的1/12下运行
#define USCI2_UART_BaudRate_FsysDIV4 0X01  //仅模式0可用，串行端口在系统时钟的1/4下运行

typedef enum
{
  USCI2_Mode_SPI = (uint8_t)0x01, //SPI
  USCI2_Mode_TWI = (uint8_t)0x02, //TWI
  USCI2_Mode_UART = (uint8_t)0x03 //UART
} USCI2_CommunicationMode_TypeDef;

typedef enum
{
  USCI2_SPI_FIRSTBIT_MSB = (uint8_t)0x00, //MSB优先发送
  USCI2_SPI_FIRSTBIT_LSB = (uint8_t)0x04  //LSB优先发送
} USCI2_SPI_FirstBit_TypeDef;

typedef enum
{
  USCI2_SPI_BAUDRATEPRESCALER_1 = (uint8_t)0x00,  //SPI时钟速率为系统时钟除以1
  USCI2_SPI_BAUDRATEPRESCALER_2 = (uint8_t)0x01,  //SPI时钟速率为系统时钟除以2
  USCI2_SPI_BAUDRATEPRESCALER_4 = (uint8_t)0x02,  //SPI时钟速率为系统时钟除以4
  USCI2_SPI_BAUDRATEPRESCALER_8 = (uint8_t)0x03,  //SPI时钟速率为系统时钟除以8
  USCI2_SPI_BAUDRATEPRESCALER_16 = (uint8_t)0x04, //SPI时钟速率为系统时钟除以16
  USCI2_SPI_BAUDRATEPRESCALER_32 = (uint8_t)0x05, //SPI时钟速率为系统时钟除以32
  USCI2_SPI_BAUDRATEPRESCALER_64 = (uint8_t)0x06, //SPI时钟速率为系统时钟除以64
  USCI2_SPI_BAUDRATEPRESCALER_128 = (uint8_t)0x07 //SPI时钟速率为系统时钟除以128
} USCI2_SPI_BaudRatePrescaler_TypeDef;

typedef enum
{
  USCI2_SPI_MODE_MASTER = (uint8_t)0x20, //SPI为主设备
  USCI2_SPI_MODE_SLAVE = (uint8_t)0x00   //SPI为从设备
} USCI2_SPI_Mode_TypeDef;

typedef enum
{
  USCI2_SPI_CLOCKPOLARITY_LOW = (uint8_t)0x00, //SCK在空闲状态下为低电平
  USCI2_SPI_CLOCKPOLARITY_HIGH = (uint8_t)0x10 //SCK在空闲状态下为高电平
} USCI2_SPI_ClockPolarity_TypeDef;

typedef enum
{
  USCI2_SPI_CLOCKPHASE_1EDGE = (uint8_t)0x00, //SCK的第一沿采集数据
  USCI2_SPI_CLOCKPHASE_2EDGE = (uint8_t)0x08  //SCK的第二沿采集数据
} USCI2_SPI_ClockPhase_TypeDef;

typedef enum
{
  USCI2_SPI_TXE_DISINT = (uint8_t)0x00, //TBIE为0时不允许发送中断
  USCI2_SPI_TXE_ENINT = (uint8_t)0x01   //TBIE为1时允许发送中断
} USCI2_SPI_TXE_INT_TypeDef;

typedef enum
{
  USCI2_SPI_DATA8 = (uint8_t)0x00, //SPI 8位传输模式
  USCI2_SPI_DATA16 = (uint8_t)0x01 //SPI 16位传输模式
} USCI2_TransmissionMode_TypeDef;

typedef enum
{
  USCI2_TWI_1024 = (uint8_t)0x00, //TWI通信速率 Fhrc/1024
  USCI2_TWI_512 = (uint8_t)0x01,  //TWI通信速率 Fhrc/512
  USCI2_TWI_256 = (uint8_t)0x02,  //TWI通信速率 Fhrc/256
  USCI2_TWI_128 = (uint8_t)0x03,  //TWI通信速率 Fhrc/128
  USCI2_TWI_64 = (uint8_t)0x04,   //TWI通信速率 Fhrc/64
  USCI2_TWI_32 = (uint8_t)0x05,   //TWI通信速率 Fhrc/32
  USCI2_TWI_16 = (uint8_t)0x06,   //TWI通信速率 Fhrc/16
} USCI2_TWI_MasterCommunicationRate_TypeDef;

typedef enum
{
  USCI2_TWI_SlaveBusy = 0x00,
  USCI2_TWI_SlaveReceivedaAddress = 0x01,
  USCI2_TWI_SlaveReceivedaData = 0x02,
  USCI2_TWI_SlaveSendData = 0x03,
  USCI2_TWI_SlaveReceivedaUACK = 0x04,
  USCI2_TWI_SlaveDisableACK = 0x05,
  USCI2_TWI_SlaveAddressError = 0x06,
  USCI2_TWI_MasterBusy = 0x00,
  USCI2_TWI_MasterSendAddress = 0x01,
  USCI2_TWI_MasterSendData = 0x02,
  USCI2_TWI_MasterReceivedaData = 0x03,
  USCI2_TWI_MasterReceivedaUACK = 0x04,
} USCI2_TWIState_TypeDef;

typedef enum
{
  USCI2_UART_Mode_8B = 0X00,  //UART设置为8位模式
  USCI2_UART_Mode_10B = 0X40, //UART设置为10位模式
  USCI2_UART_Mode_11B = 0X80  //UART设置为11位模式
} USCI2_UART_Mode_TypeDef;

typedef enum
{
  USCI2_UART_RX_ENABLE = 0X10, //UART允许接收
  USCI2_UART_RX_DISABLE = 0X00 //UART禁止接收
} USCI2_UART_RX_TypeDef;

typedef enum
{
  USCI2_SPI_FLAG_SPIF = (uint8_t)0x80, //SPI数据传送标志位SPIF
  USCI2_SPI_FLAG_WCOL = (uint8_t)0x50, //SPI写入冲突标志位WCOL
  USCI2_SPI_FLAG_TXE = (uint8_t)0x08,  //SPI发送缓存器空标志TXE
  USCI2_TWI_FLAG_TWIF = (uint8_t)0x40, //TWI中断标志位TWIF
  USCI2_TWI_FLAG_GCA = (uint8_t)0x10,  //TWI通用地址响应标志位GCA
  USCI2_TWI_FLAG_MSTR = (uint8_t)0x20, //TWI主从标志位MSTR
  USCI2_TWI_FLAG_TXRXnE = (uint8_t)0x80,
  USCI2_UART_FLAG_RI = (uint8_t)0x01, //UART接收中断标志位RI
  USCI2_UART_FLAG_TI = (uint8_t)0x02, //UART发送中断标志位TI
} USCI2_Flag_TypeDef;

typedef enum
{
  USCI2_TWI_Write = 0x00, //写操作
  USCI2_TWI_Read = 0x01,  //读操作
} USCI2_TWI_RWType;

void USCI2_DeInit(void);
void USCI2_SPI_Init(USCI2_SPI_FirstBit_TypeDef FirstBit,
                    USCI2_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, USCI2_SPI_Mode_TypeDef Mode,
                    USCI2_SPI_ClockPolarity_TypeDef ClockPolarity, USCI2_SPI_ClockPhase_TypeDef ClockPhase,
                    USCI2_SPI_TXE_INT_TypeDef SPI_TXE_INT, USCI2_TransmissionMode_TypeDef TransmissionMode);
void USCI2_TransmissionMode(USCI2_TransmissionMode_TypeDef TransmissionMode);
void USCI2_SPI_Cmd(FunctionalState NewState);
void USCI2_SPI_SendData_8(uint8_t Data);
uint8_t USCI2_SPI_ReceiveData_8(void);
void USCI2_SPI_SendData_16(uint16_t Data);
uint16_t USCI2_SPI_ReceiveData_16(void);
void USCI2_TWI_Slave_Init(uint8_t TWI_Address);
void USCI2_TWI_MasterCommunicationRate(USCI2_TWI_MasterCommunicationRate_TypeDef
                                           TWI_MasterCommunicationRate);
void USCI2_TWI_Start(void);
void USCI2_TWI_MasterModeStop(void);
void USCI2_TWI_SlaveClockExtension(FunctionalState NewState);
void USCI2_TWI_AcknowledgeConfig(FunctionalState NewState);
void USCI2_TWI_GeneralCallCmd(FunctionalState NewState);
FlagStatus USCI2_GetTWIStatus(USCI2_TWIState_TypeDef USCI2_TWIState);
void USCI2_TWI_Cmd(FunctionalState NewState);
void USCI2_TWI_SendData(uint8_t Data);
uint8_t USCI2_TWI_ReceiveData(void);
void USCI2_UART_Init(uint32_t UART1Fsys, uint32_t BaudRate, USCI2_UART_Mode_TypeDef Mode,
                     USCI2_UART_RX_TypeDef RxMode);
void USCI2_UART_SendData8(uint8_t Data);
uint8_t USCI2_UART_ReceiveData8(void);
void USCI2_UART_SendData9(uint16_t Data);
uint16_t USCI2_UART_ReceiveData9(void);
void USCI2_ITConfig(FunctionalState NewState, PriorityStatus Priority);
FlagStatus USCI2_GetFlagStatus(USCI2_Flag_TypeDef USCI2_FLAG);
void USCI2_ClearFlag(USCI2_Flag_TypeDef USCI2_FLAG);
void USCI2_TWI_SendAddr(uint8_t Addr, USCI2_TWI_RWType RW);
#endif

/******************* (C) COPYRIGHT 2022 SinOne Microelectronics *****END OF FILE****/