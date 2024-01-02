//******* ����������ռ����Դ˵�� **************************************
//  ��������ʹ��IO��ֱ�ƻ�PWM����
//  ʹ��IO������������ʱ����ռ��TIMER1��Դ
//  ʹ��PWM����������ʱ�����·PWM�������ڣ�����PWMֻ���������ã�����������;
//*********************************************************************

#include"..\H\SCDriver_Buzzer_TIM1.h"
#include "SC_Init.h"

#define  SCD_BZ_TIM1_IDLE_LOW		3				//����ʱ�����ܽ�Ϊ�͵�ƽ
#define  SCD_BZ_TIM1_IDLE_HIGH		4				//����ʱ�����ܽ�Ϊ�ߵ�ƽ
#define  SCD_BZ_TIM1_IDLE			SCD_BZ_TIM1_IDLE_HIGH	 //ѡ��SCD_BZ_IDLE_LOW��SCD_BZ_IDLE_HIGH

#define  IO_NULL 		   0xFF00//������
#define  SCD_IO_PORT(IO)    (uint8_t)(IO>>8)
#define  SCD_IO_PIN(IO)	    (uint8_t)(IO)

#define  SCD_BZ_TIM1_CLOCK_SOURCE	16000000			//ʹ��IO���������˴���дֵ��ϵͳʱ��
#define  SCD_BZ_TIM1_CLOCK_DIVIDER	TIM1_PRESSEL_FSYS_D12   //��Ƶϵ����ʹ��IO���������˴�ѡ��TIMER1��Ƶϵ����TIM1_PresSel_TypeDef��

FlagStatus SCD_BZ_TIM1_RunFlag = RESET;
unsigned int SCD_BZ_TIM1_HoldTime;
unsigned int SCD_BZ_TIM1_Count = 0;
unsigned int SCD_BZ_TIM1_FREG;
//{
//������  #SCD_BZ_TIM1_Init#
//��������#�ú������ڷ����������ĳ�ʼ�����趨������������Ƶ����ʱ��#
//�������#
//			unsigned int BuzzerFreg	     ������Ƶ��
//			unsigned int BuzzerHoldTime	 ����������ʱ�����ã�����������ʱ�� = BuzzerHoldTime * SCD_BZ_Scan����������������
//		  #
//�������#void#
//}
void SCD_BZ_TIM1_Init(unsigned int BuzzerFreg, unsigned int BuzzerHoldTime)
{
	SCD_BZ_TIM1_FREG = SCD_BZ_TIM1_CLOCK_SOURCE/12/2/BuzzerFreg;
	SCD_BZ_TIM1_HoldTime = BuzzerHoldTime;

	GPIO_Init(SCD_IO_PORT(SCD_BZ_TIM1_INIT), SCD_IO_PIN(SCD_BZ_TIM1_INIT), GPIO_MODE_OUT_PP);
	if(SCD_BZ_TIM1_IDLE == SCD_BZ_TIM1_IDLE_LOW)
	{
		GPIO_WriteLow(SCD_IO_PORT(SCD_BZ_TIM1_INIT), SCD_IO_PIN(SCD_BZ_TIM1_INIT));	
	}
	else
	{
		GPIO_WriteHigh(SCD_IO_PORT(SCD_BZ_TIM1_INIT), SCD_IO_PIN(SCD_BZ_TIM1_INIT));
	}

	TIM1_TimeBaseInit(SCD_BZ_TIM1_CLOCK_DIVIDER, TIM1_MODE_TIMER);
	TIM1_WorkMode1Config(65536 - SCD_BZ_TIM1_FREG);

	TIM1_Cmd(ENABLE);
	TIM1_ITConfig(ENABLE, HIGH);
	enableInterrupts();	
	
}
//{
//������  #SCD_BZ_TIM1_Scan#
//��������#����IO�������ɣ���ʹ��IO����������ʱ������TIMER1�ж��е��øú���#
//�������#void#
//�������#void#
//}
void SCD_BZ_TIM1_Scan(void)
{										
	TIM1_Mode1SetReloadCounter(65536 - SCD_BZ_TIM1_FREG);	
	//SCD_BZ_TIM1_Scan(); //���·�����������
	/*****************************************/
	if(SCD_BZ_TIM1_RunFlag == SET)					
	{													
		SCD_BZ_TIM1_Count++;
								
		if(SCD_BZ_TIM1_Count >= SCD_BZ_TIM1_HoldTime)
		{
			if(SCD_BZ_TIM1_IDLE == SCD_BZ_TIM1_IDLE_LOW)
			{
				GPIO_WriteLow(SCD_IO_PORT(SCD_BZ_TIM1_INIT), SCD_IO_PIN(SCD_BZ_TIM1_INIT));	
			}
			else
			{
				GPIO_WriteHigh(SCD_IO_PORT(SCD_BZ_TIM1_INIT), SCD_IO_PIN(SCD_BZ_TIM1_INIT));
			}
			SCD_BZ_TIM1_Count = 0;
			SCD_BZ_TIM1_RunFlag = RESET;
		}	
	}	
	/*****************************************/

	if(SCD_BZ_TIM1_RunFlag == SET)					
	{
		SCD_BZ_TIM1 = ~SCD_BZ_TIM1;												
					
	}
}
//{
//������  #SCD_BZ_TIM1_Run#
//��������#�ú����������������������ú����������һ��ʱ��#
//�������#void#
//�������#void#
//}
void SCD_BZ_TIM1_Run(void)
{
	SCD_BZ_TIM1_RunFlag = SET;	
}