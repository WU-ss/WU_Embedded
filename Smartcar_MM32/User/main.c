#include "headfile.h"
#include "Init.h"
#include "ADC.h"
#include "Path.h"
#include "PD.h"
#include "OLED.h"
#include "UART.h"

int main(void)
{
	init_all();
	
//	Saomiao();  //可以考虑不使用这个函数，通过调试之后直接给max和min赋值
	
	while(1)
	{
		ADC_Handle(); //处理得到ADC数据
		Test_Send_User(ADC_Avg[0],ADC_Avg[1],ADC_Avg[2],(uint16)(L_PWM*100),(uint16)(R_PWM*100));
		Path_Detect(); //路径检测
		PD_Control(); //电机的控制
		//调试出直道
//		pwm_duty_updata(TIM_2,TIM_2_CH1_A11,21100);  //更新右电机
//		pwm_duty_updata(TIM_3,TIM_3_CH4_C09,27000);  //更新左电机
	}
}

//路径检测与控制部分 5ms刷新一次
void tim1_interrupt_handler (void)		// TIM1周期中断处理函数 在 TIM1_BRK_UP_TRG_COM_IRQHandler 中调用
{
	
}

//ADC符号处理部分 0.2s刷新一次
void tim8_interrupt_handler(void)		// TIM8周期中断处理函数 在 TIM8_BRK_UP_TRG_COM_IRQHandler 中调用
{
	Get_ADC_Avg_Hist();
	Get_ADC_Symbol();
}

//显示屏调试部分 0.5s刷新一次
void tim14_interrupt_handler(void)
{
	OLED_Print(); //打印调试所用信息
	static bool io_state = GPIO_LOW;	// 状态标志
	gpio_set(D7, io_state);		    	// 更新D7状态
	gpio_set(A4, io_state);		    	// 更新A4状态
	io_state = !io_state;				// 翻转状态标志
}





