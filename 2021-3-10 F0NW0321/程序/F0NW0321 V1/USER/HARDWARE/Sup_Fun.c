#include "sup_fun.h"
#include "stm32f10x_exti.h"
#include "global.h"
#include "delay.h"
#include "lcd3033.h"
#include "other.h"
#include "stdio.h"
#include "wtb.h"
#include "zdt.h"
#include "test.h"
#include "sys.h"
#include "reg.h"
#include "rf.h"
#include "base_config.h"
#include "test_config.h"


//volatile uint16_t    Cylinder_data=0x0000;
volatile uint32_t    Relay_data=0x00000000;
const char Sensor_Name[][16] = {
	{""},
	{"L"},
	{"R"},	
	{"Motor Sensor  "},
	{"光栅被遮挡    "},
	
	{"气缸上升超时  "},
	{"气缸下压超时  "},

};
/*********************************************************************************************
	* File Name     : Sensor
	* Description   : Num,传感器编号
  * Input         : OK返回0 反正非0
  * return        : 读取传感器当前状态，有效输出的、返回真返回返回非0
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
uint8_t Read_Sensor_Status(uint8_t Num ){
	uint16_t Timer=0,t=0;
	Timer = 0;
	while(1){
		if(Safe_Grating_Sensor==0 && Num == Down_sensor){
			Valve_Drive (Big_Cylinder_Down ,RESET);
			lcdreset ();
			cyc4or3run (); lcd_printf  ("光栅被遮挡    ");
			return False ;
		}
		delay_ms (1);
		Timer ++;
		switch(Num){
			case  1 :  {if(SENSOR1  == 0)  t++;  else  t=0; }  break ;
			case  2 :  {if(SENSOR2  == 0)  t++;  else  t=0; }  break ;
			case  3 :  {if(SENSOR3  == 0)  t++;  else  t=0; }  break ;
			case  4 :  {if(SENSOR4  == 0)  t++;  else  t=0; }  break ;
			case  5 :  {if(SENSOR5  == 0)  t++;  else  t=0; }  break ;
			case  6 :  {if(SENSOR6  == 0)  t++;  else  t=0; }  break ;
			case  7 :  {if(SENSOR7  == 0)  t++;  else  t=0; }  break ;
			case  8 :  {if(SENSOR8  == 0)  t++;  else  t=0; }  break ;
			case  9 :  {if(SENSOR9  == 0)  t++;  else  t=0; }  break ;
			case 10 :  {if(SENSOR10 == 0)  t++;  else  t=0; }  break ;
			case 11 :  {if(SENSOR11 == 0)  t++;  else  t=0; }  break ;
			default :  {  cyc4or3run (); lcd_printf  ("Sensor NO. Error"); t=20;} break ; 
		}
		if(t>100)
		  break;
	 	if(Timer >5000)
		{
			cyc4or3run ();
			lcd_printf  ("%s",Sensor_Name[Num]);
			return 1;
		}
	}
	return 0;
}
/*********************************************************************************************
	* File Name     : Wait_Sensor_Signal
	* Description   : Wait_Sensor_Signal
  * Input         : Sensor number 
	* return        : Sensor_Status
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
uint8_t  Wait_Sensor_Signal(u8 Sensor){
	uint8_t  time=0;
	uint16_t Counter=0;
	uint8_t SensorStatus=False ;
	while(1){
		delay_ms (5);
		if(Sensor==0)	
				time++;
		else
			Counter++;
		if(time>5)                     //time>25ms
			break ;
		if(Counter >600){              //>3000ms 
			SensorStatus=False  ;
			return SensorStatus ;
		}
	}
	SensorStatus = True  ;
	return SensorStatus;	
}
/*********************************************************************************************
	* File Name     : Drive_Valve
	* Description   : 此函数用于U4 TPIC6B595底层驱动
  * Input         : 讲写入TPIC6B595寄存器数据，该数据用于驱动电磁阀
  * return        : 无
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
static  void Drive_Valve(uint8_t driver_data ){
	u8 i;		
	for(i=0;i<8;i++){
		if(driver_data&0x80)
			Valve_Data =0;
		else
			Valve_Data =1;
		Valve_Sck =1;
		delay_us(60);	//	delay_us(60);		
		Valve_Sck =0;
		delay_us(60);	//	delay_us(60);		
		driver_data<<=1;
	}
}
/*********************************************************************************************
	* File Name     :  Relay_Drive
	* Description   :	 电磁阀驱动上层封装函数，//此函数为电磁阀驱动函数，支持单个和多个一齐驱动
  * Input         :  Num，电磁阀编号， VALVE Driver 1 - 16  Status电磁阀状态 ，SET： 置位电磁阀 RESET：复位电磁阀
  * return        :  无
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
void Relay_Drive(uint32_t  driver_data, u8 Status){
	uint8_t   Cylinder_dat = 0;
	if(driver_data){
		if(Status == SET )
			Relay_data |= driver_data ;
		if(Status == RESET )
			Relay_data &= ~driver_data ;
	}
	else{
		Relay_data = 0;
		Drive_Valve(Relay_data);
		Valve_ST1 = 1;	Valve_ST2 = 1;Valve_ST3 = 1;
		delay_us(100);	
		Valve_ST1 = 0;	Valve_ST2 = 0;Valve_ST3 = 0;
		return ;
	}
	if(driver_data&0xFF){
		Cylinder_dat = (uint8_t)(Relay_data&0xFF); 
		Drive_Valve (Cylinder_dat);
		Valve_ST1 = 1;
		delay_us(100);	
		Valve_ST1 = 0;
	}
	if(driver_data&0xFF00){
		Cylinder_dat = (uint8_t)(Relay_data>>8);
		Drive_Valve (Cylinder_dat);
		Valve_ST2 = 1;
		delay_us(100);	
		Valve_ST2 = 0;
	}	
	if(driver_data&0xFF0000){
		Cylinder_dat = (uint8_t)(Relay_data>>16);
		Drive_Valve (Cylinder_dat);
		Valve_ST3 = 1;
		delay_us(100);	
		Valve_ST3 = 0;
	}	
}

/****************************************************************************************
	* File Name     : Valve_Drive
	* Description   : Valve_Drive
  * Input         : Num Status
  * return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
****************************************************************************************/

