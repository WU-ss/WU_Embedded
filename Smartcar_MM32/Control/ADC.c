#include "headfile.h"

uint16 ADC_Val[3][7]; //��вɼ���������ֵ
uint16 ADC_Avg[3]; //����˲���õ���ƽ��ֵ
uint16 ADC_Avg_GuiYi[3]; //��й�һ����õ���ƽ��ֵ
float max[3]={3600,3600,3600}; //������зֱ�����ֵ ��������ֵ�ɵ��Եó�
float min[3]={0,0,0
}; //������зֱ����Сֵ       ��������ֵ�ɵ��Եó�
float dif_sum; //��в�Ⱥ�
float dif_sum_last1,dif_sum_last2,dif_sum_last3,dif_sum_last4; //��в�Ⱥ͵���ʷֵ

int16 ADC_Avg_Hist[3][8]={0}; //���8�εĵ������
int ADC_Symbol_z[3]={0}; //��е����Ӵ���
int ADC_Symbol_f[3]={0}; //��еļ�С����
int L_Cap; //���еı仯���� 1���� -1��С
int M_Cap; //�е�еı仯���� 1���� -1��С
int R_Cap; //�ҵ�еı仯���� 1���� -1��С

void Get_ADC_Avg_Hist(void);

//void Saomiao(void) //ɨ������
//{
//	uint32 i,j;

//    for(i=0;i<1000;i++)  
//    {
//		ADC_Val[0][0]=adc_mean_filter(ADC_1, ADC1_CH00_A00, 10);
//		ADC_Val[1][0]=adc_mean_filter(ADC_1, ADC1_CH01_A01, 10);
//		ADC_Val[2][0]=adc_mean_filter(ADC_1, ADC1_CH02_A02, 10);
//		for(j=0;j<3;j++)
//		{
//			if(ADC_Val[j][0]>max[j]) 
//				max[j]=ADC_Val[j][0];
//			if(ADC_Val[0][0]<min[j])
//				min[j]=ADC_Val[j][0];
//		}
//    }
//	
////	printf("max= %d,%d,%d,%d. \r\n",max[0],max[1],max[2],max[3]);
////	printf("min= %d,%d,%d,%d. \r\n",min[0],min[1],min[2],min[3]);
//}

void Get_ADC(void) //���ADC��ѹ,�˲���洢��ADC_Val��
{
	//����ƽ��ֵ�˲�
	int n,i,j,temp;
	
	for(i=0;i<7;i++)
	{
		ADC_Val[0][i]=adc_mean_filter(ADC_1, ADC1_CH00_A00,7);
		ADC_Val[1][i]=adc_mean_filter(ADC_1, ADC1_CH02_A02,7);
		ADC_Val[2][i]=adc_mean_filter(ADC_1, ADC1_CH03_A03,7);
		
	}
	
	for(n=0;n<3;n++) //ð������
	{
		for(i=0;i<6;i++)    
		{
			for(j=0;j<6-i;j++)
			{
				 if(ADC_Val[n][j]>ADC_Val[n][j+1])
				{
					temp=ADC_Val[n][j+1];
					ADC_Val[n][j+1]=ADC_Val[n][j];
					ADC_Val[n][j]=temp;
				}
			}
		}
	}
	
	for(n=0;n<3;n++) //��ȡƽ��ֵ
	{ADC_Avg[n]=(uint16)((ADC_Val[n][1]+ADC_Val[n][2]+ADC_Val[n][3]+ADC_Val[n][4]+ADC_Val[n][5])/5.0);}
	
//	printf("averge= %d %d %d %d.\n",ADC_Avg[0],ADC_Avg[1],ADC_Avg[2],ADC_Avg[3])
}

void GuiYiHua_ADC(void) //���ɼ�����ADC�źŽ��й�һ������  ���ս������100��
{
	int n;
	for(n=0;n<3;n++)
	{ADC_Avg_GuiYi[n] =(uint16)(99*(ADC_Avg[n]-min[n])/(max[n]-min[n])+1);}
//	if(ADC_Avg_GuiYi[0]<0.6 && ADC_Avg_GuiYi[0]>0.8)
//	{
//		ADC_Avg_GuiYi[0]*=1.5;
//	}
//	printf("GuiYi= %d %d %d %d.\n",ADC_Avg_GuiYi[0],ADC_Avg_GuiYi[1],ADC_Avg_GuiYi[2],ADC_Avg_GuiYi[3]);
}

void Get_Dif(void) //�õ���в�Ⱥ�
{
	if(ADC_Avg_GuiYi[0]+ADC_Avg_GuiYi[2]!=0) //�ж��Ƿ���������
	{
	  dif_sum=(float)(ADC_Avg_GuiYi[0]-ADC_Avg_GuiYi[2])/(ADC_Avg_GuiYi[0]+ADC_Avg_GuiYi[2]);
	}
	else 
	{dif_sum=0;}
	
	//�����ۼƻ�ȡ��dif�����²�Ⱥ�
	dif_sum=dif_sum*0.2+dif_sum_last1*0.2+dif_sum_last2*0.2+dif_sum_last3*0.2+dif_sum_last4*0.2;
	dif_sum_last4=dif_sum_last3;
	dif_sum_last3=dif_sum_last2;
	dif_sum_last2=dif_sum_last1;
	dif_sum_last1=dif_sum;
}

void Get_ADC_Avg_Hist(void) //�õ����8�εĵ������
{
	int i,j;
	for(i=0;i<3;i++)
	{
		ADC_Avg_Hist[i][0]=ADC_Avg[i];
		for(j=6;j>=0;j--)
		{
			ADC_Avg_Hist[i][j+1]=ADC_Avg_Hist[i][j];
		}
	}
}

void Get_ADC_Symbol(void) //�õ���еı仯����
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=1;j<8;j++)
		{
			if((ADC_Avg_Hist[i][j]-ADC_Avg_Hist[i][j+1])>10) {++ADC_Symbol_z[i];}
			if((ADC_Avg_Hist[i][j]-ADC_Avg_Hist[i][j+1])<-10) {++ADC_Symbol_f[i];}
		}
	}
	
	if(ADC_Symbol_z[0]>=4)	L_Cap=1;
	else if(ADC_Symbol_f[0]>=4)	L_Cap=-1;
	else L_Cap=0;
	
	if(ADC_Symbol_z[1]>=4)	M_Cap=1;
	else if(ADC_Symbol_f[1]>=4)	M_Cap=-1;
	else M_Cap=0;
	
	if(ADC_Symbol_z[2]>=4)	R_Cap=1;
	else if(ADC_Symbol_f[2]>=4)	R_Cap=-1;
	else R_Cap=0;
	
	for(i=0;i<3;i++)
	{
		ADC_Symbol_z[i]=0;
		ADC_Symbol_f[i]=0;
	}
}

void ADC_Handle(void) //����õ�ADC����
{
	Get_ADC();
	GuiYiHua_ADC();
	Get_Dif();
}
