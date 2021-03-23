#ifndef _TEST_CONFIG_H_
#define _TEST_CONFIG_H_

#include "sys.h"

#define Hardware_typedef_Total   15
#define Max_Step_Nummber         500

typedef enum {
	Type_OS_Short = 0,
	Type_OS_Open,
	Type_Isrc ,
	Type_Vsrc,
	Type_Diode,	
	Type_Cap,
	Type_pF_Cap,
	Type_Current,
	Type_Volts,
	Type_TVS,
	Type_Switch,
	Type_LED,
	Type_Hall,
	Type_IC_ID,
	Type_RF_ID,
}Hardware_typedef ;

typedef struct {
	


  FunctionalState OS_Short;
	FunctionalState OS_Open;	
	FunctionalState Isrc;	
	FunctionalState Vsrc;
	FunctionalState Cap;
	FunctionalState pF_Cap;
	FunctionalState Diode;
	FunctionalState Hall;
	FunctionalState Current;
	FunctionalState Volts;
	FunctionalState TVS;
	FunctionalState Switch;
	FunctionalState LED;
	FunctionalState IC_ID;
	FunctionalState RF_ID;
	
	FunctionalState Short; 
  FunctionalState OPEN;              
  FunctionalState Component;  
	FunctionalState FCT;
  FunctionalState RF;
	FunctionalState FAIL_continue;
  FunctionalState OpenList;
	
}TestConfigTypedef;


typedef enum {
	OS_Short = 0,
  OS_Open,
	
	R_Isrc_10ohm ,
	
	R_Vsrc_10ohm, 
	R_Vsrc_1Kohm,
	R_Vsrc_20Kohm,

	C_100ohm,
	C_1Kohm,
	C_10Kohm,
	C_100Kohm,
	C_1Mohm,
	C_10Kohm_pF,
	D_10R,
	D_1Kohm,
	D_20Kohm,
	I_10R,
	I_1Kohm,
	I_20Kohm,
	V_10R,
	V_1Kohm,
	V_20Kohm,
	TVS_10R,
	TVS_1Kohm,
	TVS_20Kohm,
	SW_OFF1,
	SW_ON_10R,
	SW_ON_1Kohm,
	SW_ON_20Kohm,	
	SW_OFF2,
	LED_VF,
	LED_Color_R,
	LED_Color_G,
	LED_Color_B,
	Hall_10R,
	Hall_1Kohm,
	Hall_20Kohm,
	IC_ID,
	RF_ID,
	Reserved	
}Test_TypeDef;

typedef struct {
	char                   Group;
  char                  *Class;
	Test_TypeDef           Type;
	char                  *Name;          				// 电器原理图中电容编号
	float                  Src;
	uint16_t               Src_H;
	uint16_t               Test_H;   				// 测试高点
	uint16_t               Src_L;
	uint16_t               Test_L;   				// 测试低点
	float                  STD_Value;				// 标称电容值
	char                  *Unit;
	float                  LSL;    				// 电阻下限
	float                  USL;    				// 电阻上限
	uint16_t               Time;
	uint32_t               IO_CTL;
	
	
}Item_TypeDef;

typedef struct {

	float     offset;
	uint8_t   Status;
	float     Value;        				// 测试值	
}Item_Data_TypeDef;

extern  TestConfigTypedef  TestConfig;
extern  const Item_TypeDef Item[];
extern uint16_t Step_buffer[Max_Step_Nummber];

extern Item_Data_TypeDef Item_Data[Max_Step_Nummber];


void InitTestConfig(void);
uint16_t Get_Component_Num(void);
uint16_t Get_Currennt_Type_CNT( Hardware_typedef Type,uint16_t *StepNumberBuf,uint16_t Max_StepNumber );

#endif




