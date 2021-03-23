#include "sensor.h"
#include "lcd3033.h"
#include "myiic.h"
#include "net_iic.h"
#include "usart.h"
#include "ad7176.h"
#include "delay.h"
#include "Sup_Fun.h"
#include "analog_switch.h"
#include "other.h"
#include "dac.h"
#include "global.h"
#include "test.h"



#define TM27024 0
#define STK3338 1
#define LTR2568 2

uint8_t ALS_Sensor_Name = TM27024;

ALS_Test_TypeDef  U2 = {
		"U102",
		{"VDD",    "GND",    "SCL",    "SDA",   "INT",   "LEDA"},
			 1,        5,        3,        4,       0,       2,
		0x49
};


/*********************************************************************************************
	* File Name     : Set_Sensor_Test_Relay_SET
	* Description   : Set_Sensor_Test_Relay_SET
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 3-Oct-2019
*********************************************************************************************/
void Set_Sensor_Test_Relay_SET (){
		Valve_Drive (K1_Min_Ref|K2_Src_COMAB|K7_IIC_COMAB|K8_2V8_GND_COMCD|K9_Ref_IN0_1|K10_Src_Choice, SET); //连接IIC总线，供电1.8V，串10K电阻
		Open_Three_Point (COMA,U2.Vdd_Pin ,COMB, U2.GND_Pin,COMC ,U2.LEDA_Pin);	
		DAC_Set_Vol(1800); 
		delay_ms (80);	
}
/*********************************************************************************************
	* File Name     : Set_Sensor_Test_Relay_RESET
	* Description   : Set_Sensor_Test_Relay_RESET
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 3-Oct-2019
*********************************************************************************************/
void Set_Sensor_Test_Relay_RESET (){
		Valve_Drive (K1_Min_Ref|K2_Src_COMAB|K7_IIC_COMAB|K8_2V8_GND_COMCD|K9_Ref_IN0_1|K10_Src_Choice, RESET); //连接IIC总线，供电1.8V，串10K电阻
		Close_All_Point ();	
		DAC_Set_Vol(0); 
		delay_ms (100);	
}

#include "TMD27024_I.h"
#include "TMD27024_als.h"

#include "STK3338_ALS.h"
#include "STK3338_i.h"

#include "LTR_2568_ALS.h"
#include "LTR_2568_i.h"
#include "24cxx.h" 
/*********************************************************************************************
	* File Name     : Set_ALS_Sensor_Name
	* Description   : Set_ALS_Sensor_Name
  * Input         : Num
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 6-Oct-2019
*********************************************************************************************/
void Set_ALS_Sensor_Name( uint8_t Num){
	ALS_Sensor_Name = Num;
	switch(ALS_Sensor_Name){
		case TM27024 : 	 AlS_Slave_Addr = 0x49; break ;
		case STK3338 : 	 AlS_Slave_Addr = 0x47; break ;
		case LTR2568 : 	 AlS_Slave_Addr = 0x23; break ;
		default :        break;
	}		
}

/*********************************************************************************************
	* File Name     : ALS_Sensor_Test_Fun
	* Description   : ALS_Sensor_Test_Fun
  * Input         : *TestStepN
	* return        : Total_Test_Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 3-Oct-2019
*********************************************************************************************/
uint8_t ALS_Sensor_Test_Fun(uint16_t *TestStepN){
		uint8_t  Total_Test_Result = True ;
		Close_All_Point ();
		DAC_Set_Vol(0); 
		// LEDA  Current test... Supply current test...	
		if(testmode == Step_Test_Mode || Total_Test_Result == True ){	
			switch(ALS_Sensor_Name){
				case TM27024 : 	 Total_Test_Result |= TMD27024_Cur_Test(TestStepN); break ;
				case STK3338 : 	 Total_Test_Result |= STK3338_Cur_Test(TestStepN); break ;
				case LTR2568 : 	 Total_Test_Result |= LTR2568_Cur_Test(TestStepN); break ;
				default :        break;
			}
		
		}
		if(testmode == Step_Test_Mode || Total_Test_Result == True ){
			Valve_Drive (LED_Block ,SET);
			delay_ms(500);
		}
		// read chip id + ambient light sensor ps test 
		if(testmode == Step_Test_Mode || Total_Test_Result == True ){
			switch(ALS_Sensor_Name){
				case TM27024 : 	 Total_Test_Result |= TMD27024_ALS_Test_Fun(TestStepN); break ;
				case STK3338 : 	 Total_Test_Result |= STK3338_ALS_Test_Fun(TestStepN); break ;
				case LTR2568 : 	 Total_Test_Result |= LTR2568_ALS_Test_Fun(TestStepN); break ;
				default :        break;
			}			
			//	Total_Test_Result |= Sensor_ALS_Test(TestStepN);
		}	
		Valve_Drive (MOVE1|MOVE2|MOVE3|MOVE4|MOVE5|MOVE6,RESET);
		Set_Sensor_Test_Relay_RESET();
		return Total_Test_Result ;
}






///******************************************************************************************************
// * 函数名: IIC_Test_Fun
// * 参  数：Addr,从机地址，reg寄存器地址，RW读写
// * 返回值：读取返回寄存器值，写OK返回ox00，失败返回0xFF
// * 功  能：读写寄存器
// * 作  者：Morton
// * 日  期：2018.8.23
// * 修  改：NA
//******************************************************************************************************/
//uint8_t  IIC_Test_Fun(uint8_t Addr,uint8_t reg,uint8_t data,uint8_t RW,uint8_t Length ){
//		uint8_t ch[20],i;
//		Net_IIC_Init();
//		if(RW == Write){
//				if( Write_OneByteToDevice(Addr,reg,data) == True){ //0x01进入Sleep State
//						return 0x00 ;
//				}else{
//						return 0xFF ;
//				}
//		}
//		else if(RW == Read){
//					if(Read_NByteFromDevice(Addr,reg,ch,Length) == True ){
//							for(i = 0; i < Length; i ++ ){

//							}								
//					}else{
//						return 0xFF;
//					}
//		}
//		return 0x00 ;
//}
