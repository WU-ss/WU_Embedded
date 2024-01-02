#include "mpu6050.h"
MPU6050_Angle dat;
MPU6050_Ang_velocity dat1;
/****************************************************************************** 
* �������ܣ� MPU6050 ��ʼ������ 
* ��������� �� 
* ��������� �� 
* ����ֵ �� �� 
* �� ע�� ���� MPU6050 ������Χ���� 2000 ��/s �� 4g 
******************************************************************************/
void MPU6050_Init(void)
{
    IIC_Write_Byte(SlaveAddress,PWR_MGMT_1, 	0x00);    //�������״̬     
    IIC_Write_Byte(SlaveAddress,SMPLRT_DIV, 	0x07);    //�����ǲ����ʣ�����ֵ��0x07(125Hz)     
    IIC_Write_Byte(SlaveAddress,CONFIG_6050, 	0x06);    //��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)     
    IIC_Write_Byte(SlaveAddress,GYRO_CONFIG, 	0x18);  	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)     
    IIC_Write_Byte(SlaveAddress,ACCEL_CONFIG, 0x08);  	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬4G��5Hz) 
}

/****************************************************************************** 
* �������ܣ� �����������Ĵ������ϳ� 16 λ���� 
* ��������� regAddr�����ݵ�λ�Ĵ�����ַ 
* ��������� �� 
* ����ֵ �� data��2 ���Ĵ����ϳɵ� 16 λ���� 
******************************************************************************/
int16_t MPU6050_Get_Data(uint8_t regAddr)
{
    uint8_t Data_H, Data_L;
    uint16_t dat;   
    Data_H = IIC_Read_Byte(SlaveAddress,regAddr);
    Data_L = IIC_Read_Byte(SlaveAddress,regAddr+1);
    dat = (Data_H << 8) | Data_L;  // �ϳ����� 
    return dat;
}

/****************************************************************************** 
* �������ܣ� ���ڴ�ӡ 6050 ��������ȡ��������ٶȡ������Ǽ��¶����� 
* ��������� �� 
* ��������� �� 
* ����ֵ �� �� 
******************************************************************************/
void MPU6050_Display(void)
{
    /* ��ӡ x, y, z ����ٶ� */
    printf("ACCEL_X: %d\t", MPU6050_Get_Data(ACCEL_XOUT_H) + X_ACCEL_OFFSET);
    printf("ACCEL_Y: %d\t", MPU6050_Get_Data(ACCEL_YOUT_H) + Y_ACCEL_OFFSET);
    printf("ACCEL_Z: %d\t", MPU6050_Get_Data(ACCEL_ZOUT_H) + Z_ACCEL_OFFSET);
    
    /* ��ӡ�¶� */
    printf("TEMP: %0.2f\t", MPU6050_Get_Data(TEMP_OUT_H) / 340.0 + 36.53);
    
    /* ��ӡ x, y, z ����ٶ� */
    printf("GYRO_X: %d\t", MPU6050_Get_Data(GYRO_XOUT_H) + X_GYRO_OFFSET);
    printf("GYRO_Y: %d\t", MPU6050_Get_Data(GYRO_YOUT_H) + Y_GYRO_OFFSET);
    printf("GYRO_Z: %d\t", MPU6050_Get_Data(GYRO_ZOUT_H) + Z_GYRO_OFFSET);
    
    printf("\r\n");
}


void MPU6050_Get_Angle(void)
{   
	/* ����x, y, z ����ǣ����ػ���ֵ*/
	dat.X_Angle = acos((MPU6050_Get_Data(ACCEL_XOUT_H) + X_ACCEL_OFFSET) / 8192.0);
	dat.Y_Angle = acos((MPU6050_Get_Data(ACCEL_YOUT_H) + Y_ACCEL_OFFSET) / 8192.0);
	dat.Z_Angle = acos((MPU6050_Get_Data(ACCEL_ZOUT_H) + Z_ACCEL_OFFSET) / 8192.0);

	/* ����ֵת��Ϊ�Ƕ�ֵ */
	dat.X_Angle 	= dat.X_Angle * 57.29577;
	dat.Y_Angle 	= dat.Y_Angle * 57.29577;
	dat.Z_Angle 	= dat.Z_Angle * 57.29577;

	dat1.X_Ang_speed += (MPU6050_Get_Data(GYRO_XOUT_H) + X_GYRO_OFFSET)/ 65.5/4;
	dat1.Y_Ang_speed += (MPU6050_Get_Data(GYRO_YOUT_H) + Y_GYRO_OFFSET)/ 65.5/4;
	dat1.Z_Ang_speed += (MPU6050_Get_Data(GYRO_ZOUT_H) + Z_GYRO_OFFSET)/ 65.5/4;
	
	printf("X_Angle = %3d�� ", (int)dat.X_Angle);
	printf("Y_Angle = %3d�� ", (int)dat.Y_Angle);
	printf("Z_Angle = %3d�� ", (int)dat.Z_Angle);

	printf("TEMP: %0.2f\t", MPU6050_Get_Data(TEMP_OUT_H) / 340.0 + 36.53);

	/* ��ӡ x, y, z ����ٶ� */
	printf("GYRO_X: %d\t", (int)dat1.X_Ang_speed);
	printf("GYRO_Y: %d\t", (int)dat1.Y_Ang_speed);
	printf("GYRO_Z: %d\t", (int)dat1.Z_Ang_speed);
	printf("\r\n");	
} 

