//************************************************************
//  Copyright (c) 
//	文件名称	: sc95f.h
//	作者		:
//	模块功能	: 赛元SC95F系列系统头文件
//	局部函数列表:
//  最后更正日期: 2022年7月25日日
// 	版本		: V1.10031
//  说明    :
//*************************************************************

#ifndef _sc95f_H
#define _sc95f_H

#ifdef SC95F8x1x
  #include "SC95F8x1x_C.H"
#endif
#ifdef SC95F7x1x
  #include "SC95F7x1x_C.H"
#endif
#ifdef SC95F8x2x 
  #include "SC95F8x2x_C.H"
#endif
#ifdef SC95F7x2x
  #include "SC95F7x2x_C.H"
#endif
#ifdef SC95FWxx
  #include "SC95FWxx_C.H"
#endif
#ifdef SC95F8x3x
#include "SC95F8x3x_C.H"
#endif
#ifdef SC95F7x3x
#include "SC95F7x3x_C.H"
#endif
#ifdef SC95F8x6x
#include "SC95F8x6x_C.H"
#endif
#ifdef SC95F7x6x
#include "SC95F7x6x_C.H"
#endif
#ifdef SC95F8x1xB
#include "SC95F8x1xB_C.H"
#endif
#ifdef SC95F7x1xB
#include "SC95F7x1xB_C.H"
#endif
#ifdef SC95R751
#include "SC95R751_C.H"
#endif
#ifdef SC95F7610B
#include "SC95F7610B_C.H"
#endif
#ifdef SC95F7619B
#include "SC95F7619B_C.H"
#endif
#define enableInterrupts()    EA=1	 /** 开启总中断	 **/
#define disableInterrupts()   EA=0	 /** 关闭总中断	 **/

#define     __I     volatile const   /*!< defines 'read only' permissions     */
#define     __O     volatile         /*!< defines 'write only' permissions    */
#define     __IO    volatile         /*!< defines 'read / write' permissions  */

/*!< Signed integer types  */
typedef   signed char     int8_t;
typedef   signed short    int16_t;
typedef   signed long     int32_t;

/*!< Unsigned integer types  */
typedef unsigned char     uint8_t;
typedef unsigned short    uint16_t;
typedef unsigned long     uint32_t;

typedef int32_t  s32;
typedef int16_t  s16;
typedef int8_t   s8;

typedef uint32_t  u32;
typedef uint16_t  u16;
typedef uint8_t   u8;


typedef enum {FALSE = 0, TRUE = !FALSE} bool;

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, BitStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

typedef enum {LOW = 0, HIGH = !LOW} PriorityStatus;

#define SET_BIT(SFR,BIT)				((SFR) |= (BIT))

#define CLEAR_BIT(SFR,BIT)			((SFR) &= ~(BIT))

#define READ_BIT(SFR, BIT)    	((SFR) & (BIT))

#define CLEAR_REG(SFR)        	((SFR) = (0x0))

#define WRITE_REG(SFR, VAL)   	((SFR) = (VAL))

#endif