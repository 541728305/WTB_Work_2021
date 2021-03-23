#include "ID.h"
#include <string.h>
#include "lcd3033.h"
#include "test.h"
#include "global.h"
#include "delay.h"
#include "usart.h"
#include "ad7176.h"
#include "Sup_Fun.h"
#include "other.h"
#include "analog_switch.h"
#include "dac.h"
#include "NET_iic.h"
#include "test_config.h"
#include "base_Config.h"
#define Slave_Addr   0x76
#define IC_TEST_Display_En DISABLE 

static  uint8_t Read_Register_Test( uint16_t Num){
		uint8_t ch[10],CNT = 0,i,Test_Resut = True;

		for ( i = 0; i < 255; i ++){
				if(Read_OneByteFromDevice(Slave_Addr,( uint8_t)Item[Num].IO_CTL,ch)== True){
						Item_Data[Num].Value = ch[0];				  
						CNT ++;
				}else{			
						delay_us (100);
						CNT = 0;
				}
				if(CNT == 10)
					 break ;
	
		}
		if(IC_TEST_Display_En == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
			cyc4or3run ();
			lcd_printf ( "     0X%02X     ",( uint8_t)Item_Data[Num].Value);
		}
		if(Fixture.Mode == Step_Test_Mode){
			if(Read_OneByteFromDevice(Slave_Addr,( uint8_t)Item[Num].IO_CTL ,ch)== True){
					Item_Data[Num].Value = ch[0];
			}else{
					Item_Data[Num].Value = 0xFF;
			}
			if(left_start_key == 1 || right_start_key == 1 ){
				while(left_start_key ==1&&right_start_key ==1){
						lcdpos (lcdcon -1 ,0);
						if(Read_OneByteFromDevice(Slave_Addr,( uint8_t)Item[Num].IO_CTL,ch)== True){
								Item_Data[Num].Value = ch[0];

								lcd_printf ( "     0X%02X     ",( uint8_t)Item_Data[Num].Value);
						}else{
								Item_Data[Num].Value = 0xFF;
							  lcd_printf ( "     NO ACK     ");
						}

						delay_ms (150);
				}
				startkeywait (1,1);
			}
		}
		lcdpos (lcdcon-1, 14);
		if(Item_Data[Num].Value >= Item[Num].LSL && Item_Data[Num].Value <= Item[Num].USL  ){
				if(IC_TEST_Display_En == ENABLE || Fixture.Mode == Step_Test_Mode  ){
						lcdpos(lcdcon-1,14);  
						lcd_printf ("OK"); 
				}
				Test_Resut = True;
		}else{
				if(IC_TEST_Display_En == DISABLE  || Fixture.Mode == Auto_Test_Mode  ){
						cyc4or3run ();
						lcd_printf ("%s",Item[Num].Name);
						cyc4or3run ();
						lcd_printf ( "     0X%02X     ",( uint8_t)Item_Data[Num].Value);
				}
				Test_Resut = False;
				lcdpos (lcdcon-1,14);
				lcd_printf("NG");
		}
		return Test_Resut;
}

