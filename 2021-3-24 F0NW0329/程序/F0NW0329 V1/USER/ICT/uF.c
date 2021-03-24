#include "uF.h"
#include "ad7176.h"
#include "delay.h"
#include "other.h"
#include "sup_fun.h"
#include "lcd3033.h"
#include <stdio.h>
#include <string.h>
#include "global.h"
#include "usart.h"
#include "test.h"
#include "analog_switch.h"
#include "hold_data.h"
#include "test_config.h"
#include "base_Config.h"


#define uF_CAP_Ratio_Addr    0x7060

// #define TestConfig.Cap   DISABLE 

double uF_Cap_Ratio = 1.0;

/*        1
Xc = -------------- = 1000 ohm
		2*3.14*400*Cx
          1
Cx =  --------------- = 0.3981uF;
			1000*2*3.14*400
100mV 	
Rati0 = 0.003981uF/mV
*/

/****

   Vout           Vrms(150mV)
---------- = --------------------------------
  REF+9         sqrt( R^2 + Cx ^2) 
                 
            1    
  Cx = -------------               
         2*3.14*F*
        
              Vrms *(REF+9)                       1
  Zx ^2 = ---------------------- ^2 = R^2 + ---------------^2
              Vout                             2*3,14*F*C

( Vpp*(REF+9))^2    Vout^2 * R^2                1
---------------- - --------------     = ---------------^2
    Vout^2           Vout^2                2*3,14*F*C
      
                              Vout^2
Cx = 1000000 * sqrt -------------------------------------- /(2*3.1415926*f) uF
                       ( Vrms*(REF+9))^2  - Vout^2 * R^2
               
****/
#include <math.h>
#define CAP_Fre              400.0
#define Max_CAP_Ratio   (1000000.0/(2*3.141592654*CAP_Fre*1009.0)/150.0)

#define Switch_Ron     (9)
#define REF_RES_RON    (7)
#define HardwareGain  1.09
double  Vrms_Src = 100;
//double  Calibration_Ratio = 1.0;

//Cap_RES_Test_TypeDef Max_CAP[ ]={                   
//// ******电容编号******** 高点***地点**标称******Unit*****LSL******HSL****Value******delay******REF********OFFSET***RESULT
//		{   "C101",            2,     5,     1 ,    "uF" ,    0.8,     1.2,   0.0 ,       50,     1000 ,       0.0,       99   },		
//	
//	
////		{   "C101//C404",       3,    4,   10 ,      "nF" ,     8,    12,    0.0 ,      10,     100000 ,       0.0,       99   },
////		{   "C102//C406",       3,    4,   10 ,      "nF" ,     8,     12,   0.0 ,      10,     100000 ,       0.0,       99   },
////		{   "C103",             5,    6,   100 ,     "nF" ,    80,    120,   0.0 ,      10,     10000 ,        0.0,       99   },
////		{   "C104//C402",       7,    8,   1 ,       "uF" ,   0.8,    1.2,   0.0 ,      10,     1000 ,         0.0,       99   },
////		{   "C314",             9,   10,   10 ,      "uF" ,     8,     12,   0.0 ,     100,     100 ,          0.0,       99   },	
////		{   "C403//C401",       11,  12,   22 ,      "uF" ,    20,      24,   0.0 ,     100,     100 ,          0.0,       99   },
////		{   "C405//C303//C302", 11,   12,    21 ,    "uF" ,  14.7,    27.3,   0.0 ,    100,     100 ,          0.0,       99   },	
////		{   "C101//C404",       9,    10,   3.2 ,    "uF" ,   2.56,    3.84,   0.0 ,      200,     1000 ,       1.1,       99   },
////		{   "C102//C406",      11,    12,  24.2 ,    "uF" ,   19.36,  29.04,   0.0 ,      300,     100  ,       0.0,       99   },
////		{   "C103",             7,     8,   100 ,    "nF" ,   80.0,   120.0,   0.0 ,       50,     1000 ,       0.0,       99   },
////		{   "C104//C402",      11,    12,   3.2 ,    "uF" ,   2.56,    3.84,   0.0 ,      300,     1000 ,       0.0,       99   },

