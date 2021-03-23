#ifndef __DATA_H_
#define __DATA_H_



#include "sys.h"


uint16_t Init_Test_data(void );

uint8_t  UploadShortGroup(char *buf);

void     ZDT_Software_Upload_Test_Item(void );	
uint8_t  ZDT_Software_Upload_Data(u8 Result);

uint8_t  WTB_Software_Upload_Data(uint8_t Test_Result);
void     WTB_Software_Upload_Test_Item(void);
uint8_t  Upload_Test_Data(char *buf);
#endif


