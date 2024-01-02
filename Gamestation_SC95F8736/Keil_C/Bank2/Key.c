#include "Key.h"

//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//返回值：
//0，没有任何按键按下 
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按
	SCD_Joystick_GetPosition();
	if(key_up&&(KEY_Select==0||KEY_Start==0||KEY_X==0||X_POS==0||X_POS==2||KEY_B==0||KEY_A==0||KEY_Y==0))
	{
		Delay_ms(10);//去抖动
		SCD_Joystick_GetPosition();		
		key_up=0;
		if(KEY_Select==0)return KEY_Select_PRES;
		else if(KEY_Start==0)return KEY_Start_PRES;
		else if(KEY_X==0)return KEY_X_PRES;
		else if(KEY_B==0)return KEY_B_PRES;
		else if(KEY_A==0)return KEY_A_PRES;
		else if(KEY_Y==0)return KEY_Y_PRES;
		else if(X_POS==0) return R_PRES;
		else if(X_POS==2) return L_PRES;
		else if(Y_POS==0) return U_PRES;
		else if(Y_POS==2) return D_PRES;
	}else if(KEY_Select==1&&KEY_Start==1&&KEY_X==1)key_up=1; 	     
	return 0;// 无按键按下
}

//非连续模式下 检测按键Start是否按下
void KEYStart_to_skip(void){
	while(1){
		if(KEY_Scan(0) == KEY_Start){
		  break;
		}
		else{
			Delay_ms(10);
		}
	}
}