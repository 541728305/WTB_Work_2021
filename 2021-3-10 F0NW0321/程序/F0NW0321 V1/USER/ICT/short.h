#ifndef  _SHORT_H_
#define  _SHORT_H_
#include "sys.h"


#define Max_ConductionImpedance   10.0   //低压导通阻抗定义
#define ShortPoint_Num  					30  	 //短路点最大值
#define  SHORT_NUM                256




#pragma pack (1) 
	typedef  struct {
			uint8_t Status[SHORT_NUM];
			double  Value[SHORT_NUM];
	}SHORT_DATA_Typedef ;
	
#pragma pack () 	
	
extern  const  uint16_t  ShortGroup[][ShortPoint_Num];	
extern  SHORT_DATA_Typedef SHORT_RES;;	

uint8_t Type_OS_Short_Test_Fun(u16 *TestStepN, uint16_t Total_Num,uint16_t *Step_Number_buffer);

uint8_t  Short_Test_Function(u16 *TestStepN);
void Short_Gooup_Edit_Check( void );
void  ViewShortGroup(void);			
#endif
