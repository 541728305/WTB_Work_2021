#ifndef _LEAKAGE_I_H_
#define _LEAKAGE_I_H_
#include "stm32f10x_it.h" 


typedef struct {
		char     *Name;         	
		uint8_t   H_Pin; 
		uint8_t   L_Pin;
		double    Vots_Src;
		double    Value;
   	char     *Unit;   
  	double    LSL;
		double    USL;  
		uint16_t  Time;
		uint8_t   Status;
}Leakage_Current_TypeDef;

uint8_t Leakage_Current_Test_Fun(u16 *TestStepN);
uint8_t Type_Current_Test_Fun(u16 *TestStepN,uint16_t Total_Num,uint16_t *Step_Number_buffer);
#endif
