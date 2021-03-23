#include "lcd3033.h"
#include "delay.h"
#include "global.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdio.h>


#define LCD_Delay_Time 2
#define lcd_bit_set    0
#define lcd_bit_reset  1


u8 lcdarray[0x40];	
u8 lcdbase;     
u8 lcdhang=4;  
//u8 lcdcs=0;
u8 lcdcon; 

void Clear_buffer( uint8_t Row){
	uint8_t i;
	for( i = 0 ; i < 16 ;i ++)
		lcdarray[Row*16+i]= ' ';
}

void writeir(u8 command){
 	u8 i;
 	if(command==1) {
		for(i=lcdbase=0;i<0x40;lcdarray[i]=0x20,i++);		
		lcdcon =0;
	}		
	lcdcs = lcd_bit_set;
 	for(i=0;i<24;i++){
	 	if(i<5)	   
			lcdsid = lcd_bit_set;							
		else if((i>7)&&((i&4)==0))	 {
					if(	command &0x80) lcdsid =lcd_bit_set;
					else		           lcdsid =lcd_bit_reset;
					 command<<=1;
			}				
		else   
			lcdsid = lcd_bit_reset;
		delay_us (LCD_Delay_Time);
		lcdsclk  = lcd_bit_set;
		delay_us (LCD_Delay_Time);
		lcdsclk  = lcd_bit_reset;				
	} 
	lcdcs = lcd_bit_set;
}

void writeddr(u8 CHAR){
	u8 i; 
	lcdcs=lcd_bit_set;
	for(i=0;i<24;i++){						   
	 	if((i<5)||(i==6))   
			lcdsid = lcd_bit_set;							
		else if((i>7)&&((i&4)==0))  {
							if(	CHAR &0x80) lcdsid = lcd_bit_set;
					else		   
					    lcdsid = lcd_bit_reset;
					CHAR <<=1;
					}					
					else   
		lcdsid  = lcd_bit_reset;		delay_us (LCD_Delay_Time);
		lcdsclk = lcd_bit_set;	    delay_us (LCD_Delay_Time);  
		lcdsclk = lcd_bit_reset;		
	}
	lcdcs=lcd_bit_set;
}
void lcdputchar(u8 charC){
	writeddr(lcdarray[lcdbase]=charC); 		
	lcdbase=(lcdbase+1)&0x3f;	        
	if((lcdbase&0x0f)==0)
	writeir(0x80+(lcdbase&0x10)+((lcdbase&0x20)>>2)); 
}
void lcdpos(u8 x,u8 y){
   	writeir(0x80+((x&0x01)<<4)+((x&0x02)<<2)+(y>>1));
	if(y&1)	        writeddr(lcdarray[(x<<4)+(y-1)]); 
 	lcdbase=(x<<4)+y;
}
void lcdreset(void){	
	writeir(0x38);delay_ms (5);
 	writeir(0x38);delay_ms (5);
 	writeir(0x38);delay_ms (5);
 	writeir(0x06);delay_ms (5);
 	writeir(0x01);delay_ms (5);//clear lcd screeen
 	writeir(0x0c);delay_ms (5);
}
void writestring(const  char  *s)	 {
	while(*s != '\0')
		lcdputchar(*s++);
}
void cyc4or3set(u8 hang) {
   lcdhang=hang;
   lcdcon=4-hang; 
}
void cyc4or3run(){
 	u8 j;
 	if( lcdcon <4) lcdpos( lcdcon++,0 );
 	else{
	 	for( j = (4-lcdhang)<<4 ;j<0x30; j++ ){
		 	if((j&0x0f)==0) lcdpos(j>>4,0);
			lcdputchar(lcdarray[j+0x10]);
 		}
  		lcdpos( 3 , 0 );
			printf  ("                ");
			lcdpos( 3 , 0 );
 	}
} 

void Clear_Screen(){
	writeir (0x01);
	lcdcon = 0;
	lcdbase = 0;
}

void imageclear(void)    
{
	u16  x,y,i;
	writeir(0x34);		
	for(i=0;i<9;i+=8)
	for(y=0;y<32;y++)
	for(x=0;x<8;x++)
	{
		writeir(0x80+y);  		
		writeir(0x80+x+i);  
		writeddr(0x00);  
		writeddr(0x00);  	
	}
	writeir(0x36);   		
	writeir(0x30);   		
}
void imagedraw(u8  *img)    
{
	u16 j=0;
	u8 x,y,i=0;
	writeir(0x34);		
	for(i=0;i<9;i+=8)
		for(y=0;y<32;y++)
			for(x=0;x<8;x++){
				writeir(0x80+y);  		
				writeir(0x80+x+i);  
				writeddr(img[j++]); 
				writeddr(img[j++]); 
			}
	writeir(0x36);   	
	writeir(0x30);
}


void lcd_printf (char *fmt,...){
		va_list ap;	             /*This is support the format output*/ 
		char string[64];
		va_start(ap,fmt);
		vsprintf(string,fmt,ap); /* Store the string in the String buffer*/
		writestring(string);
		va_end(ap);
}


/**********************************************************************************************************************
	* File Name     : Set_Reverse
	* Description   : 反白设置
  * Input         : 无
  * return        : y
	* Author        : Morton
	* Date          : 2019/3/14
************************************************************************************************************************/
void Set_Reverse(unsigned char EN_Bit, unsigned char y,unsigned char x,unsigned char width) {   
	unsigned char i,j;         
	writeir(0x34);     
	for( i = 0 ; i < 16; i ++ ){
			writeir(0x80+((y&0x01)<<4)+i);//行标		
			writeir(0x80+((y&0x02)<<2)+(x>>1)); //列表
			for( j = (x&0x0E); j < (x+width); j ++){ 
				if((x&0x01)&& j==x)
					writeddr(0x00);
				else
					writeddr(EN_Bit?0xFF:0x00); 
			}
	}      
	writeir(0x36);
	writeir(0x30);
}


