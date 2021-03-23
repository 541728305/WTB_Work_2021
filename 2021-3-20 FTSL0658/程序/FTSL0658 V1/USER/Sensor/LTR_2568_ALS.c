#include "lcd3033.h"
#include "myiic.h"
#include "net_iic.h"
#include "global.h"
#include "delay.h"
#include "Sup_Fun.h"
#include "other.h"
#include "sensor.h"
#include "test.h"
#include "LTR_2568_ALS.h"
#include <string.h>
/**************

STK3338 大端存储方式

*****************/

extern  ALS_Sensor_TypeDef LTR2568_ALS[];


/*********************************************************************************************
	* File Name     : Sensor_Configuration
	* Description   : Configuration all resister 
  * Input         : /
	* return        : ack.nack
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
uint8_t   LTR2568_Configuration( void ){
	//	uint16_t  Clear_Channel_Low_Threshold,Clear_Channel_High_Threshold;
		uint16_t  PS_Low_Threshold,PS_High_Threshold;
		Net_IIC_Init();
		// reset the chip 
		if(Write_OneByteToDevice(AlS_Slave_Addr ,0x81,0x11))		  return False ;
		delay_ms (10);

		if(Write_OneByteToDevice(AlS_Slave_Addr ,0x7F,0x00))		  return False ;	
		if(Write_OneByteToDevice(AlS_Slave_Addr, 0xA4,0x04))		  return False ;	
		if(Write_OneByteToDevice(AlS_Slave_Addr, 0xB6,0x08))		  return False ;	
		if(Write_OneByteToDevice(AlS_Slave_Addr, 0xB7,0x10))		  return False ;			
		if(Write_OneByteToDevice(AlS_Slave_Addr, 0xAD,0x18))		  return False ;		
	
		//bit0: ALS Active
		//bit1: ALS SAR Enable When ALS_SAR_ENB=0 and under Gain=1, the ALS DATA may not be complete. Firmware needs to read the SAR value and 
		//      reconstruct the actual ALS DATA.
		if(Write_OneByteToDevice(AlS_Slave_Addr ,0x80,0x03))		  return False ;	//Mark
		if(Write_OneByteToDevice(AlS_Slave_Addr, 0x81,0xB2))		  return False ;
		if(Write_OneByteToDevice(AlS_Slave_Addr, 0x82,0x7F))		  return False ;
		if(Write_OneByteToDevice(AlS_Slave_Addr, 0x83,0x1F))		  return False ; //Mark
		if(Write_OneByteToDevice(AlS_Slave_Addr, 0x84,0x00))		  return False ;
		if(Write_OneByteToDevice(AlS_Slave_Addr, 0x85,0xA0))		  return False ;
		// 0x86 PID
		// 0x87 Manufacturer ID
		// 0x88 ALS_STATUS Register 
		/*******bit7----bit6----bit5---bit4-- bit3------bit2-------bit1------bit0------
					          Valid   |-----ALS-Gain-----|    ALS SAR   reserve   data_Status
	  *********/
	// 0x89-0x8A IR_DATA Register
	// 0x8B-0x8C ALS_DATA Register
	// 0x91      PS_Status Register	
	// 0x92-0x93 PS_DATA Register
		if(Write_OneByteToDevice(AlS_Slave_Addr, 0x98,0x80))		  return False ;
		if(Write_OneByteToDevice(AlS_Slave_Addr, 0x99,0x01))		  return False ;	
		

		//[7:0]			
		//[15:8]	
		PS_High_Threshold = 850;		
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x9A,(uint8_t)(PS_High_Threshold&0xFF)))	    return False ;
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x9B,(uint8_t)(PS_High_Threshold>>8)))		    return False ;	

		PS_Low_Threshold = 750;//LOW threshold Clear Channel 中断上限设置	
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x9C,(uint8_t)(PS_Low_Threshold&0xFF)))	    return False ;		
		if(Write_OneByteToDevice(AlS_Slave_Addr,0x9D,(uint8_t)(PS_Low_Threshold>>8)))		    return False ;

			
//		
//		//[7:0]		
//		//[15:8]
//		Clear_Channel_High_Threshold = 850;//HIGH ALS threshold. 中断上限设置	
//		if(Write_OneByteToDevice(AlS_Slave_Addr,0x0A,(uint8_t)(Clear_Channel_High_Threshold>>8)))		  return False ;
//		if(Write_OneByteToDevice(AlS_Slave_Addr,0x0B,(uint8_t)(Clear_Channel_High_Threshold&0xFF)))	    return False ;

