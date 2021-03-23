#ifndef _ADC_H_
#define _ADC_H_
#include"stm32f10x_it.h" 
void Adc_Init(void);
u16 Get_Adc(u8 ch) ;
uint16_t Get_ADC_Value(uint8_t  ch);
float Get_Adc_Average(unsigned char ch,unsigned char times);
#endif
