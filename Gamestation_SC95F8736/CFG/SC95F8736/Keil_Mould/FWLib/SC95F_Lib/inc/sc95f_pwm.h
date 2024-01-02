//************************************************************
//  Copyright (c) 
//	文件名称: 			sc95f_pwm.h
//	作者:
//	模块功能: 			PWM固件库函数H文件
//  最后更正日期:	2022年7月20日
// 	版本: 				V1.10006
//  说明:					该文件仅适用于SC95F系列芯片
//*************************************************************

#ifndef _sc95f_PWM_H_
#define _sc95f_PWM_H_

#include "sc95f.h"
#if defined(SC95F8x1x) || defined(SC95F7x1x)
//PWM输出通道选择
typedef enum
{
  PWM40 = (uint8_t)0x01, //PWM输出通道选择:PWM40
  PWM41 = (uint8_t)0x02, //PWM输出通道选择:PWM41
  PWM42 = (uint8_t)0x04, //PWM输出通道选择:PWM42
  PWM43 = (uint8_t)0x08, //PWM输出通道选择:PWM43
  PWM50 = (uint8_t)0x10, //PWM输出通道选择:PWM50
  PWM51 = (uint8_t)0x20, //PWM输出通道选择:PWM51
  PWM52 = (uint8_t)0x40, //PWM输出通道选择:PWM52
  PWM53 = (uint8_t)0x80  //PWM输出通道选择:PWM53
} PWM_OutputPin_TypeDef;

// PWM预分频
typedef enum
{
  PWM_PRESSEL_FHRC_D1 = (uint8_t)0x00, //PWM预分频为Fhrc/1
  PWM_PRESSEL_FHRC_D2 = (uint8_t)0x10, //PWM预分频为Fhrc/2
  PWM_PRESSEL_FHRC_D4 = (uint8_t)0x20, //PWM预分频为Fhrc/4
  PWM_PRESSEL_FHRC_D8 = (uint8_t)0x30  //PWM预分频为Fhrc/8
} PWM_PresSel_TypeDef;

//PWM互补模式通道选择
typedef enum
{
  PWM40PWM41 = (uint8_t)0x00, //PWM互补模式通道选择:PWM40、PWM41
  PWM42PWM43 = (uint8_t)0x02, //PWM互补模式通道选择:PWM42、PWM43
  PWM50PWM51 = (uint8_t)0x04, //PWM互补模式通道选择:PWM50、PWM51
  PWM52PWM53 = (uint8_t)0x06  //PWM互补模式通道选择:PWM52、PWM53
} PWM_ComplementaryOutputPin_TypeDef;

//PWM故障检测模式
typedef enum
{
  PWM_Latch_Mode = ((uint8_t)0x00),    //PWM故障检测模式:锁存模式
  PWM_Immediate_Mode = ((uint8_t)0x20) //PWM故障检测模式:立即模式
} PWM_FaultDetectionMode_TypeDef;

//PWM故障检测电平选择
typedef enum
{
  PWM_FaultDetectionVoltage_Low = ((uint8_t)0x00), //PWM故障检测低电平选择
  PWM_FaultDetectionVoltage_high = ((uint8_t)0x10) //PWM故障检测高电平选择
} PWM_FaultDetectionVoltageSelect_TypeDef;

typedef enum //PWM故障检测输入信号滤波时间
{
  PWM_WaveFilteringTime_0us = ((uint8_t)0x00), //PWM故障检测输入信号滤波时间0us
  PWM_WaveFilteringTime_1us = ((uint8_t)0x01), //PWM故障检测输入信号滤波时间1us
  PWM_WaveFilteringTime_4us = ((uint8_t)0x02), //PWM故障检测输入信号滤波时间4us
  PWM_WaveFilteringTime_16us = ((uint8_t)0x03) //PWM故障检测输入信号滤波时间16us
} PWM_FaultDetectionWaveFilteringTime_TypeDef;

//PWM对齐模式
typedef enum
{
  PWM_Edge_Aligned_Mode = (uint8_t)0x00,    //PWM边沿对齐模式
  PWM_Center_Alignment_Mode = (uint8_t)0x01 //PWM中间对齐模式
} PWM_Aligned_Mode_TypeDef;

#endif

