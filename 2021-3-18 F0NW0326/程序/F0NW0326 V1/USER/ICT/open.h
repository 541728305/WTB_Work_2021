#ifndef _OPEN_H_
#define _OPEN_H_
#include "sys.h"

#include "sys.h"
#define OPEN_NUM                  3500
#define OpentPoint_Num            36
#define Min_InsulationResistance  5.0    //¾øÔµ×è¿¹¶¨Òå 1M



typedef  struct {
		uint8_t Status;
		char  RESULT[50];
		double  Value[OPEN_NUM];
		uint8_t _Status[OPEN_NUM]; 
}OPEN_TEST ;



extern  const  uint16_t        OpenGroup[][OpentPoint_Num];
extern OPEN_TEST Open_Data;


uint8_t  Open_Test_Function_V2(u16 *TestStepN);
uint8_t  Open_Test_Function(u16 *TestStepN);
uint8_t Type_OS_Open_Test_Fun(u16 *TestStepN, uint16_t Total_Num,uint16_t *Step_Number_buffer);

#endif


