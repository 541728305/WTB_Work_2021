#ifndef __KOHM_H_
#define __KOHM_H_
#include "sys.h"
//************************************���ݲ������------------------------
typedef struct {
	char	*Name;          				// ����ԭ��ͼ�е��ݱ��
	uint8_t H_Pin;   				// ���Ըߵ�
	uint8_t L_Pin;   				// ���Ե͵�
	float Standard_Value;				// ��Ƶ���ֵ
	float LSL;    				// ��ֵ����
 	float USL;    				// ��ֵ����
	float Value;        				// ����ֵ
	char *Unit;
	float Compensation;
	double Vol_Src;
	uint16_t Range;
	uint8_t Status;
}KOhm_RES_TypeDef;
uint8_t Type_Vsrc_Test_Fun(u16 *TestStepN, uint16_t Total_Num,uint16_t *Step_Number_buffer);
uint8_t KOhm_RES_Test_Fun(u16 *TestStepN);
#endif

