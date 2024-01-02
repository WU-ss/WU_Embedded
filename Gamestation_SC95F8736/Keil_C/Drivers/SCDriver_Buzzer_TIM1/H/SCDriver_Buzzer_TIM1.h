#ifndef _SCDriver_Buzzer_TIM1_H_
#define _SCDriver_Buzzer_TIM1_H_
//<<<Use SPTML>>>
#define SCD_BZ_TIM1 P11//SCD_BZ_TIM1 
#define SCD_BZ_TIM1_INIT 0x0102//SCD_BZ_TIM1_INIT 
extern void SCD_BZ_TIM1_Init(unsigned int BuzzerFreg,unsigned int BuzzerHoldTime);
extern void SCD_BZ_TIM1_Scan();
extern void SCD_BZ_TIM1_Run();
//<<<end of SPTML>>>
#endif
