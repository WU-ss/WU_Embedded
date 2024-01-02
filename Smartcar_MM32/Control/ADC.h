#ifndef __ADC_H__
#define __ADC_H__

extern uint16 ADC_Val[3][7]; //��вɼ���������ֵ
extern uint16 ADC_Avg[3]; //����˲���õ���ƽ��ֵ
extern uint16 ADC_Avg_GuiYi[3]; //��й�һ����õ���ƽ��ֵ
extern uint16 max[3]; //������зֱ�����ֵ
extern uint16 min[3]; //������зֱ����Сֵ
extern float dif_sum; //��в�Ⱥ�
extern float dif_sum_last1,dif_sum_last2,dif_sum_last3,dif_sum_last4; //��в�Ⱥ͵���ʷֵ
extern int16 ADC_Avg_Hist[3][8]; //���8�εĵ������
extern int ADC_Symbol_z[3]; //��е����Ӵ���
extern int ADC_Symbol_f[3]; //��еļ�С����
extern int L_Cap; //���еı仯���� 1���� -1��С
extern int M_Cap; //�е�еı仯���� 1���� -1��С
extern int R_Cap; //�ҵ�еı仯���� 1���� -1��С

//void Saomiao(void); //ɨ������
void Get_ADC(void); //���ADC��ѹ,�˲���洢��ADC_Val��
void GuiYiHua_ADC(void); //���ɼ�����ADC�źŽ��й�һ������
void Get_Dif(void); //�õ���в�Ⱥ�
void Get_ADC_Avg_Hist(void); //�õ����8�εĵ������
void Get_ADC_Symbol(void); //�õ���еı仯����

void ADC_Handle(void); //����õ�ADC����

#endif
