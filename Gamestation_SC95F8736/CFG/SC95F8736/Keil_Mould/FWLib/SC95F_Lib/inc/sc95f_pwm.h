//************************************************************
//  Copyright (c) 
//	�ļ�����: 			sc95f_pwm.h
//	����:
//	ģ�鹦��: 			PWM�̼��⺯��H�ļ�
//  ����������:	2022��7��20��
// 	�汾: 				V1.10006
//  ˵��:					���ļ���������SC95Fϵ��оƬ
//*************************************************************

#ifndef _sc95f_PWM_H_
#define _sc95f_PWM_H_

#include "sc95f.h"
#if defined(SC95F8x1x) || defined(SC95F7x1x)
//PWM���ͨ��ѡ��
typedef enum
{
  PWM40 = (uint8_t)0x01, //PWM���ͨ��ѡ��:PWM40
  PWM41 = (uint8_t)0x02, //PWM���ͨ��ѡ��:PWM41
  PWM42 = (uint8_t)0x04, //PWM���ͨ��ѡ��:PWM42
  PWM43 = (uint8_t)0x08, //PWM���ͨ��ѡ��:PWM43
  PWM50 = (uint8_t)0x10, //PWM���ͨ��ѡ��:PWM50
  PWM51 = (uint8_t)0x20, //PWM���ͨ��ѡ��:PWM51
  PWM52 = (uint8_t)0x40, //PWM���ͨ��ѡ��:PWM52
  PWM53 = (uint8_t)0x80  //PWM���ͨ��ѡ��:PWM53
} PWM_OutputPin_TypeDef;

// PWMԤ��Ƶ
typedef enum
{
  PWM_PRESSEL_FHRC_D1 = (uint8_t)0x00, //PWMԤ��ƵΪFhrc/1
  PWM_PRESSEL_FHRC_D2 = (uint8_t)0x10, //PWMԤ��ƵΪFhrc/2
  PWM_PRESSEL_FHRC_D4 = (uint8_t)0x20, //PWMԤ��ƵΪFhrc/4
  PWM_PRESSEL_FHRC_D8 = (uint8_t)0x30  //PWMԤ��ƵΪFhrc/8
} PWM_PresSel_TypeDef;

//PWM����ģʽͨ��ѡ��
typedef enum
{
  PWM40PWM41 = (uint8_t)0x00, //PWM����ģʽͨ��ѡ��:PWM40��PWM41
  PWM42PWM43 = (uint8_t)0x02, //PWM����ģʽͨ��ѡ��:PWM42��PWM43
  PWM50PWM51 = (uint8_t)0x04, //PWM����ģʽͨ��ѡ��:PWM50��PWM51
  PWM52PWM53 = (uint8_t)0x06  //PWM����ģʽͨ��ѡ��:PWM52��PWM53
} PWM_ComplementaryOutputPin_TypeDef;

//PWM���ϼ��ģʽ
typedef enum
{
  PWM_Latch_Mode = ((uint8_t)0x00),    //PWM���ϼ��ģʽ:����ģʽ
  PWM_Immediate_Mode = ((uint8_t)0x20) //PWM���ϼ��ģʽ:����ģʽ
} PWM_FaultDetectionMode_TypeDef;

//PWM���ϼ���ƽѡ��
typedef enum
{
  PWM_FaultDetectionVoltage_Low = ((uint8_t)0x00), //PWM���ϼ��͵�ƽѡ��
  PWM_FaultDetectionVoltage_high = ((uint8_t)0x10) //PWM���ϼ��ߵ�ƽѡ��
} PWM_FaultDetectionVoltageSelect_TypeDef;

typedef enum //PWM���ϼ�������ź��˲�ʱ��
{
  PWM_WaveFilteringTime_0us = ((uint8_t)0x00), //PWM���ϼ�������ź��˲�ʱ��0us
  PWM_WaveFilteringTime_1us = ((uint8_t)0x01), //PWM���ϼ�������ź��˲�ʱ��1us
  PWM_WaveFilteringTime_4us = ((uint8_t)0x02), //PWM���ϼ�������ź��˲�ʱ��4us
  PWM_WaveFilteringTime_16us = ((uint8_t)0x03) //PWM���ϼ�������ź��˲�ʱ��16us
} PWM_FaultDetectionWaveFilteringTime_TypeDef;

//PWM����ģʽ
typedef enum
{
  PWM_Edge_Aligned_Mode = (uint8_t)0x00,    //PWM���ض���ģʽ
  PWM_Center_Alignment_Mode = (uint8_t)0x01 //PWM�м����ģʽ
} PWM_Aligned_Mode_TypeDef;

