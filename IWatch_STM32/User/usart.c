#include "usart.h"
#include <stdio.h>
void USART_CONFIG(void)
{	
	RCC_APB2PeriphClockCmd(USART_TX_CLK|USART_RX_CLK,ENABLE);
	USART_CLKCMD(USART_CLK,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode		=	GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin		=	USART_TX_GPIO_Pin;
	GPIO_InitStruct.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(USART_TX_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode		=	GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin		=	USART_RX_GPIO_Pin;
	GPIO_Init(USART_RX_PORT,&GPIO_InitStruct);
	
	USART_InitTypeDef USART_InitTypeDef;
	USART_InitTypeDef.USART_BaudRate						= USART_BAD;
	USART_InitTypeDef.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;
	USART_InitTypeDef.USART_Mode								= USART_Mode_Rx|USART_Mode_Tx;
	USART_InitTypeDef.USART_Parity							= USART_Parity_No;
	USART_InitTypeDef.USART_StopBits						= USART_StopBits_1;
	USART_InitTypeDef.USART_WordLength					= USART_WordLength_8b;
	USART_Init(USART_PORT,&USART_InitTypeDef);
	
//	NVIC_InitTypeDef NVIC_InitStruct;
//	NVIC_InitStruct.NVIC_IRQChannel 									= USART_IRQChannel;
//	NVIC_InitStruct.NVIC_IRQChannelCmd 								= ENABLE;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	= 0;
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority 				= 1;
//	NVIC_Init(&NVIC_InitStruct);
//	
//	USART_ITConfig(USART_PORT,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART_PORT,ENABLE);
}


void Usart_SendByte(USART_TypeDef* USARTx,uint8_t data)
{
	USART_SendData(USARTx,data);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);
}

void Usart_SendString(USART_TypeDef* USARTx,uint8_t *str)
{
	while(*str)
	{	
		Usart_SendByte(USARTx,*str++);
	}
}

int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}

