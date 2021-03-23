#ifndef _TEST_H_
#define _TEST_H_

#include "sys.h"

typedef enum {
	Auto_Test_Mode = 0,
	Step_Test_Mode,
	Debug_Test_Mode
}Test_Mode;

//********************************* ȫ�ֲ��Խṹ����************************************************
typedef struct {
	 uint8_t Test_Item_Num;                     //������Ŀ���
	 char   *Test_Item_Name;                //����������
	 uint8_t (*Test_Item_Fun)(uint16_t  *Num );  //���Ժ���
	 uint8_t  Test_Item_Result_Flag;						//������Խ�� False or True 	
   uint8_t  EN_Bit;	
}Test_Item_TypeDef;


void autotest(void );
void steptest(void );
unsigned char  test_item_debug( void );
unsigned char  Step_Test_Fun(void );
unsigned char  Auto_Test_Fun(void );
#endif

