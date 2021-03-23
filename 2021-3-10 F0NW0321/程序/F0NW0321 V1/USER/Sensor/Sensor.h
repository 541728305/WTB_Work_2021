#ifndef _SENSOR_H_
#define _SENSOR_H_

#include "sys.h" 
#define White            0
#define Dark             1
#define Red              2
#define Green            3
#define Blue             4
#define IR               5
#define OFF              6
#define Light_Src_White PFout(14) // PFout(15)
#define Light_Src_Red   PFout(15) //PFout(14) 
//8888888888
#define Light_Src_Green  PGout(1)
#define Light_Src_Blue   PEout(7)
#define Light_Src_IR     PEout(8)

#define SMC_LEC_CLR    PEout(8)
extern  uint8_t  AlS_Slave_Addr;


#define LEDA        0
#define Idd_Sleep   1
#define Idd_Idle    2
#define Idd_Act     3

#define Device_ID   0
#define ALS_White   1
#define ALS_IR      2
#define PROX_ON     3
#define PROX_OFF    4

//#define Red_Light    MOVE1
//#define Green_Light  MOVE2
//#define Blue_Light   MOVE3

#define Gray_Card      MOVE1
#define White_Light    MOVE4
#define IR_Light       MOVE5

typedef struct {
		//光距感基础参数
		uint8_t   Name[16];         
		uint8_t   PIN_Name[6][10];
		uint8_t   Vdd_Pin;   	      
		uint8_t 	GND_Pin;  	   
		uint8_t   SCL;     
		uint8_t 	SDA;	   
		uint8_t 	INT_Pin ;	
		uint8_t 	LEDA_Pin ;
  	uint8_t   Slave_Addr;
}ALS_Test_TypeDef;
typedef struct {
		//光距感基础参数
		char      *Name;   
		double    Volts_Src;
		double    Value;
		char      *Unit;
		double    USL;
		double    LSL;
		uint16_t  Time;
		uint8_t   Status;
			
}Sensor_Current_TypeDef;

typedef struct {
		//光距感基础参数
		char       *Name;  
		uint8_t     Addr;
	  uint8_t     Num;
		uint16_t    Value;
		char       *Unit;
		uint16_t    USL;
		uint16_t    LSL;
		uint16_t    Time;
		uint16_t    Condition;
		uint8_t     Status;
			
}ALS_Sensor_TypeDef;


void Set_ALS_Sensor_Name( uint8_t Num);
uint8_t ALS_Sensor_Test_Fun(uint16_t *TestStepN);

#endif
