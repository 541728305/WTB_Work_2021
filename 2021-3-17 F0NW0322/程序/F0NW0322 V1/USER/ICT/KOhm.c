#include "kohm.h"
#include <string.h>
#include "ad7176.h"
#include "delay.h"
#include "other.h"
#include "lcd3033.h"
#include "global.h"
#include "analog_switch.h"
#include "dac.h"
#include "sup_fun.h"
#include "test.h"
#include <stdio.h>
#include "base_Config.h"
#include "test_config.h"
 
/****************************************************************************************
	* File Name     : Kohm_Test.s
	* Description   : Kohm_Test
  * Input         : REF
  * return        : RES
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
****************************************************************************************/
double Kohm_Test( uint16_t Num, double REF){
		double  RES=0.0,Vrx = 0.0,Vref = 0.0;
		Read_AD7176_Average_Voltage_mV (AIN0 ,AIN1, 6, &Vref );  //加载在待测电阻两端
		Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3, 6, &Vrx );  //加载在待测电阻两端
		delay_us (1);
		Read_AD7176_Average_Voltage_mV (AIN0 ,AIN1, 20, &Vref );  //加载在待测电阻两端
		Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3, 20, &Vrx );  //加载在待测电阻两端
		RES = Vrx/(Vref/REF);
		#if defined Debug_Mode
				lcdreset ();
				lcdpos (0,0);   lcd_printf  ("Ref=%0.3lfR ",Ref_Res);
				lcdpos (1,0);   lcd_printf  ("Vx=%0.3lfmV  ",Vrx);
				lcdpos (2,0);   lcd_printf  ("Vrf=%0.3lfmV  ",Vref);
				lcdpos (3,0);   lcd_printf  ("Rs=%0.3lfOhm ",RES);
		#endif
		if(strstr ( Item[Num].Unit , "Kohm")){
			RES /= 1000.0;
			if(RES>1000){
				RES = 999.99;
			}
		}else if(strstr ( Item[Num].Unit, "Mohm")){
			RES /= 1000000.0;
			if(RES>10){
				RES = 9.99;
			}
		}else	{
			if(RES>1000)
				RES = 999.99;
		} 
		return  RES ;
}
/*********************************************************************************************
	* File Name     : KOhm_RES_Test
	* Description   : KOhm Test function
  * Input         : Num
  * return        : Test Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
uint8_t KOhm_RES_Test(uint16_t Num,double REF){
	uint8_t CNT = 0,i = 0,Test_Result = True ;
	double Kohm = 0.0,TEST_KOhm[25];
	Open_Two_Point (COMC, Item[Num].Test_H,COMD,Item[Num].Test_L);
	Open_Two_Point (COMA, Item[Num].Src_H ,COMB,Item[Num].Src_L);
	delay_us (1+Item[Num].Time);
	if(Fixture.Mode  == Auto_Test_Mode ){
		for( i= 0 ; i < 100 ;i ++){			
				Kohm  = Kohm_Test(Num,REF);
				if(Kohm  > Item[Num].LSL && Kohm < (Item[Num].USL) ){
						TEST_KOhm[CNT] = Kohm;
						CNT ++; 
				}
				else{
						Item_Data[Num].Value = Kohm;
						CNT = 0;
						delay_us (10);	
				}
				if(CNT >= 8){
						Item_Data[Num].Value  = Average_Fun(TEST_KOhm,8);
						break ;
				}
		
		}
		if(TestConfig.Vsrc  == ENABLE || Fixture.Mode  == Step_Test_Mode ){
				cyc4or3run();
				lcd_printf  ("  %7.3f%s  ",Item_Data[Num].Value,Item[Num].Unit);
		}
	}
	if(Fixture.Mode  == Step_Test_Mode  ){
			for( i = 0; i < 10; i ++){				
					TEST_KOhm[i]  = Kohm_Test(Num,REF);				
			}
			Item_Data[Num].Value  = Average_Fun(TEST_KOhm,10);
			cyc4or3run ();
			lcd_printf  ("  %7.3f%s  ",Item_Data[Num].Value,Item[Num].Unit);
			if(left_start_key == 1 || right_start_key == 1 ){
					while(left_start_key ==1&&right_start_key ==1){ //?˙家Α???ボ?甧
						for( i = 0; i < 10; i ++){				
								TEST_KOhm[i]  = Kohm_Test(Num,REF);	
								delay_us (10);							
						}
						Item_Data[Num].Value  = Average_Fun(TEST_KOhm,10);
						lcdpos(lcdcon-1,0);  
						lcd_printf  ("  %7.3f%s  ",Item_Data[Num].Value,Item[Num].Unit);
						delay_ms (10);
					}
					startkeywait(1,1);
			}
	}

	if(Item_Data[Num].Value > Item[Num].LSL && Item_Data[Num].Value < Item[Num].USL){
		if(TestConfig.Vsrc  == ENABLE || Fixture.Mode  == Step_Test_Mode ){
				lcdpos(lcdcon-1,14);  
				lcd_printf ("OK"); 
		}
	}else{
		if(Fixture.Mode == Auto_Test_Mode && TestConfig.Vsrc  == DISABLE ){
				cyc4or3run ();
				lcd_printf ("%s",Item[Num].Name);
				cyc4or3run ();
			  lcd_printf  ("  %7.3f%s  ",Item_Data[Num].Value,Item[Num].Unit);
		}
		lcdpos(lcdcon-1,14);  
		lcd_printf ("NG"); 
		Test_Result |= False;
	}
	return Test_Result;
}
/****************************************************************************************
	* File Name     : KOhm_RES_TEST_SET
	* Description   : relay、ADC 、DAC and so on  Hardware set
  * Input         : Num
  * return        : Test Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
****************************************************************************************/
void KOhm_RES_TEST_SET(double Src_Volts,double REF_RES,uint8_t RATE){
		Relay_Drive (  K1_Pull_Up|K12_10R_Ref|K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,RESET);
		if(REF_RES == 10)
				Relay_Drive (  K1_Pull_Up|K12_10R_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,SET);
		else if(REF_RES == 1000)
			  Relay_Drive (  K1_Pull_Up|K14_1K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,SET);
		else if(REF_RES == 20000)
			  Relay_Drive (  K1_Pull_Up|K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,SET);
		DAC_Set_Vol(Src_Volts,5,0);
		AD_Sample_Rate_Set(RATE);
		delay_ms(80);
}
/****************************************************************************************
	* File Name     : KOhm_RES_TEST_RESET
	* Description   : KOhm_RES_TEST_RESET
  * Input         : Num
  * return        : Test Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
****************************************************************************************/
void KOhm_RES_TEST_RESET(void){
		Relay_Drive (  K1_Pull_Up|K12_10R_Ref|K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,RESET);
		DAC_Set_Vol(0,5,0);
		delay_ms(80);
}
/*********************************************************************************************
	* File Name     : Read_Toatl_Item_Num
	* Description   : Read_Toatl_Item_Num
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 12-OCT-2019
*********************************************************************************************/
uint8_t Type_Vsrc_Test_Fun(u16 *TestStepN, uint16_t Total_Num,uint16_t *Step_Number_buffer){
		uint8_t k=0,Total_Test_Result = True;
		double  Range_RES[3] = {10,1000,20000};
		uint8_t Range_Type[3] = {R_Vsrc_10ohm,R_Vsrc_1Kohm,R_Vsrc_20Kohm};
		uint16_t j=0, range[3] = {0,0,0},Item_Step_Number = 0;
		if(Total_Num == 0)
			return True;
		if(TestConfig.Vsrc  == DISABLE && Fixture.Mode  == Auto_Test_Mode  ){
			(*TestStepN) ++;
				cyc4or3run ();
				lcd_printf ("%d>%s",*TestStepN,"Short ...      ");	
		}
		
		for( j = 0 ; j < Total_Num ; j ++){
			Item_Step_Number = Step_Number_buffer[j];
			if(Item[Item_Step_Number].Type == R_Vsrc_10ohm)
				range[0] ++;
			else if(Item[Item_Step_Number].Type == R_Vsrc_1Kohm)
				range[1] ++;
			else if(Item[Item_Step_Number].Type == R_Vsrc_20Kohm)
				range[2] ++;
		}
		for( k = 0; k < 3 ; k ++){
				if(range[k]){
				 Close_All_Point ();
				 KOhm_RES_TEST_SET(1000,Range_RES[k],1);
				 for(j = 0 ; j < Total_Num ; j ++){
					 Item_Step_Number = Step_Number_buffer[j];
					 if(Item[Item_Step_Number].Type == Range_Type[k]){
							if(TestConfig.Vsrc  == ENABLE || Fixture.Mode  == Step_Test_Mode ){
								(*TestStepN) ++;
								 cyc4or3run ();
								 lcd_printf ("%d>%s",*TestStepN,Item[Item_Step_Number].Name);
							}
							Item_Data[Item_Step_Number].Status = KOhm_RES_Test(Item_Step_Number,Range_RES[k]);		
							if(Fixture.Mode  == Auto_Test_Mode && Item_Data[Item_Step_Number].Status == False){
								Total_Test_Result |= False ;
								if(TestConfig.FAIL_continue  == ENABLE )
									continue ;
								else{																			
									k = 3; //完全调出循环
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
				}
			}	
		}
		Close_All_Point ();
		KOhm_RES_TEST_RESET();
		if(TestConfig.Vsrc  == DISABLE && Fixture.Mode  == Auto_Test_Mode && Total_Test_Result== True ){
			lcdpos(lcdcon -1,14);
			lcd_printf ("OK");
		}
		return Total_Test_Result ; 
}
