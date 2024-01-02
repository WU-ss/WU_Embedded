#ifndef __LCD_DRIVER_H__ 
#define __LCD_DRIVER_H__

#include "SC_Init.h"	// MCU initialization header file, including all firmware library header files

extern u16 POINT_COLOR;
extern u16 BACK_COLOR;

#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//灰色0 3165 00110 001011 00101
#define GRAY1   0x8410      	//灰色1      00000 000000 00000
#define GRAY2   0x4208      	//灰色2  1111111111011111

//定义显示方向
//0 竖屏模式
//1 竖屏模式  旋转180
//2 横屏模式
//3 横屏模式  旋转180
#define TFT_DISPLAY_DIR 0

/*PIN Defination
* 		SCL		3-USCK0		SPI总线时钟信号
* 		SDA		4-USTX0		SPI总线写数据信号
* 		RES		44-P0.1		液晶屏复位信号，低电平复位
* 		DC		1-P0.2		液晶屏寄存器/数据选择信号，高电平：寄存器，低电平：数据
* 		CS		2-P0.3		液晶屏片选信号，低电平使能
* 		BL		43-P0.0		背光控制，高电平点亮，如无需控制则接3.3V常亮
* 		VCC					3.3V
* 		GND					接地
*/

#define TFT_DC(x)		((x == 0)? (GPIO_WriteLow(GPIO0, GPIO_PIN_2)) :(GPIO_WriteHigh(GPIO0, GPIO_PIN_2)))
#define TFT_REST(x)		((x == 0)? (GPIO_WriteLow(GPIO0, GPIO_PIN_1)) :(GPIO_WriteHigh(GPIO0, GPIO_PIN_1)))
#define TFT_CS(x)		((x == 0)? (GPIO_WriteLow(GPIO0, GPIO_PIN_3)) :(GPIO_WriteHigh(GPIO0, GPIO_PIN_3)))
#define TFT_BL(x)		((x == 0)? (GPIO_WriteLow(GPIO0, GPIO_PIN_0)) :(GPIO_WriteHigh(GPIO0, GPIO_PIN_0)))


void LCD_GPIO_Init(void);
void Lcd_WriteIndex(u8 Index);
void Lcd_WriteData(u8 Data);
void Lcd_WriteReg(u8 Index,u8 Data);
u16 Lcd_ReadReg(u8 LCD_Reg);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(u16 Color);
void Lcd_Clearsome(u16 x1,u16 y1,u16 x2,u16 y2,u16 Color);
void Lcd_SetXY(u16 x,u16 y);
void Gui_DrawPoint(u16 x,u16 y,u16 Data);
unsigned int Lcd_ReadPoint(u16 x,u16 y);
void Lcd_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end);
void LCD_WriteData_16Bit(u16 Data);

#endif
