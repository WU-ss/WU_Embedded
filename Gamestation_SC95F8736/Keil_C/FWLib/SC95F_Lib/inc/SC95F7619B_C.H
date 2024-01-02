/*--------------------------------------------------------------------------
SC95F7619B_C.H

C Header file for SC95F7619B microcontroller.
Copyright (c) 2022 Shenzhen SinOne Microelectronics Co., Ltd.
All rights reserved.
版本号:  V1.0   
日期:  2022.06.06
--------------------------------------------------------------------------*/
#ifndef _SC95F7619B_H_
#define _SC95F7619B_H_

///* ------------------- 字节寄存器-------------------- */
/*CPU*/
sfr   SP    = 0X81;  //堆栈指针
sfr   DPL   = 0X82;  //DPTR数据指针低位
sfr   DPH   = 0X83;  //DPTR数据指针高位
sfr   DPL1  = 0X84;  //DPTR1数据指针低位
sfr   DPH1  = 0X85;  //DPTR1数据指针高位
sfr   DPS   = 0X86;  //DPTR选择寄存器
sfr   PSW   = 0XD0;  //程序状态字寄存器	
sfr   ACC   = 0XE0;  //累加器Ａ	
sfr   EXA0  = 0XE9;  //扩展累加器0
sfr   EXA1  = 0XEA;  //扩展累加器1
sfr   EXA2  = 0XEB;  //扩展累加器2
sfr   EXA3  = 0XEC;  //扩展累加器3
sfr   EXBL  = 0XED;  //扩展B寄存器0
sfr   EXBH  = 0XEE;  //扩展B寄存器1
sfr   B     = 0XF0;  //B寄存器	

/*SRAM*/
sfr   EXADH = 0XF7;  //外部SRAM操作地址高位

/*system*/
sfr   PCON = 0X87;  //电源管理控制寄存器

/*Interrupt*/
sfr   IE  = 0XA8;  //中断控制寄存器
sfr   IE1 = 0XA9;  //中断控制寄存器1
sfr   IE2 = 0XAA;  //中断使能寄存器2
sfr   IP  = 0XB8;  //中断优先权控制寄存器
sfr   IP1 = 0XB9;  //中断优先级控制寄存器1
sfr   IP2 = 0XBA;  //中断优先级控制寄存器2

/*PORT*/
sfr   P0      = 0X80;  //P0口数据寄存器
sfr   P1      = 0X90;  //P1口数据寄存器
sfr	  P1CON	  = 0X91;  //P1口输入/输出控制寄存器
sfr   P1PH	  = 0X92;  //P1口上拉电阻控制寄存器	
sfr   IOHCON0 = 0X96;  //IOH设置寄存器0
sfr   IOHCON1 = 0X97;  //IOH设置寄存器1
sfr	  P0CON	  = 0X9A;  //P0口输入/输出控制寄存器	
sfr	  P0PH	  = 0X9B;  //P0口上拉电阻控制寄存器
sfr   P2      = 0XA0;  //P2口数据寄存器
sfr	  P2CON	  = 0XA1;  //P2口输入/输出控制寄存器	
sfr   P2PH	  = 0XA2;  //P2口上拉电阻控制寄存器	
sfr   P4      = 0XC0;  //P4口数据寄存器
sfr   P4CON   = 0XC1;  //P4口输入/输出寄存器
sfr   P4PH    = 0XC2;  //P4口上拉电阻控制寄存器
sfr   P5      = 0XD8;  //P5口数据寄存器
sfr   P5CON   = 0XD9;  //P5口输入/输出控制寄存器
sfr   P5PH    = 0XDA;  //P5口上拉电阻控制寄存器

/*模拟比较器*/
sfr   CMPCFG  = 0XB6;  //模拟比较器设置寄存器
sfr   CMPCON  = 0XB7;  //模拟比较器控制寄存器