//		Clear_Channel_Low_Threshold = 750; // ALS threshold Clear Channel 中断下限设置	38.87-48.59-58.32 Gain = 16  621.82 777.44 933.12
//		if(Write_OneByteToDevice(AlS_Slave_Addr,0x0C,(uint8_t)(Clear_Channel_Low_Threshold>>8)))		    return False ;
//		if(Write_OneByteToDevice(AlS_Slave_Addr,0x0D,(uint8_t)(Clear_Channel_Low_Threshold&0xFF)))		  return False ;

//		//if(Write_OneByteToDevice(AlS_Slave_Addr,0x0D,(uint8_t)(Clear_Channel_Low_Threshold&0xFF)))		  return False ;
//			
//		if(Write_OneByteToDevice(AlS_Slave_Addr,0x4E,0x00))		return False ; 
//		if(Write_OneByteToDevice(AlS_Slave_Addr,0x4F,0x00))		return False ; 
//		
//		if(Write_OneByteToDevice(AlS_Slave_Addr,0xA5,0x00))		return False ; 		
		

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
uint8_t  LTR2568_ALS_Test( uint8_t Num){
		uint8_t Light_Sensor_Result = True,ch[20],i,CNT = 0;		
		if(LTR2568_ALS[Num].Condition){// Set Ambient_Light_Sensor test condition 
				Valve_Drive (MOVE1|MOVE2|MOVE3|MOVE4|MOVE5|MOVE6,RESET);
				Valve_Drive(LTR2568_ALS[Num].Condition,SET );
		}
		if(LTR2568_Configuration()== False){
				delay_ms (10); 
				if(LTR2568_Configuration()== False){
						cyc4or3run ();
						lcd_printf ("U201配置NG      ");
						Light_Sensor_Result |= False;
						if(testmode == Auto_Test_Mode ){
							return Light_Sensor_Result;
						}
				}
		}
		if( Light_Sensor_Result == True){
			delay_ms(LTR2568_ALS[Num].Time );
			CNT = 0;
			for ( i = 0; i < 200; i ++){
					delay_us (50);
					if(Read_NByteFromDevice (AlS_Slave_Addr ,LTR2568_ALS[Num].Addr ,ch,LTR2568_ALS[Num].Num )==0){
							LTR2568_ALS[Num].Value = (ch[0]|(ch[1]<<8));
					}else{
							Light_Sensor_Result |= False;
							if(testmode == Auto_Test_Mode)
									return Light_Sensor_Result;		
					}
					if(LTR2568_ALS[Num].Value >= LTR2568_ALS[Num].LSL  && LTR2568_ALS[Num].Value <= LTR2568_ALS[Num].USL){
							CNT ++;
					}else{
							CNT = 0;
					}
					if(CNT == 8)
							break ;
			}	
			cyc4or3run ();
			lcd_printf ( "    %8d    ",LTR2568_ALS[Num].Value);	
		}			
		if(testmode == Step_Test_Mode ){
				if(left_start_key == 1 || right_start_key == 1){
					while(left_start_key == 1&&right_start_key == 1){
							if(LTR2568_Configuration()== False){
									lcdpos(lcdcon-1,0);
									lcd_printf ("U201配置NG      ");
							}else{
									if(Read_NByteFromDevice (AlS_Slave_Addr ,LTR2568_ALS[Num].Addr ,ch,LTR2568_ALS[Num].Num )==0){
											LTR2568_ALS[Num].Value = (ch[0]|(ch[1]<<8));
											lcdpos(lcdcon-1,0);
											lcd_printf ( "    %8d    ",LTR2568_ALS[Num].Value);		
									}
							}
							delay_ms (50);
					}
					startkeywait (1,1);
				}
		}
		lcdpos(lcdcon -1,14);
		if(LTR2568_ALS[Num].Value >= LTR2568_ALS[Num].LSL  && LTR2568_ALS[Num].Value <= LTR2568_ALS[Num].USL){
				lcd_printf ("OK");
			  Light_Sensor_Result = True ;
		}else{
				Light_Sensor_Result |= False;
				lcd_printf ("NG");
		}
		return Light_Sensor_Result;	
}