void Valve_Drive( uint32_t Num, uint8_t Status){
	uint32_t i = 0,Temp = 0;
	if(Num == 0 && Status == SET){
		OUT_IO_1  = SET ;OUT_IO_2  = SET ;OUT_IO_3  = SET ;OUT_IO_4  = SET ;OUT_IO_5  = SET ;
		OUT_IO_6  = SET ;OUT_IO_7  = SET ;OUT_IO_8  = SET ;OUT_IO_9  = SET ;OUT_IO_10 = SET ;
		OUT_IO_11 = SET ;OUT_IO_12 = SET ;OUT_IO_13 = SET ;OUT_IO_14 = SET ;OUT_IO_15 = SET ;
		OUT_IO_16 = SET ;OUT_IO_17 = SET ;
		return ;
	}
	for( i = 0; i < 17 ; i ++){
		Temp = (Num&(1<<i));
		switch(Temp){
			case 0x00000001:  OUT_IO_1  = (Status==RESET ? 1:0);    break ;
			case 0x00000002:  OUT_IO_2  = (Status==RESET ? 1:0);    break ;
			case 0x00000004:  OUT_IO_3  = (Status==RESET ? 1:0);    break ;
			case 0x00000008:  OUT_IO_4  = (Status==RESET ? 1:0);    break ;						                   
			case 0x00000010:  OUT_IO_5  = (Status==RESET ? 1:0);    break ;
			case 0x00000020:  OUT_IO_6  = (Status==RESET ? 1:0);    break ;
			case 0x00000040:  OUT_IO_7  = (Status==RESET ? 1:0);    break ;
			case 0x00000080:  OUT_IO_8  = (Status==RESET ? 1:0);    break ;			
			case 0x00000100:  OUT_IO_9  = (Status==RESET ? 1:0);    break ;
			case 0x00000200:  OUT_IO_10 = (Status==RESET ? 1:0);    break ;
			case 0x00000400:  OUT_IO_11 = (Status==RESET ? 1:0);    break ;
			case 0x00000800:  OUT_IO_12 = (Status==RESET ? 1:0);    break ;			
			case 0x00001000:  OUT_IO_13 = (Status==RESET ? 1:0);    break ;
			case 0x00002000:  OUT_IO_14 = (Status==RESET ? 1:0);    break ;
			case 0x00004000:  OUT_IO_15 = (Status==RESET ? 1:0);    break ;
			case 0x00008000:  OUT_IO_16 = (Status==RESET ? 1:0);    break ;
			case 0x00010000:  OUT_IO_17 = (Status==RESET ? 1:0);    break ;				
			default : break ;
		}
	}
	return ;
}