/*********************************************************************************************
	* File Name     : Read_IC_ID_Test_Fun
	* Description   : Read_IC_ID_Test_Fun 
  * Input         : TestStepN
	* return        : IC_Test_Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 3-July-2019
*********************************************************************************************/
uint8_t  Type_IC_ID_Test_Fun( uint16_t *TestStepN, uint16_t Total_Num,uint16_t *Step_Number_buffer){

	uint8_t Total_ID_Test_Result = True; 
	uint16_t  i = 0,Item_Step_Number = 0;
	
	if(Total_Num == 0)
		return True;
	if(		IC_TEST_Display_En == DISABLE &&Fixture.Mode == Auto_Test_Mode ){
			(*TestStepN) ++;
			cyc4or3run ();
			lcd_printf ("%d>%s",*TestStepN,"U1_ID ...   ");
	}
	
  Net_IIC_Init();
	DAC_Set_Vol(1800,5,0); 
	Relay_Drive (  K15_Src_Choice|K12_10R_Ref|K8_Src_COMAB|K5_IIC_COMCD,SET);
			
	for( i = 0; i < Total_Num ; i ++){
		Close_All_Point ();
		Item_Step_Number = Step_Number_buffer[i];
		Open_Two_Point (COMA,Item[Item_Step_Number].Src_H  ,COMB, Item[Item_Step_Number].Test_H );
		Open_Two_Point (COMC,Item[Item_Step_Number].Src_L  ,COMD, Item[Item_Step_Number].Test_L);

		delay_ms (80);
		if(IC_TEST_Display_En == ENABLE || Fixture.Mode == Step_Test_Mode  ){
			 (*TestStepN)++;
			 cyc4or3run();
			 lcd_printf ("%d>%s",*TestStepN,Item[Item_Step_Number].Name);
		 }
		 Item_Data[Item_Step_Number].Status = Read_Register_Test(Item_Step_Number);
		 if(Fixture.Mode == Auto_Test_Mode && Item_Data[Item_Step_Number].Status == False){
				Total_ID_Test_Result |= False ;	
				if(TestConfig.FAIL_continue == ENABLE )
						continue ;
				else{
					break ;
				}
		 }
			if(Fixture.Mode == Step_Test_Mode && Item_Data[Item_Step_Number].Status == False){
					cyc4or3run ();
					lcd_printf ("L:复测  R:下一步");
					lcdcon -- ;
					Clear_buffer(3);
					if (step_test_mode_get_key () == Left_Button_Pressed_Down ){
						i --;
						Item_Step_Number --;
						(*TestStepN) --;
						continue ;
					}
					Total_ID_Test_Result |= False ;	
				}
		}	
		if(IC_TEST_Display_En == DISABLE &&Fixture.Mode == Auto_Test_Mode && Total_ID_Test_Result == True ){
				lcdpos(lcdcon -1,14);
				lcd_printf ("OK");
		}
		Close_All_Point ();
	  Relay_Drive (  K15_Src_Choice|K12_10R_Ref|K8_Src_COMAB|K5_IIC_COMCD,RESET);
		delay_ms (80);
		return Total_ID_Test_Result ;		 	
}

uint8_t Read_IC_ID_Debug(void){
	uint8_t ch[10],i,BOT_Status,REG=0x10;	
  Net_IIC_Init();
	DAC_Set_Vol(1800,5,0); 
	Relay_Drive (  K15_Src_Choice|K12_10R_Ref|K8_Src_COMAB|K5_IIC_COMCD,SET);
	Open_Four_Point (COMA,6,COMB ,9,COMC ,4,COMD,2 );
	lcdreset ();
	lcdpos (0,0); lcd_printf ("读取U1地址      ");
	lcdpos (3,0); lcd_printf ("L:读取    R:退出");
	while(1){
		  BOT_Status = Get_start_key_val();
		  if(BOT_Status == Left_Button_Pressed_Down ){
				lcdpos (2,0);lcd_printf ("ID= 0x%00    ");
				for ( i = 0; i < 250; i ++){
				    lcdpos (1,0);lcd_printf ("ID= 0x%02X    ",i);				
						if(Read_OneByteFromDevice(i,REG,ch)== True){		
								lcdpos (2,0);lcd_printf ("REG%02X=0x%02X    OK",REG,ch[0]);
								break ;
						}else {
							  lcdpos (2,0);lcd_printf ("                ");
						}
				}
			}else if(BOT_Status == Right_Button_Pressed_Down ){
				break ;
			}
	}
	Relay_Drive (  K15_Src_Choice|K12_10R_Ref|K8_Src_COMAB|K5_IIC_COMCD,RESET);	
	Close_All_Point ();
	RevertStartupScreen();
	return 1;
}


