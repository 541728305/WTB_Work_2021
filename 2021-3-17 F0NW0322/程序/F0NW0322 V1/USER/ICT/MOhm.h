#ifndef __MOHM_H__
#define __MOHM_H__

#include "sys.h"

typedef struct {
	char	*Name;          				// ?����z?��?�e??
	uint8_t H_Pin;   				// ??��?
	uint8_t L_Pin;   				// ??�C?
	float Standard_Value;				// ???�e��
 	float USL;    				// �e�ȤW��
	float LSL;    				// �e�ȤU��
	float Value;        				// ??��
	float Compensation;

	uint16_t Range;
	uint8_t Status;
}MOhm_RES_TypeDef;

uint8_t MOhm_RES_Test_Fun(u16 *TestStepN);

#endif


