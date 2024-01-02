#ifndef _MPU_USER_API_H
#define _MPU_USER_API_H

#include "stm32f10x.h"
#include "inv_mpu.h"
#include "math.h"
#include "stdio.h"
#include "inv_mpu_dmp_motion_driver.h"

extern float Pitch,Roll,Yaw;						//attitude angle
extern int16_t Direction;								// Compass Direction



/*Initialize MPU and DMP
if mode==1��Start the self-check to be at the current position as zero, 
otherwise you will not open the self-check and we'll take the water plane as a 0 Angle*/
void Mpu_Init(u8 mode);
/*Success returns 0,otherwise return 1*/
u8 Update_attitude_Angle(void);
u8 Update_accel(void);
void Update_Magnetometer(void);














#define	SMPLRT_DIV		0x19	//ox07 �����ǲ����ʣ�����ֵ��0x07(125Hz)
#define	CONFIG				0x1A	//0x06	��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//0x18 �������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define	ACCEL_CONFIG	0x1C	//0x01 ���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
#define	PWR_MGMT_1		0x6B	//��Դ��������ֵ��0x00(��������)
#define	WHO_AM_I		  0x75	//IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define MAG_ADDRESS    0x0C   //�ų���ַ
#define	GYRO_ADDRESS   0x68	  //���ݵ�ַ
#define MAG_XOUT_L		0x03
#define MAG_XOUT_H		0x04
#define MAG_YOUT_L		0x05
#define MAG_YOUT_H		0x06
#define MAG_ZOUT_L		0x07
#define MAG_ZOUT_H		0x08


#define PRINT_ACCEL     (0x01)
#define PRINT_GYRO      (0x02)
#define PRINT_QUAT      (0x04)
#define ACCEL_ON        (0x01)
#define GYRO_ON         (0x02)
#define MOTION          (0)
#define NO_MOTION       (1)


/* Starting sampling rate. */
#define DEFAULT_MPU_HZ  (100)

#define FLASH_SIZE      (512)
#define FLASH_MEM_START ((void*)0x1800)
#define q30  1073741824.0f



extern short gyro[3], accel[3];			//primary data
extern short T_X,T_Y,T_Z;		 				//Compass X,Y,Z��
extern float accel_x,accel_y,accel_z;

struct rx_s 
{
    unsigned char header[3];
    unsigned char cmd;
};


struct hal_s 
{
    unsigned char sensors;
    unsigned char dmp_on;
    unsigned char wait_for_tap;
    volatile unsigned char new_gyro;
    unsigned short report;
    unsigned short dmp_features;
    unsigned char motion_int_mode;
    struct rx_s rx;
};


enum packet_type_e
{
    PACKET_TYPE_ACCEL,
    PACKET_TYPE_GYRO,
    PACKET_TYPE_QUAT,
    PACKET_TYPE_TAP,
    PACKET_TYPE_ANDROID_ORIENT,
    PACKET_TYPE_PEDO,
    PACKET_TYPE_MISC
};

#endif
