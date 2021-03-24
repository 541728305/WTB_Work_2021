#include "switch.h"
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
#include "os.h"
#include <string.h>
#include "test_config.h"
#include "base_Config.h"
/******************************************************************************
	* File Name     : Res_4wire_Test
	* Description   : 读取两线测试电阻值
  * Input         : 无
  * return        : 无
	* Author        : Morton
	* Date          : 2016.12.6
******************************************************************************/
double  SW_Res_4wire_Test( uint16_t Num,double REF){
		double  RES=0.0,Vrx = 0.0,Vref = 0.0;
		Read_AD7176_Average_Voltage_mV (AIN0 ,AIN4, 6, &Vref );  //加载在待测电阻两端
		Read_AD7176_Average_Voltage_mV (AIN1 ,AIN4, 6, &Vrx );  //加载在待测电阻两端

		Read_AD7176_Average_Voltage_mV (AIN0 ,AIN1, 25, &Vref );  //加载在待测电阻两端
		delay_us (1);
		Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3, 25, &Vrx );  //加载在待测电阻两端
		if(Vrx == 0.0){
				Read_AD7176_Average_Voltage_mV (AIN3 ,AIN2, 15, &Vrx );  //加载在待测电阻两端
		}
		RES = Vrx/(Vref/REF)*1.002;

		if(strstr (Item[Num].Unit,"Kohm"))
		{
			RES /= 1000.0;
			if(RES > 999.99)
				RES = 999.99;
		}else if(strstr (Item[Num].Unit,"Mohm"))
		{
			RES /= 1000000.0;
			if(RES > 9.99)
				RES = 9.99;
		}else{
			if(RES > 999)
				RES = 999;
			
		}
		
		#if defined Debug_Mode
				lcdreset ();
				lcdpos (0,0);   lcd_printf  ("Ref=%0.3lfR ",Ref_Res);
				lcdpos (1,0);   lcd_printf  ("Vx=%0.3lfmV  ",Vrx);
				lcdpos (2,0);   lcd_printf  ("Vrf=%0.3lfmV  ",Vref);
				lcdpos (3,0);   lcd_printf  ("Rs=%0.3lfOhm ",RES);
		#endif
		return  RES ;
}
/*********************************************************************************************
	* File Name     : Switch_ON_Test
	* Description   : Switch ON Status Test
  * Input         : TestStepN Step Number  Num Switch test item NO.
	* return        : Switch ON Test_Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
uint8_t Switch_ON_Test(uint16_t *TestStepN, uint16_t Num,double REF){
	uint8_t Test_Result = True,i,CNT = 0;
	double R_ON,R[20];
	if(TestConfig.Switch   == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
		(*TestStepN) ++;
		cyc4or3run();
		lcd_printf ("%d>%s",*TestStepN,Item[Num].Name);
	}
	Valve_Drive (Item[Num].IO_CTL,SET );  //SET Switch Valve 
	delay_ms (Item[Num].Time+1);
	if(Fixture.Mode  == Auto_Test_Mode ){
		for( i= 0 ; i < 30 ;i ++){			
				R_ON  = SW_Res_4wire_Test(Num,REF);
				if(R_ON  > Item[Num].LSL && R_ON < (Item[Num].USL) ){
						R[CNT] = R_ON;
						CNT ++; 
				}
				else{
						Item_Data[Num].Value = R_ON;
						CNT = 0;
				}
				if(CNT >= 10){
						Item_Data[Num].Value  = Average_Fun(R,10);
						break ;
				}
				delay_us (10);			
		}
		if(TestConfig.Switch   == ENABLE){
			cyc4or3run();
			lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );
		}
	}
	if(Fixture.Mode  == Step_Test_Mode  ){
			for( i = 0; i < 10; i ++){				
					R[i]  = Res_4wire_Test();
					delay_us (10);				
			}
			Item_Data[Num].Value  = Average_Fun(R,10);
			cyc4or3run ();
			lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );
			if(left_start_key == 1 || right_start_key == 1 ){
					while(left_start_key ==1&&right_start_key ==1){ 
						for( i = 0; i < 10; i ++){				
								R[i]  = SW_Res_4wire_Test(Num,REF);	
								delay_us (10);
						}
						Item_Data[Num].Value  = Average_Fun(R,10);
						lcdpos(lcdcon-1,0);  
						lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );
						delay_ms (150);
					}
					startkeywait(1,1);
			}
	}

	if(Item_Data[Num].Value > Item[Num].LSL && Item_Data[Num].Value < Item[Num].USL){
		if(TestConfig.Switch   == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
				lcdpos(lcdcon-1,14);  
				lcd_printf ("OK"); 
		}
	}else{
		
		if(TestConfig.Switch  == DISABLE  || Fixture.Mode  == Auto_Test_Mode  ){
				cyc4or3run ();
				lcd_printf ("%s",Item[Num].Name);
				cyc4or3run();
				lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );
		}
		lcdpos(lcdcon-1,14); 
		lcd_printf ("NG"); 
		Test_Result |= False;	
	}
	Valve_Drive (Item[Num].IO_CTL  ,RESET );//RESET Switch Valve 
	delay_ms (Item[Num].Time+1);
	return Test_Result;
}
/*********************************************************************************************
	* File Name     : Switch_OFF_Test
	* Description   : Switch_OFF Status Test
  * Input         : TestStepN Step Number  Num Switch test item NO.
	* return        : Switch OFF Test_Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 25-June-2019
*********************************************************************************************/
uint8_t Switch_OFF_Test(uint16_t *TestStepN, uint16_t Num){
	uint8_t Test_Result = True,i,CNT = 0;
	double R_OFF,R[20];
	if(TestConfig.Switch   == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
		(*TestStepN) ++;
		cyc4or3run();
		lcd_printf ("%d>%s",*TestStepN,Item[Num].Name);
	}
  if(Fixture.Mode  == Auto_Test_Mode ){
		for( i= 0 ; i < 30 ;i ++){			
				R_OFF  = Res_2wire_Test_Mohm();
				if(R_OFF  > Item[Num].LSL && R_OFF < (Item[Num].USL) ){
						R[CNT] = R_OFF;
						CNT ++; 
				}
				else{
						Item_Data[Num].Value = R_OFF;
						CNT = 0;
				}
				if(CNT >= 10){
						Item_Data[Num].Value  = Average_Fun(R,10);
						break ;
				}
				delay_us (10);			
		}
		if(TestConfig.Switch   == ENABLE){
			cyc4or3run();
			lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );
		}
	}
	if(Fixture.Mode  == Step_Test_Mode  ){
			for( i = 0; i < 10; i ++){				
					R[i]  = Res_2wire_Test_Mohm();
					delay_us (10);				
			}
			Item_Data[Num].Value  = Average_Fun(R,10);
			cyc4or3run ();
			lcd_printf  ("  %7.3f%s   ",Item_Data[Num].Value,Item[Num].Unit );
			if(left_start_key == 1 || right_start_key == 1 ){
					while(left_start_key ==1&&right_start_key ==1){ //?˙家Α???ボ?甧
						for( i = 0; i < 10; i ++){				
								R[i]  = Res_2wire_Test_Mohm();	
								delay_us (10);
						}
						Item_Data[Num].Value  = Average_Fun(R,10);
						lcdpos(lcdcon-1,0);  
						lcd_printf  ("  %7.6f%s   ",Item_Data[Num].Value,Item[Num].Unit );
						delay_ms (50);
					}
					startkeywait(1,1);
			}
	}
	if(Item_Data[Num].Value > Item[Num].LSL && Item_Data[Num].Value < Item[Num].USL){
		if(TestConfig.Switch   == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
				lcdpos(lcdcon-1,14);  
				lcd_printf ("OK"); 
		}
	}else{
		
		if(TestConfig.Switch  == DISABLE  || Fixture.Mode  == Auto_Test_Mode  ){
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

///*********************************************************************************************
//	* File Name     : Switch_Test_Fun
//	* Description   : Switch Test Total test 3 status OFF-ON-OFF
//  * Input         : *TestStepN total test item step number
//	* return        : Total_Switch_Test_Result True Or Fasle
//	* Version       : V1.0
//	* Author        : Morton
//	* Date          : 25-June-2019
//*********************************************************************************************/
//uint8_t Switch_Test_Fun(uint16_t *TestStepN){
//	uint8_t Total_Switch_Test_Result = True,i = 0;
//	Vsrc_RES_TEST_SET(1000,1);
//	/****Switch OFF1 test *********/
//	for( i = 0 ;(Switch[i].Name&&strstr(Switch[i].Name,"OFF1")); i ++ ){
//			Open_Two_Point (COMA, Switch[i].H_P1 ,COMB,Switch[i].L_P1 );
//			Open_Two_Point (COMC, Switch[i].H_P2 ,COMD,Switch[i].L_P2 );		
//		  Switch[i].Status = Switch_OFF_Test(TestStepN,i);
//	  	Total_Switch_Test_Result |= Switch[i].Status;
//			if(Total_Switch_Test_Result == False && Fixture.Mode  == Auto_Test_Mode )
//				break ;	
//	}
//	/****Switch ON test *********/
//	if(Total_Switch_Test_Result == True || Fixture.Mode  == Step_Test_Mode){
//			Disable_RES_Test_Analog_Switch ();       
//			Enable_RES_Test_Analog_Switch();
//	}
//	for( i = 0 ;(Switch[i].Name&&strstr(Switch[i].Name,"ON")); i ++ ){
//			Open_Two_Point (COMA, Switch[i].H_P1 ,COMB,Switch[i].L_P1 );
//			Open_Two_Point (COMC, Switch[i].H_P2 ,COMD,Switch[i].L_P2 );	
//			Switch[i].Status = Switch_ON_Test(TestStepN,i+1);
//			Total_Switch_Test_Result |= Switch[i].Status;
//			if(Total_Switch_Test_Result == False && Fixture.Mode  == Auto_Test_Mode )
//				break ;		
//	}
//	/****Switch OFF2 test *********/
//	if(Total_Switch_Test_Result == True || Fixture.Mode  == Step_Test_Mode )
//			Vsrc_RES_TEST_SET(1000,1);
//	for( i = 0 ;(Switch[i].Name&&strstr(Switch[i].Name,"OFF2")); i ++ ){
//			Open_Two_Point (COMA, Switch[i].H_P1 ,COMB,Switch[i].L_P1 );
//			Open_Two_Point (COMC, Switch[i].H_P2 ,COMD,Switch[i].L_P2 );		
//		  Switch[i].Status = Switch_OFF_Test(TestStepN,i);
//	  	Total_Switch_Test_Result |= Switch[i].Status;
//			if(Total_Switch_Test_Result == False && Fixture.Mode  == Auto_Test_Mode )
//				break ;	
//	}
//	Close_All_Point ();
//	Disable_RES_Test_Analog_Switch ();       // Disable resistor test relay
//	return Total_Switch_Test_Result ;
//}
void SW_Vsrc_RES_TEST_SET(double Src_Volts,uint8_t RATE){
	  Relay_Drive (  K1_Pull_Up|K12_10R_Ref|K14_1K_Ref|K13_20K_Ref,RESET);
		Relay_Drive (  K1_Pull_Up|K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,SET);
		DAC_Set_Vol(Src_Volts,5.0,0);
		AD_Sample_Rate_Set(RATE);
		delay_ms(80);
}
void SW_Vsrc_RES_TEST_RESET(){
		Relay_Drive (  K1_Pull_Up|K12_10R_Ref|K14_1K_Ref|K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,RESET);
		delay_ms(80);
}
/******************************************************************************
* File Name     :  Enable_RES_Test_Analog_Switch
* Description   :  闭合电阻测试相关继电器
* Input         :  无
* return        :  无
* Author        :  Morton
* Date          :  2016.12.6
******************************************************************************/
void SW_Enable_RES_Test(uint16_t  REF){
    Relay_Drive ( K12_10R_Ref|K14_1K_Ref|K13_20K_Ref,RESET);	
		switch(REF){
			case 10    : Relay_Drive ( K12_10R_Ref,SET); break ;
			case 1000  : Relay_Drive ( K14_1K_Ref ,SET); break ;
			case 20000 : Relay_Drive ( K13_20K_Ref,SET); break ;
		}
		delay_ms(50);
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
uint8_t Type_Switch_Test_Fun(u16 *TestStepN,uint16_t Total_Num,uint16_t *Step_Number_buffer){
		uint8_t Total_Switch_Test_Result = True,Flag = RESET;
		uint16_t k=0,j=0,Item_Step_Number = 0,REF_RES[3]={1000,20000,10},SW_Type[3] = {SW_ON_1Kohm,SW_ON_20Kohm,SW_ON_10R};
		if(Total_Num == 0)
			return True;
		SW_Vsrc_RES_TEST_SET(1000,1);
		
		if(TestConfig.Switch  == DISABLE &&Fixture.Mode  == Auto_Test_Mode ){
				(*TestStepN) ++;
				cyc4or3run ();
				lcd_printf ("%d>%s",*TestStepN," Switch ...   ");
		}
		
		/****Switch OFF1 test *********/
		for( j = 0 ; j < Total_Num; j ++ ){
				Item_Step_Number = Step_Number_buffer[j]; 
				if(Item[Item_Step_Number].Type == SW_OFF1){
						Open_Two_Point (COMA, Item[Item_Step_Number].Src_H,  COMB,Item[Item_Step_Number].Src_L );
						Open_Two_Point (COMC, Item[Item_Step_Number].Test_H, COMD,Item[Item_Step_Number].Test_L);		
						Item_Data[Item_Step_Number].Status = Switch_OFF_Test(TestStepN,Item_Step_Number);
						Total_Switch_Test_Result |= Item_Data[Item_Step_Number].Status;

						if(Total_Switch_Test_Result == False && Fixture.Mode  == Auto_Test_Mode ){
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
									(*TestStepN) --;
									continue ;
								}
								Total_Switch_Test_Result |= False ;
						 }
				}
		}
		/****Switch ON test *********/
		if(Total_Switch_Test_Result == True || Fixture.Mode  == Step_Test_Mode){
				for( k=0;k < 3 ; k ++){		
					Flag = RESET;
					for( j = 0 ; j < Total_Num; j ++ ){
							Item_Step_Number = Step_Number_buffer[j]; 
							if(Item[Item_Step_Number].Type == SW_Type[k]){
								   if(Flag == RESET){
										 SW_Enable_RES_Test(REF_RES[k]);
										 Flag = SET;
									 }
                  								
									Open_Two_Point (COMA, Item[Item_Step_Number].Src_H,  COMB,Item[Item_Step_Number].Src_L );
									Open_Two_Point (COMC, Item[Item_Step_Number].Test_H, COMD,Item[Item_Step_Number].Test_L);		
									Item_Data[Item_Step_Number].Status = Switch_ON_Test(TestStepN,Item_Step_Number,REF_RES[k]);
									Total_Switch_Test_Result |= Item_Data[Item_Step_Number].Status;
								
									if(Total_Switch_Test_Result == False && Fixture.Mode  == Auto_Test_Mode ){
										if(TestConfig.FAIL_continue  == ENABLE )
											continue ;
										else{
											k=10;
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
										Total_Switch_Test_Result |= False ;
									}
							}
					}				
				}
		}
		/****Switch OFF2 test *********/
		if(Total_Switch_Test_Result == True || Fixture.Mode  == Step_Test_Mode ){ 
				SW_Vsrc_RES_TEST_SET(1000,1);
				for( j = 0 ; j < Total_Num; j ++ ){
						Item_Step_Number = Step_Number_buffer[j]; 
						if(Item[Item_Step_Number].Type == SW_OFF2){
								Open_Two_Point (COMA, Item[Item_Step_Number].Src_H,  COMB,Item[Item_Step_Number].Src_L );
								Open_Two_Point (COMC, Item[Item_Step_Number].Test_H, COMD,Item[Item_Step_Number].Test_L);		
								Item_Data[Item_Step_Number].Status = Switch_OFF_Test(TestStepN,Item_Step_Number);
								Total_Switch_Test_Result |= Item_Data[Item_Step_Number].Status;
							
								if(Total_Switch_Test_Result == False && Fixture.Mode  == Auto_Test_Mode ){
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
										(*TestStepN) --;
										continue ;
									}
									Total_Switch_Test_Result |= False ;
								}
						}
				}
		}
		if(TestConfig.Switch   == DISABLE && Fixture.Mode  == Auto_Test_Mode && Total_Switch_Test_Result == True ){
				lcdpos(lcdcon -1,14);
				lcd_printf ("OK");
		}
		Close_All_Point ();
		SW_Vsrc_RES_TEST_RESET ();       // Disable resistor test relay
		return Total_Switch_Test_Result;
}


