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
	
//	Saomiao();  //���Կ��ǲ�ʹ�����������ͨ������֮��ֱ�Ӹ�max��min��ֵ
	
	while(1)
	{
		ADC_Handle(); //����õ�ADC����
		Test_Send_User(ADC_Avg[0],ADC_Avg[1],ADC_Avg[2],(uint16)(L_PWM*100),(uint16)(R_PWM*100));
		Path_Detect(); //·�����
		PD_Control(); //����Ŀ���
		//���Գ�ֱ��
//		pwm_duty_updata(TIM_2,TIM_2_CH1_A11,21100);  //�����ҵ��
//		pwm_duty_updata(TIM_3,TIM_3_CH4_C09,27000);  //��������
	}
}

//·���������Ʋ��� 5msˢ��һ��
void tim1_interrupt_handler (void)		// TIM1�����жϴ����� �� TIM1_BRK_UP_TRG_COM_IRQHandler �е���
{
	
}

//ADC���Ŵ����� 0.2sˢ��һ��
void tim8_interrupt_handler(void)		// TIM8�����жϴ����� �� TIM8_BRK_UP_TRG_COM_IRQHandler �е���
{
	Get_ADC_Avg_Hist();
	Get_ADC_Symbol();
}

//��ʾ�����Բ��� 0.5sˢ��һ��
void tim14_interrupt_handler(void)
{
	OLED_Print(); //��ӡ����������Ϣ
	static bool io_state = GPIO_LOW;	// ״̬��־
	gpio_set(D7, io_state);		    	// ����D7״̬
	gpio_set(A4, io_state);		    	// ����A4״̬
	io_state = !io_state;				// ��ת״̬��־
}





