#include "Insulation.h"
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
double Insulation_Test( uint16_t Num, double REF){
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
uint8_t Insulation_RES_Test(uint8_t Num,double REF){
	uint8_t CNT = 0,i = 0,Test_Result = True ;
	double Kohm = 0.0,TEST_KOhm[25];
	Open_Two_Point (COMC, Item[Num].Test_H,COMD,Item[Num].Test_L);
	Open_Two_Point (COMA, Item[Num].Src_H ,COMB,Item[Num].Src_L);
	delay_us (1+Item[Num].Time);
	if(Fixture.Mode  == Auto_Test_Mode ){
		for( i= 0 ; i < 200 ;i ++){			
				Kohm  = Insulation_Test(Num,REF);
				if(Kohm  > Item[Num].LSL && Kohm < (Item[Num].USL) ){
						TEST_KOhm[CNT] = Kohm;
						CNT ++; 
				}
				else{
						Item_Data[Num].Value = Kohm;
						CNT = 0;
						delay_us (10);	
				}
				if(CNT >= 5){
						Item_Data[Num].Value  = Average_Fun(TEST_KOhm,5);
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
					TEST_KOhm[i]  = Insulation_Test(Num,REF);				
			}
			Item_Data[Num].Value  = Average_Fun(TEST_KOhm,10);
			cyc4or3run ();
			lcd_printf  ("  %7.3f%s  ",Item_Data[Num].Value,Item[Num].Unit);
			if(left_start_key == 1 || right_start_key == 1 ){
					while(left_start_key ==1&&right_start_key ==1){ //?˙家Α???ボ?甧
						for( i = 0; i < 10; i ++){				
								TEST_KOhm[i]  = Insulation_Test(Num,REF);	
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
void Insulation_RES_TEST_SET(double Src_Volts,double REF_RES,uint8_t RATE){
		Relay_Drive ( K12_10R_Ref|K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,RESET);
		if(REF_RES == 10)
				Relay_Drive ( K12_10R_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,SET);
		else if(REF_RES == 1000)
			  Relay_Drive ( K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,SET);
		else if(REF_RES == 20000)
			  Relay_Drive ( K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,SET);
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
void Insulation_RES_TEST_RESET(void){
		Relay_Drive ( K12_10R_Ref|K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,RESET);
		DAC_Set_Vol(0,5,0);
		delay_ms(80);
}

