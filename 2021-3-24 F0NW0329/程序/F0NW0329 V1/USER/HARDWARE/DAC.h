#ifndef  _DAC_H_
#define  _DAC_H_
#include"stm32f10x_it.h"

void Dac_Init(void);
uint8_t   DAC_Set_Vol(u16 REF,double Tolerance,uint8_t Display_EN);
void   DAC_Line_Check(void);
void Self_Test_DAC_line( u16 vol);
#endif 

