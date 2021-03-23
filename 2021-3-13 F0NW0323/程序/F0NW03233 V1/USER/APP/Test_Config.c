#include "sys.h"
#include "test_config.h"
#include <string.h>
#include "sup_fun.h"                                  
#include "other.h"                                    
#include "lcd3033.h"                                                      
#include "data.h"    
#include "usart.h"

#define Ossfet_Pin_Num  2  

TestConfigTypedef  TestConfig;                                                                     
Item_Data_TypeDef Item_Data[Max_Step_Nummber];






 const Item_TypeDef Item[Max_Step_Nummber] = {
	 
//***	Group******Classs**********Type**************Name*******************Src*******Hsrc****H_test***LSrc***L_Test***STD_Value***Unit******LSL*****USL*****-delay	 

//	 {   1,      "O/S",          OS_Short,         "P1.7-P1.8",              100,       7,      7,     8,     8,        1.0,      "ohm",      0,      10,      0,    0       },	
//	 {   1,      "O/S",          OS_Short,         "P1.7-P1.9",              100,       7,      7,     9,     9,        1.0,      "ohm",      0,      10,      0,    0       },		 	 
//	 {   1,      "O/S",          OS_Short,         "P1.7-P1.10",             100,       7,      7,    10,    10,        1.0,      "ohm",      0,      10,      0,    0       },	

//	 {   1,      "O/S",          OS_Open,          "P1.1-P1.2",              100,       1,      1,     2,     2,        1.0,      "Mohm",     2,      99,      0,    0       },		 
//	 {   1,      "O/S",          OS_Open,          "P1.1-P1.3",              100,       1,      1,     3,     3,        1.0,      "Mohm",     2,      99,      0,    0       },		
//	 {   1,      "O/S",          OS_Open,          "P1.1-P1.4",              100,       1,      1,     4,     4,        1.0,      "Mohm",     2,      99,      0,    0       },		
//	 {   1,      "O/S",          OS_Open,          "P1.1-P1.5",              100,       1,      1,     5,     5,        1.0,      "Mohm",     2,      99,      0,    0       },			 
//	 {   1,      "O/S",          OS_Open,          "P1.1-P1.6",              100,       1,      1,     6,     6,        1.0,      "Mohm",     2,      99,      0,    0       },		 
//	 {   1,      "O/S",          OS_Open,          "P1.1-P1.7",              100,       1,      1,     7,     7,        1.0,      "Mohm",     2,      99,      0,    0       },		

//	 {   1,      "O/S",          OS_Open,          "P1.2-P1.3",              100,       2,      2,     3,     3,        1.0,      "Mohm",     2,      99,      0,    0       },		
//	 {   1,      "O/S",          OS_Open,          "P1.2-P1.4",              100,       2,      2,     4,     4,        1.0,      "Mohm",     2,      99,      0,    0       },		
//	 {   1,      "O/S",          OS_Open,          "P1.2-P1.5",              100,       2,      2,     5,     5,        1.0,      "Mohm",     2,      99,      0,    0       },			 
//	 {   1,      "O/S",          OS_Open,          "P1.2-P1.6",              100,       2,      2,     6,     6,        1.0,      "Mohm",     2,      99,      0,    0       },		 
//	 {   1,      "O/S",          OS_Open,          "P1.2-P1.7",              100,       2,      2,     7,     7,        1.0,      "Mohm",     2,      99,      0,    0       },		


//	 {   1,      "O/S",          OS_Open,          "P1.2-P1.4",              100,       2,      2,     4,     4,        1.0,      "Mohm",     2,      99,      0,    0       },		
//	 {   1,      "O/S",          OS_Open,          "P1.2-P1.5",              100,       2,      2,     5,     5,        1.0,      "Mohm",     2,      99,      0,    0       },			 
//	 {   1,      "O/S",          OS_Open,          "P1.2-P1.6",              100,       2,      2,     6,     6,        1.0,      "Mohm",     2,      99,      0,    0       },		 
//	 {   1,      "O/S",          OS_Open,          "P1.2-P1.7",              100,       2,      2,     7,     7,        1.0,      "Mohm",     2,      99,      0,    0       },		

	 {   1,      "steel",          OS_Short,          "STEL-J3200",              100,       119,      120,     	1,     	7,        1.0,      "ohm",     0,      5,      0,    0       },		
	 {   1,      "steel",          OS_Short,          "STEL-J3201",              100,       117,      118,     113,     107,        1.0,      "ohm",     0,      5,      0,    0       },			 
//	 {   1,      "O/S",          OS_Open,          "TP101-TP104",              100,       1,      2,     3,     4,        1.0,      "Mohm",     2,      99,      0,    0       },	
//	 
//	 {   1,      "O/S",          OS_Open,          "TP102-TP103",              100,       5,      6,     7,     8,        1.0,      "Mohm",     2,      99,      0,    0       },			 
//	 {   1,      "O/S",          OS_Open,          "TP102-TP104",              100,       5,      6,     3,     4,        1.0,      "Mohm",     2,      99,      0,    0       },	

//	 {   1,      "O/S",          OS_Open,          "TP103-TP104",              100,       7,      8,     3,     4,        1.0,      "Mohm",     2,      99,      0,    0       },			 

//	 
//	 
//	 {   1,      "S201",           SW_OFF1,         "S201_OFF1",               100,       1,       2,     3,     4,        1.0,      "Mohm",     2,      99,     0,    0       },
//	 {   1,      "S202",           SW_OFF1,         "S202_OFF1",               100,       5,       6,     3,     4,        1.0,      "Mohm",     2,      99,     0,    0       },	
//	 {   1,      "S203",           SW_OFF1,         "S203_OFF1",               100,       7,       8,     3,     4,        1.0,      "Mohm",     2,      99,     0,    0       },		 

//	 {   1,      "S201",           SW_ON_10R,       "S201_ON",                 100,       1,       2,     3,     4,        1.0,      "ohm",      0,     5.0,     0,    MOVE1       },
//	 {   1,      "S202",           SW_ON_10R,       "S202_ON",                 100,       5,       6,     3,     4,        1.0,      "ohm",      0,     5.0,     0,    MOVE2       },	
//	 {   1,      "S203",           SW_ON_10R,       "S203_ON",                 100,       7,       8,     3,     4,        1.0,      "ohm",      0,     5.0,     0,    MOVE3       },		 	 

//	 {   1,      "S201",           SW_OFF2,         "S201_OFF2",               100,       1,       2,     3,     4,        1.0,      "Mohm",     2,      99,     0,    0       },
//	 {   1,      "S202",           SW_OFF2,         "S202_OFF2",               100,       5,       6,     3,     4,        1.0,      "Mohm",     2,      99,     0,    0       },	
//	 {   1,      "S203",           SW_OFF2,         "S203_OFF2",               100,       7,       8,     3,     4,        1.0,      "Mohm",     2,      99,     0,    0       },		 
	 

	 	
	
	{     0,       "NA",   Reserved,      NULL }	                                                                                                       
};
/*********************************************************************************************
	* File Name     : InitTestConfig
	* Description   : InitTestConfig
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 12-OCT-2019
*********************************************************************************************/
void InitTestConfig(void){	
//自动是否显示测试项目	
	TestConfig.Isrc          = DISABLE;
	TestConfig.OS_Open       = DISABLE;
	TestConfig.OS_Short      = DISABLE;
	TestConfig.Vsrc          = DISABLE;
	TestConfig.Cap           = DISABLE;
	TestConfig.pF_Cap        = DISABLE;
	TestConfig.Diode         = DISABLE;
	TestConfig.Hall          = DISABLE;
	TestConfig.Current       = DISABLE;
	TestConfig.Volts         = DISABLE;
	TestConfig.TVS           = DISABLE;
	TestConfig.Switch        = DISABLE;
	TestConfig.LED           = DISABLE;
	TestConfig.RF_ID         = DISABLE;
//测试配置
	TestConfig.Short         = ENABLE ;
	TestConfig.OPEN          = ENABLE ;
	TestConfig.Component     = ENABLE;
	TestConfig.FCT           = DISABLE ;
	TestConfig.RF            = DISABLE ;	
	TestConfig.FAIL_continue = DISABLE ;
	TestConfig.OpenList      = DISABLE ;
	
}

