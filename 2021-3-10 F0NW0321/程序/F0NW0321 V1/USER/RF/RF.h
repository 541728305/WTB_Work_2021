#ifndef  __RF_H___
#define  __RF_H__

#include "sys.h"
typedef struct {
	uint8_t  Group;
	char    *Name;
	uint8_t  Reg_Addr;
	uint8_t  USL;
	uint8_t  LSL;
	uint8_t  Value;
	char     *Unit;
	uint8_t  Status;
	
}RF_ID_typedef;


extern  RF_ID_typedef   RF5852[];
extern  uint8_t RF_Total_Result[4];



void SbudsCondition(uint8_t IC_Num, uint8_t Status);
uint8_t  Debug_RF_IC(void);
uint8_t RF_ID_Test(void);
u8  Type_RF_Test_Fun(u16 *TestStepN , uint16_t Total_Num);

#endif

