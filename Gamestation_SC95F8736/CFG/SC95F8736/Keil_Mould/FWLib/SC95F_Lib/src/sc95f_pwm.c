//************************************************************
//  Copyright (c) 
//	�ļ�����: 			sc95f_pwm.c
//	����:
//	ģ�鹦��: 			PWM�̼��⺯��C�ļ�
//  ����������:	2022��7��22��
// 	�汾: 				V1.10010
//  ˵��:					���ļ���������SC95Fϵ��оƬ
//*************************************************************

#include "sc95f_pwm.h"
//PWM2/3/4��TIM2/3/4���üĴ���
#include "sc95f_timer2.h"
#include "sc95f_timer3.h"
#include "sc95f_timer4.h"

#if defined(SC95F8x1x) || defined(SC95F7x1x)
uint16_t xdata PWMREG[8] _at_ 0x1040;              //PWMռ�ձȵ��ڼĴ���
uint16_t pwm_tmpreg[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //PWMռ�ձȵ��ڼĴ�����������

/**************************************************
*��������:void PWM_DeInit(void)
*��������:PWM��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void PWM_DeInit(void)
{
  static uint8_t i;
  PWMCON = 0X00;
  PWMCFG = 0;
  PWMCON = 0;
  PWMFLT = 0X00;
  PWMDFR = 0X00;
  IE1 &= 0XFD;
  IP1 &= 0XFD;

  for(i = 0; i < 8; i++)
  {
    PWMREG[i] = 0;
  }
}

/**************************************************
*��������:void PWM_Init(PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
*��������:PWM��ʼ�����ú���
*��ڲ���:
PWM_PresSel_TypeDef:PWM_PresSel:Ԥ��Ƶѡ��
uint16_t:PWM_Period:PWM��������
*���ڲ���:void
**************************************************/
void PWM_Init(PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
{
  PWM_Period -= 1;
  PWMCFG = (PWMCFG & 0XCF) | PWM_PresSel;                 //Ԥ��Ƶ
  PWMCFG = (PWMCFG & 0XF0) | (uint8_t)(PWM_Period / 256); //���ڸ�4λ
  PWMCON = (uint8_t)(PWM_Period & 0X00FF);                //���ڵ�8λ
}

/**************************************************
*��������:void PWM_OutputStateConfig(uint8_t PWM_OutputPin, PWM_OutputState_TypeDef PWM_OutputState)
*��������:PWMx���ʹ��/ʧ�����ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMxѡ��uint8_t��Ϊ��Σ��������λ�������
PWM_OutputState_TypeDef:PWM_OutputState:PWM���״̬����
*���ڲ���:void
**************************************************/
void PWM_OutputStateConfig(uint8_t PWM_OutputPin, PWM_OutputState_TypeDef PWM_OutputState)
{
  uint8_t i;

  for(i = 0; i < 8; i++)
  {
    if(PWM_OutputPin & (0x01 << i))
    {
      if(PWM_OutputState == PWM_OUTPUTSTATE_DISABLE)
      {
        pwm_tmpreg[i] &= 0X7FFF;
      }
      else
      {
        pwm_tmpreg[i] |= 0X8000;
      }

      PWMREG[i] = pwm_tmpreg[i];
    }
  }
}

/**************************************************
*��������:void PWM_PolarityConfig(uint8_t PWM_OutputPin, PWM_Polarity_TypeDef PWM_Polarity)
*��������:PWMx��/����������ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMxѡ��uint8_t��Ϊ��Σ��������λ�������
PWM_Polarity_TypeDef:PWM_Polarity:PWM�����/��������
*���ڲ���:void
**************************************************/
void PWM_PolarityConfig(uint8_t PWM_OutputPin, PWM_Polarity_TypeDef PWM_Polarity)
{
  uint8_t i;

  for(i = 0; i < 8; i++)
  {
    if(PWM_OutputPin & (0x01 << i))
    {
      if(PWM_Polarity == PWM_POLARITY_NON_INVERT)
      {
        pwm_tmpreg[i] &= 0XBFFF;
      }
      else
      {
        pwm_tmpreg[i] |= 0X4000;
      }

      PWMREG[i] = pwm_tmpreg[i];
    }
  }
}

/**************************************************
*��������:void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle)
*��������:PWMx��������ģʽ���ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMx����ͨ��ѡ��
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
*���ڲ���:void
**************************************************/
void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle)
{
  uint8_t i;

  for(i = 0; i < 8; i++)
  {
    if(PWM_OutputPin & (0x01 << i))
    {
      pwm_tmpreg[i] = pwm_tmpreg[i] & 0XF000 | PWM_DutyCycle;
      PWMREG[i] = pwm_tmpreg[i];
    }
  }
}
/**************************************************
*��������:void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin, uint16_t PWM_DutyCycle)
*��������:PWMxPWMy��������ģʽ���ú���
*��ڲ���:
PWM_ComplementaryOutputPin_TypeDef:PWM_ComplementaryOutputPin:PWMxPWMy����ͨ��ѡ��
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
*���ڲ���:void
**************************************************/
void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin,
                                 uint16_t PWM_DutyCycle)
{
  PWMCON = 0X08;

  switch(PWM_ComplementaryOutputPin)  //����ռ�ձ�
  {
    case PWM40PWM41:
      PWMREG[PWM40PWM41] = (PWMREG[PWM40PWM41] & 0XC000) | PWM_DutyCycle;
      break;

    case PWM42PWM43:
      PWMREG[PWM42PWM43] = (PWMREG[PWM42PWM43] & 0XC000) | PWM_DutyCycle;
      break;

    case PWM50PWM51:
      PWMREG[PWM50PWM51] = (PWMREG[PWM50PWM51] & 0XC000) | PWM_DutyCycle;
      break;

    case PWM52PWM53:
      PWMREG[PWM52PWM53] = (PWMREG[PWM52PWM53] & 0XC000) | PWM_DutyCycle;
      break;

    default:
      break;
  }
}

