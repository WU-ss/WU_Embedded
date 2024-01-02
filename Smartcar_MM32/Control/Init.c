#include "headfile.h"

void init_all() //初始化所有
{
	//初始化debug输出串口
	board_init(true);

	//初始化TIM1频率2Hz中断优先级3 
	tim_interrupt_init(TIM_1, 200, 2);			
	tim_interrupt_init(TIM_8, 5, 3);
	tim_interrupt_init(TIM_14, 2, 1);

	//初始化GPIO功能 输出 默认高电平
	gpio_init(D7, GPO, GPIO_LOW, GPO_PUSH_PULL);				
	gpio_init(A4, GPO, GPIO_LOW, GPO_PUSH_PULL);
	gpio_init(B8, GPO, GPIO_LOW, GPO_PUSH_PULL);

	//初始化OLED模块
	oled_init();
	
	//初始化ADC通道
	adc_init(ADC_1,ADC1_CH00_A00,ADC_12BIT);
	adc_init(ADC_1,ADC1_CH02_A02,ADC_12BIT);
	adc_init(ADC_1,ADC1_CH03_A03,ADC_12BIT);

	//初始化PWM通道
	//左轮PWM
	pwm_init(TIM_2, TIM_2_CH1_A11, 10000, 50000);	// 初始化TIM2 频率10KHz 初始占空比为 0/PWM_DUTY_MAX*100%
	//右轮PWM
	pwm_init(TIM_3, TIM_3_CH4_C09, 10000, 50000);	// 初始化TIM2 频率10KHz 初始占空比为 0/PWM_DUTY_MAX*100%

}

