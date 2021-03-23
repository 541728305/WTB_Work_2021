#ifndef   __FRE_H_
#define   __FRE_H_
 
#include "sys.h"

typedef enum {
	TIMER = 0, 
	COUNTER,
	PWM_OUT 
}TIM_Type;


typedef enum {
	RED = 0, 
	ORANGE,
	YELLOW,
	GREEN,
	Cyan,
	BLUE,
	PURPLE,
	WHITE
}Color_Typedef;
void Init_Fre_Test (void);
double  Get_Pulse_Fre( double nms);
double  Get_Color_Fre( uint8_t Color ,double nMS,uint8_t  Timer);

#endif

