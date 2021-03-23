#include <stdlib.h>
#include "pF.h"
#include "reg.h"
#include "delay.h"
#include "other.h"
#include "sup_fun.h"
#include "test.h"
#include "lcd3033.h"
#include <stdio.h>
#include "global.h"
#include "usart.h"
#include "AD5933.h"
#include "sup_fun.h"
#include "test_config.h"
#include "base_Config.h"
#include "analog_switch.h"

/*********************************************************************************************
	* File Name     : Type_pF_Cap_Test_Fun
	* Description   : Type_pF_Cap_Test_Fun
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 14-OCT-2019
*********************************************************************************************/
static double Read_pf_Cap_Value(uint16_t Num, uint8_t  range ){
	double CAP = LCR_Test(__Capacitor,0,1)-Item_Data[Num].offset ;
	if(CAP < 0.0)
		CAP = 0.0;
		
	return CAP; 
}


/*********************************************************************************************
	* File Name     : Type_pF_Cap_Test_Fun
	* Description   : Type_pF_Cap_Test_Fun
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 14-OCT-2019
*********************************************************************************************/
uint8_t pF_CAP_Tests( uint16_t Num){
		uint8_t i,CNT = 0,CAP_Test_Reault = True;
		double CAP_Value,CAP[20];
    //闭合相应继电器
		Relay_Drive (Item[Num].IO_CTL,SET );
		delay_ms (Item[Num].Time+1); 
		if(Fixture.Mode  == Auto_Test_Mode){
				for ( i = 0 ;i < 30 ; i ++){
					CAP_Value = Read_pf_Cap_Value(Num,0);
					if(CAP_Value > Item[Num].LSL&& CAP_Value < Item[Num].USL ){
							CAP[CNT] = CAP_Value;
							CNT ++;
					}else{
							Item_Data[Num].Value = CAP_Value;
							CNT = 0;
					}
					if(CNT == 5){
							Item_Data[Num].Value = Average_Fun (CAP,5);
							break ;
					}
				}
				if(TestConfig.pF_Cap  == ENABLE || Fixture.Mode  == Step_Test_Mode ){
					cyc4or3run ();
					lcd_printf("   %7.1f%s    ",Item_Data[Num].Value,Item[Num].Unit );
				}
		}
		if(Fixture.Mode  == Step_Test_Mode){
				for( i = 0; i < 10; i ++)
						CAP[i]  = Read_pf_Cap_Value(Num,0);
				Item_Data[Num].Value = Average_Fun(CAP,10);
				cyc4or3run ();
				lcd_printf("   %7.1f%s    ",Item_Data[Num].Value,Item[Num].Unit );
				if(left_start_key == 1 || right_start_key == 1 ){
					if(left_start_key == 1 || right_start_key == 1 ){
							while(left_start_key ==1&&right_start_key ==1){ //单步模式下，动态显示电容值
									for( i = 0; i < 12; i ++)
											CAP[i]  = Read_pf_Cap_Value(Num,0);
										Item_Data[Num].Value = Average_Fun(CAP,12);
										lcdpos(lcdcon-1,0);  
										lcd_printf("   %7.1f%s    ",Item_Data[Num].Value,Item[Num].Unit );
							}
							startkeywait(1,1);
					}
				}
		}
		lcdpos (lcdcon-1,14);
		if(Item_Data[Num].Value > Item[Num].LSL && Item_Data[Num].Value < Item[Num].USL ){
				if(TestConfig.pF_Cap  == ENABLE || Fixture.Mode  == Step_Test_Mode ){
						lcdpos(lcdcon-1,14);  
						lcd_printf ("OK"); 
				}
				CAP_Test_Reault = True ;
		}else{
				if(Fixture.Mode == Auto_Test_Mode && TestConfig.pF_Cap  == DISABLE ){
						cyc4or3run ();
						lcd_printf ("%s",Item[Num].Name);
						cyc4or3run ();
						lcd_printf  ("  %7.3f%s  ",Item_Data[Num].Value,Item[Num].Unit);
				}		
				CAP_Test_Reault = False;
				lcd_printf("NG");
		}
	 //闭合相应继电器
		Relay_Drive (Item[Num].IO_CTL,RESET );
		return CAP_Test_Reault;
}

