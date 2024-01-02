#include "headfile.h"
#include "ADC.h"
#include "Path.h"

#define filter 0.6f //�궨���Ȩ΢�ֺ͵�ϵ��

uint16 Left_Defult=20100; //����Ĭ��ת��
uint16 Right_Defult=25000; //����Ĭ��ת��
//uint16 Left_Defult=21100; //����Ĭ��ת��
//uint16 Right_Defult=27000; //����Ĭ��ת��

uint16 Left_Roundabout=40000; //���ֹ����������ת��		��������ֵ�ɵ��Եó�
uint16 Right_Roundabout=38000; //���ֹ����������ת��	��������ֵ�ɵ��Եó�

uint16 Left_Sancha=17100; //���ֹ����潻���ת��		��������ֵ�ɵ��Եó�
uint16 Right_Sancha=10000; //���ֹ����潻���ת��	��������ֵ�ɵ��Եó�
uint16 sancha=10000;
u16 Limit=10000; //����ת��

float Kp_S=5000; //ֱ�� PD�ı�������P��ϵ��		��������ֵ�ɵ��Եó�
float Kd_S=5000; //ֱ�� PD�Ļ��ֻ���D��ϵ��		��������ֵ�ɵ��Եó�
float Kp_C=6800; //��� PD�ı�������P��ϵ��	��������ֵ�ɵ��Եó�
float Kd_C=6000;  //��� PD�Ļ��ֻ���D��ϵ��	��������ֵ�ɵ��Եó�

float L_PWM; //����PWM
float R_PWM; //����PWM
typedef struct PIDStruct
{
float Kp;
float Ki;
float Kd;
float Err;			//��ֵ
float Err_last;
float DErr;			//��ֵ�仯��
float DErr_last;	
float OutSpeed_L;    //��������ٶ�
float OutSpeed_R;    //��������ٶ�
}PID_struct;

PID_struct PDstru={0};

float DErr_sum; //�����ļ�Ȩ���΢��(�ۺϿ���DErr��DErr_last)

void PD(float err,float autal_Kp,float autal_Kd) //�����PD����
{
	float L_Compensate;  //����ֵ
	
	PDstru.Kp=autal_Kp;
	PDstru.Kd=autal_Kd;
	PDstru.Err=err;
	PDstru.DErr=PDstru.Err-PDstru.Err_last;
	PDstru.DErr*=100; //��ַŴ�20��
	
	DErr_sum=PDstru.DErr*filter+PDstru.DErr_last*(1-filter); //�������ļ�Ȩ���΢��
	
	L_Compensate=PDstru.Kp*PDstru.Err+PDstru.Kd*DErr_sum; //������ٲ���ֵ
	
	PDstru.OutSpeed_L=Left_Defult-L_Compensate; //�����������ת��
	PDstru.OutSpeed_R=Right_Defult+L_Compensate; //�����������ת��
	
	L_PWM=PDstru.OutSpeed_L;
	R_PWM=PDstru.OutSpeed_R;
	
	//��ֹ�������/�ٶ�̫��
	if(L_PWM>Left_Defult+Limit) L_PWM=Left_Defult+Limit;
	else if(L_PWM<Left_Defult-Limit) L_PWM=Left_Defult-Limit;
	if(R_PWM>Right_Defult+Limit) R_PWM=Right_Defult+Limit;
	else if(R_PWM<Right_Defult-Limit) R_PWM=Right_Defult-Limit;
	
	//�洢�˴εĲ�ֵ��Ϊ��һ�εĲ�ֵ
	PDstru.Err_last=PDstru.Err;
	PDstru.DErr_last=PDstru.DErr;
}