#if defined(SC95F8x2x) || defined(SC95F7x2x)
// PWM预分频
typedef enum
{
  PWM_PRESSEL_FHRC_D1 = (uint8_t)0x00, //PWM预分频为FHRC/1
  PWM_PRESSEL_FHRC_D2 = (uint8_t)0x10, //PWM预分频为FHRC/2
  PWM_PRESSEL_FHRC_D4 = (uint8_t)0x20, //PWM预分频为FHRC/4
  PWM_PRESSEL_FHRC_D8 = (uint8_t)0x30  //PWM预分频为FHRC/8
} PWM_PresSel_TypeDef;

//PWM输出通道选择
typedef enum
{
  PWM0 = (uint8_t)0x01, //PWM输出通道选择:PWM0
  PWM1 = (uint8_t)0x02, //PWM输出通道选择:PWM1
  PWM2 = (uint8_t)0x04, //PWM输出通道选择:PWM2
  PWM3 = (uint8_t)0x08, //PWM输出通道选择:PWM3
  PWM4 = (uint8_t)0x10, //PWM输出通道选择:PWM4
  PWM5 = (uint8_t)0x20, //PWM输出通道选择:PWM5
  PWM6 = (uint8_t)0x40, //PWM输出通道选择:PWM6
  PWM7 = (uint8_t)0x80, //PWM输出通道选择:PWM7
} PWM_OutputPin_TypeDef;

//PWM对齐模式
typedef enum
{
  PWM_Edge_Aligned_Mode = (uint8_t)0x00,    //PWM边沿对齐模式
  PWM_Center_Alignment_Mode = (uint8_t)0x01 //PWM中间对齐模式
} PWM_Aligned_Mode_TypeDef;

//PWM故障检测模式
typedef enum
{
  PWM_Latch_Mode = ((uint8_t)0x00),    //PWM故障检测模式:锁存模式
  PWM_Immediate_Mode = ((uint8_t)0x20) //PWM故障检测模式:立即模式
} PWM_FaultDetectionMode_TypeDef;

//PWM故障检测电平选择
typedef enum
{
  PWM_FaultDetectionVoltage_Low = ((uint8_t)0x00), //PWM故障检测低电平选择
  PWM_FaultDetectionVoltage_high = ((uint8_t)0x10) //PWM故障检测高电平选择
} PWM_FaultDetectionVoltageSelect_TypeDef;

//PWM故障检测输入信号滤波时间
typedef enum
{
  PWM_WaveFilteringTime_0us = ((uint8_t)0x00), //PWM故障检测输入信号滤波时间0us
  PWM_WaveFilteringTime_1us = ((uint8_t)0x01), //PWM故障检测输入信号滤波时间1us
  PWM_WaveFilteringTime_4us = ((uint8_t)0x02), //PWM故障检测输入信号滤波时间4us
  PWM_WaveFilteringTime_16us = ((uint8_t)0x03) //PWM故障检测输入信号滤波时间16us
} PWM_FaultDetectionWaveFilteringTime_TypeDef;

//PWM互补模式通道选择
typedef enum
{
  PWM0PWM1 = (uint8_t)0x00, //PWM互补模式通道选择:PWM0、PWM1
  PWM2PWM3 = (uint8_t)0x01, //PWM互补模式通道选择:PWM2、PWM3
  PWM4PWM5 = (uint8_t)0x02, //PWM互补模式通道选择:PWM4、PWM5
  PWM6PWM7 = (uint8_t)0x03  //PWM互补模式通道选择:PWM6、PWM7
} PWM_ComplementaryOutputPin_TypeDef;

#endif

#if defined(SC95FWxx)
//PWM预分频选择
typedef enum
{
  PWM0_PRESSEL_FHRC_D1 = (uint8_t)0x00, //PWM0预分频为Fhrc/1
  PWM0_PRESSEL_FHRC_D2 = (uint8_t)0x10, //PWM0预分频为Fhrc/2
  PWM0_PRESSEL_FHRC_D4 = (uint8_t)0x20, //PWM0预分频为Fhrc/4
  PWM0_PRESSEL_FHRC_D8 = (uint8_t)0x30, //PWM0预分频为Fhrc/8
  PWM1_PRESSEL_FHRC_D1 = (uint8_t)0x01, //PWM1预分频为Fhrc/1
  PWM1_PRESSEL_FHRC_D2 = (uint8_t)0x11, //PWM1预分频为Fhrc/2
  PWM1_PRESSEL_FHRC_D4 = (uint8_t)0x21, //PWM1预分频为Fhrc/4
  PWM1_PRESSEL_FHRC_D8 = (uint8_t)0x31, //PWM1预分频为Fhrc/8
} PWM_PresSel_TypeDef;

