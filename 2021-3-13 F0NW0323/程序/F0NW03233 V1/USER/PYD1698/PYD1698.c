#include "pyd1698.h"
#include "sys.h"
#include "other.h"
#include "delay.h"
#include "lcd3033.h"
#include "NET_iic.h"
#include "myiic.h"
#include "sup_fun.h"
#include "analog_switch.h"
#include "usart.h"
#include "pyd1698.h"
#include "sys.h"
#include "other.h"
#include "delay.h"
#include "lcd3033.h"
#include "NET_iic.h"
#include "myiic.h"
#include "sup_fun.h"
#include "analog_switch.h"
#include "usart.h"
#include "base_Config.h"
#define  Serial_In   PDout(6)
#define  Direct_Link_IN    PGin(9)
#define  Direct_Link_OUT   PGout(9)
#define  T_SL        1       //200-2000ns
#define  T_SH        1       //200-2000ns
#define  T_SHD       100     // > 72  data in hold
#define  T_SLT       1000    // > 580 data load time
#define  T_DS     		130    //data SETUP time 110-150us
#define  T_DL    			  1    //200-2000ns
#define  T_DH    			  1    //200-2000ns
typedef union{
		 struct{
			  uint32_t Reserved        : 5 ;  // [4:0],Must be written to 16 decimal.
				uint32_t Filter_Source   : 2 ;  // 0 = PIR (BPF),
																				// 1 = PIR (LPF)
			                                  // 2 = reserved 
			                                  // 3 = Temperature Sensor
				uint32_t Operation_Modes : 2 ;  // 0 = Forced Read Out Mode 
																				// 1 = Interrupt Read Out Mode
			                                  // 2 = Wake Up Operation Mode 
																				// 3 = reserved
				uint32_t Window_Time     : 2 ;  // Window time = 4s + [RegisterValue] * 4s
				uint32_t Pulse_Counter   : 2 ;  // Number of pulses = 1 + [RegisterValue]
				uint32_t Blind_Time      : 4 ;  // Blind time = 0.5s + [RegisterValue] * 0.5s
			  uint32_t Sensitivity     : 8 ;  // This value defines the threshold for detection
				uint32_t                 : 7;		 
		}Register;
		uint32_t Configuration_Register;
}Configuration_Register_Typedef;

Configuration_Register_Typedef Send_data;

typedef struct  {
	Configuration_Register_Typedef  Config; //[24:0]
	uint16_t PIR_and_ADC_Voltage; //[38:25] 14bit
																// 0 = Motion Detection Unit disabled
		                            // 1 = Motion Detection Unit enabled
}Data_Transmission_Diagram_Typedef;

Data_Transmission_Diagram_Typedef Receive_data;


void delay_ns(uint32_t ns){
	uint32_t i,CNT = 2; 
	for( i = 0 ; i < ns ; i ++)
		while(CNT)
			CNT --;
	
}

/****************************************************
	* File Name     : Net_IIC_Init
	* Description   : initalize iic gpio,congiratin pull Up or drain output 
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*****************************************************/
void Init_Serial_Bus(void)
{					     
	//PG9 SDA  PD6 SCL
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOD,GPIO_Pin_6); 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOG,GPIO_Pin_9); 	
}