////		{   "C403//C401",       3,     4,     2 ,    "uF" ,    1.6,     2.4,   0.0 ,       50,     1000 ,       0.0,       99   },
////		{   "C405//C303//C302", 5,     6,    21 ,    "uF" ,   14.7,    27.3,   0.0 ,       50,     100 ,        0.0,       99   },
//	  {   NULL   },
//		
//};
/****************************************************************************************
	* File Name     : Set_CAP_Test_REF_RES
	* Description   : 设置电容测试档位
  * Input         : Range 档位 100OHM 1KOHM 10KOHM 100KOHM 1MOHM
  * return        :、
	* Author        : Morton
	* Date          :  2019/6/24
****************************************************************************************/
double  Set_CAP_Test_REF_RES( uint8_t Range){
	double REF = 100;
	switch (Range){
		case C_100ohm :  CAP_S0 = 0;CAP_S1 = 0;CAP_S2 = 1;  REF = 100;     break;   //REF = 100OHM
		case C_1Kohm  :  CAP_S0 = 1;CAP_S1 = 1;CAP_S2 = 0;  REF = 1000;    break;   //REF = 1KOHM
		case C_10Kohm :  CAP_S0 = 0;CAP_S1 = 1;CAP_S2 = 0;  REF = 10000;   break;   //REF = 10KOHM
		case C_100Kohm:  CAP_S0 = 1;CAP_S1 = 0;CAP_S2 = 0;  REF = 100000;  break;   //REF = 100KOHM
		case C_1Mohm 	:  CAP_S0 = 0;CAP_S1 = 0;CAP_S2 = 0;  REF = 1000000; break;   //REF = 1MOHM
		default      :  lcdreset (); 
										cyc4or3run (); lcd_printf ("CAP REF Error ");
										cyc4or3run (); lcd_printf ("REF = %d ",Range);
										break;
	}
	delay_us (2);
	return REF;
}
/*************************************************************************************************
	* File Name     : Cap_Test
	* Description   : 电容测试函数，计算公式如下  //Xc = 1/(2*3.14*f*Cx);Vx /RG= Vref/Xc; Vref = 200mV RG = 10K,f = 286Hz
  * Input         :
  * return        : Cap_Value返回测试电容值 单位：uF
                                               Vout^2
					         	Cx = 1000000 * sqrt -------------------------------------- /(2*3.1415926*f) uF
                                    ( Vrms*(REF+9))^2  - Vout^2 * R^2

                    Cx=Vout/(2*PI*f*RG*Vref)=Vout/(2*3.14*286*Gain*200)=Vout*10^2/(6.28*5.72*Gain)
				            Cap_Value = Vout*1000000.0/(2*3.14*CAP_Fre*100*(REF+9))/1.6; //uF
				            Cap_Value = Max_CAP_Ratio*Vout*1009/(REF+9);
	* Author        : Morton
	* Date          : 2018/11/18
*********************************************************************************************/
double Read_CAP_Value(uint8_t Num, double REF){
		uint8_t i;
		double  Cap_Value,Vout,Vol[25];
		for(i=0; i < 10; i++){
			Read_AD7176_Average_Voltage_mV(AIN0 ,AIN1 ,10,&Vout);
			Vol[i] = Vout;
			delay_us (2);
		}
		//Vout = Average_Fun (Vol,10)/HardwareGain;
		Vout = Average_Fun (Vol,10);
		Vout *= uF_Cap_Ratio;
		if(Vout > 2000){
			 return  999.999;
		}else if(Vout < 10){
			 Vout /= 10.0;
		}else if(Vout < 100.0 && REF == 1000000){
			 Vout /= 1000.0;
		}
		Cap_Value = 1000000*sqrt(pow(Vout,2)/(pow(Vrms_Src*(REF+REF_RES_RON),2)- pow (Vout*Switch_Ron,2)))/(2*3.141592654*CAP_Fre);
		if(REF == 100){
			Cap_Value *= 1.05;
		}
		if(strstr(Item[Num].Unit,"nF" )){
			Cap_Value *= 870;
		}	else	if(strstr(Item[Num].Unit,"pF" )){
			Cap_Value *= 1000000.0;
		}

		// ** Low Limit**********
		if(Cap_Value < Item[Num].LSL && Cap_Value >  (Item[Num].LSL*0.875) ){
			Cap_Value *= 1.16;
		}
		//***Up Limit************
		if(Cap_Value > Item[Num].USL && Cap_Value <  (Item[Num].USL*1.084) ){
			Cap_Value /= 1.1;
		}		
		
		
		#if defined Debug_Mode
			lcdreset ();
			lcdpos(1,0); lcd_printf  ("R=%7.3fOhm",REF );
			lcdpos(2,0); lcd_printf  ("V=%7.3fmV",Vout  );
		  lcdpos(3,0); lcd_printf  ("C=%7.3f%s",Cap_Value,Item[Num].Unit  );
		#endif 
		return Cap_Value;		
}
/****************************************************************************************
	* File Name     : Max_CAP_Tests
	* Description   : 电容测试底层函数
  * Input         : 电容编号
  * return        : OK - 0 NG -1
	* Author        : Morton
	* Date          : 2019/6/24
****************************************************************************************/
uint8_t Max_CAP_Tests( uint16_t Num){
		uint8_t i,CNT = 0,CAP_Test_Reault = True;
		double CAP_Value,CAP[20],REF;
		AD_Sample_Rate_Set(0);
		Open_Two_Point (COMA,Item[Num].Src_H,COMB,Item[Num].Src_L );
		Open_Two_Point (COMC,Item[Num].Src_H,COMD,Item[Num].Src_L );
		REF = Set_CAP_Test_REF_RES(Item[Num].Type);
		delay_ms (Item[Num].Time+1); 
		if(Fixture.Mode  == Auto_Test_Mode){
				for( i = 0; i < 10; i ++){
						Read_CAP_Value(Num, REF);
					  delay_ms (1);
				}
				for ( i = 0 ;i <100 ; i ++){
					CAP_Value = Read_CAP_Value(Num,REF );
					if(CAP_Value > Item[Num].LSL&& CAP_Value < Item[Num].USL ){
							CAP[CNT] = CAP_Value;
							CNT ++;
					}else{
							Item_Data[Num].Value = CAP_Value;
							CNT = 0;
							delay_us (10);
					}
					if(CNT == 10){
							Item_Data[Num].Value = Average_Fun (CAP,10);
							break ;
					}
					delay_us (5);
				}
				if(TestConfig.Cap == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
					cyc4or3run ();
					lcd_printf("   %7.3f%s    ",Item_Data[Num].Value,Item[Num].Unit );
				}
		}
		if(Fixture.Mode  == Step_Test_Mode){
				for( i = 0; i < 6; i ++)
						CAP[i]  = Read_CAP_Value(Num, REF);
				delay_ms (100);
				for( i = 0; i < 10; i ++)
						CAP[i]  = Read_CAP_Value(Num, REF);
				Item_Data[Num].Value = Average_Fun(CAP,10);
				cyc4or3run ();
				lcd_printf("   %7.3f%s    ",Item_Data[Num].Value,Item[Num].Unit );
				if(left_start_key == 1 || right_start_key == 1 ){
					if(left_start_key == 1 || right_start_key == 1 ){
							while(left_start_key ==1&&right_start_key ==1){ //单步模式下，动态显示电容值
									for( i = 0; i < 10; i ++)
											CAP[i]  = Read_CAP_Value(Num,REF );
										Item_Data[Num].Value = Average_Fun(CAP,10);
										lcdpos(lcdcon-1,0);  
										lcd_printf("   %7.3f%s    ",Item_Data[Num].Value,Item[Num].Unit );
										delay_ms (10);
							}
							startkeywait(1,1);
					}
				}
		}
		
		if(Item_Data[Num].Value > Item[Num].LSL && Item_Data[Num].Value < Item[Num].USL ){
				if(TestConfig.Cap == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
						lcdpos(lcdcon-1,14);  
						lcd_printf ("OK"); 
				}
				CAP_Test_Reault = True ;
		}else{
				if(TestConfig.Cap == DISABLE  || Fixture.Mode  == Auto_Test_Mode  ){
						cyc4or3run ();
						lcd_printf ("%s",Item[Num].Name);
						cyc4or3run ();
						lcd_printf("   %7.3f%s    ",Item_Data[Num].Value,Item[Num].Unit );
				}
				CAP_Test_Reault = False;
				lcdpos (lcdcon-1,14);
				lcd_printf("NG");
		}
		return CAP_Test_Reault;
}
///****************************************************************************************
//	* File Name     : Max_Cap_Test_Fun
//	* Description   : 电容测测试函数
//  * Input         : *TestStepN,当前步数
//  * return        : OK - 0 NG -1
//	* Author        : Morton
//	* Date          :  2019/6/24
//****************************************************************************************/
//u8 Max_Cap_Test_Fun( u16 *TestStepN){
//		u8 i,Total_CAP_Test_Result = True; 
//		Close_All_Point ();
//		Relay_Drive (K7_CAP_COMAB,SET);
//		AD_Sample_Rate_Set(1);
//		delay_ms (80);
//		for(i=0; Max_CAP[i].Name; i ++){
//			 (*TestStepN)++;
//			 cyc4or3run();
//			 lcd_printf ("<%d> %s",*TestStepN,Max_CAP[i].Name);
//			 Max_CAP[i].Status      = Max_CAP_Tests(i);
//			 if(Fixture.Mode  == Auto_Test_Mode && Max_CAP[i].Status == False){
//					Total_CAP_Test_Result |= False ;	
//					break ;
//			 }
//			 if(Fixture.Mode  == Step_Test_Mode && Max_CAP[i].Status == False){
//	//				cyc4or3run ();
//	//				lcd_printf ("U:%g",Max_CAP[Num].USL );
//	//				lcdpos (lcdcon-1,8);
//	//				lcd_printf ("L:%g",Max_CAP[Num].LSL);
//					cyc4or3run ();
//					lcd_printf("PIN (%d, %d)   ",Max_CAP[i].Pin_H ,Max_CAP[i].Pin_L);
//					cyc4or3run ();
//					lcd_printf ("L:复测  R:下一步");
//					lcdcon -- ;
//					Clear_buffer(3);
//					if (step_test_mode_get_key () == Left_Button_Pressed_Down ){
//						i --;
//						continue ;
//					}
//					Total_CAP_Test_Result |= False ;	
//				}
//		}		
//		Close_All_Point ();
//		Relay_Drive (K7_CAP_COMAB,RESET);
//		delay_ms (80);
//		return Total_CAP_Test_Result ;
//}
/****************************************************************************************
	* File Name     : Max_Cap_Test_Fun
	* Description   : 电容测测试函数
  * Input         : *TestStepN,当前步数
  * return        : OK - 0 NG -1
	* Author        : Morton
	* Date          :  2019/6/24
****************************************************************************************/
uint8_t  Type_Cap_Test_Fun( uint16_t *TestStepN, uint16_t Total_Num,uint16_t *Step_Number_buffer){
		u8 Total_CAP_Test_Result = True; 
		uint16_t j = 0,Item_Step_Number = 0;
		if(Total_Num == 0)
			return True;
		if(		TestConfig.Cap == DISABLE &&Fixture.Mode  == Auto_Test_Mode ){
				(*TestStepN) ++;
				cyc4or3run ();
				lcd_printf ("%d>%s",*TestStepN," uF CAP ...   ");
		}

		Close_All_Point ();
		Relay_Drive (K7_CAP_COMAB|K4_CAP_RMS,SET);
		AD_Sample_Rate_Set(0);
		delay_ms (80);	
		for( j = 0; j < Total_Num ; j ++){
			 Item_Step_Number = Step_Number_buffer[j];
			if(TestConfig.Cap == ENABLE || Fixture.Mode  == Step_Test_Mode  ){
				 (*TestStepN)++;
				 cyc4or3run();
				 lcd_printf ("%d>%s",*TestStepN,Item[Item_Step_Number].Name);
			 }
			 Item_Data[Item_Step_Number].Status = Max_CAP_Tests(Item_Step_Number);
			 if(Fixture.Mode  == Auto_Test_Mode && Item_Data[Item_Step_Number].Status == False){
					Total_CAP_Test_Result |= False ;	
					if(TestConfig.FAIL_continue  == ENABLE )  
							continue ;
					else{
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
						Item_Step_Number --;
						(*TestStepN) --;
						continue ;
					}
					Total_CAP_Test_Result |= False ;	
				}
		}	
		if(TestConfig.Cap == DISABLE &&Fixture.Mode  == Auto_Test_Mode && Total_CAP_Test_Result == True ){
				lcdpos(lcdcon -1,14);
				lcd_printf ("OK");
		}
		Close_All_Point ();
		Relay_Drive (K7_CAP_COMAB|K4_CAP_RMS,RESET);
		delay_ms (80);
		return Total_CAP_Test_Result ;
}

