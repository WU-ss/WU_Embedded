//************************************************************
//  Copyright (c) 
//	文件名称: 			sc95f_pwm.c
//	作者:
//	模块功能: 			PWM固件库函数C文件
//  最后更正日期:	2022年7月22日
// 	版本: 				V1.10010
//  说明:					该文件仅适用于SC95F系列芯片
//*************************************************************

#include "sc95f_pwm.h"
//PWM2/3/4与TIM2/3/4共用寄存器
#include "sc95f_timer2.h"
#include "sc95f_timer3.h"
#include "sc95f_timer4.h"

#if defined(SC95F8x1x) || defined(SC95F7x1x)
uint16_t xdata PWMREG[8] _at_ 0x1040;              //PWM占空比调节寄存器
uint16_t pwm_tmpreg[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //PWM占空比调节寄存器缓存数组

/**************************************************
*函数名称:void PWM_DeInit(void)
*函数功能:PWM相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
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
*函数名称:void PWM_Init(PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
*函数功能:PWM初始化配置函数
*入口参数:
PWM_PresSel_TypeDef:PWM_PresSel:预分频选择
uint16_t:PWM_Period:PWM周期配置
*出口参数:void
**************************************************/
void PWM_Init(PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
{
  PWM_Period -= 1;
  PWMCFG = (PWMCFG & 0XCF) | PWM_PresSel;                 //预分频
  PWMCFG = (PWMCFG & 0XF0) | (uint8_t)(PWM_Period / 256); //周期高4位
  PWMCON = (uint8_t)(PWM_Period & 0X00FF);                //周期低8位
}

/**************************************************
*函数名称:void PWM_OutputStateConfig(uint8_t PWM_OutputPin, PWM_OutputState_TypeDef PWM_OutputState)
*函数功能:PWMx输出使能/失能配置函数
*入口参数:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMx选择（uint8_t作为入参，方便进行位或操作）
PWM_OutputState_TypeDef:PWM_OutputState:PWM输出状态配置
*出口参数:void
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
*函数名称:void PWM_PolarityConfig(uint8_t PWM_OutputPin, PWM_Polarity_TypeDef PWM_Polarity)
*函数功能:PWMx正/反向输出配置函数
*入口参数:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMx选择（uint8_t作为入参，方便进行位或操作）
PWM_Polarity_TypeDef:PWM_Polarity:PWM输出正/反向配置
*出口参数:void
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
*函数名称:void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle)
*函数功能:PWMx独立工作模式配置函数
*入口参数:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMx独立通道选择
uint16_t:PWM_DutyCycle:PWM占空比配置
*出口参数:void
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
*函数名称:void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin, uint16_t PWM_DutyCycle)
*函数功能:PWMxPWMy互补工作模式配置函数
*入口参数:
PWM_ComplementaryOutputPin_TypeDef:PWM_ComplementaryOutputPin:PWMxPWMy互补通道选择
uint16_t:PWM_DutyCycle:PWM占空比配置
*出口参数:void
**************************************************/
void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin,
                                 uint16_t PWM_DutyCycle)
{
  PWMCON = 0X08;

  switch(PWM_ComplementaryOutputPin)  //设置占空比
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
*函数名称:void PWM_DeadTimeConfig(uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
*函数功能:PWM互补工作模式下死区时间配置函数
*入口参数:
uint8_t:PWM_RisingDeadTime:PWM死区上升时间00-FF
uint8_t:PWM_FallingDeadTime:PWM死区下降时间00-FF
*出口参数:void
**************************************************/
void PWM_DeadTimeConfig(uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
{
  PWMDFR = (PWM_RisingDeadTime | (PWM_FallingDeadTime << 4));
}

/*****************************************************
*函数名称:void PWM_Cmd(FunctionalState NewState)
*函数功能:PWM功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
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
*函数名称:void PWM_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:PWM中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
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
*函数名称:FlagStatus PWM_GetFlagStatus(void)
*函数功能:获得PWM中断标志状态
*入口参数:void
*出口参数:
FlagStatus:PWM中断标志状态
*****************************************************/
FlagStatus PWM_GetFlagStatus(void)
{
  return (bool)(PWMCFG & 0X40);
}

/*****************************************************
*函数名称:void PWM_ClearFlag(void)
*函数功能:清除PWM中断标志状态
*入口参数:void
*出口参数:void
*****************************************************/
void PWM_ClearFlag(void)
{
  PWMCFG &= 0XBF;
}

/*****************************************************
*函数名称:FlagStatus PWM_GetFaultDetectionFlagStatus(void)
*函数功能:获得PWM故障检测标志位状态
*入口参数:void
*出口参数:
FlagStatus:PWM故障检测标志位状态
*****************************************************/
FlagStatus PWM_GetFaultDetectionFlagStatus(void)
{
  return (bool)(PWMFLT & 0X40);
}

/*****************************************************
*函数名称:void PWM_ClearFaultDetectionFlag(void)
*函数功能:清除PWM故障检测标志位状态   // ！注意,处于锁存模式下，此位可软件清除
*入口参数:void
*出口参数:void
*****************************************************/
void PWM_ClearFaultDetectionFlag(void)
{
  PWMFLT &= 0XBF;
}

/*****************************************************
*函数名称:void PWM_FaultDetectionFunctionConfig(FunctionalState NewState)
*函数功能:PWM故障检测功能开启/关闭
*入口参数:
FunctionalState:NewState:故障检测功能开启/关闭
*出口参数:void
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
*函数名称:void PWM_FaultDetectionModeConfig(PWM_FaultDetectionMode_TypeDef FaultDetectionMode, PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect, PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
*函数功能:PWM故障检测模式设置
*入口参数:
PWM_FaultDetectionMode_TypeDef:FaultDetectionMode:故障检测功能模式设置:立即模式/锁存模式
PWM_FaultDetectionVoltageSelect_TypeDef:FaultDetectionVoltageSelect:故障检测电平选择
PWM_FaultDetectionWaveFilteringTime_TypeDef:FaultDetectionWaveFilteringTime:故障检测输入信号滤波时间选择
*出口参数:void
*****************************************************/
void PWM_FaultDetectionModeConfig(PWM_FaultDetectionMode_TypeDef FaultDetectionMode,
                                  PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect,
                                  PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
{
  PWMFLT = (PWMFLT & 0XC0) | FaultDetectionMode | FaultDetectionVoltageSelect |
           FaultDetectionWaveFilteringTime;
}

/*****************************************************
*函数名称:void PWM_Aligned_Mode_Select(void)
*函数功能:选择PWM的对齐模式
*入口参数:
PWM_Aligned_Mode_TypeDef:PWM_Aligned_Mode:选择对齐模式
*出口参数:void
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
*函数名称:void PWM_DeInit(void)
*函数功能:PWM相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
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
*函数名称:void PWM_Init(PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
*函数功能:PWM初始化配置函数
*入口参数:
PWM_PresSel_TypeDef:PWM_PresSel:预分频选择
uint16_t:PWM_Period:PWM周期配置
*出口参数:void
**************************************************/
void PWM_Init(PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
{
  PWM_Period -= 1;
  PWMCON0 &= 0XCF;
  PWMCON0 |= PWM_PresSel;    //预分频
  PWMPDL = PWM_Period;       //周期低八位
  PWMPDH = PWM_Period / 256; //周期高八位
}

/**************************************************
*函数名称:void PWM_OutputStateConfig(uint8_t PWM_OutputPin, PWM_OutputState_TypeDef PWM_OutputState)
*函数功能:PWMx输出使能/失能配置函数
*入口参数:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMx选择（uint8_t作为入参，方便进行位或操作）
PWM_OutputState_TypeDef:PWM_OutputState:PWM输出状态配置
*出口参数:void
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
*函数名称:void PWM_PolarityConfig(uint8_t PWM_OutputPin, PWM_Polarity_TypeDef PWM_Polarity)
*函数功能:PWMx正/反向输出配置函数
*入口参数:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMx选择（uint8_t作为入参，方便进行位或操作）
PWM_Polarity_TypeDef:PWM_Polarity:PWM输出正/反向配置
*出口参数:void
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
*函数名称:void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle)
*函数功能:PWMx独立工作模式配置函数
*入口参数:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMx独立通道选择
uint16_t:PWM_DutyCycle:PWM占空比配置
*出口参数:void
**************************************************/
void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle)
{
  PWMCON0 &= 0XFD; //设置PWM为独立模式

  switch(PWM_OutputPin)  //设置占空比
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
*函数名称:void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin, uint16_t PWM_DutyCycle)
*函数功能:PWMxPWMy互补工作模式配置函数
*入口参数:
PWM_ComplementaryOutputPin_TypeDef:PWM_ComplementaryOutputPin:PWMxPWMy互补通道选择
uint16_t:PWM_DutyCycle:PWM占空比配置
*出口参数:void
**************************************************/
void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin,
                                 uint16_t PWM_DutyCycle)
{
  PWMCON0 |= 0X02; //设置PWM为互补模式

  switch(PWM_ComplementaryOutputPin)  //设置占空比
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
*函数名称:void PWM_DeadTimeConfig(uint8_t PWM_RisingDeadTime, uint8_t PWM_fallingDeadTime)
*函数功能:PWM互补工作模式下死区时间配置函数
*入口参数:
uint8_t:PWM_RisingDeadTime:PWM死区上升时间
uint8_t:PWM_fallingDeadTime:PWM死区下降时间
*出口参数:void
**************************************************/
void PWM_DeadTimeConfig(uint8_t PWM_RisingDeadTime, uint8_t PWM_fallingDeadTime)
{
  PWMDFR = (PWM_RisingDeadTime | (PWM_fallingDeadTime << 4));
}

/*****************************************************
*函数名称:void PWM_Cmd(FunctionalState NewState)
*函数功能:PWM功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
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
*函数名称:void PWM_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:PWM中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
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
*函数名称:FlagStatus PWM_GetFlagStatus(void)
*函数功能:获得PWM中断标志状态
*入口参数:void
*出口参数:
FlagStatus:PWM中断标志状态
*****************************************************/
FlagStatus PWM_GetFlagStatus(void)
{
  return (bool)(PWMCON0 & 0X40);
}

/*****************************************************
*函数名称:void PWM_ClearFlag(void)
*函数功能:清除PWM中断标志状态
*入口参数:void
*出口参数:void
*****************************************************/
void PWM_ClearFlag(void)
{
  PWMCON0 &= 0XBF;
}
/*****************************************************
*函数名称:void PWM_Aligned_Mode_Select(void)
*函数功能:选择PWM的对齐模式
*入口参数:
PWM_Aligned_Mode_TypeDef:PWM_Aligned_Mode:选择对齐模式
*出口参数:void
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
*函数名称:FlagStatus PWM_GetFaultDetectionFlagStatus(void)
*函数功能:获得PWM故障检测标志位状态
*入口参数:void
*出口参数:
FlagStatus:PWM故障检测标志位状态
*****************************************************/
FlagStatus PWM_GetFaultDetectionFlagStatus(void)
{
  return (bool)(PWMFLT & 0X40);
}

/*****************************************************
*函数名称:void PWM_ClearFaultDetectionFlag(void)
*函数功能:清除PWM故障检测标志位状态   // ！注意,处于锁存模式下，此位可软件清除
*入口参数:void
*出口参数:void
*****************************************************/
void PWM_ClearFaultDetectionFlag(void)
{
  PWMFLT &= 0XBF;
}

/*****************************************************
*函数名称:void PWM_FaultDetectionFunctionConfig(FunctionalState NewState)
*函数功能:PWM故障检测功能开启/关闭
*入口参数:
FunctionalState:NewState:故障检测功能开启/关闭
*出口参数:void
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
*函数名称:void PWM_FaultDetectionModeConfig(PWM_FaultDetectionMode_TypeDef FaultDetectionMode, PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect, PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
*函数功能:PWM故障检测模式设置
*入口参数:
PWM_FaultDetectionMode_TypeDef:FaultDetectionMode:故障检测功能模式设置:立即模式/锁存模式
PWM_FaultDetectionVoltageSelect_TypeDef:FaultDetectionVoltageSelect:故障检测电平选择
PWM_FaultDetectionWaveFilteringTime_TypeDef:FaultDetectionWaveFilteringTime:故障检测输入信号滤波时间选择
*出口参数:void
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
uint8_t xdata PWMREG[80] _at_ 0x1000; //PWM占空比调节寄存器
/**************************************************
*函数名称:void PWM_DeInit(void)
*函数功能:PWM相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
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
*函数名称:PWM_Init(PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
*函数功能:PWM初始化配置函数
*入口参数:
PWM_PresSel_TypeDef:PWM_PresSel:预分频选择
uint16_t:PWM_Period:PWM周期配置
*出口参数:void
**************************************************/
void PWM_Init(PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
{
  if((PWM_PresSel & 0X0F) == PWM0_Type)
  {
    PWM_Period -= 1;
    PWMCFG0 = (PWMCON0 & 0XCF) | (PWM_PresSel & 0XF0);        //预分频
    PWMCFG0 = (PWMCON0 & 0XF0) | (uint8_t)(PWM_Period / 256); //周期高4位
    PWMCON0 = (uint8_t)(PWM_Period & 0X00FF);                 //周期低8位
  }
  else if((PWM_PresSel & 0X0F) == PWM1_Type)
  {
    PWM_Period -= 1;
    PWMCFG1 = (PWMCFG1 & 0XCF) | (PWM_PresSel & 0XF0);        //预分频
    PWMCFG1 = (PWMCFG1 & 0XF0) | (uint8_t)(PWM_Period / 256); //周期高4位
    PWMCON1 = (uint8_t)PWM_Period;                            //周期低8位
  }
}

/*****************************************************
*函数名称:void PWM_Aligned_Mode_Select(void)
*函数功能:选择PWM的对齐模式
*入口参数:
PWM_Aligned_Mode_TypeDef:PWM_Aligned_Mode:选择对齐模式
*出口参数:void
*****************************************************/
void PWM_Aligned_Mode_Select(PWM_Aligned_Mode_TypeDef PWM_Aligned_Mode)
{

  //PWM0选择对齐模式配置
  if(PWM_Aligned_Mode == PWM0_Edge_Aligned_Mode)
  {
    PWMMOD &= 0XFE;
  }
  else if(PWM_Aligned_Mode == PWM0_Center_Alignment_Mode)
  {
    PWMMOD |= 0X01;
  }
  //PWM1选择对齐模式配置
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
*函数名称:void PWM_OutputStateConfig(uint8_t PWM_OutputPin, PWM_OutputState_TypeDef PWM_OutputState)
*函数功能:PWMx输出使能/失能配置函数
*入口参数:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMx选择（uint8_t作为入参，方便进行位或操作）
PWM_OutputState_TypeDef:PWM_OutputState:PWM输出状态配置
*出口参数:void
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
*函数名称:void PWM_PolarityConfig(PWM_OutputPin_TypeDef PWM_OutputPin, PWM_Polarity_TypeDef PWM_Polarity)
*函数功能:PWMx正/反向输出配置函数
*入口参数:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMx选择（uint8_t作为入参，方便进行位或操作）
PWM_Polarity_TypeDef:PWM_Polarity:PWM输出正/反向配置
*出口参数:void
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
*函数名称:void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle)
*函数功能:PWMx独立工作模式配置函数
*入口参数:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMx独立通道选择（uint8_t作为入参，方便进行位或操作）
uint16_t:PWM_DutyCycle:PWM占空比配置
*出口参数:void
**************************************************/
void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle)
{
  PWMREG[PWM_OutputPin + 1] = PWM_DutyCycle;
  PWMREG[PWM_OutputPin] = (PWMREG[PWM_OutputPin] & 0xF0) | (PWM_DutyCycle / 256);
}

/**************************************************
*函数名称:void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin, uint16_t PWM_DutyCycle)
*函数功能:PWMxPWMy互补工作模式配置函数
*入口参数:
PWM_ComplementaryOutputPin_TypeDef:PWM_ComplementaryOutputPin:PWMxPWMy互补通道选择
uint16_t:PWM_DutyCycle:PWM占空比配置
*出口参数:void
**************************************************/
void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin,
                                 uint16_t PWM_DutyCycle)
{
  PWMMOD |= 0X08;
  PWMREG[PWM40 + PWM_ComplementaryOutputPin * 2 + 1] = PWM_DutyCycle;
  PWMREG[PWM40 + PWM_ComplementaryOutputPin * 2] = (PWMREG[PWM40 + PWM_ComplementaryOutputPin * 2] & 0xF0) | (PWM_DutyCycle / 256);
}

/**************************************************
*函数名称:void PWM_DeadTimeConfig(uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
*函数功能:PWM互补工作模式下死区时间配置函数
*入口参数:
uint8_t:PWM_RisingDeadTime:PWM死区上升时间	 00-FF
uint8_t:PWM_FallingDeadTime:PWM死区下降时间  00-FF
*出口参数:void
**************************************************/
void PWM_DeadTimeConfig(uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
{
  PWMDFR1 = (PWM_RisingDeadTime | (PWM_FallingDeadTime << 4));
}

/**************************************************
*函数名称:void PWM_DeadTimeConfigEX(PWM_Type_TypeDef PWM_Type, uint8_t PWM_RisingDeadTime, uint8_t PWM_fallingDeadTime)
*函数功能:PWM互补工作模式下死区时间配置函数
*入口参数:
PWM_Type_TypeDef:PWM_Type:PWM类型选择
uint8_t:PWM_RisingDeadTime:PWM死区上升时间	 00-FF
uint8_t:PWM_FallingDeadTime:PWM死区下降时间  00-FF
*出口参数:void
**************************************************/
void PWM_DeadTimeConfigEX(PWM_Type_TypeDef PWM_Type, uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
{
  if(PWM_Type == PWM1_Type)
  {
    PWMDFR1 = (PWM_RisingDeadTime | (PWM_FallingDeadTime << 4));
  }
}

/*****************************************************
*函数名称:void PWM_Cmd(PWM_Type_TypeDef PWM_Type,FunctionalState NewState)
*函数功能:PWM功能开关函数
*入口参数:
PWM_Type_TypeDef:PWM_Type:PWM类型
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
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
*函数名称:void PWM_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:PWM中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
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
*函数名称:FlagStatus PWM_GetFlagStatusEX(PWM_Type_TypeDef
                               PWM_Type)
*函数功能:获得PWM中断标志状态，多通道
*入口参数:
PWM_Type_TypeDef:PWM_Type:PWM类型
*出口参数:
FlagStatus:PWM中断标志状态
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
*函数名称:void PWM1_ClearFlag(void)
*函数功能:清除PWM中断标志状态
*入口参数:
PWM_Type_TypeDef:PWM_Type:PWM类型
*出口参数:void
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
*函数名称:void PWM_IndependentModeConfigEX(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle, PWM_OutputState_TypeDef PWM_OutputState)
*函数功能:配置独立模式占空比，并且选择是否开启通道
*入口参数:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWM通道
uint16_t:PWM_DutyCycle PWM占空比配置
PWM_OutputState_TypeDef:PWM_OutputState:功能启动/关闭选择
*出口参数:void
*****************************************************/
void PWM_IndependentModeConfigEX(PWM_OutputPin_TypeDef PWM_OutputPin,
                                 uint16_t PWM_DutyCycle,
                                 PWM_OutputState_TypeDef PWM_OutputState)
{
  if(PWM_OutputState == ENABLE)
  {
    if(PWM_OutputPin >= PWM40)  //如果属于PWM1，切换为独立模式
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
*函数名称:void PWM_ComplementaryModeConfigEX(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle, PWM_OutputState_TypeDef PWM_OutputState)
*函数功能:配置PWM互补模式占空比，并选择是否开启通道
*入口参数:
PWM_ComplementaryOutputPin_TypeDef:PWM_ComplementaryOutputPin:PWM通道
uint16_t:PWM_DutyCycle:PWM占空比配置
PWM_OutputState_TypeDef:PWM_OutputState:功能启动/关闭选择
*出口参数:void
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
*函数名称:FlagStatus PWM_GetFaultDetectionFlagStatus(void)
*函数功能:获得可选PWM源故障检测标志位状态
*入口参数:void
*出口参数:
FlagStatus:PWM故障检测标志位状态
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
*函数名称:void PWM_ClearFaultDetectionFlag(void)
*函数功能:清除可选PWM源故障检测标志位状态   // ！注意,处于锁存模式下，此位可软件清除
*入口参数:void
*出口参数:void
*****************************************************/
void PWM_ClearFaultDetectionFlagEX(PWM_Type_TypeDef PWM_Type)
{
  if(PWM_Type == PWM1_Type)
  {
    PWMFLT1 &= 0XBF;
  }
}

/*****************************************************
*函数名称:void PWM_FaultDetectionFunctionConfig(FunctionalState NewState)
*函数功能:PWM故障检测功能开启/关闭
*入口参数:
FunctionalState:NewState:故障检测功能开启/关闭
*出口参数:void
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
*函数名称:void PWM_FaultDetectionModeConfigEX(PWM_Type_TypeDef PWM_Type, PWM_FaultDetectionMode_TypeDef FaultDetectionMode, PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect, PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
*函数功能:PWM故障检测模式设置
*入口参数:
PWM_Type_TypeDef:PWM_Type:PWM类型选择
PWM_FaultDetectionMode_TypeDef:FaultDetectionMode:故障检测功能模式设置: 立即模式/锁存模式
PWM_FaultDetectionVoltageSelect_TypeDef:FaultDetectionVoltageSelect:故障检测电平选择
PWM_FaultDetectionWaveFilteringTime_TypeDef:FaultDetectionWaveFilteringTime:故障检测输入信号滤波时间选择
*出口参数:void
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
uint8_t xdata PWMREG[28] _at_ 0x2034; //PWM占空比调节寄存器
/**************************************************
*函数名称:void PWM_DeInit(void)
*函数功能:PWM相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
**************************************************/
void PWM_DeInit(void)
{
  static uint8_t i;

  //PWM0相关寄存器清零
  PWMCON0 = 0X00;
  PWMCFG = 0X00;
  PWMCON1 = 0X00;
  PWMPDL = 0x00;
  PWMPDH = 0x00;
  IE1 &= 0XFD;
  IP1 &= 0XFD;

  //PWM2/3/4相关寄存器
  for(i = 0; i < 3; i++)
  {
    TXINX = 0x02 + i;
    TXCON &= ~0x04;
    TXMOD &= ~0x3C;
    RCAPXH = 0x00;
    RCAPXL = 0x00;
  }

  //清零中断使能位和优先级位
  ET2 = 0;
  IP &= ~0x20;
  IE1 &= ~0xC0;
  IP1 &= ~0xC0;

  //占空比寄存器
  for(i = 0; i < 14; i++)
  {
    PWMREG[i] = 0;
  }
}

/**************************************************
*函数名称:PWM_Init(PWM_Type_TypeDef PWM_Type,PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
*函数功能:PWM初始化配置函数
*入口参数:
PWM_PresSel_TypeDef:PWM_PresSel:预分频选择
uint16_t:PWM_Period:PWM周期配置
*出口参数:void
**************************************************/
void PWM_Init(PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
{
  if((PWM_PresSel & 0X0F) == PWM0_Type)
  {
    PWM_Period -= 1;
    PWMCON0 = (PWMCON0 & 0XCF) | (PWM_PresSel & 0XF0); //预分频
    PWMPDH = (uint8_t)(PWM_Period >> 8);               //周期高8位
    PWMPDL = (uint8_t)(PWM_Period & 0X00FF);           //周期低8位
  }
  else
  {
    TXINX = (PWM_PresSel & 0X0F);
    PWM_PresSel = DISABLE;                   //PWM2分频唯一，不用设置
    RCAPXH = (uint8_t)(PWM_Period >> 8);     //周期高8位
    RCAPXL = (uint8_t)(PWM_Period & 0X00FF); //周期低8位
  }
}

/*****************************************************
*函数名称:void PWM_Aligned_Mode_Select(void)
*函数功能:选择PWM的对齐模式
*入口参数:
PWM_Aligned_Mode_TypeDef:PWM_Aligned_Mode:选择对齐模式
*出口参数:void
*****************************************************/
void PWM_Aligned_Mode_Select(PWM_Aligned_Mode_TypeDef PWM_Aligned_Mode)
{

  //PWM0选择对齐模式配置
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
*函数名称:void PWM_OutputStateConfig(uint8_t PWM_OutputPin, PWM_OutputState_TypeDef PWM_OutputState)
*函数功能:PWMx输出使能/失能配置函数
*入口参数:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMx选择（uint8_t作为入参，方便进行位或操作）
PWM_OutputState_TypeDef:PWM_OutputState:PWM输出状态配置
*出口参数:void
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
*函数名称:void PWM_PolarityConfig(PWM_OutputPin_TypeDef PWM_OutputPin, PWM_Polarity_TypeDef PWM_Polarity)
*函数功能:PWMx正/反向输出配置函数
*入口参数:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMx选择（uint8_t作为入参，方便进行位或操作）
PWM_Polarity_TypeDef:PWM_Polarity:PWM输出正/反向配置
*出口参数:void
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
*函数名称:void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle)
*函数功能:PWMx独立工作模式配置函数
*入口参数:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMx独立通道选择
uint16_t:PWM_DutyCycle:PWM占空比配置
*出口参数:void
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
*函数名称:void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin, uint16_t PWM_DutyCycle)
*函数功能:PWMxPWMy互补工作模式配置函数
*入口参数:
PWM_ComplementaryOutputPin_TypeDef:PWM_ComplementaryOutputPin:PWMxPWMy互补通道选择
uint16_t:PWM_DutyCycle:PWM占空比配置
*出口参数:void
**************************************************/
void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin,
                                 uint16_t PWM_DutyCycle)
{
  PWMCON0 |= 0x02;
  PWMREG[13 + PWM_ComplementaryOutputPin] = PWM_DutyCycle;
  PWMREG[12 + PWM_ComplementaryOutputPin] = PWM_DutyCycle >> 8;
}

/**************************************************
*函数名称:PWM_DeadTimeConfigEX(PWM_Type_TypeDef PWM_Type,uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
*函数功能:PWM互补工作模式下死区时间配置函数
*入口参数:
PWM_Type_TypeDef:PWM_Type:PWM源选择
uint8_t:PWM_RisingDeadTime:PWM死区上升时间	 00-FF
uint8_t:PWM_FallingDeadTime:PWM死区下降时间  00-FF
*出口参数:void
**************************************************/
void PWM_DeadTimeConfigEX(PWM_Type_TypeDef PWM_Type, uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
{
  if(PWM_Type == PWM0_Type)
  {
    PWMDFR = (PWM_RisingDeadTime | (PWM_FallingDeadTime << 4));
  }
}

/*****************************************************
*函数名称:void PWM_Cmd(PWM_Type_TypeDef PWM_Type,FunctionalState NewState)
*函数功能:PWM功能开关函数
*入口参数:
PWM_Type_TypeDef:PWM_Type:PWM类型
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
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
*函数名称:void PWM_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:PWM中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
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
*函数名称:void PWM_IndependentModeConfigEX(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle, PWM_OutputState_TypeDef PWM_OutputState)
*函数功能:PWM独立模式配置
*入口参数:
PWM_OutputPin_TypeDef:PWM_ComplementaryOutputPin:PWM通道
uint16_t:PWM_DutyCycle:PWM占空比配置
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
*****************************************************/
void PWM_IndependentModeConfigEX(PWM_OutputPin_TypeDef PWM_ComplementaryOutputPin,
                                 uint16_t PWM_DutyCycle,
                                 PWM_OutputState_TypeDef PWM_OutputState)
{
  PWM_IndependentModeConfig(PWM_ComplementaryOutputPin, PWM_DutyCycle); //配置占空比
  PWM_OutputStateConfig(PWM_ComplementaryOutputPin, PWM_OutputState);   //IO复用PWM配置函数
  if(PWM_OutputState == ENABLE)
  {
    PWM_CmdEX(PWM_ComplementaryOutputPin >> 4, ENABLE); //开启PWM
  }
}

/*****************************************************
*函数名称:void PWM_ComplementaryModeConfigEX(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle, PWM_OutputState_TypeDef PWM_OutputState)
*函数功能:PWM互补
*入口参数:
PWM_ComplementaryOutputPin_TypeDef:PWM_OutputPin:PWM通道
uint16_t:PWM_DutyCycle:PWM占空比配置
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
*****************************************************/
void PWM_ComplementaryModeConfigEX(PWM_ComplementaryOutputPin_TypeDef PWM_OutputPin,
                                   uint16_t PWM_DutyCycle,
                                   PWM_OutputState_TypeDef PWM_OutputState)
{
  PWM_ComplementaryModeConfig(PWM_OutputPin, PWM_DutyCycle); //配置占空比
  PWM_OutputStateConfig(PWM_OutputPin, PWM_OutputState);     //IO复用PWM配置函数
  PWM_OutputStateConfig(PWM_OutputPin + 2, PWM_OutputState); //IO复用PWM配置函数
  if(PWM_OutputState == ENABLE)
  {
    PWM_CmdEX(PWM_OutputPin >> 4, ENABLE); //开启PWM
  }
}

/*****************************************************
*函数名称:PWM_GetFlagStatusEX(PWM_Type_TypeDef PWM_Type)
*函数功能:获取PWM中断标志位
*入口参数:
PWM_Type_TypeDef:PWM_Type:PWM源选择
*出口参数:void
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
*函数名称:void PWM_ClearFlagEX(PWM_Type_TypeDef PWM_Type)
*函数功能:清除PWM中断
*入口参数:
PWM_Type_TypeDef:PWM_Type:PWM源选择
*出口参数:void
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
*函数名称:FlagStatus PWM_GetFaultDetectionFlagStatus(void)
*函数功能:获得PWM故障检测标志位状态
*入口参数:
PWM_Type_TypeDef:PWM_Type:PWM类型
*出口参数:
FlagStatus:PWM故障检测标志位状态
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
*函数名称:void PWM_ClearFaultDetectionFlag(void)
*函数功能:清除PWM故障检测标志位状态   // ！注意,处于锁存模式下，此位可软件清除
*入口参数:
PWM_Type_TypeDef:PWM_Type:PWM类型
*出口参数:void
*****************************************************/
void PWM_ClearFaultDetectionFlagEX(PWM_Type_TypeDef PWM_Type)
{
  if(PWM_Type == PWM0_Type)
  {
    PWMFLT &= 0XBF;
  }
}

/*****************************************************
*函数名称:void PWM_FaultDetectionFunctionConfigEX(PWM_Type_TypeDef PWM_Type, FunctionalState NewState)
*函数功能:PWM故障检测功能开启/关闭-扩展版
*入口参数:
PWM_Type_TypeDef:PWM_Type:PWM类型选择
FunctionalState:NewState:故障检测功能开启/关闭
*出口参数:void
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
*函数名称:void PWM_FaultDetectionModeConfigEX(PWM_Type_TypeDef PWM_Type, PWM_FaultDetectionMode_TypeDef FaultDetectionMode, PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect, PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
*函数功能:PWM故障检测模式设置
*入口参数:
PWM_Type_TypeDef:PWM_Type:PWM类型选择
PWM_FaultDetectionMode_TypeDef:FaultDetectionMode:故障检测功能模式设置: 立即模式/锁存模式
PWM_FaultDetectionVoltageSelect_TypeDef:FaultDetectionVoltageSelect:故障检测电平选择
PWM_FaultDetectionWaveFilteringTime_TypeDef:FaultDetectionWaveFilteringTime:故障检测输入信号滤波时间选择
*出口参数:void
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
*函数名称:void PWM_ITConfigEX(PWM_Type_TypeDef PWM_Type,FunctionalState NewState, PriorityStatus Priority)
*函数功能:PWM中断配置函数-扩展版
*入口参数:
PWM_Type_TypeDef:PWM_Type:PWM源选择
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
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