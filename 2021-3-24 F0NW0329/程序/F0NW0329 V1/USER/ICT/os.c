#include "os.h"
#include "ad7176.h"
#include <string.h>
#include <stdio.h>
#include "global.h"
#include "other.h"
#include "delay.h"
#include "lcd3033.h"
#include "base_Config.h"
#include "sup_fun.h"
#include "dac.h"
#include "mr.h"
 


// 点位名称定义
const char  *Pin_Name[128*3+1] = {
	 "  ",
//J1(1-54)  54  	
	
"J1101_1",
"J1101_2",
"J1101_3",
"J1101_4",
"J1101_5",
"J1101_6",
"J1101_7",
"J1101_8",
"J1101_9",
"J1101_10",
"J1101_11",
"J1101_12",
"J1101_13",
"J1101_14",
"J1101_15",
"J1101_16",
"J1101_17",
"J1101_18",
"J1101_19",
"J1101_20",
"J1101_21",
"J1101_22",
"J1101_23",
"J1101_24",
"J1101_25",
"J1101_26",
"J1101_27",
"J1101_28",
"J1101_29",
"J1101_30",
"J1101_31",
"J1101_32",
"J1101_33",
"J1101_34",
"J1101_35",
"J1101_36",
"J1101_37",
"J1101_38",
"J1101_39",
"J1101_40",
"J1101_41",
"J1101_42",
"J1101_43",
"J1101_44",
"J1104_1",
"J1104_2",
"J1104_3",
"J1104_4",
"J1104_5",
"J1104_6",
"J1104_7",
"J1104_8",
"J1104_9",
"J1104_10",
"J1104_11",
"J1104_12",
"J1104_13",
"J1104_14",
"J1104_15",
"J1104_16",
"_NC",
"_NC",
"_NC",
"_NC",
"J1102_1",
"J1102_2",
"J1102_3",
"J1102_4",
"J1102_5",
"J1102_6",
"J1102_7",
"J1102_8",
"J1102_9",
"J1102_10",
"J1102_11",
"J1102_12",
"J1102_13",
"J1102_14",
"J1102_15",
"J1102_16",
"J1103_1",
"J1103_2",
"J1103_3",
"J1103_4",
"J1103_5",
"J1103_6",
"J1103_7",
"J1103_8",
"J1103_9",
"J1103_10",
"J1103_11",
"J1103_12",
"J1103_13",
"J1103_14",
"J1103_15",
"J1103_16",
"J1103_17",
"J1103_18",
"J1103_19",
"J1103_20",
"J1103_21",
"J1103_22",
"J1103_23",
"J1103_24",
"J1103_25",
"J1103_26",
"J1103_27",
"J1103_28",
"J1103_29",
"J1103_30",
"J1103_31",
"J1103_32",
"J1103_33",
"J1103_34",
"J1103_35",
"J1103_36",
"J1103_37",
"J1103_38",
"J1103_39",
"J1103_40",
"J1103_41",
"J1103_42",
"J1103_45",
"J1103_43",
"J1103_44",
"J1103_46",

"NC",
"NC",



};

/******************************************************************************
* File Name     :  Enable_RES_Test_Analog_Switch
* Description   :  闭合电阻测试相关继电器
* Input         :  无
* return        :  无
* Author        :  Morton
* Date          :  2016.12.6
******************************************************************************/
void Enable_RES_Test_Analog_Switch(){
		Relay_Drive ( K1_Pull_Up|K12_10R_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1,SET);
		delay_ms(50);
}




