#ifndef __PD_H__
#define __PD_H__

#define filter 0.6f //宏定义加权微分和的系数

extern uint16 Left_Defult; //左轮默认转速
extern uint16 Right_Defult;//右轮默认转速
extern uint16 Left_Roundabout; //左轮过环岛交叉点转速	！！！该值由调试得出
extern uint16 Right_Roundabout; //右轮过环岛交叉点转速	！！！该值由调试得出
extern uint16 Left_Sancha; //左轮过环岛交叉点转速		！！！该值由调试得出
extern uint16 Right_Sancha; //右轮过环岛交叉点转速	！！！该值由调试得出
extern u16 Limit; //限制转速
extern float Kp_S; //直道 PD的比例环节P的系数		！！！该值由调试得出
extern float Kd_S; //直道 PD的积分环节D的系数		！！！该值由调试得出
extern float Kp_C; //弯道 PD的比例环节P的系数	！！！该值由调试得出
extern float Kd_C;  //弯道 PD的积分环节D的系数	！！！该值由调试得出
extern float L_PWM; //左轮PWM
extern float R_PWM; //右轮PWM
typedef struct PIDStruct
{
float Kp;
float Ki;
float Kd;
float Err;			//差值
float Err_last;
float DErr;			//差值变化率
float DErr_last;	
float OutSpeed_L;    //左轮输出速度
float OutSpeed_R;    //右轮输出速度
}PID_struct;
extern float DErr_sum; //左电机的加权误差微分(综合考量DErr与DErr_last)

void PD(float err,float autal_Kp,float autal_Kd); //电机的PD控制

void PD_Control(void); //电机的控制程序

#endif
