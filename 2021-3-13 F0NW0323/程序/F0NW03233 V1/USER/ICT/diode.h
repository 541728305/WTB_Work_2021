#ifndef _DIODE_H_
#define _DIODE_H_
#include "stm32f10x_it.h" 


typedef struct {
		char     *Name;         	
		uint8_t   H_Pin; uint8_t L_Pin;
	  double    Vsrc;
		double    Value;
		char     *Unit;
	  double    LSL;
		double    USL;  
		double    offset;
		uint16_t  Time;
		uint8_t   Status;
}Diode_TypeDef;

uint8_t Diode_Test_Fun(u16 *TestStepN);
uint8_t Type_Diode_Test_Fun(u16 *TestStepN, uint16_t  Total_Num,uint16_t *Step_Number_buffer);
uint8_t Type_TVS_Test_Fun(u16 *TestStepN,uint16_t Total_Num,uint16_t *Step_Number_buffer);
#endif
