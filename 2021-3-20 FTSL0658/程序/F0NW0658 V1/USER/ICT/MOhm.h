#ifndef __MOHM_H__
#define __MOHM_H__

#include "sys.h"

typedef struct {
	char	*Name;          				// ?器原理?中?容??
	uint8_t H_Pin;   				// ??高?
	uint8_t L_Pin;   				// ??低?
	float Standard_Value;				// ???容值
 	float USL;    				// 容值上限
	float LSL;    				// 容值下限
	float Value;        				// ??值
	float Compensation;

	uint16_t Range;
	uint8_t Status;
}MOhm_RES_TypeDef;

uint8_t MOhm_RES_Test_Fun(u16 *TestStepN);

#endif


