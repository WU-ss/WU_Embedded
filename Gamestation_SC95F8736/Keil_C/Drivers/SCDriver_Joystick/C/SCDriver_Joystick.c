//************************************************************
//  Copyright (c) 
//	�ļ�����	: SCDriver_Joystick.C
//	����		: Andy
//	ģ�鹦��	: ҡ��Ӧ��������Դ�ļ�
//  ����������: 2019/4/16
// 	�汾		: V0.1 
//  ˵��        ����������ж��ADC��ѹ�������״εĵ�ѹת��ֵ�ᱻ���ԣ�
//				  ͬʱ������ѹ���ֵ����Сֵ����ȡƽ��ֵ�������л�x,y����ͨ���������ֵ  
//*************************************************************
#include "..\H\SCDriver_Joystick.h"
#include "SC_Init.h"
unsigned char SCD_Joystick_PosX;
unsigned char SCD_Joystick_PosY; 

#define  SCD_Joystick_CLOCK	      	0x01	   //ADC��ʱ��Ƶ�ʣ������ʱ������ȹ�ϵ
#define  SCD_Joystick_CYCLE	      	0x00	  //ADC����ʱ�����ڣ������ʱ������ȹ�ϵ
#define  SCD_Joystick_SAMPLING_NUM  6					       //ADC���������������2��С��16��
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
	SCD_Joystick_PosX = PositionTrans(SCD_Joystick_GetConversionValue(SCD_Joystick_PinX)); //���Xת��ֵ
	SCD_Joystick_PosY = PositionTrans(SCD_Joystick_GetConversionValue(SCD_Joystick_PinY)); //���Yת��ֵ
}
