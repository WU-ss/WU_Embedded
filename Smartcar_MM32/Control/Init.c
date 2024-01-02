#include "headfile.h"

void init_all() //��ʼ������
{
	//��ʼ��debug�������
	board_init(true);

	//��ʼ��TIM1Ƶ��2Hz�ж����ȼ�3 
	tim_interrupt_init(TIM_1, 200, 2);			
	tim_interrupt_init(TIM_8, 5, 3);
	tim_interrupt_init(TIM_14, 2, 1);

	//��ʼ��GPIO���� ��� Ĭ�ϸߵ�ƽ
	gpio_init(D7, GPO, GPIO_LOW, GPO_PUSH_PULL);				
	gpio_init(A4, GPO, GPIO_LOW, GPO_PUSH_PULL);
	gpio_init(B8, GPO, GPIO_LOW, GPO_PUSH_PULL);

	//��ʼ��OLEDģ��
	oled_init();
	
	//��ʼ��ADCͨ��
	adc_init(ADC_1,ADC1_CH00_A00,ADC_12BIT);
	adc_init(ADC_1,ADC1_CH02_A02,ADC_12BIT);
	adc_init(ADC_1,ADC1_CH03_A03,ADC_12BIT);

	//��ʼ��PWMͨ��
	//����PWM
	pwm_init(TIM_2, TIM_2_CH1_A11, 10000, 50000);	// ��ʼ��TIM2 Ƶ��10KHz ��ʼռ�ձ�Ϊ 0/PWM_DUTY_MAX*100%
	//����PWM
	pwm_init(TIM_3, TIM_3_CH4_C09, 10000, 50000);	// ��ʼ��TIM2 Ƶ��10KHz ��ʼռ�ձ�Ϊ 0/PWM_DUTY_MAX*100%

}

