#ifndef __MUSIC_H__
#define	__MUSIC_H__

#include "SC_Init.h"	// MCU initialization header file, including all firmware library header files

extern uint16_t C_FREQ[];
extern uint8_t music_two_tiger_f[];
extern u16 music_two_tiger_t_echo;
extern u16 music_two_tiger_len;
extern uint8_t music_two_tiger_t[];

void music_set(u8 n);

struct MUSIC_T 
{
	uint8_t* f;		/*Ƶ��*/
	uint8_t* t;		/*ÿ�������ĳ�*/
	u16 len;     	/*����*/
	u16 t_each;	 	/*�����ĳ�*/
	u8* name;		/*����*/
	uint8_t now_len;/*�����ڲ�������*/
};

extern struct MUSIC_T music_t;

#endif
