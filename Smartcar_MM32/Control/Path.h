#ifndef __PATH_H__
#define __PATH_H__

extern u16 Straight_cnt;    //直道上标志位计数（计到15判定为直道）
extern u8 Straight_flag;    //直道标志位
extern u8 Circle_flag;      //弯道标志位
extern u8 Roundabout_flag;  //环岛标志位
extern u8 Roundabout_flag_order;   //环岛次数标志位 表示这是第几次经过环岛的交叉点
extern u8 Sancha_flag;      //三叉路标志位
extern u8 Sancha_flag_order;		//三叉路次数标志位 表示这是第几次经过三叉的交叉点 =1第一次经过 =2第二次经过

void Straight_Detect(void); //直道检测
void Circle_Detect(void); //弯道检测
void Roundabout_Detect(void); //环岛检测
void Sancha_Detect(void); //三叉路检测

void Path_Detect(void); //路径检测

#endif
