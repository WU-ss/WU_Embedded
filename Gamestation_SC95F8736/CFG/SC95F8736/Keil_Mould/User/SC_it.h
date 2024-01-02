//************************************************************
//  Copyright (c)  
//	FileName	   : SC_it.h
//	Author		   : 
//	Function	   : Interrupt service program header file
//	Local Functions:
//  Date           : 2022/04/07
// 	Version		   : V1.3  
//*************************************************************
#ifndef _SC_IT_H_
#define	_SC_IT_H_

#if defined (SC95F8x1x) || defined (SC95F7x1x) || defined (SC95F8x2x)  || defined (SC95F7x2x)  || defined (SC95F8x3x)  || defined (SC95F7x3x) \
 || defined (SC95F8x6x)  || defined (SC95F7x6x)  || defined (SC95F8x1xB)  || defined (SC95F7x1xB)  || defined (SC95R751)  || defined (SC95F7610B)|| defined (SC95F7619B)
#include "sc95f_conf.h"
#else
#include "sc92f_conf.h"
#endif

#endif

