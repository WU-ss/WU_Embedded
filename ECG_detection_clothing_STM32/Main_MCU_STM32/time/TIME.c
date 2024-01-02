#include "stm32f10x.h"                 					// Device header
#include <stdio.h>
#include <stdarg.h>
#include <Delay.h>


#define Read_Data GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)

unsigned int rec_data[4];

void DH11_GPIO_Init_IN(void)							//输入信息
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DH11_GPIO_Init_OUT(void)							//输出信息
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

#define read0 GPIO_ResetBits(GPIOA, GPIO_Pin_2)		//置低电平
#define read1 GPIO_SetBits(GPIOA, GPIO_Pin_2)			//置高电平
/*
************************************************************
*函数名 DH11_RST
*功能 DH11初始化
*形参 无
*返回值 无
************************************************************
*/
void DH11_RST(void)									//主机发送信号
{
	DH11_GPIO_Init_OUT(); //输出模式
	
	read1; //拉高
	Delay_us(50);
	
	read0; //拉低电平至少18us
	Delay_ms(20);
	
	read1; //拉高电平20~40us
	Delay_us(30);
	
	DH11_GPIO_Init_IN(); //输入模式
	
	//while( Read_Data == 0);
	//while( Read_Data == 1);
}



/*
************************************************************
*函数名 DHT11_Rec_Byte
*功能 DH11接收字节数据
*形参 无
*返回值 data
************************************************************
*/
unsigned char DHT11_Rec_Byte(void)
{
	unsigned char i = 0;
	unsigned char data;
	data = 0;
	for(i=0;i<8;i++) //1个数据就是1个字节byte，1个字节byte有8位bit
	{
		while( Read_Data == 0); //从1bit开始，低电平变高电平，等待低电平结束
		Delay_us(40); //延迟30us是为了区别数据0和数据1，0只有26~28us
		
		data <<= 1; //左移8次
		if( Read_Data == 1 ) //过了30us还是高电平就是数据1
		{
			//data |= 1; //下一位bit数据
			data += 1;
		}
		

		while( Read_Data == 1 ); //高电平变低电平，等待高电平结束
	}
	
	return data;
}

/*
************************************************************
*函数名 DH11_REC_Data
*功能 主机读取DH11温湿度数据
*形参 无
*返回值 温湿度，rec_data[]
************************************************************
*/

void DH11_REC_Data(void)
{
	
	unsigned int R_H,R_L,T_H,T_L;
	unsigned char RH,RL,TH,TL,CHECK;
	
	
	
	DH11_RST(); //主机发送信号
	//Delay_us(100);
	//read1; //拉高电平
	
	
	if( Read_Data == 0 ) //判断DHT11是否响应
	{	
		//Delay_us(50);
		while( Read_Data == 0); //低电平变高电平，等待低电平结束
		while( Read_Data == 1); //高电平变低电平，等待高电平结束
		
		R_H = DHT11_Rec_Byte();
		R_L = DHT11_Rec_Byte();
		T_H = DHT11_Rec_Byte();
		T_L = DHT11_Rec_Byte();
		CHECK = DHT11_Rec_Byte(); //接收5个数据,每接收一位数据移动到下一位
		
		read0; //当最后一bit数据传送完毕后，DHT11拉低总线 50us
		Delay_us(55); //这里延时55us
		read1; //随后总线由上拉电阻拉高进入空闲状态。
		
		if(R_H + R_L + T_H + T_L == CHECK) //和检验位对比，判断校验接收到的数据是否正确
		{
			RH = R_H;
			RL = R_L;
			TH = T_H;
			TL = T_L;
		}
	}
	rec_data[0] = RH;
	rec_data[1] = RL;
	rec_data[2] = TH;
	rec_data[3] = TL;
}






//8位湿度整数、8位湿度小数、8位温度整数、8位温度小数、8位校验位

//主机发送信号：拉低PA6电平保持18，拉高电平保持20-40
//读取响应：DHT11拉低40-50再拉高40-50(这里偷懒了，直接读数据)
//DHT输出数据
//0：低电平16-18+高电平26-28
//1：低电平12-14+高电平116-118

