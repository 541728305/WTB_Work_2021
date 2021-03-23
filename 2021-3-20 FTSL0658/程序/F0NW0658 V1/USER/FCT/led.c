#include "led.h"
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
#include "fre.h"
#include "base_Config.h"
#include "test_config.h"

uint16_t ColorRatio_Num = 0;
const float ColorRatio[200]={
	2.839,2.786,2.802,3.06, 3.242,3.255,2.982,3.216,2.902,3.027,
	3.257,2.775,3.771,2.985,3.106,3.463,3.621,3.513,3.293,3.194,
	2.963,2.754,3.116,3.067,2.718,3.206,3.159,2.869,3.088,2.789,
	2.908,2.846,3.075,2.768,3.208,2.606,3.389,3.505,3.314,2.765,
	3.176,3.073,3.223,3.256,3.204,3.136,3.282,2.795,3.187,2.859,
	3.369,2.865,3.045,3.01, 3.316,2.73 ,3.154,3.498,2.81, 2.961,	
	2.735,2.757,2.891,3.229,3.103,2.94, 3.182,3.003,2.983,3.033,
	3.653,3.132,2.568,3.104,3.325,2.786,3.489,3.727,3.229,3.459,	
	2.753,3.006,3.089,2.734,2.886,3.253,2.865,2.827,3.002,3.269,
	2.802,2.538,2.823,3.309,3.058,2.717,2.782,3.675,3.426,3.002,
	3.618,2.917,2.832,2.849,2.755,3.577,3.377,2.912,2.554,2.687,	
	3.213,3.168,3.228,3.295,3.284,3.019,2.828,2.81, 3.093,2.781,
	2.996,3.17, 2.746,3.107,2.552,2.887,3.436,3.455,3.762,2.976,	
	3.045,2.866,2.709,2.733,3.289,2.884,3.102,3.111,3.184,3.244,
	2.556,2.595,2.677,3.547,3.301,3.197,2.781,3.447,2.839,3.461,	
	2.705,2.831,3.113,2.739,2.731,2.843,3.194,3.173,3.029,3.156,
	3.797,3.783,3.015,3.114,2.844,2.517,3.475,3.424,2.966,3.536,	
	2.939,3.236,3.02, 3.107,2.878,2.806,2.769,2.875,2.703,2.764,
	3.415,2.56, 2.789,3.476,3.758,2.659,3.428,2.783,3.566,3.139,	
	2.796,3.031,3.232,2.88, 3.181,3.095,2.966,3.217,2.954,3.195,

};
/*********************************************************************************************
	* File Name     : Read_LED_Vlots
	* Description   : Read_LED_Vlots 
  * Input         : ,
	* return        : Volts (V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
static  double  Read_LED_Vlots(void){
		uint8_t i;
		double Vref,Volts[20];
		for(i = 0;i < 10; i ++){
				Read_AD7176_Average_Voltage_mV(AIN2 ,AIN3, 10,&Volts[i]);
		}
		Vref = Average_Fun (Volts,10)/1000.0;
		return Vref; 	
}
/*********************************************************************************************
	* File Name     : LED_Forward_Test
	* Description   : LED_Forward_Test
  * Input         : Num
	* return        : Test_Result OK 0 !0
	* Version       : V1.0 
	* Author        : Morton 
	* Date          : 24-June-2019 
*********************************************************************************************/ 
uint8_t LED_Forward_Test( uint16_t *TestStepN ,uint8_t  Num ){
		u8 Test_Result = True,CNT = 0,i;
		double LED_VF = 0.0, Volts[10];
		if(TestConfig.LED   == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
				(*TestStepN) ++;
				cyc4or3run();
				lcd_printf ("%d>%s",*TestStepN,Item[Num].Name);
		}
		if(Fixture.Mode  == Auto_Test_Mode ){
				for( i= 0 ; i < 30 ;i ++){			
						LED_VF  = Read_LED_Vlots();
						if(LED_VF  > Item[Num].LSL && LED_VF < (Item[Num].USL) ){
								Volts[CNT] = LED_VF;
								CNT ++; 
						}
						else{
								Item_Data[Num].Value = LED_VF;
								CNT = 0;
						}
						if(CNT >= 10){
								Item_Data[Num].Value  = Average_Fun(Volts,10);
								break ;
						}
						delay_us (10);			
				}
				cyc4or3run();
				lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );
			}
			if(Fixture.Mode  == Step_Test_Mode  ){
				  delay_ms (1000);
					for( i = 0; i < 10; i ++){									
							Volts[i]  = Read_LED_Vlots();
							delay_ms (10);				
					}
					Item_Data[Num].Value  = Average_Fun(Volts,10);
					cyc4or3run ();
					lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );

