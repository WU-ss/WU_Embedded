//************************************************************
//  Copyright (c)
//	文件名称: 			sc95f_iap.h
//	作者:					
//	模块功能: 			BTM固件库函数H文件
//  最后更正日期:	2022年8月10日
// 	版本: 				V1.10005
//  说明:
//*************************************************************

#ifndef _sc95f_IAP_H_
#define _sc95f_IAP_H_

#include "sc95f.h"
#include "intrins.h"

#if defined (SC95F8x3x) || defined (SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)
//IAP操作区域选择枚举
typedef enum
{
  IAP_MEMTYPE_ROM = (uint8_t)0x00, //IAP操作区域为ROM
  IAP_MEMTYPE_UID = (uint8_t)0x01, //IAP操作区域为UID，只读
  IAP_MEMTYPE_EEPROM = (uint8_t)0x02,	//IAP操作区域为EEPROM
  IAP_MEMTYPE_LDROM = (uint8_t)0x03,	//只在LDROM程序操作时生效，只读
} IAP_MemType_TypeDef;
#else
typedef enum
{
  IAP_MEMTYPE_ROM = (uint8_t)0x00, //IAP操作区域为ROM
  IAP_MEMTYPE_UID = (uint8_t)0x01, //IAP操作区域为UID
} IAP_MemType_TypeDef;

#endif
///MCU复位启动区域选择枚举
#if defined (SC95F8x3x) || defined (SC95F7x3x)
typedef enum
{
  IAP_BTLDType_APPROM = (uint8_t)0x00, //MCU复位后从APROM复位
  IAP_BTLDType_LDROM = (uint8_t)0x80,  //MCU复位后从LDROM复位
} IAP_BTLDType_TypeDef;
#else
typedef enum
{
  IAP_BTLDType_APPROM = (uint8_t)0x00, //MCU复位后从APROM复位
  IAP_BTLDType_LDROM = (uint8_t)0x01,  //MCU复位后从LDROM复位
} IAP_BTLDType_TypeDef;
#endif

void IAP_DeInit(void);
ErrorStatus IAP_ProgramByte(uint32_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType,
                            uint8_t WriteTimeLimit);
uint8_t IAP_ProgramByteArray(uint32_t Address, uint8_t* ByteArray, uint8_t ArraySize, IAP_MemType_TypeDef IAP_MemType,
                             uint8_t WriteTimeLimit);
uint8_t IAP_ReadByte(uint32_t Address, IAP_MemType_TypeDef IAP_MemType);
uint8_t IAP_ReadByteArray(uint32_t Address, uint8_t* ByteArray, uint8_t ArraySize, IAP_MemType_TypeDef IAP_MemType);
void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint32_t IAP_SectorEraseAddress,
                     uint8_t WriteTimeLimit);
void IAP_BootLoaderControl(IAP_BTLDType_TypeDef IAP_BTLDType);

#endif

/******************* (C) COPYRIGHT 2022 SinOne Microelectronics *****END OF FILE****/