#include "headfile.h"
#include "ADC.h"

u16 Straight_cnt=0;      //ֱ����־λ�������Ƶ�5�ж�Ϊֱ����
u8 Straight_flag=1;    //ֱ����־λ
u8 Circle_flag=0;      //�����־λ
u8 Roundabout_flag=0;  //������־λ
u8 Roundabout_flag_order=0;  //����������־λ ��ʾ���ǵڼ��ξ��������Ľ���� =1��һ�ξ��� =2�ڶ��ξ���......
u8 Sancha_flag=0;      //����·��־λ 
u8 Sancha_flag_order=0;		//����·������־λ ��ʾ���ǵڼ��ξ�������Ľ���� =1��һ�ξ��� =2�ڶ��ξ���

void Straight_Detect(void) //ֱ�����
{
	if(dif_sum<0.2&&dif_sum>-0.2)  //��������ֵ�ɵ��Եó�
	{
		Straight_cnt++;
	}
	else
	{
		Straight_cnt=0;
		Straight_flag=0;
	}
	if(Straight_cnt>5)   //����5�β����ֵ��(-0.2,0.2)�ڣ����ж�Ϊ��ֱ��
	{
		Straight_flag=1;
		Circle_flag=0;
	}
}

void Circle_Detect(void) //������
{
	if(dif_sum>0.6 || dif_sum<-0.6) //��������ֵ�ɵ��Եó�
	{
		Straight_flag=0;
		Circle_flag=1;
	}
}

void Roundabout_Detect(void) //�������
{
	//if(ADC_Avg[1]>3000 && ADC_Avg[0]>3200 && ADC_Avg[2]>3000)
	if(ADC_Avg[0]>3400&&ADC_Avg[1]>3400&&ADC_Avg[2]>3400) //��������ֵ�ɵ��Եó�
	{
		Roundabout_flag=1;
	}
}

void Sancha_Detect(void) //����·���
{

	if(ADC_Avg[1]<1000 && ADC_Avg[0]>3000 && ADC_Avg[2]>3000) //��������ֵ�ɵ��Եó�
	{
		Sancha_flag=1;
	}
}

void Path_Detect(void) //·�����
{
	Sancha_Detect();
	Roundabout_Detect();
	Straight_Detect();
	Circle_Detect();
}
