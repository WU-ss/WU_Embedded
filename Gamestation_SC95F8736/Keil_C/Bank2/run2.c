#include "run2.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "stdlib.h" 
#include "Key.h"

int left_limit2 = 0;
int right_limit2= 128;
int up_limit2 = 42;
int down_limit2 = 128;

//根据按键更改飞机姿态
void switch_both_act(int8_t my_plane[2],int8_t my_buttles[10][2],int8_t his_plane[2],int8_t his_buttles[10][2]){
	int i=0;
	int key2 = KEY_Scan(1);
	//清除之前所画
	Lcd_Clearsome(my_plane[0]-16,my_plane[1]-16,my_plane[0]+16,my_plane[1]+16,BACK_COLOR);
	Lcd_Clearsome(his_plane[0]-16,his_plane[1]-16,his_plane[0]+16,his_plane[1]+16,BACK_COLOR);
	switch(key2)
		{
			// right
			case R_PRES:
				if(my_plane[0]+10 < right_limit2 - 15)
				{
					my_plane[0] = my_plane[0]+10;
				}
				UART0_SendData8(R_PRES);
				break;
			
			//left
			case L_PRES:
				if(my_plane[0]-10 > left_limit2 + 15)
				{
					my_plane[0] = my_plane[0]-10;
				}
				UART0_SendData8(L_PRES);
				break;
			
			// attack
			case KEY_X_PRES:				
				for(i=0; i<10; i++)
				{
					if(my_buttles[i][0] == 0)
					{
						my_buttles[i][0] = my_plane[0];
						my_buttles[i][1] = my_plane[1]-15;
						break;	
					}
				}
				UART0_SendData8(KEY_X_PRES);
				break;
			default:
				UART0_SendData8(8); //不是设定的任何一种按键
				break;			
		} 
	switch(rev_key)
		{
			// right
			case R_PRES:
				if(his_plane[0]+10 < right_limit2 - 15)
				{
					his_plane[0] = his_plane[0]+10;
				}
				break;
			
			//left
			case L_PRES:
				if(his_plane[0]-10 > left_limit2 + 15)
				{
					his_plane[0] = his_plane[0]-10;
				}
				break;
			
			// attack
			case KEY_X_PRES:				
				for(i=0; i<10; i++)
				{
					if(his_buttles[i][0] == 0)
					{
						his_buttles[i][0] = his_plane[0];
						his_buttles[i][1] = his_plane[1]+15;
						break;	
					}
				}
				break;
			default:
				break;			
		} 
}

void update_both_buttles(int8_t my_buttles[10][2],int8_t his_buttles[10][2]){
	int i=0;	
	for(i=0; i<10; i++){
		if(my_buttles[i][0] != 0){
			//清除之前所画
			Lcd_Clearsome(my_buttles[i][0]-3,my_buttles[i][1]-3,my_buttles[i][0]+3,my_buttles[i][1]+3,BACK_COLOR);
			
			my_buttles[i][1] = my_buttles[i][1] - 3;
			
			//当到达边界时销毁
			if(my_buttles[i][1] < 18){				
				my_buttles[i][0] = 0;
				my_buttles[i][1] = 0;
			}
		}
	}
	
	for(i=0; i<10; i++){
		if(his_buttles[i][0] != 0){
			//清除之前所画
			Lcd_Clearsome(his_buttles[i][0]-3,his_buttles[i][1]-3,his_buttles[i][0]+3,his_buttles[i][1]+3,BACK_COLOR);
			
			his_buttles[i][1] = his_buttles[i][1] + 3;
			
			//当到达边界时销毁
			if(his_buttles[i][1] > 110){				
				his_buttles[i][0] = 0;
				his_buttles[i][1] = 0;
			}
		}
	}
	
}

int check_my_buttles_to_his_plane_collide(int8_t my_buttles[10][2], int8_t his_plane[2]){
	int j=0;

	for(j=0; j<10; j++){
	//碰撞检测
	if(abs(my_buttles[j][0] - his_plane[0]) <= 15){
		if(abs(my_buttles[j][1] - his_plane[1]) <= 15){
			my_buttles[j][0] = 0;
			my_buttles[j][1] = 0;
			return 1;
			}
		}
	}
	return 0;
}

int check_his_buttles_to_my_plane_collide(int8_t his_buttles[10][2], int8_t my_plane[2]){
	int j=0;
	
	for(j=0; j<10; j++){
	//碰撞检测
	if(abs(his_buttles[j][0] - my_plane[0]) <= 15){
		if(abs(his_buttles[j][1] - my_plane[1]) <= 15){
			his_buttles[j][0] = 0;
			his_buttles[j][1] = 0;
			return 1;
			}
		}
	}
	return 0;
}