#define Debug_MOVE_Num 6

/*********************************************************************************************
	* File Name     : MOVE_debug_Fun
	* Description   : 电磁阀动作调试函数
  * Input         : 无
  * return        : 无
	* Author        : Morton
	* Date          : 2018/10/9
*********************************************************************************************/
void   MOVE_debug_Fun(void ){
	uint8_t  i = 0,Button_Status,MOVE_Status = RESET;
	uint16_t MOVE[Debug_MOVE_Num] = { MOVE4,MOVE6 };
	char    *str[Debug_MOVE_Num]= {	

			                              "上下气缸        ",	
			                              "侧推气缸        ",			
																};
	lcdreset();
	cyc4or3set(4);
	cyc4or3run();
	lcd_printf ("单步模式     ");
	cyc4or3run ();
	lcd_printf  ("L:调试 R:NEXT");
	cyc4or3run ();
	lcd_printf ("%s",str[0]);
	lcdpos (lcdcon -1,12);
	lcd_printf ("%s",MOVE_Status?"置位":"复位");
	for ( i = 0 ; i < Debug_MOVE_Num ;i ++){
			lcdpos(lcdcon-1,0);
			lcd_printf ("%s",str[i]);
			while(1){
					Button_Status = Get_start_key_val();					
					if(Button_Status==Left_Button_Pressed_Down ){
							MOVE_Status = !MOVE_Status;
							Valve_Drive (MOVE[i],MOVE_Status );
							lcdpos (lcdcon-1,12);
							lcd_printf ("%s",MOVE_Status?"置位":"复位");
					}else	if(Button_Status == Right_Button_Pressed_Down){
							MOVE_Status = RESET;
							break ;
					}else if(Button_Status == Double_Button_Pressed_Down ){
							i ++;
							goto _Flag_Finish ;
					}		
					startkeywait(1,1);
			}
	}
	cyc4or3run ();
	lcd_printf ("调试结束        ");
	cyc4or3run  ();
	lcd_printf ("系统复位        ");
	delay_ms (500);
	_Flag_Finish:
	i-- ;
	for ( i = Debug_MOVE_Num; i; i--){
			MOVE_Status = RESET;
			Valve_Drive(MOVE[i-1], MOVE_Status );
			cyc4or3run ();
			lcd_printf ("%s",str[i-1]);
			lcd_printf ("%s",MOVE_Status?"置位":"复位");
			delay_ms (500);
	}
	RevertStartupScreen();
	beep (1,20);
}

