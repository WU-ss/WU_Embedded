#ifndef __PD_H__
#define __PD_H__

#define filter 0.6f //�궨���Ȩ΢�ֺ͵�ϵ��

extern uint16 Left_Defult; //����Ĭ��ת��
extern uint16 Right_Defult;//����Ĭ��ת��
extern uint16 Left_Roundabout; //���ֹ����������ת��	��������ֵ�ɵ��Եó�
extern uint16 Right_Roundabout; //���ֹ����������ת��	��������ֵ�ɵ��Եó�
extern uint16 Left_Sancha; //���ֹ����������ת��		��������ֵ�ɵ��Եó�
extern uint16 Right_Sancha; //���ֹ����������ת��	��������ֵ�ɵ��Եó�
extern u16 Limit; //����ת��
extern float Kp_S; //ֱ�� PD�ı�������P��ϵ��		��������ֵ�ɵ��Եó�
extern float Kd_S; //ֱ�� PD�Ļ��ֻ���D��ϵ��		��������ֵ�ɵ��Եó�
extern float Kp_C; //��� PD�ı�������P��ϵ��	��������ֵ�ɵ��Եó�
extern float Kd_C;  //��� PD�Ļ��ֻ���D��ϵ��	��������ֵ�ɵ��Եó�
extern float L_PWM; //����PWM
extern float R_PWM; //����PWM
typedef struct PIDStruct
{
float Kp;
float Ki;
float Kd;
float Err;			//��ֵ
float Err_last;
float DErr;			//��ֵ�仯��
float DErr_last;	
float OutSpeed_L;    //��������ٶ�
float OutSpeed_R;    //��������ٶ�
}PID_struct;
extern float DErr_sum; //�����ļ�Ȩ���΢��(�ۺϿ���DErr��DErr_last)

void PD(float err,float autal_Kp,float autal_Kd); //�����PD����

void PD_Control(void); //����Ŀ��Ƴ���

#endif
