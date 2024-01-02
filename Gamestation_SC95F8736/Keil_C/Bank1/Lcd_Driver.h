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
#define GRAY0   0xEF7D   	//��ɫ0 3165 00110 001011 00101
#define GRAY1   0x8410      	//��ɫ1      00000 000000 00000
#define GRAY2   0x4208      	//��ɫ2  1111111111011111

//������ʾ����
//0 ����ģʽ
//1 ����ģʽ  ��ת180
//2 ����ģʽ
//3 ����ģʽ  ��ת180
#define TFT_DISPLAY_DIR 0

/*PIN Defination
* 		SCL		3-USCK0		SPI����ʱ���ź�
* 		SDA		4-USTX0		SPI����д�����ź�
* 		RES		44-P0.1		Һ������λ�źţ��͵�ƽ��λ
* 		DC		1-P0.2		Һ�����Ĵ���/����ѡ���źţ��ߵ�ƽ���Ĵ������͵�ƽ������
* 		CS		2-P0.3		Һ����Ƭѡ�źţ��͵�ƽʹ��
* 		BL		43-P0.0		������ƣ��ߵ�ƽ������������������3.3V����
* 		VCC					3.3V
* 		GND					�ӵ�
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