/*********************************************************************************************
	* File Name     : Read_Toatl_Item_Num
	* Description   : Read_Toatl_Item_Num
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 12-OCT-2019
*********************************************************************************************/
uint16_t Get_Currennt_Type_CNT( Hardware_typedef Type,uint16_t *StepNumberBuf,uint16_t Max_StepNumber ){
	uint16_t i = 0, CNT = 0 ;
	for(i = 0; i < Max_StepNumber; i ++ )
	{
		StepNumberBuf[i] = 0;
	}
	for( i =0 ; Item[i].Name ; i ++){
		if(Type == Type_OS_Short && Item[i].Type == OS_Short  ){
			StepNumberBuf[CNT] = i;
			CNT ++;
			continue ;
		}
		if(Type == Type_OS_Open && Item[i].Type == OS_Open   ){
			StepNumberBuf[CNT] = i;
			CNT ++;
			continue ;
		}
		if(Type == Type_Isrc && Item[i].Type == R_Isrc_10ohm ){
			StepNumberBuf[CNT] = i;
			CNT ++;
			continue ;
		}
		if(Type == Type_Vsrc &&(Item[i].Type == R_Vsrc_10ohm||Item[i].Type == R_Vsrc_1Kohm||Item[i].Type == R_Vsrc_20Kohm)){
			StepNumberBuf[CNT] = i;
			CNT ++;
			continue ;
		}
		if(Type == Type_Cap &&( Item[i].Type == C_100ohm||Item[i].Type == C_1Kohm||Item[i].Type == C_10Kohm||\
														Item[i].Type ==C_100Kohm||Item[i].Type ==C_1Mohm)){
			StepNumberBuf[CNT] = i;
			CNT ++;
			continue ;
		}
		if(Type == Type_pF_Cap && Item[i].Type == C_10Kohm_pF ){
			StepNumberBuf[CNT] = i;
			CNT ++;
			continue ;
		}	
		if(Type == Type_Diode &&(Item[i].Type == D_10R||Item[i].Type == D_1Kohm||Item[i].Type == D_20Kohm)){
			StepNumberBuf[CNT] = i;
			CNT ++;
			continue ;
		}
		if(Type == Type_Current &&(Item[i].Type == I_10R||Item[i].Type == I_1Kohm||Item[i].Type == I_20Kohm)){
			StepNumberBuf[CNT] = i;
			CNT ++;
			continue ;
		}
		if(Type == Type_Volts &&(Item[i].Type == V_10R||Item[i].Type == V_1Kohm||Item[i].Type == V_20Kohm)){
			StepNumberBuf[CNT] = i;
			CNT ++;
			continue ;
		}
		if(Type == Type_TVS &&(Item[i].Type == TVS_10R||Item[i].Type == TVS_1Kohm||Item[i].Type == TVS_20Kohm)){
			StepNumberBuf[CNT] = i;
			CNT ++;
			continue ;
		}
		if(Type == Type_Switch &&(Item[i].Type == SW_OFF1||Item[i].Type == SW_ON_10R||Item[i].Type == SW_ON_1Kohm||Item[i].Type == SW_ON_20Kohm||Item[i].Type == SW_OFF2)){
			StepNumberBuf[CNT] = i;
			CNT ++;
			continue ;
		}	
		if(Type == Type_LED &&( Item[i].Type == LED_VF||Item[i].Type == LED_Color_R||
														Item[i].Type == LED_Color_G||Item[i].Type ==LED_Color_B)){
			StepNumberBuf[CNT] = i;
			CNT ++;
			continue ;
		}	

		if(Type == Type_Hall &&( Item[i].Type == Hall_10R || Item[i].Type == Hall_1Kohm || Item[i].Type == Hall_20Kohm)){
			StepNumberBuf[CNT] = i;
			CNT ++;
			continue ;
		}
		if(Type == Type_IC_ID &&( Item[i].Type == IC_ID)){
			StepNumberBuf[CNT] = i;
			CNT ++;
			continue ;
		}		
		if(Type == Type_RF_ID &&( Item[i].Type == RF_ID)){
			StepNumberBuf[CNT] = i;
			CNT ++;
			continue ;
		}
		
	}
	return CNT ;
}


