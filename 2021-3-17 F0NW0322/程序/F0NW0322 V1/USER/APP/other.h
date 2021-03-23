#ifndef _OTHER_H_
#define _OTHER_H_

#include "stm32f10x_it.h" 
 

typedef enum {
	True = 0, 
	False
}Bool;

typedef enum {
	No_Button_Pressed_Down = 0,
	Left_Button_Pressed_Down,
	Right_Button_Pressed_Down,
	Double_Button_Pressed_Down
}Key_Status_Typedef;

void  resetMCU(void) ;

void  RevertStartupScreen(void );
void  Display_Total_Rate(void );
uint8_t  step_test_mode_get_key(void );
void  startkeywait(uint8_t L_k,uint8_t R_k);

uint8_t gettestmode(void );
uint8_t GetKey_Status (void);
uint8_t Get_start_key_val(void);
uint8_t getstarttime( uint16_t time1);
uint8_t Getkey_Cursor( char word, uint8_t x,uint8_t y, uint8_t En_bit  );


double  Average_Fun(double *dat  , uint8_t  Num);

#endif 
