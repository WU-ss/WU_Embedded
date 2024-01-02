#include "draw.h"
#include "basic_draw.h"
#include "basic_draw.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "stdlib.h"
#include "stdio.h"

char s[2] = {0};

//设置开始页面
void draw_start_page(void){
	Gui_DrawFont_GBK24(30,20,GRAY0,BACK_COLOR,"SPACE");
	Gui_DrawFont_GBK24(72,40,GRAY0,BACK_COLOR,"WAR");
	Gui_DrawFont_GBK24(20,70,GRAY1,BACK_COLOR,"Press Key");
	DisplayButtonUp(98,70,120,86);
	
	draw_my_plane(14,113);
	draw_my_plane(64,113);
	draw_my_plane(114,113);	
}

//设置基础界面
void init_play_interface(void){
	Lcd_Clear(BACK_COLOR);
	Gui_DrawFont_GBK16(0,0,GRAY0,BACK_COLOR,"SCROE");	
	Gui_DrawFont_GBK16(90,0,GRAY0,BACK_COLOR,"LIFE");
}

//设置结束页面
void draw_end(int8_t *score,int8_t *score_2, int8_t *score_3){
	Lcd_Clear(BACK_COLOR);
	
	Gui_DrawFont_GBK16(30,20,GRAY0,BACK_COLOR,"GAME OVER");
	Gui_DrawFont_GBK16(10,40,GRAY0,BACK_COLOR,"My SCORE:");
	sprintf(s, "%d", (int)*score);
	Gui_DrawFont_GBK24(90,40,POINT_COLOR,BACK_COLOR,s);
	//LCD_ShowxNum(100,170,*score_2,4,24,"0");
	if(*score_2 == 0 && *score_3 == 0){
		*score_2 = *score;
	}else if(*score_2 != 0 && *score_3 == 0){
		*score_3 = *score_2;
		*score_2 = *score;
		Gui_DrawFont_GBK16(10,40,GRAY0,BACK_COLOR,"P2 SCORE:");
//		LCD_ShowxNum(100,170,*score_2,4,24,0);	
	}
	*score = 0;
	
	draw_my_plane(14,113);
	draw_my_plane(64,113);
	draw_my_plane(114,113);	
	
}

//设置标头
void draw_play_title(int8_t score, int8_t life){
	
	int i=0;
	int start_x = 95;
	Lcd_Clearsome(0,113,128,128,BACK_COLOR);
	Lcd_Clearsome(start_x,20-3,128,20+4,BACK_COLOR);
	sprintf(s, "%d", (int)score);
	Gui_DrawFont_GBK24(50,0,POINT_COLOR,BACK_COLOR,s);
//	Gui_DrawFont_Num32(40,0,POINT_COLOR,BACK_COLOR,score);		//显示分数
	for(i=0;i<life;i++)
	{
		Gui_Circle(start_x+10*i,20,3,RED);
	}
}

void draw_all_my_buttles(int8_t my_buttles[20][2]){
	int i =0;
	for(i=0; i<20; i++){
		if(my_buttles[i][0] != 0){
			draw_my_bullet(my_buttles[i][0],my_buttles[i][1]);
		}
	}
}

void draw_all_enemy_planes(int8_t enemy_planes[10][2]){
	int i = 0;
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] != 0){
			draw_enemy_plane(enemy_planes[i][0],enemy_planes[i][1]);
		}
	}
}

void draw_all_enemy_buttles(int8_t enemy_buttles[20][2]){
	int i =0;
	for(i=0; i<20; i++){
		if(enemy_buttles[i][0] != 0){
			draw_enemy_bullet(enemy_buttles[i][0],enemy_buttles[i][1]);
		}
	}
}

void draw_both_buttles(int8_t my_buttles[10][2],int8_t his_buttles[10][2]){
	int i =0;
	for(i=0; i<10; i++){
		if(my_buttles[i][0] != 0){
			draw_my_bullet(my_buttles[i][0],my_buttles[i][1]);
		}
		if(his_buttles[i][0] != 0){
			draw_my_bullet(his_buttles[i][0],his_buttles[i][1]);
		}
	}
}

void draw_play_all(int8_t score,int8_t life, int8_t my_plane[2], int8_t my_buttles[20][2], int8_t boss[2], int8_t enemy_planes[10][2], int8_t enemy_buttles[20][2]){
	draw_play_title(score,life);
	
	draw_my_plane(my_plane[0],my_plane[1]);
	draw_all_my_buttles(my_buttles);
	if(boss[0]!= 0){
		draw_boss(boss[0],boss[1]);
	}
	draw_all_enemy_planes(enemy_planes);
	draw_all_enemy_buttles(enemy_buttles);
}
