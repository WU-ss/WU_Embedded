#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include <stdio.h>
#include <stdarg.h>
uint16_t ADValue[100];
uint16_t ADAvg;
float Voltage;
uint16_t size;

void AD_Init(void) //初始化ADC1通道，选择A0作为输入口，模式为 单次转换|非扫描
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) == SET);
}

uint16_t AD_GetValue(void) //获取得到的ADC信息
{
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}

uint16_t Get_AD_Avg(void) 	//对得到的ADC信息进行滤波
{
							//算术平均值
	int i,j,t,sum;//n,
	size = sizeof(ADValue);
	for(i=0;i<100;i++)
	{
		ADValue[i] = AD_GetValue()		 ;									//AD_GetValue		
		Delay_us(10);
	}
    if(size > 5)
	{
		for(j=0;j<size;j++)
		{
		sum += ADValue[j];
		}
		
		for(i=0;i<size;i++)    
		{
		for(j=0;j<size-i;j++)
			{
			if(ADValue[j]>ADValue[j+1])
				{
					t=ADValue[j+1];
					ADValue[j+1]=ADValue[j];
					ADValue[j]=t;
				}
			}
		}
//            ADAvg =sum/ (size);
	ADAvg =(sum-ADValue[0]-ADValue[size-1] )/ (size -2);
//	size = 0;
//	memset(ADValue,0,sizeof(ADValue));

	}
	return ADAvg;
	size = 0;
}
float Get_Voltage(void)
{
		Get_AD_Avg();
		Voltage = ((float)ADAvg / 255* 3.3)+1.5;
	return Voltage;
}

