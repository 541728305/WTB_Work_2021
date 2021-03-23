#ifndef   __MR_H_
#define   __MR_H_


#include "sys.h"

typedef struct {
	char    *Num;          				// 电器原理图中电容编号
	uint8_t  Current_Cource_H;
	uint8_t  Test_Pin_H;   				// 测试高点
	uint8_t  Current_Cource_L;
	uint8_t  Test_Pin_L;   				// 测试低点
	float    Standard_Value;				// 标称电容值
	float    LSL;    				// 电阻下限
	float    USL;    				// 电阻上限
	float    Value;        				// 测试值
	char    *Unit;
	float    compensation_value;
	uint8_t  Status;
}mohm_RES_Test_TypeDef;


u8      Res_Test_Fun_4wire(u16 TestStepN);
u8      mohm_Test_Fun_4wire(u16 *TestStepN);
void    mohm_RES_Calibration(void);
u8  Type_Isrc_Test_Fun(u16 *TestStepN , uint16_t Total_Num,uint16_t *Step_Number_buffer);


#endif


