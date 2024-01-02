#ifndef __RUN_H
#define __RUN_H	

#include "SC_Init.h"	// MCU initialization header file, including all firmware library header files

void generate_enemy_planes(int8_t level, int8_t enemy_planes[10][2]);	//���ɵ��˷ɻ�
void switch_my_act(int8_t my_plane[2],int8_t my_buttles[20][2]);		//����ͼ��
void update_my_buttles(int8_t my_buttles[20][2]);						//�����ҵ��ӵ�
void update_enemy_buttles(int8_t enemy_buttles[20][2], int8_t level);	//���µл��ӵ�
void update_enemy_planes(int8_t enemy_planes[10][2], int8_t level);		//���µл�λ��
//�����ӵ�
void generate_enemy_buttles(int8_t level, int8_t enemy_plane[10][2],  int8_t enemy_buttles[20][2]);
void generate_boss_buttles(int8_t boss[2],  int8_t enemy_buttles[20][2]);
//��ײ���
void check_my_plane_to_enemy_plane_collide(int8_t *score,int8_t *life,	int8_t my_plane[2], int8_t enemy_planes[10][2]);
void check_my_buttles_to_enemy_plane_collide(int8_t *score,	int8_t my_buttles[20][2], int8_t enemy_planes[10][2]);
void check_my_plane_to_enemy_buttles_collide(int8_t *life,	int8_t enemy_buttles[20][2], int8_t my_plane[2]);
void check_my_buttles_to_boss_collide(int8_t *score, int8_t *boss_life,	int8_t my_buttles[20][2], int8_t boss[2]);
void clear_all_enemy_plane(int8_t my_plane[2],	int8_t enemy_plane[10][2], int8_t my_buttles[20][2], int8_t enemy_buttles[20][2]);
void move_boss(int8_t boss[2], int8_t *pace);
#endif