#endif

#if defined(SC95F8x2x) || defined(SC95F7x2x)
// PWMԤ��Ƶ
typedef enum
{
  PWM_PRESSEL_FHRC_D1 = (uint8_t)0x00, //PWMԤ��ƵΪFHRC/1
  PWM_PRESSEL_FHRC_D2 = (uint8_t)0x10, //PWMԤ��ƵΪFHRC/2
  PWM_PRESSEL_FHRC_D4 = (uint8_t)0x20, //PWMԤ��ƵΪFHRC/4
  PWM_PRESSEL_FHRC_D8 = (uint8_t)0x30  //PWMԤ��ƵΪFHRC/8
} PWM_PresSel_TypeDef;

//PWM���ͨ��ѡ��
typedef enum
{
  PWM0 = (uint8_t)0x01, //PWM���ͨ��ѡ��:PWM0
  PWM1 = (uint8_t)0x02, //PWM���ͨ��ѡ��:PWM1
  PWM2 = (uint8_t)0x04, //PWM���ͨ��ѡ��:PWM2
  PWM3 = (uint8_t)0x08, //PWM���ͨ��ѡ��:PWM3
  PWM4 = (uint8_t)0x10, //PWM���ͨ��ѡ��:PWM4
  PWM5 = (uint8_t)0x20, //PWM���ͨ��ѡ��:PWM5
  PWM6 = (uint8_t)0x40, //PWM���ͨ��ѡ��:PWM6
  PWM7 = (uint8_t)0x80, //PWM���ͨ��ѡ��:PWM7
} PWM_OutputPin_TypeDef;

//PWM����ģʽ
typedef enum
{
  PWM_Edge_Aligned_Mode = (uint8_t)0x00,    //PWM���ض���ģʽ
  PWM_Center_Alignment_Mode = (uint8_t)0x01 //PWM�м����ģʽ
} PWM_Aligned_Mode_TypeDef;

//PWM���ϼ��ģʽ
typedef enum
{
  PWM_Latch_Mode = ((uint8_t)0x00),    //PWM���ϼ��ģʽ:����ģʽ
  PWM_Immediate_Mode = ((uint8_t)0x20) //PWM���ϼ��ģʽ:����ģʽ
} PWM_FaultDetectionMode_TypeDef;

//PWM���ϼ���ƽѡ��
typedef enum
{
  PWM_FaultDetectionVoltage_Low = ((uint8_t)0x00), //PWM���ϼ��͵�ƽѡ��
  PWM_FaultDetectionVoltage_high = ((uint8_t)0x10) //PWM���ϼ��ߵ�ƽѡ��
} PWM_FaultDetectionVoltageSelect_TypeDef;

//PWM���ϼ�������ź��˲�ʱ��
typedef enum
{
  PWM_WaveFilteringTime_0us = ((uint8_t)0x00), //PWM���ϼ�������ź��˲�ʱ��0us
  PWM_WaveFilteringTime_1us = ((uint8_t)0x01), //PWM���ϼ�������ź��˲�ʱ��1us
  PWM_WaveFilteringTime_4us = ((uint8_t)0x02), //PWM���ϼ�������ź��˲�ʱ��4us
  PWM_WaveFilteringTime_16us = ((uint8_t)0x03) //PWM���ϼ�������ź��˲�ʱ��16us
} PWM_FaultDetectionWaveFilteringTime_TypeDef;

//PWM����ģʽͨ��ѡ��
typedef enum
{
  PWM0PWM1 = (uint8_t)0x00, //PWM����ģʽͨ��ѡ��:PWM0��PWM1
  PWM2PWM3 = (uint8_t)0x01, //PWM����ģʽͨ��ѡ��:PWM2��PWM3
  PWM4PWM5 = (uint8_t)0x02, //PWM����ģʽͨ��ѡ��:PWM4��PWM5
  PWM6PWM7 = (uint8_t)0x03  //PWM����ģʽͨ��ѡ��:PWM6��PWM7
} PWM_ComplementaryOutputPin_TypeDef;

#endif

