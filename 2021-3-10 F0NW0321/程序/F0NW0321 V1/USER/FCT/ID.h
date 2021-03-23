#ifndef _ID_H_
#define _ID_H_
#include "stm32f10x_it.h" 

uint8_t Read_IC_ID_Debug(void);

uint8_t  Type_IC_ID_Test_Fun( uint16_t *TestStepN, uint16_t Total_Num,uint16_t *Step_Number_buffer);
#endif
