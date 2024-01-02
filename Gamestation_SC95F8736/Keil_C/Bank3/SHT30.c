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

#define I2C_WR	0		/* 写控制bit */
#define I2C_RD	1		/* 读控制bit */

float_data humidity;//存储的湿度数据
float_data temperature;//存储的温度数据
u8 status[3];//状态寄存器
u8 status_crc;//CRC校验计算
u8 crc_check;//crc结果

u8 hANDt_buff[20]; //将温湿度转存字符数字

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
	uint8_t try_time = 100;//连接超时次数
    I2C_SDA_1();	        //CPU释放SDA总线
    i2c_Delay();
    I2C_SCL_1();	        //CPU驱动SCL = 1, 此时器件会返回ACK应答
    i2c_Delay(); 

    while(I2C_SDA_READ())//等待SHT30应答
    {
        try_time--;
        i2c_Delay(); 
        if(try_time==0)//超时，无响应
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


//CRC校验
static u8 CRC_Check(u8 *check_data, u8 num, u8 check_crc)
{
    uint8_t bitt;        // bitt mask
    uint8_t crc = 0xFF; // calculated checksum
    uint8_t byteCtr;    // byte counter
    
 // calculates 8-Bit checksum with given polynomial x8+x5+x4+1
    for(byteCtr = 0; byteCtr < num; byteCtr++)
    {
        crc ^= (*(check_data+byteCtr));
        //crc校验，最高位是1就^0x31
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

//根据所选获取数据的方式初始化
void SHT30_Init(void)
{
    SHT30_General_RESET();//软复位设备
    Delay_ms(10);
}

//复位函数
void SHT30_General_RESET(void)
{
    USCI3_TWI_Start();
    USCI3_TWI_SendData(0x00);
//	i2c_WaitAck();
    USCI3_TWI_SendData(0x06);
//	i2c_WaitAck();
}

//发送两字节指令，stop确定是否发送停止信号
void SHT30_SendBytes(u16 cmd,u8 stop)
{
    USCI3_TWI_Start();
    USCI3_TWI_SendAddr(SHT30_ADDR,I2C_WR);//写7位I2C设备地址加0作为写取位,1为读取位
//    i2c_WaitAck();
	USCI3_TWI_SendData(cmd>>8);
//	i2c_WaitAck();
    USCI3_TWI_SendData(cmd&0xFF);
//	i2c_WaitAck();
    if(stop)
        USCI3_TWI_MasterModeStop();
}

//加速响应指令
void SHT30_ART(void)
{
    SHT30_SendBytes(0x2B32,0);
}

//配置周期读取重复性和采样速率
void SHT30_Periodic_SetRepeat(void)
{
    SHT30_SendBytes(0x2737,0);//高重复度，mps为10
}

//配置周期读取总配置
void SHT30_Periodic_Config(void)
{
    //配置
    SHT30_Periodic_SetRepeat();
    SHT30_ART();
}

//单次读取数据
void SHT30_Single_Shot(u8 *buffer)
{
    u8 try_time=100;
    
    SHT30_SendBytes(0x2C06,1);
    
    Delay_ms(20);//很重要！不然读不出数据
    USCI3_TWI_Start();
	USCI3_TWI_SendAddr(SHT30_ADDR,I2C_RD);//写7位I2C设备地址加0作为写取位,1为读取位
	
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

//周期读取数据 如果使用就要在初始化时加上SHT30_Periodic_Config()函数
void SHT30_Periodic(u8 *buffer)
{
    u8 try_time=100;
    
    //获取数据
    SHT30_SendBytes(0xE000,0);
    Delay_ms(20);//很重要！不然读不出数据

    USCI3_TWI_Start();

    USCI3_TWI_SendAddr(SHT30_ADDR,I2C_RD);//写7位I2C设备地址加0作为写取位,1为读取位
    
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
    u8 buff[6];//获取raw数据
    u16 tem,hum;//拼接温湿度数据
    u8 crcT,crcH;//温度和湿度的CRC校验

    float Temperature=0;//转换后的温湿度
    float Humidity=0;

	SHT30_Single_Shot(buff);
//    SHT30_Periodic(buff);
    
    tem = ((buff[0]<<8) | buff[1]);//温度拼接
    hum = ((buff[3]<<8) | buff[4]);//湿度拼接

    //计算温度和湿度CRC校验码
    crcT = CRC_Check(buff,2,buff[2]);   //温度
    crcH = CRC_Check(buff+3,2,buff[5]); //湿度
    
//    if(crcT&&crcH)//判断CRC校验是否对
//    {
        //根据手册计算公式计算
        Temperature= (175.0*(float)tem/65535.0-45.0) ;  // T = -45 + 175 * tem / (2^16-1)
        Humidity= (100.0*(float)hum/65535.0);           // RH = hum*100 / (2^16-1)
//        if((Temperature>=-20)&&(Temperature<=125)&&(Humidity>=0)&&(Humidity<=100))//过滤超出测量范围的错误数据
        {
            temperature.fdata=Temperature;
            humidity.fdata=Humidity;
        }
//    }
}

void SHT30_Show(void)
{
	sprintf(hANDt_buff,"%6.2f*C %6.2f",temperature.fdata,humidity.fdata); //111.01*C 100.01%（保留2位小数）
	Gui_DrawFont_GBK24(-1,50,RED,BACK_COLOR,hANDt_buff);
}

