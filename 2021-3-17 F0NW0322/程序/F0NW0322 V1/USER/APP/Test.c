#include "test.h"
#include "os.h"
#include "diode.h"
#include "lcd3033.h"
#include "usart.h"
#include "Sup_Fun.h"
#include "global.h"
#include "delay.h"
#include "24cxx.h"
#include "open.h"
#include "short.h"
#include "sup_fun.h"
#include "zdt.h"
#include "mR.h"
#include "ohm.h"
#include "kohm.h"
#include "Mohm.h"
#include "kohm.h"
#include "other.h"
#include "uF.h"
#include "led.h"
#include "leakage_I.h"
#include "diode.h"
#include "ldo.h"
#include "ID.h"
#include "switch.h"
#include "sensor.h"
#include "laser.h"
#include "base_Config.h"


 //初始化整个测试项目
 Test_Item_TypeDef Test_Item[]={
//  NO.   Item Name**************Test Function***************Test Result****************************  
//	{ 1,   "SHORT ...    ",        Short_Test_Function,		  	  True,    ENABLE},	
//	{ 2,   "STEEL ...    ",        mohm_Test_Fun_4wire,			    True,    ENABLE},
//	{ 2,   "STEEL ...    ",        Read_ID,			    True,    ENABLE},
//	 
	 
//	  { 3,   "OPEN  ...    ",        Open_Test_Function,		  	  True,    ENABLE},
//	  { 1,   "Mohm_Test    ", 	     MOhm_RES_Test_Fun,           True,    ENABLE}, 
//  	{ 1,   "switch ...   ",        Switch_Test_Fun,		          True,    ENABLE},
		
//	{ 2,   "CAP   ...    ",        Max_Cap_Test_Fun,		    	  True,    ENABLE},
//	{ 3,   "diode ...    ",        Diode_Test_Fun,		      	  True,    ENABLE},
//  { 4,   "Sensor...    ",        ALS_Sensor_Test_Fun,		      True,    ENABLE},		

//  { 7,   "Leak I...    ",        Leakage_Current_Test_Fun,		True,    ENABLE},		
//	{ 1,   "SHORT ...    ",        Short_Test_Function,		  	  True,    ENABLE},	
//	{ 1,   "SHORT ...    ",        Ohm_RES_Test_Fun,		  	    True,    ENABLE},		  

//	{ 4,   "Kohm  ...    ", 	     KOhm_RES_Test_Fun,           True,    ENABLE}, 
//  { 8,   "ID    ...    ",        IC_Test_Fun,	              	True,    ENABLE},
//	{ 9,   "LDO   ...    ",        LDO_Test_Fun,	            	True,    ENABLE},


//	{ 1,   "led ...      ",        LED_Test_Fun,		      	   True,    ENABLE},
 
//	{ 5,   "Ohm_Test     ", 	     Ohm_RES_Test_Fun,           True,    ENABLE},  

	  { 7,   NULL}, 	
};
/*********************************************************************************************
	* 函数名test_item_debug
	* Description   :单个测试项目调试
  * Input         :无
  * return        :无
	* Author        :Morton
	* Date          :2018/11/18
*********************************************************************************************/
uint8_t test_item_debug( void ){
	uint8_t i = 0,Button_Status,Item_Result = True;
	u16 TestStepN = 0;
	Fixture.Mode  = Step_Test_Mode  ;
	while(1){
		lcdreset();
		cyc4or3run();
		lcd_printf  ("单项测试:       ");
		cyc4or3run ();
		lcd_printf ("%2d) %s",Test_Item[i].Test_Item_Num ,Test_Item[i].Test_Item_Name );
		cyc4or3run  ();
		lcd_printf ("L:调试  R:下一项");
		cyc4or3run  ();
		lcd_printf ("L+R:退出调试    ");
		Button_Status = Get_start_key_val();
		if(Button_Status == Left_Button_Pressed_Down ){
			TestStepN = 0;
			Turn_OFF_RYG_Light();
			Yellow_Light_ON();
			Item_Result =  Test_Item[i].Test_Item_Fun(&TestStepN);
			Yellow_Light_OFF();
			if(Item_Result == True ){
					Green_Light_ON();
			}
			else{
					Red_Light_ON();
			}
			step_test_mode_get_key  ();
		}else if(Button_Status == Right_Button_Pressed_Down ){
			do{
				i ++;
			}while(Test_Item[i].EN_Bit == DISABLE && Test_Item[i].Test_Item_Name != NULL );
			if(Test_Item[i].Test_Item_Name  == NULL){
				i = 0;
			}
		}else if( Button_Status == Double_Button_Pressed_Down ){
			break ;
		}
	}
	startkeywait (1,1);
	Turn_OFF_RYG_Light();
	RevertStartupScreen();
	Fixture.Mode =2;
	return 0;
}
/********************************************************************************
	* File Name     :Auto_Test_Fun
	* Description   :单个测试项目调试
  * Input         :无
  * return        :无
	* Author        :Morton
	* Date          :2018/11/18
***********************************************************************************/
uint8_t  Auto_Test_Fun(){
	u8 i,Auto_Test_Result = True ;
	u16 TestStepN = 0;
	lcdreset ();
	cyc4or3set(4);
	cyc4or3run();
	lcd_printf ("自动测试模式    ");
	//Upload_Test_Item();
	for(i = 0;Test_Item[i].Test_Item_Name  ;i++){
			if(Test_Item[i].Test_Item_Fun (  &TestStepN) == False ){
				Auto_Test_Result = False ;
				break ;	
			}
	}
	return Auto_Test_Result;
}
/********************************************************************************
	* File Name     :Step_Test_Fun
	* Description   :单个测试项目调试
  * Input         :无
  * return        :无
	* Author        :Morton
	* Date          :2018/11/18
***********************************************************************************/
uint8_t Step_Test_Fun(){
	uint8_t  i;
	uint16_t  TestStepN = 0,Step_Test_Result = True ;
	lcdreset ();
	cyc4or3set(4);
	cyc4or3run();
	lcd_printf ("单步测试模式    ");
	for(i=0;  Test_Item[i].Test_Item_Name;  i++){
		Step_Test_Result |= Test_Item[i].Test_Item_Fun ( &TestStepN);	
	}
	return Step_Test_Result;
}	