//					if(left_start_key == 1 || right_start_key == 1 ){
//							while(left_start_key ==1&&right_start_key ==1){ 
//								for( i = 0; i < 10; i ++){				
//										Volts[i]  = Read_LED_Vlots();	
//										delay_us (10);
//								}
//								Item[Num].Value  = Average_Fun(Volts,10);
//								lcdpos(lcdcon-1,0);  
//								lcd_printf  ("  %7.3f%s   ",Item[Num].Value,Item[Num].Unit );
//								delay_ms (150);
//							}
//							startkeywait(1,1);
//					}
			}
			if(Item_Data[Num].Value > Item[Num].LSL && Item_Data[Num].Value < Item[Num].USL){
				if(TestConfig.LED    == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
						lcdpos(lcdcon-1,14);  
						lcd_printf ("OK"); 
				}
			}else{
				
				if(TestConfig.LED  == DISABLE  || Fixture.Mode  == Auto_Test_Mode  ){
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
	* File Name     : Read_Clolor_Percentage
	* Description   : Read_Clolor_Percentage
  * Input         : Color
	* return        : Percentage
	* Version       : V1.0 
	* Author        : Morton 
	* Date          : 24-June-2019 
*********************************************************************************************/
double Read_Clolor_Percentage( uint8_t Color){
		double  Percentage = 0.0,Total = 0.0;
		ColorRatio_Num ++;
		if(ColorRatio_Num > 197)
			ColorRatio_Num = 0;
		Percentage = Get_Color_Fre(Color,2,5)/ColorRatio[ColorRatio_Num];
		Total      = Get_Color_Fre(WHITE,2,5);
		if(Total > 5000)
				Percentage = Percentage/Total *100.0;
		else
				Percentage = 0.0;
		#if defined Debug_Mode
			cyc4or3run ();
			lcd_printf ("T = %5.0f",Total);
			cyc4or3run ();
			lcd_printf ("P = %5.0f",Percentage);
		#endif
		return  Percentage;
}
/*********************************************************************************************
	* File Name     : LED_light_Test
	* Description   : LED_light_Test
  * Input         : TestStepN ,Num
	* return        : Test_Result OK 0 !0
	* Version       : V1.0 
	* Author        : Morton 
	* Date          : 24-June-2019 
*********************************************************************************************/ 
uint8_t LED_light_Test( uint16_t *TestStepN ,uint8_t  Num, uint8_t Color){
		uint8_t  Test_Result = True ,j = 0,CNT = 0;
		double   Percentage = 0.0,Percentage_data[20];
		if(TestConfig.LED   == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
			(*TestStepN) ++;
			cyc4or3run();
			lcd_printf ("%d>%s",*TestStepN,Item[Num].Name);
		}
		if(Fixture.Mode  == Auto_Test_Mode ){
				CNT = 0;
				for( j= 0 ; j < 30 ;j ++){			
						Percentage = Read_Clolor_Percentage(Color);
						if(Percentage > Item[Num].LSL && Percentage < (Item[Num].USL) ){
							Percentage_data[CNT] = Percentage;
							CNT ++; 
						}
						else{
								Item_Data[Num].Value = Percentage;
								CNT = 0;
						}
						if(CNT >= 10){
								Item_Data[Num].Value  = Average_Fun(Percentage_data,10);
								break ;
						}
						delay_us (10);			
				}
				cyc4or3run();
				lcd_printf  ("  %7.1f%s   ",Item_Data[Num].Value,Item[Num].Unit );
		}
		if(Fixture.Mode  == Step_Test_Mode  ){				
			  delay_ms (1000);
				for( j = 0; j < 10; j ++){				
						Percentage_data[j]  = Read_Clolor_Percentage(Color);
						delay_ms (10);				
				}
				Item_Data[Num].Value  = Average_Fun(Percentage_data,10);
				cyc4or3run ();
				lcd_printf  ("  %7.1f%s   ",Item_Data[Num].Value,Item[Num].Unit );

//				if(left_start_key == 1 || right_start_key == 1 ){
//						while(left_start_key ==1&&right_start_key ==1){ 
//							for( j = 0; j < 10; j ++){				
//									Percentage_data[j]  = Read_Clolor_Percentage(Color);	
//									delay_us (10);
//							}
//							Item[Num].Value  = Average_Fun(Percentage_data,10);
//							lcdpos(lcdcon-1,0);  
//							lcd_printf  ("  %7.1f%s   ",Item[Num].Value,Item[Num].Unit );
//							delay_ms (150);
//						}
//						startkeywait(1,1);
//				}
		}
		if(Item_Data[Num].Value > Item[Num].LSL && Item_Data[Num].Value < Item[Num].USL){
				if(TestConfig.LED    == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
						lcdpos(lcdcon-1,14);  
						lcd_printf ("OK"); 
				}
			}else{
				
				if(TestConfig.LED  == DISABLE  || Fixture.Mode  == Auto_Test_Mode  ){
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
	* File Name     : LED_Forward_Vol_Color_Test
	* Description   : TestStepN,Num
  * Input         : Num
  * return        : Test Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
****************************************************************************************/
uint8_t LED_Forward_Vol_Color_Test(uint16_t  *TestStepN, uint16_t Num){
	uint8_t  Test_Result = True ;
	uint16_t Step_Num = 0;
	if(Fixture.Mode  == Auto_Test_Mode ){
		Test_Result |= LED_Forward_Test(TestStepN,Num);
		Item_Data[Num].Status = Test_Result;
		if(Test_Result == False && Fixture.Mode  ==Auto_Test_Mode ){
			return False ;
		}	
		Test_Result |= LED_light_Test (TestStepN,Num+1,RED);
		Item_Data[Num+1].Status = Test_Result;
		if(Test_Result == False && Fixture.Mode  ==Auto_Test_Mode )
			return False ;	

		Test_Result |= LED_light_Test (TestStepN,Num+2,GREEN );
		Item_Data[Num+2].Status = Test_Result;
		if(Test_Result == False && Fixture.Mode  ==Auto_Test_Mode )
			return False ;
		
		Test_Result |= LED_light_Test (TestStepN,Num+3,BLUE );
		Item_Data[Num+3].Status = Test_Result;
		if(Test_Result == False && Fixture.Mode  ==Auto_Test_Mode )
			return False ;
	}
	if(Fixture.Mode  == Step_Test_Mode ){
		Step_Num = *TestStepN;
		while(left_start_key ==1&&right_start_key ==1){
			Step_Num = *TestStepN;
			Item_Data[Num].Status    = LED_Forward_Test( &Step_Num,Num);
			Item_Data[Num+1].Status |= LED_light_Test ( &Step_Num,Num+1,RED);
			Item_Data[Num+2].Status |= LED_light_Test ( &Step_Num,Num+2,GREEN );
			Item_Data[Num+3].Status |= LED_light_Test ( &Step_Num,Num+3,BLUE );
		}
		*TestStepN +=4;
		startkeywait (1,1);
		Test_Result = (Item_Data[Num].Status|Item_Data[Num+1].Status|Item_Data[Num+2].Status|Item_Data[Num+3].Status);
	}
	return Test_Result;
}
/****************************************************************************************
	* File Name     : KOhm_RES_TEST_SET
	* Description   : relay¡¢ADC ¡¢DAC and so on  Hardware set
  * Input         : Num
  * return        : Test Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
****************************************************************************************/
void LED_Vsrc_TEST_SET(uint8_t Src, double Src_Volts,uint8_t RATE){
		if(Src)
			 Relay_Drive ( K12_10R_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,SET);
		else 
			 Relay_Drive ( K12_10R_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1,SET); 
		DAC_Set_Vol(Src_Volts,5.0,0);
		AD_Sample_Rate_Set(RATE);
		delay_ms(80);
}

/****************************************************************************************
	* File Name     : KOhm_RES_TEST_SET
	* Description   : relay¡¢ADC ¡¢DAC and so on  Hardware set
  * Input         : Num
  * return        : Test Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
****************************************************************************************/
void LED_Vsrc_TEST_RESET(void){
		Relay_Drive ( K12_10R_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,RESET);
		delay_ms(80);
}
/****************************************************************************************
	* File Name     : Type_LED_Test_Fun
	* Description   : Led check
  * Input         : TestStepN¡Total_Num 
  * return        : Total_LED_Test_Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 29-Nov-2019
****************************************************************************************/
uint8_t Type_LED_Test_Fun(u16 *TestStepN,uint16_t Total_Num,uint16_t *Step_Number_buffer){
	 uint8_t Total_LED_Test_Result = True;
		uint16_t j=0,Item_Step_Number = 0;
		if(Total_Num == 0)
			return True;
		LED_Vsrc_TEST_SET(0,4000,1);
		
		if(TestConfig.LED  == DISABLE &&Fixture.Mode  == Auto_Test_Mode ){
				(*TestStepN) ++;
				cyc4or3run ();
				lcd_printf ("%d>%s",*TestStepN,"LED ...   ");
		}
			
		for( j = 0 ; j < Total_Num; j = j + 4 ){
				Item_Step_Number = Step_Number_buffer[j]; 
			
				Open_Two_Point (COMA, Item[Item_Step_Number].Src_H,  COMB,Item[Item_Step_Number].Src_L );
				Open_Two_Point (COMC, Item[Item_Step_Number].Test_H, COMD,Item[Item_Step_Number].Test_L);	
			
				Item_Data[Item_Step_Number].Status = LED_Forward_Vol_Color_Test(TestStepN,Item_Step_Number);
				Total_LED_Test_Result |= Item_Data[Item_Step_Number].Status;
				if(Total_LED_Test_Result == False && Fixture.Mode  == Auto_Test_Mode ){
					if(TestConfig.FAIL_continue  == ENABLE )
						continue ;
					else
						break ;	
				}
				if(Fixture.Mode  == Step_Test_Mode && Item_Data[Item_Step_Number].Status == False){
						cyc4or3run ();
						lcd_printf ("L:¸´²â  R:ÏÂÒ»²½");
						lcdcon -- ;
						Clear_buffer(3);
						if (step_test_mode_get_key () == Left_Button_Pressed_Down ){
							j --;
							(*TestStepN) --;
							continue ;
						}
						Total_LED_Test_Result |= False ;
				 }
				
		}
		
		if(TestConfig.LED == DISABLE &&Fixture.Mode  == Auto_Test_Mode && Total_LED_Test_Result == True ){
				lcdpos(lcdcon -1,14);
				lcd_printf ("OK");
		}
		
		
		Close_All_Point ();
		LED_Vsrc_TEST_RESET();
		return Total_LED_Test_Result;
}





