#include "stm32f10x.h"                  	// Device header
#include <stdio.h>
#include <stdarg.h>
#include "usart.h"
#include "Delay.h"	
#include "filter.h"
const char DATA_SIZE=100;
const float sample_time = 0.01;
char pre_flag=0;
char flag=0;
char idx=0;
float data[DATA_SIZE];
float max_data;
float min_data;
float mid_data;
float num_filter=400;
uint8_t timeCount=0;
uint8_t rCount=0;
float IBI=0;
float BPM=0;


float Getmax(float* array){
	int size = sizeof(array) / sizeof(array[0]);
	int i=0;
	int max;
	for ( i = 0; i < size; i++)
	{
		if (max < array[i])
		{
			max = array[i];
		}
	}
	return max;
}

float Getmin(float* array){
	int size = sizeof(array) / sizeof(array[0]);
	int i=0;
	int min;
	for ( i = 0; i < size; i++)
	{
		if (min > array[i])
		{
			min = array[i];
		}
	}
	return min;
}

uint8_t Rwave_detection(float readData,float preReadData){
	if (readData - preReadData < num_filter)   //滤除突变噪声信号干扰
	{
		data[idx]=readData;                  //填充缓存数组
        idx += 1;
	}
	if (idx >= DATA_SIZE)
	{
		idx=0;
		max_data=Getmax(data);
		min_data=Getmin(data);
		mid_data = (max_data + min_data) / 5 * 2.65;  //该系数可微调，升高或降低阈值
        num_filter = (max_data - min_data) / 2;
	}
	pre_flag=flag;
	if(readData>mid_data)	flag=1;
	else flag=0;
	if ((pre_flag == 0)&&(flag == 1)&& (timeCount > 35)&&(readData - preReadData >= 5))
        return 1;
    else
        return 0;
}

float calcul_BPM(void){
	rCount += 1;
    rCount %= 2;
    if (rCount == 1) 		//两次心跳的第一次
        timeCount=0;   
	
    else if(rCount == 0)	// 两次心跳的第二次
	{
        if (timeCount > 50)
        {
			IBI = timeCount * sample_time;		//计算相邻两次心跳的时间，得到 IBI，可以加上计时器时间以获得更精准的值
            BPM = 60 / IBI;                  	//通过 IBI 得到心率值 BPM
            if (BPM > 170)                 		 //限制BPM最高显示值
                BPM = 170;
            else if(BPM < 30)                 		 //限制BPM最低显示值
                BPM = 30;
		}
        else
            rCount = 1;
        timeCount=0;
	}
	return BPM;
}