/*TIMER*/	
sfr   TCON   = 0X88;  //定时器控制寄存器
sfr   TMOD   = 0X89;  //定时器工作模式寄存器
sfr   TL0    = 0X8A;  //定时器0低8位
sfr   TL1    = 0X8B;  //定时器1低8位
sfr   TH0    = 0X8C;  //定时器0高8位
sfr   TH1    = 0X8D;  //定时器1高8位
sfr   TMCON  = 0X8E;  //定时器频率控制寄存器
sfr   TXCON  = 0XC8;  //定时器2/3/4控制寄存器
sfr   TXMOD  = 0XC9;  //定时器2/3/4工作模式寄存器
sfr   RCAPXL = 0XCA;  //定时器2/3/4重载/捕捉低8位
sfr   RCAPXH = 0XCB;  //定时器2/3/4重载/捕捉高8位
sfr   TLX    = 0XCC;  //定时器2/3/4低8位
sfr   THX    = 0XCD;  //定时器2/3/4高8位
sfr   TXINX  = 0XCE;  //定时器控制寄存器指针

/*ADC*/
sfr	  ADCCFG0 = 0XAB;  //ADC设置寄存器0
sfr	  ADCCFG1 = 0XAC;  //ADC设置寄存器1
sfr   ADCCON  = 0XAD;  //ADC控制寄存器
sfr   ADCVL   = 0XAE;  //ADC 结果寄存器
sfr   ADCVH   = 0XAF;  //ADC 结果寄存器
sfr   ADCCFG2 = 0XB5;  //ADC设置寄存器2

/*PWM*/
sfr   PWMCFG  = 0XD1;  //PWM设置寄存器
sfr   PWMCON0 = 0XD2;  //PWM0控制寄存器0
sfr   PWMCON1 = 0XD3;  //PWM1控制寄存器1
sfr   PWMPDL  = 0XD4;  //PWM0周期寄存器低8位
sfr   PWMPDH  = 0XD5;  //PWM0周期寄存器高8位
sfr   PWMDFR  = 0XD6;  //PWM0死区设置寄存器

/*WatchDog*/
sfr   WDTCON = 0XCF;  //WDT控制寄存器

/*BTM*/
sfr	  BTMCON = 0XFB;  //低频定时器控制寄存器

/*INT*/
sfr   INT0F = 0XB4;  //INT0 下降沿中断控制寄存器
sfr   INT0R = 0XBB;  //INT0 上降沿中断控制寄存器
sfr   INT1F = 0XBC;  //INT1 下降沿中断控制寄存器
sfr   INT1R = 0XBD;  //INT1 上降沿中断控制寄存器
sfr   INT2F = 0XBE;  //INT2 下降沿中断控制寄存器
sfr   INT2R = 0XBF;  //INT2 上降沿中断控制寄存器

/*IAP */
sfr   IAPKEY = 0XF1;  //IAP保护寄存器
sfr   IAPADL = 0XF2;  //IAP写入地址低位寄存器
sfr   IAPADH = 0XF3;  //IAP写入地址高位寄存器
sfr   IAPADE = 0XF4;  //IAP扩展地址寄存器
sfr   IAPDAT = 0XF5;  //IAP数据寄存器
sfr   IAPCTL = 0XF6;  //IAP控制寄存器

/*uart0*/
sfr   OTCON = 0X8F;  //输出控制寄存器
sfr   SCON  = 0X98;  //串口控制寄存器
sfr   SBUF  = 0X99;  //串口数据缓存寄存器

/*三合一*/
sfr   US0CON0 = 0X95;  //USCI0控制寄存器0
sfr   US0CON1 = 0X9D;  //USCI0控制寄存器1
sfr   US0CON2 = 0X9E;  //USCI0控制寄存器2
sfr   US0CON3 = 0X9F;  //USCI0控制寄存器3
sfr   US1CON0 = 0XA4;  //USCI1控制寄存器0
sfr   US1CON1 = 0XA5;  //USCI1控制寄存器1
sfr   US1CON2 = 0XA6;  //USCI1控制寄存器2
sfr   US1CON3 = 0XA7;  //USCI1控制寄存器3
sfr   USXCON0 = 0XC4;  //USCI2/3/5控制寄存器0
sfr   USXCON1 = 0XC5;  //USCI2/3/5控制寄存器1
sfr   USXCON2 = 0XC6;  //USCI2/3/5控制寄存器2
sfr   USXCON3 = 0XC7;  //USCI2/3/5控制寄存器3
sfr   USXINX  = 0XDC;  //USCI2/3/5控制寄存器指针  


