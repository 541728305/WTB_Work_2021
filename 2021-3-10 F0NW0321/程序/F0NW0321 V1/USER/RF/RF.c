#include "rf.h"
#include "wtb.h"
#include "subus.h"
#include "other.h"
#include "delay.h"
#include "lcd3033.h"
#include "usart.h"
#include "delay.h"
#include <string.h>
#include <stdlib.h>
#include "subus.h"
#include "base_Config.h"
#include "analog_switch.h"
#include "sup_fun.h"
#include "test.h"
#include "global.h"
static  uint8_t Sbuds_Relay_Status[4] = {RESET ,RESET,RESET,RESET};

uint8_t RF_Total_Result[4] = {True,True,True,True };

/*********************************************************************************************
	* File Name     : ChangeRFICStatus
	* Description   : ChangeRFICStatus
  * Input         : IC_Num Status
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 12-April-2020
*********************************************************************************************/
void SbudsCondition(uint8_t IC_Num, uint8_t Status)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14; //RESET
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOF,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOF,GPIO_Pin_13);
	
	if(Status == SET ){
		GPIO_SetBits(GPIOF,GPIO_Pin_14);
		uart3_init(115200);	
		switch(IC_Num){
			case 1 : Valve_Drive (MOVE2|MOVE3|MOVE4,RESET ); 
							 Valve_Drive (MOVE1,SET ); 
							 Sbuds_Relay_Status[0] = SET ;	
							 Sbuds_Relay_Status[1] = RESET ;
							 Sbuds_Relay_Status[2] = RESET ;
							 Sbuds_Relay_Status[3] = RESET ;			
							 break ;
			
			case 2 : Valve_Drive (MOVE1|MOVE3|MOVE4,RESET ); 
							 Valve_Drive (MOVE2,SET ); 
							 Sbuds_Relay_Status[0] = RESET ;	
							 Sbuds_Relay_Status[1] = SET ;
							 Sbuds_Relay_Status[2] = RESET ;
							 Sbuds_Relay_Status[3] = RESET ;				
			         break ;
			
			case 3 : Valve_Drive (MOVE1|MOVE2|MOVE4,RESET ); 
							 Valve_Drive (MOVE3,SET );  
							 Sbuds_Relay_Status[0] = RESET ;	
							 Sbuds_Relay_Status[1] = RESET ;
							 Sbuds_Relay_Status[2] = SET ;
							 Sbuds_Relay_Status[3] = RESET ;			
								break ;
			
			case 4 : Valve_Drive (MOVE1|MOVE2|MOVE3,RESET ); 
							 Valve_Drive (MOVE4,SET );   
							 Sbuds_Relay_Status[0] = RESET ;	
							 Sbuds_Relay_Status[1] = RESET ;
							 Sbuds_Relay_Status[2] = RESET ;
							 Sbuds_Relay_Status[3] = SET ;
							 break ;			
		}				
	}else{
		GPIO_ResetBits(GPIOF,GPIO_Pin_14);
		Valve_Drive (MOVE1|MOVE2|MOVE3|MOVE4,RESET ); 
	}
	delay_ms (80);
}

/********************************************
	* File Name     : ChangeRFICStatus
	* Description   : ChangeRFICStatus
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 12-April-2020
********************************************/
uint8_t  ChangeRFICStatus( char *Cmd){
	uint8_t i = 0,IC_Status = True,Num = 0  ;
	for( i = 0; Cmd[i] ; i ++){
		if(Cmd[i]== 0x0A || Cmd[i] == 0xD)
			Cmd[i] = 0;
	}
	Num = atof(&Cmd[5+2]);
	if(SetRFSwitchStatus( Num,6)==True ){
		Uart_printf(USART1, "%s OK\r\n",Cmd);	
	}else{
		Uart_printf(USART1, "%s NG\r\n",Cmd);
		IC_Status = False ;
	}
	cyc4or3run();
	
	lcd_printf("%c#State%d       ",Cmd[0],Num);
	lcdpos (lcdcon -1,12);
	lcd_printf ("%s",((IC_Status== True)?"OK":"NG"));
	return IC_Status;
}