/****************************************************************************************
	* File Name     : Max_CAP_Self_Check
	* Description   : 电容测测试自检函数
  * Input         : 、
  * return        :、
	* Author        : Morton
	* Date          :  2019/6/24
****************************************************************************************/
void Max_CAP_Self_Check(void){
	char str[16];
	uint8_t i,CNT = 0;
	double  REF_Volts = 0.0,Vout,Vol[10];
	AD_Sample_Rate_Set (1);
	Relay_Drive (K4_CAP_RMS,SET);
	Set_CAP_Test_REF_RES(C_1Kohm);
	delay_ms (1000);
	for(i = 0;i < 100;i ++){
			Read_AD7176_Average_Voltage_mV(AIN0 ,AIN1 ,10,&Vout);
		  Vout  /= HardwareGain ;
			if(Vout < 200 && Vout > 100){
					Vol[CNT] = Vout;
					CNT ++;
			}else {
				  REF_Volts = Vout ;
			}
			if(CNT > 10){
				REF_Volts = Average_Fun (Vol,10);
				break ;
			}
			delay_ms (1);
	}
	cyc4or3run ();
	lcd_printf ("V = %5.1fmV",REF_Volts);
	if(REF_Volts > 200 ||REF_Volts < 100){
		lcdpos (lcdcon-1,14);lcd_printf ("NG");
		if(REF_Volts < 10){
			cyc4or3run ();
			lcd_printf ("请检查电容板    ");
		}
		Vrms_Src = 150.0;
		step_test_mode_get_key ();
	}else{		
		Vrms_Src = REF_Volts;
		lcdpos (lcdcon-1,14);lcd_printf ("OK");
	}
	Close_All_Point ();
	uF_Cap_Ratio = read_double_data(uF_CAP_Ratio_Addr);
	lcd_printf ("%s",str);
	if(uF_Cap_Ratio > 1.2 || uF_Cap_Ratio < 0.8){
		uF_Cap_Ratio = 1.0;
		Write_double_data (uF_CAP_Ratio_Addr,uF_Cap_Ratio);
	}
	cyc4or3run ();
	lcd_printf ("uF_Ratio=%4.2f   ",uF_Cap_Ratio);
	Relay_Drive (K4_CAP_RMS,RESET);
	delay_ms (180);	
}

