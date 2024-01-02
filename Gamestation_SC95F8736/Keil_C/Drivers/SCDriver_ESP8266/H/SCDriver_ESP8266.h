#ifndef _SCDriver_ESP8266_H_
#define _SCDriver_ESP8266_H_
//<<<Use SPTML>>>
#define SCD_ESP8266_TXD P44 //SCD_ESP8266_TXD 
#define SCD_ESP8266_TXD_INIT 0x0410 //SCD_ESP8266_TXD_INIT 
#define SCD_ESP8266_RXD P45 //SCD_ESP8266_RXD 
#define SCD_ESP8266_RXD_INIT 0x0420 //SCD_ESP8266_RXD_INIT 
#define SCD_ESP8266_BAUD 115200 //SCD_ESP8266_BAUD 
#define SCD_ESP8266_FSYS 32000000//SCD_ESP8266_FSYS 
extern void SCD_ESP8266_AP_Init(unsigned char* ssid,unsigned char* pwd,unsigned char chl,unsigned char ecn);
extern void SCD_ESP8266_STA_Init(unsigned char* ssid,unsigned char* pwd);
extern void SCD_ESP8266_STA_PassThrough(unsigned char Start);
extern void SCD_ESP8266_Init(unsigned char xdata * buffpoint,unsigned int bufflength);
extern void SCD_ESP8266_Uart_Send_String(unsigned char* string);
extern void SCD_ESP8266_AP_ServerSet(unsigned char server,unsigned char* port_t);
extern void SCD_ESP8266_AP_SendData(unsigned char Addr,unsigned char DataLength,unsigned char* Data);
extern void SCD_ESP8266_InterruptWork();
extern void SCD_ESP8266_STA_LinkServer(unsigned char* IP_t,unsigned char* port_t);
//<<<end of SPTML>>>
#endif
