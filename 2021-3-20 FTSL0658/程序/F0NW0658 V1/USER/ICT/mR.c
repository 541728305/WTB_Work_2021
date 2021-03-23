#include "mR.h"
#include "lcd3033.h"
#include "test.h"
#include "os.h"
#include "global.h"
#include "delay.h"
#include "ad7176.h"
#include "Sup_Fun.h"
#include "other.h"
#include "analog_switch.h"
#include <string.h>
#include "base_Config.h"
#include "test_config.h"




/**********************************************************************************************************************
	* File Name     :  Res_4wire_Test
	* Description   :  电阻4线测函数，所用通道COMA,B ,D
  * Input         :  信号源高、低点（Source_H、L ），测试高、低点（Test_Pin_H、L），电阻标称值（Res_Standard_Value）
  * return        :  测试电阻值 26 48
	* Author        :  Morton
	* Date          :  2018/8/14
************************************************************************************************************************/
static  double  mohm_4wire_Test_Res(uint16_t Num){
		double  RES=0.0,Vrx = 0.0,Vref = 0.0;
		Read_AD7176_Average_Voltage_mV (AIN0 ,AIN4, 6, &Vref );  //加载在待测电阻两端
		Read_AD7176_Average_Voltage_mV (AIN1 ,AIN4, 6, &Vrx );  //加载在待测电阻两端
		if(Vref > 60.0 && Vrx < 3590.0 ){
				Read_AD7176_Average_Voltage_mV (AIN0 ,AIN1, 15, &Vref );  //加载在待测电阻两端
				delay_us (1);
				Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3, 15, &Vrx );  //加载在待测电阻两端
				if(Vrx == 0.0){
						Read_AD7176_Average_Voltage_mV (AIN3 ,AIN2, 15, &Vrx );  //加载在待测电阻两端
				}
				RES = Vrx/(Vref/10.0)*1.002;
				if(RES <=0.0001){
					RES = 0.0001;
				}
		}else {
				RES = 99.9;
		}
		if(strstr (Item[Num].Unit,"mohm"))
			RES *= 1000.0;
		
		
		#if defined Debug_Mode
				lcdreset ();
			//	lcdpos (0,0);   lcd_printf  ("Ref=%0.3lfR ",Ref_Res);
				lcdpos (1,0);   lcd_printf  ("Vx=%0.3lfmV  ",Vrx);
				lcdpos (2,0);   lcd_printf  ("Vrf=%0.3lfmV  ",Vref);
				lcdpos (3,0);   lcd_printf  ("Rs=%0.4lf%s ",RES,Item[Num].Unit);
		#endif
		return  RES ;
}



