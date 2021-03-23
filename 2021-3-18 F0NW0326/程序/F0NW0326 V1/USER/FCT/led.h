#ifndef   __LED_H__
#define   __LED_H__
#include  "sys.h"

typedef struct {
		char     *Name;         	
		uint8_t   H_Pin; 
		uint8_t   L_Pin;
		double    Vsrc;
		double    Value;
	  char     *Unit;
	  double    Standard_Value;
		double    LSL;	
		double    USL;   
    uint8_t   Status;
}LED_TypeDef;

uint8_t  LED_Test_Fun(u16 *TestStepN);
uint8_t Type_LED_Test_Fun(u16 *TestStepN,uint16_t Total_Num,uint16_t *Step_Number_buffer);
#endif