//PWM输出通道选择
typedef enum
{
  PWM00 = (uint8_t)0x00, //PWM输出通道选择: PWM00
  PWM01 = (uint8_t)0x02, //PWM输出通道选择: PWM01
  PWM02 = (uint8_t)0x04, //PWM输出通道选择: PWM02
  PWM03 = (uint8_t)0x06, //PWM输出通道选择: PWM03
  PWM04 = (uint8_t)0x08, //PWM输出通道选择: PWM04
  PWM05 = (uint8_t)0x0A, //PWM输出通道选择: PWM05
  PWM06 = (uint8_t)0x0C, //PWM输出通道选择: PWM06
  PWM07 = (uint8_t)0x0E, //PWM输出通道选择: PWM07
  PWM10 = (uint8_t)0x10, //PWM输出通道选择: PWM10
  PWM11 = (uint8_t)0x12, //PWM输出通道选择: PWM11
  PWM12 = (uint8_t)0x14, //PWM输出通道选择: PWM12
  PWM13 = (uint8_t)0x16, //PWM输出通道选择: PWM13
  PWM14 = (uint8_t)0x18, //PWM输出通道选择: PWM14
  PWM15 = (uint8_t)0x1A, //PWM输出通道选择: PWM15
  PWM16 = (uint8_t)0x1C, //PWM输出通道选择: PWM16
  PWM17 = (uint8_t)0x1E, //PWM输出通道选择: PWM17
  PWM20 = (uint8_t)0x20, //PWM输出通道选择: PWM20
  PWM21 = (uint8_t)0x22, //PWM输出通道选择: PWM21
  PWM22 = (uint8_t)0x24, //PWM输出通道选择: PWM22
  PWM23 = (uint8_t)0x26, //PWM输出通道选择: PWM23
  PWM24 = (uint8_t)0x28, //PWM输出通道选择: PWM24
  PWM25 = (uint8_t)0x2A, //PWM输出通道选择: PWM25
  PWM26 = (uint8_t)0x2C, //PWM输出通道选择: PWM26
  PWM27 = (uint8_t)0x2E, //PWM输出通道选择: PWM27
  PWM30 = (uint8_t)0x30, //PWM输出通道选择: PWM30
  PWM31 = (uint8_t)0x32, //PWM输出通道选择: PWM31
  PWM32 = (uint8_t)0x34, //PWM输出通道选择: PWM32
  PWM33 = (uint8_t)0x36, //PWM输出通道选择: PWM33
  PWM34 = (uint8_t)0x38, //PWM输出通道选择: PWM34
  PWM35 = (uint8_t)0x3A, //PWM输出通道选择: PWM25
  PWM36 = (uint8_t)0x3C, //PWM输出通道选择: PWM26
  PWM37 = (uint8_t)0x3E, //PWM输出通道选择: PWM27
  PWM40 = (uint8_t)0x40, //PWM输出通道选择: PWM40
  PWM41 = (uint8_t)0x42, //PWM输出通道选择: PWM41
  PWM42 = (uint8_t)0x44, //PWM输出通道选择: PWM42
  PWM43 = (uint8_t)0x46, //PWM输出通道选择: PWM53
  PWM50 = (uint8_t)0x48, //PWM输出通道选择: PWM50
  PWM51 = (uint8_t)0x4A, //PWM输出通道选择: PWM51
  PWM52 = (uint8_t)0x4C, //PWM输出通道选择: PWM52
  PWM53 = (uint8_t)0x4E, //PWM输出通道选择: PWM53
} PWM_OutputPin_TypeDef;

//PWM对齐模式
typedef enum
{
  PWM0_Edge_Aligned_Mode = (uint8_t)0x00,     //PWM边沿对齐模式
  PWM0_Center_Alignment_Mode = (uint8_t)0x01, //PWM中间对齐模式
  PWM1_Edge_Aligned_Mode = (uint8_t)0x10,     //PWM边沿对齐模式
  PWM1_Center_Alignment_Mode = (uint8_t)0x11  //PWM中间对齐模式
} PWM_Aligned_Mode_TypeDef;

