#ifndef  _ZDT_UPPER_H_
#define  _ZDT_UPPER_H_
#include "sys.h"
		
		
void     ZDT_Software_Sotp(void);
	
void     ZDT_Software_Cmd_Check(char *buf, u8 *_Mark_Flag);

uint8_t  ZDT_Software_Get_Scan_Result(void);
uint8_t  ZDT_Software_Get_Save_Result(void);


#endif