/******************************************************************************
* File Name     : Disable_RES_Test_Analog_Switch
* Description   : 断开电阻测试相关继电器
* Input         : 无
* return        : 无
* Author        : Morton
* Date          : 2016.12.6
******************************************************************************/
void Disable_RES_Test_Analog_Switch(){
		Relay_Drive ( K1_Pull_Up|K12_10R_Ref|K14_1K_Ref|K13_20K_Ref|K8_Src_COMAB|K3_COMCD_IN2_3|K13_20K_Ref|K10_Ref_IN0_1|K15_Src_Choice,RESET);
		delay_ms(50);
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
void Vsrc_RES_TEST_SET(double Src_Volts,uint8_t RATE){
		Relay_Drive ( K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,SET);
		DAC_Set_Vol(Src_Volts,5.0,0);
		AD_Sample_Rate_Set(RATE);
		delay_ms(80);
}
/******************************************************************************
	* File Name     :  Res_2wire_Test
	* Description   :  读取两线测试电阻值
  * Input         :  无
  * return        :  无
	* Author        :  Morton
	* Date          :  2016.12.6
******************************************************************************/
double  Res_2wire_Test( void){
		double  RES=0.0,Vrx = 0.0,Vref = 0.0;
		Read_AD7176_Average_Voltage_mV (AIN0 ,AIN1, 6, &Vref );  //加载在待测电阻两端
		Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3, 6, &Vrx );  //加载在待测电阻两端
		if(Vref > 60.0 && Vrx < 3590.0 ){
				Read_AD7176_Average_Voltage_mV (AIN0 ,AIN1, 20, &Vref );  //加载在待测电阻两端
				delay_us (1);
				Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3, 20, &Vrx );  //加载在待测电阻两端
				if(Vrx == 0.0){
						Read_AD7176_Average_Voltage_mV (AIN3 ,AIN2, 15, &Vrx );  //加载在待测电阻两端
				}
				RES = Vrx/(Vref/10.0)*1.02;
		}else {
				RES = 999;
		}
		#if defined Debug_Mode
				lcdreset ();
				lcdpos (0,0);   lcd_printf  ("Ref=%0.3lfR ",Ref_Res);
				lcdpos (1,0);   lcd_printf  ("Vx=%0.3lfmV  ",Vrx);
				lcdpos (2,0);   lcd_printf  ("Vrf=%0.3lfmV  ",Vref);
				lcdpos (3,0);   lcd_printf  ("Rs=%0.3lfOhm ",RES);
		#endif
		if(RES > 1000)
			RES = 999;
		return  RES ;
}
/******************************************************************************
	* File Name     : Res_4wire_Test
	* Description   : 读取两线测试电阻值
  * Input         : 无
  * return        : 无
	* Author        : Morton
	* Date          : 2016.12.6
******************************************************************************/
double  Res_4wire_Test( void){
		double  RES=0.0,Vrx = 0.0,Vref = 0.0;
		Read_AD7176_Average_Voltage_mV (AIN0 ,AIN4, 6, &Vref );  //加载在待测电阻两端
		Read_AD7176_Average_Voltage_mV (AIN1 ,AIN4, 6, &Vrx );  //加载在待测电阻两端
		if(Vref > 100.0 && Vrx < 3000.0 ){
				Read_AD7176_Average_Voltage_mV (AIN0 ,AIN1, 25, &Vref );  //加载在待测电阻两端
				delay_us (1);
				Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3, 25, &Vrx );  //加载在待测电阻两端
				if(Vrx == 0.0){
						Read_AD7176_Average_Voltage_mV (AIN3 ,AIN2, 15, &Vrx );  //加载在待测电阻两端
				}
				RES = Vrx/(Vref/10.0)*1.002;
		}else {
				RES = 99.999;
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
/******************************************************************************
	* File Name     : Res_2wire_Test_Mohm
	* Description   : 读取两线测试电阻值
  * Input         : 无
  * return        : 无
	* Author        : Morton
	* Date          : 2016.12.6
******************************************************************************/
double  Res_2wire_Test_Mohm(void){
		double  RES=0.0,Vrx = 0.0,Vref = 0.0;
		Read_AD7176_Average_Voltage_mV (AIN0 ,AIN1, 6, &Vref );  //加载在待测电阻两端
		Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3, 6, &Vrx );  //加载在待测电阻两端
		Read_AD7176_Average_Voltage_mV (AIN0 ,AIN1, 20, &Vref );  //加载在待测电阻两端
		if(Vref < 0.0001)
			Vref = 0.0001;
		Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3, 20, &Vrx );  //加载在待测电阻两端
		RES = Vrx/(Vref/20)/1000.0;
		#if defined Debug_Mode
				lcdreset ();
				lcdpos (0,0);   lcd_printf  ("Ref=%0.3lfR ",Ref_Res);
				lcdpos (1,0);   lcd_printf  ("Vx=%0.3lfmV  ",Vrx);
				lcdpos (2,0);   lcd_printf  ("Vrf=%0.3lfmV  ",Vref);
				lcdpos (3,0);   lcd_printf  ("Rs=%0.3lfOhm ",RES);
		#endif
		if(RES > 9.9)
			RES = 9.9;
		if(RES>1&&RES < 2 )
			RES *=2.0;
		return  RES  ;
}

