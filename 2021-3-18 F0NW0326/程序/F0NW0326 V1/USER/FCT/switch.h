#ifndef _SWITCH_TEST_H_
#define _SWITCH_TEST_H_
#include "stm32f10x_it.h" 



typedef struct {
	char    *Name;         
	uint8_t  H_P1;       uint8_t  H_P2;  
	uint8_t  L_P1;       uint8_t  L_P2; 	
	double   Value; 		 char *Unit;   
	double   LSL;        double USL;
	uint16_t MOVE;
	uint16_t Time;
	uint8_t  Status;
}Switch_TypeDef;


uint8_t Switch_Test_Fun(uint16_t *TestStepN);
uint8_t Type_Switch_Test_Fun(u16 *TestStepN,uint16_t Total_Num,uint16_t *Step_Number_buffer);

#endif
