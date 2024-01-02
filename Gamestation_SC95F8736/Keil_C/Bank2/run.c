#include "run.h"
#include "basic_draw.h"
#include "draw.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "stdlib.h" 
#include "Delay.h"
#include "Key.h"

int left_limit = 0;
int right_limit = 128;
int up_limit = 42;
int down_limit = 128;

void generate_enemy_planes(int8_t level, int8_t enemy_planes[10][2]){
	int i = 0;
	
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] == 0){
			if(i < level*3){
				if(rand()%100 < level + 3){
					enemy_planes[i][0] = rand()%100 + 15;  //随机飞机的横坐标
					enemy_planes[i][1] = 30;               //随机飞机的纵坐标
				}
			}
			break;
		}
	}
}

void switch_my_act(int8_t my_plane[2],int8_t my_buttles[20][2]){
	int i=0;
	int key = KEY_Scan(1);
	Lcd_Clearsome(my_plane[0]-14,my_plane[1]-14,my_plane[0]+14,my_plane[1]+14,BACK_COLOR);
	switch(key)
		{
			case R_PRES:
				if(my_plane[0]+10 < right_limit - 10){
				my_plane[0] = my_plane[0]+10;
			}
			
				break;
			
			case L_PRES:
				if(my_plane[0]-10 > left_limit + 10){
				my_plane[0] = my_plane[0]-10;
			}
				break;
			
			case KEY_X_PRES:				
				for(i=0; i<20; i++){
				if(my_buttles[i][0] == 0){
					my_buttles[i][0] = my_plane[0];
					my_buttles[i][1] = my_plane[1]-15;
					break;	
				}
			}
				break;
			default:
				break;
					
		} 
}	
	

void update_my_buttles(int8_t my_buttles[20][2]){
	int i=0;
	for(i=0; i<20; i++){
		if(my_buttles[i][0] != 0){
			Lcd_Clearsome(my_buttles[i][0]-3,my_buttles[i][1]-3,my_buttles[i][0]+3,my_buttles[i][1]+3,BACK_COLOR);
			
			my_buttles[i][1] = my_buttles[i][1] - 3;
			if(my_buttles[i][1] < 42){				
				my_buttles[i][0] = 0;
				my_buttles[i][1] = 0;
			}
		}
	}
	
}

void update_enemy_buttles(int8_t enemy_buttles[20][2], int8_t level){
	int i=0;
	
	for(i=0; i<20; i++){
		if(enemy_buttles[i][0] != 0){
			Lcd_Clearsome(enemy_buttles[i][0]-2,enemy_buttles[i][1]-2,	enemy_buttles[i][0]+2,enemy_buttles[i][1]+2,BACK_COLOR);
			enemy_buttles[i][1] = enemy_buttles[i][1] + level + 1;

			if(enemy_buttles[i][1] > 126){				
				enemy_buttles[i][0] = 0;
				enemy_buttles[i][1] = 0;
		
			}
		}
	}
}

void update_enemy_planes(int8_t enemy_planes[10][2], int8_t level){
	int i=0;
	
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] != 0){
			Lcd_Clearsome(enemy_planes[i][0]-8,enemy_planes[i][1]-8,	enemy_planes[i][0]+8,enemy_planes[i][1]+8,BACK_COLOR);	
			enemy_planes[i][1] = enemy_planes[i][1] + level;

			if(enemy_planes[i][1] > 100){			
				enemy_planes[i][0] = 0;
				enemy_planes[i][1] = 0;
			}
		}
	}
}


void check_my_plane_to_enemy_plane_collide(int8_t *score,int8_t *life,int8_t my_plane[2],int8_t enemy_planes[10][2]){
	int i=0;
	int temp=0;
	
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] != 0){
			if(abs(enemy_planes[i][0] - my_plane[0]) <= 22){
				if(abs(enemy_planes[i][1] - my_plane[1]) <= 22){
					Lcd_Clearsome(my_plane[0]-14,my_plane[1]-14,my_plane[0]+14,my_plane[1]+14,BACK_COLOR);
					Lcd_Clearsome(enemy_planes[i][0]-8,enemy_planes[i][1]-8,enemy_planes[i][0]+8,enemy_planes[i][1]+8,BACK_COLOR);
				
					my_plane[0] = 64;
					my_plane[1] = 113;
					
					enemy_planes[i][0] = 0;
					enemy_planes[i][1] = 0;
					
					temp = (*score);
					(*score) = temp+1;
					
					temp = (*life);
					(*life) = temp-1;
					
					Delay_ms(100);
					
					break;
				}
			}
		}
	}
}


