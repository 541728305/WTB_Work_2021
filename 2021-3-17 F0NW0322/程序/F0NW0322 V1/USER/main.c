#include "test.h"
#include "24cxx.h"
#include "other.h"
#include "global.h"
#include "usart.h"
#include "sys.h"
#include "zdt.h"
#include "lcd3033.h"
#include "Sup_Fun.h"
#include "delay.h"
#include "barcode.h"
#include "menu.h"
#include "X_axis.h"
#include "Y_axis.h"
#include "hold_data.h"
#include "wtb.h"
#include "analog_switch.h"
#include "test_config.h"
#include "base_Config.h"
#include "data.h"
#include "reg.h"
#include "dot.h"
#include "block_check.h"
#include "usb_move.h"
//#define  Debug_Mode





/*********************************************************************************************
  * File Name     : Check_Test_Condition
	* Description   : Check_Test_Condition
  * Input         : mode
  * return        : Result
  * Version       : V1.0
	* Author        : Morton
	* Date          : 2020/4/5
*********************************************************************************************/
void InitUartBps(){
	if(Fixture .Comm_Uart == USART1 ){
		if(Fixture.Software == ZDT_Software )
				uart1_init(19200);	
		else if( Fixture.Software == WTB_Software )
				uart1_init(115200);	
		else if( Fixture.Software == JDT_Software )
				uart1_init(38400);	
	}else if( Fixture.Comm_Uart == USART2 ){
		if(Fixture.Software == ZDT_Software )
				uart2_init(19200);	
		else if( Fixture.Software == WTB_Software )
				uart2_init(115200);	
		else if( Fixture.Software == JDT_Software )
				uart2_init(38400);	
	}else if( Fixture .Comm_Uart == USART3 ){
		if(Fixture.Software == ZDT_Software )
				uart3_init(19200);	
		else if( Fixture.Software == WTB_Software )
				uart3_init(115200);	
		else if( Fixture.Software == JDT_Software )
				uart3_init(38400);	
	}else if( Fixture .Comm_Uart == UART4 ){
		
	}
}