//PWM故障检测模式
typedef enum
{
  PWM1_Latch_Mode = ((uint8_t)0x00),    //PWM故障检测模式:锁存模式
  PWM1_Immediate_Mode = ((uint8_t)0x20) //PWM故障检测模式:立即模式
} PWM_FaultDetectionMode_TypeDef;

//PWM故障检测电平选择
typedef enum
{
  PWM1_FaultDetectionVoltage_Low = ((uint8_t)0x00), //PWM故障检测低电平选择
  PWM1_FaultDetectionVoltage_high = ((uint8_t)0x10) //PWM故障检测高电平选择
} PWM_FaultDetectionVoltageSelect_TypeDef;

//PWM故障检测输入信号滤波时间
typedef enum
{
  PWM1_WaveFilteringTime_0us = ((uint8_t)0x00), //PWM故障检测输入信号滤波时间0us
  PWM1_WaveFilteringTime_1us = ((uint8_t)0x01), //PWM故障检测输入信号滤波时间1us
  PWM1_WaveFilteringTime_4us = ((uint8_t)0x02), //PWM故障检测输入信号滤波时间4us
  PWM1_WaveFilteringTime_16us = ((uint8_t)0x03) //PWM故障检测输入信号滤波时间16us
} PWM_FaultDetectionWaveFilteringTime_TypeDef;

//PWM互补模式通道选择
typedef enum
{
  PWM40PWM41 = (uint8_t)0x00, //PWM互补模式通道选择:PWM40、PWM11
  PWM42PWM43 = (uint8_t)0x01, //PWM互补模式通道选择:PWM12、PWM13
  PWM50PWM51 = (uint8_t)0x02, //PWM互补模式通道选择:PWM50、PWM51
  PWM52PWM53 = (uint8_t)0x03  //PWM互补模式通道选择:PWM52、PWM53
} PWM_ComplementaryOutputPin_TypeDef;

//PWM源选择
typedef enum
{
  PWM0_Type = (uint8_t)0x00, //操作PWM0
  PWM1_Type = (uint8_t)0x01, //操作PWM1
} PWM_Type_TypeDef;
#endif
#if defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)
//PWM预分频选择
typedef enum
{
  PWM0_PRESSEL_FHRC_D1 = (uint8_t)0x00, //PWM0预分频为Fhrc/1
  PWM0_PRESSEL_FHRC_D2 = (uint8_t)0x10, //PWM0预分频为Fhrc/2
  PWM0_PRESSEL_FHRC_D4 = (uint8_t)0x20, //PWM0预分频为Fhrc/4
  PWM0_PRESSEL_FHRC_D8 = (uint8_t)0x30, //PWM0预分频为Fhrc/8
  PWM2_PRESSEL_FHRC_D1 = (uint8_t)0x02, //PWM2预分频为Fhrc/1
  PWM3_PRESSEL_FHRC_D1 = (uint8_t)0x03, //PWM3预分频为Fhrc/1
  PWM4_PRESSEL_FHRC_D1 = (uint8_t)0x04, //PWM4预分频为Fhrc/1
} PWM_PresSel_TypeDef;

//PWM输出通道选择
typedef enum
{
  PWM00 = (uint8_t)0x00, //PWM输出通道选择: PWM00
  PWM01 = (uint8_t)0x02, //PWM输出通道选择: PWM01
  PWM02 = (uint8_t)0x04, //PWM输出通道选择: PWM02
  PWM03 = (uint8_t)0x06, //PWM输出通道选择: PWM03
  PWM04 = (uint8_t)0x08, //PWM输出通道选择: PWM04
  PWM05 = (uint8_t)0x0A, //PWM输出通道选择: PWM05
  PWM06 = (uint8_t)0x0C, //PWM输出通道选择: PWM06
  PWM07 = (uint8_t)0x0E, //PWM输出通道选择: PWM07
  PWM20 = (uint8_t)0x20, //PWM输出通道选择: PWM20
  PWM21 = (uint8_t)0x22, //PWM输出通道选择: PWM21
  PWM30 = (uint8_t)0x34, //PWM输出通道选择: PWM30
  PWM31 = (uint8_t)0x36, //PWM输出通道选择: PWM31
  PWM40 = (uint8_t)0x48, //PWM输出通道选择: PWM40
  PWM41 = (uint8_t)0x4A, //PWM输出通道选择: PWM41
} PWM_OutputPin_TypeDef;

