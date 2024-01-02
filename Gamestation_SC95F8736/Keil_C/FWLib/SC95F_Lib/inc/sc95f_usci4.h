//************************************************************
//  Copyright (c) 
//	�ļ�����	: sc95f_USCI4.h
//	����		:
//	ģ�鹦��	: USCI4�̼��⺯��ͷ�ļ�
//  ����������: 2021/07/14
// 	�汾		: V1.0002
//  ˵��    :���ļ���������SC95Fϵ��оƬ
//*************************************************************

#ifndef _sc95f_USCI4_H_
#define _sc95f_USCI4_H_

#include "sc95f.h"

#define USCI4_UART_BaudRate_FsysDIV12 0X00 //��ģʽ0���ã����ж˿���ϵͳʱ�ӵ�1/12������
#define USCI4_UART_BaudRate_FsysDIV4 0X01  //��ģʽ0���ã����ж˿���ϵͳʱ�ӵ�1/4������

typedef enum
{
  USCI4_Mode_SPI = (uint8_t)0x01, //SPI
  USCI4_Mode_TWI = (uint8_t)0x02, //TWI
  USCI4_Mode_UART = (uint8_t)0x03 //UART
} USCI4_CommunicationMode_TypeDef;

typedef enum
{
  USCI4_SPI_FIRSTBIT_MSB = (uint8_t)0x00, //MSB���ȷ���
  USCI4_SPI_FIRSTBIT_LSB = (uint8_t)0x04  //LSB���ȷ���
} USCI4_SPI_FirstBit_TypeDef;

typedef enum
{
  USCI4_SPI_BAUDRATEPRESCALER_1 = (uint8_t)0x00,  //SPIʱ������Ϊϵͳʱ�ӳ���1
  USCI4_SPI_BAUDRATEPRESCALER_2 = (uint8_t)0x01,  //SPIʱ������Ϊϵͳʱ�ӳ���2
  USCI4_SPI_BAUDRATEPRESCALER_4 = (uint8_t)0x02,  //SPIʱ������Ϊϵͳʱ�ӳ���4
  USCI4_SPI_BAUDRATEPRESCALER_8 = (uint8_t)0x03,  //SPIʱ������Ϊϵͳʱ�ӳ���8
  USCI4_SPI_BAUDRATEPRESCALER_16 = (uint8_t)0x04, //SPIʱ������Ϊϵͳʱ�ӳ���16
  USCI4_SPI_BAUDRATEPRESCALER_32 = (uint8_t)0x05, //SPIʱ������Ϊϵͳʱ�ӳ���32
  USCI4_SPI_BAUDRATEPRESCALER_64 = (uint8_t)0x06, //SPIʱ������Ϊϵͳʱ�ӳ���64
  USCI4_SPI_BAUDRATEPRESCALER_128 = (uint8_t)0x07 //SPIʱ������Ϊϵͳʱ�ӳ���128
} USCI4_SPI_BaudRatePrescaler_TypeDef;

typedef enum
{
  USCI4_SPI_MODE_MASTER = (uint8_t)0x20, //SPIΪ���豸
  USCI4_SPI_MODE_SLAVE = (uint8_t)0x00   //SPIΪ���豸
} USCI4_SPI_Mode_TypeDef;

typedef enum
{
  USCI4_SPI_CLOCKPOLARITY_LOW = (uint8_t)0x00, //SCK�ڿ���״̬��Ϊ�͵�ƽ
  USCI4_SPI_CLOCKPOLARITY_HIGH = (uint8_t)0x10 //SCK�ڿ���״̬��Ϊ�ߵ�ƽ
} USCI4_SPI_ClockPolarity_TypeDef;

typedef enum
{
  USCI4_SPI_CLOCKPHASE_1EDGE = (uint8_t)0x00, //SCK�ĵ�һ�زɼ�����
  USCI4_SPI_CLOCKPHASE_2EDGE = (uint8_t)0x08  //SCK�ĵڶ��زɼ�����
} USCI4_SPI_ClockPhase_TypeDef;

typedef enum
{
  USCI4_SPI_TXE_DISINT = (uint8_t)0x00, //TBIEΪ0ʱ���������ж�
  USCI4_SPI_TXE_ENINT = (uint8_t)0x01   //TBIEΪ1ʱ�������ж�
} USCI4_SPI_TXE_INT_TypeDef;

typedef enum
{
  USCI4_SPI_DATA8 = (uint8_t)0x00, //SPI 8λ����ģʽ
  USCI4_SPI_DATA16 = (uint8_t)0x01 //SPI 16λ����ģʽ
} USCI4_TransmissionMode_TypeDef;

typedef enum
{
  USCI4_TWI_1024 = (uint8_t)0x00, //TWIͨ������ Fhrc/1024
  USCI4_TWI_512 = (uint8_t)0x01,  //TWIͨ������ Fhrc/512
  USCI4_TWI_256 = (uint8_t)0x02,  //TWIͨ������ Fhrc/256
  USCI4_TWI_128 = (uint8_t)0x03,  //TWIͨ������ Fhrc/128
  USCI4_TWI_64 = (uint8_t)0x04,   //TWIͨ������ Fhrc/64
  USCI4_TWI_32 = (uint8_t)0x05,   //TWIͨ������ Fhrc/32
  USCI4_TWI_16 = (uint8_t)0x06,   //TWIͨ������ Fhrc/16
} USCI4_TWI_MasterCommunicationRate_TypeDef;

