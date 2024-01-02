//************************************************************
//  Copyright (c) 
//	文件名称: 		sc95f_gpio.h
//	作者:
//	模块功能:			GPIO固件库函数头文件
//  最后更正日期:	2022年7月22日
// 	版本: 				V1.10004
//  说明:					该文件仅适用于SC95F系列芯片
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
  GPIO_MODE_IN_HI = (uint8_t)0x00, //高阻输入模式
  GPIO_MODE_IN_PU = (uint8_t)0x01, //带上拉的输入模式
  GPIO_MODE_OUT_PP = (uint8_t)0x02 //强推挽输出模式
} GPIO_Mode_TypeDef;

typedef enum
{
  GPIO_PIN_0 = ((uint8_t)0x01),    //IO管脚Px0
  GPIO_PIN_1 = ((uint8_t)0x02),    //IO管脚Px1
  GPIO_PIN_2 = ((uint8_t)0x04),    //IO管脚Px2
  GPIO_PIN_3 = ((uint8_t)0x08),    //IO管脚Px3
  GPIO_PIN_4 = ((uint8_t)0x10),    //IO管脚Px4
  GPIO_PIN_5 = ((uint8_t)0x20),    //IO管脚Px5
  GPIO_PIN_6 = ((uint8_t)0x40),    //IO管脚Px6
  GPIO_PIN_7 = ((uint8_t)0x80),    //IO管脚Px7
  GPIO_PIN_LNIB = ((uint8_t)0x0F), //IO管脚Px0~3
  GPIO_PIN_HNIB = ((uint8_t)0xF0), //IO管脚Px4~7
  GPIO_PIN_ALL = ((uint8_t)0xFF)   //IO管脚Px0~7
} GPIO_Pin_TypeDef;

typedef enum
{
  IOH_Grade_0 = ((uint8_t)0x00), //IOH等级0
  IOH_Grade_1 = ((uint8_t)0x01), //IOH等级1
  IOH_Grade_2 = ((uint8_t)0x02), //IOH等级2
  IOH_Grade_3 = ((uint8_t)0x03), //IOH等级3
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
