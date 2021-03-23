#ifndef  __LDO_H_
#define  __LDO_H_

#include "sys.h"

typedef struct {
		char     *Name;         	
		uint8_t   Vin_Pin; 
		uint8_t   GND_Pin;
		uint8_t   EN_Pin;
		uint8_t   Vout_Pin;
		double    Vots_Src;
		double    Value;
   	char     *Unit;   
  	double    LSL;
		double    USL;  
		uint16_t  Time;
		uint8_t   Status;
}LDO_TypeDef;
uint8_t LDO_Test_Fun(u16 *TestStepN);
uint8_t Type_Volts_Test_Fun(u16 *TestStepN,uint16_t Total_Num,uint16_t *Step_Number_buffer);
#endif



