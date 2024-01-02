/*
 * I2C.c
 *
 *  Created on: 2022��10��10��
 *      Author: WU
 */

#include <msp430.h>
#include "I2C.h"

////SDA->P10  SCL->P11
//
///**
//  * @brief  I2C��ʼ��
//  * @param  ��
//  * @retval ��
//  */
//void I2C_Init(void)
//{
//    P1DIR |= (BIT0+BIT1);//P1^0 GPIO����ΪOUTģʽ   P1^1 GPIO����Ϊ OUTģʽ
//}
//
///**
//  * @brief  I2C��ʼ
//  * @param  ��
//  * @retval ��
//  */
//void I2C_Start(void)
//{
//    P1OUT |= BIT0;// SDA��������
//    P1OUT |= BIT1;// SCL��������
//    P1OUT &= (~BIT0);// SDA��������
//    P1OUT &= (~BIT1);// SCL��������
//}
//
///**
//  * @brief  I2Cֹͣ
//  * @param  ��
//  * @retval ��
//  */
//void I2C_Stop(void)
//{
//    P1OUT &= (~BIT0);// SDA��������
//    P1OUT |= BIT1;// SCL��������
//    P1OUT |= BIT0;// SDA��������
//}
//
///**
//  * @brief  I2C����һ���ֽ�
//  * @param  Byte Ҫ���͵��ֽ�
//  * @retval ��
//  */
//void I2C_SendByte(unsigned char Byte)
//{
//    unsigned char i;
//    for(i=0;i<8;i++)
//    {
//        if((Byte&(0x80>>i))==1)
//        {
//            P1OUT |= BIT0;// SDA��������
//        }
//        else
//        {
//            P1OUT &= (~BIT0);// SDA��������
//        }
//        P1OUT |= BIT1;// SCL��������
//        P1OUT &= (~BIT1);// SCL��������
//    }
//}
//
///**
//  * @brief  I2C����Ӧ��λ
//  * @param  ��
//  * @retval ���յ���Ӧ��λ��0ΪӦ��1Ϊ��Ӧ��
//  */
//unsigned char I2C_ReceiveAck(void)
//{
//    unsigned char AckBit;
//    P1OUT |= BIT0;// SDA��������
//    P1OUT |= BIT1;// SCL��������
//    AckBit=(P1IN & BIT0); //�жϽ��յ���ACK�ź�
//    P1OUT &= (~BIT1);// SCL��������
//    return AckBit;
//}

