#include "laser.h"

#include "lcd3033.h"
#include "test_item.h"
#include "global.h"
#include "delay.h"
#include "usart.h"
#include "ad7176.h"
#include "Sup_Fun.h"
#include "other.h"
#include "analog_switch.h"
#include "dac.h"
#include "NET_iic.h"
#include "usart.h"
#include "myiic.h"
#define Addr  0x29
#define LASERt_Write  0
#define LASERt_Read   1



uint8_t  Read_Reg_demo( uint8_t Device_Addr, uint16_t Reg_Addr,uint8_t Length,uint8_t *Reg_Value){
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


uint8_t Read_ID(u16 *TestStepN){
	uint8_t i,ReadData[10];
//	uint16_t Reg_Addr = 0x010F;
	Close_All_Point ();
	Net_IIC_Init ();
	Valve_Drive (K8_2V8_GND_COMCD, SET); 
	delay_ms (50);
	Valve_Drive (K7_IIC_COMAB|K8_2V8_GND_COMCD, SET); 
	delay_ms (100);
	Open_Two_Point (COMC, 1,COMD,5);
//	Open_Two_Point (COMA, 4,COMB,3);
	delay_ms (1);
	lcdreset ();
	for( i= 0; i < 240; i ++){
		cyc4or3run ();
		lcd_printf ("----%d-----",i);
		Net_IIC_Start();  
		Net_IIC_Send_Byte(i );	 
		if(Net_IIC_Wait_Ack() == 0){
			cyc4or3run ();
			lcd_printf ("ID=0x%02X",(i));		
			step_test_mode_get_key ();
		}
		Net_IIC_Stop();  
		delay_ms (1);
	}
	for( i= 0; i < 255; i ++){
		if(Read_Reg_demo(0x29,0x010F,2,ReadData)==0){
				cyc4or3run ();
				lcd_printf ("ID=0x%04X",(ReadData[0]<<8) +ReadData[1]);			
		}
	}
	step_test_mode_get_key ();
	Valve_Drive (K7_IIC_COMAB|K8_2V8_GND_COMCD, RESET); 
	Close_All_Point ();
	return 1;
}


