#include "Mohm.h"
#include "test_item.h"
#include "string.h"
#include "ad7176.h"
#include "delay.h"
#include "other.h"
#include "lcd3033.h"
#include "global.h"
#include "test.h"
#include "analog_switch.h"
#include "dac.h"
#include "sup_fun.h"
#include "open.h"
#include <stdio.h>
#define Mohm_Value_Display_Enable  0
extern OPEN_TEST Open_Data;
extern uint8_t testmode,lcdcon;
 
MOhm_RES_TypeDef  R_MOhm[]={
//        ---- 编号 ----高点-----地点---MOhm-----HSL---LSL----测试值---补偿值-----档位----测试结果
	{   "TP101-TP102",    1,      2,      1 ,     9999.9,  20,    0.0,    1.0,    20000.0 ,    99  },
	{   "TP101-TP103",    1,      3,      1 ,     9999.9,  20,    0.0,    1.0,    20000.0 ,    99  },
	{   "TP101-TP104",    1,      4,      1 ,     9999.9,  20,    0.0,    1.0,    20000.0 ,    99  },
	{   "TP101-TP105",    1,      5,      1 ,     9999.9,  20,    0.0,    1.0,    20000.0 ,    99  },
	                                                      
	{   "TP102-TP103",    2,      3,      1 ,     9999.9,  20,    0.0,    1.0,    20000.0 ,    99  },
	{   "TP102-TP104",    2,      4,      1 ,     9999.9,  20,    0.0,    1.0,    20000.0 ,    99  },
	{   "TP102-TP105",    2,      5,      1 ,     9999.9,  20,    0.0,    1.0,    20000.0 ,    99  },
	                                                      
	{   "TP103-TP104",    3,      4,      1 ,     9999.9,  20,    0.0,    1.0,    20000.0 ,    99  },
	{   "TP103-TP105",    3,      5,      1 ,     9999.9,  20,    0.0,    1.0,    20000.0 ,    99  },
	                                                      
	{   "TP104-TP105",    4,      5,      1 ,     9999.9,  20,    0.0,    1.0,    20000.0 ,    99  },	
	
	{    NULL,     0,       0,      0 ,      0,    0,     0.0,    0.0,        0 ,       0  },
}; 
/****************************************************************************************
	* 函数名： KOhm_RES_TEST_SET
	* 功  能： Kohm电阻测试环境搭建，
	* 参  数： Src_Volts 信号源mV ,REF_RES参考电阻, RATE 采样速率 
  * 返回值： 测试结果PASS  OR FAIL
  * 作  者:  Morton
  * 日  期:  2018/8/14
****************************************************************************************/
double Mohm_Test(double REF){
		double  RES=0.0,Vrx = 0.0,Vref = 0.0;
		Read_AD7176_Average_Voltage_mV (AIN0 ,AIN1, 6, &Vref );  //加载在待测电阻两端
		Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3, 6, &Vrx );  //加载在待测电阻两端
		delay_us (1);
		Read_AD7176_Average_Voltage_mV (AIN0 ,AIN1, 20, &Vref );  //加载在待测电阻两端
		Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3, 20, &Vrx );  //加载在待测电阻两端
		if(Vref < 0.1)
			Vref = 0.1;
		RES = Vrx/(Vref/REF)/1000.0;
		#if defined Debug_Mode
				lcdreset ();
				lcdpos (0,0);   printf  ("Ref=20K ");
				lcdpos (1,0);   printf  ("Vx=%0.3lfmV  ",Vrx);
				lcdpos (2,0);   printf  ("Vrf=%0.3lfmV  ",Vref);
				lcdpos (3,0);   printf  ("Rs=%0.3lfOhm ",RES);
		#endif
		if(RES > 999.99)
			RES = 999.99;
		return  RES ;
}
/*********************************************************************************************
	* 函数名：KOhm_RES_Test
	* 功  能：Kohm测试函数
	* 参  数：Num 编号
	* 返回值：测试结果 1： False 0： True
	* 作  者：Morton
	* 日  期：2018/8/13
*********************************************************************************************/
uint8_t MOhm_RES_Test(uint8_t Num){
	uint8_t CNT = 0,i = 0,Test_Result = True ;
	double Mohm = 0.0,TEST_MOhm[10];
	Open_Two_Point (COMC, R_MOhm[Num].H_Pin,COMD,R_MOhm[Num].L_Pin);
	Open_Two_Point (COMA, R_MOhm[Num].H_Pin,COMB,R_MOhm[Num].L_Pin);
	if(testmode == Auto_Test_Mode ){
		  R_MOhm[Num].Value = Mohm_Test(R_MOhm[Num].Range);
			if(R_MOhm[Num].Value < R_MOhm[Num].LSL || R_MOhm[Num].Value > R_MOhm[Num].USL ){
					for( i= 0 ; i < 100 ;i ++){			
						Mohm  = Mohm_Test(R_MOhm[Num].Range);
						if(Mohm  > R_MOhm[Num].LSL && Mohm < (R_MOhm[Num].USL) ){
								TEST_MOhm[CNT] = Mohm;
								CNT ++; 
						}
						else{
								R_MOhm[Num].Value = Mohm;
								CNT = 0;
						}
						if(CNT >= 10){
								R_MOhm[Num].Value  = Average_Fun(TEST_MOhm,10);
								break ;
						}
				 }	
			}
			if(Mohm_Value_Display_Enable){
					cyc4or3run ();
					printf  ("     %5.3fK     ",R_MOhm[Num].Value );
			}
	}
	if(testmode == Step_Test_Mode ){
			for( i = 0; i < 10; i ++)
					TEST_MOhm[i]  = Mohm_Test(R_MOhm[Num].Range);
			R_MOhm[Num].Value = Average_Fun(TEST_MOhm,10);
			if(Mohm_Value_Display_Enable){
					cyc4or3run ();
					printf  ("     %5.3fK     ",R_MOhm[Num].Value );
					if(left_start_key == 1 || right_start_key == 1 ){
						while(left_start_key ==1&&right_start_key ==1){ //单步模式下，动态显示电容值
							for( i = 0; i < 10; i ++)
									TEST_MOhm[i]  = Mohm_Test(R_MOhm[Num].Range);
							R_MOhm[Num].Value  = Average_Fun(TEST_MOhm,10);
							lcdpos(lcdcon-1,0);  
							printf  ("     %5.3fK     ",R_MOhm[Num].Value );
							delay_ms (10);
						}
						startkeywait(1,1);
					}
			}
	}
	if(R_MOhm[Num].Value > R_MOhm[Num].LSL && R_MOhm[Num].Value < R_MOhm[Num].USL){
		if(Mohm_Value_Display_Enable){
				lcdpos(lcdcon-1,14);  
				printf  ("OK"); 
		}
	}else{
		if(Mohm_Value_Display_Enable != SET ){
				cyc4or3run ();
				printf ("%s",R_MOhm[Num].Name);
				cyc4or3run ();
				printf  ("     %5.3fK     ",R_MOhm[Num].Value );
//				cyc4or3run ();
//				printf("PIN %3d %3d",R_MOhm[Num].H_Pin,R_MOhm[Num].L_Pin );
		}
		lcdpos(lcdcon-1,14);  
		printf  ("NG"); 
		Test_Result |= False;
		if(testmode == Step_Test_Mode ){
//				cyc4or3run ();
//				printf ("U:%g",R_MOhm[Num].USL );
//				lcdpos (lcdcon-1,8);
//				printf ("L:%g",R_MOhm[Num].LSL);
//				cyc4or3run ();
//				printf("PIN %3d %3d",R_MOhm[Num].H_Pin,R_MOhm[Num].L_Pin );
				step_test_mode_get_key ();
		}
	}
	return Test_Result;
}
/****************************************************************************************
	* 函数名： KOhm_RES_TEST_SET
	* 功  能： Kohm电阻测试环境搭建，
	* 参  数： Src_Volts 信号源mV ,REF_RES参考电阻, RATE 采样速率 
  * 返回值： 测试结果PASS  OR FAIL
  * 作  者:  Morton
  * 日  期:  2018/8/14
****************************************************************************************/
void MOhm_RES_TEST_SET(double Src_Volts,double REF_RES,uint8_t RATE){
		
	  Valve_Drive ( K4_Max_Ref |K2_Src_COMAB|K3_COMCD_IN2_3|K9_Ref_IN0_1|K10_Src_Choice,SET);

		DAC_Set_Vol(Src_Volts);
	//	AD_Sample_Rate_Set(RATE);
		delay_ms(80);
}
void MOhm_RES_TEST_RESET(){
	  Valve_Drive ( K4_Max_Ref |K2_Src_COMAB|K3_COMCD_IN2_3|K9_Ref_IN0_1|K10_Src_Choice,RESET);
		DAC_Set_Vol(0);
		//AD_Sample_Rate_Set(1);
		delay_ms(80);
}
/*****************************************************************************************
	* 函数名： MOhm_RES_Test_Fun
	* 功  能： Mohm电租函数，
	* 参  数： TestStepN项目测试编号
  * 返回值： 测试结果PASS  OR FAIL
  * 作  者:  Morton
  * 日  期:  2018/8/14
*****************************************************************************************/
uint8_t MOhm_RES_Test_Fun(u16 *TestStepN){
		uint16_t i,Test_Result = True; 
		if(Mohm_Value_Display_Enable == DISABLE ){
				(*TestStepN) ++;
				cyc4or3run ();
				printf ("<%d> open ...  ",(*TestStepN));
		}
		MOhm_RES_TEST_SET(200,20000,0);
		for(i = 0;  R_MOhm[i].Name; i++){
				if(Mohm_Value_Display_Enable == ENABLE){
						(*TestStepN) ++;
						cyc4or3run ();
						printf ("<%d>%s",*TestStepN,R_MOhm[i].Name);
				}
				Test_Result |= MOhm_RES_Test(i);
				R_MOhm[i].Status = Test_Result;
				if(testmode == Auto_Test_Mode && Test_Result == False){
					if( Mohm_Value_Display_Enable == DISABLE ){
						sprintf(Open_Data.RESULT,"%s:%0.4fK@", R_MOhm[i].Name, R_MOhm[i].Value);
						Open_Data.Status = False;
					}
					break ;
				}
		}
		if(Mohm_Value_Display_Enable==DISABLE && Test_Result == True){
				lcdpos(lcdcon-1,14);  
				printf ("OK"); 
				sprintf(Open_Data.RESULT,"OK");
				Open_Data.Status = True;
		}		
		Close_All_Point ();
		MOhm_RES_TEST_RESET();
		delay_ms (10);
		return Test_Result ; 
}




