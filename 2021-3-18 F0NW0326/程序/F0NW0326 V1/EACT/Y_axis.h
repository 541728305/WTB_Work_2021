#ifndef _Y_AXIS_H_
#define _Y_AXIS_H_
#include "sys.h"


#define Up_tandby         0
#define Down_PUSH         1


void Init_Up_Down_EACT(void);


uint8_t  Up_Down_EACT_set(void);

uint8_t Up_Down_EACT_MOVE( uint8_t Num);

#endif

