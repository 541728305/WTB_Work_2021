#include "ohm.h"
#include "string.h"
#include "ad7176.h"
#include "delay.h"
#include "other.h"
#include "lcd3033.h"
#include "test.h"
#include "global.h"
#include "analog_switch.h"
#include "dac.h"
#include "sup_fun.h"
#include <stdio.h>
#define ohm_Value_Display_Enable  1

Ohm_RES_TypeDef  R_Ohm[]={             
//************* 编号 *****高点*****地点****Ohm---LSL--  -HSL-----测试值--单位---补偿值-----档位----测试结果
	{   "J101.1-J101.3",    1,      3,      1 ,    0.0,    10,      0.0,   "ohm",   0.0,     10.0 ,    99  },
	{   "J101.1-J102.5",    1,      5,      1 ,    0.0,    10,      0.0,   "ohm",   0.0,     10.0 ,    99  },
	{   "J102.6-J102.8",    6,      8,      1 ,    0.0,    10,      0.0,   "ohm",   0.0,     10.0 ,    99  },
	{   "J102.6-J101.10",   6,     10,      1 ,    0.0,    10,      0.0,   "ohm",   0.0,     10.0 ,    99  },
	{   "J102.6-J101.11",   6,     11,      1 ,    0.0,    10,      0.0,   "ohm",   0.0,     10.0 ,    99  },
	{   "J102.6-J101.12",   6,     12,      1 ,    0.0,    10,      0.0,   "ohm",   0.0,     10.0 ,    99  },
	{   "J102.6-J101.13",   6,     13,      1 ,    0.0,    10,      0.0,   "ohm",   0.0,     10.0 ,    99  },
	{   "J102.6-J101.14",   6,     14,      1 ,    0.0,    10,      0.0,   "ohm",   0.0,     10.0 ,    99  },	
	{    NULL  },
}; 
/****************************************************************************************
	* File Name     : KOhm_RES_TEST_SET
	* Description   : Kohm电阻测试环境搭建，
  * Input         : Src_Volts 信号源mV ,REF_RES参考电阻, RATE 采样速率 
  * return        : 测试结果PASS  OR FAIL
	* Author        : Morton
	* Date          :  2018/8/14
****************************************************************************************/
double ohm_Test(double REF){
		double  RES=0.0,Vrx = 0.0,Vref = 0.0;
		Read_AD7176_Average_Voltage_mV (AIN0 ,AIN4, 6, &Vref );  //加载在待测电阻两端
		Read_AD7176_Average_Voltage_mV (AIN1 ,AIN4, 6, &Vrx );  //加载在待测电阻两端
		delay_us (1);
		Read_AD7176_Average_Voltage_mV (AIN0 ,AIN1, 15, &Vref );  //加载在待测电阻两端
		Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3, 15, &Vrx );  //加载在待测电阻两端
		RES = Vrx/(Vref/REF);
		#if defined Debug_Mode
				lcdreset ();
				lcdpos (0,0);   lcd_printf  ("Ref=%0.3lfR ",REF);
				lcdpos (1,0);   lcd_printf  ("Vx=%0.3lfmV  ",Vrx);
				lcdpos (2,0);   lcd_printf  ("Vrf=%0.3lfmV  ",Vref);
				lcdpos (3,0);   lcd_printf  ("Rs=%0.3lfOhm ",RES);
		#endif
		if(RES > 999.99)
			RES = 999.99;
		return  RES ;
}
/*********************************************************************************************
	* File Name     :  KOhm_RES_Test
	* Description   :  Kohm测试函数
  * Input         :  Num 编号
  * return        :  测试结果 1： False 0： True
	* Author        :  Morton
	* Date          :  2018/8/13
*********************************************************************************************/
uint8_t Ohm_RES_Test(uint8_t Num){
	uint8_t CNT = 0,i = 0,Test_Result = True ;
	double ohm = 0.0,TEST_Ohm[10];
	Open_Two_Point (COMC, R_Ohm[Num].H_Pin,COMD,R_Ohm[Num].L_Pin);
	Open_Two_Point (COMA, R_Ohm[Num].H_Pin,COMB,R_Ohm[Num].L_Pin);
	if(testmode == Auto_Test_Mode ){
		  R_Ohm[Num].Value = ohm_Test(R_Ohm[Num].Range);
			if(R_Ohm[Num].Value < R_Ohm[Num].LSL || R_Ohm[Num].Value > R_Ohm[Num].USL ){
					for( i= 0 ; i < 100 ;i ++){			
						ohm  = ohm_Test(R_Ohm[Num].Range);
						if(ohm  > R_Ohm[Num].LSL && ohm < (R_Ohm[Num].USL) ){
								TEST_Ohm[CNT] = ohm;
								CNT ++; 
						}
						else{
								R_Ohm[Num].Value = ohm;
								CNT = 0;
						}
						if(CNT >= 10){
								R_Ohm[Num].Value  = Average_Fun(TEST_Ohm,10);
								break ;
						}
				 }	
			}
			cyc4or3run ();
			lcd_printf  ("   %7.3fOhm   ",R_Ohm[Num].Value );
	}
	if(testmode == Step_Test_Mode && ohm_Value_Display_Enable ){
			for( i = 0; i < 10; i ++)
					TEST_Ohm[i]  = ohm_Test(R_Ohm[Num].Range);
			R_Ohm[Num].Value = Average_Fun(TEST_Ohm,10);
			cyc4or3run ();
			lcd_printf  ("   %7.3fOhm   ",R_Ohm[Num].Value );
			if(left_start_key == 1 || right_start_key == 1 ){
					while(left_start_key ==1&&right_start_key ==1){ //单步模式下，动态显示电容值
						for( i = 0; i < 10; i ++)
								TEST_Ohm[i]  = ohm_Test(R_Ohm[Num].Range);
						R_Ohm[Num].Value  = Average_Fun(TEST_Ohm,10);
						lcdpos(lcdcon-1,0);  
						lcd_printf  ("   %7.3fOhm   ",R_Ohm[Num].Value );
						delay_ms (10);
					}
					startkeywait(1,1);
			}
	}
	if(R_Ohm[Num].Value > R_Ohm[Num].LSL && R_Ohm[Num].Value < R_Ohm[Num].USL){
		lcdpos(lcdcon-1,14);  
		lcd_printf ("OK"); 
	}else{
		lcdpos(lcdcon-1,14);  
		lcd_printf ("NG"); 
		Test_Result |= False;
	}
	return Test_Result;
}
/****************************************************************************************
	* File Name     : KOhm_RES_TEST_SET
	* Description   : Kohm电阻测试环境搭建，
  * Input         : Src_Volts 信号源mV ,REF_RES参考电阻, RATE 采样速率 
  * return        : 测试结果PASS  OR FAIL
	* Author        : Morton
	* Date          :  2018/8/14
****************************************************************************************/
void Ohm_RES_TEST_SET(double Src_Volts,double REF_RES,uint8_t RATE){
	  Valve_Drive ( K1_Min_Ref |K2_Src_COMAB|K3_COMCD_IN2_3|K9_Ref_IN0_1|K10_Src_Choice,SET);
		DAC_Set_Vol(Src_Volts);
		AD_Sample_Rate_Set(RATE);
		delay_ms(80);
}
void Ohm_RES_TEST_RESET(){
	  Valve_Drive ( K1_Min_Ref |K2_Src_COMAB|K3_COMCD_IN2_3|K9_Ref_IN0_1|K10_Src_Choice,RESET);
		DAC_Set_Vol(0);
		AD_Sample_Rate_Set(1);
		delay_ms(80);
}
/*****************************************************************************************
	* File Name     : MOhm_RES_Test_Fun
	* Description   : Mohm电租函数，
  * Input         : TestStepN项目测试编号
  * return        : 测试结果PASS  OR FAIL
	* Author        : Morton
	* Date          :  2018/8/14
*****************************************************************************************/
uint8_t Ohm_RES_Test_Fun(u16 *TestStepN){
		uint16_t i,Test_Result = True; 
		Ohm_RES_TEST_SET(1000,10.0,1);
		for(i = 0;  R_Ohm[i].Name; i++){
				(*TestStepN) ++; 
				cyc4or3run ();
				lcd_printf ("<%d> %s",*TestStepN,R_Ohm[i].Name);
				R_Ohm[i].Status = Ohm_RES_Test(i);
				if(testmode == Auto_Test_Mode && R_Ohm[i].Status == False){
					Test_Result  |= False ;
					break ;
				}
				if(testmode == Step_Test_Mode && R_Ohm[i].Status == False){
	//				cyc4or3run ();
	//				lcd_printf ("U:%g",R_Ohm[Num].USL );
	//				lcdpos (lcdcon-1,8);
	//				lcd_printf ("L:%g",R_Ohm[Num].LSL);
					cyc4or3run ();
					lcd_printf("PIN (%d, %d)   ",R_Ohm[i].H_Pin ,R_Ohm[i].L_Pin);
					cyc4or3run ();
					lcd_printf ("L:复测  R:下一步");
					lcdcon -- ;
					Clear_buffer(3);
					if (step_test_mode_get_key () == Left_Button_Pressed_Down ){
						i --;
						continue ;
					}
					Test_Result  |= False ;
			}
		}
//   cyc4or3run ();
//lcd_printf ("CNT = %4d      ",i);		
		Close_All_Point ();
		Ohm_RES_TEST_RESET();
		delay_ms (10);
		return Test_Result ; 
}




