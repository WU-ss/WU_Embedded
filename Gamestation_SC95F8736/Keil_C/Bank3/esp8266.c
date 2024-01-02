#include "esp8266.h"
#include "Delay.h"
#include <string.h>
#include <stdarg.h>
#include "stdio.h"
#include "..\Bank1\GUI.h"
#include "..\Bank1\Lcd_Driver.h"
#include "..\Bank2\Key.h"
#include "..\Bank3\SHT30.h"

char numbuf[6];
extern char year;
extern char month;
extern char day;
extern char hour;
extern char minute;
extern char second;
char set_hour;
char set_minute;
char set_second;
char set_numbuf[6];
char clock_mode=0;

void USCI2_SendByte(uint8_t Byte)
{
	USCI2_UART_SendData8(Byte);
}

void USCI2_SendString(char* p)
{
	while(*p !='\0')
	{
		USCI2_SendByte(*p);
		p++;
		Delay_ms(10);
	}
}

char ESP8266_Cmd_Init()	//esp8266 配置信息
{
	USCI2_SendString("AT+RST\r\n");  ////esp8266重启指令
	Delay_ms(1000);

	USCI2_SendString("ATE0\r\n");  //关闭回显
	Delay_ms(2000);
	
	USCI2_SendString("AT+CWMODE=1\r\n");	// 设置工作模式 1 station模式  2 ap模式  3 station+ap模式
	Delay_ms(1000);
	
	USCI2_SendString("AT+CWJAP=\"WWW\",\"wyn62399\"\r\n");//输入路由器的账号密码
	Delay_ms(5000);
	
	USCI2_SendString("AT+CIPSTART=\"TCP\",\"api.k780.com\",88\r\n");
	Delay_ms(1000);
	
	USCI2_SendString("AT+CIPMODE=1\r\n");	
	Delay_ms(1000);

	USCI2_SendString("AT+CIPSEND\r\n");
	Delay_ms(1000);

//	USCI2_SendString("AT+RST\r\n");  ////esp8266重启指令
//	Delay_ms(1000);
	
	return 0;
}

char ESP_get_data(void)
{
	i=0;
	USCI2_SendString("GET http://api.k780.com:88/?app=life.time&appkey=10003&sign=b59bc3ef6191eb9f747dd4e83c99f2a4&format=json\r\n");//??·??μ?????	
	Delay_ms(1000);
	return 0;
}

void Parse_BJ_Time(void)
{
	year=Recbuff[1];
	month=Recbuff[2];
	day=Recbuff[3];
	hour=Recbuff[4];
	minute=Recbuff[5];
	second=Recbuff[6];
}

void Clock_start_draw(void)
{
	year=23;
	month=03;
	day=18;
	hour=10;
	minute=35;
	second=20;
}

void Clock_run(void)
{
		//显示年月日，时分秒
		sprintf(numbuf,"%d,",(int)year);
		Gui_DrawFont_GBK24(0,0,POINT_COLOR,BACK_COLOR,numbuf);
		sprintf(numbuf,"%d,",(int)month);
		Gui_DrawFont_GBK24(25,0,POINT_COLOR,BACK_COLOR,numbuf);
		sprintf(numbuf,"%d",(int)day);
		Gui_DrawFont_GBK24(50,0,POINT_COLOR,BACK_COLOR,numbuf);
		sprintf(numbuf,"%d:",(int)hour);
		Gui_DrawFont_GBK24(0,20,POINT_COLOR,BACK_COLOR,numbuf);
		sprintf(numbuf,"%d:",(int)minute);
		Gui_DrawFont_GBK24(25,20,POINT_COLOR,BACK_COLOR,numbuf);
		if(second>=10)
		{
			sprintf(numbuf,"%d",(int)second);
			Gui_DrawFont_GBK24(50,20,POINT_COLOR,BACK_COLOR,numbuf);
		}
		else 
		{
			Gui_DrawFont_GBK24(50,20,POINT_COLOR,BACK_COLOR,"0");
			sprintf(numbuf,"%d",(int)second);
			Gui_DrawFont_GBK24(58,20,POINT_COLOR,BACK_COLOR,numbuf);
		}
		
		SHT30_Read();			//温湿度传感器信息获取
		SHT30_Show();			//温湿度传感器信息显示
}