#if defined(SC95FWxx)
//PWMԤ��Ƶѡ��
typedef enum
{
  PWM0_PRESSEL_FHRC_D1 = (uint8_t)0x00, //PWM0Ԥ��ƵΪFhrc/1
  PWM0_PRESSEL_FHRC_D2 = (uint8_t)0x10, //PWM0Ԥ��ƵΪFhrc/2
  PWM0_PRESSEL_FHRC_D4 = (uint8_t)0x20, //PWM0Ԥ��ƵΪFhrc/4
  PWM0_PRESSEL_FHRC_D8 = (uint8_t)0x30, //PWM0Ԥ��ƵΪFhrc/8
  PWM1_PRESSEL_FHRC_D1 = (uint8_t)0x01, //PWM1Ԥ��ƵΪFhrc/1
  PWM1_PRESSEL_FHRC_D2 = (uint8_t)0x11, //PWM1Ԥ��ƵΪFhrc/2
  PWM1_PRESSEL_FHRC_D4 = (uint8_t)0x21, //PWM1Ԥ��ƵΪFhrc/4
  PWM1_PRESSEL_FHRC_D8 = (uint8_t)0x31, //PWM1Ԥ��ƵΪFhrc/8
} PWM_PresSel_TypeDef;

//PWM���ͨ��ѡ��
typedef enum
{
  PWM00 = (uint8_t)0x00, //PWM���ͨ��ѡ��: PWM00
  PWM01 = (uint8_t)0x02, //PWM���ͨ��ѡ��: PWM01
  PWM02 = (uint8_t)0x04, //PWM���ͨ��ѡ��: PWM02
  PWM03 = (uint8_t)0x06, //PWM���ͨ��ѡ��: PWM03
  PWM04 = (uint8_t)0x08, //PWM���ͨ��ѡ��: PWM04
  PWM05 = (uint8_t)0x0A, //PWM���ͨ��ѡ��: PWM05
  PWM06 = (uint8_t)0x0C, //PWM���ͨ��ѡ��: PWM06
  PWM07 = (uint8_t)0x0E, //PWM���ͨ��ѡ��: PWM07
  PWM10 = (uint8_t)0x10, //PWM���ͨ��ѡ��: PWM10
  PWM11 = (uint8_t)0x12, //PWM���ͨ��ѡ��: PWM11
  PWM12 = (uint8_t)0x14, //PWM���ͨ��ѡ��: PWM12
  PWM13 = (uint8_t)0x16, //PWM���ͨ��ѡ��: PWM13
  PWM14 = (uint8_t)0x18, //PWM���ͨ��ѡ��: PWM14
  PWM15 = (uint8_t)0x1A, //PWM���ͨ��ѡ��: PWM15
  PWM16 = (uint8_t)0x1C, //PWM���ͨ��ѡ��: PWM16
  PWM17 = (uint8_t)0x1E, //PWM���ͨ��ѡ��: PWM17
  PWM20 = (uint8_t)0x20, //PWM���ͨ��ѡ��: PWM20
  PWM21 = (uint8_t)0x22, //PWM���ͨ��ѡ��: PWM21
  PWM22 = (uint8_t)0x24, //PWM���ͨ��ѡ��: PWM22
  PWM23 = (uint8_t)0x26, //PWM���ͨ��ѡ��: PWM23
  PWM24 = (uint8_t)0x28, //PWM���ͨ��ѡ��: PWM24
  PWM25 = (uint8_t)0x2A, //PWM���ͨ��ѡ��: PWM25
  PWM26 = (uint8_t)0x2C, //PWM���ͨ��ѡ��: PWM26
  PWM27 = (uint8_t)0x2E, //PWM���ͨ��ѡ��: PWM27
  PWM30 = (uint8_t)0x30, //PWM���ͨ��ѡ��: PWM30
  PWM31 = (uint8_t)0x32, //PWM���ͨ��ѡ��: PWM31
  PWM32 = (uint8_t)0x34, //PWM���ͨ��ѡ��: PWM32
  PWM33 = (uint8_t)0x36, //PWM���ͨ��ѡ��: PWM33
  PWM34 = (uint8_t)0x38, //PWM���ͨ��ѡ��: PWM34
  PWM35 = (uint8_t)0x3A, //PWM���ͨ��ѡ��: PWM25
  PWM36 = (uint8_t)0x3C, //PWM���ͨ��ѡ��: PWM26
  PWM37 = (uint8_t)0x3E, //PWM���ͨ��ѡ��: PWM27
  PWM40 = (uint8_t)0x40, //PWM���ͨ��ѡ��: PWM40
  PWM41 = (uint8_t)0x42, //PWM���ͨ��ѡ��: PWM41
  PWM42 = (uint8_t)0x44, //PWM���ͨ��ѡ��: PWM42
  PWM43 = (uint8_t)0x46, //PWM���ͨ��ѡ��: PWM53
  PWM50 = (uint8_t)0x48, //PWM���ͨ��ѡ��: PWM50
  PWM51 = (uint8_t)0x4A, //PWM���ͨ��ѡ��: PWM51
  PWM52 = (uint8_t)0x4C, //PWM���ͨ��ѡ��: PWM52
  PWM53 = (uint8_t)0x4E, //PWM���ͨ��ѡ��: PWM53
} PWM_OutputPin_TypeDef;

