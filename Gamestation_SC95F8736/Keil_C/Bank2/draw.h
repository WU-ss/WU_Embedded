#ifndef __DRAW_H
#define __DRAW_H

#include "SC_Init.h"	// MCU initialization header file, including all firmware library header files

void draw_start_page(void);
void init_play_interface(void);
void draw_end(int8_t *score,int8_t *score_2, int8_t *score_3);
void draw_play_all(int8_t score,int8_t life, int8_t my_plane[2], int8_t my_buttles[20][2], int8_t boss[2], int8_t enemy_planes[10][2], int8_t enemy_buttles[20][2]);
void draw_both_buttles(int8_t my_buttles[10][2],int8_t his_buttles[10][2]);

#endif
