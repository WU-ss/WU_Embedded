//************************************************************
//  Copyright (c) 
//	文件名称	: IAP_Option_EW.h
//	作者		:
//	模块功能	: IAP固件库函数头文件
//	局部函数列表:
//  最后更正日期: 2022/1/6
// 	版本		: V1.0
//  说明        ：该文件仅适用于SC95FXX6X、SC95FXX1XB系列芯片
//*************************************************************
#ifndef _IAP_OPTION_EW_H_
#define	_IAP_OPTION_EW_H_


/**************************************************
*函数名称：void IAP_CodeProgramByteOption(unsigned long Add,unsigned char Data)
*函数功能：单Byte写入 
		   操作对象CODE区
*入口参数：Add ：需要写入的地址
*          Data：要写入的Byte
*          
*出口参数：void
**************************************************/
void IAP_CodeProgramByteOption(unsigned long Add,unsigned char Data);

/**************************************************
*函数名称：void IAP_CodeSectorEraseOption(unsigned long Add)
*函数功能：扇区擦除
		   操作对象CODE区
*入口参数：Add ：需要擦除的地址
*         
*出口参数：void
**************************************************/
void IAP_CodeSectorEraseOption(unsigned long Add);

/**************************************************
*函数名称：void IAP_EEPROMProgramByteOption(unsigned int Add,unsigned char Data)
*函数功能：单Byte写入
		   操作对象EEPROM区
*入口参数：Add ：需要写入的地址
*          Data：要写入的Byte
*          
*出口参数：void
**************************************************/
void IAP_EEPROMProgramByteOption(unsigned int Add,unsigned char Data);

/**************************************************
*函数名称：void IAP_EEPROMSectorEraseOption(unsigned int Add)
*函数功能：扇区擦除
		   操作对象EEPROM区
*入口参数：Add ：需要擦除的地址
*         
*出口参数：void
**************************************************/
void IAP_EEPROMSectorEraseOption(unsigned int Add);

#endif