//PWM����ģʽ
typedef enum
{
  PWM0_Edge_Aligned_Mode = (uint8_t)0x00,     //PWM���ض���ģʽ
  PWM0_Center_Alignment_Mode = (uint8_t)0x01, //PWM�м����ģʽ
  PWM1_Edge_Aligned_Mode = (uint8_t)0x10,     //PWM���ض���ģʽ
  PWM1_Center_Alignment_Mode = (uint8_t)0x11  //PWM�м����ģʽ
} PWM_Aligned_Mode_TypeDef;

//PWM���ϼ��ģʽ
typedef enum
{
  PWM1_Latch_Mode = ((uint8_t)0x00),    //PWM���ϼ��ģʽ:����ģʽ
  PWM1_Immediate_Mode = ((uint8_t)0x20) //PWM���ϼ��ģʽ:����ģʽ
} PWM_FaultDetectionMode_TypeDef;

//PWM���ϼ���ƽѡ��
typedef enum
{
  PWM1_FaultDetectionVoltage_Low = ((uint8_t)0x00), //PWM���ϼ��͵�ƽѡ��
  PWM1_FaultDetectionVoltage_high = ((uint8_t)0x10) //PWM���ϼ��ߵ�ƽѡ��
} PWM_FaultDetectionVoltageSelect_TypeDef;

//PWM���ϼ�������ź��˲�ʱ��
typedef enum
{
  PWM1_WaveFilteringTime_0us = ((uint8_t)0x00), //PWM���ϼ�������ź��˲�ʱ��0us
  PWM1_WaveFilteringTime_1us = ((uint8_t)0x01), //PWM���ϼ�������ź��˲�ʱ��1us
  PWM1_WaveFilteringTime_4us = ((uint8_t)0x02), //PWM���ϼ�������ź��˲�ʱ��4us
  PWM1_WaveFilteringTime_16us = ((uint8_t)0x03) //PWM���ϼ�������ź��˲�ʱ��16us
} PWM_FaultDetectionWaveFilteringTime_TypeDef;

//PWM����ģʽͨ��ѡ��
typedef enum
{
  PWM40PWM41 = (uint8_t)0x00, //PWM����ģʽͨ��ѡ��:PWM40��PWM11
  PWM42PWM43 = (uint8_t)0x01, //PWM����ģʽͨ��ѡ��:PWM12��PWM13
  PWM50PWM51 = (uint8_t)0x02, //PWM����ģʽͨ��ѡ��:PWM50��PWM51
  PWM52PWM53 = (uint8_t)0x03  //PWM����ģʽͨ��ѡ��:PWM52��PWM53
} PWM_ComplementaryOutputPin_TypeDef;

//PWMԴѡ��
typedef enum
{
  PWM0_Type = (uint8_t)0x00, //����PWM0
  PWM1_Type = (uint8_t)0x01, //����PWM1
} PWM_Type_TypeDef;
#endif
#if defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)
//PWMԤ��Ƶѡ��
typedef enum
{
  PWM0_PRESSEL_FHRC_D1 = (uint8_t)0x00, //PWM0Ԥ��ƵΪFhrc/1
  PWM0_PRESSEL_FHRC_D2 = (uint8_t)0x10, //PWM0Ԥ��ƵΪFhrc/2
  PWM0_PRESSEL_FHRC_D4 = (uint8_t)0x20, //PWM0Ԥ��ƵΪFhrc/4
  PWM0_PRESSEL_FHRC_D8 = (uint8_t)0x30, //PWM0Ԥ��ƵΪFhrc/8
  PWM2_PRESSEL_FHRC_D1 = (uint8_t)0x02, //PWM2Ԥ��ƵΪFhrc/1
  PWM3_PRESSEL_FHRC_D1 = (uint8_t)0x03, //PWM3Ԥ��ƵΪFhrc/1
  PWM4_PRESSEL_FHRC_D1 = (uint8_t)0x04, //PWM4Ԥ��ƵΪFhrc/1
} PWM_PresSel_TypeDef;

