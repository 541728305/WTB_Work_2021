#ifndef  __OHM_H_
#define  __OHM_H_
#include "sys.h"


 typedef struct {
	char	*Name;          				// ?����z?��?�e??
	uint8_t H_Pin;   				// ??��?
	uint8_t L_Pin;   				// ??�C?
	float Standard_Value;				// ???�e��W��
	float LSL;    				// �e?
	float USL;    				// �e��ȤU��
	float Value;        				// ??��
	char *Unit;
	float Compensation;

	uint16_t Range;
	uint8_t Status;
}Ohm_RES_TypeDef;
 

uint8_t Ohm_RES_Test_Fun(u16 *TestStepN);

#endif

