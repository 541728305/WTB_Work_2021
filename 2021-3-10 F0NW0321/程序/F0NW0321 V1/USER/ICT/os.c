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
 


// ��λ���ƶ���
const char  *Pin_Name[128*3+1] = {
	 "  ",
//J1(1-54)  54  	
	
"J3200-1",
"J3200-2",
"J3200-3",
"J3200-4",
"J3200-5",
"J3200-6",
"J3200-7",
"J3200-8",
"J3200-9",
"J3200-10",
"J3200-11",
"J3200-12",
"J3200-13",
"J3200-14",
"J3200-15",
"J3200-16",
"J3200-17",
"J3200-18",
"J3200-19",
"J3200-20",
"J3200-21",
"J3200-22",
"J3200-23",
"J3200-24",
"J3200-25",
"J3200-26",
"J3200-27",
"J3200-28",
"J3200-29",
"J3200-30",
"J3200-31",
"J3200-32",
"J3200-33",
"J3200-34",
"J3200-35",
"J3200-36",
"J3200-37",
"J3200-38",
"J3200-39",
"J3200-40",
"J3200-41",
"J3200-42",
"J3200-43",
"J3200-44",
"J3200-45",
"J3200-46",
"J3200-47",
"J3200-48",
"J3200-49",
"J3200-50",
"J3200-51",
"J3200-52",
"J3200-STEEL",
"J3200-STEEL",
"NC",
"NC",
"NC",
"NC",
"NC",
"NC",
"NC",
"NC",
"NC",
"NC",
"J3201-50",
"J3201-49",
"J3201-48",
"J3201-47",
"J3201-46",
"J3201-45",
"J3201-44",
"J3201-43",
"J3201-42",
"J3201-41",
"J3201-40",
"J3201-39",
"J3201-38",
"J3201-37",
"J3201-36",
"J3201-35",
"J3201-34",
"J3201-33",
"J3201-32",
"J3201-31",
"J3201-30",
"J3201-29",
"J3201-28",
"J3201-27",
"J3201-26",
"J3201-25",
"J3201-24",
"J3201-23",
"J3201-22",
"J3201-21",
"J3201-20",
"J3201-19",
"J3201-18",
"J3201-17",
"J3201-16",
"J3201-15",
"J3201-14",
"J3201-13",
"J3201-12",
"J3201-11",
"J3201-10",
"J3201-9",
"J3201-8",
"J3201-7",
"J3201-6",
"J3201-5",
"J3201-4",
"J3201-3",
"J3201-2",
"J3201-1",
"J3201-52",
"J3201-51",
"J3201-STEEL",
"J3201-STEEL",
"NC"
"NC"


};

/******************************************************************************
* File Name     :  Enable_RES_Test_Analog_Switch
* Description   :  �պϵ��������ؼ̵���
* Input         :  ��
* return        :  ��
* Author        :  Morton
* Date          :  2016.12.6
******************************************************************************/
void Enable_RES_Test_Analog_Switch(){
		Relay_Drive ( K1_Pull_Up|K12_10R_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1,SET);
		delay_ms(50);
}