//PWM���ͨ��ѡ��
typedef enum
{
  PWM00 = (uint8_t)0x00, //PWM���ͨ��ѡ��: PWM00
  PWM01 = (uint8_t)0x02, //PWM���ͨ��ѡ��: PWM01
  PWM02 = (uint8_t)0x04, //PWM���ͨ��ѡ��: PWM02
  PWM03 = (uint8_t)0x06, //PWM���ͨ��ѡ��: PWM03
  PWM04 = (uint8_t)0x08, //PWM���ͨ��ѡ��: PWM04
  PWM05 = (uint8_t)0x0A, //PWM���ͨ��ѡ��: PWM05
  PWM06 = (uint8_t)0x0C, //PWM���ͨ��ѡ��: PWM06
  PWM07 = (uint8_t)0x0E, //PWM���ͨ��ѡ��: PWM07
  PWM20 = (uint8_t)0x20, //PWM���ͨ��ѡ��: PWM20
  PWM21 = (uint8_t)0x22, //PWM���ͨ��ѡ��: PWM21
  PWM30 = (uint8_t)0x34, //PWM���ͨ��ѡ��: PWM30
  PWM31 = (uint8_t)0x36, //PWM���ͨ��ѡ��: PWM31
  PWM40 = (uint8_t)0x48, //PWM���ͨ��ѡ��: PWM40
  PWM41 = (uint8_t)0x4A, //PWM���ͨ��ѡ��: PWM41
} PWM_OutputPin_TypeDef;

//PWM����ģʽ
typedef enum
{
  PWM0_Edge_Aligned_Mode = (uint8_t)0x00,     //PWM���ض���ģʽ
  PWM0_Center_Alignment_Mode = (uint8_t)0x01, //PWM�м����ģʽ
} PWM_Aligned_Mode_TypeDef;

//PWM���ϼ��ģʽ
typedef enum
{
  PWM0_Latch_Mode = ((uint8_t)0x00),    //PWM���ϼ��ģʽ:����ģʽ
  PWM0_Immediate_Mode = ((uint8_t)0x20) //PWM���ϼ��ģʽ:����ģʽ
} PWM_FaultDetectionMode_TypeDef;

//PWM���ϼ���ƽѡ��
typedef enum
{
  PWM0_FaultDetectionVoltage_Low = ((uint8_t)0x00), //PWM���ϼ��͵�ƽѡ��
  PWM0_FaultDetectionVoltage_high = ((uint8_t)0x10) //PWM���ϼ��ߵ�ƽѡ��
} PWM_FaultDetectionVoltageSelect_TypeDef;

//PWM���ϼ�������ź��˲�ʱ��
typedef enum
{
  PWM0_WaveFilteringTime_0us = ((uint8_t)0x00), //PWM���ϼ�������ź��˲�ʱ��0us
  PWM0_WaveFilteringTime_1us = ((uint8_t)0x01), //PWM���ϼ�������ź��˲�ʱ��1us
  PWM0_WaveFilteringTime_4us = ((uint8_t)0x02), //PWM���ϼ�������ź��˲�ʱ��4us
  PWM0_WaveFilteringTime_16us = ((uint8_t)0x03) //PWM���ϼ�������ź��˲�ʱ��16us
} PWM_FaultDetectionWaveFilteringTime_TypeDef;

//PWM����ģʽͨ��ѡ��
typedef enum
{
  PWM00PWM01 = (uint8_t)0x00, //PWM����ģʽͨ��ѡ��:PWM00��PWM01
  PWM02PWM03 = (uint8_t)0x04, //PWM����ģʽͨ��ѡ��:PWM02��PWM03
  PWM04PWM05 = (uint8_t)0x08, //PWM����ģʽͨ��ѡ��:PWM04��PWM05
  PWM06PWM07 = (uint8_t)0x0C  //PWM����ģʽͨ��ѡ��:PWM06��PWM07
} PWM_ComplementaryOutputPin_TypeDef;

//PWMԴѡ��
typedef enum
{
  PWM0_Type = (uint8_t)0x00, //����PWM0
  PWM2_Type = (uint8_t)0x02, //����PWM2
  PWM3_Type = (uint8_t)0x03, //����PWM3
  PWM4_Type = (uint8_t)0x04, //����PWM4
} PWM_Type_TypeDef;
#endif

#if defined (SC95R751)
//PWMԤ��Ƶѡ��
typedef enum
{
  PWM0_PRESSEL_FHRC_D1 = (uint8_t)0x00, //PWM0Ԥ��ƵΪFhrc/1
  PWM0_PRESSEL_FHRC_D2 = (uint8_t)0x10, //PWM0Ԥ��ƵΪFhrc/2
  PWM0_PRESSEL_FHRC_D4 = (uint8_t)0x20, //PWM0Ԥ��ƵΪFhrc/4
  PWM0_PRESSEL_FHRC_D8 = (uint8_t)0x30, //PWM0Ԥ��ƵΪFhrc/8
  PWM3_PRESSEL_FHRC_D1 = (uint8_t)0x03, //PWM3Ԥ��ƵΪFhrc/1
} PWM_PresSel_TypeDef;

