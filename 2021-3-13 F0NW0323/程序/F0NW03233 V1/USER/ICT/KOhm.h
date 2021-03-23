#ifndef __KOHM_H_
#define __KOHM_H_
#include "sys.h"
//************************************电容测试项定义------------------------
typedef struct {
	char	*Name;          				// 电器原理图中电容编号
	uint8_t H_Pin;   				// 测试高点
	uint8_t L_Pin;   				// 测试低点
	float Standard_Value;				// 标称电容值
	float LSL;    				// 容值下限
 	float USL;    				// 容值上限
	float Value;        				// 测试值
	char *Unit;
	float Compensation;
	double Vol_Src;
	uint16_t Range;
	uint8_t Status;
}KOhm_RES_TypeDef;
uint8_t Type_Vsrc_Test_Fun(u16 *TestStepN, uint16_t Total_Num,uint16_t *Step_Number_buffer);
uint8_t KOhm_RES_Test_Fun(u16 *TestStepN);
#endif

