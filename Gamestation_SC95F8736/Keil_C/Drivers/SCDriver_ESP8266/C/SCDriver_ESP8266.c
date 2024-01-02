//************************************************************
//  Copyright (c) 
//	文件名称	: SCDriver_ESP8266.C
//	作者		: Andy
//	模块功能	: ESP8266 WIFI模块应用驱动程序
//  最后更正日期: 2019/1/20
// 	版本		: V0.1 
//  说明        ：该库使用AT指令实现对ESP8266 WIFI模块的控制。
//*************************************************************	
#include"..\H\SCDriver_ESP8266.h"
#include "SC_Init.h"	
#define	SCD_ESP8266_UART0_TIMER_SELECT  UART0_CLOCK_TIMER1	 //使用UART0的时候才需要选择，使用UART1时忽略此值

#define IO_NULL  0xFF00
#define  SCD_IO_PORT(IO)    (uint8_t)(IO>>8)
#define  SCD_IO_PIN(IO)	    (uint8_t)(IO)

#define SCD_ESP8266_UART0		0x00
#define SCD_ESP8266_UART1		0x01
#define	SCD_ESP8266_MODE_STA 	'1'
#define	SCD_ESP8266_MODE_AP	  	'2'
#define	SCD_ESP8266_MODE_APSTA	'3'
#define SCD_ESP8266_OPEN	     0
#define SCD_ESP8266_WPA_PSK		 2
#define SCD_ESP8266_WPA2_PSK     3
#define SCD_ESP8266_WPA_WPA2_PSK 4
//extern unsigned char xdata SCD_ESP8266_BUFF[SCD_ESP8266_BUFF_LENGTH];//ESP8266接收缓存
unsigned char xdata *SCD_ESP8266_BuffPoint;
unsigned int SCD_ESP8266_BuffLength;
unsigned char SCD_ESP8266_BUFF_Number=0; //当前接受编号
bit SCD_ESP8266_UartReceFlag = 0;
bit SCD_ESP8266_UartSendFlag = 0;
//{
//函数名  #SCD_NT_PinMode#
//函数功能#对应的数码管驱动脚输出高#
//输入参数#
//			uint16_t IO_Pxx, 			  选择需要配置的IO口
//			GPIO_Mode_TypeDef IO_Pxx_Mode 选择IO口的工作模式
//		  #
//输出参数#void#
//}
void SCD_ESP8266_PinMode(uint16_t IO_Pxx, GPIO_Mode_TypeDef IO_Pxx_Mode)
{
	if(IO_Pxx != IO_NULL)
	{
		GPIO_Init(SCD_IO_PORT(IO_Pxx), SCD_IO_PIN(IO_Pxx), IO_Pxx_Mode);	
	}	
}
//{
//函数名  #SCD_ESP8266_Delay#
//函数功能#延时函数#
//输入参数#uint16_t n  延时时间长度#
//输出参数#void#
//}
void SCD_ESP8266_Delay(uint16_t n)
{
	uint16_t  i,j;
	for(i=0;i<n;i++)
		for(j=0;j<2000;j++);
}
//{
//函数名  #SCD_ESP8266_Init#
//函数功能#该函数用于初始化ESP8266所需使用的GPIO口状态#
//输入参数#void#
//输出参数#void#
//}
void SCD_ESP8266_Init(unsigned char xdata *buffpoint,unsigned int bufflength)
{
	SCD_ESP8266_PinMode(SCD_ESP8266_TXD_INIT, GPIO_MODE_IN_PU);
	UART0_Init(SCD_ESP8266_FSYS, SCD_ESP8266_BAUD, UART0_Mode_10B, SCD_ESP8266_UART0_TIMER_SELECT, UART0_RX_ENABLE);
	//波特率115200，SCD_ESP8266_UART0_TIMER_SELECT做时钟源，允许接收
	UART0_ITConfig(ENABLE, LOW);	//使能uart0中断
	SCD_ESP8266_BuffPoint = buffpoint;
	SCD_ESP8266_BuffLength= bufflength;

}
//{
//函数名  #SCD_ESP8266_Uart_Send_Byte#
//函数功能#通过UART发送一个BYTE#
//输入参数#unsigned char value#
//输出参数#void#
//}
void SCD_ESP8266_Uart_Send_Byte(unsigned char value)
{
	SBUF = value;
	while(!SCD_ESP8266_UartSendFlag);
	SCD_ESP8266_UartSendFlag = 0;
}
//{
//函数名  #SCD_ESP8266_Uart_Send_String#
//函数功能#该函数用于通过串口向ESP8266发字符串#
//输入参数#unsigned char *string 需要发送的字符串#
//输出参数#void#
//}
void SCD_ESP8266_Uart_Send_String(unsigned char *string)
{
	while(*string)
	{
		SCD_ESP8266_Uart_Send_Byte(*string++);
	}
}
//{
//函数名  #SCD_ESP8266_MODE#
//函数功能#ESP8266工作模式选择#
//输入参数#unsigned char ModeSelect 模式选择‘1’ ‘2’ ‘3’#
//输出参数#void#
//}
void SCD_ESP8266_MODE(unsigned char ModeSelect)
{
	SCD_ESP8266_Uart_Send_String("AT+CWMODE=");
	SCD_ESP8266_Uart_Send_Byte(ModeSelect); //需要填入ASII码值
	SCD_ESP8266_Uart_Send_Byte('\r');
	SCD_ESP8266_Uart_Send_Byte('\n');
}
//{
//函数名  #SCD_ESP8266_CWLAP#
//函数功能#扫描当前可用AP(WIFI)#
//输入参数#void#
//输出参数#void#
//}
void SCD_ESP8266_CWLAP()
{
	SCD_ESP8266_Uart_Send_String("AT+CWLAP\r\n");
}
//{
//函数名  #SCD_ESP8266_CWQAP#
//函数功能#断开与AP的连接#
//输入参数#void#
//输出参数#void#
//}
void SCD_ESP8266_CWQAP()
{
	SCD_ESP8266_Uart_Send_String("AT+CWQAP\r\n");	
}