//PWM���ͨ��ѡ��
typedef enum
{
  PWM00 = (uint8_t)0x00, //PWM���ͨ��ѡ��: PWM00
  PWM01 = (uint8_t)0x02, //PWM���ͨ��ѡ��: PWM01
  PWM02 = (uint8_t)0x04, //PWM���ͨ��ѡ��: PWM02
  PWM04 = (uint8_t)0x08, //PWM���ͨ��ѡ��: PWM04
  PWM05 = (uint8_t)0x0A, //PWM���ͨ��ѡ��: PWM05
  PWM06 = (uint8_t)0x0C, //PWM���ͨ��ѡ��: PWM06
  PWM30 = (uint8_t)0x34, //PWM���ͨ��ѡ��: PWM30
  PWM31 = (uint8_t)0x36, //PWM���ͨ��ѡ��: PWM31
} PWM_OutputPin_TypeDef;

//PWM����ģʽ
typedef enum
{
  PWM0_Edge_Aligned_Mode = (uint8_t)0x00,     //PWM���ض���ģʽ
  PWM0_Center_Alignment_Mode = (uint8_t)0x01, //PWM�м����ģʽ
} PWM_Aligned_Mode_TypeDef;

//PWM���ϼ��ģʽ
typedef enum
{
  PWM0_Latch_Mode = ((uint8_t)0x00),    //PWM���ϼ��ģʽ:����ģʽ
  PWM0_Immediate_Mode = ((uint8_t)0x20) //PWM���ϼ��ģʽ:����ģʽ
} PWM_FaultDetectionMode_TypeDef;

//PWM���ϼ���ƽѡ��
typedef enum
{
  PWM0_FaultDetectionVoltage_Low = ((uint8_t)0x00), //PWM���ϼ��͵�ƽѡ��
  PWM0_FaultDetectionVoltage_high = ((uint8_t)0x10) //PWM���ϼ��ߵ�ƽѡ��
} PWM_FaultDetectionVoltageSelect_TypeDef;

//PWM���ϼ�������ź��˲�ʱ��
typedef enum
{
  PWM0_WaveFilteringTime_0us = ((uint8_t)0x00), //PWM���ϼ�������ź��˲�ʱ��0us
  PWM0_WaveFilteringTime_1us = ((uint8_t)0x01), //PWM���ϼ�������ź��˲�ʱ��1us
  PWM0_WaveFilteringTime_4us = ((uint8_t)0x02), //PWM���ϼ�������ź��˲�ʱ��4us
  PWM0_WaveFilteringTime_16us = ((uint8_t)0x03) //PWM���ϼ�������ź��˲�ʱ��16us
} PWM_FaultDetectionWaveFilteringTime_TypeDef;

//PWM����ģʽͨ��ѡ��
typedef enum
{
  PWM00PWM01 = (uint8_t)0x00, //PWM����ģʽͨ��ѡ��:PWM00��PWM01
  PWM04PWM05 = (uint8_t)0x08, //PWM����ģʽͨ��ѡ��:PWM04��PWM05
} PWM_ComplementaryOutputPin_TypeDef;

//PWMԴѡ��
typedef enum
{
  PWM0_Type = (uint8_t)0x00, //����PWM0
  PWM3_Type = (uint8_t)0x03, //����PWM3
} PWM_Type_TypeDef;
#endif

#if defined(SC95F7610B)
//PWMԤ��Ƶѡ��
typedef enum
{
  PWM0_PRESSEL_FHRC_D1 = (uint8_t)0x00, //PWM0Ԥ��ƵΪFhrc/1
  PWM0_PRESSEL_FHRC_D2 = (uint8_t)0x10, //PWM0Ԥ��ƵΪFhrc/2
  PWM0_PRESSEL_FHRC_D4 = (uint8_t)0x20, //PWM0Ԥ��ƵΪFhrc/4
  PWM0_PRESSEL_FHRC_D8 = (uint8_t)0x30, //PWM0Ԥ��ƵΪFhrc/8
  PWM2_PRESSEL_FHRC_D1 = (uint8_t)0x02, //PWM2Ԥ��ƵΪFhrc/1
  PWM3_PRESSEL_FHRC_D1 = (uint8_t)0x03, //PWM3Ԥ��ƵΪFhrc/1
} PWM_PresSel_TypeDef;

