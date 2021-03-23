#include "diode.h"
#include "lcd3033.h"
#include "test.h"
#include "global.h"
#include "delay.h"
#include "ad7176.h"
#include "Sup_Fun.h"
#include "other.h"
#include "analog_switch.h"
#include "dac.h"
#include "string.h"
#include "test_config.h"
#include "base_Config.h"

/*********************************************************************************************
	* File Name     : Read_Diode_Volts
	* Description   : Read diode forward volts 
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
static  double  Read_Diode_Volts(uint16_t Num){
		double Vref = 0.0;
	  Read_AD7176_Average_Voltage_mV(AIN2 ,AIN3,15,&Vref);
		if(strstr( Item[Num].Unit ,"mV") == 0){
			Vref /= 1000.0;
		}
		return Vref; 
} 
/*********************************************************************************************
	* File Name     : Diode_Test
	* Description   : Diode_Test 
  * Input         : Num
	* return        : Test_Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
uint8_t Diode_Test( uint16_t Num){
	uint16_t Test_Result = True,i,CNT = 0;
	double Volts,Vd[20];
//	DAC_Set_Vol(Item[Num].Src  );
	Open_Two_Point (COMA, Item[Num].Src_H,  COMB,Item[Num].Src_L );
	Open_Two_Point (COMC, Item[Num].Test_H ,COMD,Item[Num].Test_L );
	delay_ms (1+Item[Num].Time);
	if(Fixture.Mode  == Auto_Test_Mode ){
		for( i= 0 ; i < 300 ;i ++){			
				Volts  = Read_Diode_Volts(Num);
				if(Volts  > Item[Num].LSL && Volts < (Item[Num].USL) ){
						Vd[CNT] = Volts;
						CNT ++; 
				}
				else{
						Item_Data[Num].Value = Volts;
						CNT = 0;
				}
				if(CNT >= 6){
						Item_Data[Num].Value  = Average_Fun(Vd,6);
						break ;
				}
			//	delay_us (10);			
		}
		if(TestConfig.Diode  == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
			cyc4or3run();
			lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );
		}

	}
	if(Fixture.Mode  == Step_Test_Mode  ){
			for( i = 0; i < 10; i ++){				
					Vd[i]  = Read_Diode_Volts(Num);
					delay_us (10);				
			}
			Item_Data[Num].Value  = Average_Fun(Vd,10);
			cyc4or3run ();
			lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );
			if(left_start_key == 1 || right_start_key == 1 ){
					while(left_start_key ==1&&right_start_key ==1){ //?˙家Α???ボ?甧
						for( i = 0; i < 10; i ++){				
								Vd[i]  = Read_Diode_Volts(Num);	
								delay_us (10);
						}
						Item_Data[Num].Value  = Average_Fun(Vd,10);
						lcdpos(lcdcon-1,0);  
						lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );
						delay_ms (50);
					}
					startkeywait(1,1);
			}
	}

	if(Item_Data[Num].Value > Item[Num].LSL && Item_Data[Num].Value < Item[Num].USL){
		if(TestConfig.Diode  == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
				lcdpos(lcdcon-1,14);  
				lcd_printf ("OK"); 
		}

	}else{
		if(TestConfig.Diode  == DISABLE  || Fixture.Mode  == Auto_Test_Mode  ){
				cyc4or3run ();
				lcd_printf ("%s",Item[Num].Name);
				cyc4or3run();
				lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );
		}
		lcdpos(lcdcon-1,14); 
		lcd_printf ("NG"); 
		Test_Result |= False;
		
	}
	return Test_Result;
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
void Diode_TEST_Relay_SET(double REF_RES,uint8_t RATE){
		Relay_Drive ( K12_10R_Ref|K14_1K_Ref|K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K15_Src_Choice,RESET);
		if(REF_RES == 10)
				Relay_Drive ( K12_10R_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K15_Src_Choice,SET);
		else if(REF_RES == 1000)
			  Relay_Drive ( K14_1K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K15_Src_Choice,SET);
		else if(REF_RES == 20000)
			  Relay_Drive ( K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K15_Src_Choice,SET);
		AD_Sample_Rate_Set(RATE);
		DAC_Set_Vol (1800,5.0,0);
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
void Diode_TEST_Relay_RESET(void){
		Relay_Drive (K9_K11_TVS| K12_10R_Ref|K14_1K_Ref|K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K15_Src_Choice,RESET);	
		DAC_Set_Vol (0,5.0,0);
		delay_ms(80);
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
u8 Type_Diode_Test_Fun(u16 *TestStepN, uint16_t  Total_Num,uint16_t *Step_Number_buffer){
		uint8_t k=0,Total_Test_Result = True;
		double  Range_RES[3] = {10,1000,20000};
		uint8_t Range_Type[3] = {D_10R,D_1Kohm,D_20Kohm};
		uint16_t j=0,range[3] = {0,0,0},Item_Step_Number = 0;
		if(Total_Num == 0)
			return True;
		
		if(TestConfig.Diode  == DISABLE &&Fixture.Mode  == Auto_Test_Mode ){
				(*TestStepN) ++;
				cyc4or3run ();
				lcd_printf ("%d>%s",*TestStepN,"Diode ...   ");
		}
		
		for( j = 0 ; j < Total_Num ; j ++){
			Item_Step_Number = Step_Number_buffer[j];
			if(Item[Item_Step_Number].Type == D_10R)
				range[0] ++;
			else if(Item[Item_Step_Number].Type == D_1Kohm)
				range[1] ++;
			else if(Item[Item_Step_Number].Type == D_20Kohm)
				range[2] ++;
		}
		for( k = 0; k < 3 ; k ++){
			if(range[k]){
				 Close_All_Point ();
				 Diode_TEST_Relay_SET(Range_RES[k],0);
				 for(j = 0 ; j < Total_Num ; j ++){
					 Item_Step_Number = Step_Number_buffer[j];
					 if(Item[Item_Step_Number].Type == Range_Type[k]){
						 
							if(TestConfig.Diode  == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
									(*TestStepN) ++;
									cyc4or3run ();
									lcd_printf ("%d>%s",*TestStepN,Item[Item_Step_Number].Name);
							}
							Item_Data[Item_Step_Number].Status = Diode_Test(Item_Step_Number);		
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
		if(TestConfig.Diode  == DISABLE &&Fixture.Mode  == Auto_Test_Mode && Total_Test_Result == True ){
				lcdpos(lcdcon -1,14);
				lcd_printf ("OK");
		}

		Diode_TEST_Relay_RESET();
		return Total_Test_Result ;	
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
void TVS_Diode_TEST_Relay_SET(double REF_RES,uint8_t RATE,double Volts){
		Relay_Drive ( K12_10R_Ref|K14_1K_Ref|K13_20K_Ref |K8_Src_COMAB|K9_K11_TVS|K15_Src_Choice,RESET);
		if(REF_RES == 10)
				Relay_Drive ( K12_10R_Ref |K8_Src_COMAB|K9_K11_TVS|K15_Src_Choice,SET);
		else if(REF_RES == 1000)
			  Relay_Drive ( K14_1K_Ref |K8_Src_COMAB|K9_K11_TVS|K15_Src_Choice,SET);
		else if(REF_RES == 20000)
			  Relay_Drive ( K13_20K_Ref |K8_Src_COMAB|K9_K11_TVS|K15_Src_Choice,SET);
		AD_Sample_Rate_Set(RATE);
		DAC_Set_Vol (Volts,5.0,0);
		delay_ms(80);
}

/*********************************************************************************************
	* File Name     : Read_Diode_Volts
	* Description   : Read diode forward volts 
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
static  double  Read_TVS_Diode_Volts(uint16_t Num){
		double Vref = 0.0;
	  Read_AD7176_Average_Voltage_mV(AIN0 ,AIN1,15,&Vref);
		if(strstr( Item[Num].Unit ,"mV") == 0){
			Vref /= 1000.0;
		}
		if(strstr( Item[Num].Name ,"-")){
			Vref *= (-1);
		}
		return Vref*6.0; 
}


/*********************************************************************************************
	* File Name     : TVS_Diode_Test
	* Description   : TVS_Diode_Test 
  * Input         : Num
	* return        : Test_Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 30-May-2020
*********************************************************************************************/
uint8_t TVS_Diode_Test( uint16_t Num){
	uint16_t Test_Result = True,i,CNT = 0;
	double Volts,Vd[20];
	Open_Two_Point (COMA, Item[Num].Src_H,  COMB,Item[Num].Src_L );
	Open_Two_Point (COMC, Item[Num].Test_H ,COMD,Item[Num].Test_L );
	delay_ms (1+Item[Num].Time);
	if(Fixture.Mode  == Auto_Test_Mode ){
		for( i= 0 ; i < 300 ;i ++){			
				Volts  = Read_TVS_Diode_Volts(Num);
				if(Volts  > Item[Num].LSL && Volts < (Item[Num].USL) ){
						Vd[CNT] = Volts;
						CNT ++; 
				}
				else{
						Item_Data[Num].Value = Volts;
						CNT = 0;
						delay_us (10);		
				}
				if(CNT >= 6){
						Item_Data[Num].Value  = Average_Fun(Vd,6);
						break ;
				}
		}
		if(TestConfig.TVS  == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
			cyc4or3run();
			lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );
		}

	}
	if(Fixture.Mode  == Step_Test_Mode  ){
			for( i = 0; i < 10; i ++){				
					Vd[i]  = Read_Diode_Volts(Num);
					delay_us (10);				
			}
			Item_Data[Num].Value  = Average_Fun(Vd,10);
			cyc4or3run ();
			lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );
			if(left_start_key == 1 || right_start_key == 1 ){
					while(left_start_key ==1&&right_start_key ==1){ //?˙家Α???ボ?甧
						for( i = 0; i < 10; i ++){				
								Vd[i]  = Read_TVS_Diode_Volts(Num);	
								delay_us (10);
						}
						Item_Data[Num].Value  = Average_Fun(Vd,10);
						lcdpos(lcdcon-1,0);  
						lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );
						delay_ms (50);
					}
					startkeywait(1,1);
			}
	}

	if(Item_Data[Num].Value > Item[Num].LSL && Item_Data[Num].Value < Item[Num].USL){
		if(TestConfig.TVS  == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
				lcdpos(lcdcon-1,14);  
				lcd_printf ("OK"); 
		}

	}else{
		if(TestConfig.TVS  == DISABLE  || Fixture.Mode  == Auto_Test_Mode  ){
				cyc4or3run ();
				lcd_printf ("%s",Item[Num].Name);
				cyc4or3run();
				lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );
		}
		lcdpos(lcdcon-1,14); 
		lcd_printf ("NG"); 
		Test_Result |= False;
		
	}
	return Test_Result;
}