/*********************************************************************************************
  * File Name     : Get_Scan_Result
	* Description   : Get_Scan_Result
  * Input         : /
  * return        : Result
  * Version       : V1.0
	* Author        : Morton
	* Date          : 2020/4/5
*********************************************************************************************/
uint8_t Get_Scan_Result(void){
	uint8_t Scan_Result = True ;
	if(Check_Hand_Scan(Fixture.Mode) == False ) // 手动模式检查扫描
			return False ;
	if(Fixture.Software == ZDT_Software )
		Scan_Result |= ZDT_Software_Get_Scan_Result ();
	else if(Fixture.Software == WTB_Software  )
		Scan_Result |= WTB_Software_Get_Scan_Result ();
  else{
		Scan_Result |= False ;
	}
	if(Scan_Result == False){
		if(Fixture.Software == ZDT_Software )
			ZDT_Software_Sotp();
		if(Fixture.Software == WTB_Software  )
			Uart_printf (Fixture.Comm_Uart,"STOP_TEST\r\n");
		Valve_Drive(Yellow_Light,RESET );
 }
	return Scan_Result;
}
/*********************************************************************************************
  * File Name     : Get_Scan_Result
	* Description   : Get_Scan_Result
  * Input         : /
  * return        : Result
  * Version       : V1.0
	* Author        : Morton
	* Date          : 2020/4/5
*********************************************************************************************/
uint8_t Test_Up_Down_Move( uint8_t Status){
	uint8_t Result = True ;
	if(Status == SET){
		lcdreset  ();
		cyc4or3run  ();
		if(Fixture.UpDown  == ACT_Controller ){
			lcd_printf  (">>>>电缸下压");
			Result |= Up_Down_EACT_MOVE( Status);	
		}else if(Fixture.UpDown  == Valve  ){
			lcd_printf  (">>>>气缸下压");
			Valve_Drive (Big_Cylinder_Down,Status);
			Valve_Drive (Fixe_Products,Status);
			Result |= Read_Sensor_Status(Down_sensor)  ;
			if(Result == False)
				Valve_Drive (Big_Cylinder_Down,RESET );
			Valve_Drive (Fixe_Products,RESET );
		}else if(Fixture.UpDown == None ){
			lcd_printf  (">>>>手动下压");
		}			
		if(Result == False){
			if(Fixture.Software == ZDT_Software )
				ZDT_Software_Sotp();
			else if(Fixture.Software == WTB_Software)
				Uart_printf (USART1,"STOP_TEST\r\n");
			Valve_Drive(Yellow_Light,RESET );
		}
	}else {
		if(Fixture.UpDown  == ACT_Controller ){
			Result |= Up_Down_EACT_MOVE( Status);	
		}else if(Fixture.UpDown  == Valve  ){
			while(Safe_Grating_Sensor == 0) delay_ms (100);
			Valve_Drive (Big_Cylinder_Down,Status);
			//Result |= Read_Sensor_Status(Up_Sensor)  ;  
			Valve_Drive (Fixe_Products,Status);
		}	
	}
	return Result;
}
/*********************************************************************************************
  * File Name     : Check_Test_Condition
	* Description   : Check_Test_Condition
  * Input         : mode
  * return        : Result
  * Version       : V1.0
	* Author        : Morton
	* Date          : 2019/12/25
*********************************************************************************************/
uint8_t Check_Test_Condition(uint8_t mode)
{
	Valve_Drive(Red_Light|Yellow_Light|Green_Light,RESET );
	Valve_Drive(Yellow_Light,SET );
	if( Fixture.Mech_Struct == SmallFixture)
	{
			if(Fixture.Mode  < 2 ){
				Valve_Drive (Fixe_Products ,SET);
			}
			if( mode == Auto_Test_Mode && Fixture.Scan_Way == Push_Previous ){
				//Valve_Drive (Pre_Push_Cylinder_Up , SET );
				//delay_ms (200);
				if(Get_Scan_Result()== False){
					Valve_Drive (Fixe_Products|Pre_Push_Cylinder_Up ,RESET);
					return False ;  
				}
				

			}	
			if(Fixture.Mode  < 2 ){
				Valve_Drive (Pre_Push_Cylinder_Up|Pre_Push_Cylinder_DOWN , SET );
				delay_ms (350);
				Valve_Drive (Pre_Push_Cylinder_DOWN , RESET );
			}						
			if(Fixture.Mode  < 2 ){		
				if(Fixture.Take_Product == ENABLE)
					TAKE_OFF_EACT_MOVE(ACT_Standby,DISABLE );
				if(Test_Up_Down_Move(SET) == False)
					return False;
				delay_ms (100);
				Valve_Drive (Fixe_Products ,RESET);
			}
			if( mode == Auto_Test_Mode && Fixture.Scan_Way == Push_Next  ){
				if(Get_Scan_Result()== False){
					Test_Up_Down_Move(RESET);
					return False ;  
				}
			}

			return True;
	}	else {
		if( Fixture.Block_Check == ENABLE )
				return Block_Recognition(Get_TEST_Station());
	}
	return True;
}
//#define Debug_Mode
/*********************************************************************************************
  * File Name     : System_Start
	* Description   : 主循环
  * Input         : 无
  * return        : 无
  * Version       : 
	* Author        : Morton
	* Date          : 2019/6/18
*********************************************************************************************/
void System_Start(){
		unsigned char  Return_Value = 1;
		while(1){
			Valve_Drive (Fixe_Products|Pre_Push_Cylinder_Up|Pre_Push_Cylinder_DOWN  ,RESET);
			Fixture.Status = 0;
			Set_Scan_Result (False);
			Fixture.Mode  = gettestmode();
			
			#if defined Debug_Mode
				Uart_printf (USART1,"Sample Time:%02d:%02d:%02d\r\n",(Fixture.Sample_Time/60/60)%60,
			                                 										   (Fixture.Sample_Time/60)%60   ,		
			                                 											  Fixture.Sample_Time%60);			
				//Uart_printf (USART1,"Dot Counter:%d/%d\r\n",(uint16_t)Reg[Dot_Pen_CNT].Value,( uint16_t )(Reg[Dot_Pen_MAX].Value)   );
			#endif
			
			
			Fixture.Status = 1;
			
			if(Check_Test_Condition(Fixture.Mode )== False)
				continue;
			
			if(Fixture.Mode  < 2){
				Init_Test_data();
				//USB_MOVE(SET);
			}			
			
			Return_Value = _Test_Mode[Fixture.Mode ].fun() ;
			Valve_Drive(Yellow_Light,RESET );
			if( Fixture.Mode  < 2 ){ 
			//	USB_MOVE(RESET);
				Display_Test_Result(Return_Value);
				Display_Total_Rate();
				if(Fixture.Mech_Struct == SmallFixture && Fixture.Mode < 2 ){
					if( Fixture.Dot == ENABLE && Return_Value == True && Reg[Dot_Enable].Value  == ENABLE ){ // &&
						Product_Mark_Dot();
					}
					Test_Up_Down_Move(RESET) ;
					if(Fixture.Take_Product == ENABLE )
						Take_OFF_Products(Return_Value);
				}
			}
			#if defined  Debug_Mode
				Uart_printf (USART1,"Sample Time:%02d:%02d:%02d\r\n",(Fixture.Sample_Time/60/60)%60,
			                                 										   (Fixture.Sample_Time/60)%60   ,		
			                                 											  Fixture.Sample_Time%60);			
				//Uart_printf (USART1,"Dot Counter:%d/%d\r\n",(uint16_t)Reg[Dot_Pen_CNT].Value,( uint16_t )(Reg[Dot_Pen_MAX].Value)   );
			#endif
	}
}


/*********************************************************************************************
  * File Name     :  main
	* Description   : 主循环
  * Input         : 无
  * return        : 无
  * Version       : 
	* Author        : Morton
	* Date          : 2019/6/18
*********************************************************************************************/
int main(void ){

		delay_init();	
		ALL_GPIO_CFG();	
		uart1_init(115200);	
	  uart2_init(USART2_Baud);
		uart3_init(USART3_Baud);
  	uart5_init(115200);	
 	  Uart_printf (USART1 ,"Usart1 Test...\n");	
 	  Uart_printf (USART2 ,"Usart2 Test...\n");
 	  Uart_printf (USART3 ,"Usart3 Test...\n");
	 	Uart_printf (UART5 , "Uart5 Test...\n");

		lcdreset ();
		cyc4or3run ();
		lcd_printf ("初始化...");

		InitTestConfig();
		Init_Test_data();
		Read_Hold_Reg_data();	  
		Read_All_Reg_Value(0);
	  Init_Fixture();
		resetMCU();
	  InitUartBps();
		LED_Light_Check(3,300);
		System_Start();
}
