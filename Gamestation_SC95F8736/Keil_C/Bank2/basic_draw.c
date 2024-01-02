#include "basic_draw.h"
#include "Lcd_Driver.h"
#include "GUI.h"

int cross_width = 15; 
int cross_height = 15;

int heart_width = 11;
int heart_height = 11;

int buttle_width = 3; 
int buttle_height = 3;

int star_width = 5;
int star_height = 9;
	
void draw_my_plane(int x, int y){
	Gui_DrawLine(x, y-14, x-3.8, y-1.3,POINT_COLOR);
	Gui_DrawLine(x-3.8, y-1.3, x-12.7,y+3.8,POINT_COLOR);
	Gui_DrawLine(x-12.7, y+3.8, x-14, y+8.9,POINT_COLOR);
	Gui_DrawLine(x-14, y+8.9, x-5.1, y+6.4,POINT_COLOR);
	Gui_DrawLine(x-5.1, y+6.4, x-2.5, y+8.9,POINT_COLOR);
	Gui_DrawLine(x-2.5, y+8.9, x-5.1, y+11.5,POINT_COLOR);
	Gui_DrawLine(x-5.1, y+11.5, x-5.1, y+14,POINT_COLOR);
	Gui_DrawLine(x-3.8, y+1.3, x-2.5, y+8.9,POINT_COLOR);
	Gui_DrawLine(x, y-14, x, y+14,POINT_COLOR);
	Gui_DrawLine(x, y-14, x+3.8, y-1.3,POINT_COLOR);
	Gui_DrawLine(x+3.8, y-1.3, x+12.7,y+3.8,POINT_COLOR);
	Gui_DrawLine(x+12.7, y+3.8, x+14, y+8.9,POINT_COLOR);
	Gui_DrawLine(x+14, y+8.9, x+5.1, y+6.4,POINT_COLOR);
	Gui_DrawLine(x+5.1, y+6.4, x+2.5, y+8.9,POINT_COLOR);
	Gui_DrawLine(x+2.5, y+8.9, x+5.1, y+11.5,POINT_COLOR);
	Gui_DrawLine(x+5.1, y+11.5, x+5.1, y+14,POINT_COLOR);
	Gui_DrawLine(x+3.8, y+1.3, x+2.5, y+8.9,POINT_COLOR);
	Gui_DrawLine(x-5.1, y+14, x+5.1, y+14,POINT_COLOR);
	
}

void draw_enemy_plane(int x ,int y){
	Gui_DrawLine(x, y-4, x, y+8,POINT_COLOR);
	Gui_DrawLine(x, y-4, x+4, y-8,POINT_COLOR);
	Gui_DrawLine(x, y-4, x-4, y-8,POINT_COLOR);
	Gui_DrawLine(x+4, y-8, x+8, y,POINT_COLOR);
	Gui_DrawLine(x-4, y-8, x-8, y,POINT_COLOR);
	Gui_DrawLine(x+8, y, x, y+8,POINT_COLOR);
	Gui_DrawLine(x-8, y, x, y+8,POINT_COLOR);
	Gui_DrawLine(x+4, y-8, x+4, y+4,POINT_COLOR);
	Gui_DrawLine(x-4, y-8, x-4, y+4,POINT_COLOR);
}

void draw_his_plane(int x, int y){
	Gui_DrawLine(x, y+14, x-3.8, y+1.3,POINT_COLOR);
	Gui_DrawLine(x-3.8, y+1.3, x-12.7,y-3.8,POINT_COLOR);
	Gui_DrawLine(x-12.7, y-3.8, x-14, y-8.9,POINT_COLOR);
	Gui_DrawLine(x-14, y-8.9, x-5.1, y-6.4,POINT_COLOR);
	Gui_DrawLine(x-5.1, y-6.4, x-2.5, y-8.9,POINT_COLOR);
	Gui_DrawLine(x-2.5, y-8.9, x-5.1, y-11.5,POINT_COLOR);
	Gui_DrawLine(x-5.1, y-11.5, x-5.1, y-14,POINT_COLOR);
	Gui_DrawLine(x-3.8, y-1.3, x-2.5, y-8.9,POINT_COLOR);
	Gui_DrawLine(x, y+14, x, y-14,POINT_COLOR);
	Gui_DrawLine(x, y+14, x+3.8, y+1.3,POINT_COLOR);
	Gui_DrawLine(x+3.8, y+1.3, x+12.7,y-3.8,POINT_COLOR);
	Gui_DrawLine(x+12.7, y-3.8, x+14, y-8.9,POINT_COLOR);
	Gui_DrawLine(x+14, y-8.9, x+5.1, y-6.4,POINT_COLOR);
	Gui_DrawLine(x+5.1, y-6.4, x+2.5, y-8.9,POINT_COLOR);
	Gui_DrawLine(x+2.5, y-8.9, x+5.1, y-11.5,POINT_COLOR);
	Gui_DrawLine(x+5.1, y-11.5, x+5.1, y-14,POINT_COLOR);
	Gui_DrawLine(x+3.8, y-1.3, x+2.5, y-8.9,POINT_COLOR);
	Gui_DrawLine(x-5.1, y-14, x+5.1, y-14,POINT_COLOR);
}

