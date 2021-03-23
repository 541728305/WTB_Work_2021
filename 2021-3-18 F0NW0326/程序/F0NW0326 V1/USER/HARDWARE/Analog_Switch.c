#include "analog_switch.h"
#include "lcd3033.h"
#include "global.h"
#include "delay.h"
#include "other.h"
#include "stdio.h"
#include "base_Config.h"




#define cpld_data0  ARC_C0
#define cpld_data1  ARC_C1
#define cpld_data2  ARC_B2
#define cpld_data3  ARC_B3
#define cpld_data4  ARC_B0
#define cpld_data5  ARC_B1
#define cpld_data6  ARC_A2
#define cpld_data7  ARC_A3
#define cpld_data8  ARC_C2
#define cpld_clk    ARC_C3
#define cpld_COML   ARC_A0
#define cpld_COMH   ARC_A1
#define cpld_clear  ARC_D0





void SwitchBoardDisconnect_COMA( void ){
		cpld_COML = 0,cpld_COMH = 0; 
		cpld_clear = 1;
		cpld_clk = 0;
		delay_us (2);
		cpld_clk  = 1;
		cpld_clear = 0;	
		delay_us (2);
}
void SwitchBoardDisconnect_COMB( void ){
		cpld_COML = 1,cpld_COMH = 0; 
		cpld_clear = 1;
		cpld_clk = 0;
		delay_us (2);
		cpld_clk  = 1;
		cpld_clear = 0;	
		delay_us (2);
}
void SwitchBoardDisconnect_COMC( void ){
		cpld_COML = 0,cpld_COMH = 1; 
		cpld_clear = 1;
		cpld_clk = 0;
		delay_us (2);
		cpld_clk  = 1;
		cpld_clear = 0;	
		delay_us (2);
}
void SwitchBoardDisconnect_COMD( void ){
		cpld_COML = 1,cpld_COMH = 1; 
		cpld_clear = 1;	
		cpld_clk = 0;
		delay_us (2);
		cpld_clk  = 1;
		cpld_clear = 0;	
		delay_us (2);
}
void SwitchBoardClose_All_Point(){
		SwitchBoardDisconnect_COMA();
		SwitchBoardDisconnect_COMB();
		SwitchBoardDisconnect_COMC();
		SwitchBoardDisconnect_COMD();
		delay_us (2);
}
//COM A 0x80 COMB 0x20 COMC 0x08 COMD 0x02
void SwitchBoardOpen_Single_Point(u8 Port,uint16_t  Point_Num){

			if(Point_Num >Fixture.Max_Point ){
				cyc4or3run ();
				lcd_printf   ("编程错误PIN=%04d",Point_Num);
				while(1);
		}
	
		 Point_Num --;
		 cpld_data0  = ((Point_Num&0x01)?1:0);
		 cpld_data1  = ((Point_Num&0x02)?1:0);
		 cpld_data2  = ((Point_Num&0x04)?1:0);
		 cpld_data3  = ((Point_Num&0x08)?1:0);
		 cpld_data4  = ((Point_Num&0x10)?1:0);
		 cpld_data5  = ((Point_Num&0x20)?1:0);
		 cpld_data6  = ((Point_Num&0x40)?1:0);
		 cpld_data7  = ((Point_Num&0x80)?1:0);
		 cpld_data8  = ((Point_Num&0x100)?1:0);

		switch(Port ){
			case 'A' :  cpld_COML = 0,cpld_COMH = 0; ;  break ;
			case 'B' :  cpld_COML = 1,cpld_COMH = 0; ;  break ;
			case 'C' :  cpld_COML = 0,cpld_COMH = 1; ;  break ;
			case 'D' :  cpld_COML = 1,cpld_COMH = 1; ;  break ;
			default :    
			lcd_printf   ("Port Choice Error");  while(1);
		
		}
		cpld_clk = 0;
		delay_us (1);
		cpld_clk  = 1;
		delay_us (1);
}