/*********************************************************************************************
	* File Name     : R_Isrc_Test_Fun
	* Description   : R_Isrc_Test_Fun
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 12-OCT-2019
*********************************************************************************************/
u8  Type_Isrc_Test_Fun(u16 *TestStepN , uint16_t Total_Num,uint16_t *Step_Number_buffer){
		u8 Test_Result = True,CNT = 0,t; 
		uint16_t j=0 ,Item_Step_Number = 0;
		char space[13];
		double Resistor,Test_Res[20];
		if(Total_Num == 0)
			return True;
		
		if(TestConfig.Isrc == DISABLE && Fixture.Mode  == Auto_Test_Mode  ){
			 (*TestStepN) ++;
				cyc4or3run ();
			  lcd_printf ("%d>%s",*TestStepN,"SUS  ...   ");
		}
		
		memset (space,0,13);
		memset (space,' ',12);
		Close_All_Point ();
		Enable_RES_Test_Analog_Switch();
		AD_Sample_Rate_Set(1);
		for( j =0;  j < Total_Num ;j ++){
		  	Item_Step_Number = Step_Number_buffer[j];
			
			  if(TestConfig.Isrc == ENABLE || Fixture.Mode  == Step_Test_Mode ){
						(*TestStepN) ++;
						cyc4or3run ();
						lcd_printf ("%d>%s%s",*TestStepN,Item[Item_Step_Number].Name,&space[strlen(Item[Item_Step_Number].Name)]);
				}
			
				Open_Four_Point ( COMA,Item[Item_Step_Number].Src_H ,
													COMB,Item[Item_Step_Number].Src_L,
													COMC,Item[Item_Step_Number].Test_H,
													COMD,Item[Item_Step_Number].Test_L
												);
				delay_us (1+Item[Item_Step_Number].Time);	
				CNT = 0; 
				for( t= 0 ; t < 100 ;t ++){			
						Resistor  = mohm_4wire_Test_Res(Item_Step_Number);
						if(Resistor  > Item[Item_Step_Number].LSL && Resistor < (Item[Item_Step_Number].USL) ){
								Test_Res[CNT] = Resistor;
								CNT ++; 
						}
						else{
								Item_Data[Item_Step_Number].Value  = Resistor;
								CNT = 0;
								delay_us (10);
						}
						if(CNT >= 8){
								Item_Data[Item_Step_Number].Value  = Average_Fun(Test_Res ,8);
								break ;
						}
		    }
				
				if(TestConfig.Isrc  == ENABLE || Fixture.Mode  == Step_Test_Mode ){
						cyc4or3run ();
						if( strstr(Item[Item_Step_Number].Unit,"mohm") )
							lcd_printf  ("   %6.1f%s  ",Item_Data[Item_Step_Number].Value,Item[Item_Step_Number].Unit  );
						else
							lcd_printf  ("   %6.4f%s  ",Item_Data[Item_Step_Number].Value,Item[Item_Step_Number].Unit  );
			  }
				
				if(Fixture.Mode  == Step_Test_Mode ) { 
						if(left_start_key == 1 || right_start_key == 1 ){
							while(left_start_key ==1&&right_start_key ==1){
									for( t =0 ; t < 20; t ++){
										Test_Res[t]= mohm_4wire_Test_Res(Item_Step_Number);
										delay_us(10);
									}
									Item_Data[Item_Step_Number].Value  = Average_Fun(Test_Res ,20);
									lcdpos(lcdcon-1,0);
									if( strstr(Item[Item_Step_Number].Unit,"mohm") )
										lcd_printf  ("   %6.1f%s  ",Item_Data[Item_Step_Number].Value,Item[Item_Step_Number].Unit  );
									else
										lcd_printf  ("   %6.4f%s  ",Item_Data[Item_Step_Number].Value,Item[Item_Step_Number].Unit  );
									delay_ms (50);
							}
							startkeywait (1,1);
						}
				}

				if(Item_Data[Item_Step_Number].Value > Item[Item_Step_Number].LSL && Item_Data[Item_Step_Number].Value < (Item[Item_Step_Number].USL)){
						Item_Data[Item_Step_Number].Status = True ;
					  if(TestConfig.Isrc == ENABLE || Fixture.Mode  == Step_Test_Mode ){
								lcdpos(lcdcon-1,14);
								lcd_printf  ("OK"); 
					  }						 
					
				}
				else {
						Item_Data[Item_Step_Number].Status = False ;
						if(Fixture.Mode == Auto_Test_Mode && TestConfig.Isrc == DISABLE ){
								cyc4or3run ();
								lcd_printf ("%s",Item[Item_Step_Number].Name);
								cyc4or3run ();
								lcd_printf  ("  %7.3f%s  ",Item_Data[Item_Step_Number].Value,Item[Item_Step_Number].Unit);
						}
					
					  lcdpos(lcdcon-1,14);
						lcd_printf  ("NG"); 
					
						if(Fixture.Mode  == Step_Test_Mode ){
								cyc4or3run ();
								lcd_printf ("L:复测  R:下一步");
								lcdcon -- ;
								Clear_buffer(3);
								if (step_test_mode_get_key () == Left_Button_Pressed_Down ){
									j --;
									(*TestStepN) --;
								}else{
									Test_Result |= False;
								}				
								continue ;
						}
						Test_Result |= False;
						if(TestConfig.FAIL_continue  == ENABLE )
							continue ;
						else
						  break ;
				}	
		}
		if(TestConfig.Isrc == DISABLE && Fixture.Mode  == Auto_Test_Mode && Test_Result== True ){
			lcdpos(lcdcon -1,14);
			lcd_printf ("OK");
		}
		Disable_RES_Test_Analog_Switch();
		Close_All_Point ();
		delay_ms (10);
		return Test_Result ; 
}