/*********************************************************************************************
	* File Name     : Type_TVS_Test_Fun
	* Description   : Diode_Test  test voltage < 4000mV
  * Input         : uint16_t Total_Num,uint16_t *Step_Number_buffer
	* return        : Total_Test_Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 30-May-2020
*********************************************************************************************/
uint8_t Type_TVS_Test_Fun(u16 *TestStepN,uint16_t Total_Num,uint16_t *Step_Number_buffer){
		uint8_t k=0,Total_Test_Result = True;
		double  Range_RES[3] = {10,1000,20000};
		uint8_t Range_Type[3] = {TVS_10R,TVS_1Kohm,TVS_20Kohm};
		uint16_t j=0,range[3] = {0,0,0},Item_Step_Number = 0;
		if(Total_Num == 0)
			return True;

		if(TestConfig.TVS  == DISABLE &&Fixture.Mode  == Auto_Test_Mode ){
				(*TestStepN) ++;
				cyc4or3run ();
				lcd_printf ("%d>%s",*TestStepN,"TVS Diode ...   ");
		}
		
		for( j = 0 ; j < Total_Num ; j ++){
			Item_Step_Number = Step_Number_buffer[j];
			if(Item[Item_Step_Number].Type == TVS_10R)
				range[0] ++;
			else if(Item[Item_Step_Number].Type == TVS_1Kohm)
				range[1] ++;
			else if(Item[Item_Step_Number].Type == TVS_20Kohm)
				range[2] ++;
		}
		for( k = 0; k < 3 ; k ++){
			if(range[k]){
				 Close_All_Point ();
				 TVS_Diode_TEST_Relay_SET(Range_RES[k],0,12000);
				 for(j = 0 ; j < Total_Num ; j ++){
					 Item_Step_Number = Step_Number_buffer[j];
					 if(Item[Item_Step_Number].Type == Range_Type[k]){
						 
							if(TestConfig.TVS  == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
									(*TestStepN) ++;
									cyc4or3run ();
									lcd_printf ("%d>%s",*TestStepN,Item[Item_Step_Number].Name);
							}
							Item_Data[Item_Step_Number].Status = TVS_Diode_Test(Item_Step_Number);		
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
		if(TestConfig.TVS  == DISABLE &&Fixture.Mode  == Auto_Test_Mode && Total_Test_Result == True ){
				lcdpos(lcdcon -1,14);
				lcd_printf ("OK");
		}

		Diode_TEST_Relay_RESET();
		return Total_Test_Result ;	
}



