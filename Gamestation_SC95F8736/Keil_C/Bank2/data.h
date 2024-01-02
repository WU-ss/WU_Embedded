#ifndef __DATA_H
#define __DATA_H  

#include "SC_Init.h"	// MCU initialization header file, including all firmware library header files

#define my_buttle_max 20
#define enemy_buttle_max 20

#define enemy_plane_max 10

struct Interface
{
    //简单记录三个分数
    int8_t score;
    int8_t score_2;
    int8_t score_3;
    //生命值
    int8_t life;
    //我的飞机
    int8_t my_plane[2];
    int8_t my_buttles[my_buttle_max][2];
    //游戏难度
    int8_t level;
    //boss
    int8_t boss[2];
    int8_t boss_life;
    int8_t pace;
    //敌机
    int8_t enemy_planes[enemy_plane_max][2];
    int8_t enemy_buttles[enemy_buttle_max][2];
    //已出现boss数量
    int8_t come_boss;
}interface;

#endif
