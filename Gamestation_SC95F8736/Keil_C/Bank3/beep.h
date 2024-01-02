#ifndef __BEEP_H__
#define __BEEP_H__

#include "SC_Init.h"	// MCU initialization header file, including all firmware library header files

void passive_buzzer_set(uint16_t note_f);
extern u32 paly_delay_ms;
void my_buzzer_play();

extern struct MUSIC_T music_t;

#endif