void check_my_buttles_to_enemy_plane_collide(int8_t *score,int8_t my_buttles[20][2], int8_t enemy_planes[10][2]){
	int i=0;
	int j=0;
	int temp=0;
	
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] != 0){
			for(j=0; j<20; j++){
				//碰撞检测
				if(abs(my_buttles[j][0] - enemy_planes[i][0]) <= 9){
					if(abs(my_buttles[j][1] - enemy_planes[i][1]) <= 9){
						Lcd_Clearsome(enemy_planes[i][0]-8,enemy_planes[i][1]-8,enemy_planes[i][0]+8,enemy_planes[i][1]+8,BACK_COLOR);

						my_buttles[j][0] = 0;
						my_buttles[j][1] = 0;
						
						enemy_planes[i][0] = 0;
						enemy_planes[i][1] = 0;
						
						temp = (*score);
						(*score) = temp+1;
						
					    Delay_ms(100);
					
						break;
					}
				}
			}
		}
	}
}

void check_my_buttles_to_boss_collide(int8_t *score, int8_t *boss_life,int8_t my_buttles[20][2], int8_t boss[2]){
	int i = 0;
	int temp = 0;
	for(i=0; i<20; i++){
		if(my_buttles[i][0] != 0){
			if(abs(my_buttles[i][0] - boss[0]) <= 21){
					if(abs(my_buttles[i][1] - boss[1]) <= 21){
						Lcd_Clearsome(boss[0]-20, boss[1] - 20, boss[0] + 20, boss[1] + 20,BACK_COLOR);
					
						my_buttles[i][0] = 0;
						my_buttles[i][1] = 0;
						
						temp = (*score);
						(*score) = temp+1;
						
						temp = (*boss_life);
						(*boss_life) = temp-1;
						
					    Delay_ms(20);
			
						break;
					}
				}
		}
	}
}


void check_my_plane_to_enemy_buttles_collide(int8_t *life,	int8_t enemy_buttles[20][2], int8_t my_plane[2]){
	int temp = 0;
	int i = 0;
	for(i=0; i<20; i++){
		if(enemy_buttles[i][0] != 0){
			if(abs(enemy_buttles[i][0] - my_plane[0]) <= 15){
					if(abs(enemy_buttles[i][1] - my_plane[1]) <= 15){
						
						my_plane[0] = 64;
					    my_plane[1] = 113;
						
						enemy_buttles[i][0] = 0;
						enemy_buttles[i][1] = 0;
						
						temp = (*life);
					    (*life) = temp-1;
						
					    Delay_ms(20);
					
					  break;
					}
		}
	}
 }
}

void generate_enemy_buttles(int8_t level, int8_t enemy_plane[10][2],  int8_t enemy_buttles[20][2]){
	int i = 0;
	int j = 0;
	for(i=0; i<10; i++){
		
		if(enemy_plane[i][0] != 0 && rand()%50 < level){
			for(j=0; j<20; j++){
				if(enemy_buttles[j][0] == 0){
					enemy_buttles[j][0] = enemy_plane[i][0];
					enemy_buttles[j][1] = enemy_plane[i][1] + 15;
					break;
				}
			}	
		}
	}
}

void generate_boss_buttles(int8_t boss[2],  int8_t enemy_buttles[20][2]){
	int i = 0;
	int j = 0;
	for(i=0; i<11; i++){
		
		if(rand()%300 < 3){
			for(j=0; j<20; j++){
				if(enemy_buttles[j][0] == 0){
					enemy_buttles[j][0] = boss[0] - 22 + i * 2;
					enemy_buttles[j][1] = boss[1] + 21;
					break;
				}
			}	
		}
	}
	for(j=0; j<20; j++)
	{
		if(enemy_buttles[j][1]>123)
		{
			enemy_buttles[j][0]=0;
			enemy_buttles[j][1]=0;
		}
	}
}

void clear_all_enemy_plane(int8_t my_plane[2],	int8_t enemy_plane[10][2], int8_t my_buttles[20][2], int8_t enemy_buttles[20][2])
{
	int i=0;
	for(i=0; i<10; i++)
	{
		enemy_plane[i][0] = 0;
		enemy_plane[i][1] = 0;
	}
	
	for(i=0; i<20; i++){
		if(my_buttles[i][0] != 0){
			my_buttles[i][0] = 0;
			my_buttles[i][1] = 0;
		}
	}
	
	for(i=0; i<20; i++){
		if(enemy_buttles[i][0] != 0){
			enemy_buttles[i][0] = 0;
			enemy_buttles[i][1] = 0;
		}
	}
	
	Lcd_Clearsome(0,25,128,128,BACK_COLOR);
	draw_my_plane(my_plane[0],my_plane[1]);
}

void move_boss(int8_t boss[2], int8_t *pace){
			
			int temp = 0;
			Lcd_Clearsome(boss[0]-23, boss[1] - 23, boss[0] + 24, boss[1] + 24,BACK_COLOR);
			
			boss[0] = boss[0] + (*pace);
			
			if(boss[0] < 30 || boss[0] > 98){				
				temp = (*pace);
				(*pace) = -temp;
			}
}
