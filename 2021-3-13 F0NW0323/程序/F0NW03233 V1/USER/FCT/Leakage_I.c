#include "leakage_I.h"
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
                                                       

/*********************************************************************************************
	* File Name     : Read_Current
	* Description   : Read_Current
  * Input         : /
  * return        : Current Unit(uA)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
static double  Read_Current(uint16_t Num, double REF ){
		uint8_t i;
		double Cur = 0.0,Vref,Volts[20];
		for(i = 0;i < 10; i ++){
				Read_AD7176_Average_Voltage_mV(AIN0 ,AIN1, 10, &Volts[i]);
		}
		Vref = Average_Fun (Volts,10);
		Cur = (Vref)/REF; //mV/ohm=mA
		if( strstr(Item [Num].Unit,"uA"))
			Cur *= 1000.0;
		return Cur;
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
void Cur_TEST_Relay_SET(double REF_RES,uint8_t RATE){
		Relay_Drive ( K12_10R_Ref|K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,RESET);
		if(REF_RES == 10)
				Relay_Drive ( K12_10R_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,SET);
		else if(REF_RES == 1000)
			  Relay_Drive ( K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,SET);
		else if(REF_RES == 20000)
			  Relay_Drive ( K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,SET);
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
void Cur_TEST_Relay_RESET(void){
		Relay_Drive ( K12_10R_Ref|K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,RESET);
		DAC_Set_Vol(0,5,0);
		delay_ms(80);
}
/*********************************************************************************************
	* File Name     : Leakage_Current_Test
	* Description   : Leakage_Current_Test
  * Input         : Num 
  * return        : Test_Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
static uint8_t Leakage_Current_Test(uint16_t Num, double REF){
	uint8_t Test_Result = True,CNT = 0,i;
	double Current,I[20];
	DAC_Set_Vol(Item[Num].Src,5,0);
	Open_Two_Point (COMA, Item[Num].Src_H,COMB,Item[Num].Src_L);
	delay_ms (10+Item[Num].Time);
	if(Fixture.Mode  == Auto_Test_Mode ){
		for( i= 0 ; i < 30 ;i ++){			
				Current  = Read_Current( Num ,REF);
				if(Current  > Item[Num].LSL && Current < (Item[Num].USL) ){
						I[CNT] = Current;
						CNT ++; 
				}
				else{
						Item_Data[Num].Value = Current;
						CNT = 0;
				}
				if(CNT >= 10){
						Item_Data[Num].Value  = Average_Fun(I,10);
						break ;
				}
				delay_us (10);			
		}
		cyc4or3run();
		lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );
	}
	if(Fixture.Mode  == Step_Test_Mode  ){
			for( i = 0; i < 10; i ++){				
					I[i]  =  Read_Current( Num ,REF);
					delay_us (10);
			}
			Item_Data[Num].Value  = Average_Fun(I,10);
			cyc4or3run ();
			lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );
			if(left_start_key == 1 || right_start_key == 1 ){
					while(left_start_key ==1&&right_start_key ==1){ //?˙家Α???ボ?甧
						for( i = 0; i < 10; i ++){				
								I[i]  = Read_Current( Num ,REF);	
						}
						Item_Data[Num].Value  = Average_Fun(I,10);
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
	return Test_Result;
}
///*********************************************************************************************
//	* File Name     : Leakage_Current_Test_Fun
//	* Description   : Test IC  Leakage Current
//  * Input         : *TestStepN Step Number
//  * return        : Test Result
//	* Version       : V1.0
//	* Author        : Morton
//	* Date          : 24-June-2019
//*********************************************************************************************/
//uint8_t Leakage_Current_Test_Fun(u16 *TestStepN){
//		u8 i,Total_Test_Result = True; 
//		Close_All_Point ();
//		Relay_Drive ( K13_20K_Ref |K8_Src_COMAB|K10_Ref_IN0_1|K15_Src_Choice,SET);
//		AD_Sample_Rate_Set(1);
//		delay_ms(80);
//		for(i = 0 ; Leakage_I[i].Name ; i ++){
//			 (*TestStepN) ++;
//			 cyc4or3run();
//			 lcd_printf ("<%d> %s",*TestStepN,Leakage_I[i].Name);
//			 Leakage_I[i].Status  = Leakage_Current_Test(i);
//			 if(Fixture.Mode  == Auto_Test_Mode && Leakage_I[i].Status == False){
//				 	Total_Test_Result |= False;
//					break ;
//			 }
//			 if(Fixture.Mode  == Step_Test_Mode && Leakage_I[i].Status == False){
//	//				cyc4or3run ();
//	//				lcd_printf ("U:%g",Max_CAP[Num].USL );
//	//				lcdpos (lcdcon-1,8);
//	//				lcd_printf ("L:%g",Max_CAP[Num].LSL);
//					cyc4or3run ();
//					lcd_printf("PIN (%d, %d)   ",Leakage_I[i].H_Pin ,Leakage_I[i].L_Pin);
//					cyc4or3run ();
//				 	lcd_printf ("L:复测  R:下一步");
//					lcdcon -- ;
//					Clear_buffer(3);
//					if (step_test_mode_get_key () == Left_Button_Pressed_Down ){
//						i --;
//						continue ;
//					}
//					Total_Test_Result |= False;
//				}
//		}
//	  Relay_Drive ( K13_20K_Ref |K8_Src_COMAB|K10_Ref_IN0_1|K15_Src_Choice,RESET);
//		DAC_Set_Vol(0);
//		Close_All_Point ();
//		delay_ms (10);
//		return Total_Test_Result ; 
//}
uint8_t Type_Current_Test_Fun(u16 *TestStepN,uint16_t Total_Num,uint16_t *Step_Number_buffer){
		uint8_t k=0,Total_Test_Result = True;
		double  Range_RES[3] = {10,1000,20000};
		uint8_t Range_Type[3] = {I_10R,I_1Kohm,I_20Kohm};
		uint16_t j=0,range[3] = {0,0,0},Item_Step_Number = 0;
		if(Total_Num == 0)
			return True;
		for( j = 0 ; j < Total_Num ; j ++){
			Item_Step_Number = Step_Number_buffer[j];
			if(Item[Item_Step_Number].Type == I_10R)
				range[0] ++;
			else if(Item[Item_Step_Number].Type == I_1Kohm)
				range[1] ++;
			else if(Item[Item_Step_Number].Type == I_20Kohm)
				range[2] ++;
		}
		for( k = 0; k < 3 ; k ++){
				if(range[k]){
				 Cur_TEST_Relay_SET(Range_RES[k],1);
				 for(j = 0 ; j < Total_Num ; j ++){
					 Item_Step_Number = Step_Number_buffer[j];
					 if(Item[Item_Step_Number].Type == Range_Type[k]){
							(*TestStepN) ++;
							cyc4or3run ();
							lcd_printf ("<%d> %s",*TestStepN,Item[Item_Step_Number].Name);
							Item_Data[Item_Step_Number].Status = Leakage_Current_Test(Item_Step_Number,Range_RES[k]);		
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
		Cur_TEST_Relay_RESET();
		return Total_Test_Result ;
}


