//************************************************************
//  Copyright (c)
//	文件名称	: sc95f_CRC.h
//	作者		:
//	模块功能	: CRC固件库函数头文件
//  最后更正日期: 2020/8/14
// 	版本		: V1.0
//  说明        :该文件仅适用于SC95F系列芯片
//*************************************************************

#ifndef _sc95f_CRC_H_
#define _sc95f_CRC_H_

#include "sc95f.h"

uint32_t CRC_All(void); //根据IAP Range选项，硬件CRC运算CODE内容，返回CRC结果
uint32_t CRC_Frame(uint8_t *buff,
                   uint8_t Length); //软件CRC，将buff指向的数组进行CRC运算，返回CRC结果

#endif

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/