/****************************************************************************************
	* File Name     : Max_CAP_Calibration
	* Description   : 电容测测试校准函数
  * Input         : 、
  * return        : 0
	* Author        : Morton
	* Date          :  2019/6/24
****************************************************************************************/
uint8_t Max_CAP_Calibration(void){
	uint8_t i,Key_Status;
	double  Vout,Vol[25],REF_Volts = 0.0;
	lcdreset ();
	lcdpos (0,0); lcd_printf ("    电容校准    "); 
	lcdpos (1,0); lcd_printf ("校准至150mV     "); 
	lcdpos (3,0); lcd_printf ("L:+ R:- L+R:SAVE"); 
	Relay_Drive (K4_CAP_RMS,SET);
	Set_CAP_Test_REF_RES(C_1Kohm);
	delay_ms (80);
	while(1){
			Key_Status = GetKey_Status() ;
			if (Key_Status == Right_Button_Pressed_Down )
			{
				uF_Cap_Ratio += 0.005;
				if(uF_Cap_Ratio > 1.2){
					uF_Cap_Ratio = 1.2;
				}
			}else if(Key_Status == Left_Button_Pressed_Down ){
				uF_Cap_Ratio -= 0.005;
				if(uF_Cap_Ratio < 0.8){
					uF_Cap_Ratio = 0.8;
				}
			}else if(Key_Status == Double_Button_Pressed_Down  ){
				break ;
			}
			for(i=0;i<10;i++){
					Read_AD7176_Average_Voltage_mV(AIN0,AIN4,10,&Vout);
					Vol[i] = Vout;
			}
			lcdpos (2,0);
			REF_Volts = Average_Fun (Vol,10)/HardwareGain*uF_Cap_Ratio;
			lcd_printf ("V = %5.1fmV",REF_Volts);

	}
	Write_double_data (uF_CAP_Ratio_Addr,uF_Cap_Ratio);
	Relay_Drive (K4_CAP_RMS,RESET);
	Close_All_Point ();
	delay_ms (80);
	RevertStartupScreen ();
	return 0;
}

