#include "lcd3033.h"
#include "myiic.h"
#include "net_iic.h"
#include "global.h"
#include "delay.h"
#include "Sup_Fun.h"
#include "other.h"
#include "sensor.h"
#include "test.h"
#include "tmd27024_als.h"
#include <string.h>


extern  ALS_Test_TypeDef  U2;
extern  ALS_Sensor_TypeDef TMD27024_ALS[];
/*********************************************************************************************
	* File Name     : Sensor_Configuration
	* Description   : Configuration all resister 
  * Input         : /
	* return        : ack.nack
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
uint8_t  TMD27024_Configuration( void ){
		uint16_t  Clear_Channel_Low_Threshold,Clear_Channel_High_Threshold;
		uint16_t  PS_Low_Threshold,PS_High_Threshold;
		Net_IIC_Init();
		//Bit0: the internal oscillator Enable Bit1:ALS actives. Bit2 :proximity activates Bit3: activates the wait feature
		if(Write_OneByteToDevice(AlS_Slave_Addr ,0x80,0x07))		  return False ;
		if(Write_OneByteToDevice(AlS_Slave_Addr, 0x81,0x23))		  return False ;//RGBC时间寄存器 cycle 1,2.78ms,1024 max counts 100ms
		if(Write_OneByteToDevice(AlS_Slave_Addr, 0x82,0x1F))		  return False ;//This register defines the duration of 1 Prox Sample,which is (PRATE + 1)*88us.
		if(Write_OneByteToDevice(AlS_Slave_Addr, 0x83,0x00))		  return False ;//Value that specifies the wait time between ALS and proximity cycles in 2.78ms increments 
	
		Clear_Channel_Low_Threshold = 750; //Clear Channel 中断下限设置	38.87-48.59-58.32 Gain = 16  621.82 777.44 933.12
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x84,(uint8_t)(Clear_Channel_Low_Threshold&0xFF)))		  return False ;
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x85,(uint8_t)(Clear_Channel_Low_Threshold>>8)))		    return False ;
	
		Clear_Channel_High_Threshold = 850;//Clear Channel 中断上限设置	
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x86,(uint8_t)(Clear_Channel_High_Threshold&0xFF)))	    return False ;
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x87,(uint8_t)(Clear_Channel_High_Threshold>>8)))		  return False ;
	
		PS_Low_Threshold = 750;//Clear Channel 中断上限设置	
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x88,(uint8_t)(PS_Low_Threshold&0xFF)))	    return False ;
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x89,(uint8_t)(PS_Low_Threshold>>8)))		    return False ;
	
		PS_High_Threshold = 850;
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x8A,(uint8_t)(PS_High_Threshold&0xFF)))	    return False ;
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x8B,(uint8_t)(PS_High_Threshold>>8)))		    return False ;
		// Bit；7:4 the proximity persistence filter. Bit：3:0 the ALS persistence filter.
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x8C,0x44))		return False ; 
		// CFG0 Register
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x8D,0x40))		return False ; //等待时间寄存器WLONG=0中断控制寄存器，1次超出范围，为有效中断
		// Bit:7:6  PPULSE_LEN 8us/32us  5:0 Maximum number of pulses in a single proximity cycle
//		if(Write_OneByteToDevice(AlS_Slave_Addr,0x8E,0x0F))		return False ;
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x8E,0xC7))		return False ; 
		// 7:6  PGAIN   4X(10)  5:4 00 default  3:0 PLDrive: 19mA 0100 0:gainX1 X2
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x8F,0xC8))		return False ;  // Filed Value  10 
		//Notice : Bit6 = 1  IR_MUX  Bit4:0  64X 00101=7 ,不开启IR复用功能 
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x90,0x03))		return False ;  //使能光感饱和中断 ALS2X=0 Gain2X=0
		//0x91,REVID Register
		//0x92,ID Register
		//0x93,Status Register
		//0x94-0x9D C&R&G&B&P  reg
		//0x9E REVID2 Register
		//CFG2 
	  //if(Write_OneByteToDevice(AlS_Slave_Addr,0x9F,0x00))		return False ;  
		// SOFTRST Register
		//if(Write_OneByteToDevice(AlS_Slave_Addr,0xA0,0x00))		return False ;  
		//CFG3 Register Bit7: If set, then all flag bits in the STATUS register will be reset whenever the STATUS register is read over I睠.
		// Bit4 :  disable    The Sleep After Interrupt bit is used to place the device into a low power mode upon an interrupt pin assertion.
		if(Write_OneByteToDevice(AlS_Slave_Addr,0xAB,0x04))		return False ;  
		// CFG4 Register, Reserved. Must be set to 0x3D.  Default:0x3F
		if(Write_OneByteToDevice(AlS_Slave_Addr,0xAC,0x3D))		return False ;  
		// Bit6: Proximity automatic pulse control (APC) disable.
		if(Write_OneByteToDevice(AlS_Slave_Addr,0xAE,0x3F))		return False ;  //CHR偏移设置为0	
		//0xC0-C1  POFFSETH 
		if(Write_OneByteToDevice(AlS_Slave_Addr,0xD7,0x00))		return False ;  
		// 0xD9 0XDC CALIBCFG Register
		if(Write_OneByteToDevice(AlS_Slave_Addr,0xDD,0xFE))		return False ;   //使能所有中断
//{
//		uint8_t  ch[50],i;
// 	Read_NByteFromDevice (AlS_Slave_Addr ,0x80,ch,30);
// 	for(i=0;i<20;i++){
// 		cyc4or3run ();
// 		lcd_printf ("REG%02X=%02X        ",(i+0x80),ch[i]);
// 		step_test_mode_get_key ();
// 	}
//}	
	return  True;
}

/*********************************************************************************************
	* File Name     : Ambient_Light_Sensor_Test
	* Description   : Check color Ambient_Light_Sensor
  * Input         : Num
	* return        : Test_Resut
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
uint8_t TMD27024_ALS_Test( uint8_t Num){
		uint8_t Light_Sensor_Result = True,ch[20],i,CNT = 0;		
		if(TMD27024_ALS[Num].Condition){// Set Ambient_Light_Sensor test condition 
				Valve_Drive (MOVE1|MOVE4|MOVE5,RESET);
				Valve_Drive(TMD27024_ALS[Num].Condition,SET );
		}
		if(TMD27024_Configuration()== False){
				delay_ms (10); 
				if(TMD27024_Configuration()== False){
						cyc4or3run ();
						lcd_printf ("U201配置NG      ");
						Light_Sensor_Result |= False;
						if(testmode == Auto_Test_Mode ){
							return Light_Sensor_Result;
						}
				}
		}
		if( Light_Sensor_Result == True ){
				delay_ms(TMD27024_ALS[Num].Time );
				CNT = 0;
				for ( i = 0; i < 200; i ++){
						delay_us (50);
						if(Read_NByteFromDevice (AlS_Slave_Addr ,TMD27024_ALS[Num].Addr ,ch,TMD27024_ALS[Num].Num )==0){
								TMD27024_ALS[Num].Value = (ch[0]|(ch[1]<<8));
						}else{
								Light_Sensor_Result |= False;
								if(testmode == Auto_Test_Mode)
										return Light_Sensor_Result;		
						}
						if(TMD27024_ALS[Num].Value >= TMD27024_ALS[Num].LSL  && TMD27024_ALS[Num].Value <= TMD27024_ALS[Num].USL){
								CNT ++;
						}else{
								CNT = 0;
						}
						if(CNT == 8)
								break ;
				}	
				cyc4or3run ();
				lcd_printf ( "    %8d    ",TMD27024_ALS[Num].Value);	
		}		
		if(testmode == Step_Test_Mode ){
				if(left_start_key == 1 || right_start_key == 1){
					while(left_start_key == 1&&right_start_key == 1){
							if(TMD27024_Configuration()== False){
									lcdpos(lcdcon-1,0);
									lcd_printf ("U201配置NG      ");
							}else{
									if(Read_NByteFromDevice (AlS_Slave_Addr ,TMD27024_ALS[Num].Addr ,ch,TMD27024_ALS[Num].Num )==0){
											TMD27024_ALS[Num].Value = (ch[0]|(ch[1]<<8));
											lcdpos(lcdcon-1,0);
											lcd_printf ( "    %8d    ",TMD27024_ALS[Num].Value);		
									}
							}
							delay_ms (50);
					}
					startkeywait (1,1);
				}
		}
		lcdpos(lcdcon -1,14);
		if(TMD27024_ALS[Num].Value >= TMD27024_ALS[Num].LSL  && TMD27024_ALS[Num].Value <= TMD27024_ALS[Num].USL){
				lcd_printf ("OK");
				Light_Sensor_Result = True;
		}else{
				Light_Sensor_Result |= False;
				lcd_printf ("NG");
		}
		return Light_Sensor_Result;	
}
/*********************************************************************************************
	* File Name     : Sensor_ID_Test
	* Description   : read als snesor id
  * Input         : Num
	* return        : Test_Resut
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
static  uint8_t  TMD27024_ID_Test(uint8_t Num){
		uint8_t ch[10],CNT = 0,i,ID = 0xFF,Test_Resut = True;
		Net_IIC_Init();
		delay_ms (10);
		for ( i = 0; i < 100; i ++){
				Write_OneByteToDevice(AlS_Slave_Addr,0xA0,0x00); //0x01进入Sleep State
				if(Read_OneByteFromDevice(AlS_Slave_Addr, TMD27024_ALS[Num].Addr ,ch)== True){
						ID = ch[0];
						CNT ++;
				}else{
						CNT = 0;
				}
				if(CNT == 10){
					 TMD27024_ALS[Num].Value = ID; 
					 break ;
				}
				delay_us (100);
		}
		cyc4or3run ();
		lcd_printf ( "      0X%02X      ",TMD27024_ALS[Num].Value);		
		if(testmode == Step_Test_Mode){
				while(left_start_key ==1&&right_start_key ==1){
						if(Read_OneByteFromDevice(AlS_Slave_Addr,TMD27024_ALS[Num].Addr,ch)== True){
								TMD27024_ALS[Num].Value = ch[0];
						}else{
								TMD27024_ALS[Num].Value = 0xFF;
						}
						lcdpos (lcdcon -1 ,0);
						lcd_printf ( "      0X%02X      ",TMD27024_ALS[Num].Value);	
						delay_ms (150);
				}
				startkeywait (1,1);
		}
		lcdpos (lcdcon-1, 14);
		if(TMD27024_ALS[Num].Value  == TMD27024_ALS[Num].USL ){
				Test_Resut = True;
				lcd_printf ("OK");
		}else{
				Test_Resut |= False;
				lcd_printf ("NG");
				if(testmode == Step_Test_Mode )
						step_test_mode_get_key ();
		}
		return Test_Resut;
}

/*********************************************************************************************
	* File Name     : Diode_Test_Fun
	* Description   : Diode_Test  test voltage < 4000mV
  * Input         : *TestStepN
	* return        : Total_Test_Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
u8 TMD27024_ALS_Test_Fun(u16 *TestStepN){
		u8 i = 0,Total_Test_Result = True;	
		for( i = 0;  TMD27024_ALS[i].Name ; i ++){
			(*TestStepN) ++;
			cyc4or3run();
			lcd_printf ("<%d> %s",*TestStepN,TMD27024_ALS[i].Name);
			if( i == 0){
				TMD27024_ALS[i].Status= TMD27024_ID_Test(i); 
			}					 
			else{		
				TMD27024_ALS[i].Status= TMD27024_ALS_Test(i); 
				Valve_Drive (MOVE1|MOVE4|MOVE5,RESET);
				if(strstr(TMD27024_ALS[i].Name,"IR")){
					Valve_Drive (LED_Block ,RESET); delay_ms (300);
				}
			}
			if(testmode == Auto_Test_Mode && TMD27024_ALS[i].Status == False){
					Total_Test_Result |= False ;	
					break ;
			}
			if(testmode == Step_Test_Mode && TMD27024_ALS[i].Status == False){
				cyc4or3run ();
				lcd_printf ("L:复测  R:下一步");
				lcdcon -- ;
				Clear_buffer(3);
			if (step_test_mode_get_key () == Left_Button_Pressed_Down ){
				i --;
				continue ;
			}
			Total_Test_Result |= False ;	
			}		 
		}
		
		return Total_Test_Result ; 
}


