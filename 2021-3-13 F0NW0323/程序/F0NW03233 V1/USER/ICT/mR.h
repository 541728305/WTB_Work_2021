#ifndef   __MR_H_
#define   __MR_H_


#include "sys.h"

typedef struct {
	char    *Num;          				// ����ԭ��ͼ�е��ݱ��
	uint8_t  Current_Cource_H;
	uint8_t  Test_Pin_H;   				// ���Ըߵ�
	uint8_t  Current_Cource_L;
	uint8_t  Test_Pin_L;   				// ���Ե͵�
	float    Standard_Value;				// ��Ƶ���ֵ
	float    LSL;    				// ��������
	float    USL;    				// ��������
	float    Value;        				// ����ֵ
	char    *Unit;
	float    compensation_value;
	uint8_t  Status;
}mohm_RES_Test_TypeDef;


u8      Res_Test_Fun_4wire(u16 TestStepN);
u8      mohm_Test_Fun_4wire(u16 *TestStepN);
void    mohm_RES_Calibration(void);
u8  Type_Isrc_Test_Fun(u16 *TestStepN , uint16_t Total_Num,uint16_t *Step_Number_buffer);


#endif


