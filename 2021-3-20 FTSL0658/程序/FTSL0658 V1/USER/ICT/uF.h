#ifndef _CAP_H_
#define _CAP_H_
#include "stm32f10x_it.h" 



//************************************电容测试项定义------------------------
typedef struct {
		char  *Name;          			// 电器原理图中电容编号
		uint8_t  	Pin_H;   				// 测试高点
		uint8_t 	Pin_L;   				// 测试低点
		double    Standard_Value;				// 标称电容值
	  char     *Unit;
		double    LSL;    				// 容值下限
		double    USL;    				// 容值上限
		double    Value;        				// 测试值
	  uint16_t  Time;
		uint32_t  REF;
		uint16_t  offset; 
		uint8_t  Status;
}Cap_RES_Test_TypeDef;
uint8_t Max_CAP_Calibration(void);
void Max_CAP_Self_Check(void);
uint8_t Max_CAP_Calibration(void);
uint8_t Max_Cap_Test_Fun( u16 *TestStepN);
uint8_t  Type_Cap_Test_Fun( uint16_t *TestStepN, uint16_t Total_Num,uint16_t *Step_Number_buffer);
#endif