/*******************************************************************
	* File Name     : Close_All_Point
	* Description   : 、
  * Input         : 、
  * return        : y
	* Author        : Morton
	* Date          : 2019/3/14
*******************************************************************/
void MainBoard_Close_All_Point(){
		ARC_Enable_COMA1 = 0;
		ARC_Enable_COMA2 = 0;
		ARC_Enable_COMB1 = 0;
		ARC_Enable_COMB2 = 0;
		ARC_Enable_COMC1 = 0;
		ARC_Enable_COMC2 = 0;
		ARC_Enable_COMD1 = 0;
		ARC_Enable_COMD2 = 0;
}
/*******************************************************************
	* File Name     : Open_Single_Point
	* Description   : Port1 Num
  * Input         : 无
  * return        : y
	* Author        : Morton
	* Date          : 2019/3/14
*******************************************************************/
void MainBoard_Open_Single_Point(u8 Port,uint16_t Point_Num){
		uint16_t Code_Point = Point_Num;
		Point_Num -- ;
		if(Point_Num >Fixture.Max_Point ){
				cyc4or3run ();
				lcd_printf   ("编程错误PIN=%04d",Point_Num);
				while(1);
		}
		switch(Port ){
			case 'A' :  ARC_A0 = ((Point_Num&0x01)?1:0);
									ARC_A1 = ((Point_Num&0x02)?1:0);
									ARC_A2 = ((Point_Num&0x04)?1:0);
									ARC_A3 = ((Point_Num&0x08)?1:0);
									ARC_Enable_COMA1 = 0;
									ARC_Enable_COMA2 = 0;
									if(Code_Point>=1 && Code_Point <= 16){ 
											ARC_Enable_COMA1 = 1;
								 }
								 else if(Code_Point>=17 && Code_Point <= 32){
											ARC_Enable_COMA2 = 1;
								 }										
								 break ;
			case 'B' :  ARC_B0 = ((Point_Num&0x01)?1:0);
									ARC_B1 = ((Point_Num&0x02)?1:0);
									ARC_B2 = ((Point_Num&0x04)?1:0);
									ARC_B3 = ((Point_Num&0x08)?1:0);
									ARC_Enable_COMB1 = 0;
									ARC_Enable_COMB2 = 0;
									if(Code_Point>=1 && Code_Point <= 16){ 
											ARC_Enable_COMB1 = 1;
								 }
								 else if(Code_Point>=17 && Code_Point <= 32){
											ARC_Enable_COMB2 = 1;
								 }										
								 break ;
			case 'C' :  ARC_C0 = ((Point_Num&0x01)?1:0);
									ARC_C1 = ((Point_Num&0x02)?1:0);
									ARC_C2 = ((Point_Num&0x04)?1:0);
									ARC_C3 = ((Point_Num&0x08)?1:0);
									ARC_Enable_COMC1 = 0;
									ARC_Enable_COMC2 = 0;
									if(Code_Point>=1 && Code_Point <= 16){ 
											ARC_Enable_COMC1 = 1;
								 }
								 else if(Code_Point>=17 && Code_Point <= 32){
											ARC_Enable_COMC2 = 1;
								 }										
								 break ;
			case 'D' :  ARC_D0 = ((Point_Num&0x01)?1:0);
									ARC_D1 = ((Point_Num&0x02)?1:0);
									ARC_D2 = ((Point_Num&0x04)?1:0);
									ARC_D3 = ((Point_Num&0x08)?1:0);
									ARC_Enable_COMD1 = 0;
									ARC_Enable_COMD2 = 0;
									if(Code_Point>=1 && Code_Point <= 16){ 
											ARC_Enable_COMD1 = 1;
								 }
								 else if(Code_Point>=17 && Code_Point <= 32){
											ARC_Enable_COMD2 = 1;
								 }										
								 break ;				 						 		 
							default : lcd_printf    ("Port Choice Error");  while(1);
		}
}

/*******************************************************************
	* File Name     : Open_Single_Point
	* Description   : Port1 Num
  * Input         : 无
  * return        : y
	* Author        : Morton
	* Date          : 2019/3/14
*******************************************************************/
void Open_Single_Point(u8 Port,uint16_t Point_Num){
	if(Fixture.Board == Main_Board )
		MainBoard_Open_Single_Point(Port, Point_Num);
	else if(Fixture.Board == Switch_Board )
		SwitchBoardOpen_Single_Point(Port, Point_Num);
	else{
		lcdreset ();
		lcd_printf ("开关板配置出错");
		step_test_mode_get_key ();
	}
	
}
/*******************************************************************
	* File Name     : Close_All_Point
	* Description   : 、
  * Input         : 、
  * return        : y
	* Author        : Morton
	* Date          : 2019/3/14
*******************************************************************/
void Close_All_Point(){
	if(Fixture.Board == Main_Board )
		MainBoard_Close_All_Point ();
	else if(Fixture.Board == Switch_Board )
		SwitchBoardClose_All_Point ();
	else{
		lcdreset ();
		lcd_printf ("开关板配置出错");
		step_test_mode_get_key ();
	}
}
/*******************************************************************
	* File Name     : Open_Single_Point
	* Description   : Port1 Num
  * Input         : 无
  * return        : y
	* Author        : Morton
	* Date          : 2019/3/14
*******************************************************************/
void Open_Two_Point(u8 Port1,uint16_t Point_num1,u8 Port2,uint16_t Point_num2){
	Open_Single_Point(Port1 ,Point_num1 );
	Open_Single_Point(Port2 ,Point_num2 );
	delay_us(2);
}
/***********************************************************************
	* File Name     : Open_Three_Point
	* Description   : Port1 Num
  * Input         : 无
  * return        : y
	* Author        : Morton
	* Date          : 2019/3/14
***********************************************************************/
void Open_Three_Point(u8 Port1,uint16_t Point_num1,u8 Port2,uint16_t Point_num2,u8 Port3,uint16_t Point_num3 ){
	Open_Single_Point(Port1 ,Point_num1 );
	Open_Single_Point(Port2 ,Point_num2 );
	Open_Single_Point(Port3 ,Point_num3 );
		delay_us(2);
}

/****************************************************************************
	* File Name     : Open_Four_Point
	* Description   : Port1 Num
  * Input         : 无
  * return        : y
	* Author        : Morton
	* Date          : 2019/3/14
*****************************************************************************/
void Open_Four_Point( u8 Port1,uint16_t  Point_num1,
											u8 Port2,uint16_t Point_num2,
										  u8 Port3,uint16_t Point_num3,
										  u8 Port4,uint16_t Point_num4
										 ){
	Open_Single_Point(Port1 ,Point_num1 );
	Open_Single_Point(Port2 ,Point_num2 );
	Open_Single_Point(Port3 ,Point_num3 );
	Open_Single_Point(Port4 ,Point_num4 );
	delay_us(2);
}






