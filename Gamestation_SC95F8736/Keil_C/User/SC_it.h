//************************************************************
//  Copyright (c)  
//	FileName	   : SC_it.h
//	Author		   : 
//	Function	   : Interrupt service program header file
//	Local Functions:
//  Date           : 2022/04/07
// 	Version		   : V1.3  
//*************************************************************

/***********************user_code_area*********************/
/*<UserCodeStart>*/
/*<UserCodeEnd>*/
/**********************.user_code_area.********************/

#ifndef _SC_IT_H_
#define	_SC_IT_H_

#if defined (SC95F8x1x) || defined (SC95F7x1x) || defined (SC95F8x2x)  || defined (SC95F7x2x)  || defined (SC95F8x3x)  || defined (SC95F7x3x) \
 || defined (SC95F8x6x)  || defined (SC95F7x6x)  || defined (SC95F8x1xB)  || defined (SC95F7x1xB)  || defined (SC95R751)  || defined (SC95F7610B)|| defined (SC95F7619B)
#include "sc95f_conf.h"
#else
#include "sc92f_conf.h"
#endif

extern int16_t ms_cnt;
extern uint8_t delay_begin;
//extern char Receive[40];//定义字符串缓冲区
extern unsigned char i;//指针，用于判断接收字符串
extern bit ESP8266_UartReceFlag;
extern bit ESP8266_UartSendFlag;
extern uint8_t rev_key;
extern char Recbuff[10];
extern unsigned char i;//指针，用于判断接收字符串
	
#endif

