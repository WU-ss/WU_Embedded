#ifndef __usart2_H
#define __usart2_H

#include <stdio.h>

//extern uint8_t Serial_TxPacket[];
extern char receive_cmd[256];
extern uint8_t Serial_RxFlag;

uint8_t Serial_GetRxData(void);
//uint8_t Serial_GetRxFlag(void);
//void Serial_SendPacket(void);

void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void USART_IQRnHandler(void);
void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Send_Char(char*str);

#endif
