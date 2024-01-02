#ifndef __AD_H
#define __AD_H

extern uint16_t ADValue[70];
extern uint16_t ADAvg;
extern float Voltage;

void AD_Init(void); //初始化ADC1通道，选择A0作为输入口，模式为单次转换非扫描
uint16_t AD_GetValue(void); //获取得到的ADC信息
uint16_t Get_AD_Avg(void); //对得到的ADC信息进行滤波
//void Get_Voltage(void);
float Get_Voltage(void);

#endif
