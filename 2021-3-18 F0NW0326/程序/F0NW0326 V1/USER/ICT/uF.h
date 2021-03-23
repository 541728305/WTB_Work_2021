#ifndef _CAP_H_
#define _CAP_H_
#include "stm32f10x_it.h" 



//************************************���ݲ������------------------------
typedef struct {
		char  *Name;          			// ����ԭ��ͼ�е��ݱ��
		uint8_t  	Pin_H;   				// ���Ըߵ�
		uint8_t 	Pin_L;   				// ���Ե͵�
		double    Standard_Value;				// ��Ƶ���ֵ
	  char     *Unit;
		double    LSL;    				// ��ֵ����
		double    USL;    				// ��ֵ����
		double    Value;        				// ����ֵ
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
