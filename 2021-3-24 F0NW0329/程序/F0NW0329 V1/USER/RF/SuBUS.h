#ifndef  __SUBUS_H_
#define  __SUBUS_H_

#include "sys.h"

void SbudCondition( uint8_t Status);
uint8_t  SetRFSwitchStatus(  uint8_t RF_Status, uint8_t Timer);
uint8_t ReadRegValue( uint8_t reg_Num ,uint8_t *RegValue);

#endif