typedef enum
{
  USCI4_TWI_SlaveBusy = 0x00, //��Ϊ�ӻ�
  USCI4_TWI_SlaveReceivedaAddress = 0x01,
  USCI4_TWI_SlaveReceivedaData = 0x02,
  USCI4_TWI_SlaveSendData = 0x03,
  USCI4_TWI_SlaveReceivedaUACK = 0x04,
  USCI4_TWI_SlaveDisableACK = 0x05,
  USCI4_TWI_SlaveAddressError = 0x06,
  USCI4_TWI_MasterBusy = 0x00, //��Ϊ����
  USCI4_TWI_MasterSendAddress = 0x01,
  USCI4_TWI_MasterSendData = 0x02,
  USCI4_TWI_MasterReceivedaData = 0x03,
  USCI4_TWI_MasterReceivedaUACK = 0x04,
} USCI4_TWIState_TypeDef;

typedef enum
{
  USCI4_UART_Mode_8B = 0X00,  //UART����Ϊ8λģʽ
  USCI4_UART_Mode_10B = 0X40, //UART����Ϊ10λģʽ
  USCI4_UART_Mode_11B = 0X80  //UART����Ϊ11λģʽ
} USCI4_UART_Mode_TypeDef;

typedef enum
{
  USCI4_UART_RX_ENABLE = 0X10, //UART�������
  USCI4_UART_RX_DISABLE = 0X00 //UART��ֹ����
} USCI4_UART_RX_TypeDef;

typedef enum
{
  USCI4_SPI_FLAG_SPIF = (uint8_t)0x80, //SPI���ݴ��ͱ�־λSPIF
  USCI4_SPI_FLAG_WCOL = (uint8_t)0x50, //SPIд���ͻ��־λWCOL
  USCI4_SPI_FLAG_TXE = (uint8_t)0x08,  //SPI���ͻ������ձ�־TXE
  USCI4_TWI_FLAG_TWIF = (uint8_t)0x40, //TWI�жϱ�־λTWIF
  USCI4_TWI_FLAG_GCA = (uint8_t)0x10,  //TWIͨ�õ�ַ��Ӧ��־λGCA
  USCI4_TWI_FLAG_MSTR = (uint8_t)0x20, //TWI���ӱ�־λMSTR
  USCI4_TWI_FLAG_TXRXnE = (uint8_t)0x80,
  USCI4_UART_FLAG_RI = (uint8_t)0x01, //UART�����жϱ�־λRI
  USCI4_UART_FLAG_TI = (uint8_t)0x02, //UART�����жϱ�־λTI
} USCI4_Flag_TypeDef;

typedef enum
{
  USCI4_TWI_Write = 0x00, //д����
  USCI4_TWI_Read = 0x01,  //������
} USCI4_TWI_RWType;

void USCI4_DeInit(void);
void USCI4_SPI_Init(USCI4_SPI_FirstBit_TypeDef FirstBit,
                    USCI4_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, USCI4_SPI_Mode_TypeDef Mode,
                    USCI4_SPI_ClockPolarity_TypeDef ClockPolarity, USCI4_SPI_ClockPhase_TypeDef ClockPhase,
                    USCI4_SPI_TXE_INT_TypeDef SPI_TXE_INT, USCI4_TransmissionMode_TypeDef TransmissionMode);
void USCI4_TransmissionMode(USCI4_TransmissionMode_TypeDef TransmissionMode);
void USCI4_SPI_Cmd(FunctionalState NewState);
void USCI4_SPI_SendData_8(uint8_t Data);
uint8_t USCI4_SPI_ReceiveData_8(void);
void USCI4_SPI_SendData_16(uint16_t Data);
uint16_t USCI4_SPI_ReceiveData_16(void);
void USCI4_TWI_Slave_Init(uint8_t TWI_Address);
void USCI4_TWI_MasterCommunicationRate(USCI4_TWI_MasterCommunicationRate_TypeDef
                                           TWI_MasterCommunicationRate);
void USCI4_TWI_Start(void);
void USCI4_TWI_MasterModeStop(void);
void USCI4_TWI_SlaveClockExtension(FunctionalState NewState);
void USCI4_TWI_AcknowledgeConfig(FunctionalState NewState);
void USCI4_TWI_GeneralCallCmd(FunctionalState NewState);
FlagStatus USCI4_GetTWIStatus(USCI4_TWIState_TypeDef USCI4_TWIState);
void USCI4_TWI_Cmd(FunctionalState NewState);
void USCI4_TWI_SendData(uint8_t Data);
uint8_t USCI4_TWI_ReceiveData(void);
void USCI4_UART_Init(uint32_t UART1Fsys, uint32_t BaudRate, USCI4_UART_Mode_TypeDef Mode,
                     USCI4_UART_RX_TypeDef RxMode);
void USCI4_UART_SendData8(uint8_t Data);
uint8_t USCI4_UART_ReceiveData8(void);
void USCI4_UART_SendData9(uint16_t Data);
uint16_t USCI4_UART_ReceiveData9(void);
void USCI4_ITConfig(FunctionalState NewState, PriorityStatus Priority);
FlagStatus USCI4_GetFlagStatus(USCI4_Flag_TypeDef USCI4_FLAG);
void USCI4_ClearFlag(USCI4_Flag_TypeDef USCI4_FLAG);
void USCI4_TWI_SendAddr(uint8_t Addr, USCI4_TWI_RWType RW);

#endif

/******************* (C) COPYRIGHT 2022 SinOne Microelectronics *****END OF FILE****/