/******************************************************************************
* File Name     : Disable_RES_Test_Analog_Switch
* Description   : �Ͽ����������ؼ̵���
* Input         : ��
* return        : ��
* Author        : Morton
* Date          : 2016.12.6
******************************************************************************/
void Disable_RES_Test_Analog_Switch(){
		Relay_Drive ( K1_Pull_Up|K12_10R_Ref|K14_1K_Ref|K13_20K_Ref|K8_Src_COMAB|K3_COMCD_IN2_3|K13_20K_Ref|K10_Ref_IN0_1|K15_Src_Choice,RESET);
		delay_ms(50);
}
/****************************************************************************************
	* File Name     : KOhm_RES_TEST_SET
	* Description   : relay��ADC ��DAC and so on  Hardware set
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
	* Description   :  ��ȡ���߲��Ե���ֵ
  * Input         :  ��
  * return        :  ��
	* Author        :  Morton
	* Date          :  2016.12.6
******************************************************************************/
double  Res_2wire_Test( void){
		double  RES=0.0,Vrx = 0.0,Vref = 0.0;
		Read_AD7176_Average_Voltage_mV (AIN0 ,AIN1, 6, &Vref );  //�����ڴ����������
		Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3, 6, &Vrx );  //�����ڴ����������
		if(Vref > 60.0 && Vrx < 3590.0 ){
				Read_AD7176_Average_Voltage_mV (AIN0 ,AIN1, 20, &Vref );  //�����ڴ����������
				delay_us (1);
				Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3, 20, &Vrx );  //�����ڴ����������
				if(Vrx == 0.0){
						Read_AD7176_Average_Voltage_mV (AIN3 ,AIN2, 15, &Vrx );  //�����ڴ����������
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
	* Description   : ��ȡ���߲��Ե���ֵ
  * Input         : ��
  * return        : ��
	* Author        : Morton
	* Date          : 2016.12.6
******************************************************************************/
double  Res_4wire_Test( void){
		double  RES=0.0,Vrx = 0.0,Vref = 0.0;
		Read_AD7176_Average_Voltage_mV (AIN0 ,AIN4, 6, &Vref );  //�����ڴ����������
		Read_AD7176_Average_Voltage_mV (AIN1 ,AIN4, 6, &Vrx );  //�����ڴ����������
		if(Vref > 100.0 && Vrx < 3000.0 ){
				Read_AD7176_Average_Voltage_mV (AIN0 ,AIN1, 25, &Vref );  //�����ڴ����������
				delay_us (1);
				Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3, 25, &Vrx );  //�����ڴ����������
				if(Vrx == 0.0){
						Read_AD7176_Average_Voltage_mV (AIN3 ,AIN2, 15, &Vrx );  //�����ڴ����������
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
	* Description   : ��ȡ���߲��Ե���ֵ
  * Input         : ��
  * return        : ��
	* Author        : Morton
	* Date          : 2016.12.6
******************************************************************************/
double  Res_2wire_Test_Mohm(void){
		double  RES=0.0,Vrx = 0.0,Vref = 0.0;
		Read_AD7176_Average_Voltage_mV (AIN0 ,AIN1, 6, &Vref );  //�����ڴ����������
		Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3, 6, &Vrx );  //�����ڴ����������
		Read_AD7176_Average_Voltage_mV (AIN0 ,AIN1, 20, &Vref );  //�����ڴ����������
		if(Vref < 0.0001)
			Vref = 0.0001;
		Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3, 20, &Vrx );  //�����ڴ����������
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
	* Description   : �ҵ�
  * Input         : ��   
  * return        : �� 
	* Author        : Morton
	* Date          : 21-Jun-2019
******************************************************************************/
uint8_t Search_Point_Function(){
	uint16_t i,j=0,Point[20];
	double  Vrx;
	lcdreset ();
	lcdpos (0,0);
	lcd_printf  ("�ҵ�ģʽ:       ");
	Close_All_Point ();
	Enable_RES_Test_Analog_Switch ();
	while(1){
		for(i = 1;i <= Fixture.Max_Point; i ++){
				Open_Single_Point('A' ,i );
				delay_us (10);
				Read_AD7176_Average_Voltage_mV (AIN1 ,AIN4, 10, &Vrx );  //�����ڴ����������
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
	startkeywait (1,1); //����̧�������������
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
		lcd_printf  ("��·�Լ�  ...   ");
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
  * Input         :  ��
  * return        :  Result
	* Author        :  Morton
	* Date          :  2018/8/13
*********************************************************************************************/
void Short_Self_Check(void){
		uint8_t  i,j,Result = True;
		double Res; 
		lcdreset ();
		cyc4or3run ();
		lcd_printf  ("��·�Ų�       ");
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
	* Description   :  �����λ���м��
  * Input         :  ��
  * return        :  ��
	* Author        :  Morton
	* Date          :  2018/8/13
*********************************************************************************************/
void Ananlog_Switch_debug_fun(void ){
	uint8_t Button_Status,i,j;
	lcdreset ();
	lcdpos(0,0);
	lcd_printf  ("ģ�⿪������    ");	
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

