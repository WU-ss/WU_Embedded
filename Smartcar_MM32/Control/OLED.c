#include "headfile.h"
#include "ADC.h"
#include "Path.h"

void OLED_Print(void)
{
	//显示左、中、右的ADC采集值
	oled_printf_int32(0,0,ADC_Avg[0],4);
	oled_printf_int32(32,0,ADC_Avg[1],4);
	oled_printf_int32(64,0,ADC_Avg[2],4);
	
	//显示左、中、右的ADC归一化后的值
	oled_printf_int32(0,1,ADC_Avg_GuiYi[0],4);
	oled_printf_int32(32,1,ADC_Avg_GuiYi[1],4);
	oled_printf_int32(64,1,ADC_Avg_GuiYi[2],4);

	//显示差和比
	oled_printf_float(0,2,dif_sum,1,3);
	
	//显示左、中、右的ADC值的变化趋势
	oled_printf_int32(0,3,L_Cap,1);
	oled_printf_int32(32,3,M_Cap,1);
	oled_printf_int32(64,3,R_Cap,1);
	
	//显示ADC_Symbol_z的值
//	oled_printf_int32(0,3,ADC_Symbol_z[0],1);
//	oled_printf_int32(32,3,ADC_Symbol_z[1],1);
//	oled_printf_int32(64,3,ADC_Symbol_z[2],1);
	
	//显示ADC_Avg_Hist[0]的值
//	oled_printf_int32(0,4,ADC_Avg_Hist[0][1],4);
//	oled_printf_int32(32,4,ADC_Avg_Hist[0][2],4);
//	oled_printf_int32(64,4,ADC_Avg_Hist[0][3],4);
//	oled_printf_int32(96,4,ADC_Avg_Hist[0][4],4);

	//显示标志位判断
	if(Straight_flag==1)
	{
		oled_p8x16str(0,4,"Straight");
	}
	else if(Circle_flag==1)
	{
		oled_p8x16str(0,4,"Circle  ");
	}
	
//	oled_uint16(0,6,Roundabout_flag_order);
	oled_uint16(0,6,Roundabout_flag_order);
	oled_uint16(0,7,Sancha_flag_order);

}
