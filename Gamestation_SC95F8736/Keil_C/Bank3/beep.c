#include "beep.h"
#include "music.h"

#define TEA_VOL 30

void passive_buzzer_set(uint16_t note_f)
{
		/*�����Զ���װռ�ձ�,�����µ�Ƶ��*/
		uint16_t Autoreload=(8000000/(float)C_FREQ[note_f]+1);	
		/*��������*/	
		uint16_t volume=(((float)Autoreload)/100.0)*TEA_VOL;
	
		/*������Ƶ��*/
		PWMPDH = (uint8_t)(Autoreload >> 8);               //���ڸ�8λ
		PWMPDL = (uint8_t)(Autoreload & 0X00FF);           //���ڵ�8λ

	    /*�������� ռ�ձ�*/
		PWM_IndependentModeConfig(PWM03,volume);
	
//		/*�������ֵ*/
//		__HAL_TIM_SET_COUNTER(&htim4,0);
}
 
u32 paly_delay_ms=0;
void my_buzzer_play()
{
	if(paly_delay_ms==0)
	{
		paly_delay_ms=music_t.t_each*music_t.t[music_t.now_len];
		passive_buzzer_set(music_t.f[music_t.now_len]);
				
		if(music_t.now_len>=(music_t.len-1))
		{
			music_t.now_len=0;
		}else
		{
			music_t.now_len++;
		}
	}else
	{
		paly_delay_ms--;
	}
}
