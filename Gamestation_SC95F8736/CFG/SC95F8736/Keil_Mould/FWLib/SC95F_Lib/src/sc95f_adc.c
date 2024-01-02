//************************************************************
//  Copyright (c) 
//	文件名称: 			sc95f_adc.c
//	作者:					赛元应用团队
//	模块功能: 			BTM固件库函数C文件
//  最后更正日期: 	2022年3月23日
// 	版本: 					V1.10001
//  说明: 
//*************************************************************
#include "sc95f_adc.h"

/**************************************************
*函数名称:void ADC_DeInit(void)
*函数功能:ADC相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
**************************************************/
void ADC_DeInit(void)
{
  ADCCON = 0x00;
  ADCCFG0 = 0X00;
  ADCCFG1 = 0X00;
  ADCCFG2 = 0X00;
  ADCVL = 0X00;
  ADCVH = 0X00;
  EADC = 0;
  IPADC = 0;
}

/**************************************************
*函数名称:void ADC_Init(ADC_PresSel_TypeDef ADC_PrescalerSelection,ADC_Cycle_TypeDef ADC_Cycle)
*函数功能:ADC初始化配置函数
*入口参数:
ADC_PresSel_TypeDef:ADC_PrescalerSelection:ADC预分频选择
ADC_Cycle_TypeDef:ADC_Cycle:采样时间选择
*出口参数:void
**************************************************/
void ADC_Init(ADC_PresSel_TypeDef ADC_PrescalerSelection, ADC_Cycle_TypeDef ADC_Cycle)
{
	/* 配置ADC采样时钟分频 */
  ADCCFG2 = ADC_PrescalerSelection;
	/* 该入参在95F系列无效 */
  ADC_Cycle = 0x00; 
}

/**************************************************
*函数名称:void ADC_ChannelConfig(ADC_Channel_TypeDef ADC_Channel, FunctionalState NewState)
*函数功能:ADC输入口配置函数
*入口参数:
ADC_Channel_TypeDef:ADC_Channel:ADC输入口选择
FunctionalState:NewState:ADCx使能/关闭选择
*出口参数:void
**************************************************/
void ADC_ChannelConfig(ADC_Channel_TypeDef ADC_Channel, FunctionalState NewState)
{
  uint16_t tmpreg;

	/* ADC采样通道选择外部通道，将对应的ADC输入口设置为模拟输入模式 */
  if (ADC_Channel < ADC_CHANNEL_VDD_D4)
  {
		tmpreg = (0x0001 << ADC_Channel);			//通过移位得到ADCCFG寄存器·配置值
    if (NewState == DISABLE)
    {
			/* ADC输入口退出模拟输入模式 */
      ADCCFG0 &= (~(uint8_t)tmpreg);
      ADCCFG1 &= (~(uint8_t)(tmpreg >> 8));
    }
    else
    {
			/* ADC输入口设置为模拟输入模式 */
      ADCCFG0 |= ((uint8_t)tmpreg);
      ADCCFG1 |= ((uint8_t)(tmpreg >> 8));
    }
  }
	
	/* 配置ADC采样时钟分频 */
  ADCCON = (ADCCON & 0XE0) | ADC_Channel;
}

/**************************************************
*函数名称:void ADC_EAINConfig(ADC_EAIN_TypeDef ADC_Channel, FunctionalState NewState)
*函数功能:将对应的ADC输入口设置为模拟输入模式
*入口参数:
ADC_EAIN_TypeDef:ADC_EAIN_Select:选择需要设置的ADC口（uint16_t作为入参，方便进行位或操作）
FunctionalState:NewState:ADC通道使能/关闭选择
*出口参数:void
**************************************************/
void ADC_EAINConfig(uint16_t ADC_EAIN_Select, FunctionalState NewState)
{
  if (NewState == DISABLE)
  {
		/* ADC输入口退出模拟输入模式 */
    ADCCFG0 &= (~(uint8_t)ADC_EAIN_Select);
    ADCCFG1 &= (~(uint8_t)(ADC_EAIN_Select >> 8));
  }
  else
  {
		/* ADC输入口设置为模拟输入模式 */
    ADCCFG0 |= ((uint8_t)ADC_EAIN_Select);
    ADCCFG1 |= ((uint8_t)(ADC_EAIN_Select >> 8));
  }
}

/*****************************************************
*函数名称:uint16_t ADC_GetConversionValue(void)
*函数功能:获得一次AD转换数据
*入口参数:void
*出口参数:uint16_t
*****************************************************/
uint16_t ADC_GetConversionValue(void)
{
	return ((ADCVH << 4) + (ADCVL >> 4));
}

/*****************************************************
*函数名称:void ADC_Cmd(FunctionalState NewState)
*函数功能:ADC功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
*****************************************************/
void ADC_Cmd(FunctionalState NewState)
{
	/* 使能/失能ADC功能 */
  if (NewState == DISABLE)
  {
    ADCCON &= 0X7F;
  }
  else
  {
    ADCCON |= 0x80;
  }
}

/*****************************************************
*函数名称:void ADC_VrefConfig(ADC_Vref_TypeDef ADC_Vref)
*函数功能:配置ADC的参考电压
*入口参数:
ADC_Vref_TypeDef:ADC_Vref:选择ADC参考电压
*出口参数:void
*****************************************************/
void ADC_VrefConfig(ADC_Vref_TypeDef ADC_Vref)
{
  OPINX = 0xC2;

  if (ADC_Vref == ADC_VREF_2_048V)
  {
    OPREG &= 0x3f;
    OPREG |= 0x40; //选择参考内部电压2.048V。
  }

  if (ADC_Vref == ADC_VREF_1_024V)
  {
    OPREG &= 0x3f;
    OPREG |= 0x80; //选择参考内部电压1.024V。
  }

  if (ADC_Vref == ADC_VREF_VDD)
  {
    OPREG &= 0x3f; //选择参考电压VDD。
  }
}

/******************* (C) COPYRIGHT 2022 SinOne Microelectronics *****END OF FILE****/