/*OPTION*/
sfr   OPINX = 0XFE;  //Option指针 
sfr   OPREG = 0XFF;  //Option寄存器

/*CRC*/
sfr   OPERCON = 0XEF;  //运算控制寄存器
sfr   CRCINX  = 0XFC;  //CRC指针
sfr   CRCREG  = 0XFD;  //CRC寄存器


///* ------------------- 位寄存器-------------------- */
/*PSW*/
sbit  CY  = PSW^7;  //标志位          0:加法运算最高位无进位，或者减法运算最高位无借位时	1:加法运算最高位有进位，或者减法运算最高位有借位时
sbit  AC  = PSW^6;  //进位辅助标志位  0:无借位、进位	1:加法运算时在bit3位有进位，或减法运算在bit3位有借位时
sbit  F0  = PSW^5;  //用户标志位
sbit  RS1 = PSW^4;  //工作寄存器组选择位
sbit  RS0 = PSW^3;  //工作寄存器组选择位
sbit  OV  = PSW^2;  //溢出标志位
sbit  F1  = PSW^1;  //F1标志
sbit  P   = PSW^0;  //奇偶标志位      0:ACC中1的个数为偶数（包括0个）		1:ACC中1的个数为奇数

/*TXCON*/
sbit  TFX   = TXCON^7;  //定时器2/3/4溢出标志位
sbit  EXFX  = TXCON^6;  //TnEX(n=2/3)引脚外部事件输入(下降沿)被检测到的标志位
sbit  RCLKX = TXCON^5;  //UART0接收时钟控制位        0: 定时器1产生接收波特率	1: 定时器2产生接收波特率
sbit  TCLKX = TXCON^4;  //UART0发送时钟控制位        0: 定时器1产生发送波特率	1: 定时器2产生发送波特率
sbit  EXENX = TXCON^3;  //TnEX(n=2/3)引脚上的外部事件输入(下降沿)用作重载/捕获触发器允许/禁止控制
sbit  TRX   = TXCON^2;  //定时器2/3/4开始/停止控制位 0: 停止定时器2/3/4         1: 开始定时器2/3/4
sbit  TX    = TXCON^1;  //定时器2/3/4定时器/计数器方式选定位
sbit  CP    = TXCON^0;  //捕获/重载方式选定位

/*IP*/
sbit  IPADC  = IP^6;  //ADC中断优先权选择         0:设定 ADC的中断优先权是 “低”      1:设定 ADC的中断优先权是 “高”
sbit  IPT2   = IP^5;  //Timer2中断优先权选择      0:设定 Timer 2的中断优先权是 “低”	 1:设定 Timer 2的中断优先权是 “高”
sbit  IPUART = IP^4;  //UART中断优先权选择        0:设定 UART的中断优先权是 “低”     1:设定 UART的中断优先权是 “高”
sbit  IPT1   = IP^3;  //Timer1中断优先权选择      0:设定 Timer 1的中断优先权是 “低”	 1:设定 Timer 1的中断优先权是 “高”
sbit  IPINT1 = IP^2;  //INT1计数器中断优先权选择  0:设定 INT1的中断优先权是 “低”     1:设定 INT1的中断优先权是 “高”
sbit  IPT0   = IP^1;  //Timer0中断优先权选择      0:设定 Timer 0的中断优先权是 “低”	 1:设定 Timer 0的中断优先权是 “高”
sbit  IPINT0 = IP^0;  //INT0计数器中断优先权选择  0:设定 INT0的中断优先权为 “低”     1: INT0中断优先权为高

