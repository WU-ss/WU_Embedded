#include "stm32f10x.h"                  	// Device header
#include <stdio.h>
#include <stdarg.h>
#include "usart.h"
#include "Delay.h"	
extern char receive_cmd[256];				//定义字符串缓冲区
extern unsigned int rec_data[4];	
extern float Voltage;
extern uint16_t ADAvg;
extern float BPM;
const char* WIFISSID = " 工程训练中心204";			//配置ssid
const char* WIFIPASSWORD = "12345678";		//配置password
const char* ClintID="user";
const char* username="zn931q55de0fke5z";	//根据云平台账号配置username
const char* password="kJTENfFtzl";			//根据云平台账号配置passwod
const char* Url="gz-3-mqtt.iot-api.com";	//配置api
const char* pubtopic="/sys/hidySzlCxPC/home/thing/event/property/post_reply";	//配置参数，发布消息
const char* subtopic="/sys/hidySzlCxPC/home/thing/event/property/post";			//配置参数，订阅消息
//const char* func_1="temperature";			//设备参数temperature
//const char* func_2="humidity";				//设备参数humidity
//const char* func_3="switch1";
//const char* func_4="switch2";


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
	//USART_SendData(USART1,(uint8_t)ch);//写入串口待发送的数据
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
	Delay_ms(2000);
	
	memset(receive_cmd,0,sizeof(receive_cmd));		//关闭回显
	printf("ATE0\r\n");
	Delay_ms(10);
	if(strcmp(receive_cmd,"OK"))
		return 1;
	
	printf("AT+CWMODE=1\r\n");						//开启sta模式
	Delay_ms(2000);
	if(strcmp(receive_cmd,"OK"))
		return 2;
	
	memset(receive_cmd,0,sizeof(receive_cmd));		//连接热点
	printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFISSID,WIFIPASSWORD);
	Delay_ms(10000);
	if(strcmp(receive_cmd,"OK"))
		return 3;
	
	memset(receive_cmd,0,sizeof(receive_cmd));		//配置mqtt用户信息
	printf("AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"\r\n",ClintID,username,password);
	Delay_ms(10);
	if(strcmp(receive_cmd,"OK"))
		return 4 ;
	
	memset(receive_cmd,0,sizeof(receive_cmd));		//连接服务器
	printf("AT+MQTTCONN=0,\"%s\",1883,1\r\n",Url);
	Delay_ms(10000);
	if(strcmp(receive_cmd,"OK"))
		return 5 ;
	
//	printf("AT+MQTTPUB=0,\"attributes\",\"{\\\"Voltage\\\":%f\\,\\\"ADAvg\\\":%u\\}\",0,0\r\n",Voltage,ADAvg);	//配置相应的json参数，发布消息
	printf("AT+MQTTPUB=0,\"attributes\",\"{\\\"Voltage\\\":%f\\,\\\"BPM\\\":%f\\,\\\"temperature\\\":%d\\,\\\"humdity\\\":%d}\",0,0\r\n",Voltage,BPM,rec_data[2],rec_data[0]);	//发布消息
	Delay_ms(1000);
	if(strcmp(receive_cmd,"OK"))
		return 6 ;
	
	memset(receive_cmd,0,sizeof(receive_cmd));
	return 0;										//缓冲区清零

}



