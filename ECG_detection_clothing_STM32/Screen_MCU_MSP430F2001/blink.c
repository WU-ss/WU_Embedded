#include <msp430.h>
//#include "DM130036.h"
//#include "I2C.h"
#include "TIM.h"

 #define V_PUMP                0x0b    // 0xab=17V   0x8b=32V   bit7=CPEN=1(开高压)  bit5=VPP15=1(15V) =0(30V)  bit3=Load=1(Load)
//  #define V_PUMP_Off            0x0b    // 0x2b=17V   0x0b=32V   bit7=CPEN=0(关高压)  bit5=VPP15=1(15V) =0(30V)  bit3=Load=1(Load)
  #define V_PUMP_PRE            0x03    // 0xa3=17V   0x83=32V   bit7=CPEN=1(开高压)  bit5=VPP15=1(15V) =0(30V)  bit3=Load=0(Latch)

#define I2C_SCL               0x02  //P1.1
#define I2C_SDA               0x01  //P1.0
#define DM130036_ID           0xf3

unsigned char ack;

const unsigned char Picture[5][5]={
0x00,0x00,0x00,0x00,0xc0, //全白
0x77,0x01,0x00,0x00,0x00, //01110111 数字0+心
0x88,0xfe,0xff,0xff,0xff, //变白
0x24,0x01,0x00,0x00,0x00, //00100100 数字1+心
0xdb,0xfe,0xff,0xff,0xff, //全白
//0x5d,0x01,0x00,0x00,0x00, //01011101 数字2+心
//0xa2,0xfe,0xff,0xff,0xff, //全白
//0x6d,0x01,0x00,0x00,0x00, //01101101 数字3+心
//0x92,0xfe,0xff,0xff,0xff, //全白
//0x2e,0x01,0x00,0x00,0x00, //00101110 数字4+心
//0xd1,0xfe,0xff,0xff,0xff, //全白
//0x6b,0x01,0x00,0x00,0x00, //01101011 数字5+心
//0x94,0xfe,0xff,0xff,0xff, //全白
//0x7b,0x01,0x00,0x00,0x00, //01111011 数字6+心
//0x84,0xfe,0xff,0xff,0xff, //全白
//0x25,0x01,0x00,0x00,0x00, //00100101 数字7+心
//0xda,0xfe,0xff,0xff,0xff, //全白
//0x7f,0x01,0x00,0x00,0x00, //01111111 数字8+心
//0x80,0xfe,0xff,0xff,0xff, //全白
};

unsigned char Show_enable;      // 图像显示使能
unsigned char TIM_Count;        // 显示使能后，程序进入定时器计数
unsigned char TIM_Count_Par;    // 程序进入定时器计数的奇偶性
unsigned char Picture_Count;    // 每次发送的画面计数
unsigned char send_buf[5];      // 要显示的图形数组

//inline void Fun_Drive_Picture()
//{
//  unsigned char i;
//  for(i=0;i<5;i++)
//  {
//    send_buf[i]=Picture[Picture_Count][i];
//  }
//  DM130036_WriteByte(5,V_PUMP_PRE);
//  DM130036_Send_One_String(send_buf);
//  DM130036_WriteByte(5,V_PUMP);
//}