void writeregval(unsigned long regval){
		int i;
		unsigned char nextbit;
		unsigned long regmask = 0x1000000;
		Serial_In = 0;
		for(i=0;i < 25;i++){
			nextbit = (regval&regmask)!=0;
			regmask >>= 1;
			Serial_In = 0;
			Serial_In = 1;
			Serial_In = nextbit;
			delay_us(100);
		}
		Serial_In = 0;
		delay_us(600);
}
int PIRval = 0;               // PIR signal
unsigned long statcfg = 0;   // status and configuration register
void readlowpowerpyro(void) {
		int i;
		unsigned int   uibitmask;
		unsigned long ulbitmask;
	
	// get 25bit status and config
		ulbitmask = 0x1000000; // Set BitPos
		uibitmask = 0x4000;
		statcfg = 0;
		PIRval = 0;
	
		Net_SDA_OUT();
		Direct_Link_OUT = 1; // Set DL = High, to force fast uC controlled DL read out
		delay_us(150);       // get first 15bit out-off-range and ADC value

		for (i=0; i < 15; i++)
		{		
			Net_SDA_OUT();
			Direct_Link_OUT = 0; // Set DL = Low, duration must be > 200 ns (tL)
			delay_ns (2);
														//#asm("nop") // number of nop dependant processor speed (200ns min.)
			Direct_Link_OUT = 1; 	// Set DL = High, duration must be > 200 ns (tH)
			//delay_us(1); 
			Net_SDA_IN();    			//DLA_DIR = PORT_IS_INP; // Configure DL as Input
			delay_us(3); 					// Wait for stable low signal
														// If DL High set masked bit in PIRVal
			if (Direct_Link_IN) 
				PIRval |= uibitmask;
			uibitmask >>= 1;
		}
		for (i=0; i < 25; i++)
		{
			Net_SDA_OUT();        // create low to high transition
			Direct_Link_OUT = 0;  // Set DL = Low, duration must be > 200 ns (tL)
														// Configure DL as Output
			delay_ns (2);         //#asm("nop") // number of nop dependant processor speed (200ns min.)
			Direct_Link_OUT = 1;  // Set DL = High, duration must be > 200 ns (tH)
		//	delay_us(1); 
			Net_SDA_IN();         //DLA_DIR = PORT_IS_INP; // Configure DL as Input
			delay_us(3); 				  // Wait for stable low signal, tbd empirically using scope
													  // If DL High set masked bit
			if (Direct_Link_IN)
				statcfg |= ulbitmask;
			ulbitmask>>=1;
		}
			Net_SDA_OUT();
			Direct_Link_OUT  = 0; // Set DL = Low
			delay_ns (2);      //DLA_DIR = PORT_IS_OUTP; // Configure DL as Output
									        //#asm("nop")
			Net_SDA_IN();  // Configure DL as Input
			PIRval &= 0x3FFF;;
			if(PIRval == 0x3FFF){
				PIRval = 0;
			}
//			PIRval &= 0x3FFF; // clear unused bit
//			if (!(statcfg & 0x60)){
//			// ADC source to PIR band pass
//			// number in 14bit two's complement
//			if(PIRval & 0x2000) 
//				PIRval -= 0x4000;
//			}
//		cyc4or3run ();
//		lcd_printf ("ADC = %d   ",PIRval);
//		cyc4or3run ();
//		lcd_printf ("REG = %08X  ",statcfg);

			return;
}
	
	
#include "dac.h"
#include "test.h"
#include "test_config.h"
#include "string.h"
#include "global.h"





double Read_Temp_Reg(void){
	double Temp = 0.0;
	Send_data.Register.Sensitivity = 00;
	Send_data.Register.Blind_Time = 0x00; 
	Send_data.Register.Pulse_Counter = 0x00;
	Send_data.Register.Window_Time = 0x00;
	Send_data.Register.Operation_Modes = 0x00;
	Send_data.Register.Filter_Source = 0x03;
	Send_data.Register.Reserved = 0x10;
	writeregval(Send_data.Configuration_Register);
	readlowpowerpyro();	
	if(PIRval > 0 )
		Temp =(double) PIRval/750.0 +16.0666666667;
	else
		Temp = 0.0;
	return Temp	;
}
double Read_ADC_Reg(void){

	Send_data.Register.Sensitivity = 00;
	Send_data.Register.Blind_Time = 0x00; 
	Send_data.Register.Pulse_Counter = 0x00;
	Send_data.Register.Window_Time = 0x00;
	Send_data.Register.Operation_Modes = 0x00;
	Send_data.Register.Filter_Source = 0x02;
	Send_data.Register.Reserved = 0x10;
	writeregval(Send_data.Configuration_Register);
	readlowpowerpyro();	
//	if(PIRval & 0x2000){ 
//		PIRval -= 0x4000;
//	}	
	return PIRval;
}