void draw_boss(int x, int y){
	Gui_DrawLine(x-4.4,y-17.6,x-8.8,y-22,POINT_COLOR);
	Gui_DrawLine(x-8.8,y-22,x-22,y+17.6,POINT_COLOR);
	Gui_DrawLine(x-22,y+17.6,x-17.6,y+22,POINT_COLOR);
	Gui_DrawLine(x-17.6,y+22,x-10.3,y,POINT_COLOR);
	Gui_DrawLine(x-4.4,y+13.2,x-10.3,y,POINT_COLOR);
	Gui_DrawLine(x-8.8,y+4.4,x-4.4,y-8.8,POINT_COLOR);
	Gui_DrawLine(x-4.4,y-8.8,x-8.8,y-4.4,POINT_COLOR);
	Gui_DrawLine(x-8.8,y-4.4,x-4.4,y-17.6,POINT_COLOR);
	Gui_DrawLine(x-2.2,y,x-2.2,y+8.8,POINT_COLOR);
	Gui_DrawLine(x+4.4,y-17.6,x+8.8,y-22,POINT_COLOR);
	Gui_DrawLine(x+8.8,y-22,x+22,y+17.6,POINT_COLOR);
	Gui_DrawLine(x+22,y+17.6,x+17.6,y+22,POINT_COLOR);
	Gui_DrawLine(x+17.6,y+22,x+10.3,y,POINT_COLOR);
	Gui_DrawLine(x+4.4,y+13.2,x+10.3,y,POINT_COLOR);
	Gui_DrawLine(x+8.8,y+4.4,x+4.4,y-8.8,POINT_COLOR);
	Gui_DrawLine(x+4.4,y-8.8,x+8.8,y-4.4,POINT_COLOR);
	Gui_DrawLine(x+8.8,y-4.4,x+4.4,y-17.6,POINT_COLOR);
	Gui_DrawLine(x+2.2,y,x+2.2,y+8.8,POINT_COLOR);
	Gui_DrawLine(x-4.4,y-8.8,x+4.4,y-8.8,POINT_COLOR);
	Gui_DrawLine(x+2.2,y,x-2.2,y,POINT_COLOR);
	Gui_DrawLine(x-2.2,y+8.8,x+2.2,y+8.8,POINT_COLOR);
	Gui_DrawLine(x-4.4,y+13.2,x+4.4,y+13.2,POINT_COLOR);

}


void draw_my_bullet(int x, int y){
	Gui_DrawPoint(x,y-1,POINT_COLOR);
	
	Gui_DrawPoint(x-1,y,POINT_COLOR);
	Gui_DrawPoint(x,y,POINT_COLOR);
	Gui_DrawPoint(x+1,y,POINT_COLOR);

	Gui_DrawPoint(x-1,y+1,POINT_COLOR);
	Gui_DrawPoint(x,y+1,POINT_COLOR);
	Gui_DrawPoint(x+1,y+1,POINT_COLOR);
}

void draw_enemy_bullet(int x, int y){
	Gui_DrawPoint(x-1,y-1,POINT_COLOR);
	Gui_DrawPoint(x,y-1,POINT_COLOR);
	Gui_DrawPoint(x+1,y-1,POINT_COLOR);
	
	Gui_DrawPoint(x-1,y,POINT_COLOR);
	Gui_DrawPoint(x,y,POINT_COLOR);
	Gui_DrawPoint(x+1,y,POINT_COLOR);

	Gui_DrawPoint(x,y+1,POINT_COLOR);
}

void draw_cross(int x, int y){
	Gui_DrawLine(x-cross_width/2,y-cross_height/2, x+cross_width/2,y+cross_height/2,POINT_COLOR);
	Gui_DrawLine(x-cross_width/2,y+cross_height/2, x+cross_width/2,y-cross_height/2,POINT_COLOR);
}

void draw_heart(int x, int y){
	Gui_DrawLine(x-heart_width/2,y-heart_height/2, x+heart_width/2,y+heart_height/2,POINT_COLOR);
	Gui_DrawLine(x-heart_width/2,y+heart_height/2, x+heart_width/2,y-heart_height/2,POINT_COLOR);
	
	Gui_DrawLine(x-heart_width/2,y, x+heart_width/2,y,POINT_COLOR);
	Gui_DrawLine(x,y+heart_height/2, x,y-heart_height/2,POINT_COLOR);
}


void draw_star(int x,int y){
	//竖向较长
	Gui_DrawLine(x,y-star_height/2, x,y+star_height/2,POINT_COLOR);
	//横向较短
	Gui_DrawLine(x-star_width/2,y, x+star_width/2,y,POINT_COLOR);
}
