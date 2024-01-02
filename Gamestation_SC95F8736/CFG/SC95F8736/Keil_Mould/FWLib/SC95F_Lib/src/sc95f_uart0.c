//************************************************************
//  Copyright (c) 
//	�ļ�����: 			sc95f_uart0.c
//	����:					��ԪӦ���Ŷ�
//	ģ�鹦��: 			UART0�̼��⺯��C�ļ�
//  ����������:	2022��7��20��
// 	�汾: 				V1.10002
//  ˵��: 				���ļ���������SC95Fϵ��оƬ
//*************************************************************

#include "sc95f_uart0.h"

#if !defined (SC95R751)
/**************************************************
*��������:void UART0_DeInit(void)
*��������:UART0��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void UART0_DeInit(void)
{
  SCON = 0X00;
  SBUF = 0X00;
  PCON &= 0X7F;
  IE &= 0XEF;
  IP &= 0XEF;
}

/**************************************************
*��������:void UART0_Init(uint32_t Uart0Fsys, uint32_t BaudRate, UART0_Mode_Typedef Mode,
						   UART0_Clock_Typedef ClockMode, UART0_RX_Typedef RxMode)
*��������:UART0��ʼ�����ú���
*��ڲ���:
uint32_t:Uart0Fsys:ϵͳʱ��Ƶ��
uint32_t:BaudRate:������
UART0_Mode_Typedef:Mode:UART0����ģʽ
UART0_Clock_Typedef:ClockMode:������ʱ��Դ��TIMER1/TIMER2��
UART0_RX_Typedef:RxMode:��������ѡ��
*���ڲ���:void
**************************************************/
void UART0_Init(uint32_t Uart0Fsys, uint32_t BaudRate, UART0_Mode_Typedef Mode,
                UART0_Clock_Typedef ClockMode, UART0_RX_Typedef RxMode)
{
  SCON = SCON & 0X2F | Mode | RxMode; //����UART����ģʽ,���ý�������λ

  if (Mode == UART0_Mode_8B)
  {
    if (BaudRate == UART0_BaudRate_FsysDIV12)
    {
      SCON &= 0XDF;
    }
    else if (BaudRate == UART0_BaudRate_FsysDIV4)
    {
      SCON |= 0X20;
    }
  }
  else
  {
#if defined(SC95F8x2x) || defined(SC95F7x2x)
    TXINX = 0X02;
#endif
    TXCON = (TXCON & 0xCF) | ClockMode; //���ò�����ʱ��Դ

    if (ClockMode == UART0_CLOCK_TIMER1)
    {
      TH1 = (Uart0Fsys / BaudRate) / 256;
      TL1 = (Uart0Fsys / BaudRate) % 256;
      TR1 = 0;
    }
    else if (ClockMode == UART0_CLOCK_TIMER2)
    {
			TXINX = 0X02;
			RCAPXH = (Uart0Fsys / BaudRate) / 256;
      RCAPXL = (Uart0Fsys / BaudRate) % 256;
      TRX = 1;
    }
  }
}

/*****************************************************
*��������:void UART0_SendData8(uint8_t Data)
*��������:UART0����8λ����
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void UART0_SendData8(uint8_t Data)
{
  SBUF = Data;
}

/**************************************************
*��������:uint8_t UART0_ReceiveData8(void)
*��������:���SBUF�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:���յ�����
**************************************************/
uint8_t UART0_ReceiveData8(void)
{
  return SBUF;
}

/*****************************************************
*��������:void UART0_SendData9(uint16_t Data)
*��������:UART0����9λ����
*��ڲ���:
uint16_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void UART0_SendData9(uint16_t Data)
{
  uint8_t Data_9Bit;
  Data_9Bit = (Data >> 8);

  if (Data_9Bit)
  {
    SCON |= 0X08;
  }
  else
  {
    SCON &= 0XF7;
  }

  SBUF = (uint8_t)Data;
}

/**************************************************
*��������:uint16_t UART0_ReceiveData9(void)
*��������:���SBUF�е�ֵ���ھ�λ��ֵ
*��ڲ���:void
*���ڲ���:
uint16_t:SBUF�е�ֵ���ھ�λ��ֵ
**************************************************/
uint16_t UART0_ReceiveData9(void)
{
  uint16_t Data9;
  Data9 = SBUF + ((uint16_t)(SCON & 0X04) << 6);
  SCON &= 0XFB;
  return Data9;
}

/*****************************************************
*��������:void UART0_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:UART0�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void UART0_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  if (NewState == DISABLE)
  {
    EUART = 0;
  }
  else
  {
    EUART = 1;
  }

  //�����ж����ȼ�
  if (Priority == LOW)
  {
    IPUART = 0;
  }
  else
  {
    IPUART = 1;
  }
}
#endif

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/