//PWM���ͨ��ѡ��
typedef enum
{
  PWM00 = (uint8_t)0x00, //PWM���ͨ��ѡ��: PWM00
  PWM01 = (uint8_t)0x02, //PWM���ͨ��ѡ��: PWM01
  PWM02 = (uint8_t)0x04, //PWM���ͨ��ѡ��: PWM02
  PWM04 = (uint8_t)0x08, //PWM���ͨ��ѡ��: PWM04
  PWM05 = (uint8_t)0x0A, //PWM���ͨ��ѡ��: PWM05
  PWM06 = (uint8_t)0x0C, //PWM���ͨ��ѡ��: PWM06
  PWM07 = (uint8_t)0x0E, //PWM���ͨ��ѡ��: PWM07
  PWM20 = (uint8_t)0x20, //PWM���ͨ��ѡ��: PWM20
  PWM21 = (uint8_t)0x22, //PWM���ͨ��ѡ��: PWM21
  PWM30 = (uint8_t)0x34, //PWM���ͨ��ѡ��: PWM30
  PWM31 = (uint8_t)0x36, //PWM���ͨ��ѡ��: PWM31
} PWM_OutputPin_TypeDef;

//PWM����ģʽ
typedef enum
{
  PWM0_Edge_Aligned_Mode = (uint8_t)0x00,     //PWM���ض���ģʽ
  PWM0_Center_Alignment_Mode = (uint8_t)0x01, //PWM�м����ģʽ
} PWM_Aligned_Mode_TypeDef;

//PWM����ģʽͨ��ѡ��
typedef enum
{
  PWM00PWM01 = (uint8_t)0x00, //PWM����ģʽͨ��ѡ��:PWM00��PWM01
  PWM04PWM05 = (uint8_t)0x08, //PWM����ģʽͨ��ѡ��:PWM04��PWM05
  PWM06PWM07 = (uint8_t)0x0C  //PWM����ģʽͨ��ѡ��:PWM06��PWM07
} PWM_ComplementaryOutputPin_TypeDef;

//PWMԴѡ��
typedef enum
{
  PWM0_Type = (uint8_t)0x00, //����PWM0
  PWM2_Type = (uint8_t)0x02, //����PWM2
  PWM3_Type = (uint8_t)0x03, //����PWM3
} PWM_Type_TypeDef;
#endif

#if defined(SC95F7619B)
//PWMԤ��Ƶѡ��
typedef enum
{
  PWM0_PRESSEL_FHRC_D1 = (uint8_t)0x00, //PWM0Ԥ��ƵΪFhrc/1
  PWM0_PRESSEL_FHRC_D2 = (uint8_t)0x10, //PWM0Ԥ��ƵΪFhrc/2
  PWM0_PRESSEL_FHRC_D4 = (uint8_t)0x20, //PWM0Ԥ��ƵΪFhrc/4
  PWM0_PRESSEL_FHRC_D8 = (uint8_t)0x30, //PWM0Ԥ��ƵΪFhrc/8
  PWM2_PRESSEL_FHRC_D1 = (uint8_t)0x02, //PWM2Ԥ��ƵΪFhrc/1
  PWM3_PRESSEL_FHRC_D1 = (uint8_t)0x03, //PWM3Ԥ��ƵΪFhrc/1
} PWM_PresSel_TypeDef;

//PWM���ͨ��ѡ��
typedef enum
{
  PWM00 = (uint8_t)0x00, //PWM���ͨ��ѡ��: PWM00
  PWM01 = (uint8_t)0x02, //PWM���ͨ��ѡ��: PWM01
  PWM04 = (uint8_t)0x08, //PWM���ͨ��ѡ��: PWM04
  PWM05 = (uint8_t)0x0A, //PWM���ͨ��ѡ��: PWM05
  PWM06 = (uint8_t)0x0C, //PWM���ͨ��ѡ��: PWM06
  PWM07 = (uint8_t)0x0E, //PWM���ͨ��ѡ��: PWM07
  PWM20 = (uint8_t)0x20, //PWM���ͨ��ѡ��: PWM20
  PWM21 = (uint8_t)0x22, //PWM���ͨ��ѡ��: PWM21
  PWM30 = (uint8_t)0x34, //PWM���ͨ��ѡ��: PWM30
  PWM31 = (uint8_t)0x36, //PWM���ͨ��ѡ��: PWM31
} PWM_OutputPin_TypeDef;

