#ifndef  __PF_CAP_H_
#define  __PF_CAP_H_
#include "sys.h"

typedef struct {
		char     *Name;          			
		uint8_t  	Pin_H;   				
		uint8_t 	Pin_L;   				
		double    Standard_Value;	
		double    LSL; 	
		double    USL;    				 				
		double    Value;        				
	  uint16_t  Time;
		uint16_t  offset_Value; 
		uint16_t  Drive_data;
		uint8_t   Status;
}pF_Cap_TypeDef;

void Read_pF_Capacitor_offset( uint8_t En);
uint8_t  pF_Capacitor_Calibration_Fun(void);
uint8_t  Type_pF_Cap_Test_Fun (uint16_t *TestStepN, uint16_t Total_Num,uint16_t *Step_Number_buffer);
#endif
