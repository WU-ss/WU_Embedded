#include "stm32f10x.h"                  		// Device header
#include "OLED.h"
#include "Delay.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "AT.h"
#include "AD.h"
#include "TIME.h"
#include "filter.h"
#include "Lcd_Driver.h"
#include "GUI.h"

extern char receive_cmd[256];					//定义字符串缓冲区
extern unsigned int rec_data[4];
extern float Voltage;
extern float BPM;
extern char flag;
extern uint8_t timeCount;
u8 numbuf[6];
uint16_t x=0;					//作图的横坐标，每次自增1，类比时间轴，0~127
uint16_t y=0;					//作图的纵坐标，与采集到的信号值有关，0~127
uint16_t Pre_y=0;				//上一时刻作图的纵坐标，与采集到的信号值有关，0~127
uint16_t Pre_ADC_Value=200;	//假设这个是ADC上一次采集的值，范围是0~65535
uint16_t ADC_Value=200;		//假设这个是ADC这次采集的值，范围是0~65535
//u16 POINT_COLOR=0x0000;	//画笔颜色
//u16 BACK_COLOR=0xFFFF;  //背景色 

void ECG_draw(uint16_t Value,uint16_t Pre_Value)	//图形绘制函数，本质就是将之前的点与这一时刻的点连线
{

//	ADAvg=AD_GetValue();
	Pre_y=(0.8-Pre_Value/(float)4095)*127;	//1-（）是将高数值放在坐标的低位；+60是将原点平移到中间位置
	y=(0.8-Value/(float)4095)*127;
		//将这一时刻的ADC值赋给上一时刻
	Gui_DrawLine(x,Pre_y,x+1,y,BLUE);
	Pre_ADC_Value=ADC_Value;
	if(x>127)	
	{
		x=0;
		Lcd_Clear(WHITE);
	}
		
	else	x++;
}
int main(void)
{	
	uint8_t Judge=0;
	SystemInit();	
	AD_Init();
	OLED_Init();
	Serial_Init();
	Lcd_Init();
	LCD_LED_SET;//通过IO控制背光亮
	Lcd_Clear(WHITE);
	OLED_ShowString(1,2,"Init...");
	Gui_DrawFont_GBK24(5,10,RED,BACK_COLOR,"init");
	Delay_ms(10);
	do
	{
		Judge = esp_Init();
		OLED_Clear();
		Lcd_Clear(WHITE);
		Gui_DrawFont_GBK24(5,5,RED,BACK_COLOR,"error code: ");	//初始化失败：1，未能关闭回显；2，未能开启sta模式；3，未能连接wifi
		OLED_ShowString(1,2,"error code: ");
		OLED_ShowNum(1,13,Judge,1);				//4，未能配置用户信息；5，未能连接Thingsloud服务器
		sprintf((u8*)numbuf,"%d",(int)Judge);
		Gui_DrawFont_GBK24(100,5,RED,BACK_COLOR,numbuf);
		memset(numbuf,0,sizeof(numbuf));		//清零

	}
	while(Judge);
	OLED_ShowString(1,1,"Init Complished");
	Gui_DrawFont_GBK24(5,5,RED,BACK_COLOR,"Init Complished");
	Delay_s(2);
	BPM=75;
	OLED_Clear();
	Lcd_Clear(WHITE);
	OLED_ShowString(1, 1, "BPM:");
	OLED_ShowString(2, 1, "Voltage:0.00V");
	OLED_ShowNum(2, 9, Voltage, 1);
	OLED_ShowString(3,2,"temp");
	OLED_ShowString(3,10,"humi");
	Lcd_Clear(WHITE);
	Gui_DrawFont_GBK24(10,70,RED,WHITE,"BPM: ");
	Gui_DrawFont_GBK24(10,100,RED,WHITE,"temp");
	Gui_DrawFont_GBK24(73,100,RED,WHITE,"humi");
	Serial_SendNumber(BPM,4);
	Serial_SendString("V ");
	
	while(1)
	{
		uint8_t i;
		DH11_REC_Data(); 						//接收温度和湿度的数据
		OLED_ShowNum(4,2,rec_data[2],2);
		OLED_ShowNum(4,10,rec_data[0],2);	
		OLED_ShowNum(1, 9, BPM, 4);
		OLED_ShowNum(2, 11, ((uint16_t)(Voltage * 100) % 100+1.5), 2);
		
		Gui_DrawLine(0,65,127,65,BLUE);
		Gui_DrawLine(0,90,127,90,BLUE);
		Gui_DrawLine(63,90,63,127,BLUE);
		
		
		
		Gui_DrawFont_GBK24(10,70,RED,WHITE,"BPM:");
		Gui_DrawFont_GBK24(10,100,RED,WHITE,"temp");
		Gui_DrawFont_GBK24(73,100,RED,WHITE,"humi");
		
		sprintf((u8*)numbuf,"%d",(int)rec_data[2]);
		Gui_DrawFont_GBK24(45,100,RED,BACK_COLOR,numbuf);
		memset(numbuf,0,sizeof(numbuf));		//清零	
		sprintf((u8*)numbuf,"%d",(int)rec_data[0]);
		Gui_DrawFont_GBK24(105,100,RED,BACK_COLOR,numbuf);
		memset(numbuf,0,sizeof(numbuf));
		printf("AT+MQTTPUB=0,\"attributes\",\"{\\\"Voltage\\\":%f\\,\\\"BPM\\\":%f\\,\\\"temperature\\\":%d\\,\\\"humidity\\\":%d}\",0,0\r\n",Voltage,BPM,rec_data[2],rec_data[0]);	//发布消息
		
	for (i = 0; i < 50; i ++)					//计数器
	{
		Get_AD_Avg();
		Get_Voltage();
		if(Rwave_detection(ADAvg,AD_GetValue()))
		{
			calcul_BPM();
		}
		else
		{
			flag=0;
			timeCount+=1;
		}
			
		ADC_Value=Get_AD_Avg();
		ECG_draw(ADC_Value,Pre_ADC_Value);
		
		sprintf((u8*)numbuf,"%d",(int)BPM);
		Gui_DrawFont_GBK24(45,70,RED,BACK_COLOR,numbuf);
		memset(numbuf,0,sizeof(numbuf));		//清零		

		Delay_ms(30); 
	}
		i=0;
	}
}


