#include "stm32f10x.h"
#include "systick.h"
//#include "usart.h"
#include "iic.h"
#include "Font.h"
#include "OLED_IIC.h"
#include "MAX30102.h"
#include "algorithm.h"
#include "blood.h"
#include "RTC.h" 
#include "delay.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "inv_mpu.h"
#include "math.h"
#include "usart2.h"
#include "AT.h"
#include "stm32_iic.h"
#include "stdio.h"
#include "mpu_user_api.h"
#include "Timer.h"

extern BloodData g_blooddata;
extern const char* pubtopic;	//配置参数，发布消息


int main(void)
{	
	IIC_GPIO_INIT();
	i2cInit();      //IIC总线的初始化

	RTC_Init();
//	RTC_Set(2023,7,11,16,47,00);
	
	OLED_Init();
	fill_picture(0x00);	
	
	Serial_Init();
	
	OLED_Printf_EN(1,0,"IWatch is initializing.");
	OLED_Printf_EN(6,0,"    Please wait");
	Mpu_Init(1);
	esp_Init();
	
	MAX30102_GPIO();	
	Max30102_reset();	
	MAX30102_Config();
	
	fill_picture(0x00);	
	
	Timer_Init();
	
	while(1)
	{	

	}
}