//PWM对齐模式
typedef enum
{
  PWM0_Edge_Aligned_Mode = (uint8_t)0x00,     //PWM边沿对齐模式
  PWM0_Center_Alignment_Mode = (uint8_t)0x01, //PWM中间对齐模式
} PWM_Aligned_Mode_TypeDef;

//PWM故障检测模式
typedef enum
{
  PWM0_Latch_Mode = ((uint8_t)0x00),    //PWM故障检测模式:锁存模式
  PWM0_Immediate_Mode = ((uint8_t)0x20) //PWM故障检测模式:立即模式
} PWM_FaultDetectionMode_TypeDef;

//PWM故障检测电平选择
typedef enum
{
  PWM0_FaultDetectionVoltage_Low = ((uint8_t)0x00), //PWM故障检测低电平选择
  PWM0_FaultDetectionVoltage_high = ((uint8_t)0x10) //PWM故障检测高电平选择
} PWM_FaultDetectionVoltageSelect_TypeDef;

//PWM故障检测输入信号滤波时间
typedef enum
{
  PWM0_WaveFilteringTime_0us = ((uint8_t)0x00), //PWM故障检测输入信号滤波时间0us
  PWM0_WaveFilteringTime_1us = ((uint8_t)0x01), //PWM故障检测输入信号滤波时间1us
  PWM0_WaveFilteringTime_4us = ((uint8_t)0x02), //PWM故障检测输入信号滤波时间4us
  PWM0_WaveFilteringTime_16us = ((uint8_t)0x03) //PWM故障检测输入信号滤波时间16us
} PWM_FaultDetectionWaveFilteringTime_TypeDef;

//PWM互补模式通道选择
typedef enum
{
  PWM00PWM01 = (uint8_t)0x00, //PWM互补模式通道选择:PWM00、PWM01
  PWM02PWM03 = (uint8_t)0x04, //PWM互补模式通道选择:PWM02、PWM03
  PWM04PWM05 = (uint8_t)0x08, //PWM互补模式通道选择:PWM04、PWM05
  PWM06PWM07 = (uint8_t)0x0C  //PWM互补模式通道选择:PWM06、PWM07
} PWM_ComplementaryOutputPin_TypeDef;

//PWM源选择
typedef enum
{
  PWM0_Type = (uint8_t)0x00, //操作PWM0
  PWM2_Type = (uint8_t)0x02, //操作PWM2
  PWM3_Type = (uint8_t)0x03, //操作PWM3
  PWM4_Type = (uint8_t)0x04, //操作PWM4
} PWM_Type_TypeDef;
#endif

#if defined (SC95R751)
//PWM预分频选择
typedef enum
{
  PWM0_PRESSEL_FHRC_D1 = (uint8_t)0x00, //PWM0预分频为Fhrc/1
  PWM0_PRESSEL_FHRC_D2 = (uint8_t)0x10, //PWM0预分频为Fhrc/2
  PWM0_PRESSEL_FHRC_D4 = (uint8_t)0x20, //PWM0预分频为Fhrc/4
  PWM0_PRESSEL_FHRC_D8 = (uint8_t)0x30, //PWM0预分频为Fhrc/8
  PWM3_PRESSEL_FHRC_D1 = (uint8_t)0x03, //PWM3预分频为Fhrc/1
} PWM_PresSel_TypeDef;

//PWM输出通道选择
typedef enum
{
  PWM00 = (uint8_t)0x00, //PWM输出通道选择: PWM00
  PWM01 = (uint8_t)0x02, //PWM输出通道选择: PWM01
  PWM02 = (uint8_t)0x04, //PWM输出通道选择: PWM02
  PWM04 = (uint8_t)0x08, //PWM输出通道选择: PWM04
  PWM05 = (uint8_t)0x0A, //PWM输出通道选择: PWM05
  PWM06 = (uint8_t)0x0C, //PWM输出通道选择: PWM06
  PWM30 = (uint8_t)0x34, //PWM输出通道选择: PWM30
  PWM31 = (uint8_t)0x36, //PWM输出通道选择: PWM31
} PWM_OutputPin_TypeDef;

