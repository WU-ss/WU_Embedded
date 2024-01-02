//************************************************************
//  Copyright (c) 
//	�ļ�����	: IAP_Option_EW.h
//	����		:
//	ģ�鹦��	: IAP�̼��⺯��ͷ�ļ�
//	�ֲ������б�:
//  ����������: 2022/1/6
// 	�汾		: V1.0
//  ˵��        �����ļ���������SC95FXX6X��SC95FXX1XBϵ��оƬ
//*************************************************************
#ifndef _IAP_OPTION_EW_H_
#define	_IAP_OPTION_EW_H_


/**************************************************
*�������ƣ�void IAP_CodeProgramByteOption(unsigned long Add,unsigned char Data)
*�������ܣ���Byteд�� 
		   ��������CODE��
*��ڲ�����Add ����Ҫд��ĵ�ַ
*          Data��Ҫд���Byte
*          
*���ڲ�����void
**************************************************/
void IAP_CodeProgramByteOption(unsigned long Add,unsigned char Data);

/**************************************************
*�������ƣ�void IAP_CodeSectorEraseOption(unsigned long Add)
*�������ܣ���������
		   ��������CODE��
*��ڲ�����Add ����Ҫ�����ĵ�ַ
*         
*���ڲ�����void
**************************************************/
void IAP_CodeSectorEraseOption(unsigned long Add);

/**************************************************
*�������ƣ�void IAP_EEPROMProgramByteOption(unsigned int Add,unsigned char Data)
*�������ܣ���Byteд��
		   ��������EEPROM��
*��ڲ�����Add ����Ҫд��ĵ�ַ
*          Data��Ҫд���Byte
*          
*���ڲ�����void
**************************************************/
void IAP_EEPROMProgramByteOption(unsigned int Add,unsigned char Data);

/**************************************************
*�������ƣ�void IAP_EEPROMSectorEraseOption(unsigned int Add)
*�������ܣ���������
		   ��������EEPROM��
*��ڲ�����Add ����Ҫ�����ĵ�ַ
*         
*���ڲ�����void
**************************************************/
void IAP_EEPROMSectorEraseOption(unsigned int Add);

#endif