#ifndef __AD_H
#define __AD_H

extern uint16_t ADValue[70];
extern uint16_t ADAvg;
extern float Voltage;

void AD_Init(void); //��ʼ��ADC1ͨ����ѡ��A0��Ϊ����ڣ�ģʽΪ����ת����ɨ��
uint16_t AD_GetValue(void); //��ȡ�õ���ADC��Ϣ
uint16_t Get_AD_Avg(void); //�Եõ���ADC��Ϣ�����˲�
//void Get_Voltage(void);
float Get_Voltage(void);

#endif