//PWM����ģʽ
typedef enum
{
  PWM0_Edge_Aligned_Mode = (uint8_t)0x00,     //PWM���ض���ģʽ
  PWM0_Center_Alignment_Mode = (uint8_t)0x01, //PWM�м����ģʽ
} PWM_Aligned_Mode_TypeDef;

//PWM����ģʽͨ��ѡ��
typedef enum
{
  PWM00PWM01 = (uint8_t)0x00, //PWM����ģʽͨ��ѡ��:PWM00��PWM01
  PWM04PWM05 = (uint8_t)0x08, //PWM����ģʽͨ��ѡ��:PWM04��PWM05
  PWM06PWM07 = (uint8_t)0x0C  //PWM����ģʽͨ��ѡ��:PWM06��PWM07
} PWM_ComplementaryOutputPin_TypeDef;

//PWMԴѡ��
typedef enum
{
  PWM0_Type = (uint8_t)0x00, //����PWM0
  PWM2_Type = (uint8_t)0x02, //����PWM2
  PWM3_Type = (uint8_t)0x03, //����PWM3
} PWM_Type_TypeDef;
#endif

//PWM���Ÿ���ѡ��
typedef enum
{
  PWM_OUTPUTSTATE_DISABLE = ((uint8_t)0x00), //��PIN����ΪGPIO
  PWM_OUTPUTSTATE_ENABLE = ((uint8_t)0x01)   //��PIN����ΪPWM
} PWM_OutputState_TypeDef;

//PWM���������ѡ��
typedef enum
{
  PWM_POLARITY_NON_INVERT = ((uint8_t)0x00), //PWM���������
  PWM_POLARITY_INVERT = ((uint8_t)0x01)      //PWM�������
} PWM_Polarity_TypeDef;

#if defined(SC95FWxx) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)\
		|| defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)
void PWM_CmdEX(PWM_Type_TypeDef PWM_Type, FunctionalState NewState);
FlagStatus PWM_GetFlagStatusEX(PWM_Type_TypeDef PWM_Type);
void PWM_ClearFlagEX(PWM_Type_TypeDef PWM_Type);
void PWM_IndependentModeConfigEX(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle,
                                 PWM_OutputState_TypeDef PWM_OutputState);
void PWM_ComplementaryModeConfigEX(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin,
                                   uint16_t PWM_DutyCycle,
                                   PWM_OutputState_TypeDef PWM_OutputState);

void PWM_DeadTimeConfigEX(PWM_Type_TypeDef PWM_Type, uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime);
#if !defined (SC95F7610B) && !defined (SC95F7619B)
FlagStatus PWM_GetFaultDetectionFlagStatusEX(PWM_Type_TypeDef PWM_Type);
void PWM_ClearFaultDetectionFlagEX(PWM_Type_TypeDef PWM_Type);
void PWM_FaultDetectionConfigEX(PWM_Type_TypeDef PWM_Type, FunctionalState NewState);
void PWM_FaultDetectionModeConfigEX(PWM_Type_TypeDef PWM_Type,
                                    PWM_FaultDetectionMode_TypeDef FaultDetectionMode,
                                    PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect,
                                    PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime);
#endif
void PWM_ITConfigEX(PWM_Type_TypeDef PWM_Type, FunctionalState NewState, PriorityStatus Priority);
#endif

void PWM_DeInit(void);
void PWM_Init(PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period);
void PWM_OutputStateConfig(uint8_t PWM_OutputPin, PWM_OutputState_TypeDef PWM_OutputState);
void PWM_PolarityConfig(uint8_t PWM_OutputPin, PWM_Polarity_TypeDef PWM_Polarity);
void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle);
void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin,
                                 uint16_t PWM_DutyCycle);
void PWM_DeadTimeConfig(uint8_t PWM_RisingDeadTime, uint8_t PWM_fallingDeadTime);
void PWM_Cmd(FunctionalState NewState);
void PWM_ITConfig(FunctionalState NewState, PriorityStatus Priority);

void PWM_Aligned_Mode_Select(PWM_Aligned_Mode_TypeDef PWM_Aligned_Mode);
FlagStatus PWM_GetFlagStatus(void);
void PWM_ClearFlag(void);
#if !defined (SC95F7610B) && !defined (SC95F7619B)
void PWM_ClearFaultDetectionFlag(void);
void PWM_FaultDetectionConfig(FunctionalState NewState);
void PWM_FaultDetectionModeConfig(PWM_FaultDetectionMode_TypeDef FaultDetectionMode,
                                  PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect,
                                  PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime);

FlagStatus PWM_GetFaultDetectionFlagStatus(void);
#endif
#endif

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/