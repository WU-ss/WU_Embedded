#include "SHT30.h"
#include "Delay.h"
#include "Intrins.h"
#include "..\Bank1\GUI.h"
#include "..\Bank1\Lcd_Driver.h"
#include "stdio.h"

#define I2C_SDA_1() 	GPIO_WriteHigh(GPIO2,6)
#define I2C_SCL_1()		GPIO_WriteHigh(GPIO2,5)
#define I2C_SDA_0()		GPIO_WriteLow(GPIO2,6)
#define I2C_SCL_0()		GPIO_WriteLow(GPIO2,5)
#define I2C_SDA_READ()	GPIO_ReadPin(GPIO2,6)	

#define I2C_WR	0		/* д����bit */
#define I2C_RD	1		/* ������bit */

float_data humidity;//�洢��ʪ������
float_data temperature;//�洢���¶�����
u8 status[3];//״̬�Ĵ���
u8 status_crc;//CRCУ�����
u8 crc_check;//crc���

u8 hANDt_buff[20]; //����ʪ��ת���ַ�����

void Delay_us(uint8_t uss)
{
	while(uss--)
	{
		_nop_();_nop_();_nop_();
	}
}

void i2c_Delay()
{
	 _nop_();_nop_();_nop_();_nop_();    _nop_();_nop_();_nop_();_nop_();
}

uint8_t i2c_WaitAck(void)
{
	uint8_t try_time = 100;//���ӳ�ʱ����
    I2C_SDA_1();	        //CPU�ͷ�SDA����
    i2c_Delay();
    I2C_SCL_1();	        //CPU����SCL = 1, ��ʱ�����᷵��ACKӦ��
    i2c_Delay(); 

    while(I2C_SDA_READ())//�ȴ�SHT30Ӧ��
    {
        try_time--;
        i2c_Delay(); 
        if(try_time==0)//��ʱ������Ӧ
        {
            I2C_SCL_0();
            i2c_Delay();
            return 1;
        }
    }
    I2C_SCL_0();
    i2c_Delay();    
    return 0;
}


//CRCУ��
static u8 CRC_Check(u8 *check_data, u8 num, u8 check_crc)
{
    uint8_t bitt;        // bitt mask
    uint8_t crc = 0xFF; // calculated checksum
    uint8_t byteCtr;    // byte counter
    
 // calculates 8-Bit checksum with given polynomial x8+x5+x4+1
    for(byteCtr = 0; byteCtr < num; byteCtr++)
    {
        crc ^= (*(check_data+byteCtr));
        //crcУ�飬���λ��1��^0x31
        for(bitt = 8; bitt > 0; --bitt)
        {
            if(crc & 0x80)
                crc = (crc << 1) ^ 0x31;
            else
                crc = (crc << 1);
        }
    }
    if(crc==check_crc)
        return 1;
    else 
        return 0;
}

//������ѡ��ȡ���ݵķ�ʽ��ʼ��
void SHT30_Init(void)
{
    SHT30_General_RESET();//��λ�豸
    Delay_ms(10);
}

//��λ����
void SHT30_General_RESET(void)
{
    USCI3_TWI_Start();
    USCI3_TWI_SendData(0x00);
//	i2c_WaitAck();
    USCI3_TWI_SendData(0x06);
//	i2c_WaitAck();
}

//�������ֽ�ָ�stopȷ���Ƿ���ֹͣ�ź�
void SHT30_SendBytes(u16 cmd,u8 stop)
{
    USCI3_TWI_Start();
    USCI3_TWI_SendAddr(SHT30_ADDR,I2C_WR);//д7λI2C�豸��ַ��0��Ϊдȡλ,1Ϊ��ȡλ
//    i2c_WaitAck();
	USCI3_TWI_SendData(cmd>>8);
//	i2c_WaitAck();
    USCI3_TWI_SendData(cmd&0xFF);
//	i2c_WaitAck();
    if(stop)
        USCI3_TWI_MasterModeStop();
}

//������Ӧָ��
void SHT30_ART(void)
{
    SHT30_SendBytes(0x2B32,0);
}

//�������ڶ�ȡ�ظ��ԺͲ�������
void SHT30_Periodic_SetRepeat(void)
{
    SHT30_SendBytes(0x2737,0);//���ظ��ȣ�mpsΪ10
}

