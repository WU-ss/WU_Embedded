/*
 * DM130036.c
 *
 *  Created on: 2022��10��10��
 *      Author: WU
 */

#include <msp430.h>
#include "DM130036.h"
#include "I2C.h"

#define DM130036_ADDRESS  0xF3     //11110011

/**
  * @brief  DM130036д��һ���ֽ�
  * @param  WordAddress Ҫд���ֽڵĵ�ַ
  * @param  Data Ҫд�������
  * @retval ��
  */
void DM130036_WriteByte(unsigned char WordAddress,unsigned char Data)
{
    I2C_Start();
    I2C_SendByte(DM130036_ADDRESS);
    I2C_ReceiveAck();
    I2C_SendByte(WordAddress);
    I2C_ReceiveAck();
    I2C_SendByte(Data);
    I2C_ReceiveAck();
    I2C_Stop();
}

unsigned char DM130036_Send_One_String(unsigned char *astring)
{
    unsigned char i;
    for(i=0;i<5;i++)
    {
        DM130036_WriteByte(i, *(astring+i));
    }
    return(1);
}
