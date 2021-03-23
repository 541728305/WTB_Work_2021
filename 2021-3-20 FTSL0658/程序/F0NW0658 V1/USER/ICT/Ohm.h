#ifndef  __OHM_H_
#define  __OHM_H_
#include "sys.h"


 typedef struct {
	char	*Name;          				// ?器原理?中?容??
	uint8_t H_Pin;   				// ??高?
	uint8_t L_Pin;   				// ??低?
	float Standard_Value;				// ???容值W限
	float LSL;    				// 容?
	float USL;    				// 容值�下限
	float Value;        				// ??值
	char *Unit;
	float Compensation;

	uint16_t Range;
	uint8_t Status;
}Ohm_RES_TypeDef;
 

uint8_t Ohm_RES_Test_Fun(u16 *TestStepN);

#endif

