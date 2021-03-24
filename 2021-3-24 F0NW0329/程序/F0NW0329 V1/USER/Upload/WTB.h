#ifndef   __WTB_H_
#define   __WTB_H_



#include "sys.h"

extern uint8_t  Soft_Start_Test;
void     Set_Test_Satation(uint8_t );


uint8_t  Get_Soft_Start_Status(void);

void     WTB_Software_Cmd_Check(char *buf, uint8_t *_Mark_Flag);


uint8_t  WTB_Software_Get_Soft_Start_Status(void);
uint8_t  WTB_Software_Get_Save_Result( uint8_t Test_Result);
uint8_t  WTB_Software_Get_Scan_Result(void);
		
		
#endif

