#ifndef _ANALOG_SWITCH_H_
#define _ANALOG_SWITCH_H_
#include "stm32f10x_it.h" 



//#define SWITCH_Board


#define COMA  'A'
#define COMB  'B'
#define COMC  'C'
#define COMD  'D'

void Procuct_Direction_Set( uint8_t  Dir);

void Close_All_Point(void );

void Open_Single_Point(u8 Port,uint16_t  Point_Num);

void Open_Two_Point(u8 Port1,uint16_t Point_num1,u8 Port2,uint16_t Point_num2);	

void Open_Three_Point(u8 Port1,uint16_t Point_num1,u8 Port2,uint16_t Point_num2,u8 Port3,uint16_t Point_num3 );

void Open_Four_Point(u8 Port1,uint16_t Point_num1,u8 Port2,uint16_t Point_num2,\
										 u8 Port3,uint16_t Point_num3,u8 Port4,uint16_t Point_num4);	
#endif
