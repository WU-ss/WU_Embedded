//************************************************************
//  Copyright (c) 
//	文件名称: 		sc95f_gpio.c
//	作者:
//	模块功能:			GPIO固件库函数头文件
//  最后更正日期:	2022年7月22日
// 	版本: 				V1.10006
//  说明:					该文件仅适用于SC95F系列芯片
//*************************************************************

#include "sc95f_gpio.h"

/**************************************************
*函数名称:void GPIO_DeInit(void)
*函数功能:GPIO相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
**************************************************/
void GPIO_DeInit(void)
{
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx) || defined(SC95F8x3x) || defined(SC95F7x3x)\
		|| defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751)\
		|| defined (SC95F7610B)
  P0CON = 0x00;
  P1CON = 0x00;
  P2CON = 0x00;
  P3CON = 0x00;
  P4CON = 0x00;
  P5CON = 0x00;
  P0PH = 0x00;
  P1PH = 0x00;
  P2PH = 0x00;
  P3PH = 0x00;
  P4PH = 0x00;
  P5PH = 0x00;
  P0 = P1 = P2 = P3 = P4 = P5 = 0;
#endif
#if defined(SC95F7619B)
  P0CON = 0x00;
  P1CON = 0x00;
  P2CON = 0x00;
  P4CON = 0x00;
  P5CON = 0x00;
  P0PH = 0x00;
  P1PH = 0x00;
  P2PH = 0x00;
  P4PH = 0x00;
  P5PH = 0x00;
  P0 = P1 = P2 = P4 = P5 = 0;
#endif
	
#if defined(SC95F8x2x) || defined(SC95F7x2x)
  P0CON = 0x00;
  P1CON = 0x00;
  P2CON = 0x00;
  P5CON = 0x00;
  P0PH = 0x00;
  P1PH = 0x00;
  P2PH = 0x00;
  P5PH = 0x00;
  P0 = P1 = P2 = P5 = 0;
#endif
}

/**************************************************
*函数名称:void GPIO_Init(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef PortPins, GPIO_Mode_TypeDef GPIO_Mode)
*函数功能:GPIO口配置初始化
*入口参数:
GPIO_TypeDef:GPIOx:待操作的GPIO口
GPIO_Pin_TypeDef:PortPins:GPIO管脚Pxy（uint8_t作为入参，方便进行位或操作）
GPIO_Mode_TypeDef:GPIO_Mode:GPIO口模式（高阻输入、上拉输入、推挽输出）
*出口参数:void
**************************************************/
void GPIO_Init(GPIO_TypeDef GPIOx, uint8_t PortPins, GPIO_Mode_TypeDef GPIO_Mode)
{
	/* 选择需要操作的GPIO */
  switch(GPIOx)
  {
		case GPIO0:
		{
			switch(GPIO_Mode)
			{
				/* 配置IO为高阻输入模式 */
				case GPIO_MODE_IN_HI:			
					P0CON &= ~PortPins;
					P0PH &= ~PortPins;
				break;
				/* 配置IO为上拉输入模式 */
				case GPIO_MODE_IN_PU:
					P0CON &= ~PortPins;
					P0PH |= PortPins;
				break;
				/* 配置IO为推挽输出模式 */
				case GPIO_MODE_OUT_PP:
					P0CON |= PortPins;
				break;
				default: 
				break;
			}
		}
		break;
		case GPIO1:
		{
			switch(GPIO_Mode)
			{
				/* 配置IO为高阻输入模式 */
				case GPIO_MODE_IN_HI:
					P1CON &= ~PortPins;
					P1PH &= ~PortPins;
				break;
				/* 配置IO为上拉输入模式 */
				case GPIO_MODE_IN_PU:
					P1CON &= ~PortPins;
					P1PH |= PortPins;
				break;
				/* 配置IO为推挽输出模式 */
				case GPIO_MODE_OUT_PP:
					P1CON |= PortPins;
				break;
				default: 
				break;
			}
		}
		break;
		case GPIO2:
		{
			switch(GPIO_Mode)
			{
				/* 配置IO为高阻输入模式 */
				case GPIO_MODE_IN_HI:
					P2CON &= ~PortPins;
					P2PH &= ~PortPins;
				break;
				/* 配置IO为上拉输入模式 */
				case GPIO_MODE_IN_PU:
					P2CON &= ~PortPins;
					P2PH |= PortPins;
				break;
				/* 配置IO为推挽输出模式 */
				case GPIO_MODE_OUT_PP:
					P2CON |= PortPins;
				break;
				default: 
				break;
			}
		}
		break;
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB)
		#if !defined(SC95F7619B)
		case GPIO3:
		{
			switch(GPIO_Mode)
			{
				/* 配置IO为高阻输入模式 */
				case GPIO_MODE_IN_HI:
					P3CON &= ~PortPins;
					P3PH &= ~PortPins;
				break;
				/* 配置IO为上拉输入模式 */
				case GPIO_MODE_IN_PU:
					P3CON &= ~PortPins;
					P3PH |= PortPins;
				break;
				/* 配置IO为推挽输出模式 */
				case GPIO_MODE_OUT_PP:
					P3CON |= PortPins;
				break;
				default: 
				break;
			}
		}
		break;
		#endif
		case GPIO4:
		{
			switch(GPIO_Mode)
			{
				/* 配置IO为高阻输入模式 */
				case GPIO_MODE_IN_HI:
					P4CON &= ~PortPins;
					P4PH &= ~PortPins;
				break;
				/* 配置IO为上拉输入模式 */
				case GPIO_MODE_IN_PU:
					P4CON &= ~PortPins;
					P4PH |= PortPins;
				break;
				/* 配置IO为推挽输出模式 */
				case GPIO_MODE_OUT_PP:
					P4CON |= PortPins;
				break;
				default: 
				break;
			}
		}
		break;
#endif
		case GPIO5:
		{
			switch(GPIO_Mode)
			{
				/* 配置IO为高阻输入模式 */
				case GPIO_MODE_IN_HI:
					P5CON &= ~PortPins;
					P5PH &= ~PortPins;
				break;
				/* 配置IO为上拉输入模式 */
				case GPIO_MODE_IN_PU:
					P5CON &= ~PortPins;
					P5PH |= PortPins;
				break;
				/* 配置IO为推挽输出模式 */
				case GPIO_MODE_OUT_PP:
					P5CON |= PortPins;
				break;
				default: 
				break;
			}
		}
		break;
		default: 
		break;
  }
}

