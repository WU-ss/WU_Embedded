#ifndef __RUN_H
#define __RUN_H	

#include "SC_Init.h"	// MCU initialization header file, including all firmware library header files

void generate_enemy_planes(int8_t level, int8_t enemy_planes[10][2]);	//生成敌人飞机
void switch_my_act(int8_t my_plane[2],int8_t my_buttles[20][2]);		//更新图像
void update_my_buttles(int8_t my_buttles[20][2]);						//更新我的子弹
void update_enemy_buttles(int8_t enemy_buttles[20][2], int8_t level);	//更新敌机子弹
void update_enemy_planes(int8_t enemy_planes[10][2], int8_t level);		//更新敌机位置
//生成子弹
void generate_enemy_buttles(int8_t level, int8_t enemy_plane[10][2],  int8_t enemy_buttles[20][2]);
void generate_boss_buttles(int8_t boss[2],  int8_t enemy_buttles[20][2]);
//碰撞检测
void check_my_plane_to_enemy_plane_collide(int8_t *score,int8_t *life,	int8_t my_plane[2], int8_t enemy_planes[10][2]);
void check_my_buttles_to_enemy_plane_collide(int8_t *score,	int8_t my_buttles[20][2], int8_t enemy_planes[10][2]);
void check_my_plane_to_enemy_buttles_collide(int8_t *life,	int8_t enemy_buttles[20][2], int8_t my_plane[2]);
void check_my_buttles_to_boss_collide(int8_t *score, int8_t *boss_life,	int8_t my_buttles[20][2], int8_t boss[2]);
void clear_all_enemy_plane(int8_t my_plane[2],	int8_t enemy_plane[10][2], int8_t my_buttles[20][2], int8_t enemy_buttles[20][2]);
void move_boss(int8_t boss[2], int8_t *pace);
#endif