void   Get_RF_Total_Result( char *rev){
	uint8_t i = 0, RF_Cmd = True;
	for( i = 0; rev[i] ; i ++){
		if(rev[i]== 0x0A || rev[i] == 0x0D)
			rev[i] = 0;
	}
	if(strstr(rev,"1#PASS" ) && strstr(rev,"1#FAIL" ) == 0 )
		RF_Total_Result[0] |= True ;
	else if(strstr(rev,"1#FAIL")&&strstr(rev,"1#PASS" )==0)
			RF_Total_Result[0] |= False ;
	else{
		 RF_Total_Result[0] |= False ;
		 RF_Cmd |= False ;
	}
	if(strstr(rev,"2#PASS" ) && strstr(rev,"2#FAIL" ) == 0)
		RF_Total_Result[1] = True ;
	else if(strstr(rev,"2#FAIL" )&& strstr(rev,"2#PASS" ) == 0 )
			RF_Total_Result[1] |= False ;
	else{
		 RF_Total_Result[1] |= False ;	
		 RF_Cmd |= False ;
	}
	
	if(strstr(rev,"3#PASS" ) && strstr(rev,"3#FAIL" ) ==0)
		RF_Total_Result[2] |= True ;
	else if(strstr(rev,"3#FAIL" )&&strstr(rev,"3#PASS" ) ==0 )
			RF_Total_Result[2] |= False ;
	else{
		 RF_Total_Result[2] |= False ;
		 RF_Cmd |= False ;
	}

	if(strstr(rev,"4#PASS" )&&strstr(rev,"4#FAIL" )==0)
		RF_Total_Result[3] |= True ;
	else if(strstr(rev,"4#FAIL" )&&strstr(rev,"4#PASS" ) ==0)
			RF_Total_Result[3] |= False ;
	else{
		 RF_Total_Result[3] |= False ;
		 RF_Cmd |= False ;		
	}
	Uart_printf(USART1,"%s %s\r\n",rev,(RF_Cmd==True)?"OK":"NG");		
}
/*********************************************************************************************
	* File Name     : FCT_Step_debug
	* Description   : FCT_Step_debug
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 20-April-2020
*********************************************************************************************/
uint8_t RF_Step_debug( void){
	uint8_t FCT_Result = True ;
	u8  i = 0,j = 0,Reg_Value = 0xFF,CurrentStatus= True;
	for( i = 0 ; i < Fixture.PCS_Num ; i ++){
		SbudsCondition(1+i,SET);
		for( j = 0x1D ; j<=0x1F;j ++ ){	
			
			CurrentStatus = ReadRegValue(j,&Reg_Value);
			cyc4or3run ();
			if(CurrentStatus == True )
				lcd_printf ("%d#REG%02X=0x%02X OK",i+1,j,Reg_Value);
			else
				lcd_printf ("%d#REG%02X=0x%02X NG",i+1,j,0xFF);
			
			while(left_start_key == 1 && right_start_key == 1){
				CurrentStatus = ReadRegValue(j,&Reg_Value);
				lcdpos(lcdcon-1,0);
				if(CurrentStatus  == True )
					lcd_printf ("%d#REG%02X=0x%02X OK",i+1,j,Reg_Value);
				else
					lcd_printf ("%d#REG%02X=0x%02X NG",i+1,j,0xFF);	
			}
			startkeywait (1,1);
			RF_Total_Result[i] |= CurrentStatus;
		}	
		for( j = 0; j < 4 ; j++){
			cyc4or3run();
			CurrentStatus = SetRFSwitchStatus(j ,5);
			if(CurrentStatus == True ){
				lcd_printf("%d#State%d OK",i+1,j);
			}else{
				lcd_printf("%d#State%d NG",i+1,j);
			}
			while(left_start_key == 1 && right_start_key == 1){
				CurrentStatus = SetRFSwitchStatus(j ,5);
				lcdpos(lcdcon-1,0);
				if(CurrentStatus == True ){
					lcd_printf("%d#State%d OK",i+1,j);
				}else{
					lcd_printf("%d#State%d NG",i+1,j);
				}
			}
			startkeywait (1,1);
			RF_Total_Result[i] |= CurrentStatus;
		}		
	}
	SbudsCondition(1,RESET);
	FCT_Result = RF_Total_Result[0]|RF_Total_Result[1]|RF_Total_Result[2]|RF_Total_Result[3];
	
	return FCT_Result;
}