//�������ڶ�ȡ������
void SHT30_Periodic_Config(void)
{
    //����
    SHT30_Periodic_SetRepeat();
    SHT30_ART();
}

//���ζ�ȡ����
void SHT30_Single_Shot(u8 *buffer)
{
    u8 try_time=100;
    
    SHT30_SendBytes(0x2C06,1);
    
    Delay_ms(20);//����Ҫ����Ȼ����������
    USCI3_TWI_Start();
	USCI3_TWI_SendAddr(SHT30_ADDR,I2C_RD);//д7λI2C�豸��ַ��0��Ϊдȡλ,1Ϊ��ȡλ
	
	while(i2c_WaitAck())
	{
		try_time--;
		Delay_us(50);
		if(try_time==0)
			return;
	}
	
    buffer[0]=USCI3_TWI_ReceiveData();
    buffer[1]=USCI3_TWI_ReceiveData();
    buffer[2]=USCI3_TWI_ReceiveData();
    buffer[3]=USCI3_TWI_ReceiveData();
    buffer[4]=USCI3_TWI_ReceiveData();
    buffer[5]=USCI3_TWI_ReceiveData();
    USCI3_TWI_MasterModeStop();
}

//���ڶ�ȡ���� ���ʹ�þ�Ҫ�ڳ�ʼ��ʱ����SHT30_Periodic_Config()����
void SHT30_Periodic(u8 *buffer)
{
    u8 try_time=100;
    
    //��ȡ����
    SHT30_SendBytes(0xE000,0);
    Delay_ms(20);//����Ҫ����Ȼ����������

    USCI3_TWI_Start();

    USCI3_TWI_SendAddr(SHT30_ADDR,I2C_RD);//д7λI2C�豸��ַ��0��Ϊдȡλ,1Ϊ��ȡλ
    
	while(i2c_WaitAck())
    {
        try_time--;
        Delay_us(50);
        if(try_time==0)
            return;
    }
	
    buffer[0]=USCI3_TWI_ReceiveData();
    buffer[1]=USCI3_TWI_ReceiveData();
    buffer[2]=USCI3_TWI_ReceiveData();
    buffer[3]=USCI3_TWI_ReceiveData();
    buffer[4]=USCI3_TWI_ReceiveData();
    buffer[5]=USCI3_TWI_ReceiveData();
    USCI3_TWI_MasterModeStop();
}

void SHT30_Read(void)
{    
    u8 buff[6];//��ȡraw����
    u16 tem,hum;//ƴ����ʪ������
    u8 crcT,crcH;//�¶Ⱥ�ʪ�ȵ�CRCУ��

    float Temperature=0;//ת�������ʪ��
    float Humidity=0;

	SHT30_Single_Shot(buff);
//    SHT30_Periodic(buff);
    
    tem = ((buff[0]<<8) | buff[1]);//�¶�ƴ��
    hum = ((buff[3]<<8) | buff[4]);//ʪ��ƴ��

    //�����¶Ⱥ�ʪ��CRCУ����
    crcT = CRC_Check(buff,2,buff[2]);   //�¶�
    crcH = CRC_Check(buff+3,2,buff[5]); //ʪ��
    
//    if(crcT&&crcH)//�ж�CRCУ���Ƿ��
//    {
        //�����ֲ���㹫ʽ����
        Temperature= (175.0*(float)tem/65535.0-45.0) ;  // T = -45 + 175 * tem / (2^16-1)
        Humidity= (100.0*(float)hum/65535.0);           // RH = hum*100 / (2^16-1)
//        if((Temperature>=-20)&&(Temperature<=125)&&(Humidity>=0)&&(Humidity<=100))//���˳���������Χ�Ĵ�������
        {
            temperature.fdata=Temperature;
            humidity.fdata=Humidity;
        }
//    }
}

void SHT30_Show(void)
{
	sprintf(hANDt_buff,"%6.2f*C %6.2f",temperature.fdata,humidity.fdata); //111.01*C 100.01%������2λС����
	Gui_DrawFont_GBK24(-1,50,RED,BACK_COLOR,hANDt_buff);
}