//PWM对齐模式
typedef enum
{
  PWM0_Edge_Aligned_Mode = (uint8_t)0x00,     //PWM边沿对齐模式
  PWM0_Center_Alignment_Mode = (uint8_t)0x01, //PWM中间对齐模式
} PWM_Aligned_Mode_TypeDef;

//PWM故障检测模式
typedef enum
{
  PWM0_Latch_Mode = ((uint8_t)0x00),    //PWM故障检测模式:锁存模式
  PWM0_Immediate_Mode = ((uint8_t)0x20) //PWM故障检测模式:立即模式
} PWM_FaultDetectionMode_TypeDef;

//PWM故障检测电平选择
typedef enum
{
  PWM0_FaultDetectionVoltage_Low = ((uint8_t)0x00), //PWM故障检测低电平选择
  PWM0_FaultDetectionVoltage_high = ((uint8_t)0x10) //PWM故障检测高电平选择
} PWM_FaultDetectionVoltageSelect_TypeDef;

//PWM故障检测输入信号滤波时间
typedef enum
{
  PWM0_WaveFilteringTime_0us = ((uint8_t)0x00), //PWM故障检测输入信号滤波时间0us
  PWM0_WaveFilteringTime_1us = ((uint8_t)0x01), //PWM故障检测输入信号滤波时间1us
  PWM0_WaveFilteringTime_4us = ((uint8_t)0x02), //PWM故障检测输入信号滤波时间4us
  PWM0_WaveFilteringTime_16us = ((uint8_t)0x03) //PWM故障检测输入信号滤波时间16us
} PWM_FaultDetectionWaveFilteringTime_TypeDef;

//PWM互补模式通道选择
typedef enum
{
  PWM00PWM01 = (uint8_t)0x00, //PWM互补模式通道选择:PWM00、PWM01
  PWM04PWM05 = (uint8_t)0x08, //PWM互补模式通道选择:PWM04、PWM05
} PWM_ComplementaryOutputPin_TypeDef;

//PWM源选择
typedef enum
{
  PWM0_Type = (uint8_t)0x00, //操作PWM0
  PWM3_Type = (uint8_t)0x03, //操作PWM3
} PWM_Type_TypeDef;
#endif

#if defined(SC95F7610B)
//PWM预分频选择
typedef enum
{
  PWM0_PRESSEL_FHRC_D1 = (uint8_t)0x00, //PWM0预分频为Fhrc/1
  PWM0_PRESSEL_FHRC_D2 = (uint8_t)0x10, //PWM0预分频为Fhrc/2
  PWM0_PRESSEL_FHRC_D4 = (uint8_t)0x20, //PWM0预分频为Fhrc/4
  PWM0_PRESSEL_FHRC_D8 = (uint8_t)0x30, //PWM0预分频为Fhrc/8
  PWM2_PRESSEL_FHRC_D1 = (uint8_t)0x02, //PWM2预分频为Fhrc/1
  PWM3_PRESSEL_FHRC_D1 = (uint8_t)0x03, //PWM3预分频为Fhrc/1
} PWM_PresSel_TypeDef;

//PWM输出通道选择
typedef enum
{
  PWM00 = (uint8_t)0x00, //PWM输出通道选择: PWM00
  PWM01 = (uint8_t)0x02, //PWM输出通道选择: PWM01
  PWM02 = (uint8_t)0x04, //PWM输出通道选择: PWM02
  PWM04 = (uint8_t)0x08, //PWM输出通道选择: PWM04
  PWM05 = (uint8_t)0x0A, //PWM输出通道选择: PWM05
  PWM06 = (uint8_t)0x0C, //PWM输出通道选择: PWM06
  PWM07 = (uint8_t)0x0E, //PWM输出通道选择: PWM07
  PWM20 = (uint8_t)0x20, //PWM输出通道选择: PWM20
  PWM21 = (uint8_t)0x22, //PWM输出通道选择: PWM21
  PWM30 = (uint8_t)0x34, //PWM输出通道选择: PWM30
  PWM31 = (uint8_t)0x36, //PWM输出通道选择: PWM31
} PWM_OutputPin_TypeDef;

//PWM对齐模式
typedef enum
{
  PWM0_Edge_Aligned_Mode = (uint8_t)0x00,     //PWM边沿对齐模式
  PWM0_Center_Alignment_Mode = (uint8_t)0x01, //PWM中间对齐模式
} PWM_Aligned_Mode_TypeDef;