/******************************************************************************
	* File Name     : Search_Point_Function
	* Description   : 找点
  * Input         : 无   
  * return        : 无 
	* Author        : Morton
	* Date          : 21-Jun-2019
******************************************************************************/
uint8_t Search_Point_Function(){
	uint16_t i,j=0,Point[20];
	double  Vrx;
	lcdreset ();
	lcdpos (0,0);
	lcd_printf  ("找点模式:       ");
	Close_All_Point ();
	Enable_RES_Test_Analog_Switch ();
	while(1){
		for(i = 1;i <= Fixture.Max_Point; i ++){
				Open_Single_Point('A' ,i );
				delay_us (10);
				Read_AD7176_Average_Voltage_mV (AIN1 ,AIN4, 10, &Vrx );  //加载在待测电阻两端
				if(Vrx < 200.0){//R<10ohm OK
					Point[j]=i; j++;
				}
		}
		Point[j]='\0';
		if(j){
			lcdreset ();
			lcdpos (0,0);
			for(i=0;i<j;i++){
				lcd_printf  ("%d-%s",Point[i],Pin_Name[Point[i]]);
				if(i!= j-1)
					lcd_printf  (",");
				else
					lcd_printf  (".");
			}
			j=0;
	//		lcdpos (3,0); lcd_printf  ("RES=%4.2lf Ohm  ",R);
		}
		if( left_start_key == 0 ||  right_start_key == 0 ){
				 startkeywait(1,1);
				 break;
			}
	}
	Close_All_Point ();
	Disable_RES_Test_Analog_Switch();
	startkeywait (1,1); //按键抬起继续后续动作
	RevertStartupScreen();
	delay_ms (500);
	return 0;
}
/*********************************************************************************************
	* File Name     :  Self_Check_Ananlog_Switch
	* Description   :  Self_Check_Ananlog_Switch
  * Input         :  /
  * return        :  /
	* Author        :  Morton
	* Date          :  2018/8/13
*********************************************************************************************/
void Self_Check_Ananlog_Switch(void){
		uint16_t  i,Result = True;
		double Res; 
		cyc4or3run ();
		lcd_printf  ("开路自检  ...   ");
		Close_All_Point ();
		AD_Sample_Rate_Set(2);
		Enable_RES_Test_Analog_Switch ();
		for ( i = 1; i <= Fixture.Max_Point  ; i ++){
				Open_Four_Point(COMA, i, COMB ,i,COMC, i, COMD ,i);
				Res = Res_4wire_Test();
				if(Res < 1.0 ){
					continue ;
				}
				else{	
						lcdpos (lcdcon -1,14);
						lcd_printf  ("NG");
						cyc4or3run (); 
						lcd_printf  ("PIN-%d=%0.3f ",i,Res);
						Result = False ;
						beep(2,200);
						while(left_start_key == SET && right_start_key  ==SET ) delay_ms (10);
						break ;
				}
		}
		if(Result == True){
				lcdpos (lcdcon -1,14);
				lcd_printf  ("OK");
		}
		Close_All_Point ();
	//	mohm_RES_Calibration();
		
		Disable_RES_Test_Analog_Switch ();
		delay_ms (200);
}
/*********************************************************************************************
	* File Name     :  Short_Self_Check
	* Description   :  Short_Self_Check
  * Input         :  无
  * return        :  Result
	* Author        :  Morton
	* Date          :  2018/8/13
*********************************************************************************************/
void Short_Self_Check(void){
		uint8_t  i,j,Result = True;
		double Res; 
		lcdreset ();
		cyc4or3run ();
		lcd_printf  ("短路排查       ");
		Close_All_Point ();
		DAC_Set_Vol(1000,5,0); 
		Relay_Drive ( K10_Ref_IN0_1|K15_Src_Choice|K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3,SET);
		delay_ms (100);
		for ( i = 1; i < Fixture.Max_Point   ; i ++){
				Open_Two_Point(COMA, i,COMC, i);
				for( j = i+1 ; j <= Fixture.Max_Point ; j ++){
						Open_Two_Point( COMB ,j, COMD ,j);
						Res = Res_2wire_Test_Mohm();
						if(Res < 2.0){	
								delay_ms (50);
								Res = Res_2wire_Test_Mohm();Res = Res_2wire_Test_Mohm();
								if(Res < 2.0){
										lcdpos (lcdcon -1,14);
										lcd_printf  ("NG");
										cyc4or3run (); 
										lcd_printf  ("%d-%d=%0.2fM",i,j,Res);
										beep(2,200);
										while( left_start_key == 1 && right_start_key == 1) {
												Res = Res_2wire_Test_Mohm();
												lcdpos( lcdcon -1 ,0);								
												lcd_printf  ("%d-%d=%0.2fM",i,j,Res);
												delay_ms (100);	
										}
										startkeywait (1,1);
										if(Res < 2){
											Result = False ;
											break ;
										}
								}
						}
				}
		}
		if(Result == True){
				lcdpos (lcdcon -1,14);
				lcd_printf  ("OK");
		}
		Close_All_Point ();
		Relay_Drive (K10_Ref_IN0_1| K15_Src_Choice|K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3,RESET);
		DAC_Set_Vol(0,5,0);
		delay_ms (80);
		RevertStartupScreen();
}
/*********************************************************************************************
	* File Name     :  Ananlog_Switch_debug_fun
	* Description   :  逐个点位进行检查
  * Input         :  无
  * return        :  无
	* Author        :  Morton
	* Date          :  2018/8/13
*********************************************************************************************/
void Ananlog_Switch_debug_fun(void ){
	uint8_t Button_Status,i,j;
	lcdreset ();
	lcdpos(0,0);
	lcd_printf  ("模拟开关量测    ");	
	startkeywait (1,1);
	for( i = 0; i < 4 ; i ++ ){
		lcdpos(1,0); lcd_printf  ("COM%c            ",'A'+i);
		lcdpos (3,0);
		lcd_printf  ("L:debugR:NEXTCOM");
		Button_Status = Get_start_key_val();
		if(Button_Status == Left_Button_Pressed_Down ){
				lcdpos (3,0);
				lcd_printf  ("L:NEXT  R:EXIT  ");
				for( j = 1; j <= Fixture.Max_Point  ; j ++){
						lcdpos(1,0); lcd_printf  ("COM%c----%03d     ",'A'+i,j);
						Open_Single_Point('A'+i,j);
						Button_Status = Get_start_key_val();
						if(Button_Status == Left_Button_Pressed_Down )
								continue  ;	
						if(Button_Status == Right_Button_Pressed_Down  )
							break ;
				}
				Close_All_Point ();
		}
		if(Button_Status == Right_Button_Pressed_Down )
				continue  ;
	}	
	RevertStartupScreen();
	delay_ms (50);
}

