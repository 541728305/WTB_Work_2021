#include "lcd3033.h"
#include "myiic.h"
#include "net_iic.h"
#include "global.h"
#include "delay.h"
#include "Sup_Fun.h"
#include "other.h"
#include "sensor.h"
#include "test.h"
#include "STK3338_ALS.h"
#include "string.h"
/**************

STK3338 大端存储方式

*****************/

extern  ALS_Sensor_TypeDef STK3338_ALS[];


/*********************************************************************************************
	* File Name     : Sensor_Configuration
	* Description   : Configuration all resister 
  * Input         : /
	* return        : ack.nack
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
uint8_t  STK3338_Configuration( void ){
		uint16_t  Clear_Channel_Low_Threshold,Clear_Channel_High_Threshold;
		uint16_t  PS_Low_Threshold,PS_High_Threshold;
		Net_IIC_Init();
		// reset the chip 
		if(Write_OneByteToDevice(AlS_Slave_Addr ,0x80,0xFF))		  return False ;	
		//Bit0: Enable the PS function. 
	  //Bit1: Enable the ALS/C function.. 
	  //Bit2: Enable the Wait state. 
		//Bit3: Enable the intelligent persistence function.
		if(Write_OneByteToDevice(AlS_Slave_Addr ,0x00,0x03))		  return False ;	
		if(Write_OneByteToDevice(AlS_Slave_Addr, 0x01,0x30))		  return False ;
		if(Write_OneByteToDevice(AlS_Slave_Addr, 0x02,0x32))		  return False ;
		if(Write_OneByteToDevice(AlS_Slave_Addr, 0x03,0x40))		  return False ;
		//interrupt mode and enable SET  disable interrupt function 
		if(Write_OneByteToDevice(AlS_Slave_Addr, 0x04,0x00))		  return False ;
		//ALS/PS Wait (+1)*1.54ms
		if(Write_OneByteToDevice(AlS_Slave_Addr, 0x05,0x00))		  return False ;
	
		//[15:8]
		//[7:0]		
		PS_High_Threshold = 850;
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x06,(uint8_t)(PS_High_Threshold>>8)))		    return False ;	
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x07,(uint8_t)(PS_High_Threshold&0xFF)))	    return False ;
	
		PS_Low_Threshold = 750;//LOW threshold Clear Channel 中断上限设置	
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x08,(uint8_t)(PS_Low_Threshold>>8)))		    return False ;
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x09,(uint8_t)(PS_Low_Threshold&0xFF)))	    return False ;
		//[15:8]
		//[7:0]		
		Clear_Channel_High_Threshold = 850;//HIGH ALS threshold. 中断上限设置	
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x0A,(uint8_t)(Clear_Channel_High_Threshold>>8)))		  return False ;
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x0B,(uint8_t)(Clear_Channel_High_Threshold&0xFF)))	    return False ;

		Clear_Channel_Low_Threshold = 750; // ALS threshold Clear Channel 中断下限设置	38.87-48.59-58.32 Gain = 16  621.82 777.44 933.12
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x0C,(uint8_t)(Clear_Channel_Low_Threshold>>8)))		    return False ;
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x0D,(uint8_t)(Clear_Channel_Low_Threshold&0xFF)))		  return False ;

		//if(Write_OneByteToDevice(AlS_Slave_Addr,0x0D,(uint8_t)(Clear_Channel_Low_Threshold&0xFF)))		  return False ;
			
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x4E,0x00))		return False ; 
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x4F,0x00))		return False ; 
		
		if(Write_OneByteToDevice(AlS_Slave_Addr,0xA5,0x00))		return False ; 		
		

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
uint8_t STK3338_ALS_Test( uint8_t Num){
		uint8_t Light_Sensor_Result = True,ch[20],i,CNT = 0;		
		if(STK3338_ALS[Num].Condition){// Set Ambient_Light_Sensor test condition 
				Valve_Drive (MOVE1|MOVE4|MOVE5,RESET);
				Valve_Drive(STK3338_ALS[Num].Condition,SET );
		}
		if(STK3338_Configuration()== False){
				delay_ms (10); 
				if(STK3338_Configuration()== False){
						cyc4or3run ();
						lcd_printf ("U201配置NG      ");
						Light_Sensor_Result |= False;
						if(testmode == Auto_Test_Mode ){
							return Light_Sensor_Result;
						}
				}
		}
		if( Light_Sensor_Result == True){
			delay_ms(STK3338_ALS[Num].Time );
			CNT = 0;
			for ( i = 0; i < 200; i ++){
					delay_us (50);
					if(Read_NByteFromDevice (AlS_Slave_Addr ,STK3338_ALS[Num].Addr ,ch,STK3338_ALS[Num].Num )==0){
							STK3338_ALS[Num].Value = (ch[1]|(ch[0]<<8));
					}else{
							Light_Sensor_Result |= False;
							if(testmode == Auto_Test_Mode)
									return Light_Sensor_Result;		
					}
					if(STK3338_ALS[Num].Value >= STK3338_ALS[Num].LSL  && STK3338_ALS[Num].Value <= STK3338_ALS[Num].USL){
							CNT ++;
					}else{
							CNT = 0;
					}
					if(CNT == 8)
							break ;
			}	
			cyc4or3run ();
			lcd_printf ( "    %8d    ",STK3338_ALS[Num].Value);	
		}			
		if(testmode == Step_Test_Mode ){
				if(left_start_key == 1 || right_start_key == 1){
					while(left_start_key == 1&&right_start_key == 1){
							if(STK3338_Configuration()== False){
									lcdpos(lcdcon-1,0);
									lcd_printf ("U201配置NG      ");
							}else{
									if(Read_NByteFromDevice (AlS_Slave_Addr ,STK3338_ALS[Num].Addr ,ch,STK3338_ALS[Num].Num )==0){
											STK3338_ALS[Num].Value = (ch[1]|(ch[0]<<8));
											lcdpos(lcdcon-1,0);
											lcd_printf ( "    %8d    ",STK3338_ALS[Num].Value);		
									}
							}
							delay_ms (50);
					}
					startkeywait (1,1);
				}
		}
		lcdpos(lcdcon -1,14);
		if(STK3338_ALS[Num].Value >= STK3338_ALS[Num].LSL  && STK3338_ALS[Num].Value <= STK3338_ALS[Num].USL){
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
static  uint8_t  STK3338_ID_Test(uint8_t Num){
		uint8_t ch[10],CNT = 0,i,ID = 0xFF,Test_Resut = True;
		Net_IIC_Init();
		delay_ms (10);
		for ( i = 0; i < 100; i ++){
				Write_OneByteToDevice(AlS_Slave_Addr,0xA0,0x00); //0x01进入Sleep State
				if(Read_OneByteFromDevice(AlS_Slave_Addr, STK3338_ALS[Num].Addr ,ch)== True){
						ID = ch[0];
						CNT ++;
				}else{
						CNT = 0;
				}
				if(CNT == 10){
					 STK3338_ALS[Num].Value = ID; 
					 break ;
				}
				delay_us (100);
		}
		cyc4or3run ();
		lcd_printf ( "      0X%02X      ",STK3338_ALS[Num].Value);		
		if(testmode == Step_Test_Mode){
				while(left_start_key ==1&&right_start_key ==1){
						if(Read_OneByteFromDevice(AlS_Slave_Addr,STK3338_ALS[Num].Addr,ch)== True){
								STK3338_ALS[Num].Value = ch[0];
						}else{
								STK3338_ALS[Num].Value = 0xFF;
						}
						lcdpos (lcdcon -1 ,0);
						lcd_printf ( "      0X%02X      ",STK3338_ALS[Num].Value);	
						delay_ms (150);
				}
				startkeywait (1,1);
		}
		lcdpos (lcdcon-1, 14);
		if(STK3338_ALS[Num].Value  == STK3338_ALS[Num].USL ){
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
u8 STK3338_ALS_Test_Fun(u16 *TestStepN){
		u8 i = 0,Total_Test_Result = True;	
		for( i = 0;  STK3338_ALS[i].Name ; i ++){
			(*TestStepN) ++;
			cyc4or3run();
			lcd_printf ("<%d> %s",*TestStepN,STK3338_ALS[i].Name);
			if( i == 0){
				STK3338_ALS[i].Status= STK3338_ID_Test(i); 
			}					 
			else{
				STK3338_ALS[i].Status= STK3338_ALS_Test(i); 
				Valve_Drive (MOVE1|MOVE4|MOVE5,RESET);
				if(strstr(STK3338_ALS[i].Name,"IR")){
						Valve_Drive (LED_Block ,RESET); delay_ms (300);
				}
			}
			if(testmode == Auto_Test_Mode && STK3338_ALS[i].Status == False){
					Total_Test_Result |= False ;	
					break ;
			}
			if(testmode == Step_Test_Mode && STK3338_ALS[i].Status == False){
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
		Valve_Drive (MOVE1|MOVE4|MOVE5,RESET);
		return Total_Test_Result ; 
}






