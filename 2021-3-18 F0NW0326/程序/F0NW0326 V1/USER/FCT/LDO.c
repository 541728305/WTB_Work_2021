#include "ldo.h"
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
#include "string.h"
#include "test_config.h"
#include "base_Config.h"

/****************************************************************************************
	* File Name     : Diode_TEST_Relay_SET
	* Description   : Diode_TEST_Relay_SET
  * Input         : Num
  * return        : Test Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
****************************************************************************************/
void Volts_TEST_Relay_SET(double REF_RES,uint8_t RATE){
		Valve_Drive (MOVE14 ,SET );
		Relay_Drive (K1_Pull_Up|K14_1K_Ref|K12_10R_Ref|K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K15_Src_Choice,RESET);
		if(REF_RES == 10)
				Relay_Drive ( K1_Pull_Up|K12_10R_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K15_Src_Choice,SET);
		else if(REF_RES == 1000)
			  Relay_Drive ( K1_Pull_Up|K14_1K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K15_Src_Choice,SET);
		else if(REF_RES == 20000)
			  Relay_Drive (K1_Pull_Up| K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K15_Src_Choice,SET);
		AD_Sample_Rate_Set(RATE);
		delay_ms(80);
}
/****************************************************************************************
	* File Name     : Diode_TEST_Relay_SET
	* Description   : Diode_TEST_Relay_SET
  * Input         : Num
  * return        : Test Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
****************************************************************************************/
void DVolts_TEST_Relay_RESET(void){
		Relay_Drive ( K1_Pull_Up|K12_10R_Ref|K14_1K_Ref|K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K15_Src_Choice,RESET);
		DAC_Set_Vol (0,5,0);
		Valve_Drive (MOVE14 ,RESET );
		delay_ms(80);
}
/*********************************************************************************************
	* File Name     : Read_LDO_Volts
	* Description   : Read LDO Output Voltage,ADC AIN3-AIN4 
  * Input         : /
  * return        : Volts Unit(V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 25-June-2019
*********************************************************************************************/
static double  Read_LDO_Volts(uint16_t Num ){
//		uint8_t i;
		double Vref;//,Volts[20];
//		for(i = 0;i < 10; i ++){
//				Read_AD7176_Average_Voltage_mV(AIN2 ,AIN3, 10, &Volts[i]);
//		}
//		if(strstr(Item[Num].Unit ,"mV") == 0 )
//			Vref = Average_Fun (Volts,10)/1000.0;
	if(Item[Num].IO_CTL){
		Read_AD7176_Average_Voltage_mV(AIN2 ,AIN4, 20, &Vref);
	}else{
		Read_AD7176_Average_Voltage_mV(AIN2 ,AIN3, 20, &Vref);
	}
	if(strstr(Item[Num].Unit ,"mV") == 0 )
			Vref /= 1000.0;
		return Vref; //V
}
/*********************************************************************************************
	* File Name     : LDO_Volts_Test
	* Description   : Test LDO Output Voltage,ADC Sample by AIN2-AIN3 
  * Input         : Num 
  * return        : Test_Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
static uint8_t LDO_Volts_Test(uint16_t Num){
	uint8_t Test_Result = True,CNT = 0,i;
	double Volts,V[20];
	if(Item[Num].IO_CTL){
		Valve_Drive (Item[Num].IO_CTL ,SET);
		delay_ms (20);
	}else {
			DAC_Set_Vol(Item[Num].Src,1.0,0 );
			Open_Two_Point (COMA, Item[Num].Src_H , COMB,Item[Num].Src_L );
	}
	Open_Two_Point (COMC, Item[Num].Test_H, COMD,Item[Num].Test_L );
	delay_ms (10+Item[Num].Time);
	if(Fixture.Mode  == Auto_Test_Mode ){
		for( i= 0 ; i < 30 ;i ++){			
				Volts  = Read_LDO_Volts(Num);
				if(Volts  > Item[Num].LSL && Volts < (Item[Num].USL) ){
						V[CNT] = Volts;
						CNT ++; 
				}
				else{
						Item_Data[Num].Value = Volts;
						CNT = 0;
				}
				if(CNT >= 6){
						Item_Data[Num].Value  = Average_Fun(V,6);
						break ;
				}
				delay_us (5);			
		}
		cyc4or3run();
		lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );
	}
	if(Fixture.Mode  == Step_Test_Mode  ){
			for( i = 0; i < 10; i ++){				
					V[i]  = Read_LDO_Volts(Num);				
			}
			Item_Data[Num].Value  = Average_Fun(V,10);
			cyc4or3run ();
			lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );
			if(left_start_key == 1 || right_start_key == 1 )
			{
					while(left_start_key ==1&&right_start_key ==1){ 
						for( i = 0; i < 10; i ++){				
								V[i]  = Read_LDO_Volts(Num);				
						}
						Item_Data[Num].Value  = Average_Fun(V,10);
						lcdpos(lcdcon-1,0);  
						lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );
						delay_ms (10);
					}
					startkeywait(1,1);
			}
	}
	lcdpos(lcdcon-1,14);  
	if(Item_Data[Num].Value > Item[Num].LSL && Item_Data[Num].Value < Item[Num].USL){
		lcd_printf ("OK"); 
	}else{
		lcd_printf ("NG"); 
		Test_Result |= False;
	}
	if(Item[Num].IO_CTL){
		Valve_Drive (Item[Num].IO_CTL ,RESET);
		delay_ms (20);
	}
	return Test_Result;
}


uint8_t Type_Volts_Test_Fun(u16 *TestStepN,uint16_t Total_Num,uint16_t *Step_Number_buffer){
		uint8_t k=0,Total_Test_Result = True;
		double  Range_RES[3] = {10,1000,20000};
		uint8_t Range_Type[3] = {V_10R,V_1Kohm,V_20Kohm};
		uint16_t j=0,range[3] = {0,0,0},Item_Step_Number = 0;
		if(Total_Num == 0)
			return True;
		for( j = 0 ; j < Total_Num ; j ++){
			Item_Step_Number = Step_Number_buffer[j];
			if(Item[Item_Step_Number].Type == V_10R)
				range[0] ++;
			else if(Item[Item_Step_Number].Type == V_1Kohm)
				range[1] ++;
			else if(Item[Item_Step_Number].Type == V_20Kohm)
				range[2] ++;
		}
		for( k = 0; k < 3 ; k ++){
			if(range[k]){
				 Close_All_Point ();
				 Volts_TEST_Relay_SET(Range_RES[k],0);
				 for(j = 0 ; j < Total_Num ; j ++){
					 Item_Step_Number = Step_Number_buffer[j];
					 if(Item[Item_Step_Number].Type == Range_Type[k]){
							(*TestStepN) ++;
							cyc4or3run ();
							lcd_printf ("<%d> %s",*TestStepN,Item[Item_Step_Number].Name);
							Item_Data[Item_Step_Number].Status = LDO_Volts_Test(Item_Step_Number);		
							if(Fixture.Mode  == Auto_Test_Mode && Item_Data[Item_Step_Number].Status == False){
								Total_Test_Result |= False ;
								k = 3; //完全调出循环
								break ;
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
		DVolts_TEST_Relay_RESET();
		return Total_Test_Result ;	
}


