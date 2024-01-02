#include "headfile.h"
#include "ADC.h"
#include "Path.h"

#define filter 0.6f //宏定义加权微分和的系数

uint16 Left_Defult=20100; //右轮默认转速
uint16 Right_Defult=25000; //左轮默认转速
//uint16 Left_Defult=21100; //右轮默认转速
//uint16 Right_Defult=27000; //左轮默认转速

uint16 Left_Roundabout=40000; //左轮过环岛交叉点转速		！！！该值由调试得出
uint16 Right_Roundabout=38000; //右轮过环岛交叉点转速	！！！该值由调试得出

uint16 Left_Sancha=17100; //左轮过三叉交叉点转速		！！！该值由调试得出
uint16 Right_Sancha=10000; //右轮过三叉交叉点转速	！！！该值由调试得出
uint16 sancha=10000;
u16 Limit=10000; //限制转速

float Kp_S=5000; //直道 PD的比例环节P的系数		！！！该值由调试得出
float Kd_S=5000; //直道 PD的积分环节D的系数		！！！该值由调试得出
float Kp_C=6800; //弯道 PD的比例环节P的系数	！！！该值由调试得出
float Kd_C=6000;  //弯道 PD的积分环节D的系数	！！！该值由调试得出

float L_PWM; //左轮PWM
float R_PWM; //右轮PWM
typedef struct PIDStruct
{
float Kp;
float Ki;
float Kd;
float Err;			//差值
float Err_last;
float DErr;			//差值变化率
float DErr_last;	
float OutSpeed_L;    //左轮输出速度
float OutSpeed_R;    //右轮输出速度
}PID_struct;

PID_struct PDstru={0};

float DErr_sum; //左电机的加权误差微分(综合考量DErr与DErr_last)

void PD(float err,float autal_Kp,float autal_Kd) //电机的PD控制
{
	float L_Compensate;  //补偿值
	
	PDstru.Kp=autal_Kp;
	PDstru.Kd=autal_Kd;
	PDstru.Err=err;
	PDstru.DErr=PDstru.Err-PDstru.Err_last;
	PDstru.DErr*=100; //差分放大20倍
	
	DErr_sum=PDstru.DErr*filter+PDstru.DErr_last*(1-filter); //计算电机的加权误差微分
	
	L_Compensate=PDstru.Kp*PDstru.Err+PDstru.Kd*DErr_sum; //计算差速补偿值
	
	PDstru.OutSpeed_L=Left_Defult-L_Compensate; //计算左轮输出转速
	PDstru.OutSpeed_R=Right_Defult+L_Compensate; //计算右轮输出转速
	
	L_PWM=PDstru.OutSpeed_L;
	R_PWM=PDstru.OutSpeed_R;
	
	//防止电机过速/速度太低
	if(L_PWM>Left_Defult+Limit) L_PWM=Left_Defult+Limit;
	else if(L_PWM<Left_Defult-Limit) L_PWM=Left_Defult-Limit;
	if(R_PWM>Right_Defult+Limit) R_PWM=Right_Defult+Limit;
	else if(R_PWM<Right_Defult-Limit) R_PWM=Right_Defult-Limit;
	
	//存储此次的差值作为上一次的差值
	PDstru.Err_last=PDstru.Err;
	PDstru.DErr_last=PDstru.DErr;
}

void PD_Control(void) //电机的控制程序
{
//	if(ADC_Avg_GuiYi[0]<0.5&&ADC_Avg_GuiYi[1]<0.5&&ADC_Avg_GuiYi[2]<0.5) //若小车偏离赛道
//	{
//		pwm_duty_updata(TIM_2,TIM_2_CH1_A11,0);  //左电机停转
//		pwm_duty_updata(TIM_3,TIM_3_CH4_C09,0);  //右电机停转
//	}
	if(Roundabout_flag==1)
	{
//		Get_ADC();
//		Get_ADC_Avg_Hist();
//		Get_ADC_Symbol();
		gpio_set(B8, 1);		    	// 更新D7状态
		Roundabout_flag_order++; //过环岛交叉点次数加1
		switch(Roundabout_flag_order)
		{
			case 1:
				pwm_duty_updata(TIM_2,TIM_2_CH1_A11,13500);	 //更新右电机
				pwm_duty_updata(TIM_3,TIM_3_CH4_C09,22000);  //更新左电机	
				systick_delay_ms(1200);				
				pwm_duty_updata(TIM_2,TIM_2_CH1_A11,24000);	 //更新右电机
				pwm_duty_updata(TIM_3,TIM_3_CH4_C09,34000);  //更新左电机				
				systick_delay_ms(1800);	//强制打角入环 ！！！该值由调试得出
				gpio_set(B8, 0);// 更新D7状态
				for(int i=0;i<300;i++)
				{
					gpio_set(B8, 1);		    	// 更新D7状态
					ADC_Handle(); //处理得到ADC数据
					Roundabout_flag=0;
					Straight_Detect();
					Circle_Detect();
					PD_Control();
				}
				gpio_set(B8, 0);		    	// 更新D7状态
				break;
					
			case 2:
				pwm_duty_updata(TIM_2,TIM_2_CH1_A11,25000);	 //更新右电机
				pwm_duty_updata(TIM_3,TIM_3_CH4_C09,32000);  //更新左电机				
				systick_delay_ms(500);
//				pwm_duty_updata(TIM_2,TIM_2_CH1_A11,14000);	 //更新左电机
//				pwm_duty_updata(TIM_3,TIM_3_CH4_C09,14000);  //更新右电机
//				systick_delay_ms(1000);	//强制直行出环 ！！！该值由调试得出
				break;
		}
		Roundabout_flag=0;
		if(Roundabout_flag_order==2)
		{
			Roundabout_flag_order=0;
			gpio_set(B8, 1);
			for(int i=0;i<30000;i++)
			{
				gpio_set(B8, 0);// 更新D7状态
				ADC_Handle(); //处理得到ADC数据

				Straight_Detect();
				Circle_Detect();
				PD_Control();
			}
			gpio_set(B8, 0);// 更新D7状态
		}
	}

	if(Sancha_flag)
	{
		Sancha_flag_order++;
		switch(Sancha_flag_order)
		{
			case 1:
				gpio_set(B8, 1);
				pwm_duty_updata(TIM_2,TIM_2_CH1_A11,24000);	 //更新右电机
				pwm_duty_updata(TIM_3,TIM_3_CH4_C09,45000);  //更新左电机				
				systick_delay_ms(350);	//强制打脚入三叉 ！！！该值由调试得出
				gpio_set(B8, 0);		    	// 更新D7状态
				break;		
		}
		Sancha_flag=0;
	}
	if(Straight_flag) //若小车走直道
	{
		PD(dif_sum,Kp_S,Kd_S);
		pwm_duty_updata(TIM_2,TIM_2_CH1_A11,(uint32)L_PWM);  //更新左电机
		pwm_duty_updata(TIM_3,TIM_3_CH4_C09,(uint32)R_PWM);  //更新右电机
	}
	if(Circle_flag) //若小车走弯道
	{
		PD(dif_sum,Kp_C,Kd_C);
		pwm_duty_updata(TIM_2,TIM_2_CH1_A11,(uint32)L_PWM);  //更新左电机
		pwm_duty_updata(TIM_3,TIM_3_CH4_C09,(uint32)R_PWM);  //更新右电机
	}
}
