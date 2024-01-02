//************************************************************
//  Copyright (c)
//	�ļ�����: 			sc95f_iap.h
//	����:					
//	ģ�鹦��: 			BTM�̼��⺯��H�ļ�
//  ����������:	2022��8��10��
// 	�汾: 				V1.10005
//  ˵��:
//*************************************************************

#ifndef _sc95f_IAP_H_
#define _sc95f_IAP_H_

#include "sc95f.h"
#include "intrins.h"

#if defined (SC95F8x3x) || defined (SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)
//IAP��������ѡ��ö��
typedef enum
{
  IAP_MEMTYPE_ROM = (uint8_t)0x00, //IAP��������ΪROM
  IAP_MEMTYPE_UID = (uint8_t)0x01, //IAP��������ΪUID��ֻ��
  IAP_MEMTYPE_EEPROM = (uint8_t)0x02,	//IAP��������ΪEEPROM
  IAP_MEMTYPE_LDROM = (uint8_t)0x03,	//ֻ��LDROM�������ʱ��Ч��ֻ��
} IAP_MemType_TypeDef;
#else
typedef enum
{
  IAP_MEMTYPE_ROM = (uint8_t)0x00, //IAP��������ΪROM
  IAP_MEMTYPE_UID = (uint8_t)0x01, //IAP��������ΪUID
} IAP_MemType_TypeDef;

#endif
///MCU��λ��������ѡ��ö��
#if defined (SC95F8x3x) || defined (SC95F7x3x)
typedef enum
{
  IAP_BTLDType_APPROM = (uint8_t)0x00, //MCU��λ���APROM��λ
  IAP_BTLDType_LDROM = (uint8_t)0x80,  //MCU��λ���LDROM��λ
} IAP_BTLDType_TypeDef;
#else
typedef enum
{
  IAP_BTLDType_APPROM = (uint8_t)0x00, //MCU��λ���APROM��λ
  IAP_BTLDType_LDROM = (uint8_t)0x01,  //MCU��λ���LDROM��λ
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