#ifndef __KEY_H
#define __KEY_H

#include "SC_Init.h"	// MCU initialization header file, including all firmware library header files
#include "..\Drivers\SCDriver_Joystick\H\SCDriver_Joystick.h"
#include "Delay.h"

#define X_POS  SCD_Joystick_PosY
#define Y_POS  SCD_Joystick_PosX

#define KEY_Select  GPIO_ReadPin(GPIO2,GPIO_PIN_2)
#define KEY_Start	GPIO_ReadPin(GPIO2,GPIO_PIN_3)
#define KEY_X		GPIO_ReadPin(GPIO1,GPIO_PIN_6)
#define KEY_B		GPIO_ReadPin(GPIO1,GPIO_PIN_5)
#define KEY_A		GPIO_ReadPin(GPIO1,GPIO_PIN_4)
#define KEY_Y		GPIO_ReadPin(GPIO1,GPIO_PIN_7)
 
#define KEY_Select_PRES	1		  
#define KEY_Start_PRES	2		
#define KEY_X_PRES		3
#define	L_PRES			4
#define	R_PRES			5
#define	U_PRES			6
#define	D_PRES			7
#define KEY_B_PRES		8
#define KEY_A_PRES		9
#define KEY_Y_PRES		10


u8 KEY_Scan(u8 mode);  	//按键扫描函数
void KEYStart_to_skip(void); //判断按键0是否按下

#endif
