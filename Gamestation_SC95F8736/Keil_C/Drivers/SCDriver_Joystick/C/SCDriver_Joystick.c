//************************************************************
//  Copyright (c) 
//	文件名称	: SCDriver_Joystick.C
//	作者		: Andy
//	模块功能	: 摇杆应用驱动库源文件
//  最后更正日期: 2019/4/16
// 	版本		: V0.1 
//  说明        ：驱动库进行多次ADC电压采样，首次的电压转换值会被忽略，
//				  同时舍弃电压最大值与最小值后求取平均值，来回切换x,y两个通道获得坐标值  
//*************************************************************
#include "..\H\SCDriver_Joystick.h"
#include "SC_Init.h"
unsigned char SCD_Joystick_PosX;
unsigned char SCD_Joystick_PosY; 

#define  SCD_Joystick_CLOCK	      	0x01	   //ADC的时钟频率，与采样时间成正比关系
#define  SCD_Joystick_CYCLE	      	0x00	  //ADC采样时钟周期，与采样时间成正比关系
#define  SCD_Joystick_SAMPLING_NUM  6					       //ADC采样次数，需大于2，小于16。
unsigned int code PositionTab[]={0,1000,2200,4095};

void SCD_Joystick_Init(void)
{
	ADC_Init(SCD_Joystick_CLOCK, SCD_Joystick_CYCLE);
	ADC_ITConfig(DISABLE, LOW);
	ADC_Cmd(ENABLE);		
}

unsigned int SCD_Joystick_GetConversionValue(ADC_Channel_TypeDef ADC_Channel)
{
	unsigned char i;
	unsigned int SCD_Joystick_MaxValue = 0, SCD_Joystick_MinValue = 4096;
	unsigned int SCD_Joystick_Value = 0, SCD_Joystick_ValueSum = 0;
	  
	ADC_ChannelConfig(ADC_Channel, ENABLE);
	ADC_StartConversion();
	while(!ADC_GetFlagStatus());
	ADC_ClearFlag();
	
	for(i=0; i<SCD_Joystick_SAMPLING_NUM; i++)
	{
		ADC_StartConversion();
		while(!ADC_GetFlagStatus());
		ADC_ClearFlag();
		SCD_Joystick_Value = ADC_GetConversionValue();

		if(SCD_Joystick_Value >= SCD_Joystick_MaxValue)
		{
			SCD_Joystick_MaxValue = SCD_Joystick_Value;	
		}
		if(SCD_Joystick_Value <= SCD_Joystick_MinValue)
		{
			SCD_Joystick_MinValue = SCD_Joystick_Value;
		}
		SCD_Joystick_ValueSum += SCD_Joystick_Value;
	}
	
	SCD_Joystick_Value = (SCD_Joystick_ValueSum - SCD_Joystick_MaxValue - SCD_Joystick_MinValue) / (SCD_Joystick_SAMPLING_NUM - 2);
		
	return SCD_Joystick_Value; 
}


unsigned int PositionTrans(unsigned int ADValue)
{
	unsigned int i;
	for(i=0;i<3;i++)
	{
		if((ADValue>PositionTab[i])&&(ADValue<=PositionTab[i+1]))
		{
			return i;
		}
	}
	return 0;
}

void SCD_Joystick_GetPosition()
{
	SCD_Joystick_PosX = PositionTrans(SCD_Joystick_GetConversionValue(SCD_Joystick_PinX)); //获得X转换值
	SCD_Joystick_PosY = PositionTrans(SCD_Joystick_GetConversionValue(SCD_Joystick_PinY)); //获得Y转换值
}
