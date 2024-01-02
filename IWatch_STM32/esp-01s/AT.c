#include "stm32f10x.h"                  	// Device header
#include <stdio.h>
#include <stdarg.h>
#include "usart2.h"
#include "delay.h"	

extern char receive_cmd[256];				//定义字符串缓冲区	
const char* WIFISSID = "WWW";			//配置ssid
const char* WIFIPASSWORD = "wyn62399";		//配置password

const char* ClintID="a1bJx7P5asu.Watch_Sys_Demo|securemode=2\\,signmethod=hmacsha256\\,timestamp=1688880712615|";
const char* username="Watch_Sys_Demo&a1bJx7P5asu";	//根据云平台账号配置username
const char* password="7ec58f77844de0175fbadaab6d5106a2048a1bd18c52601286ce81d867730e8b";			//根据云平台账号配置passwod
const char* Url="a1bJx7P5asu.iot-as-mqtt.cn-shanghai.aliyuncs.com";	//配置api

const char* pubtopic="/sys/a1bJx7P5asu/Watch_Sys_Demo/thing/event/property/post";	//配置参数，发布消息

/*
************************************************************

"product_key": "a1bJx7P5asu",
"device_name": "Watch_Sys_Demo",
"device_secret": "6f8ef89259006691721c35a16c2c1775"
	
{"clientId":"a1bJx7P5asu.Watch_Sys_Demo|securemode=2,signmethod=hmacsha256,timestamp=1688880712615|",
"username":"Watch_Sys_Demo&a1bJx7P5asu",
"mqttHostUrl":"a1bJx7P5asu.iot-as-mqtt.cn-shanghai.aliyuncs.com",
"passwd":"7ec58f77844de0175fbadaab6d5106a2048a1bd18c52601286ce81d867730e8b",
"port":1883}

************************************************************
*/


/*
************************************************************
*函数名 fputc
*功能 重定向
*形参 无
*返回值 无
************************************************************
*/
int fputc(int ch,FILE *f)
{
	Serial_SendByte(ch);
	while(USART_GetFlagStatus (USART1,USART_FLAG_TC) == RESET)
		
	return ch;
}										//重定向
/*
************************************************************
*函数名 esp_Init
*功能	esp初始化，连接服务器
*形参 无
*返回值 无
************************************************************
*/
char esp_Init(void)
{
	
	memset(receive_cmd,0,sizeof(receive_cmd));
	printf("AT+RST\r\n");							//重启
	delay_ms(200);
	
	memset(receive_cmd,0,sizeof(receive_cmd));		//关闭回显
	printf("ATE0\r\n");
	delay_ms(10);
	if(strcmp(receive_cmd,"OK"))
//		return 1;
	
	printf("AT+CWMODE=1\r\n");						//开启sta模式
	delay_ms(200);
	if(strcmp(receive_cmd,"OK"))
		//return 2;
	
	memset(receive_cmd,0,sizeof(receive_cmd));		//连接热点
	printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFISSID,WIFIPASSWORD);
	delay_ms(5000);
	if(strcmp(receive_cmd,"OK"))
		return 3;
	
	memset(receive_cmd,0,sizeof(receive_cmd));		//配置mqtt用户信息
	printf("AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"\r\n",ClintID,username,password);
	delay_ms(10);
	if(strcmp(receive_cmd,"OK"))
		return 4 ;
	
	memset(receive_cmd,0,sizeof(receive_cmd));		//连接服务器
	printf("AT+MQTTCONN=0,\"%s\",1883,1\r\n",Url);
	delay_ms(5000);
	if(strcmp(receive_cmd,"OK"))
		return 5 ;
	
	memset(receive_cmd,0,sizeof(receive_cmd));
	return 0;										//缓冲区清零
}
