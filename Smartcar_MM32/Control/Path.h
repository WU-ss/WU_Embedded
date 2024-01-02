#ifndef __PATH_H__
#define __PATH_H__

extern u16 Straight_cnt;    //ֱ���ϱ�־λ�������Ƶ�15�ж�Ϊֱ����
extern u8 Straight_flag;    //ֱ����־λ
extern u8 Circle_flag;      //�����־λ
extern u8 Roundabout_flag;  //������־λ
extern u8 Roundabout_flag_order;   //����������־λ ��ʾ���ǵڼ��ξ��������Ľ����
extern u8 Sancha_flag;      //����·��־λ
extern u8 Sancha_flag_order;		//����·������־λ ��ʾ���ǵڼ��ξ�������Ľ���� =1��һ�ξ��� =2�ڶ��ξ���

void Straight_Detect(void); //ֱ�����
void Circle_Detect(void); //������
void Roundabout_Detect(void); //�������
void Sancha_Detect(void); //����·���

void Path_Detect(void); //·�����

#endif