/*********************************************************************************************
	* File Name     : Type_pF_Cap_Test_Fun
	* Description   : Type_pF_Cap_Test_Fun
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 14-OCT-2019
*********************************************************************************************/
uint8_t  Type_pF_Cap_Test_Fun (uint16_t *TestStepN, uint16_t Total_Num,uint16_t *Step_Number_buffer){
		u8 Total_CAP_Test_Result = True; 
		uint16_t j,Item_Step_Number = 0;
		if(Total_Num == 0)
			return True;
		
			
		if(		TestConfig.pF_Cap  == DISABLE && Fixture.Mode  == Auto_Test_Mode  ){
			 (*TestStepN) ++;
				cyc4or3run ();
			  lcd_printf ("%d>%s",*TestStepN,"pF CAP ...   ");
		}		
//		cyc4or3run ();
//		lcd_printf ("pF test start ..");
		Close_All_Point ();
		for( j = 0; j < Total_Num ; j ++){
			 Item_Step_Number = Step_Number_buffer[j];
				if(TestConfig.pF_Cap  == ENABLE || Fixture.Mode  == Step_Test_Mode ){
					 (*TestStepN)++;
					 cyc4or3run();
					 lcd_printf ("%d>%s",*TestStepN,Item[Item_Step_Number].Name);
				}
			 Item_Data[Item_Step_Number].Status = pF_CAP_Tests(Item_Step_Number);
			 if(Fixture.Mode  == Auto_Test_Mode && Item_Data[Item_Step_Number].Status == False){
					Total_CAP_Test_Result |= False ;	
				 if(TestConfig.FAIL_continue  == ENABLE )
					continue ;
				 else
					break ;
			 }
			 if(Fixture.Mode  == Step_Test_Mode && Item_Data[Item_Step_Number].Status == False){
					cyc4or3run ();
					lcd_printf ("L:复测  R:下一步");
					lcdcon -- ;
					Clear_buffer(3);
					if (step_test_mode_get_key () == Left_Button_Pressed_Down ){
						j --;
						Item_Step_Number --;
						(*TestStepN) --;
						continue ;
					}
					Total_CAP_Test_Result |= False ;	
				}
		}	
		
		if(TestConfig.pF_Cap  == DISABLE && Fixture.Mode  == Auto_Test_Mode && Total_CAP_Test_Result== True ){
			lcdpos(lcdcon -1,14);
			lcd_printf ("OK");
		}
		
		delay_ms (50);
//	  cyc4or3run ();
//		lcd_printf ("pF test end ..");
		return Total_CAP_Test_Result ;	
}




/*********************************************************************************************
	* File Name     : Type_pF_Cap_Test_Fun
	* Description   : Type_pF_Cap_Test_Fun
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 14-OCT-2019
*********************************************************************************************/
void pF_Capacitor_Calibration( uint8_t Num){
		uint8_t i;
		double CAP[20];
		Relay_Drive (Item[Num].IO_CTL,SET );
		delay_ms (Item[Num].Time+1); 
		for( i = 0; i < 10; i ++)
			CAP[i]  = LCR_Test(__Capacitor,0,1);
		Item_Data[Num].Value = Average_Fun(CAP,10);
		cyc4or3run ();
		lcd_printf("%s=%7.3f%s    ",	Item[Num].Name,Item_Data[Num].Value,Item[Num].Unit );
		while(left_start_key ==1&&right_start_key ==1){ //单步模式下，动态显示电容值
			for( i = 0; i < 10; i ++)
					CAP[i]  = LCR_Test(__Capacitor,0,1);
			Item_Data[Num].Value = Average_Fun(CAP,10);
			lcdpos (lcdcon -1,0);
			lcd_printf("%s=%7.3f%s    ",	Item[Num].Name,Item_Data[Num].Value,Item[Num].Unit );
		}
		startkeywait(1,1);
		Item_Data[Num].offset = 	Item_Data[Num].Value - Item[Num].STD_Value;
		if(Item_Data[Num].offset > 0.0)
			Item_Data[Num].offset = Item_Data[Num].offset;
		else
			Item_Data[Num].offset = Item_Data[Num].Value;
		Relay_Drive (Item[Num].IO_CTL,RESET );
		delay_ms (Item[Num].Time+1); 
}
/*********************************************************************************************
	* File Name     : pF_Capacitor_Calibration
	* Description   : pF_Capacitor_Calibration
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 19-OCT-2019
*********************************************************************************************/
uint8_t  pF_Capacitor_Calibration_Fun(void){
		u8 j; 
		uint16_t Total_Num,Item_Step_Number = 0,buf[32];
		Total_Num = Get_Currennt_Type_CNT(Type_pF_Cap,buf,32 );
		if(Total_Num == 0){
			cyc4or3run ();
			lcd_printf ("无此项测试      ");
			return 1;
		}
		lcdreset ();
		cyc4or3run ();
		lcd_printf ("pF电容校准      ");
		Close_All_Point ();
		for( j = 0; j < Total_Num ; j ++){
			 Item_Step_Number = buf[j];
			 pF_Capacitor_Calibration(Item_Step_Number);	
		}
		Write_pF_Capacitor_offset();
		RevertStartupScreen();
		return  0;	
}
