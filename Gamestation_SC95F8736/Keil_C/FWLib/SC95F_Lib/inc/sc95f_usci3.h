//************************************************************
//  Copyright (c) 
//	文件名称	: sc95f_USCI3.h
//	作者		:
//	模块功能	: USCI3固件库函数头文件
//  最后更正日期: 2021/07/14
// 	版本		: V1.0002
//  说明        :该文件仅适用于SC95Fxx1x、SC95Fxx2x系列芯片
//*************************************************************

#ifndef _sc95f_USCI3_H_
#define _sc95f_USCI3_H_

#include "sc95f.h"

#define USCI3_UART_BaudRate_FsysDIV12 0X00 //仅模式0可用，串行端口在系统时钟的1/12下运行
#define USCI3_UART_BaudRate_FsysDIV4 0X01  //仅模式0可用，串行端口在系统时钟的1/4下运行

typedef enum
{
  USCI3_Mode_SPI = (uint8_t)0x01, //SPI
  USCI3_Mode_TWI = (uint8_t)0x02, //TWI
  USCI3_Mode_UART = (uint8_t)0x03 //UART
} USCI3_CommunicationMode_TypeDef;

typedef enum
{
  USCI3_SPI_FIRSTBIT_MSB = (uint8_t)0x00, //MSB优先发送
  USCI3_SPI_FIRSTBIT_LSB = (uint8_t)0x04  //LSB优先发送
} USCI3_SPI_FirstBit_TypeDef;

typedef enum
{
  USCI3_SPI_BAUDRATEPRESCALER_1 = (uint8_t)0x00,  //SPI时钟速率为系统时钟除以1
  USCI3_SPI_BAUDRATEPRESCALER_2 = (uint8_t)0x01,  //SPI时钟速率为系统时钟除以2
  USCI3_SPI_BAUDRATEPRESCALER_4 = (uint8_t)0x02,  //SPI时钟速率为系统时钟除以4
  USCI3_SPI_BAUDRATEPRESCALER_8 = (uint8_t)0x03,  //SPI时钟速率为系统时钟除以8
  USCI3_SPI_BAUDRATEPRESCALER_16 = (uint8_t)0x04, //SPI时钟速率为系统时钟除以16
  USCI3_SPI_BAUDRATEPRESCALER_32 = (uint8_t)0x05, //SPI时钟速率为系统时钟除以32
  USCI3_SPI_BAUDRATEPRESCALER_64 = (uint8_t)0x06, //SPI时钟速率为系统时钟除以64
  USCI3_SPI_BAUDRATEPRESCALER_128 = (uint8_t)0x07 //SPI时钟速率为系统时钟除以128
} USCI3_SPI_BaudRatePrescaler_TypeDef;

typedef enum
{
  USCI3_SPI_MODE_MASTER = (uint8_t)0x20, //SPI为主设备
  USCI3_SPI_MODE_SLAVE = (uint8_t)0x00   //SPI为从设备
} USCI3_SPI_Mode_TypeDef;

typedef enum
{
  USCI3_SPI_CLOCKPOLARITY_LOW = (uint8_t)0x00, //SCK在空闲状态下为低电平
  USCI3_SPI_CLOCKPOLARITY_HIGH = (uint8_t)0x10 //SCK在空闲状态下为高电平
} USCI3_SPI_ClockPolarity_TypeDef;

typedef enum
{
  USCI3_SPI_CLOCKPHASE_1EDGE = (uint8_t)0x00, //SCK的第一沿采集数据
  USCI3_SPI_CLOCKPHASE_2EDGE = (uint8_t)0x08  //SCK的第二沿采集数据
} USCI3_SPI_ClockPhase_TypeDef;

typedef enum
{
  USCI3_SPI_TXE_DISINT = (uint8_t)0x00, //TBIE为0时不允许发送中断
  USCI3_SPI_TXE_ENINT = (uint8_t)0x01   //TBIE为1时允许发送中断
} USCI3_SPI_TXE_INT_TypeDef;

typedef enum
{
  USCI3_SPI_DATA8 = (uint8_t)0x00, //SPI 8位传输模式
  USCI3_SPI_DATA16 = (uint8_t)0x01 //SPI 16位传输模式
} USCI3_TransmissionMode_TypeDef;

typedef enum
{
  USCI3_TWI_1024 = (uint8_t)0x00, //TWI通信速率 Fhrc/1024
  USCI3_TWI_512 = (uint8_t)0x01,  //TWI通信速率 Fhrc/512
  USCI3_TWI_256 = (uint8_t)0x02,  //TWI通信速率 Fhrc/256
  USCI3_TWI_128 = (uint8_t)0x03,  //TWI通信速率 Fhrc/128
  USCI3_TWI_64 = (uint8_t)0x04,   //TWI通信速率 Fhrc/64
  USCI3_TWI_32 = (uint8_t)0x05,   //TWI通信速率 Fhrc/32
  USCI3_TWI_16 = (uint8_t)0x06,   //TWI通信速率 Fhrc/16
} USCI3_TWI_MasterCommunicationRate_TypeDef;

