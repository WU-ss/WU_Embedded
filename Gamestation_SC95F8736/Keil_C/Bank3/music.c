#include "music.h"
#include "stdlib.h"

#define P_1 1
#define P_2 2
#define P_4_3 0.75
#define P_4_1 0.25

uint16_t C_FREQ[]={0,262,294,330,349,392,440,494,523,587,659,698,784,880,988,1046,1175,1318,1397,1568,1760,1976};
 
//1/4拍长
u16 music_two_tiger_t_echo=250;
 
//长度
u16 music_two_tiger_len=(sizeof(music_two_tiger_f)/sizeof(uint8_t));
 
//拍长
uint8_t music_two_tiger_t[]={
		P_1,P_1,P_1,P_1,
		P_1,P_1,P_1,P_1,
		P_1,P_1,P_2,
		P_1,P_1,P_2,
		P_4_3,P_4_1,P_4_3,P_4_1,P_1,P_1,
		P_4_3,P_4_1,P_4_3,P_4_1,P_1,P_1,
		P_1,P_1,P_2,
		P_1,P_1,P_2,
};

//频率
uint8_t music_two_tiger_f[]={
		1,2,3,1,
		1,2,3,1,
		3,4,5,
		3,4,5,
		5,6,5,6,3,1,
		5,6,5,4,3,1,
		1,5,1,
		1,5,1,
};

u8 B0[]="STOP";
u8 B1[]="two tigers";

struct MUSIC_T music_t;

void music_set(u8 n)
{
	switch(n){
		case 0:{
					music_t.f=NULL;
					music_t.t=NULL;
					music_t.len=0;
					music_t.t_each=0;
					music_t.name=B0;
					};break;
		case 1:{
					music_t.f=music_two_tiger_f;
					music_t.t=music_two_tiger_t;
					music_t.len=music_two_tiger_len;
					music_t.t_each=music_two_tiger_t_echo;
					music_t.name=B1;
					}; break;
	}
}

