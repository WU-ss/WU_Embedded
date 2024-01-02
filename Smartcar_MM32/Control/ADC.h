#ifndef __ADC_H__
#define __ADC_H__

extern uint16 ADC_Val[3][7]; //电感采集到的样本值
extern uint16 ADC_Avg[3]; //电感滤波后得到的平均值
extern uint16 ADC_Avg_GuiYi[3]; //电感归一化后得到的平均值
extern uint16 max[3]; //三个电感分别的最大值
extern uint16 min[3]; //三个电感分别的最小值
extern float dif_sum; //电感差比和
extern float dif_sum_last1,dif_sum_last2,dif_sum_last3,dif_sum_last4; //电感差比和的历史值
extern int16 ADC_Avg_Hist[3][8]; //最近8次的电感数据
extern int ADC_Symbol_z[3]; //电感的增加次数
extern int ADC_Symbol_f[3]; //电感的减小次数
extern int L_Cap; //左电感的变化趋势 1增加 -1减小
extern int M_Cap; //中电感的变化趋势 1增加 -1减小
extern int R_Cap; //右电感的变化趋势 1增加 -1减小

//void Saomiao(void); //扫描赛道
void Get_ADC(void); //获得ADC电压,滤波后存储到ADC_Val上
void GuiYiHua_ADC(void); //将采集到的ADC信号进行归一化处理
void Get_Dif(void); //得到电感差比和
void Get_ADC_Avg_Hist(void); //得到最近8次的电感数据
void Get_ADC_Symbol(void); //得到电感的变化趋势

void ADC_Handle(void); //处理得到ADC数据

#endif
