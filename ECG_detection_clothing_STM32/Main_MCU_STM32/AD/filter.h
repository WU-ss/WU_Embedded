#ifndef __filter_H
#define __filter_H

	float Getmax(float* array);
	float Getmin(float* array);
	uint8_t Rwave_detection(float readData,float preReadData);
	float calcul_BPM(void);
	extern float BPM;
	extern char flag;
	extern uint8_t timeCount;
#endif
