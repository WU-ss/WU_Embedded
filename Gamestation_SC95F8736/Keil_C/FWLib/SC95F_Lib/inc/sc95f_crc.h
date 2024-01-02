//************************************************************
//  Copyright (c)
//	�ļ�����	: sc95f_CRC.h
//	����		:
//	ģ�鹦��	: CRC�̼��⺯��ͷ�ļ�
//  ����������: 2020/8/14
// 	�汾		: V1.0
//  ˵��        :���ļ���������SC95Fϵ��оƬ
//*************************************************************

#ifndef _sc95f_CRC_H_
#define _sc95f_CRC_H_

#include "sc95f.h"

uint32_t CRC_All(void); //����IAP Rangeѡ�Ӳ��CRC����CODE���ݣ�����CRC���
uint32_t CRC_Frame(uint8_t *buff,
                   uint8_t Length); //���CRC����buffָ����������CRC���㣬����CRC���

#endif

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/