///*********************************************************************************************
//	* File Name     : Read_Toatl_Item_Num
//	* Description   : Read_Toatl_Item_Num
//  * Input         : /
//	* return        : /
//	* Version       : V1.0
//	* Author        : Morton
//	* Date          : 12-OCT-2019
//*********************************************************************************************/
//void Cal_Every_Group_Num(uint16_t *Every_Type_Num ){
//	uint16_t i = 0,__Type = 0,buf[Hardware_typedef_Total];
//	for(i = 0; i < Hardware_typedef_Total; i ++ ){
//		buf[i] = 0;
//	}
//	
//	for( i =0 ; Item[i].Name ; i ++){
//		__Type = Item[i].Type ;
//		switch (__Type){		

//			case OS_Short     :    Step_Number_buffer[Type_OS_Short][buf[Type_OS_Short]] = i;		
//				                     buf[Type_OS_Short] ++;  
//			                       break ;	
//			
//			case OS_Open      :    Step_Number_buffer[Type_OS_Open][buf[Type_OS_Open]] = i;		
//				                     buf[Type_OS_Open] ++;  
//			                       break ;	
//			
//			case  R_Isrc_10ohm :   Step_Number_buffer[Type_Isrc][buf[Type_Isrc]] = i;				
//					                   buf[Type_Isrc] ++;  
//					                   break ;
//			
//			case	R_Vsrc_10ohm: 
//			case	R_Vsrc_1Kohm:
//			case	R_Vsrc_20Kohm:   Step_Number_buffer[Type_Vsrc][buf[Type_Vsrc]] = i;				
//														 buf[Type_Vsrc] ++;  
//														 break ;
//			case	C_100ohm:
//			case	C_1Kohm:
//			case	C_10Kohm:
//			case	C_100Kohm:      
//			case  C_1Mohm :		     Step_Number_buffer[Type_Cap][buf[Type_Cap]] = i;				
//					                   buf[Type_Cap] ++;  
//					                   break ;
//			
//			case  C_10Kohm_pF :    Step_Number_buffer[Type_pF_Cap][buf[Type_pF_Cap]] = i;				
//			                       buf[Type_pF_Cap] ++;  
//			                       break ;
//			case	D_10R:
//			case	D_1Kohm:
//			case	D_20Kohm:				 Step_Number_buffer[Type_Diode][buf[Type_Diode]] = i;				
//					                   buf[Type_Diode] ++; 
//					                   break ;		
//			case	I_10R:
//			case	I_1Kohm:
//			case	I_20Kohm:       Step_Number_buffer[Type_Current][buf[Type_Current]] = i;		
//				                    buf[Type_Current] ++;  

