//************************************************************
//  Copyright (c) 
//	�ļ�����	: SCDriver_ESP8266.C
//	����		: Andy
//	ģ�鹦��	: ESP8266 WIFIģ��Ӧ����������
//  ����������: 2019/1/20
// 	�汾		: V0.1 
//  ˵��        ���ÿ�ʹ��ATָ��ʵ�ֶ�ESP8266 WIFIģ��Ŀ��ơ�
//*************************************************************	
#include"..\H\SCDriver_ESP8266.h"
#include "SC_Init.h"	
#define	SCD_ESP8266_UART0_TIMER_SELECT  UART0_CLOCK_TIMER1	 //ʹ��UART0��ʱ�����Ҫѡ��ʹ��UART1ʱ���Դ�ֵ

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
//extern unsigned char xdata SCD_ESP8266_BUFF[SCD_ESP8266_BUFF_LENGTH];//ESP8266���ջ���
unsigned char xdata *SCD_ESP8266_BuffPoint;
unsigned int SCD_ESP8266_BuffLength;
unsigned char SCD_ESP8266_BUFF_Number=0; //��ǰ���ܱ��
bit SCD_ESP8266_UartReceFlag = 0;
bit SCD_ESP8266_UartSendFlag = 0;
//{
//������  #SCD_NT_PinMode#
//��������#��Ӧ������������������#
//�������#
//			uint16_t IO_Pxx, 			  ѡ����Ҫ���õ�IO��
//			GPIO_Mode_TypeDef IO_Pxx_Mode ѡ��IO�ڵĹ���ģʽ
//		  #
//�������#void#
//}
void SCD_ESP8266_PinMode(uint16_t IO_Pxx, GPIO_Mode_TypeDef IO_Pxx_Mode)
{
	if(IO_Pxx != IO_NULL)
	{
		GPIO_Init(SCD_IO_PORT(IO_Pxx), SCD_IO_PIN(IO_Pxx), IO_Pxx_Mode);	
	}	
}
//{
//������  #SCD_ESP8266_Delay#
//��������#��ʱ����#
//�������#uint16_t n  ��ʱʱ�䳤��#
//�������#void#
//}
void SCD_ESP8266_Delay(uint16_t n)
{
	uint16_t  i,j;
	for(i=0;i<n;i++)
		for(j=0;j<2000;j++);
}
//{
//������  #SCD_ESP8266_Init#
//��������#�ú������ڳ�ʼ��ESP8266����ʹ�õ�GPIO��״̬#
//�������#void#
//�������#void#
//}
void SCD_ESP8266_Init(unsigned char xdata *buffpoint,unsigned int bufflength)
{
	SCD_ESP8266_PinMode(SCD_ESP8266_TXD_INIT, GPIO_MODE_IN_PU);
	UART0_Init(SCD_ESP8266_FSYS, SCD_ESP8266_BAUD, UART0_Mode_10B, SCD_ESP8266_UART0_TIMER_SELECT, UART0_RX_ENABLE);
	//������115200��SCD_ESP8266_UART0_TIMER_SELECT��ʱ��Դ���������
	UART0_ITConfig(ENABLE, LOW);	//ʹ��uart0�ж�
	SCD_ESP8266_BuffPoint = buffpoint;
	SCD_ESP8266_BuffLength= bufflength;

}
//{
//������  #SCD_ESP8266_Uart_Send_Byte#
//��������#ͨ��UART����һ��BYTE#
//�������#unsigned char value#
//�������#void#
//}
void SCD_ESP8266_Uart_Send_Byte(unsigned char value)
{
	SBUF = value;
	while(!SCD_ESP8266_UartSendFlag);
	SCD_ESP8266_UartSendFlag = 0;
}
//{
//������  #SCD_ESP8266_Uart_Send_String#
//��������#�ú�������ͨ��������ESP8266���ַ���#
//�������#unsigned char *string ��Ҫ���͵��ַ���#
//�������#void#
//}
void SCD_ESP8266_Uart_Send_String(unsigned char *string)
{
	while(*string)
	{
		SCD_ESP8266_Uart_Send_Byte(*string++);
	}
}
//{
//������  #SCD_ESP8266_MODE#
//��������#ESP8266����ģʽѡ��#
//�������#unsigned char ModeSelect ģʽѡ��1�� ��2�� ��3��#
//�������#void#
//}
void SCD_ESP8266_MODE(unsigned char ModeSelect)
{
	SCD_ESP8266_Uart_Send_String("AT+CWMODE=");
	SCD_ESP8266_Uart_Send_Byte(ModeSelect); //��Ҫ����ASII��ֵ
	SCD_ESP8266_Uart_Send_Byte('\r');
	SCD_ESP8266_Uart_Send_Byte('\n');
}
//{
//������  #SCD_ESP8266_CWLAP#
//��������#ɨ�赱ǰ����AP(WIFI)#
//�������#void#
//�������#void#
//}
void SCD_ESP8266_CWLAP()
{
	SCD_ESP8266_Uart_Send_String("AT+CWLAP\r\n");
}
//{
//������  #SCD_ESP8266_CWQAP#
//��������#�Ͽ���AP������#
//�������#void#
//�������#void#
//}
void SCD_ESP8266_CWQAP()
{
	SCD_ESP8266_Uart_Send_String("AT+CWQAP\r\n");	
}