/*********************************************************************************************
	* File Name     : FCT_Step_debug
	* Description   : FCT_Step_debug
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 20-April-2020
*********************************************************************************************/
uint8_t RF_Auto_Test( void){

	uint16_t TIME = 0;
	char rev[64];
	u8 RF_Test_Result = True;
	TIME = 0; 
	memset(Sbuds_Relay_Status, 0,4);
	memset(RF_Total_Result,True ,4);
	SbudsCondition(1,SET);
	while(TIME < Fixture.Cmd_Delay ){
		TIME ++;
		delay_ms(1);
		if(Read_USART_buffer(USART1,rev) > 0){
			 if(strstr(rev,"FAIL")||strstr(rev,"PASS")){		 
				 Get_RF_Total_Result(rev);
				 break;
			}else if( strstr(rev,"State")){
				 if(strstr(rev,"1#State")){
						if(Sbuds_Relay_Status[0] != SET )
							SbudsCondition(1,SET );
						RF_Total_Result[0] |= ChangeRFICStatus(rev);
				 }
				 if(strstr(rev,"2#State")){
						if(Sbuds_Relay_Status[1] != SET )
							SbudsCondition(2,SET );
						RF_Total_Result[1] |= ChangeRFICStatus(rev);
				 }
				 if(strstr(rev,"3#State")){
						if(Sbuds_Relay_Status[2] != SET )
							SbudsCondition(3,SET );
						RF_Total_Result[2] |= ChangeRFICStatus(rev);
				 }
				 if(strstr(rev,"4#State")){
						if(Sbuds_Relay_Status[3] != SET )
							SbudsCondition(4,SET );
						RF_Total_Result[3] |= ChangeRFICStatus(rev);
				 }						 
			}
			RESET_UART(USART1);
			TIME = 0;
		}
		if((TIME%1000)==0){
			lcdpos(lcdcon -1,14);
			lcd_printf("%2d",TIME/1000);
		}
	}
	if(TIME >= Fixture.Cmd_Delay){
		RF_Test_Result |= False;
		cyc4or3run();
		lcd_printf("RF²âÊÔ³¬Ê±");
		RF_Total_Result[0] |= False ;
		RF_Total_Result[1] |= False ;
		RF_Total_Result[2] |= False ;
		RF_Total_Result[3] |= False ;
	}	
	SbudsCondition(4,RESET );	
	RF_Test_Result = RF_Total_Result[0]|RF_Total_Result[1]|RF_Total_Result[2]|RF_Total_Result[3];
	return RF_Test_Result;
}
/*********************************************************************************************
	* File Name     : Type_RF_Test_Fun
	* Description   : Type_RF_Test_Fun
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 12-April-2020
*********************************************************************************************/
u8  Type_RF_Test_Fun(u16 *TestStepN , uint16_t Total_Num){
		uint8_t RF_Test_Result = True;
		if(Total_Num == 0)
			return True;
		Close_All_Point ();
	 (*TestStepN) ++;
		cyc4or3run ();
		lcd_printf ("%d>%s",*TestStepN,"U0201 Test...   ");		
		if(Fixture.Mode  == Step_Test_Mode)	{
			RF_Test_Result |= RF_Step_debug();
		} 								 
		else{	
			RF_Test_Result |= RF_Auto_Test();
		}
		return RF_Test_Result ; 
}

uint8_t  Debug_RF_IC(void){
	lcdreset ();
	lcd_printf ("U0201 debug ...");
	SbudsCondition(3,SET );	
	
	
	SbudsCondition(3,RESET );	
	RevertStartupScreen();
	return 0;
}

