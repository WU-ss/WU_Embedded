#include "headfile.h"

//匿名上位机显示波形
uint8_t testdatatosend[50];

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) +1))

void Test_Send_User(uint16 data1, uint16 data2, uint16 data3,uint16 data4,uint16 data5) 
{
 uint8_t _cnt=0;
 
 testdatatosend[_cnt++]=0xAA;
 testdatatosend[_cnt++]=0x05;
 testdatatosend[_cnt++]=0xAF;
 testdatatosend[_cnt++]=0xF1;
 testdatatosend[_cnt++]=0;
 
 testdatatosend[_cnt++]=BYTE1(data1);
 testdatatosend[_cnt++]=BYTE0(data1);
 
 testdatatosend[_cnt++]=BYTE1(data2);
 testdatatosend[_cnt++]=BYTE0(data2);
 
 testdatatosend[_cnt++]=BYTE1(data3);
 testdatatosend[_cnt++]=BYTE0(data3);
 
 testdatatosend[_cnt++]=BYTE1(data4);
 testdatatosend[_cnt++]=BYTE0(data4);
 
 testdatatosend[_cnt++]=BYTE1(data5);
 testdatatosend[_cnt++]=BYTE0(data5);
 
 testdatatosend[4] = _cnt-5;
 
 uint8_t sum = 0; 
 for(uint8_t i=0;i<_cnt;i++)
  sum += testdatatosend[i];
 
 testdatatosend[_cnt++]=sum; 
 
  seekfree_wireless_send_buff(testdatatosend,_cnt);
}