typedef enum
{
  USCI3_TWI_SlaveBusy = 0x00,
  USCI3_TWI_SlaveReceivedaAddress = 0x01,
  USCI3_TWI_SlaveReceivedaData = 0x02,
  USCI3_TWI_SlaveSendData = 0x03,
  USCI3_TWI_SlaveReceivedaUACK = 0x04,
  USCI3_TWI_SlaveDisableACK = 0x05,
  USCI3_TWI_SlaveAddressError = 0x06,
  USCI3_TWI_MasterBusy = 0x00,
  USCI3_TWI_MasterSendAddress = 0x01,
  USCI3_TWI_MasterSendData = 0x02,
  USCI3_TWI_MasterReceivedaData = 0x03,
  USCI3_TWI_MasterReceivedaUACK = 0x04,
} USCI3_TWIState_TypeDef;

typedef enum
{
  USCI3_UART_Mode_8B = 0X00,  //UART设置为8位模式
  USCI3_UART_Mode_10B = 0X40, //UART设置为10位模式
  USCI3_UART_Mode_11B = 0X80  //UART设置为11位模式
} USCI3_UART_Mode_TypeDef;

typedef enum
{
  USCI3_UART_RX_ENABLE = 0X10, //UART允许接收
  USCI3_UART_RX_DISABLE = 0X00 //UART禁止接收
} USCI3_UART_RX_TypeDef;

typedef enum
{
  USCI3_SPI_FLAG_SPIF = (uint8_t)0x80, //SPI数据传送标志位SPIF
  USCI3_SPI_FLAG_WCOL = (uint8_t)0x50, //SPI写入冲突标志位WCOL
  USCI3_SPI_FLAG_TXE = (uint8_t)0x08,  //SPI发送缓存器空标志TXE
  USCI3_TWI_FLAG_TWIF = (uint8_t)0x40, //TWI中断标志位TWIF
  USCI3_TWI_FLAG_GCA = (uint8_t)0x10,  //TWI通用地址响应标志位GCA
  USCI3_TWI_FLAG_MSTR = (uint8_t)0x20, //TWI主从标志位MSTR
  USCI3_TWI_FLAG_TXRXnE = (uint8_t)0x80,
  USCI3_UART_FLAG_RI = (uint8_t)0x01, //UART接收中断标志位RI
  USCI3_UART_FLAG_TI = (uint8_t)0x02, //UART发送中断标志位TI
} USCI3_Flag_TypeDef;

typedef enum
{
  USCI3_TWI_Write = 0x00, //写操作
  USCI3_TWI_Read = 0x01,  //读操作
} USCI3_TWI_RWType;

void USCI3_DeInit(void);
void USCI3_SPI_Init(USCI3_SPI_FirstBit_TypeDef FirstBit,
                    USCI3_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, USCI3_SPI_Mode_TypeDef Mode,
                    USCI3_SPI_ClockPolarity_TypeDef ClockPolarity, USCI3_SPI_ClockPhase_TypeDef ClockPhase,
                    USCI3_SPI_TXE_INT_TypeDef SPI_TXE_INT, USCI3_TransmissionMode_TypeDef TransmissionMode);
void USCI3_TransmissionMode(USCI3_TransmissionMode_TypeDef TransmissionMode);
void USCI3_SPI_Cmd(FunctionalState NewState);
void USCI3_SPI_SendData_8(uint8_t Data);
uint8_t USCI3_SPI_ReceiveData_8(void);
void USCI3_SPI_SendData_16(uint16_t Data);
uint16_t USCI3_SPI_ReceiveData_16(void);
void USCI3_TWI_Slave_Init(uint8_t TWI_Address);
void USCI3_TWI_MasterCommunicationRate(USCI3_TWI_MasterCommunicationRate_TypeDef
                                           TWI_MasterCommunicationRate);
void USCI3_TWI_Start(void);
void USCI3_TWI_MasterModeStop(void);
void USCI3_TWI_SlaveClockExtension(FunctionalState NewState);
void USCI3_TWI_AcknowledgeConfig(FunctionalState NewState);
void USCI3_TWI_GeneralCallCmd(FunctionalState NewState);
FlagStatus USCI3_GetTWIStatus(USCI3_TWIState_TypeDef USCI3_TWIState);
void USCI3_TWI_Cmd(FunctionalState NewState);
void USCI3_TWI_SendData(uint8_t Data);
uint8_t USCI3_TWI_ReceiveData(void);
void USCI3_UART_Init(uint32_t UART1Fsys, uint32_t BaudRate, USCI3_UART_Mode_TypeDef Mode,
                     USCI3_UART_RX_TypeDef RxMode);
void USCI3_UART_SendData8(uint8_t Data);
uint8_t USCI3_UART_ReceiveData8(void);
void USCI3_UART_SendData9(uint16_t Data);
uint16_t USCI3_UART_ReceiveData9(void);
void USCI3_ITConfig(FunctionalState NewState, PriorityStatus Priority);
FlagStatus USCI3_GetFlagStatus(USCI3_Flag_TypeDef USCI3_FLAG);
void USCI3_ClearFlag(USCI3_Flag_TypeDef USCI3_FLAG);
void USCI3_TWI_SendAddr(uint8_t Addr, USCI3_TWI_RWType RW);

#endif

/******************* (C) COPYRIGHT 2022 SinOne Microelectronics *****END OF FILE****/