//{
//函数名  #SCD_ESP8266_CWSAP_READ#
//函数功能#查看ESP8266的AP设置，通过串口获得结果#
//输入参数#void#
//输出参数#void#
//}
void SCD_ESP8266_CWSAP_READ()
{
	SCD_ESP8266_Uart_Send_String("AT+CWSAP?\r\n");
}
//{
//函数名  #SCD_ESP8266_CWSAP#
//函数功能#设置AP参数#
//输入参数#
//			unsigned char *ssid	 WIFI名
//			unsigned char *pwd	 WIFI密码
//			unsigned char chl		 通道号
//			unsigned char ecn		 加密方式$0-OPEN，1-WEP，2-WPA_PSK，3-WPA2_PSK，4-WPA_WPA2_PSK$
//		  #
//输出参数#void#
//}
void SCD_ESP8266_CWSAP(unsigned char *ssid,unsigned char *pwd,unsigned char chl,unsigned char ecn)
{
	SCD_ESP8266_Uart_Send_String("AT+CWSAP=\"");
	SCD_ESP8266_Uart_Send_String(ssid);
	SCD_ESP8266_Uart_Send_Byte('\"');
	SCD_ESP8266_Uart_Send_Byte(',');
	SCD_ESP8266_Uart_Send_Byte('\"');
	SCD_ESP8266_Uart_Send_String(pwd);
	SCD_ESP8266_Uart_Send_Byte('\"');
	SCD_ESP8266_Uart_Send_Byte(',');
	SCD_ESP8266_Uart_Send_Byte(chl+0x30);
	SCD_ESP8266_Uart_Send_Byte(',');
	SCD_ESP8266_Uart_Send_Byte(ecn+0x30);
	SCD_ESP8266_Uart_Send_Byte('\r');
	SCD_ESP8266_Uart_Send_Byte('\n');
}
//{
//函数名  #SCD_ESP8266_CWJAP#
//函数功能#连接WIFI网络#
//输入参数#
//			unsigned char *ssid	 WIFI名
//			unsigned char *pwd	 WIFI密码
//		  #
//输出参数#void#
//}
void SCD_ESP8266_CWJAP(unsigned char *ssid,unsigned char *pwd) 
{
	SCD_ESP8266_Uart_Send_String("AT+CWJAP=\"");
	SCD_ESP8266_Uart_Send_String(ssid);
	SCD_ESP8266_Uart_Send_Byte('\"');
	SCD_ESP8266_Uart_Send_Byte(',');
	SCD_ESP8266_Uart_Send_Byte('\"');
	SCD_ESP8266_Uart_Send_String(pwd);
	SCD_ESP8266_Uart_Send_Byte('\"');
	SCD_ESP8266_Uart_Send_Byte('\r');
	SCD_ESP8266_Uart_Send_Byte('\n');
}
//{
//函数名  #SCD_ESP8266_CIFSR#
//函数功能#查阅本地IP地址#
//输入参数#void#
//输出参数#void#
//}
void SCD_ESP8266_CIFSR()
{
	SCD_ESP8266_Uart_Send_String("AT+CIFSR\r\n");	
}
//{
//函数名  #SCD_ESP8266_AP_ServerSet#
//函数功能#AP模式下开启服务器#
//输入参数#
//			unsigned char server   服务器开关，1表示开，0表示关
//			unsigned char *port_t	 服务器端口号
//		  #
//输出参数#void#
//}
void SCD_ESP8266_AP_ServerSet(unsigned char server,unsigned char *port_t)	  //建立或关闭server
{
	SCD_ESP8266_Uart_Send_String("AT+CIPSERVER=");
	SCD_ESP8266_Uart_Send_Byte(server+0X30);
	SCD_ESP8266_Uart_Send_Byte(',');
	SCD_ESP8266_Uart_Send_String(port_t);
	SCD_ESP8266_Uart_Send_Byte('\r');
	SCD_ESP8266_Uart_Send_Byte('\n');
}
//{
//函数名  #SCD_ESP8266_CIPMODE#
//函数功能#选择传输模式#
//输入参数#unsigned char select  0：普通模式；1：透传模式#
//输出参数#void#
//}
void SCD_ESP8266_CIPMODE(unsigned char select)
{
	SCD_ESP8266_Uart_Send_String("AT+CIPMODE=");
	SCD_ESP8266_Uart_Send_Byte(select+0X30);
	SCD_ESP8266_Uart_Send_Byte('\r');
	SCD_ESP8266_Uart_Send_Byte('\n');
}
//{
//函数名  #SCD_ESP8266_RST#
//函数功能#复位#
//输入参数#void#
//输出参数#void#
//}
void SCD_ESP8266_RST()
{
	SCD_ESP8266_Uart_Send_String("AT+RST\r\n");	
}
//{
//函数名  #SCD_ESP8266_TEST#
//函数功能#查阅当前版本号，结果通过串口获得#
//输入参数#void#
//输出参数#void#
//}
void SCD_ESP8266_VIEW()
{
	SCD_ESP8266_Uart_Send_String("AT+GMR\n");	//查阅当前版本
}
//{
//函数名  #SCD_ESP8266_AP_Init#
//函数功能#AP模式下开启服务器#
//输入参数#
//			unsigned char *ssid	 WIFI名
//			unsigned char *pwd	 WIFI密码
//			unsigned char chl		 通道号
//			unsigned char ecn		 加密方式$0-OPEN，1-WEP，2-WPA_PSK，3-WPA2_PSK，4-WPA_WPA2_PSK$
//		  #
//输出参数#void#
//}
void SCD_ESP8266_AP_Init(unsigned char *ssid,unsigned char *pwd,unsigned char chl,unsigned char ecn) //将ESP8266设置为AP模式进行工作
{
	SCD_ESP8266_MODE(SCD_ESP8266_MODE_AP);	  //选择工作模式为AP模式
	SCD_ESP8266_Delay(1000);
	SCD_ESP8266_RST();
	SCD_ESP8266_Delay(3000);//复位
	SCD_ESP8266_CWSAP(ssid,pwd,chl,ecn);
	SCD_ESP8266_Delay(1000);
	SCD_ESP8266_Uart_Send_String("AT+CIPMUX=1\r\n");//1启动多连接,0启动单连接
	SCD_ESP8266_Delay(1000);
}
//{
//函数名  #SCD_ESP8266_STA_LinkServer#
//函数功能#AP模式下开启服务器#
//输入参数#
//			unsigned char *IP_t    服务器IP地址
//			unsigned char *port_t	 服务器端口号
//		  #
//输出参数#void#
//}
void SCD_ESP8266_STA_LinkServer(unsigned char *IP_t,unsigned char *port_t)//连接服务器
{
	SCD_ESP8266_Uart_Send_String("AT+CIPSTART=\"TCP\"");
	SCD_ESP8266_Uart_Send_Byte(',');
	SCD_ESP8266_Uart_Send_Byte('\"');
	SCD_ESP8266_Uart_Send_String(IP_t);
	SCD_ESP8266_Uart_Send_Byte('\"');
	SCD_ESP8266_Uart_Send_Byte(',');
	SCD_ESP8266_Uart_Send_String(port_t);
	SCD_ESP8266_Uart_Send_Byte('\r');
	SCD_ESP8266_Uart_Send_Byte('\n');
	SCD_ESP8266_Delay(1000);
}
//{
//函数名  #SCD_ESP8266_STA_Init#
//函数功能#将ESP8266设置为STA模式进行工作#
//输入参数#
//			unsigned char *ssid	 WIFI名
//			unsigned char *pwd	 WIFI密码
//		  #
//输出参数#void#
//}
void SCD_ESP8266_STA_Init(unsigned char *ssid,unsigned char *pwd) //将ESP8266设置为STA模式进行工作
{
	SCD_ESP8266_MODE(SCD_ESP8266_MODE_STA);	  //选择工作模式为STA模式
	SCD_ESP8266_Delay(1000);
	SCD_ESP8266_RST();
	SCD_ESP8266_Delay(3000);//复位
	SCD_ESP8266_CWJAP(ssid, pwd);
	SCD_ESP8266_Delay(1000);
}
//{
//函数名  #SCD_ESP8266_AP_SendData#
//函数功能#在AP模式下发送数据#
//输入参数#
//			unsigned char Addr		发送地址编号
//			unsigned char DataLength	发送数据长度
//			unsigned char*Data		发送数据
//		  #
//输出参数#void#
//}
void SCD_ESP8266_AP_SendData(unsigned char Addr,unsigned char DataLength,unsigned char*Data)
{
	SCD_ESP8266_Uart_Send_String("AT+CIPSEND=");
	SCD_ESP8266_Uart_Send_Byte(Addr+0X30);
	SCD_ESP8266_Uart_Send_Byte(',');
	SCD_ESP8266_Uart_Send_Byte(DataLength+0X30);
	SCD_ESP8266_Uart_Send_Byte('\r');
	SCD_ESP8266_Uart_Send_Byte('\n');
	SCD_ESP8266_Delay(10);
	SCD_ESP8266_Uart_Send_String(Data);
}
//{
//函数名  #SCD_ESP8266_STA_SendData#
//函数功能#在STA模式下发送数据#
//输入参数#
//			unsigned char DataLength	发送数据长度
//			unsigned char*Data		发送数据
//		  #
//输出参数#void#
//}
void SCD_ESP8266_STA_SendData(unsigned char DataLength,unsigned char*Data)
{
	SCD_ESP8266_Uart_Send_String("AT+CIPSEND=");
	SCD_ESP8266_Uart_Send_Byte(DataLength+0X30);
	SCD_ESP8266_Uart_Send_Byte('\r');
	SCD_ESP8266_Uart_Send_Byte('\n');
	SCD_ESP8266_Delay(10);
	SCD_ESP8266_Uart_Send_String(Data);
}
//{
//函数名  #SCD_ESP8266_STA_PassThrough#
//函数功能#STA模式下的透传开关#
//输入参数#
//			FunctionalState Start	透传开关$FunctionalState$
//		  #
//输出参数#void#
//}
void SCD_ESP8266_STA_PassThrough(FunctionalState Start)
{
	if(Start)
	{
	   SCD_ESP8266_Uart_Send_String("AT+CIPMODE=1\r\n"); //使能透传模式
	   SCD_ESP8266_Delay(1000);
	   SCD_ESP8266_Uart_Send_String("AT+CIPSEND\r\n");	 //进入发送数据模式
	   SCD_ESP8266_Delay(1000);
	}
	else
	{
	   SCD_ESP8266_Uart_Send_String("+++");
	}
	
}
//{
//函数名  #SCD_ESP8266_BUFF_Clear#
//函数功能#清空接收缓存#
//输入参数#void#
//输出参数#void#
//}
void SCD_ESP8266_BUFF_Clear()
{
	unsigned char i;
	for(i=0;i<SCD_ESP8266_BuffLength;i++)
	{
	   SCD_ESP8266_BuffPoint[i] = 0;
	}
	SCD_ESP8266_BUFF_Number=0;
}
//{
//函数名  #SCD_ESP8266_BUFF_Update#
//函数功能#接收缓存更新#
//输入参数#void#
//输出参数#void#
//}
void SCD_ESP8266_BUFF_Update()
{
    SCD_ESP8266_BUFF_Number++;
	if(SCD_ESP8266_BUFF_Number>=SCD_ESP8266_BuffLength)
	{
		SCD_ESP8266_BUFF_Number	= 0;
		SCD_ESP8266_BUFF_Clear();//清空接收缓冲区
	}
}
//{
//函数名  #SCD_ESP8266_InterruptWork#
//函数功能#该函数必须放于对应的UART中断函数内，用于清中断和接收数据#
//输入参数#unsigned char *string 需要发送的字符串#
//输出参数#void#
//}
void SCD_ESP8266_InterruptWork()
{
	if(UART0_GetFlagStatus(UART0_FLAG_RI))
	{
		UART0_ClearFlag(UART0_FLAG_RI);
		SCD_ESP8266_UartReceFlag = 1;
		SCD_ESP8266_BuffPoint[SCD_ESP8266_BUFF_Number] = UART0_ReceiveData8();
		SCD_ESP8266_BUFF_Update();
	}
	if(UART0_GetFlagStatus(UART0_FLAG_TI))
	{
		UART0_ClearFlag(UART0_FLAG_TI);
		SCD_ESP8266_UartSendFlag = 1;
	}
}


							 