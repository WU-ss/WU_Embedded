#ifndef __DATA_H
#define __DATA_H  

#include "SC_Init.h"	// MCU initialization header file, including all firmware library header files

#define my_buttle_max 20
#define enemy_buttle_max 20

#define enemy_plane_max 10

struct Interface
{
    //�򵥼�¼��������
    int8_t score;
    int8_t score_2;
    int8_t score_3;
    //����ֵ
    int8_t life;
    //�ҵķɻ�
    int8_t my_plane[2];
    int8_t my_buttles[my_buttle_max][2];
    //��Ϸ�Ѷ�
    int8_t level;
    //boss
    int8_t boss[2];
    int8_t boss_life;
    int8_t pace;
    //�л�
    int8_t enemy_planes[enemy_plane_max][2];
    int8_t enemy_buttles[enemy_buttle_max][2];
    //�ѳ���boss����
    int8_t come_boss;
}interface;

#endif