void PD_Control(void) //����Ŀ��Ƴ���
{
//	if(ADC_Avg_GuiYi[0]<0.5&&ADC_Avg_GuiYi[1]<0.5&&ADC_Avg_GuiYi[2]<0.5) //��С��ƫ������
//	{
//		pwm_duty_updata(TIM_2,TIM_2_CH1_A11,0);  //����ͣת
//		pwm_duty_updata(TIM_3,TIM_3_CH4_C09,0);  //�ҵ��ͣת
//	}
	if(Roundabout_flag==1)
	{
//		Get_ADC();
//		Get_ADC_Avg_Hist();
//		Get_ADC_Symbol();
		gpio_set(B8, 1);		    	// ����D7״̬
		Roundabout_flag_order++; //����������������1
		switch(Roundabout_flag_order)
		{
			case 1:
				pwm_duty_updata(TIM_2,TIM_2_CH1_A11,13500);	 //�����ҵ��
				pwm_duty_updata(TIM_3,TIM_3_CH4_C09,22000);  //��������	
				systick_delay_ms(1200);				
				pwm_duty_updata(TIM_2,TIM_2_CH1_A11,24000);	 //�����ҵ��
				pwm_duty_updata(TIM_3,TIM_3_CH4_C09,34000);  //��������				
				systick_delay_ms(1800);	//ǿ�ƴ���뻷 ��������ֵ�ɵ��Եó�
				gpio_set(B8, 0);// ����D7״̬
				for(int i=0;i<300;i++)
				{
					gpio_set(B8, 1);		    	// ����D7״̬
					ADC_Handle(); //����õ�ADC����
					Roundabout_flag=0;
					Straight_Detect();
					Circle_Detect();
					PD_Control();
				}
				gpio_set(B8, 0);		    	// ����D7״̬
				break;
					
			case 2:
				pwm_duty_updata(TIM_2,TIM_2_CH1_A11,25000);	 //�����ҵ��
				pwm_duty_updata(TIM_3,TIM_3_CH4_C09,32000);  //��������				
				systick_delay_ms(500);
//				pwm_duty_updata(TIM_2,TIM_2_CH1_A11,14000);	 //��������
//				pwm_duty_updata(TIM_3,TIM_3_CH4_C09,14000);  //�����ҵ��
//				systick_delay_ms(1000);	//ǿ��ֱ�г��� ��������ֵ�ɵ��Եó�
				break;
		}
		Roundabout_flag=0;
		if(Roundabout_flag_order==2)
		{
			Roundabout_flag_order=0;
			gpio_set(B8, 1);
			for(int i=0;i<30000;i++)
			{
				gpio_set(B8, 0);// ����D7״̬
				ADC_Handle(); //����õ�ADC����

				Straight_Detect();
				Circle_Detect();
				PD_Control();
			}
			gpio_set(B8, 0);// ����D7״̬
		}
	}

	if(Sancha_flag)
	{
		Sancha_flag_order++;
		switch(Sancha_flag_order)
		{
			case 1:
				gpio_set(B8, 1);
				pwm_duty_updata(TIM_2,TIM_2_CH1_A11,24000);	 //�����ҵ��
				pwm_duty_updata(TIM_3,TIM_3_CH4_C09,45000);  //��������				
				systick_delay_ms(350);	//ǿ�ƴ�������� ��������ֵ�ɵ��Եó�
				gpio_set(B8, 0);		    	// ����D7״̬
				break;		
		}
		Sancha_flag=0;
	}
	if(Straight_flag) //��С����ֱ��
	{
		PD(dif_sum,Kp_S,Kd_S);
		pwm_duty_updata(TIM_2,TIM_2_CH1_A11,(uint32)L_PWM);  //��������
		pwm_duty_updata(TIM_3,TIM_3_CH4_C09,(uint32)R_PWM);  //�����ҵ��
	}
	if(Circle_flag) //��С�������
	{
		PD(dif_sum,Kp_C,Kd_C);
		pwm_duty_updata(TIM_2,TIM_2_CH1_A11,(uint32)L_PWM);  //��������
		pwm_duty_updata(TIM_3,TIM_3_CH4_C09,(uint32)R_PWM);  //�����ҵ��
	}
}