extern Item_TypeDef Item[];
extern  uint16_t Step_Number_buffer[Hardware_typedef_Total][Max_Step_Nummber];
uint8_t IR_Sensor_Test(uint16_t Num){
	uint8_t  i, Test_Result = True,CNT = 0;
	double Value,reg[10];
	Init_Serial_Bus();
	if(Item[Num].IO_CTL){
			Valve_Drive (Item[Num].IO_CTL ,SET);
			delay_ms (Item[Num].Time +1);
	}
	if(Fixture.Mode  == Auto_Test_Mode ){
		for( i= 0 ; i < 100 ;i ++){		
				if(strstr (Item[Num].Name ,"Temp")  ){
						Value  = Read_Temp_Reg();
				}
				else{
						Value  = Read_ADC_Reg();
				}	
				if(Value  > Item[Num].LSL && Value < (Item[Num].USL) ){
						reg[CNT] = Value;
						CNT ++; 
				}
				else{
						Item[Num].Value = Value;
						CNT = 0;
				}
				
				if(CNT >= 10){
						Item[Num].Value  = Average_Fun(reg,10);
						break ;
				}
				delay_us (10);			
		}
		cyc4or3run();
		lcd_printf  ("  %7.1f%s   ",Item[Num].Value,Item[Num].Unit );
	}
	if(Fixture.Mode  == Step_Test_Mode  ){
			for( i = 0; i < 10; i ++){				
				if(strstr (Item[Num].Name ,"Temp")  )
						reg[i]  = Read_Temp_Reg();
				else
						reg[i]  = Read_ADC_Reg();
					delay_us (10);				
			}
			Item[Num].Value  = Average_Fun(reg,10);
			cyc4or3run ();
			lcd_printf  ("  %7.1f%s   ",Item[Num].Value,Item[Num].Unit );
			if(left_start_key == 1 || right_start_key == 1 ){
					while(left_start_key ==1&&right_start_key ==1){ //?˙家Α???ボ?甧
						for( i = 0; i < 10; i ++){				
							if(strstr (Item[Num].Name ,"Temp")  )
									reg[i]  = Read_Temp_Reg();
							else
									reg[i]  = Read_ADC_Reg();
							delay_us (10);				
						}
						Item[Num].Value  = Average_Fun(reg,10);
						lcdpos(lcdcon-1,0);  
						lcd_printf  ("  %7.1f%s   ",Item[Num].Value,Item[Num].Unit );
						delay_ms (50);
					}
					startkeywait(1,1);
			}
	}
	lcdpos(lcdcon-1,14);  
	if(Item[Num].Value > Item[Num].LSL && Item[Num].Value < Item[Num].USL){
		lcd_printf ("OK"); 
	}else{
		lcd_printf ("NG"); 
		Test_Result |= False;
	}
	if(Item[Num].IO_CTL){
			Valve_Drive (Item[Num].IO_CTL ,RESET);
			delay_ms (Item[Num].Time +1);
	}
	return Test_Result;
}
	/*********************************************************************************************
	* File Name     : Read_Toatl_Item_Num
	* Description   : Read_Toatl_Item_Num
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 12-OCT-2019
*********************************************************************************************/
uint8_t Type_IR_Sensor_Test_Fun(u16 *TestStepN,uint16_t Total_Num){
		uint8_t i,j=0,Total_Sensor_Test_Result = True;
		uint16_t Item_Step_Number = 0;
		uint32_t dat[3] = {MOVE7,MOVE8,MOVE9};
		if(Total_Num == 0)
			return True;
		Relay_Drive (K8_Src_COMAB|K15_Src_Choice|K12_10R_Ref|K5_IIC_COMCD,SET );
		DAC_Set_Vol (3300,5,0);
		delay_ms (80);
		for( j = 0 ; j < (Total_Num/2); j ++ ){
				Valve_Drive (dat[j%3],SET ); 
				Item_Step_Number = Step_Number_buffer[Type_FCT_IR_Sensor][j]; 
				Open_Two_Point (COMA, Item[Item_Step_Number].Src_H,  COMB,Item[Item_Step_Number].Src_L );
			  //	Open_Two_Point (COMC, Item[Item_Step_Number].Test_H, COMD,Item[Item_Step_Number].Test_L);
				delay_ms (80);
				for ( i = 0 ; i < 2 ; i ++){
					Item_Step_Number = Step_Number_buffer[Type_FCT_IR_Sensor][j*2+i]; 
					(*TestStepN) ++;
					cyc4or3run();
					lcd_printf ("<%d> %s",*TestStepN,Item[Item_Step_Number].Name);
					Item[Item_Step_Number].Status = IR_Sensor_Test(Item_Step_Number);
					if(Fixture.Mode  == Auto_Test_Mode && Item[Item_Step_Number].Status == False   ){
						Total_Sensor_Test_Result |= Item[Item_Step_Number].Status;
						j = Total_Num +1;
						break ;	
					}
					if(Fixture.Mode  == Step_Test_Mode && Item[Item_Step_Number].Status == False){
							cyc4or3run ();
							lcd_printf ("L:复测  R:下一步");
							lcdcon -- ;
							Clear_buffer(3);
							if (step_test_mode_get_key () == Left_Button_Pressed_Down ){
								i--;
								(*TestStepN) --;
								continue ;
							}
							Total_Sensor_Test_Result |= False ;
					 }	
				}
				Valve_Drive (dat[j%3],RESET );
		}
		Close_All_Point ( );
		Valve_Drive (MOVE7|MOVE8|MOVE9,RESET);
		Relay_Drive (K8_Src_COMAB|K15_Src_Choice|K12_10R_Ref|K5_IIC_COMCD,RESET );
		DAC_Set_Vol(0,5,0);
		delay_ms (80);
		return Total_Sensor_Test_Result;
}