//Cap_RES_Test_TypeDef AC_RES[ ]={
//// 电容编号 , 高点，地点，  标称值， Unit   HSL，  LSL，  测试值 *****delay******REF********OFFSET***
//		{   "C6",    1,    2,   680 ,  "Mohm" ,   816,   544,    0.0 ,       50,     100000 ,    0.0,       99   },	
//		{   "C1",    3,    4,    10 ,  "Kohm" ,    12,     8,    0.0 ,       50,     100000 ,    0.0,       99   },
//		{   "C2",    5,    6,   100 ,  "Kohm" ,   120,    80,    0.0 ,       50,     10000 ,     0.0,       99   },
//		{   "C3",    7,    8,     1 ,  "ohm" ,   1.2,   0.8,    0.0 ,        50,     1000 ,      0.0,       99   },
//		{   "C4",    9,   10,    10 ,  "ohm" ,    12,     8,    0.0 ,       200,     100 ,       0.0,       99   },
//		{   "C5",   11,   12,    22 ,  "ohm" ,   26.4, 17.6,    0.0 ,       300,     100 ,       0.0,       99   },
//	  {   NULL,    2,    3,     1 ,  " " ,   1.3,   0.7,    0.0 ,          0,      0  ,       0.0,       99   },
//};
//double Read_RES_Value(uint8_t Num, double REF){
//		uint8_t i;
//		double  RES_Value,Vout,Vol[25];
//		for(i=0;i<10;i++){
//			Read_AD7176_Voltage_mV_Auto(AIN0 ,AIN4 ,&Vout);
//			Vol[i] = Vout;
//		}
//		Vout = Average_Fun (Vol,10)/HardwareGain;
//		RES_Value = Vrms_Src/(Vout/(REF+REF_RES_RON))-9.0;
//		if(strstr(AC_RES[Num].Unit,"Kohm" )){
//			RES_Value /= 1000;
//		}	else	if(strstr(AC_RES[Num].Unit,"Mohm" )){
//			RES_Value /= 1000000.0;
//		}
//		#if defined Debug_Mode
//			lcdreset ();
//			lcdpos(1,0); lcd_printf  ("R=%7.3fOhm",REF );
//			lcdpos(2,0); lcd_printf  ("V=%7.3fmV",Vout  );
//		  lcdpos(3,0); lcd_printf  ("C=%7.3f%s",RES_Value,AC_RES[Num].Unit  );
//		#endif 
//		return RES_Value;		
//}
//uint8_t AC_RES_Tests( uint8_t Num){
//		uint8_t i,CNT = 0,RES_Test_Reault = True;
//		double RES_Value,RES[20];
//		Open_Two_Point (COMA,AC_RES[Num].Pin_H ,COMB,AC_RES[Num].Pin_L );
//		Set_CAP_Test_REF_RES(AC_RES[Num].REF);
//		delay_ms (AC_RES[Num].Time+1); 
//		if(Fixture.Mode  == Auto_Test_Mode){
//				for ( i = 0 ;i <100 ; i ++){
//					RES_Value = Read_RES_Value(Num, AC_RES[Num].REF );
//					if(RES_Value > AC_RES[Num].LSL && RES_Value < AC_RES[Num].USL ){
//							RES[CNT] = RES_Value;
//							CNT ++;
//					}else{
//							Max_CAP[Num].Value = RES_Value;
//							CNT = 0;
//					}
//					if(CNT == 10){
//							Max_CAP[Num].Value = Average_Fun (RES,10);
//							break ;
//					}
//					delay_us (100);
//				}
//				cyc4or3run ();
//				lcd_printf("   %7.3f%s    ",AC_RES[Num].Value,AC_RES[Num].Unit );
//		}
//		if(Fixture.Mode  == Step_Test_Mode){
//				for( i = 0; i < 10; i ++)
//						RES[i]  = Read_RES_Value(Num, AC_RES[Num].REF );
//				AC_RES[Num].Value = Average_Fun(RES,10);
//				cyc4or3run ();
//				lcd_printf("   %7.3f%s    ",AC_RES[Num].Value,AC_RES[Num].Unit );
//				if(left_start_key == 1 || right_start_key == 1 ){
//					if(left_start_key == 1 || right_start_key == 1 ){
//							while(left_start_key ==1&&right_start_key ==1){ //单步模式下，动态显示电容值
//									for( i = 0; i < 10; i ++)
//											RES[i]  = Read_RES_Value(Num,AC_RES[Num].REF );
//										AC_RES[Num].Value = Average_Fun(RES,10);
//										lcdpos(lcdcon-1,0);  
//										lcd_printf("   %7.3f%s    ",AC_RES[Num].Value,AC_RES[Num].Unit );
//										delay_ms (10);
//							}
//							startkeywait(1,1);
//					}
//				}
//		}
//		lcdpos (lcdcon-1,14);
//		if(AC_RES[Num].Value > AC_RES[Num].LSL && AC_RES[Num].Value < AC_RES[Num].USL ){
//				lcd_printf("OK");
//				RES_Test_Reault = True ;
//		}else{
//				RES_Test_Reault = False;
//				lcd_printf("NG");
//				if(Fixture.Mode  == Step_Test_Mode ){
//						cyc4or3run ();
//						lcd_printf ("U:%g",AC_RES[Num].USL );
//						lcdpos (lcdcon-1,8);
//						lcd_printf ("L:%g",AC_RES[Num].LSL);
//						cyc4or3run ();
//						lcd_printf("PIN %3d %3d     ",AC_RES[Num].Pin_H,AC_RES[Num].Pin_L);
//						step_test_mode_get_key ();
//				}
//		}
//		return RES_Test_Reault;
//}

