#ifndef _SCDriver_Joystick_H_
#define _SCDriver_Joystick_H_
//<<<Use SPTML>>>
#define SCD_Joystick_VRX P12//SCD_Joystick_VRX 
#define SCD_Joystick_VRX_INIT 0x0104//SCD_Joystick_VRX_INIT 
#define SCD_Joystick_VRY P12//SCD_Joystick_VRY 
#define SCD_Joystick_VRY_INIT 0x0104//SCD_Joystick_VRY_INIT 
#define SCD_Joystick_PinX 8//SCD_Joystick_PinX 
#define SCD_Joystick_PinY 9//SCD_Joystick_PinY 
extern unsigned char SCD_Joystick_PosX;
extern unsigned char SCD_Joystick_PosY;
extern void SCD_Joystick_GetPosition();
extern void SCD_Joystick_Init();
//<<<end of SPTML>>>
#endif