//			                      break ;		
//			case	V_10R:
//			case	V_1Kohm:
//			case	V_20Kohm:       Step_Number_buffer[Type_Volts][buf[Type_Volts]] = i;	
//				                    buf[Type_Volts] ++;  
//			                      break ;	
//			case	TVS_10R:
//			case	TVS_1Kohm:
//			case	TVS_20Kohm:     Step_Number_buffer[Type_TVS][buf[Type_TVS]] = i;	
//				                    buf[Type_TVS] ++; 		
//			                      break ;	
//			case	SW_OFF1:
//			case	SW_ON:
//			case	SW_OFF2:        Step_Number_buffer[Type_Switch][buf[Type_Switch]] = i;	
//				                    buf[Type_Switch] ++;  
//			                      break ;
//			case	LED_VF:
//			case	LED_Color_R:
//			case	LED_Color_G:
//			case	LED_Color_B:    Step_Number_buffer[Type_LED][buf[Type_LED]] = i;
//				                    buf[Type_LED] ++;  
//			                      break ;

//			case  RF_ID :          Step_Number_buffer[Type_RF_ID][buf[Type_RF_ID]] = i;	
//				                    buf[Type_RF_ID] ++; 		
//			                      break ;	
//			
//			
//			
//		  default :             break ;
//		}
//	}
//	for(i = 0; i < Hardware_typedef_Total; i ++ ){
//		Every_Type_Num[i] = buf[i];
////		Uart_printf (USART1,"Type&%d-Toal=%d\r\n",i,buf[i]);
////		cyc4or3run ();
////		lcd_printf ("Type&%d-Toal=%d",i,buf[i]);	
////	  step_test_mode_get_key ();
//	}
//}

