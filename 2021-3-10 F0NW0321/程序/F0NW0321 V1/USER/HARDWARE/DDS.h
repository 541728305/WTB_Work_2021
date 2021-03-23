#ifndef  _CAP_MEASURE_H_
#define	 _CAP_MEASURE_H_
#include "stm32f10x_it.h"
void Initalize_DDS(void );
void Write_data( uint16_t  data);
void Set_DDS_Fre(u32 Fre_Hz);
double  Cap_Measure(u8 Test_Pin_H,u8 Test_Pin_L,double  Cap_Vaue);
#endif 
