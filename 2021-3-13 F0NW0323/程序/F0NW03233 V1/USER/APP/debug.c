#include "debug.h"
#include "other.h"
#include "lcd3033.h"
#include "global.h"
#include "usart.h"
#include "Sup_Fun.h"
#include "ad7176.h"
#include "uF.h"
#include "os.h"
#include "24cxx.h"
#include "delay.h"
#include "analog_switch.h"
#include "DAC.h"
#include "menu.h"
/*********************************************************************************************
 	* File Name     : Self_Check_Fun
	* Description   : 自检函数
  * Input         : 无
  * return        : 无
  * Author        : Morton
  * Date          : 2019/6/18
*********************************************************************************************/
void Self_Check_Fun(void){
		double Vrx;
		uint8_t i;
		lcdreset();
		cyc4or3set (4);
		cyc4or3run();
		lcd_printf  ("Init Hardware...");
		Relay_Drive (0,SET ); 
		Close_All_Point ();	
		{
				cyc4or3run ();
				lcd_printf  ("输入信号检查    ");
				while( left_start_key == 1) delay_ms (10);
				cyc4or3run ();lcd_printf  ("左键OK          ");
				while( right_start_key== 1) delay_ms (10);
				cyc4or3run ();lcd_printf  ("右键OK          ");
			
				while( SENSOR3 == 1) delay_ms (10);
				cyc4or3run ();lcd_printf  ("电机传感器OK    ");
				while( SENSOR4 == 1) delay_ms (10);
				cyc4or3run ();lcd_printf  ("光栅检测OK      ");
			

				while( SENSOR5 == 1) delay_ms (10);
				cyc4or3run ();lcd_printf  ("输入-1检测OK    ");			
			
				while( SENSOR6 == 1) delay_ms (10);
				cyc4or3run ();lcd_printf  ("输入-2检测OK    ");		
			
				while( SENSOR7 == 1) delay_ms (10);
				cyc4or3run ();lcd_printf  ("输入-3检测OK    ");		
			
				while( SENSOR8 == 1) delay_ms (10);
				cyc4or3run ();lcd_printf  ("输入-4检测OK    ");		
			
				while( SENSOR9 == 1) delay_ms (10);
				cyc4or3run ();lcd_printf  ("输入-5检测OK    ");		
			
				while( SENSOR10 == 1) delay_ms (10);
				cyc4or3run ();lcd_printf  ("输入-6检测OK    ");		
			
				while( SENSOR11 == 1) delay_ms (10);
				cyc4or3run ();lcd_printf  ("输入-7检测OK    ");						
		}
		cyc4or3run ();
		lcd_printf  ("24C256检查    ");
		{
				uint8_t i;
				AT24CXX_WriteOneByte(0x7FFF,0x55);
				i= AT24CXX_ReadOneByte (0x7FFF);
				if(i==0x55){
						AT24CXX_WriteOneByte(0x7FFF,0xAA);
						i= AT24CXX_ReadOneByte (0x7FFF);
						if(i==0xAA){
							lcdpos (lcdcon -1,14); lcd_printf  ("OK");
						}
				}else {
						lcdpos (lcdcon -1,14); lcd_printf  ("NG");
						beep (2,100);
						while(left_start_key ==1 && right_start_key  == 1) delay_ms (10);
				}
		}
		cyc4or3run ();
		lcd_printf  ("电磁阀驱动检测");
		{
//				uint16_t Move_Test[6] = {MOVE1,MOVE2,MOVE3,MOVE4,MOVE5,MOVE6};
//				for( i = 0; i < 6 ; i ++){
//						Relay_Drive (Move_Test[i],SET);
//						delay_ms (300);
//						Relay_Drive (Move_Test[i],RESET);
//						delay_ms (300);
//				}	
		}
		{
				cyc4or3run ();
				lcd_printf  ("指示灯检查      ");
				Valve_Drive(Red_Light|Yellow_Light|Green_Light,RESET ); 
				cyc4or3run (); lcd_printf  ("红灯...         ");
				Valve_Drive(Red_Light,SET ); 
				cyc4or3run (); lcd_printf  ("黄灯...         ");
				Valve_Drive(Yellow_Light,RESET ); 
				cyc4or3run (); lcd_printf  ("绿灯...         ");
				Valve_Drive(Green_Light,RESET ); 
				Valve_Drive(Red_Light|Yellow_Light|Green_Light,RESET );
		}
		cyc4or3run ();
		lcd_printf  ("电机驱动信号检测");
		while( left_start_key == 1 && right_start_key  == 1){
				PUL = 1 ;DIR = 0;
				delay_ms (500);
				PUL = 0 ;DIR = 1;
				delay_ms (500);
		}
		PUL = 0 ;DIR = 0;
		cyc4or3run ();
		lcd_printf  ("电流检查...     ");
		{
				double Vref;
				Close_All_Point ();
				Enable_RES_Test_Analog_Switch ();
				Open_Two_Point (COMA,1,COMB ,1);
				delay_ms (100);
				Read_AD7176_Average_Voltage_mV (AIN0 ,AIN1, 8, &Vref );  //加载在待测电阻两端
				for(i=0;i < 20; i ++){
						Read_AD7176_Average_Voltage_mV (AIN0 ,AIN1, 8, &Vref );  //加载在待测电阻两端
						Vref /=10.0 ;
						lcdpos (lcdcon-1,0);
						lcd_printf  ("Cur=%5.3fmA      ",Vref);
						delay_ms (100);
				}
				lcdpos (lcdcon-1,14);
				if(Vref > (20.625-2) && Vref < (20.625+2)){
						lcd_printf ("OK");
				}else{
						lcd_printf ("NG");
						beep (2,100);
						while(left_start_key ==1 && right_start_key  == 1) delay_ms (10);
				}
				Close_All_Point ();
				Disable_RES_Test_Analog_Switch ();
		}
		startkeywait (1,1);
		Initialize_AD7176();
		delay_ms (1000);
		Self_Test_DAC_line(2000);		
		delay_ms (1000);
		Self_Check_Ananlog_Switch();
		delay_ms (1000);
		Short_Self_Check();
		cyc4or3run ();
		lcd_printf  ("1.8V信号检测 ");
		{
				Relay_Drive (K2_1V8_COMAB|K3_COMCD_IN2_3,SET);
				delay_ms (100);
				Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3, 10, &Vrx );  //加载在待测电阻两端
				cyc4or3run ();
				lcd_printf  ("VCC=%5.3fV      ",Vrx/1000.0);
				for(i=0;i < 20; i ++){
						Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3, 10, &Vrx );  //加载在待测电阻两端
						lcdpos (lcdcon-1,0);
						lcd_printf  ("VCC=%5.3fV      ",Vrx/1000.0);
						delay_ms (100);
				}
				lcdpos (lcdcon-1,14);
				if(Vrx > 1750 && Vrx < 1850){
						lcd_printf ("OK");
				}else{
						lcd_printf ("NG");
						beep (2,100);
						while(left_start_key ==1 && right_start_key  == 1) delay_ms (10);
				}
				Relay_Drive (K2_1V8_COMAB|K3_COMCD_IN2_3,RESET);
				delay_ms (100);
		}
		{
			cyc4or3run ();
			lcd_printf  ("电容测试线路检查");
			Relay_Drive(K7_CAP_COMAB,SET );
			Close_All_Point ();
			Open_Two_Point(COMA,1,COMB ,2);
			delay_ms (100);
			cyc4or3run ();
			lcd_printf  ("CAP=%5.3fmV      ",Vrx);
			while( left_start_key == 1 && right_start_key == 1){
//					Vrx = Cap_Test (1000)*4.0/9.0;  //加载在待测电阻两端
					lcdpos (lcdcon-1,0);
					lcd_printf  ("CAP=%5.3fuF      ",Vrx);
					delay_ms (100);
			}
			lcdpos (lcdcon-1,14);
			if(Vrx  < 2.66 &&Vrx > 1.78){
					lcd_printf ("OK");
			}else{
					lcd_printf ("NG");
					beep (2,100);
					while(left_start_key ==1 && right_start_key  == 1) delay_ms (10);
			}
			Relay_Drive(K7_CAP_COMAB,RESET );delay_ms (100);
		}
		Close_All_Point ();
		lcdreset ();
		cyc4or3run ();
		lcd_printf  ("调试完成");
		while(left_start_key ==1 && right_start_key  == 1) delay_ms (10);
}
#include "sup_fun.h"
#include "os.h"
#include "short.h"
#include "os_study.h"

Menu_List_Typedef Debug_List[] = 
{
	{"电磁阀调试    ", MOVE_debug_Fun           },
	{"摆盘机调试    ", Debug_Banpanji           },	
	{"点位量测      ", Ananlog_Switch_debug_fun },
	{"主板调试      ", Self_Check_Fun           },
	{"短路点排查    ", Short_Self_Check         },
	
	{"开路自检      ", Self_Check_Ananlog_Switch},	
	{"短路群学习    ", Read_OS_Group            },
	{"短路群检查    ", Short_Gooup_Edit_Check   },
	{"短路群查看    ", ViewShortGroup           },

	{NULL }
};



/**************************************************************************
	* File Name     : Up_Down_EACT_set
	* Description   : 上下运动电缸参数设置
  * Input         : 无
  * return        : 读取OK 0 反之非0
	* Author        : Morton
	* Date          : 2019/4/26
**************************************************************************/
uint8_t  DebugMode(void)
{
	Menu_List_Fun("调试模式",Debug_List);		
	RevertStartupScreen ();//显示界面	
	return 0;
}
