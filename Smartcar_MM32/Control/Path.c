#include "headfile.h"
#include "ADC.h"

u16 Straight_cnt=0;      //直道标志位计数（计到5判定为直道）
u8 Straight_flag=1;    //直道标志位
u8 Circle_flag=0;      //弯道标志位
u8 Roundabout_flag=0;  //环岛标志位
u8 Roundabout_flag_order=0;  //环岛次数标志位 表示这是第几次经过环岛的交叉点 =1第一次经过 =2第二次经过......
u8 Sancha_flag=0;      //三叉路标志位 
u8 Sancha_flag_order=0;		//三叉路次数标志位 表示这是第几次经过三叉的交叉点 =1第一次经过 =2第二次经过

void Straight_Detect(void) //直道检测
{
	if(dif_sum<0.2&&dif_sum>-0.2)  //！！！该值由调试得出
	{
		Straight_cnt++;
	}
	else
	{
		Straight_cnt=0;
		Straight_flag=0;
	}
	if(Straight_cnt>5)   //连续5次差除和值在(-0.2,0.2)内，则判断为在直道
	{
		Straight_flag=1;
		Circle_flag=0;
	}
}

void Circle_Detect(void) //弯道检测
{
	if(dif_sum>0.6 || dif_sum<-0.6) //！！！该值由调试得出
	{
		Straight_flag=0;
		Circle_flag=1;
	}
}

void Roundabout_Detect(void) //环岛检测
{
	//if(ADC_Avg[1]>3000 && ADC_Avg[0]>3200 && ADC_Avg[2]>3000)
	if(ADC_Avg[0]>3400&&ADC_Avg[1]>3400&&ADC_Avg[2]>3400) //！！！该值由调试得出
	{
		Roundabout_flag=1;
	}
}

void Sancha_Detect(void) //三叉路检测
{

	if(ADC_Avg[1]<1000 && ADC_Avg[0]>3000 && ADC_Avg[2]>3000) //！！！该值由调试得出
	{
		Sancha_flag=1;
	}
}

void Path_Detect(void) //路径检测
{
	Sancha_Detect();
	Roundabout_Detect();
	Straight_Detect();
	Circle_Detect();
}
