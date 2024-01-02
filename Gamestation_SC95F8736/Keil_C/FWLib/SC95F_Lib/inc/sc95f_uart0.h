//************************************************************
//  Copyright (c) 
//	�ļ�����: 			sc95f_uart0.h
//	����:					��ԪӦ���Ŷ�
//	ģ�鹦��: 			UART0�̼��⺯��H�ļ�
//  ����������:	2022��7��20��
// 	�汾: 				V1.10002
//  ˵��: 
//*************************************************************
#ifndef _sc95f_UART0_H_
#define _sc95f_UART0_H_

#include "sc95f.h"

#if !defined (SC95R751)

#define UART0_BaudRate_FsysDIV12 0X00 //��ģʽ0���ã����ж˿���ϵͳʱ�ӵ�1/12������
#define UART0_BaudRate_FsysDIV4 0X01  //��ģʽ0���ã����ж˿���ϵͳʱ�ӵ�1/4������

typedef enum
{
  UART0_CLOCK_TIMER1 = (uint8_t)0X00, //TIMER1�������ʷ�����
  UART0_CLOCK_TIMER2 = (uint8_t)0X30  //TIMER2�������ʷ�����
} UART0_Clock_Typedef;

typedef enum
{
  UART0_Mode_8B = 0X00,  //UART����ģʽ:8λ��˫��
  UART0_Mode_10B = 0X40, //UART����ģʽ:10λȫ˫��
  UART0_Mode_11B = 0XC0  //UART����ģʽ:11λȫ˫��
} UART0_Mode_Typedef;

typedef enum
{
  UART0_RX_ENABLE = 0x10, //�����������
  UART0_RX_DISABLE = 0x00 //�������������
} UART0_RX_Typedef;

typedef enum
{
  UART0_FLAG_RI = 0X01, //�����жϱ�־λRI
  UART0_FLAG_TI = 0X02  //�����жϱ�־λTI
} UART0_Flag_Typedef;

/*******************************�꺯��*******************************/
/*****************************************************
*��������:FlagStatus UART0_GetFlagStatus(UART0_Flag_Typedef UART0_Flag)
*��������:���UART0�жϱ�־״̬
*��ڲ���:
UART0_GetFlagStatus:UART0_Flag:�жϱ�־λѡ��
*���ڲ���:
FlagStatus:UART0�жϱ�־λ����״̬
*****************************************************/
#define UART0_GetFlagStatus(UART0_Flag) ((UART0_Flag == UART0_FLAG_TI) ? (TI):(RI))

/*****************************************************
*��������:void UART0_ClearFlag(UART0_Flag_Typedef UART0_Flag)
*��������:���UART0�жϱ�־״̬
*��ڲ���:
UART0_Flag_Typedef;UART0_Flag:�жϱ�־λѡ��
*���ڲ���:void
*****************************************************/
#define UART0_ClearFlag(UART0_Flag) CLEAR_BIT(SCON,UART0_Flag)

void UART0_DeInit(void);
void UART0_Init(uint32_t Uart0Fsys, uint32_t BaudRate, UART0_Mode_Typedef Mode,
                UART0_Clock_Typedef ClockMode, UART0_RX_Typedef RxMode);
void UART0_SendData8(uint8_t Data);
uint8_t UART0_ReceiveData8(void);
void UART0_SendData9(uint16_t Data);
uint16_t UART0_ReceiveData9(void);
void UART0_ITConfig(FunctionalState NewState, PriorityStatus Priority);

#endif

#endif

/******************* (C) COPYRIGHT 2018 SinOne Microelectronics *****END OF FILE****/
