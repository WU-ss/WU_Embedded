#ifndef __RUN2_H__
#define __RUN2_H__

#include "SC_Init.h"	// MCU initialization header file, including all firmware library header files
#include "SC_it.h"

void switch_both_act(int8_t my_plane[2],int8_t my_buttles[10][2],int8_t his_plane[2],int8_t his_buttles[10][2]);
void update_both_buttles(int8_t my_buttles[10][2],int8_t his_buttles[10][2]);
int check_my_buttles_to_his_plane_collide(int8_t my_buttles[10][2], int8_t his_plane[2]);
int check_his_buttles_to_my_plane_collide(int8_t his_buttles[10][2], int8_t my_plane[2]);

#endif