/**************************************************
*函数名称:void GPIO_Write(GPIO_TypeDef GPIOx, uint8_t PortVal)
*函数功能:GPIO口赋值
*入口参数:
GPIO_TypeDef:GPIOx:待操作的GPIO口
uint8_t:PortVal:GPIO口的值
*出口参数:void
**************************************************/
void GPIO_Write(GPIO_TypeDef GPIOx, uint8_t PortVal)
{
	/* 选择需要操作的GPIO */
	switch(GPIOx)
	{
		case GPIO0:
			P0 = PortVal;
		break;
		case GPIO1:
			P1 = PortVal;
		break;
		case GPIO2:
			P2 = PortVal;
		break;
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB)
		#if !defined(SC95F7619B)
		case GPIO3:
			P3 = PortVal;
		break;
		#endif
		case GPIO4:
			P4 = PortVal;
		break;
#endif
		case GPIO5:
			P5 = PortVal;
		break;
		default: 
		break;
	}
}

/**************************************************
*函数名称:void GPIO_WriteHigh(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef PortPins)
*函数功能:GPIO口管脚Pxy置位
*入口参数:
GPIO_TypeDef:GPIOx:待操作的GPIO口
GPIO_Pin_TypeDef:PortPins:选择GPIO口管脚Pxy（uint8_t作为入参，方便进行位或操作）
*出口参数:void
**************************************************/
void GPIO_WriteHigh(GPIO_TypeDef GPIOx, uint8_t PortPins)
{
	/* 选择需要操作的GPIO */
		switch(GPIOx)
	{
		case GPIO0:
			P0 |= PortPins;
		break;
		case GPIO1:
			P1 |= PortPins;
		break;
		case GPIO2:
			P2 |= PortPins;
		break;
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB)
		#if !defined(SC95F7619B)
		case GPIO3:
			P3 |= PortPins;
		break;
		#endif
		case GPIO4:
			P4 |= PortPins;
		break;
#endif
		case GPIO5:
			P5 |= PortPins;
		break;
		default: 
		break;
	}
}

/**************************************************
*函数名称:void GPIO_WriteLow(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef PortPins)
*函数功能:GPIO口管脚Pxy复位
*入口参数:
GPIO_TypeDef:GPIOx:待操作的GPIO口
GPIO_Pin_TypeDef:PortPins:选择GPIO口管脚Pxy（uint8_t作为入参，方便进行位或操作）
*出口参数:void
**************************************************/
void GPIO_WriteLow(GPIO_TypeDef GPIOx, uint8_t PortPins)
{
	/* 选择需要操作的GPIO */
		switch(GPIOx)
	{
		case GPIO0:
			P0 &= ~PortPins;
		break;
		case GPIO1:
			P1 &= ~PortPins;
		break;
		case GPIO2:
			P2 &= ~PortPins;
		break;
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB)
		#if !defined(SC95F7619B)
		case GPIO3:
			P3 &= ~PortPins;
		break;
		#endif
		case GPIO4:
			P4 &= ~PortPins;
		break;
#endif
		case GPIO5:
			P5 &= ~PortPins;
		break;
		default: 
		break;
	}
}

