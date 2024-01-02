#ifndef __ESP8266_H__
#define __ESP8266_H__

#include "SC_Init.h"
#include "SC_it.h"
extern char year;
extern char month;
extern char day;
extern char hour;
extern char minute;
extern char second;

void USCI2_SendString(char* p);
char ESP8266_Cmd_Init();	//esp8266 ≈‰÷√–≈œ¢
char ESP_get_data(void);
void Parse_BJ_Time(void);
void Clock_start_draw(void);
void Clock_run(void);

#endif