//{
//������  #SCD_ESP8266_CWSAP_READ#
//��������#�鿴ESP8266��AP���ã�ͨ�����ڻ�ý��#
//�������#void#
//�������#void#
//}
void SCD_ESP8266_CWSAP_READ()
{
	SCD_ESP8266_Uart_Send_String("AT+CWSAP?\r\n");
}
//{
//������  #SCD_ESP8266_CWSAP#
//��������#����AP����#
//�������#
//			unsigned char *ssid	 WIFI��
//			unsigned char *pwd	 WIFI����
//			unsigned char chl		 ͨ����
//			unsigned char ecn		 ���ܷ�ʽ$0-OPEN��1-WEP��2-WPA_PSK��3-WPA2_PSK��4-WPA_WPA2_PSK$
//		  #
//�������#void#
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
//������  #SCD_ESP8266_CWJAP#
//��������#����WIFI����#
//�������#
//			unsigned char *ssid	 WIFI��
//			unsigned char *pwd	 WIFI����
//		  #
//�������#void#
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
//������  #SCD_ESP8266_CIFSR#
//��������#���ı���IP��ַ#
//�������#void#
//�������#void#
//}
void SCD_ESP8266_CIFSR()
{
	SCD_ESP8266_Uart_Send_String("AT+CIFSR\r\n");	
}
//{
//������  #SCD_ESP8266_AP_ServerSet#
//��������#APģʽ�¿���������#
//�������#
//			unsigned char server   ���������أ�1��ʾ����0��ʾ��
//			unsigned char *port_t	 �������˿ں�
//		  #
//�������#void#
//}
void SCD_ESP8266_AP_ServerSet(unsigned char server,unsigned char *port_t)	  //������ر�server
{
	SCD_ESP8266_Uart_Send_String("AT+CIPSERVER=");
	SCD_ESP8266_Uart_Send_Byte(server+0X30);
	SCD_ESP8266_Uart_Send_Byte(',');
	SCD_ESP8266_Uart_Send_String(port_t);
	SCD_ESP8266_Uart_Send_Byte('\r');
	SCD_ESP8266_Uart_Send_Byte('\n');
}
//{
//������  #SCD_ESP8266_CIPMODE#
//��������#ѡ����ģʽ#
//�������#unsigned char select  0����ͨģʽ��1��͸��ģʽ#
//�������#void#
//}
void SCD_ESP8266_CIPMODE(unsigned char select)
{
	SCD_ESP8266_Uart_Send_String("AT+CIPMODE=");
	SCD_ESP8266_Uart_Send_Byte(select+0X30);
	SCD_ESP8266_Uart_Send_Byte('\r');
	SCD_ESP8266_Uart_Send_Byte('\n');
}
//{
//������  #SCD_ESP8266_RST#
//��������#��λ#
//�������#void#
//�������#void#
//}
void SCD_ESP8266_RST()
{
	SCD_ESP8266_Uart_Send_String("AT+RST\r\n");	
}
//{
//������  #SCD_ESP8266_TEST#
//��������#���ĵ�ǰ�汾�ţ����ͨ�����ڻ��#
//�������#void#
//�������#void#
//}
void SCD_ESP8266_VIEW()
{
	SCD_ESP8266_Uart_Send_String("AT+GMR\n");	//���ĵ�ǰ�汾
}
//{
//������  #SCD_ESP8266_AP_Init#
//��������#APģʽ�¿���������#
//�������#
//			unsigned char *ssid	 WIFI��
//			unsigned char *pwd	 WIFI����
//			unsigned char chl		 ͨ����
//			unsigned char ecn		 ���ܷ�ʽ$0-OPEN��1-WEP��2-WPA_PSK��3-WPA2_PSK��4-WPA_WPA2_PSK$
//		  #
//�������#void#
//}
void SCD_ESP8266_AP_Init(unsigned char *ssid,unsigned char *pwd,unsigned char chl,unsigned char ecn) //��ESP8266����ΪAPģʽ���й���
{
	SCD_ESP8266_MODE(SCD_ESP8266_MODE_AP);	  //ѡ����ģʽΪAPģʽ
	SCD_ESP8266_Delay(1000);
	SCD_ESP8266_RST();
	SCD_ESP8266_Delay(3000);//��λ
	SCD_ESP8266_CWSAP(ssid,pwd,chl,ecn);
	SCD_ESP8266_Delay(1000);
	SCD_ESP8266_Uart_Send_String("AT+CIPMUX=1\r\n");//1����������,0����������
	SCD_ESP8266_Delay(1000);
}
//{
//������  #SCD_ESP8266_STA_LinkServer#
//��������#APģʽ�¿���������#
//�������#
//			unsigned char *IP_t    ������IP��ַ
//			unsigned char *port_t	 �������˿ں�
//		  #
//�������#void#
//}
void SCD_ESP8266_STA_LinkServer(unsigned char *IP_t,unsigned char *port_t)//���ӷ�����
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
//������  #SCD_ESP8266_STA_Init#
//��������#��ESP8266����ΪSTAģʽ���й���#
//�������#
//			unsigned char *ssid	 WIFI��
//			unsigned char *pwd	 WIFI����
//		  #
//�������#void#
//}
void SCD_ESP8266_STA_Init(unsigned char *ssid,unsigned char *pwd) //��ESP8266����ΪSTAģʽ���й���
{
	SCD_ESP8266_MODE(SCD_ESP8266_MODE_STA);	  //ѡ����ģʽΪSTAģʽ
	SCD_ESP8266_Delay(1000);
	SCD_ESP8266_RST();
	SCD_ESP8266_Delay(3000);//��λ
	SCD_ESP8266_CWJAP(ssid, pwd);
	SCD_ESP8266_Delay(1000);
}
//{
//������  #SCD_ESP8266_AP_SendData#
//��������#��APģʽ�·�������#
//�������#
//			unsigned char Addr		���͵�ַ���
//			unsigned char DataLength	�������ݳ���
//			unsigned char*Data		��������
//		  #
//�������#void#
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
//������  #SCD_ESP8266_STA_SendData#
//��������#��STAģʽ�·�������#
//�������#
//			unsigned char DataLength	�������ݳ���
//			unsigned char*Data		��������
//		  #
//�������#void#
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
//������  #SCD_ESP8266_STA_PassThrough#
//��������#STAģʽ�µ�͸������#
//�������#
//			FunctionalState Start	͸������$FunctionalState$
//		  #
//�������#void#
//}
void SCD_ESP8266_STA_PassThrough(FunctionalState Start)
{
	if(Start)
	{
	   SCD_ESP8266_Uart_Send_String("AT+CIPMODE=1\r\n"); //ʹ��͸��ģʽ
	   SCD_ESP8266_Delay(1000);
	   SCD_ESP8266_Uart_Send_String("AT+CIPSEND\r\n");	 //���뷢������ģʽ
	   SCD_ESP8266_Delay(1000);
	}
	else
	{
	   SCD_ESP8266_Uart_Send_String("+++");
	}
	
}
//{
//������  #SCD_ESP8266_BUFF_Clear#
//��������#��ս��ջ���#
//�������#void#
//�������#void#
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
//������  #SCD_ESP8266_BUFF_Update#
//��������#���ջ������#
//�������#void#
//�������#void#
//}
void SCD_ESP8266_BUFF_Update()
{
    SCD_ESP8266_BUFF_Number++;
	if(SCD_ESP8266_BUFF_Number>=SCD_ESP8266_BuffLength)
	{
		SCD_ESP8266_BUFF_Number	= 0;
		SCD_ESP8266_BUFF_Clear();//��ս��ջ�����
	}
}
//{
//������  #SCD_ESP8266_InterruptWork#
//��������#�ú���������ڶ�Ӧ��UART�жϺ����ڣ��������жϺͽ�������#
//�������#unsigned char *string ��Ҫ���͵��ַ���#
//�������#void#
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


							 