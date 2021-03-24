#include "rf_id.h"
#include "test_config.h"
#include "base_Config.h"
#include "other.h"
#include "lcd3033.h"
#include "test.h"
#include "analog_switch.h"
#include "rf.h"
#include "subus.h"
#include "global.h"
#include "delay.h"

/*********************************************************************************************
	* File Name     : Diode_Test_Fun
	* Description   : Diode_Test  test voltage < 4000mV
  * Input         : *TestStepN
	* return        : Total_Test_Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 20-April-2020
*********************************************************************************************/
uint8_t ID_Test( uint16_t Num){
	
	uint8_t ID_Test_Result = True,i=0,Reg_Value =0x00,CNT = 0;
	SbudsCondition(Item[Num].Group,SET);	
	if(Fixture.Mode  == Auto_Test_Mode ){
		for( i= 0 ; i < 10 ;i ++){			
			if(ReadRegValue(( uint8_t)Item[Num].IO_CTL,&Reg_Value)==True ){
				Item_Data[Num].Value = Reg_Value;
				CNT ++;
			}else{
				Item_Data[Num].Value = 0xFF;
				CNT = 0;
			}
			if(CNT >= 2){
					Item_Data[Num].Value = ((uint8_t )Item_Data[Num].Value&0x0F);
					break ;
			}
		}
		if(TestConfig.RF_ID   == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
			cyc4or3run();
			lcd_printf  ("   0x%02X   ",( uint8_t)Item_Data[Num].Value);
		}
	}
	if(Fixture.Mode  == Step_Test_Mode  ){
			if(ReadRegValue(( uint8_t)Item[Num].IO_CTL,&Reg_Value)==True ){
				Item_Data[Num].Value = Reg_Value;
			}else{
				Item_Data[Num].Value = 0xFF;
			}
			Item_Data[Num].Value = ((uint8_t )Item_Data[Num].Value&0x0F);
			cyc4or3run ();
			lcd_printf  ("   0x%02X   ",( uint8_t)Item_Data[Num].Value);
			if(left_start_key == 1 || right_start_key == 1 ){
					while(left_start_key ==1&&right_start_key ==1){ //?˙家Α???ボ?甧
						if(ReadRegValue(( uint8_t)Item[Num].IO_CTL,&Reg_Value)==True ){
							Item_Data[Num].Value = Reg_Value;
						}else{
							Item_Data[Num].Value = 0xFF;
						}
						Item_Data[Num].Value = ((uint8_t )Item_Data[Num].Value&0x0F);
						lcdpos(lcdcon-1,0);  
						lcd_printf  ("   0x%02X   ",( uint8_t)Item_Data[Num].Value);
						delay_ms (50);
					}
					startkeywait(1,1);
			}
	}

	if(Item_Data[Num].Value >= Item[Num].LSL && Item_Data[Num].Value <= Item[Num].USL){
		if(TestConfig.RF_ID  == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
				lcdpos(lcdcon-1,14);  
				lcd_printf ("OK"); 
		}

	}else{
		if(TestConfig.RF_ID  == DISABLE  || Fixture.Mode  == Auto_Test_Mode  ){
				cyc4or3run ();
				lcd_printf ("%d#%s",Item[Num].Group,Item[Num].Name );
				cyc4or3run();
				lcd_printf  ("   0x%02X   ",( uint8_t)Item_Data[Num].Value);
		}
		lcdpos(lcdcon-1,14); 
		lcd_printf ("NG"); 
		ID_Test_Result |= False;
	}

	SbudsCondition(1,RESET);
	return ID_Test_Result;
}



/*********************************************************************************************
	* File Name     : Diode_Test_Fun
	* Description   : Diode_Test  test voltage < 4000mV
  * Input         : *TestStepN
	* return        : Total_Test_Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
u8 Type_RF_ID_Test_Fun(u16 *TestStepN, uint16_t  Total_Num,uint16_t *Step_Number_buffer){
		uint8_t Total_Test_Result = True;
		uint16_t j=0,Item_Step_Number = 0;
		if(Total_Num == 0)
			return True;
		
		if(TestConfig.RF_ID  == DISABLE &&Fixture.Mode  == Auto_Test_Mode ){
				(*TestStepN) ++;
				cyc4or3run ();
				lcd_printf ("%d>%s",*TestStepN,"U0201 ID ... ");
		}
		

		for(j = 0 ; j < Total_Num ; j ++){
				Item_Step_Number = Step_Number_buffer[j];		 
				if(TestConfig.RF_ID   == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
						(*TestStepN) ++;
						cyc4or3run ();
						lcd_printf ("%d>%d#%s",*TestStepN,Item[Item_Step_Number].Group,Item[Item_Step_Number].Name);
				}
				Item_Data[Item_Step_Number].Status = ID_Test(Item_Step_Number);		
				if(Fixture.Mode  == Auto_Test_Mode && Item_Data[Item_Step_Number].Status == False){
					Total_Test_Result |= False ;
					if(TestConfig.FAIL_continue  == ENABLE )
							continue ;
					else{
						break ;
					}
				}
				if(Fixture.Mode  == Step_Test_Mode && Item_Data[Item_Step_Number].Status == False){
					cyc4or3run ();
					lcd_printf ("L:复测  R:下一步");
					lcdcon -- ;
					Clear_buffer(3);
					if (step_test_mode_get_key () == Left_Button_Pressed_Down ){
						j --;
						(*TestStepN) --;
						continue ;
					}
					Total_Test_Result |= False ;
			 }				
		}	
		if(TestConfig.RF_ID   == DISABLE &&Fixture.Mode  == Auto_Test_Mode && Total_Test_Result == True ){
				lcdpos(lcdcon -1,14);
				lcd_printf ("OK");
		}
		return Total_Test_Result ;	
}



