#include "block_check.h"
#include "lcd3033.h"
#include "ad7176.h"
#include "dac.h"
#include "delay.h"
#include "other.h"
#include "sup_fun.h"
#include "base_Config.h"
#include "analog_switch.h"
#include "reg.h"
/****************************************************************************************
	* File Name     : Kohm_Test.s
	* Description   : Kohm_Test
  * Input         : REF
  * return        : RES
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
****************************************************************************************/
double Block_RES_Check(double REF){
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
		if(RES>1000000)
				RES = 999999;		
		return  RES ;
}

/****************************************************************************************
	* File Name     : Block_Recognition_Fun
	* Description   : Block_Recognition_Fun
  * Input         : Num
  * return        : Test Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
****************************************************************************************/
uint8_t  Block_Recognition( uint8_t  Fixture_Num){
  uint8_t  Recognition_Result = False,i=0,CNT = 0;
 
	//**********************************NA*****0R*****3K****5.1K***10K*******
	double Fixture_RES_Value_LSL[5] = {0.0,  -1.0 , 2000.0, 4500.0,  9000.0  };
	double Fixture_RES_Value_USL[5] = {0.0, 500.0 , 4000.0, 6100.0, 11000.0  };
	
	double Kohm = 0.0 ,REF = 1000.0 ;
	
	if(Reg[Block_Check].Value  == DISABLE )
		return True ;
	lcdreset ();
	cyc4or3run ();
	lcd_printf ("工位-%d识别...   ",Fixture_Num);
	
	Open_Two_Point (COMC, Fixture.Check_PIN_H,COMD,Fixture.Check_PIN_L);
	Open_Two_Point (COMA, Fixture.Check_PIN_H,COMB,Fixture.Check_PIN_L);
	
	Relay_Drive ( K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,SET);
	DAC_Set_Vol(1000,5,0);
	AD_Sample_Rate_Set(0);
	delay_ms(80);
	
	for( i= 0 ; i < 100 ;i ++){			
				Kohm  = Block_RES_Check(REF);
				if( Kohm  > (Fixture_RES_Value_LSL[Fixture_Num]) && Kohm < (Fixture_RES_Value_USL[Fixture_Num]))
				{	
						CNT ++; 
				}
				else
				{
						CNT = 0;
				  	Recognition_Result = False ;
				}
				if(CNT >= 10){
						Recognition_Result = True ;
						break ;
				}
				delay_us (10);			
	}
	lcdpos (lcdcon -1, 14);
	if(Recognition_Result == False){
		lcd_printf ("NG");
		cyc4or3run ();
		lcd_printf ("%7.1f ohm   ",Kohm);
		startkeywait (1,1);
	}else {
		lcd_printf ("OK");
	}
	Relay_Drive ( K12_10R_Ref|K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,RESET);	
	Close_All_Point ();
	delay_ms (80);
	return Recognition_Result;
}