//PWM互补模式通道选择
typedef enum
{
  PWM00PWM01 = (uint8_t)0x00, //PWM互补模式通道选择:PWM00、PWM01
  PWM04PWM05 = (uint8_t)0x08, //PWM互补模式通道选择:PWM04、PWM05
  PWM06PWM07 = (uint8_t)0x0C  //PWM互补模式通道选择:PWM06、PWM07
} PWM_ComplementaryOutputPin_TypeDef;

//PWM源选择
typedef enum
{
  PWM0_Type = (uint8_t)0x00, //操作PWM0
  PWM2_Type = (uint8_t)0x02, //操作PWM2
  PWM3_Type = (uint8_t)0x03, //操作PWM3
} PWM_Type_TypeDef;
#endif

#if defined(SC95F7619B)
//PWM预分频选择
typedef enum
{
  PWM0_PRESSEL_FHRC_D1 = (uint8_t)0x00, //PWM0预分频为Fhrc/1
  PWM0_PRESSEL_FHRC_D2 = (uint8_t)0x10, //PWM0预分频为Fhrc/2
  PWM0_PRESSEL_FHRC_D4 = (uint8_t)0x20, //PWM0预分频为Fhrc/4
  PWM0_PRESSEL_FHRC_D8 = (uint8_t)0x30, //PWM0预分频为Fhrc/8
  PWM2_PRESSEL_FHRC_D1 = (uint8_t)0x02, //PWM2预分频为Fhrc/1
  PWM3_PRESSEL_FHRC_D1 = (uint8_t)0x03, //PWM3预分频为Fhrc/1
} PWM_PresSel_TypeDef;

//PWM输出通道选择
typedef enum
{
  PWM00 = (uint8_t)0x00, //PWM输出通道选择: PWM00
  PWM01 = (uint8_t)0x02, //PWM输出通道选择: PWM01
  PWM04 = (uint8_t)0x08, //PWM输出通道选择: PWM04
  PWM05 = (uint8_t)0x0A, //PWM输出通道选择: PWM05
  PWM06 = (uint8_t)0x0C, //PWM输出通道选择: PWM06
  PWM07 = (uint8_t)0x0E, //PWM输出通道选择: PWM07
  PWM20 = (uint8_t)0x20, //PWM输出通道选择: PWM20
  PWM21 = (uint8_t)0x22, //PWM输出通道选择: PWM21
  PWM30 = (uint8_t)0x34, //PWM输出通道选择: PWM30
  PWM31 = (uint8_t)0x36, //PWM输出通道选择: PWM31
} PWM_OutputPin_TypeDef;

//PWM对齐模式
typedef enum
{
  PWM0_Edge_Aligned_Mode = (uint8_t)0x00,     //PWM边沿对齐模式
  PWM0_Center_Alignment_Mode = (uint8_t)0x01, //PWM中间对齐模式
} PWM_Aligned_Mode_TypeDef;

//PWM互补模式通道选择
typedef enum
{
  PWM00PWM01 = (uint8_t)0x00, //PWM互补模式通道选择:PWM00、PWM01
  PWM04PWM05 = (uint8_t)0x08, //PWM互补模式通道选择:PWM04、PWM05
  PWM06PWM07 = (uint8_t)0x0C  //PWM互补模式通道选择:PWM06、PWM07
} PWM_ComplementaryOutputPin_TypeDef;

//PWM源选择
typedef enum
{
  PWM0_Type = (uint8_t)0x00, //操作PWM0
  PWM2_Type = (uint8_t)0x02, //操作PWM2
  PWM3_Type = (uint8_t)0x03, //操作PWM3
} PWM_Type_TypeDef;
#endif

//PWM引脚复用选择
typedef enum
{
  PWM_OUTPUTSTATE_DISABLE = ((uint8_t)0x00), //该PIN脚作为GPIO
  PWM_OUTPUTSTATE_ENABLE = ((uint8_t)0x01)   //该PIN脚作为PWM
} PWM_OutputState_TypeDef;

//PWM输出正反向选择
typedef enum
{
  PWM_POLARITY_NON_INVERT = ((uint8_t)0x00), //PWM输出不反向
  PWM_POLARITY_INVERT = ((uint8_t)0x01)      //PWM输出反向
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