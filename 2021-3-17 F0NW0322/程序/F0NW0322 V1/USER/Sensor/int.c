#include "int.h"
#include "analog_switch.h"
#include "ps_als.h"
#include "lcd3033.h"
#include "myiic.h"
#include "net_iic.h"
#include "usart.h"
#include "global.h"
#include "delay.h"
#include "Sup_Fun.h"
#include "other.h"
#include "als.h"
#include "dac.h"
#include "ad7176.h"
extern  uint16_t  Test_Item_Num;
extern  uint8_t lcdcon,testmode ;
extern  ALS_Test_TypeDef  U2;

uint8_t Sensot_INT_Test(void){
		uint8_t INT_Test_Result = True, k, CNT = 0 ;
		double INT_Volts = 0.0,Vol[10];
		DAC_Set_Vol(1800); //Connect_ADC_Ref_Res_K15
		Net_IIC_Init();
//		Valve_Drive( Connect_ADC_COMCD_K17|Connect_Src_COMA_COMB|Connect_Src_Vol_K18|Connect_Ref_Res_20K,SET);
		Open_Two_Point (COMD,U2.GND_Pin,COMC,U2.INT_Pin ); //利用OS测试的20K电阻做上拉测中断
		Open_Single_Point(COMA,U2.INT_Pin );
		Open_Two_Point (COMA,U2.INT_Pin,COMB,5 ); 
		delay_ms(200);
		//中断脚测试
		if(testmode == Step_Test_Mode || INT_Test_Result == True ){
				cyc4or3run ();
				lcd_printf ("PROX_OFF_INT:   ");
				Write_OneByteToDevice(AlS_Slave_Addr,0xA0,0x01); 	//0x01进入Sleep State
				Write_OneByteToDevice(AlS_Slave_Addr,0xA0,0x01);
				delay_ms (50);
				if(testmode ==  Auto_Test_Mode ){
						for(k = 0; k < 100; k ++){
								delay_us (100);
								Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3,10,&INT_Volts );
								INT_Volts /= 1000.0;
								if(INT_Volts > 1.8){
										while(INT_Volts > 1.8){
											INT_Volts -= 0.013254;
										}
								}
								if( INT_Volts > U2.INT_H_LSL && INT_Volts < U2.INT_H_USL ){
										Vol[CNT] = INT_Volts;
										CNT ++;
								}
								else {
										U2.INT_H_Value = INT_Volts;
										CNT = 0;
								}
								if(CNT == 10){
										U2.INT_H_Value = Average_Fun (Vol,10); 
										break ;
								}
					  }
						cyc4or3run ();
						lcd_printf ("     %5.3fV     ",U2.INT_H_Value);
				}
				if(testmode == Step_Test_Mode ){
						cyc4or3run ();
						lcd_printf ("      ---      ");
						while(left_start_key ==1&&right_start_key ==1){
								for( k = 0; k < 10 ; k ++){
										Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3,10,&Vol[k] );
										if(Vol[k] > 1.8){
										while(Vol[k] > 1.8){
											Vol[k] -= 0.013254;
										}
								}
								}
								U2.INT_H_Value = Average_Fun (Vol,10)/1000.0; 
								lcdpos (lcdcon -1,0);
								lcd_printf ("     %5.3fV     ",U2.INT_H_Value);
								delay_ms (200);
						}
						startkeywait (1,1);
				}
				lcdpos (lcdcon-1,14);
				if(U2.INT_H_Value > U2.INT_H_LSL && U2.INT_H_Value < U2.INT_H_USL  ){//中断脚测试，3mA，0.5 6mA 
						lcd_printf ("OK");
						Uart_Printf(USART1,"%0.3f#",U2.INT_H_Value);
				}else{
						INT_Test_Result |= False ;
						lcd_printf ("NG"); 
						Uart_Printf(USART1,"%0.3@#",U2.INT_H_Value);
						if(testmode == Step_Test_Mode )
								step_test_mode_get_key ();
				}
				Test_Item_Num ++;
		}
		//中断低测试
		if(testmode == Step_Test_Mode || INT_Test_Result == True ){
				cyc4or3run ();
				lcd_printf ("PROX_ON_INT:    "); 
				if(Sensor_Configuration()== False){
						delay_ms (10); //配置失败，延时10ms重新配置一次
						if(Sensor_Configuration()== False){
								cyc4or3run ();
								lcd_printf ("U2配置NG        ");
								INT_Test_Result |= False;
								if(testmode == Auto_Test_Mode )
										return INT_Test_Result;
						}
				}
				if(testmode ==  Auto_Test_Mode ){
						for(k = 0; k < 100; k ++){
								delay_us (100);
								Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3,10,&INT_Volts );
								INT_Volts /= 1000.0;
								if( INT_Volts > U2.INT_H_LSL && INT_Volts < U2.INT_H_USL ){
										Vol[CNT] = INT_Volts;
										CNT ++;
								}
								else {
										U2.INT_H_Value = INT_Volts;
										CNT = 0;
								}
								if(CNT == 10){
										U2.INT_H_Value = Average_Fun (Vol,10); 
										break ;
								}
					  }
						cyc4or3run ();
						lcd_printf ("     %5.3f     ",U2.INT_H_Value);
				}
				if(testmode == Step_Test_Mode ){
						cyc4or3run ();
						lcd_printf ("      ---      ");
						while(left_start_key ==1&&right_start_key ==1){
								for( k = 0; k < 10 ; k ++){
										Read_AD7176_Average_Voltage_mV (AIN2 ,AIN3,10,&Vol[k] );
								}
								U2.INT_H_Value = Average_Fun (Vol,10)/1000.0; 
								lcdpos (lcdcon -1,0);
								lcd_printf ("     %5.3f     ",U2.INT_H_Value);
								delay_ms (200);
						}
						startkeywait (1,1);
				}
				lcdpos (lcdcon-1,14);
				if(U2.INT_H_Value > U2.INT_L_LSL && U2.INT_H_Value < U2.INT_L_USL  ){//中断脚测试，3mA，0.5 6mA 
						lcd_printf ("OK");
						Uart_Printf(USART1,"%0.3f#",U2.INT_H_Value);
				}else{
						INT_Test_Result |= False ;
						lcd_printf ("NG"); 
						Uart_Printf(USART1,"%0.3@#",U2.INT_H_Value);
						if(testmode == Step_Test_Mode )
								step_test_mode_get_key ();
				}
			Test_Item_Num ++;
		}
//		Valve_Drive( Connect_ADC_COMCD_K17|Connect_Src_COMA_COMB|Connect_Src_Vol_K18|Connect_Ref_Res_20K, RESET);
		Close_All_Point ();
		delay_ms (80);
		return INT_Test_Result ;
}

