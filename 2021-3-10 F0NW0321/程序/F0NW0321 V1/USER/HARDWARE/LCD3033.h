#ifndef __LCD3033SERIAL_H__
#define __LCD3033SERIAL_H__	
#include "stm32f10x_it.h" 

extern uint8_t lcdcon;

void Clear_buffer( uint8_t Row);
void writeir(u8 command);
void lcdputchar(u8 charC);
void lcdpos(u8 x,u8 y) ;
void lcdreset(void) ;
void writestring(const char  *s);
void cyc4or3set(u8 hang) ;
void cyc4or3run(void) ;
void imagedraw(u8  *img);
void imageclear(void)  ;  
void Clear_Screen(void ); 
void lcd_printf (char *fmt,...);
void Set_Reverse(unsigned char EN_Bit, unsigned char y,unsigned char x,unsigned char width);
#endif

