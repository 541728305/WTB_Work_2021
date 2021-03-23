#ifndef _os_H_
#define _os_H_
#include "stm32f10x_it.h" 
#include "analog_switch.h"




#define  display_EN     	0

extern const char  *Pin_Name[128*3+1];


void Enable_RES_Test_Analog_Switch(void );
void Enable_RES_Test(uint16_t  REF);
void Vsrc_RES_TEST_SET(double Src_Volts,uint8_t RATE);
void Disable_RES_Test_Analog_Switch(void );
double  Res_2wire_Test_Mohm(void);
double  Res_2wire_Test( void);
double  Res_4wire_Test( void);
void  Self_Check_Ananlog_Switch(void);
uint8_t  Search_Point_Function(void );
void Ananlog_Switch_debug_fun(void );
void Short_Self_Check(void);

#endif
