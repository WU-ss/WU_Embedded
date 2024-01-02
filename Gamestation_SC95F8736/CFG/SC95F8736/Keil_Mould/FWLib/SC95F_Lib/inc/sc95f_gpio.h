//************************************************************
//  Copyright (c) 
//	�ļ�����: 		sc95f_gpio.h
//	����:
//	ģ�鹦��:			GPIO�̼��⺯��ͷ�ļ�
//  ����������:	2022��7��22��
// 	�汾: 				V1.10004
//  ˵��:					���ļ���������SC95Fϵ��оƬ
//*************************************************************

#ifndef _sc95f_GPIO_H_
#define _sc95f_GPIO_H_

#include "sc95f.h"

#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx) || defined(SC95F8x3x) || defined(SC95F7x3x)\
		|| defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751)\
		|| defined (SC95F7610B)
typedef enum
{
  GPIO0 = (uint8_t)0x00, //P0
  GPIO1 = (uint8_t)0x01, //P1
  GPIO2 = (uint8_t)0x02, //P2
  GPIO3 = (uint8_t)0x03, //P3
  GPIO4 = (uint8_t)0x04, //P4
  GPIO5 = (uint8_t)0x05  //P5
} GPIO_TypeDef;
#elif defined (SC95F7619B)
typedef enum
{
  GPIO0 = (uint8_t)0x00, //P0
  GPIO1 = (uint8_t)0x01, //P1
  GPIO2 = (uint8_t)0x02, //P2
  GPIO4 = (uint8_t)0x04, //P4
  GPIO5 = (uint8_t)0x05  //P5
} GPIO_TypeDef;
#else
typedef enum
{
  GPIO0 = (uint8_t)0x00, //P0
  GPIO1 = (uint8_t)0x01, //P1
  GPIO2 = (uint8_t)0x02, //P2
  GPIO5 = (uint8_t)0x05  //P5
} GPIO_TypeDef;
#endif

typedef enum
{
  GPIO_MODE_IN_HI = (uint8_t)0x00, //��������ģʽ
  GPIO_MODE_IN_PU = (uint8_t)0x01, //������������ģʽ
  GPIO_MODE_OUT_PP = (uint8_t)0x02 //ǿ�������ģʽ
} GPIO_Mode_TypeDef;

typedef enum
{
  GPIO_PIN_0 = ((uint8_t)0x01),    //IO�ܽ�Px0
  GPIO_PIN_1 = ((uint8_t)0x02),    //IO�ܽ�Px1
  GPIO_PIN_2 = ((uint8_t)0x04),    //IO�ܽ�Px2
  GPIO_PIN_3 = ((uint8_t)0x08),    //IO�ܽ�Px3
  GPIO_PIN_4 = ((uint8_t)0x10),    //IO�ܽ�Px4
  GPIO_PIN_5 = ((uint8_t)0x20),    //IO�ܽ�Px5
  GPIO_PIN_6 = ((uint8_t)0x40),    //IO�ܽ�Px6
  GPIO_PIN_7 = ((uint8_t)0x80),    //IO�ܽ�Px7
  GPIO_PIN_LNIB = ((uint8_t)0x0F), //IO�ܽ�Px0~3
  GPIO_PIN_HNIB = ((uint8_t)0xF0), //IO�ܽ�Px4~7
  GPIO_PIN_ALL = ((uint8_t)0xFF)   //IO�ܽ�Px0~7
} GPIO_Pin_TypeDef;

typedef enum
{
  IOH_Grade_0 = ((uint8_t)0x00), //IOH�ȼ�0
  IOH_Grade_1 = ((uint8_t)0x01), //IOH�ȼ�1
  IOH_Grade_2 = ((uint8_t)0x02), //IOH�ȼ�2
  IOH_Grade_3 = ((uint8_t)0x03), //IOH�ȼ�3
} GPIO_IOH_Grade_TypeDef;

void GPIO_IOH_Config(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef PortPins, GPIO_IOH_Grade_TypeDef GPIO_IOH_Grade);

void GPIO_DeInit(void);
void GPIO_Init(GPIO_TypeDef GPIOx, uint8_t PortPins, GPIO_Mode_TypeDef GPIO_Mode);
void GPIO_Write(GPIO_TypeDef GPIOx, uint8_t PortVal);
void GPIO_WriteHigh(GPIO_TypeDef GPIOx, uint8_t PortPins);
void GPIO_WriteLow(GPIO_TypeDef GPIOx, uint8_t PortPins);

uint8_t GPIO_ReadPort(GPIO_TypeDef GPIOx);
uint8_t GPIO_ReadPin(GPIO_TypeDef GPIOx, uint8_t PortPins);

#endif

/******************* (C) COPYRIGHT 2022 SinOne Microelectronics *****END OF FILE****/