/*IE*/
sbit  EA    = IE^7;  //中断使能的总控制       0:关闭所有的中断      1:打开所有的中断
sbit  EADC  = IE^6;  //ADC中断使能控制        0:关闭ADC中断         1:打开ADC中断
sbit  ET2   = IE^5;  //Timer2中断使能控制     0:关闭TIMER2中断      1:打开TIMER2中断
sbit  EUART = IE^4;  //UART中断使能控制       0:关闭SIF中断         1:打开SIF中断
sbit  ET1   = IE^3;  //Timer1中断使能控制     0:关闭TIMER1中断      1:打开TIMER1中断
sbit  EINT1 = IE^2;  //外部中断1中断使能控制  0:关闭外部中断1中断   1:打开外部中断1中断	
sbit  ET0   = IE^1;  //Timer0中断使能控制     0:关闭TIMER0中断      1:打开TIMER0中断
sbit  EINT0 = IE^0;  //外部中断0中断使能控制  0:关闭外部中断0中断   1:打开外部中断0中断

/*TCON*/
sbit  TF1 = TCON^7;  //T1溢出中断请求标志位	T1产生溢出，发生中断时，硬件将TF1置为“1”，申请中断，CPU响应时，硬件清“0”。
sbit  TR1 = TCON^6;  //定时器T1的运行控制位	0:Timer1禁止计数		1:Timer1开始计数
sbit  TF0 = TCON^5;  //T0溢出中断请求标志位	T0产生溢出，发生中断时，硬件将TF0置为“1”，申请中断，CPU响应时，硬件清“0”。
sbit  TR0 = TCON^4;  //定时器T0的运行控制位	0:Timer0禁止计数		1:Timer0开始计数

/*SCON*/
sbit  SM0 = SCON^7;  //串行通信模式控制位:与SM1配合使用 00: 模式0，8位半双工同步通信模式 01: 模式1，10位全双工异步通信 11: 模式3，11位全双工异步通信
sbit  SM1 = SCON^6;  //串行通信模式控制位
sbit  SM2 = SCON^5;  //串行通信模式控制位2，此控制位只对模式3有效   0：每收到一个完整数据帧就置位RI产生中断请求   1：收到一个完整的数据帧时，只有当RB8=1时才会置位RI产生中断请求
sbit  REN = SCON^4;  //接收允许控制位  0:不允许接受数据   1：允许接受数据
sbit  TB8 = SCON^3;  //只对模式3有效，为发送数据的第9位
sbit  RB8 = SCON^2;  //只对模式3有效，为接收数据的第9位
sbit  TI  = SCON^1;  //发送中断标志位
sbit  RI  = SCON^0;  //接收中断标志位


/******************* P0 *******************/
sbit  P07 = P0^7;
sbit  P06 = P0^6;
sbit  P05 = P0^5;
sbit  P04 = P0^4;
sbit  P03 = P0^3;
sbit  P02 = P0^2;
sbit  P01 = P0^1;
sbit  P00 = P0^0;

/******************* P1 *******************/
sbit  P17 = P1^7;
sbit  P16 = P1^6;
sbit  P15 = P1^5;
sbit  P14 = P1^4;
sbit  P13 = P1^3;
sbit  P12 = P1^2;
sbit  P11 = P1^1;
sbit  P10 = P1^0;

/******************* P2 *******************/
sbit  P26 = P2^6;
sbit  P25 = P2^5;
sbit  P24 = P2^4;
sbit  P23 = P2^3;
sbit  P22 = P2^2;
sbit  P21 = P2^1;
sbit  P20 = P2^0;

/******************* P4 *******************/
sbit  P44 = P4^4;
sbit  P43 = P4^3;
sbit  P42 = P4^2;
sbit  P41 = P4^1;
sbit  P40 = P4^0;

/******************* P5 *******************/
sbit  P51 = P5^1;
sbit  P50 = P5^0;
/****************************************************************************
*注意：封装未引出的管脚，需设置为强推挽输出模式
*****************************************************************************/    
#define  SC95F7619B_NIO_Init()   {P2CON|=0X80,P3CON|=0xF0,P4CON|=0xE0,P5CON|=0xFC;}  //SC95F7619B的未引出来的IO口配置
#endif