/**************************************************
*��������:void PWM_DeadTimeConfig(uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
*��������:PWM��������ģʽ������ʱ�����ú���
*��ڲ���:
uint8_t:PWM_RisingDeadTime:PWM��������ʱ��00-FF
uint8_t:PWM_FallingDeadTime:PWM�����½�ʱ��00-FF
*���ڲ���:void
**************************************************/
void PWM_DeadTimeConfig(uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
{
  PWMDFR = (PWM_RisingDeadTime | (PWM_FallingDeadTime << 4));
}

/*****************************************************
*��������:void PWM_Cmd(FunctionalState NewState)
*��������:PWM���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_Cmd(FunctionalState NewState)
{
  if(NewState != DISABLE)
  {
    PWMCFG |= 0X80;
  }
  else
  {
    PWMCFG &= 0X7F;
  }
}

/*****************************************************
*��������:void PWM_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:PWM�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  if(NewState != DISABLE)
  {
    IE1 |= 0X02;
  }
  else
  {
    IE1 &= 0XFD;
  }

  if(Priority == LOW)
  {
    IP1 &= ~0X02;
  }
  else
  {
    IP1 |= 0X02;
  }
}

/*****************************************************
*��������:FlagStatus PWM_GetFlagStatus(void)
*��������:���PWM�жϱ�־״̬
*��ڲ���:void
*���ڲ���:
FlagStatus:PWM�жϱ�־״̬
*****************************************************/
FlagStatus PWM_GetFlagStatus(void)
{
  return (bool)(PWMCFG & 0X40);
}

/*****************************************************
*��������:void PWM_ClearFlag(void)
*��������:���PWM�жϱ�־״̬
*��ڲ���:void
*���ڲ���:void
*****************************************************/
void PWM_ClearFlag(void)
{
  PWMCFG &= 0XBF;
}

/*****************************************************
*��������:FlagStatus PWM_GetFaultDetectionFlagStatus(void)
*��������:���PWM���ϼ���־λ״̬
*��ڲ���:void
*���ڲ���:
FlagStatus:PWM���ϼ���־λ״̬
*****************************************************/
FlagStatus PWM_GetFaultDetectionFlagStatus(void)
{
  return (bool)(PWMFLT & 0X40);
}

/*****************************************************
*��������:void PWM_ClearFaultDetectionFlag(void)
*��������:���PWM���ϼ���־λ״̬   // ��ע��,��������ģʽ�£���λ��������
*��ڲ���:void
*���ڲ���:void
*****************************************************/
void PWM_ClearFaultDetectionFlag(void)
{
  PWMFLT &= 0XBF;
}

/*****************************************************
*��������:void PWM_FaultDetectionFunctionConfig(FunctionalState NewState)
*��������:PWM���ϼ�⹦�ܿ���/�ر�
*��ڲ���:
FunctionalState:NewState:���ϼ�⹦�ܿ���/�ر�
*���ڲ���:void
*****************************************************/
void PWM_FaultDetectionConfig(FunctionalState NewState)
{
  if(NewState != DISABLE)
  {
    PWMFLT |= 0X80;
  }
  else
  {
    PWMFLT &= 0X7F;
  }
}

/*****************************************************
*��������:void PWM_FaultDetectionModeConfig(PWM_FaultDetectionMode_TypeDef FaultDetectionMode, PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect, PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
*��������:PWM���ϼ��ģʽ����
*��ڲ���:
PWM_FaultDetectionMode_TypeDef:FaultDetectionMode:���ϼ�⹦��ģʽ����:����ģʽ/����ģʽ
PWM_FaultDetectionVoltageSelect_TypeDef:FaultDetectionVoltageSelect:���ϼ���ƽѡ��
PWM_FaultDetectionWaveFilteringTime_TypeDef:FaultDetectionWaveFilteringTime:���ϼ�������ź��˲�ʱ��ѡ��
*���ڲ���:void
*****************************************************/
void PWM_FaultDetectionModeConfig(PWM_FaultDetectionMode_TypeDef FaultDetectionMode,
                                  PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect,
                                  PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
{
  PWMFLT = (PWMFLT & 0XC0) | FaultDetectionMode | FaultDetectionVoltageSelect |
           FaultDetectionWaveFilteringTime;
}

/*****************************************************
*��������:void PWM_Aligned_Mode_Select(void)
*��������:ѡ��PWM�Ķ���ģʽ
*��ڲ���:
PWM_Aligned_Mode_TypeDef:PWM_Aligned_Mode:ѡ�����ģʽ
*���ڲ���:void
*****************************************************/
void PWM_Aligned_Mode_Select(PWM_Aligned_Mode_TypeDef PWM_Aligned_Mode)
{
  if(PWM_Aligned_Mode == PWM_Edge_Aligned_Mode)
  {
    PWMCON &= 0XFB;
  }
  else if(PWM_Aligned_Mode == PWM_Center_Alignment_Mode)
  {
    PWMCON |= 0X04;
  }
}
#endif

#if defined(SC95F8x2x) || defined(SC95F7x2x)
unsigned int xdata PDT[8] _at_ 0x1040;

/**************************************************
*��������:void PWM_DeInit(void)
*��������:PWM��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void PWM_DeInit(void)
{
  PWMCFG = 0X00;
  PWMCON0 = 0X00;
  PWMCON1 = 0X00;
  PWMPDL = 0X00;
  PWMPDH = 0X00;
  PWMFLT = 0X00;
  PWMDFR = 0X00;

  IE1 &= ~0X02;
  IP1 &= ~0X02;
}

/**************************************************
*��������:void PWM_Init(PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
*��������:PWM��ʼ�����ú���
*��ڲ���:
PWM_PresSel_TypeDef:PWM_PresSel:Ԥ��Ƶѡ��
uint16_t:PWM_Period:PWM��������
*���ڲ���:void
**************************************************/
void PWM_Init(PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
{
  PWM_Period -= 1;
  PWMCON0 &= 0XCF;
  PWMCON0 |= PWM_PresSel;    //Ԥ��Ƶ
  PWMPDL = PWM_Period;       //���ڵͰ�λ
  PWMPDH = PWM_Period / 256; //���ڸ߰�λ
}

/**************************************************
*��������:void PWM_OutputStateConfig(uint8_t PWM_OutputPin, PWM_OutputState_TypeDef PWM_OutputState)
*��������:PWMx���ʹ��/ʧ�����ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMxѡ��uint8_t��Ϊ��Σ��������λ�������
PWM_OutputState_TypeDef:PWM_OutputState:PWM���״̬����
*���ڲ���:void
**************************************************/
void PWM_OutputStateConfig(uint8_t PWM_OutputPin, PWM_OutputState_TypeDef PWM_OutputState)
{
  if(PWM_OutputState == PWM_OUTPUTSTATE_ENABLE)
  {
    PWMCON1 |= PWM_OutputPin;
  }
  else
  {
    PWMCON1 &= (~PWM_OutputPin);
  }
}

/**************************************************
*��������:void PWM_PolarityConfig(uint8_t PWM_OutputPin, PWM_Polarity_TypeDef PWM_Polarity)
*��������:PWMx��/����������ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMxѡ��uint8_t��Ϊ��Σ��������λ�������
PWM_Polarity_TypeDef:PWM_Polarity:PWM�����/��������
*���ڲ���:void
**************************************************/
void PWM_PolarityConfig(uint8_t PWM_OutputPin, PWM_Polarity_TypeDef PWM_Polarity)
{
  if(PWM_Polarity == PWM_POLARITY_INVERT)
  {
    PWMCFG |= PWM_OutputPin;
  }
  else
  {
    PWMCFG &= (~PWM_OutputPin);
  }
}

/**************************************************
*��������:void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle)
*��������:PWMx��������ģʽ���ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMx����ͨ��ѡ��
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
*���ڲ���:void
**************************************************/
void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle)
{
  PWMCON0 &= 0XFD; //����PWMΪ����ģʽ

  switch(PWM_OutputPin)  //����ռ�ձ�
  {
    case PWM0:
      PDT[0] = PWM_DutyCycle;
      break;

    case PWM1:
      PDT[1] = PWM_DutyCycle;
      break;

    case PWM2:
      PDT[2] = PWM_DutyCycle;
      break;

    case PWM3:
      PDT[3] = PWM_DutyCycle;
      break;

    case PWM4:
      PDT[4] = PWM_DutyCycle;
      break;

    case PWM5:
      PDT[5] = PWM_DutyCycle;
      break;

    case PWM6:
      PDT[6] = PWM_DutyCycle;
      break;

    case PWM7:
      PDT[7] = PWM_DutyCycle;
      break;

    default:
      break;
  }
}

/**************************************************
*��������:void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin, uint16_t PWM_DutyCycle)
*��������:PWMxPWMy��������ģʽ���ú���
*��ڲ���:
PWM_ComplementaryOutputPin_TypeDef:PWM_ComplementaryOutputPin:PWMxPWMy����ͨ��ѡ��
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
*���ڲ���:void
**************************************************/
void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin,
                                 uint16_t PWM_DutyCycle)
{
  PWMCON0 |= 0X02; //����PWMΪ����ģʽ

  switch(PWM_ComplementaryOutputPin)  //����ռ�ձ�
  {
    case PWM0PWM1:
      PDT[0] = PWM_DutyCycle;
      break;

    case PWM2PWM3:
      PDT[2] = PWM_DutyCycle;
      break;

    case PWM4PWM5:
      PDT[4] = PWM_DutyCycle;
      break;

    case PWM6PWM7:
      PDT[6] = PWM_DutyCycle;
      break;

    default:
      break;
  }
}

/**************************************************
*��������:void PWM_DeadTimeConfig(uint8_t PWM_RisingDeadTime, uint8_t PWM_fallingDeadTime)
*��������:PWM��������ģʽ������ʱ�����ú���
*��ڲ���:
uint8_t:PWM_RisingDeadTime:PWM��������ʱ��
uint8_t:PWM_fallingDeadTime:PWM�����½�ʱ��
*���ڲ���:void
**************************************************/
void PWM_DeadTimeConfig(uint8_t PWM_RisingDeadTime, uint8_t PWM_fallingDeadTime)
{
  PWMDFR = (PWM_RisingDeadTime | (PWM_fallingDeadTime << 4));
}

/*****************************************************
*��������:void PWM_Cmd(FunctionalState NewState)
*��������:PWM���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_Cmd(FunctionalState NewState)
{
  if(NewState != DISABLE)
  {
    PWMCON0 |= 0X80;
  }
  else
  {
    PWMCON0 &= ~0X80;
  }
}

/*****************************************************
*��������:void PWM_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:PWM�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  if(NewState != DISABLE)
  {
    IE1 |= 0X02;
  }
  else
  {
    IE1 &= 0XFD;
  }

  if(Priority == LOW)
  {
    IP1 &= 0XFD;
  }
  else
  {
    IP1 |= 0X02;
  }
}

/*****************************************************
*��������:FlagStatus PWM_GetFlagStatus(void)
*��������:���PWM�жϱ�־״̬
*��ڲ���:void
*���ڲ���:
FlagStatus:PWM�жϱ�־״̬
*****************************************************/
FlagStatus PWM_GetFlagStatus(void)
{
  return (bool)(PWMCON0 & 0X40);
}

/*****************************************************
*��������:void PWM_ClearFlag(void)
*��������:���PWM�жϱ�־״̬
*��ڲ���:void
*���ڲ���:void
*****************************************************/
void PWM_ClearFlag(void)
{
  PWMCON0 &= 0XBF;
}
/*****************************************************
*��������:void PWM_Aligned_Mode_Select(void)
*��������:ѡ��PWM�Ķ���ģʽ
*��ڲ���:
PWM_Aligned_Mode_TypeDef:PWM_Aligned_Mode:ѡ�����ģʽ
*���ڲ���:void
*****************************************************/
void PWM_Aligned_Mode_Select(PWM_Aligned_Mode_TypeDef PWM_Aligned_Mode)
{
  if(PWM_Aligned_Mode == PWM_Edge_Aligned_Mode)
  {
    PWMCON0 &= 0XFE;
  }
  else if(PWM_Aligned_Mode == PWM_Center_Alignment_Mode)
  {
    PWMCON0 |= 0X01;
  }
}

/*****************************************************
*��������:FlagStatus PWM_GetFaultDetectionFlagStatus(void)
*��������:���PWM���ϼ���־λ״̬
*��ڲ���:void
*���ڲ���:
FlagStatus:PWM���ϼ���־λ״̬
*****************************************************/
FlagStatus PWM_GetFaultDetectionFlagStatus(void)
{
  return (bool)(PWMFLT & 0X40);
}

/*****************************************************
*��������:void PWM_ClearFaultDetectionFlag(void)
*��������:���PWM���ϼ���־λ״̬   // ��ע��,��������ģʽ�£���λ��������
*��ڲ���:void
*���ڲ���:void
*****************************************************/
void PWM_ClearFaultDetectionFlag(void)
{
  PWMFLT &= 0XBF;
}

/*****************************************************
*��������:void PWM_FaultDetectionFunctionConfig(FunctionalState NewState)
*��������:PWM���ϼ�⹦�ܿ���/�ر�
*��ڲ���:
FunctionalState:NewState:���ϼ�⹦�ܿ���/�ر�
*���ڲ���:void
*****************************************************/
void PWM_FaultDetectionConfig(FunctionalState NewState)
{
  if(NewState != DISABLE)
  {
    PWMFLT |= 0X80;
  }
  else
  {
    PWMFLT &= 0X7F;
  }
}

/*****************************************************
*��������:void PWM_FaultDetectionModeConfig(PWM_FaultDetectionMode_TypeDef FaultDetectionMode, PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect, PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
*��������:PWM���ϼ��ģʽ����
*��ڲ���:
PWM_FaultDetectionMode_TypeDef:FaultDetectionMode:���ϼ�⹦��ģʽ����:����ģʽ/����ģʽ
PWM_FaultDetectionVoltageSelect_TypeDef:FaultDetectionVoltageSelect:���ϼ���ƽѡ��
PWM_FaultDetectionWaveFilteringTime_TypeDef:FaultDetectionWaveFilteringTime:���ϼ�������ź��˲�ʱ��ѡ��
*���ڲ���:void
*****************************************************/
void PWM_FaultDetectionModeConfig(PWM_FaultDetectionMode_TypeDef FaultDetectionMode,
                                  PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect,
                                  PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
{
  PWMFLT = (PWMFLT & 0XC0) | FaultDetectionMode | FaultDetectionVoltageSelect |
           FaultDetectionWaveFilteringTime;
}
#endif

#if defined(SC95FWxx)
uint8_t xdata PWMREG[80] _at_ 0x1000; //PWMռ�ձȵ��ڼĴ���
/**************************************************
*��������:void PWM_DeInit(void)
*��������:PWM��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void PWM_DeInit(void)
{
  static uint8_t i;
  PWMCON0 = 0X00;
  PWMCON0 = 0X00;
  PWMCFG1 = 0X00;
  PWMCON1 = 0X00;
  IE1 &= 0XFD;
  IP1 &= 0XFD;

  for(i = 0; i < 80; i++)
  {
    PWMREG[i] = 0;
  }
}

/**************************************************
*��������:PWM_Init(PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
*��������:PWM��ʼ�����ú���
*��ڲ���:
PWM_PresSel_TypeDef:PWM_PresSel:Ԥ��Ƶѡ��
uint16_t:PWM_Period:PWM��������
*���ڲ���:void
**************************************************/
void PWM_Init(PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
{
  if((PWM_PresSel & 0X0F) == PWM0_Type)
  {
    PWM_Period -= 1;
    PWMCFG0 = (PWMCON0 & 0XCF) | (PWM_PresSel & 0XF0);        //Ԥ��Ƶ
    PWMCFG0 = (PWMCON0 & 0XF0) | (uint8_t)(PWM_Period / 256); //���ڸ�4λ
    PWMCON0 = (uint8_t)(PWM_Period & 0X00FF);                 //���ڵ�8λ
  }
  else if((PWM_PresSel & 0X0F) == PWM1_Type)
  {
    PWM_Period -= 1;
    PWMCFG1 = (PWMCFG1 & 0XCF) | (PWM_PresSel & 0XF0);        //Ԥ��Ƶ
    PWMCFG1 = (PWMCFG1 & 0XF0) | (uint8_t)(PWM_Period / 256); //���ڸ�4λ
    PWMCON1 = (uint8_t)PWM_Period;                            //���ڵ�8λ
  }
}

/*****************************************************
*��������:void PWM_Aligned_Mode_Select(void)
*��������:ѡ��PWM�Ķ���ģʽ
*��ڲ���:
PWM_Aligned_Mode_TypeDef:PWM_Aligned_Mode:ѡ�����ģʽ
*���ڲ���:void
*****************************************************/
void PWM_Aligned_Mode_Select(PWM_Aligned_Mode_TypeDef PWM_Aligned_Mode)
{

  //PWM0ѡ�����ģʽ����
  if(PWM_Aligned_Mode == PWM0_Edge_Aligned_Mode)
  {
    PWMMOD &= 0XFE;
  }
  else if(PWM_Aligned_Mode == PWM0_Center_Alignment_Mode)
  {
    PWMMOD |= 0X01;
  }
  //PWM1ѡ�����ģʽ����
  else if(PWM_Aligned_Mode == PWM1_Edge_Aligned_Mode)
  {
    PWMMOD &= 0XFB;
  }
  else if(PWM_Aligned_Mode == PWM1_Center_Alignment_Mode)
  {
    PWMMOD |= 0X04;
  }
}

/**************************************************
*��������:void PWM_OutputStateConfig(uint8_t PWM_OutputPin, PWM_OutputState_TypeDef PWM_OutputState)
*��������:PWMx���ʹ��/ʧ�����ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMxѡ��uint8_t��Ϊ��Σ��������λ�������
PWM_OutputState_TypeDef:PWM_OutputState:PWM���״̬����
*���ڲ���:void
**************************************************/
void PWM_OutputStateConfig(uint8_t PWM_OutputPin,
                           PWM_OutputState_TypeDef PWM_OutputState)
{
  if(PWM_OutputState == ENABLE)
  {
    PWMREG[PWM_OutputPin] |= 0x80;
  }
  else
  {
    PWMREG[PWM_OutputPin] &= 0x7F;
  }
}

/**************************************************
*��������:void PWM_PolarityConfig(PWM_OutputPin_TypeDef PWM_OutputPin, PWM_Polarity_TypeDef PWM_Polarity)
*��������:PWMx��/����������ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMxѡ��uint8_t��Ϊ��Σ��������λ�������
PWM_Polarity_TypeDef:PWM_Polarity:PWM�����/��������
*���ڲ���:void
**************************************************/
void PWM_PolarityConfig(uint8_t PWM_OutputPin,
                        PWM_Polarity_TypeDef PWM_Polarity)
{
  if(PWM_Polarity == PWM_POLARITY_INVERT)
  {
    PWMREG[PWM_OutputPin] |= 0x40;
  }
  else
  {
    PWMREG[PWM_OutputPin] &= 0xBF;
  }
}

/**************************************************
*��������:void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle)
*��������:PWMx��������ģʽ���ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMx����ͨ��ѡ��uint8_t��Ϊ��Σ��������λ�������
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
*���ڲ���:void
**************************************************/
void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle)
{
  PWMREG[PWM_OutputPin + 1] = PWM_DutyCycle;
  PWMREG[PWM_OutputPin] = (PWMREG[PWM_OutputPin] & 0xF0) | (PWM_DutyCycle / 256);
}

/**************************************************
*��������:void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin, uint16_t PWM_DutyCycle)
*��������:PWMxPWMy��������ģʽ���ú���
*��ڲ���:
PWM_ComplementaryOutputPin_TypeDef:PWM_ComplementaryOutputPin:PWMxPWMy����ͨ��ѡ��
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
*���ڲ���:void
**************************************************/
void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin,
                                 uint16_t PWM_DutyCycle)
{
  PWMMOD |= 0X08;
  PWMREG[PWM40 + PWM_ComplementaryOutputPin * 2 + 1] = PWM_DutyCycle;
  PWMREG[PWM40 + PWM_ComplementaryOutputPin * 2] = (PWMREG[PWM40 + PWM_ComplementaryOutputPin * 2] & 0xF0) | (PWM_DutyCycle / 256);
}

/**************************************************
*��������:void PWM_DeadTimeConfig(uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
*��������:PWM��������ģʽ������ʱ�����ú���
*��ڲ���:
uint8_t:PWM_RisingDeadTime:PWM��������ʱ��	 00-FF
uint8_t:PWM_FallingDeadTime:PWM�����½�ʱ��  00-FF
*���ڲ���:void
**************************************************/
void PWM_DeadTimeConfig(uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
{
  PWMDFR1 = (PWM_RisingDeadTime | (PWM_FallingDeadTime << 4));
}

/**************************************************
*��������:void PWM_DeadTimeConfigEX(PWM_Type_TypeDef PWM_Type, uint8_t PWM_RisingDeadTime, uint8_t PWM_fallingDeadTime)
*��������:PWM��������ģʽ������ʱ�����ú���
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����ѡ��
uint8_t:PWM_RisingDeadTime:PWM��������ʱ��	 00-FF
uint8_t:PWM_FallingDeadTime:PWM�����½�ʱ��  00-FF
*���ڲ���:void
**************************************************/
void PWM_DeadTimeConfigEX(PWM_Type_TypeDef PWM_Type, uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
{
  if(PWM_Type == PWM1_Type)
  {
    PWMDFR1 = (PWM_RisingDeadTime | (PWM_FallingDeadTime << 4));
  }
}

/*****************************************************
*��������:void PWM_Cmd(PWM_Type_TypeDef PWM_Type,FunctionalState NewState)
*��������:PWM���ܿ��غ���
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_CmdEX(PWM_Type_TypeDef PWM_Type,
               FunctionalState NewState)
{
  if(PWM_Type == PWM0_Type)
  {
    if(NewState != DISABLE)
    {
      PWMCFG0 |= 0X80;
    }
    else
    {
      PWMCFG0 &= 0X7F;
    }
  }
  else if(PWM_Type == PWM1_Type)
  {
    if(NewState != DISABLE)
    {
      PWMCFG1 |= 0X80;
    }
    else
    {
      PWMCFG1 &= 0X7F;
    }
  }
}

/*****************************************************
*��������:void PWM_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:PWM�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_ITConfig(FunctionalState NewState,
                  PriorityStatus Priority)
{
  if(NewState != DISABLE)
  {
    IE1 |= 0X02;
  }
  else
  {
    IE1 &= 0XFD;
  }

  if(Priority == LOW)
  {
    IP1 &= ~0X02;
  }
  else
  {
    IP1 |= 0X02;
  }
}

/*****************************************************
*��������:FlagStatus PWM_GetFlagStatusEX(PWM_Type_TypeDef
                               PWM_Type)
*��������:���PWM�жϱ�־״̬����ͨ��
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����
*���ڲ���:
FlagStatus:PWM�жϱ�־״̬
*****************************************************/
FlagStatus PWM_GetFlagStatusEX(PWM_Type_TypeDef
                               PWM_Type)
{
  if(PWM_Type == PWM0_Type)
  {
    return (bool)(PWMCFG0 & 0X40);
  }
  else if(PWM_Type == PWM1_Type)
  {
    return (bool)(PWMCFG1 & 0X40);
  }
  return 0;
}

/*****************************************************
*��������:void PWM1_ClearFlag(void)
*��������:���PWM�жϱ�־״̬
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����
*���ڲ���:void
*****************************************************/
void PWM_ClearFlagEX(PWM_Type_TypeDef PWM_Type)
{
  if(PWM_Type == PWM0_Type)
  {
    PWMCFG0 &= 0XBF;
  }
  else if(PWM_Type == PWM1_Type)
  {
    PWMCFG1 &= 0XBF;
  }
}

/*****************************************************
*��������:void PWM_IndependentModeConfigEX(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle, PWM_OutputState_TypeDef PWM_OutputState)
*��������:���ö���ģʽռ�ձȣ�����ѡ���Ƿ���ͨ��
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMͨ��
uint16_t:PWM_DutyCycle PWMռ�ձ�����
PWM_OutputState_TypeDef:PWM_OutputState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_IndependentModeConfigEX(PWM_OutputPin_TypeDef PWM_OutputPin,
                                 uint16_t PWM_DutyCycle,
                                 PWM_OutputState_TypeDef PWM_OutputState)
{
  if(PWM_OutputState == ENABLE)
  {
    if(PWM_OutputPin >= PWM40)  //�������PWM1���л�Ϊ����ģʽ
    {
      PWMMOD &= 0XF7;
    }

    PWMREG[PWM_OutputPin + 1] = PWM_DutyCycle;
    PWMREG[PWM_OutputPin] = (PWMREG[PWM_OutputPin] & 0xF0) | (PWM_DutyCycle / 256) | 0x80;
  }
  else
  {
    PWMREG[PWM_OutputPin] &= 0x7F;
  }
}

/*****************************************************
*��������:void PWM_ComplementaryModeConfigEX(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle, PWM_OutputState_TypeDef PWM_OutputState)
*��������:����PWM����ģʽռ�ձȣ���ѡ���Ƿ���ͨ��
*��ڲ���:
PWM_ComplementaryOutputPin_TypeDef:PWM_ComplementaryOutputPin:PWMͨ��
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
PWM_OutputState_TypeDef:PWM_OutputState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_ComplementaryModeConfigEX(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin,
                                   uint16_t PWM_DutyCycle,
                                   PWM_OutputState_TypeDef PWM_OutputState)
{
  if(PWM_OutputState == ENABLE)
  {
    PWMMOD |= 0X08;
    PWMREG[PWM40 + PWM_ComplementaryOutputPin * 4] = (PWMREG[PWM40 + PWM_ComplementaryOutputPin * 4] & 0xF0) | (0x80 | (PWM_DutyCycle / 256));
    PWMREG[PWM40 + PWM_ComplementaryOutputPin * 4 + 1] = PWM_DutyCycle;
    PWMREG[PWM40 + PWM_ComplementaryOutputPin * 4 + 2] |= 0x80;
  }
  else
  {
    PWMREG[PWM40 + PWM_ComplementaryOutputPin * 4] &= 0x7F;
    PWMREG[PWM40 + PWM_ComplementaryOutputPin * 4 + 2] &= 0x7F;
  }
}

/*****************************************************
*��������:FlagStatus PWM_GetFaultDetectionFlagStatus(void)
*��������:��ÿ�ѡPWMԴ���ϼ���־λ״̬
*��ڲ���:void
*���ڲ���:
FlagStatus:PWM���ϼ���־λ״̬
*****************************************************/
FlagStatus PWM_GetFaultDetectionFlagStatusEX(PWM_Type_TypeDef PWM_Type)
{
  if(PWM_Type == PWM1_Type)
  {
    return (bool)(PWMFLT1 & 0X40);
  }

  return RESET;
}

/*****************************************************
*��������:void PWM_ClearFaultDetectionFlag(void)
*��������:�����ѡPWMԴ���ϼ���־λ״̬   // ��ע��,��������ģʽ�£���λ��������
*��ڲ���:void
*���ڲ���:void
*****************************************************/
void PWM_ClearFaultDetectionFlagEX(PWM_Type_TypeDef PWM_Type)
{
  if(PWM_Type == PWM1_Type)
  {
    PWMFLT1 &= 0XBF;
  }
}

/*****************************************************
*��������:void PWM_FaultDetectionFunctionConfig(FunctionalState NewState)
*��������:PWM���ϼ�⹦�ܿ���/�ر�
*��ڲ���:
FunctionalState:NewState:���ϼ�⹦�ܿ���/�ر�
*���ڲ���:void
*****************************************************/
void PWM_FaultDetectionConfigEX(PWM_Type_TypeDef PWM_Type, FunctionalState NewState)
{
  if(PWM_Type == PWM1_Type)
  {
    if(NewState != DISABLE)
    {
      PWMFLT1 |= 0X80;
    }
    else
    {
      PWMFLT1 &= 0X7F;
    }
  }
}

/*****************************************************
*��������:void PWM_FaultDetectionModeConfigEX(PWM_Type_TypeDef PWM_Type, PWM_FaultDetectionMode_TypeDef FaultDetectionMode, PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect, PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
*��������:PWM���ϼ��ģʽ����
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����ѡ��
PWM_FaultDetectionMode_TypeDef:FaultDetectionMode:���ϼ�⹦��ģʽ����: ����ģʽ/����ģʽ
PWM_FaultDetectionVoltageSelect_TypeDef:FaultDetectionVoltageSelect:���ϼ���ƽѡ��
PWM_FaultDetectionWaveFilteringTime_TypeDef:FaultDetectionWaveFilteringTime:���ϼ�������ź��˲�ʱ��ѡ��
*���ڲ���:void
*****************************************************/
void PWM_FaultDetectionModeConfigEX(PWM_Type_TypeDef PWM_Type,
                                    PWM_FaultDetectionMode_TypeDef FaultDetectionMode,
                                    PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect,
                                    PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
{
  if(PWM_Type == PWM1_Type)
  {
    PWMFLT1 = (PWMFLT1 & 0XC0) | FaultDetectionMode | FaultDetectionVoltageSelect |
              FaultDetectionWaveFilteringTime;
  }
}

#endif

#if defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)\
		|| defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B)
uint8_t xdata PWMREG[28] _at_ 0x2034; //PWMռ�ձȵ��ڼĴ���
/**************************************************
*��������:void PWM_DeInit(void)
*��������:PWM��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void PWM_DeInit(void)
{
  static uint8_t i;

  //PWM0��ؼĴ�������
  PWMCON0 = 0X00;
  PWMCFG = 0X00;
  PWMCON1 = 0X00;
  PWMPDL = 0x00;
  PWMPDH = 0x00;
  IE1 &= 0XFD;
  IP1 &= 0XFD;

  //PWM2/3/4��ؼĴ���
  for(i = 0; i < 3; i++)
  {
    TXINX = 0x02 + i;
    TXCON &= ~0x04;
    TXMOD &= ~0x3C;
    RCAPXH = 0x00;
    RCAPXL = 0x00;
  }

  //�����ж�ʹ��λ�����ȼ�λ
  ET2 = 0;
  IP &= ~0x20;
  IE1 &= ~0xC0;
  IP1 &= ~0xC0;

  //ռ�ձȼĴ���
  for(i = 0; i < 14; i++)
  {
    PWMREG[i] = 0;
  }
}

/**************************************************
*��������:PWM_Init(PWM_Type_TypeDef PWM_Type,PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
*��������:PWM��ʼ�����ú���
*��ڲ���:
PWM_PresSel_TypeDef:PWM_PresSel:Ԥ��Ƶѡ��
uint16_t:PWM_Period:PWM��������
*���ڲ���:void
**************************************************/
void PWM_Init(PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
{
  if((PWM_PresSel & 0X0F) == PWM0_Type)
  {
    PWM_Period -= 1;
    PWMCON0 = (PWMCON0 & 0XCF) | (PWM_PresSel & 0XF0); //Ԥ��Ƶ
    PWMPDH = (uint8_t)(PWM_Period >> 8);               //���ڸ�8λ
    PWMPDL = (uint8_t)(PWM_Period & 0X00FF);           //���ڵ�8λ
  }
  else
  {
    TXINX = (PWM_PresSel & 0X0F);
    PWM_PresSel = DISABLE;                   //PWM2��ƵΨһ����������
    RCAPXH = (uint8_t)(PWM_Period >> 8);     //���ڸ�8λ
    RCAPXL = (uint8_t)(PWM_Period & 0X00FF); //���ڵ�8λ
  }
}

/*****************************************************
*��������:void PWM_Aligned_Mode_Select(void)
*��������:ѡ��PWM�Ķ���ģʽ
*��ڲ���:
PWM_Aligned_Mode_TypeDef:PWM_Aligned_Mode:ѡ�����ģʽ
*���ڲ���:void
*****************************************************/
void PWM_Aligned_Mode_Select(PWM_Aligned_Mode_TypeDef PWM_Aligned_Mode)
{

  //PWM0ѡ�����ģʽ����
  if(PWM_Aligned_Mode == PWM0_Edge_Aligned_Mode)
  {
    PWMCON0 &= 0XFE;
  }
  else if(PWM_Aligned_Mode == PWM0_Center_Alignment_Mode)
  {
    PWMCON0 |= 0X01;
  }
}

/**************************************************
*��������:void PWM_OutputStateConfig(uint8_t PWM_OutputPin, PWM_OutputState_TypeDef PWM_OutputState)
*��������:PWMx���ʹ��/ʧ�����ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMxѡ��uint8_t��Ϊ��Σ��������λ�������
PWM_OutputState_TypeDef:PWM_OutputState:PWM���״̬����
*���ڲ���:void
**************************************************/
void PWM_OutputStateConfig(uint8_t PWM_OutputPin,
                           PWM_OutputState_TypeDef PWM_OutputState)
{
  unsigned char Reg_Data;
  if((PWM_OutputPin & 0xF0) == 0x00)
  {
    if(PWM_OutputState == PWM_OUTPUTSTATE_ENABLE)
    {
      PWMCON1 |= 1 << ((PWM_OutputPin >> 1) & 0x0F);
    }
    else
    {
      PWMCON1 &= ~(1 << ((PWM_OutputPin >> 1) & 0x0F));
    }
  }
  else
  {
    TXINX = (PWM_OutputPin & 0xF0) >> 4;

    if(PWM_OutputPin & 0x02)
    {
      Reg_Data = 0x20;
    }
    else
    {
      Reg_Data = 0x10;
    }

    if(PWM_OutputState == PWM_OUTPUTSTATE_ENABLE)
    {
      TXMOD |= Reg_Data;
    }
    else
    {
      TXMOD &= ~Reg_Data;
    }
  }
}

/**************************************************
*��������:void PWM_PolarityConfig(PWM_OutputPin_TypeDef PWM_OutputPin, PWM_Polarity_TypeDef PWM_Polarity)
*��������:PWMx��/����������ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMxѡ��uint8_t��Ϊ��Σ��������λ�������
PWM_Polarity_TypeDef:PWM_Polarity:PWM�����/��������
*���ڲ���:void
**************************************************/
void PWM_PolarityConfig(uint8_t PWM_OutputPin,
                        PWM_Polarity_TypeDef PWM_Polarity)
{
  unsigned char Reg_Data;
  if((PWM_OutputPin & 0xF0) == 0x00)
  {
    if(PWM_Polarity == PWM_POLARITY_INVERT)
    {
      PWMCFG |= 1 << ((PWM_OutputPin >> 1) & 0x0F);
    }
    else
    {
      PWMCFG &= ~(1 << ((PWM_OutputPin >> 1) & 0x0F));
    }
  }
  else
  {
    TXINX = (PWM_OutputPin & 0xF0) >> 4;

    if(PWM_OutputPin & 0x02)
    {
      Reg_Data = 0x08;
    }
    else
    {
      Reg_Data = 0x04;
    }

    if(PWM_Polarity == PWM_POLARITY_INVERT)
    {
      TXMOD |= Reg_Data;
    }
    else
    {
      TXMOD &= ~Reg_Data;
    }
  }
}

/**************************************************
*��������:void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle)
*��������:PWMx��������ģʽ���ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMx����ͨ��ѡ��
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
*���ڲ���:void
**************************************************/
void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle)
{
  if((PWM_OutputPin & 0xF0) == 0x00)
  {
    PWMCON0 &= ~0x02;
    PWMREG[12 + PWM_OutputPin] = PWM_DutyCycle >> 8;
    PWMREG[13 + PWM_OutputPin] = PWM_DutyCycle;
  }
  else
  {
    PWMREG[PWM_OutputPin & 0x0F] = PWM_DutyCycle >> 8;
    PWMREG[1 + PWM_OutputPin & 0x0F] = PWM_DutyCycle;
  }
}

/**************************************************
*��������:void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin, uint16_t PWM_DutyCycle)
*��������:PWMxPWMy��������ģʽ���ú���
*��ڲ���:
PWM_ComplementaryOutputPin_TypeDef:PWM_ComplementaryOutputPin:PWMxPWMy����ͨ��ѡ��
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
*���ڲ���:void
**************************************************/
void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin,
                                 uint16_t PWM_DutyCycle)
{
  PWMCON0 |= 0x02;
  PWMREG[13 + PWM_ComplementaryOutputPin] = PWM_DutyCycle;
  PWMREG[12 + PWM_ComplementaryOutputPin] = PWM_DutyCycle >> 8;
}

/**************************************************
*��������:PWM_DeadTimeConfigEX(PWM_Type_TypeDef PWM_Type,uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
*��������:PWM��������ģʽ������ʱ�����ú���
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWMԴѡ��
uint8_t:PWM_RisingDeadTime:PWM��������ʱ��	 00-FF
uint8_t:PWM_FallingDeadTime:PWM�����½�ʱ��  00-FF
*���ڲ���:void
**************************************************/
void PWM_DeadTimeConfigEX(PWM_Type_TypeDef PWM_Type, uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
{
  if(PWM_Type == PWM0_Type)
  {
    PWMDFR = (PWM_RisingDeadTime | (PWM_FallingDeadTime << 4));
  }
}

/*****************************************************
*��������:void PWM_Cmd(PWM_Type_TypeDef PWM_Type,FunctionalState NewState)
*��������:PWM���ܿ��غ���
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_CmdEX(PWM_Type_TypeDef PWM_Type,
               FunctionalState NewState)
{
  if(PWM_Type == PWM0_Type)
  {
    if(NewState != DISABLE)
    {
      PWMCON0 |= 0X80;
    }
    else
    {
      PWMCON0 &= 0X7F;
    }
  }
  else
  {
    TXINX = PWM_Type;
    if(NewState != DISABLE)
    {
      TXCON |= 0X04;
    }
    else
    {
      TXCON &= ~0X04;
    }
  }
}

/*****************************************************
*��������:void PWM_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:PWM�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_ITConfig(FunctionalState NewState,
                  PriorityStatus Priority)
{
  if(NewState != DISABLE)
  {
    IE1 |= 0X02;
  }
  else
  {
    IE1 &= 0XFD;
  }

  if(Priority == LOW)
  {
    IP1 &= ~0X02;
  }
  else
  {
    IP1 |= 0X02;
  }
}

/*****************************************************
*��������:void PWM_IndependentModeConfigEX(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle, PWM_OutputState_TypeDef PWM_OutputState)
*��������:PWM����ģʽ����
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_ComplementaryOutputPin:PWMͨ��
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_IndependentModeConfigEX(PWM_OutputPin_TypeDef PWM_ComplementaryOutputPin,
                                 uint16_t PWM_DutyCycle,
                                 PWM_OutputState_TypeDef PWM_OutputState)
{
  PWM_IndependentModeConfig(PWM_ComplementaryOutputPin, PWM_DutyCycle); //����ռ�ձ�
  PWM_OutputStateConfig(PWM_ComplementaryOutputPin, PWM_OutputState);   //IO����PWM���ú���
  if(PWM_OutputState == ENABLE)
  {
    PWM_CmdEX(PWM_ComplementaryOutputPin >> 4, ENABLE); //����PWM
  }
}

/*****************************************************
*��������:void PWM_ComplementaryModeConfigEX(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle, PWM_OutputState_TypeDef PWM_OutputState)
*��������:PWM����
*��ڲ���:
PWM_ComplementaryOutputPin_TypeDef:PWM_OutputPin:PWMͨ��
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_ComplementaryModeConfigEX(PWM_ComplementaryOutputPin_TypeDef PWM_OutputPin,
                                   uint16_t PWM_DutyCycle,
                                   PWM_OutputState_TypeDef PWM_OutputState)
{
  PWM_ComplementaryModeConfig(PWM_OutputPin, PWM_DutyCycle); //����ռ�ձ�
  PWM_OutputStateConfig(PWM_OutputPin, PWM_OutputState);     //IO����PWM���ú���
  PWM_OutputStateConfig(PWM_OutputPin + 2, PWM_OutputState); //IO����PWM���ú���
  if(PWM_OutputState == ENABLE)
  {
    PWM_CmdEX(PWM_OutputPin >> 4, ENABLE); //����PWM
  }
}

/*****************************************************
*��������:PWM_GetFlagStatusEX(PWM_Type_TypeDef PWM_Type)
*��������:��ȡPWM�жϱ�־λ
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWMԴѡ��
*���ڲ���:void
*****************************************************/
FlagStatus PWM_GetFlagStatusEX(PWM_Type_TypeDef PWM_Type)
{
  if((PWM_Type == PWM0_Type))
  {
    return (bool)(PWMCON0 & 0X40);
  }
#if defined (SC95R751)
  else if(PWM_Type == PWM3_Type)
  {
    TXINX = PWM_Type;
    return (bool)(TXCON & 0x80);
  }
#elif defined (SC95F7610B) || defined (SC95F7619B)
  else if((PWM_Type == PWM2_Type) || (PWM_Type == PWM3_Type))
  {
    TXINX = PWM_Type;
    return (bool)(TXCON & 0x80);
  }
#else
  else if((PWM_Type == PWM2_Type) || (PWM_Type == PWM3_Type) || (PWM_Type == PWM0_Type))
  {
    TXINX = PWM_Type;
    return (bool)(TXCON & 0x80);
  }
#endif

  return RESET;
}

/*****************************************************
*��������:void PWM_ClearFlagEX(PWM_Type_TypeDef PWM_Type)
*��������:���PWM�ж�
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWMԴѡ��
*���ڲ���:void
*****************************************************/
void PWM_ClearFlagEX(PWM_Type_TypeDef PWM_Type)
{
  if((PWM_Type == PWM0_Type))
  {
    PWMCON0 &= ~0X40;
  }

#if  defined (SC95R751)
  else if(PWM_Type == PWM3_Type)
  {
    TXINX = PWM_Type;
    TXCON &= ~0x80;
  }
#elif defined (SC95F7610B) || defined (SC95F7619B)
  else if((PWM_Type == PWM2_Type) || (PWM_Type == PWM3_Type))
  {
    TXINX = PWM_Type;
    TXCON &= ~0x80;
  }
#else
  else if((PWM_Type == PWM2_Type) || (PWM_Type == PWM3_Type) || (PWM_Type == PWM0_Type))
  {
    TXINX = PWM_Type;
    TXCON &= ~0x80;
  }
#endif
}

#if !defined (SC95F7610B) && !defined (SC95F7619B)
/*****************************************************
*��������:FlagStatus PWM_GetFaultDetectionFlagStatus(void)
*��������:���PWM���ϼ���־λ״̬
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����
*���ڲ���:
FlagStatus:PWM���ϼ���־λ״̬
*****************************************************/
FlagStatus PWM_GetFaultDetectionFlagStatusEX(PWM_Type_TypeDef PWM_Type)
{
  if(PWM_Type == PWM0_Type)
  {
    return (bool)(PWMFLT & 0X40);
  }

  return RESET;
}

/*****************************************************
*��������:void PWM_ClearFaultDetectionFlag(void)
*��������:���PWM���ϼ���־λ״̬   // ��ע��,��������ģʽ�£���λ��������
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����
*���ڲ���:void
*****************************************************/
void PWM_ClearFaultDetectionFlagEX(PWM_Type_TypeDef PWM_Type)
{
  if(PWM_Type == PWM0_Type)
  {
    PWMFLT &= 0XBF;
  }
}

/*****************************************************
*��������:void PWM_FaultDetectionFunctionConfigEX(PWM_Type_TypeDef PWM_Type, FunctionalState NewState)
*��������:PWM���ϼ�⹦�ܿ���/�ر�-��չ��
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����ѡ��
FunctionalState:NewState:���ϼ�⹦�ܿ���/�ر�
*���ڲ���:void
*****************************************************/
void PWM_FaultDetectionConfigEX(PWM_Type_TypeDef PWM_Type, FunctionalState NewState)
{
  if(PWM_Type == PWM0_Type)
  {
    if(NewState != DISABLE)
    {
      PWMFLT |= 0X80;
    }
    else
    {
      PWMFLT &= 0X7F;
    }
  }
}

/*****************************************************
*��������:void PWM_FaultDetectionModeConfigEX(PWM_Type_TypeDef PWM_Type, PWM_FaultDetectionMode_TypeDef FaultDetectionMode, PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect, PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
*��������:PWM���ϼ��ģʽ����
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����ѡ��
PWM_FaultDetectionMode_TypeDef:FaultDetectionMode:���ϼ�⹦��ģʽ����: ����ģʽ/����ģʽ
PWM_FaultDetectionVoltageSelect_TypeDef:FaultDetectionVoltageSelect:���ϼ���ƽѡ��
PWM_FaultDetectionWaveFilteringTime_TypeDef:FaultDetectionWaveFilteringTime:���ϼ�������ź��˲�ʱ��ѡ��
*���ڲ���:void
*****************************************************/
void PWM_FaultDetectionModeConfigEX(PWM_Type_TypeDef PWM_Type,
                                    PWM_FaultDetectionMode_TypeDef FaultDetectionMode,
                                    PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect,
                                    PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
{
  if(PWM_Type == PWM0_Type)
  {
    PWMFLT = (PWMFLT & 0XC0) | FaultDetectionMode | FaultDetectionVoltageSelect |
             FaultDetectionWaveFilteringTime;
  }
}
#endif

/*****************************************************
*��������:void PWM_ITConfigEX(PWM_Type_TypeDef PWM_Type,FunctionalState NewState, PriorityStatus Priority)
*��������:PWM�ж����ú���-��չ��
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWMԴѡ��
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_ITConfigEX(PWM_Type_TypeDef PWM_Type, FunctionalState NewState, PriorityStatus Priority)
{

  if((PWM_Type == PWM0_Type))
  {
    PWM_ITConfig(NewState, Priority);
  }
  else
  {
    TXINX = PWM_Type;

    if(NewState == DISABLE)
    {
      ET2 = 0;
    }
    else
    {
      ET2 = 1;
    }

    if(Priority == LOW)
    {
      IPT2 = 0;
    }
    else
    {
      IPT2 = 1;
    }
  }
}

#endif
/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/