#include "xy_axis.h"
#include "X_axis.h"
#include "modbus.h"
#include "delay.h"
#include "usart.h"
#include "sys.h"
#include "lcd3033.h"
#include "other.h"
extern LEC_Run_Parameter *LEC_SET;
extern LEC_Frame         *Lec_Ptr;
extern  Act_typedef X_Axis,Y_Axis;



uint8_t XY_MOVE(void){
		uint8_t t=0;
//		Y_Axis.Protect_Mode      =  RETURN ;
//		Y_Axis.Protect_Range_LSL = 0;
//		Y_Axis.Protect_Range_USL = eep_save_da[ELEC_UPDOWN_UP].SAVE_DATA0;
//		t= Axis_Running_Position(X_Axis,Absolute_Coordinate,eep_save_da[ELEC_WAIT_POINT ].SAVE_DATA0,eep_save_da[ELEC_TAKEOFF_SPEED].SAVE_DATA0,
//					                Y_Axis,Absolute_Coordinate,eep_save_da[ELEC_UPDOWN_DO].SAVE_DATA0,eep_save_da[ELEC_UPDOWN_SPEED].SAVE_DATA0);
	return t;
}


