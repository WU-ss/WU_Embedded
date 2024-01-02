#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

//定义缓冲区数组
//uint8_t Serial_TxPacket[4];
char receive_cmd[256];//定义字符串缓冲区
unsigned char i;//指针，用于判断接收字符串
	
//uint8_t Serial_RxData;
//uint8_t Serial_RxFlag;

//usart1,apb1
void Serial_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//define two pin(RX)
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx| USART_Mode_Tx ;//
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART1,&USART_InitStructure );
	
	//中断
	USART_ITConfig(USART1, USART_IT_RXNE,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1 ;
	
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
	
}
//定义字符串发送函数
void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
	
}

void Send_Char(char*str)
{
	uint8_t pstr = 0;//point for str
	while(str[pstr] != '\0')//判断是否为换行符,若是则发送数据
		USART_SendData(USART1,USART_IT_RXNE);
}

//接收数据包
void USART1_IRQHandler(void)
{
	//static uint8_t pRxPacket = 0;
	//static uint8_t RxState = 0;
	if (USART_GetITStatus(USART1,USART_IT_RXNE) == SET )
	{	
		receive_cmd[i++]=USART_ReceiveData(USART1);
		if((receive_cmd[i-2]=='\r') | (receive_cmd[i-1] =='\n'))
		{
			receive_cmd[i-2]='\0';//判断字符串结束
			i = 0;
		}
	}
}