uint8_t  Read_Reg( uint8_t Device_Addr, uint16_t Reg_Addr,uint8_t Length,uint8_t *Reg_Value){
	uint8_t i,ACK = 0;
	Net_IIC_Start();  
	Net_IIC_Send_Byte((Device_Addr<<1)|Write);	 
	ACK = Net_IIC_Wait_Ack();
	Net_IIC_Send_Byte(Reg_Addr>>8); 
	ACK = Net_IIC_Wait_Ack();
	Net_IIC_Send_Byte(Reg_Addr&0xFF); 
	ACK = Net_IIC_Wait_Ack();
	Net_IIC_Start();  	 	   
	Net_IIC_Send_Byte((Device_Addr<<1)|Read);        		   
	ACK = Net_IIC_Wait_Ack();	
	if(ACK ==Ack_NG ){
		return 1;
	}
	for( i= 0; i < Length ; i ++){
		if(i != Length -1)
			Reg_Value[i]=Net_IIC_Read_Byte(1);		
		else	
			Reg_Value[i]=Net_IIC_Read_Byte(0);		
	}
	Net_IIC_Stop();  
	return 0;	
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
static  uint8_t   LTR2568_ID_Test(uint8_t Num){
		uint8_t ch[10],CNT = 0,i,ID = 0xFF,Test_Resut = True;
		Net_IIC_Init();
		delay_ms (10);
		for ( i = 0; i < 100; i ++){
				Write_OneByteToDevice(AlS_Slave_Addr,0xA0,0x00); //0x01进入Sleep State
				if(Read_OneByteFromDevice(AlS_Slave_Addr, LTR2568_ALS[Num].Addr ,ch)== True){
						ID = ch[0];
						CNT ++;
				}else{
						CNT = 0;
				}
				if(CNT == 10){
					 LTR2568_ALS[Num].Value = ID; 
					 break ;
				}
				delay_us (100);
		}
		cyc4or3run ();
		lcd_printf ( "      0X%02X      ",LTR2568_ALS[Num].Value);		
		if(testmode == Step_Test_Mode){
				while(left_start_key ==1&&right_start_key ==1){
						if(Read_OneByteFromDevice(i,LTR2568_ALS[Num].Addr,ch)== True){
								LTR2568_ALS[Num].Value = ch[0];
						}else{
								LTR2568_ALS[Num].Value = 0xFF;
						}
						lcdpos (lcdcon -1 ,0);
						lcd_printf ( "      0X%02X      ",LTR2568_ALS[Num].Value);	
					delay_ms (50);
				}
				startkeywait (1,1);
		}
		lcdpos (lcdcon-1, 14);
		if(LTR2568_ALS[Num].Value  == LTR2568_ALS[Num].USL ){
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





//uint8_t Read_ID(u16 *TestStepN){
//	uint8_t i,ReadData[10];
//	uint16_t Reg_Addr = 0x010F;
//	Net_IIC_Init ();
//	Valve_Drive (K8_2V8_GND_COMCD|K7_IIC_COMAB,SET  );
//	Open_Two_Point (COMC, 12,COMD,2);
//	Open_Two_Point (COMA, 8,COMB,1);
//	delay_ms (100);
//	lcdreset ();
////	for( i= 0; i < 240; i ++){
////		ch[0]= 0xAA;
////		Write_NByteDataToDevice(Addr,i,ch,1);
////		ch[0]= 0x55; i ++;
////		Write_NByteDataToDevice(Addr,i,ch,1);
////	}
//	for( i= 0; i < 255; i ++){
//		Read_Reg(Addr,0x010F+i,2,ReadData);
//		cyc4or3run ();
//		//lcd_printf ("Reg:%04X=0x02X",0x010F+i,ReadData[0]);
//		Uart_Printf (USART1,"Reg:%04X=0x%04X\r\n",0x010F+i,(ReadData[0]<<8)+ReadData[1]);
//		
//	}
//	step_test_mode_get_key ();
//	Valve_Drive (K8_2V8_GND_COMCD|K7_IIC_COMAB,RESET  );
//	Close_All_Point ();
//	return 1;
//}




/*********************************************************************************************
	* File Name     : Diode_Test_Fun
	* Description   : Diode_Test  test voltage < 4000mV
  * Input         : *TestStepN
	* return        : Total_Test_Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
u8  LTR2568_ALS_Test_Fun(u16 *TestStepN){
		u8 i = 0,Total_Test_Result = True;	
		for( i = 0;  LTR2568_ALS[i].Name ; i ++){
			(*TestStepN) ++;
			cyc4or3run();
			lcd_printf ("<%d> %s",*TestStepN,LTR2568_ALS[i].Name);
			if( i == 0){
				LTR2568_ALS[i].Status= LTR2568_ID_Test(i); 
			}					 
			else{
				LTR2568_ALS[i].Status= LTR2568_ALS_Test(i); 
				Valve_Drive (MOVE1|MOVE4|MOVE5,RESET);
				if(strstr(LTR2568_ALS[i].Name,"IR")){
						Valve_Drive (LED_Block ,RESET); delay_ms (300);
				}
			}
			if(testmode == Auto_Test_Mode && LTR2568_ALS[i].Status == False){
					Total_Test_Result |= False ;	
					break ;
			}
			if(testmode == Step_Test_Mode && LTR2568_ALS[i].Status == False){
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
