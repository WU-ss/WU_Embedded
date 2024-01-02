/*
 * I2C.c
 *
 *  Created on: 2022年10月10日
 *      Author: WU
 */

#include <msp430.h>
#include "I2C.h"

////SDA->P10  SCL->P11
//
///**
//  * @brief  I2C初始化
//  * @param  无
//  * @retval 无
//  */
//void I2C_Init(void)
//{
//    P1DIR |= (BIT0+BIT1);//P1^0 GPIO设置为OUT模式   P1^1 GPIO设置为 OUT模式
//}
//
///**
//  * @brief  I2C开始
//  * @param  无
//  * @retval 无
//  */
//void I2C_Start(void)
//{
//    P1OUT |= BIT0;// SDA进行拉高
//    P1OUT |= BIT1;// SCL进行拉高
//    P1OUT &= (~BIT0);// SDA进行拉低
//    P1OUT &= (~BIT1);// SCL进行拉低
//}
//
///**
//  * @brief  I2C停止
//  * @param  无
//  * @retval 无
//  */
//void I2C_Stop(void)
//{
//    P1OUT &= (~BIT0);// SDA进行拉低
//    P1OUT |= BIT1;// SCL进行拉高
//    P1OUT |= BIT0;// SDA进行拉高
//}
//
///**
//  * @brief  I2C发送一个字节
//  * @param  Byte 要发送的字节
//  * @retval 无
//  */
//void I2C_SendByte(unsigned char Byte)
//{
//    unsigned char i;
//    for(i=0;i<8;i++)
//    {
//        if((Byte&(0x80>>i))==1)
//        {
//            P1OUT |= BIT0;// SDA进行拉高
//        }
//        else
//        {
//            P1OUT &= (~BIT0);// SDA进行拉低
//        }
//        P1OUT |= BIT1;// SCL进行拉高
//        P1OUT &= (~BIT1);// SCL进行拉低
//    }
//}
//
///**
//  * @brief  I2C接收应答位
//  * @param  无
//  * @retval 接收到的应答位，0为应答，1为非应答
//  */
//unsigned char I2C_ReceiveAck(void)
//{
//    unsigned char AckBit;
//    P1OUT |= BIT0;// SDA进行拉高
//    P1OUT |= BIT1;// SCL进行拉高
//    AckBit=(P1IN & BIT0); //判断接收到的ACK信号
//    P1OUT &= (~BIT1);// SCL进行拉低
//    return AckBit;
//}