void Start_I2c()
{
    P1DIR |= I2C_SDA;
    P1OUT |= I2C_SDA;               //发送起始条件的数据信号*/

    P1OUT |= I2C_SCL;
    _NOP();             //起始条件建立时间大于4.7us,延时

    P1OUT &=~ I2C_SDA;              //发送起始信号
    _NOP();
    P1OUT &=~ I2C_SCL;              //钳住I2C总线，准备发送或接收数据
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void Stop_I2c()
{
    P1DIR |= I2C_SDA;
    P1OUT &=~ I2C_SDA;              //发送结束条件的数据信号

    P1OUT |= I2C_SCL;               //结束条件建立时间大于4μs
    _NOP();

    P1OUT |= I2C_SDA;               //发送I2C总线结束信号
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void I2C_Send_Byte(unsigned char c)
{
    unsigned char BitCnt;


    P1DIR |= I2C_SDA;
    for(BitCnt=0;BitCnt<8;BitCnt++)   //要传送的数据长度为8位
    {
        if((c<<BitCnt)&0x80)        //判断发送位
            P1OUT |= I2C_SDA;
        else
            P1OUT &=~ I2C_SDA;

        P1OUT |= I2C_SCL;             //置时钟线为高，通知被控器开始接收数据位
        _NOP();
        P1OUT &=~ I2C_SCL;
    }

    P1OUT |= I2C_SDA;                 //8位发送完后释放数据线，准备接收应答位
    P1OUT |= I2C_SCL;

    P1DIR &=~ I2C_SDA;
    if((P1IN & I2C_SDA)==I2C_SDA)     //断是否接收到应答信号
        ack = 0;
    else
        ack = 1;

    P1OUT &=~ I2C_SCL;
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//void Ack_I2c(unsigned char a)
//{
//    P1DIR |= I2C_SDA;
//    if(a==0)                          //在此发出应答或非应答信号
//        P1OUT &=~ I2C_SDA;
//    else
//        P1OUT |= I2C_SDA;
//
//    _NOP();
//
//    P1OUT |= I2C_SCL;
//    _NOP();
//    P1OUT &=~ I2C_SCL;                //清时钟线，钳住I2C总线以便继续接收
//}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
unsigned char I2c_Send_One_Byte(unsigned char sla, unsigned char suba, unsigned char data)
{
    Start_I2c();
    I2C_Send_Byte(sla);
    if(ack == 0)
        return(0);

    I2C_Send_Byte(suba);
    if(ack == 0)
        return(0);

    I2C_Send_Byte(data);
    if(ack == 0)
        return(0);

    Stop_I2c();
    return(1);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
unsigned char I2c_Send_One_String(unsigned char *astring)
{
    unsigned char i;
    for(i=0;i<5;i++)
    {
        I2c_Send_One_Byte(DM130036_ID, i, *(astring+i));
    }
    return(1);
}

void Fun_Drive_Picture()
{
  unsigned char i;

  for(i=0;i<5;i++)
  {
    send_buf[i]=Picture[Picture_Count][i];
  }
  I2c_Send_One_Byte(DM130036_ID,5,V_PUMP_PRE);
  I2c_Send_One_String(send_buf);
  I2c_Send_One_Byte(DM130036_ID,5,V_PUMP);
}
void main(void)
{
    //关闭看门狗
	WDTCTL = WDTPW + WDTHOLD;

	//配置基础时钟
	BCSCTL1 = CALBC1_1MHZ+DIVA_2; //ACLK，4分频 即ACLK=32768/4=8192Hz
	DCOCTL = CALDCO_1MHZ;
	BCSCTL2 = 0;
	BCSCTL3 = 0;

	//初始化外部时钟信号
	P2SEL |=0xc0;  // P2.6/P2.7(32K晶振)功能开启
	P2DIR = 0x80;  // P2DIR.7=1(P2.7=XOUT+) P2DIR.6=0(P2.6=XIN+)

	//初始化引脚
//	P1DIR &= (~BIT5); //P1^5  GPIO设置为 IN模式
	P1DIR |= (BIT5|BIT6);
//	I2C_Init();    //初始化SDA、SCL引脚,SDA->P10  SCL->P11

	//初始化定时器TimerA0
	TimerA_Init();

	// 打开全局中断控制
	_EINT();

	Show_enable=1;
	P1OUT |= (BIT5 |BIT6);
	while(1)
	{
	    P1OUT |= (BIT5 |BIT6);
	    //判断P1^5的输入信号
//	    if(P1IN & BIT5)
//	    {Show_enable=1;}
//	    else
//	    {Show_enable=0;}
	}
}

//TimerA0中断函数
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
    if(Show_enable==1)
    {
        if(TIM_Count>0 && TIM_Count<=60)
        {
            if(TIM_Count_Par)
            {
                Picture_Count=1;
                P1OUT &=(~BIT5);
            }
            else
            {
                Picture_Count=2;
                P1OUT &=(~BIT6);
            }
        }
        else if(TIM_Count>0 &&TIM_Count<=120)
        {
            if(TIM_Count_Par)
            {
                Picture_Count=3;
//                P1OUT &=(~BIT5);
            }
            else
            {
                Picture_Count=4;
//                P1OUT &=(~BIT6);
            }
        }
//        else if(TIM_Count<=181)
//        {
//            if(TIM_Count_Par) Picture_Count=4;
//            else Picture_Count=5;
//        }
//        else if(TIM_Count<=241)
//        {
//            if(TIM_Count_Par) Picture_Count=6;
//            else Picture_Count=7;
//        }
//        else if(TIM_Count<=301)
//        {
//            if(TIM_Count_Par) Picture_Count=8;
//            else Picture_Count=9;
//        }
//        else if(TIM_Count<=361)
//        {
//            if(TIM_Count_Par) Picture_Count=10;
//            else Picture_Count=11;
//        }
        Fun_Drive_Picture();
        TIM_Count++;
        TIM_Count_Par=TIM_Count%2;
        TACCR0+=1024;
    }
//    else
//    {
//        TIM_Count=0;
//        Picture_Count=0;
//    }
}