/**************************************************
*函数名称:uint8_t GPIO_ReadPort(GPIO_TypeDef GPIOx)
*函数功能:读GPIO口Px的值
*入口参数:
GPIO_TypeDef:GPIOx:待操作的GPIO口
*出口参数:
uint8_t:返回Px的值
**************************************************/
uint8_t GPIO_ReadPort(GPIO_TypeDef GPIOx)
{
	/* 选择需要操作的GPIO */
	switch(GPIOx)
	{
		case GPIO0:
			return P0;
		case GPIO1:
			return P1;
		case GPIO2:
			return P2;
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB)
		#if !defined(SC95F7619B)
		case GPIO3:
			return P3;
		#endif
		case GPIO4:
			return P4;
#endif
		case GPIO5:
			return P5;
		default: 
			return 0;
	}
}

/**************************************************
*函数名称:BitStatus GPIO_ReadPin(GPIO_TypeDef GPIOx, uint8_t PortPins)
*函数功能:读GPIO口管脚Pxy的值
*入口参数:
GPIO_TypeDef:GPIOx:待操作的GPIO口
GPIO_Pin_TypeDef:PortPins:选择GPIO口管脚Pxy（uint8_t作为入参，方便进行位或操作）
*出口参数:
BitStatus:返回Pxy的值
**************************************************/
BitStatus GPIO_ReadPin(GPIO_TypeDef GPIOx, uint8_t PortPins)
{
	/* 选择需要操作的GPIO */
	switch(GPIOx)
	{
		case GPIO0:
			return (P0 & PortPins);
		case GPIO1:
			return (P1 & PortPins);
		case GPIO2:
			return (P2 & PortPins);
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
		|| defined (SC95F8x1xB) || defined (SC95F7x1xB)
		#if !defined(SC95F7619B)
		case GPIO3:
			return (P3 & PortPins);
		#endif
		case GPIO4:
			return (P4 & PortPins);
#endif
		case GPIO5:
			return (P5 & PortPins);
		default: 
			return 0;
	}
}

/**************************************************
*函数名称:void GPIO_IOH_Config(GPIO_TypeDef GPIOx, uint8_t PortPins,GPIO_IOH_Grade_TypeDef GPIO_IOH_Grade)
*函数功能:设置GPIO口管脚IOH输出能力
*入口参数:
GPIO_TypeDef:GPIOx:待操作的GPIO口
GPIO_Pin_TypeDef:PortPins:选择GPIO口管脚Pxy
GPIO_IOH_Grade_TypeDef:GPIO_IOH_Grade:选择IOH的输出等级
*出口参数:void
**************************************************/
void GPIO_IOH_Config(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef PortPins, GPIO_IOH_Grade_TypeDef GPIO_IOH_Grade)
{
	/* 选择需要操作的GPIO */
  switch (GPIOx)
  {
  case GPIO0:
    if (PortPins == GPIO_PIN_LNIB)
    {
      IOHCON0 &= 0xFC;
      IOHCON0 |= GPIO_IOH_Grade;
    }
    else if (PortPins == GPIO_PIN_HNIB)
    {
      IOHCON0 &= 0xF3;
      IOHCON0 |= GPIO_IOH_Grade << 2;
    }
    break;
  case GPIO1:
    if (PortPins == GPIO_PIN_LNIB)
    {
      IOHCON0 &= 0xCF;
      IOHCON0 |= GPIO_IOH_Grade << 4;
    }
    else if (PortPins == GPIO_PIN_HNIB)
    {
      IOHCON0 &= 0x3F;
      IOHCON0 |= GPIO_IOH_Grade << 6;
    }
    break;
  case GPIO2:
    if (PortPins == GPIO_PIN_LNIB)
    {
      IOHCON1 &= 0xFC;
      IOHCON1 |= GPIO_IOH_Grade;
    }
    else if (PortPins == GPIO_PIN_HNIB)
    {
      IOHCON1 &= 0xF3;
      IOHCON1 |= GPIO_IOH_Grade << 2;
    }
    break;
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx) ||defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)
  #if !defined(SC95F7619B)
	case GPIO3:
    if (PortPins == GPIO_PIN_LNIB)
    {
      IOHCON1 &= 0xCF;
      IOHCON1 |= GPIO_IOH_Grade << 4;
    }
    break;
		#endif
#elif defined(SC95F8x2x) || defined(SC95F7x2x)
  case GPIO5:
    if (PortPins == GPIO_PIN_LNIB)
    {
      IOHCON1 &= 0xCF;
      IOHCON1 |= GPIO_IOH_Grade << 4;
    }
    break;
#endif
  default:
    break;
  }
}

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/