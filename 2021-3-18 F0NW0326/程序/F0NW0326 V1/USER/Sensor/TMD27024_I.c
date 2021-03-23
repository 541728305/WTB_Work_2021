#include "TMD27024_I.h"
#include "lcd3033.h"
#include "myiic.h"
#include "net_iic.h"
#include "ad7176.h"
#include "global.h"
#include "delay.h"
#include "Sup_Fun.h"
#include "analog_switch.h"
#include "other.h"
#include "dac.h"
#include "sensor.h"
#include "test.h"
#include <string.h>

extern  ALS_Test_TypeDef  U2;
extern Sensor_Current_TypeDef TMD27024_Current[];
/*********************************************************************************************
	* File Name     : Read_Current
	* Description   : Read_Current
  * Input         : /
  * return        : Current Unit(uA)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
static double  Read_Sensor_Current(uint8_t Num ){
		uint8_t i;
		double Vref,Volts[20];
		for(i = 0;i < 10; i ++){
				Read_AD7176_Average_Voltage_mV(AIN0 ,AIN1, 10, &Volts[i]);
		}
		Vref = Average_Fun (Volts,10);
//		cyc4or3run ();
//		lcd_printf ("V=%0.3fmV ",Vref);
		if(strstr (TMD27024_Current[Num].Unit ,"uA"))
			Vref *= 1000.0;
		return (Vref)/10.0; //uA
}
/*********************************************************************************************
	* File Name     : Leakage_Current_Test
	* Description   : Leakage_Current_Test
  * Input         : Num 
  * return        : Test_Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 3-Oct-2019
*********************************************************************************************/
uint8_t TMD27024_LEDA_Current_Test(uint8_t Num){
	uint8_t Test_Result = True,CNT = 0,i;
	double Current,I[20];
	Open_Two_Point (COMA, U2.LEDA_Pin ,COMB,U2.GND_Pin );
	delay_ms (10+TMD27024_Current[Num].Time);
	if(testmode == Auto_Test_Mode ){
		for( i= 0 ; i < 30 ;i ++){			
				Current  = Read_Sensor_Current(Num);
				if(Current  > TMD27024_Current[Num].LSL && Current < (TMD27024_Current[Num].USL) ){
						I[CNT] = Current;
						CNT ++; 
				}
				else{
						TMD27024_Current[Num].Value = Current;
						CNT = 0;
				}
				if(CNT >= 10){
						TMD27024_Current[Num].Value  = Average_Fun(I,10);
						break ;
				}
				delay_us (10);			
		}
		cyc4or3run();
		lcd_printf  ("  %7.3f%s   ",TMD27024_Current[Num].Value,TMD27024_Current[Num].Unit );
	}
	if(testmode == Step_Test_Mode  ){
			for( i = 0; i < 10; i ++){				
					I[i]  = Read_Sensor_Current(Num);				
			}
			TMD27024_Current[Num].Value  = Average_Fun(I,10);
			cyc4or3run ();
			lcd_printf  ("  %7.3f%s   ",TMD27024_Current[Num].Value,TMD27024_Current[Num].Unit );
			if(left_start_key == 1 || right_start_key == 1 ){
					while(left_start_key ==1&&right_start_key ==1){ //?˙家Α???ボ?甧
						for( i = 0; i < 10; i ++){				
								I[i]  = Read_Sensor_Current(Num);				
						}
						TMD27024_Current[Num].Value  = Average_Fun(I,10);
						lcdpos(lcdcon-1,0);  
						lcd_printf  ("  %7.3f%s   ",TMD27024_Current[Num].Value,TMD27024_Current[Num].Unit );
						delay_ms (10);
					}
					startkeywait(1,1);
			}
	}
	lcdpos(lcdcon-1,14);  
	if(TMD27024_Current[Num].Value > TMD27024_Current[Num].LSL && TMD27024_Current[Num].Value < TMD27024_Current[Num].USL){
		lcd_printf ("OK"); 
	}else{
		lcd_printf ("NG"); 
		Test_Result |= False;
	}
	return Test_Result;
}
/*********************************************************************************************
	* File Name     : Current_Test
	* Description   : Current_Test
  * Input         : Num
	* return        : Test_Resut
	* Version       : V1.0
	* Author        : Morton
	* Date          : 3-Oct-2019
*********************************************************************************************/
uint8_t  TMD27024_Current_Test(uint8_t Num){
		uint16_t CNT = 0,i,Test_Resut = True;
		double I_Value = 0.0,Current[40]; 
		Net_IIC_Init();
		switch (Num){
			case 1:		Write_OneByteToDevice(AlS_Slave_Addr,0x80,0x00); 
					      Write_OneByteToDevice(AlS_Slave_Addr,0x80,0x00);  //	(PON=0, AEN=0, PEN=0)
								break ;
			case 2:		Write_OneByteToDevice(AlS_Slave_Addr,0x80,0x01); 
								Write_OneByteToDevice(AlS_Slave_Addr,0x80,0x01);  //	(PON=1, AEN=0, PEN=0)
								break ;
			case 3:  	Write_OneByteToDevice(AlS_Slave_Addr,0x80,0x03); 
								Write_OneByteToDevice(AlS_Slave_Addr,0x80,0x03);  //	(PON=AEN=1, PEN=0)
			          break ;
			default :  break;
			
		}
		delay_ms (10+TMD27024_Current[Num].Time);
		if(testmode == Auto_Test_Mode ){
				for ( i = 0; i < 300; i ++){
						I_Value = Read_Sensor_Current(Num ); // mV/ohm = mA*1000=uA
						if(I_Value >= TMD27024_Current[Num].LSL && I_Value < TMD27024_Current[Num].USL ){
								Current[CNT] = I_Value;
								CNT ++;
						}else{
								TMD27024_Current[Num].Value = I_Value;
						}
						if(CNT == 10){
								TMD27024_Current[Num].Value = Average_Fun (Current,10);
								break ;
						}
						delay_us (100);
				}
				cyc4or3run ();
				lcd_printf ("    %6.3fuA    ",TMD27024_Current[Num].Value);
		}
		if(testmode == Step_Test_Mode){
				for( i = 0 ;i < 20; i ++){
						Current[i] = Read_Sensor_Current(Num ); // mV/ohm = mA*1000=uA
						delay_us (10);
				}
				TMD27024_Current[Num].Value = Average_Fun (Current,20);
				cyc4or3run ();
				lcd_printf ("    %6.3fuA    ",TMD27024_Current[Num].Value);
				if(left_start_key == 1 || right_start_key == 1 ){
						while(left_start_key ==1&&right_start_key ==1){
								for( i = 0 ;i < 30; i ++){
										Current[i] = Read_Sensor_Current(Num ); // mV/ohm = mA*1000=uA
//										delay_us (1);
								}
								TMD27024_Current[Num].Value = Average_Fun (Current,30);
								lcdpos (lcdcon -1, 0);
								lcd_printf ("    %6.3fuA    ",TMD27024_Current[Num].Value);
								delay_ms (50);
						}
						startkeywait (1,1);
				}
		}
		lcdpos (lcdcon -1, 14);
		if( TMD27024_Current[Num].Value > TMD27024_Current[Num].LSL &&TMD27024_Current[Num].Value < TMD27024_Current[Num].USL){
				lcd_printf ("OK");
		}else{
				Test_Resut |= False;
				lcd_printf ("NG");
		}
		return Test_Resut;
}
/*********************************************************************************************
	* File Name     : Sensor_Cur_Test
	* Description   : Sensor_Cur_Test
  * Input         : *TestStepN
	* return        : Total_Test_Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 3-Oct-2019
*********************************************************************************************/
u8 TMD27024_Cur_Test(u16 *TestStepN){
		u8 i = 0,Total_Test_Result = True;
		Close_All_Point ();
		Valve_Drive (K1_Min_Ref|K2_Src_COMAB|K9_Ref_IN0_1|K10_Src_Choice, SET); 
		DAC_Set_Vol(0); 
		delay_ms (80);	
		for( i = 0;  TMD27024_Current[i].Name ; i ++){
			(*TestStepN) ++;
			cyc4or3run();
			lcd_printf ("<%d> %s",*TestStepN,TMD27024_Current[i].Name);
			DAC_Set_Vol(TMD27024_Current[i].Volts_Src ); 
			delay_ms (80);
			if( i == 0){
				TMD27024_Current[i].Status= TMD27024_LEDA_Current_Test(i); //just test LEDA PIN inptut Current 
			}					 
			else{
				if(i == 1){
					Open_Two_Point (COMA, U2.Vdd_Pin ,COMB,U2.GND_Pin );
					Open_Two_Point (COMC, U2.LEDA_Pin,COMD,U2.GND_Pin );
					Valve_Drive (K7_IIC_COMAB|K8_2V8_GND_COMCD, SET);  //Connect IIC interface change sensor to sleep .act .or idle mode 
					delay_ms (80);
				}
				TMD27024_Current[i].Status= TMD27024_Current_Test(i); 
			}
			if(testmode == Auto_Test_Mode && TMD27024_Current[i].Status == False){
					Total_Test_Result |= False ;	
					break ;
			}
			if(testmode == Step_Test_Mode && TMD27024_Current[i].Status == False){
				cyc4or3run ();
				lcd_printf ("L:复测  R:下一步");
				lcdcon -- ;
				Clear_buffer(3);
			if (step_test_mode_get_key () == Left_Button_Pressed_Down ){
				i --;
				continue ;
			}
			Total_Test_Result |= False ;	
			}		 
		}
		return Total_Test_Result ; 
}







