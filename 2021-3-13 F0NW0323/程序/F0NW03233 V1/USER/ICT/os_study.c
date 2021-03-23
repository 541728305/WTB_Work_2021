#include "os_study.h"
#include "os.h"
#include "ad7176.h"
#include "short.h"
#include "Sup_Fun.h"
#include "analog_switch.h"
#include "other.h"
#include "global.h"
#include "delay.h"
#include "usart.h"
#include "lcd3033.h"
#include "usart.h"
#include <string.h>
#include "base_Config.h"
/******************************************************************************
	* File Name     :  Res_2wire_Test
	* Description   :  读取两线测试电阻值
  * Input         :  无
  * return        :  无
	* Author        :  Morton
	* Date          :  2016.12.6
******************************************************************************/
static  double  Short_RES_Test( void){
		double  RES=0.0,Vrx = 0.0,Vref = 0.0;
		Read_AD7176_Average_Voltage_mV (AIN0 ,AIN4, 6, &Vref );  //加载在待测电阻两端
		Read_AD7176_Average_Voltage_mV (AIN1 ,AIN4, 6, &Vrx );  //加载在待测电阻两端
		if(Vref > 20.0 && Vrx < 3000.0 ){
				Read_AD7176_Average_Voltage_mV (AIN0 ,AIN1, 15, &Vref );  //加载在待测电阻两端
				delay_us (1);
				Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3, 15, &Vrx );  //加载在待测电阻两端
				RES = Vrx/(Vref/10.0);
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
		if(RES >=100)
			RES = 99.999;
		return  RES ;
}
/*********************************************************************************************
	* File Name     : Mark_Short_Pin
	* Description   : Mark_Short_Pin
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 3-Oct-2019
*********************************************************************************************/
void Mark_Short_Pin(uint16_t Pin, uint16_t *Group ){
	uint16_t i = 0;
	while(Group[i])
		i ++;
	Group[i] = Pin;
}
/*********************************************************************************************
	* File Name     : Find_Mark_Short_Pin
	* Description   : Find_Mark_Short_Pin
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 3-Oct-2019
*********************************************************************************************/
uint8_t  Find_Mark_Short_Pin(uint16_t Pin, uint16_t *Group ){
	uint16_t i = 0;
	while(Group[i]){
		if(Group[i] == Pin)
			return True;
		i ++;
	}
	return False ;
}
/*********************************************************************************************
	* File Name     : Find_Mark_Short_Pin
	* Description   : Find_Mark_Short_Pin
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 3-Oct-2019
*********************************************************************************************/
void  View_Short_Group(uint16_t str,uint16_t *Group ){
	uint16_t Num = 0, i = 0,CNT = 0,str_Num = 0,Length = 0;
	char buf[128];
	while(Group[i]||Group[i+1]){
//		Uart_printf (Fixture.Comm_Uart,"%d-",Group[i]);
		if(Group[i]==str ){
			Num ++;
//			Uart_printf(Fixture.Comm_Uart,"\r\n");
		}
		i++;	
	}
	Num ++;
	for( i = 0; i < Num ; i ++){
		lcdreset ();
		cyc4or3set (3);
		lcd_printf ("%d/%d",i+1,Num);
//		Uart_printf(Fixture.Comm_Uart,"\r\n");
		lcdpos(1,0);
		str_Num = 0;
		
		while(Group[CNT] != str){	
			memset (buf, 0,128);
			if(Group[CNT+1] != str){
				sprintf(buf,"%d,",Group[CNT]);
			}
			else{
				sprintf(buf,"%d",Group[CNT]);
			}
			Length = strlen (buf);
//			Uart_printf(Fixture.Comm_Uart,"%s",buf);
			if((str_Num + Length) <= 48){
				lcd_printf ("%s",buf);
				str_Num += Length;
			}else{
				step_test_mode_get_key ();
				lcdpos(1,0); lcd_printf ("                ");
				lcdpos(2,0); lcd_printf ("                ");
				lcdpos(3,0); lcd_printf ("                ");
				lcdpos(1,0);
				lcd_printf ("%s",buf);			
				str_Num = Length ;
			}
			CNT++;
		}
		CNT++;
//		Uart_printf(Fixture.Comm_Uart,"\r\n");
		step_test_mode_get_key ();
	}
	cyc4or3set (4);
}
/*********************************************************************************************
	* File Name     : Read_Group
	* Description   : Read_Group
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 3-Oct-2019
*********************************************************************************************/
void  Read_OS_Group(void  ){
	uint16_t i = 0,j = 0,CNT = 0,Num = 1,Max;
	uint16_t Group[260],Mark[512];
	double R = 0.0;
	while(1){
			i = 0,j = 0,CNT = 0,Num = 1,Max = Fixture.Max_Point ;
			memset (Group,0,260);memset (Mark,0,512);
			lcdreset ();
			cyc4or3run ();
			lcd_printf ("短路群读取中... ");
			memset (Group,0,256);
			memset (Mark,0,512);
			Max = Fixture.Max_Point ;
			Enable_RES_Test_Analog_Switch();
			for( i = 1; i <= Max ; i ++){
				if(Find_Mark_Short_Pin(i,Mark)==True)
					continue ;
				Uart_printf (Fixture.Comm_Uart , "Group%d:",Num);
				Open_Two_Point(COMA,i,COMC,i);
				Group[CNT] = i; 
				Uart_printf (Fixture.Comm_Uart, "%d,",i);
				Mark_Short_Pin(i,Mark);
				CNT ++;Num ++;
				for( j = i+1 ; j <= Max ; j ++){
					Open_Two_Point(COMB,j,COMD,j);
					R = Short_RES_Test();
					if( R < 50){
						Group[CNT] = j;
						Uart_printf (Fixture.Comm_Uart, "%d,",j);
						Mark_Short_Pin(j,Mark);
						CNT ++;
					}
				}
				Group[CNT] = 0;CNT ++;
				Uart_printf (Fixture.Comm_Uart, "\r\n");
			}
			lcdpos (1,0);
			lcd_printf ("短路群读取OK    ");
			lcdpos (3,0);;
			lcd_printf ("L:查看    R:退出");
			if(step_test_mode_get_key ()==Left_Button_Pressed_Down ){
				View_Short_Group(0,Group);
				lcdreset ();
				lcdpos (1,0); lcd_printf ("L:再次读取短路群");
				lcdpos (2,0); lcd_printf ("R:退出当前模式  ");
				if(step_test_mode_get_key ()==Right_Button_Pressed_Down)
					break;
			}else
			   break ;
	}

	Disable_RES_Test_Analog_Switch();
	Close_All_Point ();
	RevertStartupScreen();
}

