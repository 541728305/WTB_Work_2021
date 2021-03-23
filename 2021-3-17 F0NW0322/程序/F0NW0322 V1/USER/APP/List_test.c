#include "list_test.h"
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
#include "test_config.h"
#include "led.h"
#include "pF.h"
#include "data.h"
#include "pyd1698.h"
#include "Insulation.h"
#include "base_Config.h"
#include "rf.h"
#include "rf_id.h"
#include "hall.h"
//typedef enum {
//	Type_OS_Short = 0,
//	Type_OS_Open,
//	Type_Isrc ,
//	Type_Vsrc,
//	Type_Cap,
//	Type_pF_Cap,
//	Type_Diode,
//	Type_Current,
//	Type_Volts,
//	Type_TVS,
//	Type_Switch,
//	Type_LED,
//	Type_Hall,
//	Type_IC_ID,
//	Type_RF_ID,
//}Hardware_typedef ;
uint8_t  (*Type_fun[])(uint16_t *, uint16_t,uint16_t * )= {
	Type_OS_Short_Test_Fun,
	Type_OS_Open_Test_Fun,	
	Type_Isrc_Test_Fun,
	Type_Vsrc_Test_Fun,
	Type_Diode_Test_Fun,
	Type_Cap_Test_Fun,
	Type_pF_Cap_Test_Fun,

	Type_Current_Test_Fun,
	Type_Volts_Test_Fun,
	Type_TVS_Test_Fun,
	Type_Switch_Test_Fun,
	Type_LED_Test_Fun,
	Type_Hall_Test_Fun,
	Type_IC_ID_Test_Fun,
	Type_RF_ID_Test_Fun,
	NULL
};

uint16_t Step_buffer[Max_Step_Nummber];
/********************************************************************************
	* File Name     :Step_Test_Fun
	* Description   :单个测试项目调试
  * Input         :无
  * return        :无
	* Author        :Morton
	* Date          :2019/8/13
***********************************************************************************/
uint8_t List_Auto_Test_Fun(void){
	uint16_t  i = 0;
	uint16_t CNT = 0,TestStepN = 0,Auto_Test_Result = True,Temp = 0 ;
	
	for(Temp = 0 ; Temp < 10 ; Temp ++){
		i = 0;
		CNT = 0,TestStepN = 0,Auto_Test_Result = True ;
		lcdreset ();
		cyc4or3set(4);
		cyc4or3run();
		lcd_printf ("自动测试模式    ");
		if(Fixture.Software == ZDT_Software )
				ZDT_Software_Upload_Test_Item ();
		for( i = 0 ; i < Fixture.Test_Wait; i +=50)
				delay_ms (50);
		// *******short 测试 **************************************************
		if(TestConfig.Short  == ENABLE  && Auto_Test_Result == True){
			Auto_Test_Result |= Short_Test_Function(&TestStepN);
		}
		// *******short 测试 OVER *********************************************
		
		// *******Open 测试 **************************************************
		if(TestConfig.OPEN  == ENABLE && Auto_Test_Result == True){
			Auto_Test_Result |= Open_Test_Function(&TestStepN);
		}	
		// *******Open 测试 OVER *********************************************

		//****零件测试******************************************************
		if(TestConfig.Component  == ENABLE && Auto_Test_Result == True){

				for(i = 0;  Type_fun[i];  i++){
					CNT = Get_Currennt_Type_CNT(( Hardware_typedef)i,Step_buffer,Max_Step_Nummber);
					if(!CNT)
						continue ;
					Auto_Test_Result |= Type_fun[i](&TestStepN,CNT,Step_buffer);	
					if(Auto_Test_Result == False){
						 if(TestConfig.FAIL_continue  == ENABLE )
							 continue ; 
						 else 
								break;
					}
				}
		}
		
		if(TestConfig.FCT  == ENABLE ){
			
		}
		if(TestConfig.RF == ENABLE){
				WTB_Software_Upload_Data (Auto_Test_Result);
				Auto_Test_Result |= Type_RF_Test_Fun(&TestStepN,1 );
		}
		
		if(TestConfig.RF == DISABLE ){
			if(Fixture.Software == WTB_Software){
				Auto_Test_Result |= WTB_Software_Upload_Data (Auto_Test_Result);
				if(Auto_Test_Result >= 99){
					continue ;
				}
				
			}else if(Fixture.Software == ZDT_Software)
				Auto_Test_Result |= ZDT_Software_Upload_Data (Auto_Test_Result);
		}
		break ;
	}
	return Auto_Test_Result;
}	




/********************************************************************************
	* File Name     :Step_Test_Fun
	* Description   :单个测试项目调试
  * Input         :无
  * return        :无
	* Author        :Morton
	* Date          :2019/8/13
***********************************************************************************/
uint8_t List_Step_Test_Fun(){
	uint8_t  i;
	uint16_t CNT = 0,TestStepN = 0,Step_Test_Result = True ;
	lcdreset ();
	cyc4or3set(4);
	cyc4or3run();
	lcd_printf ("单步测试模式    ");
	// *******short 测试 **************************************************
	if(TestConfig.Short  == ENABLE ){
		Step_Test_Result |= Short_Test_Function(&TestStepN);
	}
	// *******short 测试 OVER *********************************************
	
	// *******Open 测试 **************************************************
	if(TestConfig.OPEN  == ENABLE ){
		Step_Test_Result |= Open_Test_Function(&TestStepN);
	}	
	// *******Open 测试 OVER *********************************************

	//****零件测试******************************************************
	if(TestConfig.Component  == ENABLE ){

			for(i = 0;  Type_fun[i];  i++){
				CNT = Get_Currennt_Type_CNT(( Hardware_typedef)i,Step_buffer,Max_Step_Nummber);
				if(!CNT)
					continue ;
				Step_Test_Result |= Type_fun[i](&TestStepN,CNT,Step_buffer);	
			}
	}
	if(TestConfig.FCT == ENABLE ){
		//	Step_Test_Result |= Init_PYD1698();
	}
	if(TestConfig.RF == ENABLE ){
		Step_Test_Result |= Type_RF_Test_Fun(&TestStepN,1);
	}
	if(Fixture.Software == WTB_Software){
		 WTB_Software_Upload_Data (Step_Test_Result);
	}else if(Fixture.Software == ZDT_Software)
	  ZDT_Software_Upload_Data (Step_Test_Result);
	//****零件测试OVER**************************
	return Step_Test_Result;
}	