/*********************************************************************************************
	* File Name     : beep
	* Description   : beep 蜂鸣器驱动函数
  * Input         : timer，蜂鸣器响次数，time，蜂鸣器频率设置参数： f
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
void beep(u8 timer,u16 time)
{
	u8 i;
	for(i=0;i<timer;i++){
		Relay_Drive (Beep_CTR ,SET );
    delay_ms(time);
		Relay_Drive (Beep_CTR ,RESET );
		delay_ms(time);
	}
}

void RG_Light_Set(  uint8_t Num, uint8_t Red_Status,uint8_t Green_Status){
//		switch(Num){
//			case 1:   if(Red_Status == SET)    {Red_Light_ON();  }  else {Red_Light_OFF()};
//							  if(Green_Status == SET)  {Green_Light_ON();}  else {Green_Light_OFF (); }   
//							  break ;
//			case 2: 	if(Red_Status == SET)    {Valve_Drive (Red2,  SET ); }  else {Valve_Drive (Red2 , RESET );};			
//				        if(Green_Status == SET)  {Valve_Drive (Green2,SET ); }  else {Valve_Drive (Green2,RESET );  }   
//                break ;
//			case 3: 	if(Red_Status == SET)    {Valve_Drive (Red3,  SET ); }  else {Valve_Drive (Red3 , RESET );};			
//				        if(Green_Status == SET)  {Valve_Drive (Green3,SET ); }  else {Valve_Drive (Green3,RESET );  }   
//                break ;
//			case 4: 	if(Red_Status == SET)    {Valve_Drive (Red4,  SET ); }  else {Valve_Drive (Red4 , RESET );};			
//				        if(Green_Status == SET)  {Valve_Drive (Green4,SET ); }  else {Valve_Drive (Green4,RESET );  }   
//                break ;			
//			default : break ;
//			
//		}
}

/*********************************************************************************************
	* File Name     : Display_Test_Result
	* Description   : Display_Test_Result
  * Input         : Result true or false
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
void Display_Test_Result(uint8_t Result){
	uint8_t Station_Result[4] = {True ,True ,True ,True };
	uint16_t j=0, i=0,TestStepN=0xA2D9; 
	Valve_Drive(Yellow_Light ,RESET);	
	if(Result == True ){
		Valve_Drive (Green_Light ,SET);
		if(Fixture.Software == ZDT_Software)	{
				cyc4or3run ();
				lcd_printf("------PASS------");
		}
		else if(Fixture.Software == WTB_Software && Fixture.PCS_Num == 1){
		  	cyc4or3run ();
	 		  lcd_printf ("工位-%d:--PASS---",Get_TEST_Station());	
		}else if(Fixture.Software == WTB_Software && Fixture.PCS_Num > 1){
//				cyc4or3run ();
//				lcd_printf ("工位-%d          ",Get_TEST_Station());	
				for( i = 0 ;i < (Fixture.PCS_Num); i ++){
					RG_Light_Set( i+1,RESET,SET );
					if((i%4) == 0)
						cyc4or3run ();
					lcd_printf ("%c%cOK",(u8)(TestStepN>>8),(u8)(TestStepN&0xff));
					TestStepN ++;
				}

		}else {
			
		}
		if(Fixture.Mode  == Auto_Test_Mode ){
			Reg[PASS_Num].Value  += Fixture.PCS_Num;
		}
	}
	else{
		Valve_Drive (Red_Light,SET);
		for( i = 0; (Item[i].Name != NULL&& Fixture.PCS_Num > 1) ; i ++){
			for( j = 0 ;j < Fixture.PCS_Num; j ++){
					if((Item[i].Group-1) == j)
						Station_Result[j] |= Item_Data[i].Status;
			}
		}
		for( j = 0 ; (j < Fixture.PCS_Num && Fixture.PCS_Num > 1); j ++){
			if((Station_Result[j]|RF_Total_Result[i]) == True && Fixture.Mode  == Auto_Test_Mode )
				Reg[PASS_Num].Value  ++ ; 
		}		
		if(Fixture.Software == ZDT_Software)	{
				cyc4or3run ();
				lcd_printf("------FAIL------");
		}
		else if(Fixture.Software == WTB_Software && Fixture.PCS_Num == 1){
		  	cyc4or3run ();
	 		  lcd_printf ("工位-%d:--FAIL---",Get_TEST_Station());	
		}else if(Fixture.Software == WTB_Software && Fixture.PCS_Num > 1){
//				cyc4or3run ();
//				lcd_printf ("工位-%d          ",Get_TEST_Station());	
				for( i = 0 ;i < (Fixture.PCS_Num); i ++){
					
					RG_Light_Set( i+1,(Station_Result[i]||RF_Total_Result[i]),!(Station_Result[i]||RF_Total_Result[i]));

					if((i%4) == 0)
						cyc4or3run ();
					if(TestConfig.RF == DISABLE )
							lcd_printf ("%c%c%s",(u8)(TestStepN>>8),(u8)(TestStepN&0xff),(Station_Result[i]==True ?"OK":"NG"));
					else
						  lcd_printf ("%c%c%s",(u8)(TestStepN>>8),(u8)(TestStepN&0xff),((Station_Result[i]|RF_Total_Result[i])==True ?"OK":"NG"));
					TestStepN ++;
				}

		}
	}
	Reg[Total_Num].Value   += Fixture.PCS_Num  ;
}
/*********************************************************************************************
	* File Name     : Drive_Baipanji
	* Description   : Drive_Baipanji
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
void Drive_Baipanji(void){
	Valve_Drive (Baipanji,SET );
	delay_ms (100);
	Valve_Drive (Baipanji,RESET );	
}
/*********************************************************************************************
	* File Name     : Display_Test_Result
	* Description   : Display_Test_Result
  * Input         : Result true or false
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/

void LED_Light_Check( uint8_t Num,uint16_t ms){
	uint8_t i = 0;
	for( i = 0 ; i < Num ; i ++){
//		Valve_Drive(Red_Light,SET );         		 			
//		delay_ms (ms+1);
//		Valve_Drive(Red_Light,RESET );     
//		delay_ms (ms+1);
//		Valve_Drive(Yellow_Light,SET );         		 			
//		delay_ms (ms+1);
//		Valve_Drive(Yellow_Light,RESET );     
//		delay_ms (ms+1);
//		Valve_Drive(Green_Light,SET );         		 			
//		delay_ms (ms+1);
//		Valve_Drive(Green_Light,RESET );     
//		delay_ms (ms+1);		
		
		Valve_Drive(Red_Light|Yellow_Light|Green_Light,SET );         		 			
		delay_ms (ms+1);
		Valve_Drive(Red_Light|Yellow_Light|Green_Light,RESET );     
		delay_ms (ms+1);
	}

}
/*********************************************************************************************
	* 函数名：debug_Banpanji
	* 功  能+：单次触发摆盘机
	* 参  数：无
	* 返回值：无
	* 作  者：Morton
	* 日  期：2018/10/9
*********************************************************************************************/
void  Debug_Banpanji(void){
		uint8_t Button_Status;
		lcdreset ();
		lcdpos (0,0);lcd_printf ("摆盘机触发测试  ");
		lcdpos (3,0);lcd_printf ("L:触发    R:退出");
		startkeywait (1,1);
		while(1){

				Button_Status = Get_start_key_val();
				if(Button_Status == Left_Button_Pressed_Down ){
						lcdpos (2,0);lcd_printf("触发摆盘机开始  ");
						Drive_Baipanji();; 
						lcdpos (2,0);lcd_printf("触发摆盘机结束  ");
						delay_ms (100); 
				}else	if(Button_Status == Right_Button_Pressed_Down){
						break ;
				}
				lcdpos (2,0);lcd_printf("                ");
				startkeywait  (1,1);
		}
		startkeywait  (1,1);
		RevertStartupScreen();
		beep (1,20);
}


