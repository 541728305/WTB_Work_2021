#include "other.h"
#include "image.h"
#include "global.h"
#include "lcd3033.h"
#include "Sup_Fun.h"
#include "ad7176.h"
#include "lec_set.h"
#include "barcode.h"
#include "os.h"
#include "24cxx.h"
#include "delay.h"
#include "analog_switch.h"
#include "DAC.h"
#include "menu.h"
#include "zdt.h"
#include "short.h"
#include "X_axis.h"
#include "Y_axis.h"
#include "hold_data.h"
#include "wtb.h"
#include "eth_config.h"
#include "test_config.h"
#include "base_Config.h"
#include "reg.h"
#include "sample.h"
#include "dot.h"
#include "motor.h"
#include "usb_move.h"
extern  mode_fun_def _Test_Mode[];

/*****************************************************************************************************************
	* File Name     :  Average_Fun
	* Description   :  掐头去尾之后取平均值
  * Input         :  dat ,Num
  * return        :  平均值
	* Author        :  2018.7.15
	* Date          :  Morton
*****************************************************************************************************************/
double  Average_Fun(double *dat  , uint8_t  Num){
		uint8_t  i,j;
		double  Vol=0, temp=0.0;
		for ( i = 0 ; i < (Num-1) ; i++){
			 for ( j = i + 1 ; j < Num ; j++) {
					if (dat[j] < dat[i])
					{
						temp = dat[i] ;
						dat[i] = dat[j] ;
						dat[j] = temp ;
					}
			 }
		}
		for( i = 2 ; i < Num - 2; i ++){
				Vol += dat[i];
		}
    Vol = Vol/(Num - 4) ;
		return Vol;
}

/*****************************************************************************************************************
	* File Name     :  resetMCU
	* Description   :  复位MCU，初始化硬件，还原默认设置
  * Input         :  无 
  * return        :  无
	* Author        :  Morton
	* Date          :  24-June-2019
*****************************************************************************************************************/
void  resetMCU(void) {
		Relay_Drive (0,SET );
		Valve_Drive (0,SET );
		Close_All_Point ();			
		Initialize_AD7176();
		Self_Test_DAC_line(2000);
		Self_Check_Ananlog_Switch();
		if(Fixture.Comm_Mode == __ETH )
			InitaServerPar();
	  if (Fixture.Mech_Struct == SmallFixture ){
					Read_Scan_Configration();
			if( Fixture.UpDown == ACT_Controller  ){
					Init_Up_Down_EACT();
					Up_Down_EACT_MOVE(RESET );
			}
			else if (Fixture .UpDown == Valve )
				 	while(Read_Sensor_Status(Up_Sensor));
			
			if(Fixture.Take_Product == ENABLE ){
				 Init_Take_OFF_EACT(); 
				 TAKE_OFF_EACT_MOVE(ACT_Standby,ENABLE  );
			}
			if(Fixture.Dot_Type == __byMotor ){
				Initialize_Motor();
			}
			if(Fixture.USB_Move == ENABLE )
					Init_USB_Move_Motor();			
		}
		RevertStartupScreen();
}
//	beep(1,1000);}
/*****************************************************************************************************************
	* File Name     :  getFixture.Mode 
	* Description   :  选取MCU当前模式，默认模式0，长按3S进入模式选择，小于3S进入自动测试模式
  * Input         :  无
  * return        :  当前模式值
	* Author        :  Morton
	* Date          :  24-June-2019
*****************************************************************************************************************/
uint8_t gettestmode (void){
		uint8_t  Mode=1,Row=1,Button_Status=0;
	  uint8_t  Test_Mode_Count = 0;
		startkeywait(1,1);
		startkeywait(0,0);
		if(getstarttime(30000)==1) 
				return (0);	
		lcdreset();
		lcdpos(0,0); lcd_printf ("      提示      ");
		lcdpos(1,0); lcd_printf ("松开按键进入模式");
		lcdpos(2,0); lcd_printf ("选择界面...     ");
		imageclear();
		for(Row = 0; _Test_Mode[Row].fun; Row ++ ){
			if(_Test_Mode[Row].En_bit == ENABLE )
					Test_Mode_Count ++;
		}
		Row = 1;
		startkeywait (1,1);  
		lcdreset();
		lcdpos(0,0);
		lcd_printf("【模式选择%02u项】",(u16)(Test_Mode_Count));	
		cyc4or3set (3);
		cyc4or3run ();
		lcd_printf("%2d%s",Mode,  _Test_Mode[1].Name	);
		cyc4or3run();
		lcd_printf("%2d%s",Mode+1, _Test_Mode[2].Name );
		cyc4or3run();
		lcd_printf("%2d%s",Mode+2, _Test_Mode[3].Name );
		Set_Reverse(ENABLE,Row,0,16);
		Test_Mode_Count = 4;		
		while(1){
				Button_Status = Get_start_key_val();
				if( Button_Status == Right_Button_Pressed_Down ) 
						break ;
				if(Button_Status == Left_Button_Pressed_Down ){  						
						do // 调过未使能菜单
						{						
							Mode++;	
							if(_Test_Mode[Mode].Name == NULL){
								Mode = 0;
								Test_Mode_Count  = 0;
								break ;
							}								
						}while(_Test_Mode[Mode].En_bit == DISABLE );
						
						if(Row < 3){
							Row++; 
							Set_Reverse(DISABLE,Row-1,0,16);
							Set_Reverse(ENABLE, Row,  0,16);
						}else{ 					
							cyc4or3run();
							lcd_printf ("%2d%s",Test_Mode_Count,_Test_Mode[Mode].Name);									
							Test_Mode_Count ++;		
						}		
						startkeywait (1,1);  
				}		
		}
		startkeywait (1,1);  
		return Mode ;
}

uint16_t Gas_Keep_Time = 0;
uint8_t  Trigger_Gas   = RESET ;
void Safe_Protect_Trigger_Gas(){
	
		if(Fixture.Sen_Trigger_Gas == DISABLE)
			return ;
	
		if( Trigger_Gas == RESET || Safe_Grating_Sensor == 0 ){
			if(Safe_Grating_Sensor == 0 ){
				Valve_Drive (Fixe_Products ,SET );
				Gas_Keep_Time= 0;Trigger_Gas = SET;
			}
		}
		if(Trigger_Gas == SET){
			Gas_Keep_Time ++;
			if(Gas_Keep_Time > Fixture.Gas_Keep_Time ){
				Valve_Drive (Fixe_Products ,RESET ); 
				Trigger_Gas = RESET;
			}
		}
}


/*****************************************************************************************************************
	* File Name     :  startkeywait
	* Description   :  按键请求状态等待，满足条件后跳出循环，否则一直等待
  * Input         :  L_k,R_k，左右键请求状态  0：被按下，1按键复位
  * return        :  无
	* Author        :  Morton
	* Date          :  24-June-2019
*****************************************************************************************************************/
void startkeywait(uint8_t L_k,uint8_t R_k){
 	uint8_t time1=50;
 	while(1){		

		Dot_Pen_Replace_Check();
		
		Sample_Notice_Check();

		Safe_Protect_Trigger_Gas();

		if(Fixture.Mech_Struct == AutoFixture ){
			if (Get_Soft_Start_Status() == SET)
				return  ;
		}
  	if( ((( left_start_key == 1)&&(L_k==1))||((left_start_key==0)&&( L_k==0))) && ((( right_start_key == 1)&&(R_k==1))||((right_start_key==0)&&( R_k==0)))  )
			time1 --;
		else
			time1=50;
		if(time1 == 0) {
			 beep(1,50);
			return ;
		}
		delay_ms(1);
 	}
}
/*****************************************************************************************************************
	* File Name     :  getstarttime
	* Description   :  获取按键被按下的时间
  * Input         :  无
  * return        :  无
	* Author        :  Morton
	* Date          :  24-June-2019
*****************************************************************************************************************/
uint8_t  getstarttime( uint16_t  time1){
	uint8_t time2=50;
	if(Fixture.Mech_Struct == AutoFixture ){
			if (Get_Soft_Start_Status() == SET)
				return 1  ;
	}
	while(time1) {
		 time1--; //用于记录按键按下时间
  	 if(( left_start_key == 1 ) || ( right_start_key == 1 ))  //左右键均松开
		 	time2--;
		 else
		 	time2=50;
		 delay_us(80);
		 if(time2==0)  break;
	}
	if(time1==0)
		 return (0);
	else
		return (1);
}
/*****************************************************************************************************************
	* File Name     :  step_test_mode_get_key
	* Description   :  单步模式专用按键
  * Input         :  无
  * return        :  无
	* Author        :  Morton
	* Date          :  24-June-2019
*****************************************************************************************************************/
uint8_t  step_test_mode_get_key(){
	uint8_t Key = 0;
//	cyc4or3run();
//	lcd_printf ("继续请按键...   ");
// 	lcdcon--;
	lcdpos(3,14);
	writeir(0x0f);
	Key = Get_start_key_val();
	startkeywait (1,1);
//	startkeywait(0,0);	startkeywait(1,1); 
	writeir(0x0c); 
	return Key;
}
/*****************************************************************************************************************
	* File Name     :  Get_start_key_val
	* Description   :  wait until key pressed down 
  * Input         :  无
  * return        :  按键状态，1：左键按下 2：右键按下 3：双键被按下
	* Author        :  Morton
	* Date          :  24-June-2019
*****************************************************************************************************************/
uint8_t Get_start_key_val(){
	uint8_t time;
	while(1){	 
	 	while((left_start_key==1)&& (right_start_key==1)) 
				delay_ms(3);
		time=10;
		if(( left_start_key==1)&&( right_start_key == 0 )){ //右键被按下
				while(time){
					if((left_start_key==1)&&(right_start_key==0)) 
						time--;
					else   
						break;
					if(time==0)	
						{ beep (1,50);	return(2);}
					delay_ms(8);
				}
		}
		else if((left_start_key==0) && ( right_start_key == 1 )){ //左键被按下
				while(time)
				{
					if((left_start_key==0)&&(right_start_key==1))
						time--;
					else 
						break;
					if(time==0)
						{beep (1,50); return(1);}
					delay_ms(8);
				}
		}
		else if(( left_start_key==0) && ( right_start_key == 0 )) //左右键均被按下
		{
			while(time)
			{
				if((left_start_key==0)&&(right_start_key==0))time--;
				else break;
				if(time==0)
				{
					while((left_start_key==0)||(right_start_key==0));
					beep (1,50);
					return(3);
				}
				delay_ms(8);
			}
		}
	}
}
/*****************************************************************************************************************
	* File Name     :  GetKey_Status
	* Description   :  read two key status
  * Input         :  /
  * return        :  按键状态，1：左键按下 2：右键按下 3：双键被按下
	* Author        :  Morton
	* Date          :  24-June-2019
*****************************************************************************************************************/
uint8_t GetKey_Status (void){
	uint8_t time;
	while(1){	 		
		time=10;
//	 	while((left_start_key==1)&& (right_start_key==1)) 
//				delay_ms(3);
		if(( left_start_key==1)&&( right_start_key == 1 )){ //右键被按下
				while(time){
					if((left_start_key==1)&&(right_start_key==1)) 
						time--;
					else   
						break;
					if(time==0)	
					{ 
						return(0);
					}
					delay_ms(1);
				}
		}
		else if(( left_start_key==1)&&( right_start_key == 0 )){ //右键被按下
				while(time){
					if((left_start_key==1)&&(right_start_key==0)) 
						time--;
					else   
						break;
					if(time==0)	
						{ beep (1,50);	return(2);}
					delay_ms(5);
				}
		}
		else if((left_start_key==0) && ( right_start_key == 1 )){ //左键被按下
				while(time)
				{
					if((left_start_key==0)&&(right_start_key==1))
						time--;
					else 
						break;
					if(time==0)
						{beep (1,50); return(1);}
					delay_ms(5);
				}
		}
		else if(( left_start_key==0) && ( right_start_key == 0 )) //左右键均被按下
		{
			while(time)
			{
				if((left_start_key==0)&&(right_start_key==0))time--;
				else break;
				if(time==0)
				{
			//		while((left_start_key==0)||(right_start_key==0));
					beep (1,50);
					return(3);
				}
				delay_ms(5);
			}
		}
	}
}

/*********************************************************************************************
	* File Name     : Password_Input
	* Description   : 密码输入函数
  * Input         : password 密码 Num 密码长度
  * return        : 输入正确,返回结果
	* Author        : Morton
	* Date          : 2018/11/18
*********************************************************************************************/
uint8_t Getkey_Cursor( char word, uint8_t x,uint8_t y, uint8_t En_bit  ){
	uint8_t time;
	uint16_t CNT = 0;
	lcdpos (x, y);
	lcd_printf("%c",word);
	while(1){	 
	 	while((left_start_key==1)&& (right_start_key==1)){ 
				delay_ms(3); 
				if(En_bit){
					CNT ++;
					if(CNT == 150){
							lcdpos (x, y);
							lcd_printf ("_");

					}else if(CNT >= 300 ){
							lcdpos (x, y);
							lcd_printf ("%c",word);
							CNT = 0;
					}
				}
		}
		lcdpos (x, y);
		lcd_printf ("%c",word);
		time=10;
		if(( left_start_key==1)&&( right_start_key == 0 )){ //右键被按下
				while(time){
					if((left_start_key==1)&&(right_start_key==0)) 
						time--;
					else   
						break;
					if(time==0)	
						{ beep (1,50);	return(2);}
					delay_ms(8);
				}
		}
		else if((left_start_key==0) && ( right_start_key == 1 )){ //左键被按下
				while(time)
				{
					if((left_start_key==0)&&(right_start_key==1))
						time--;
					else 
						break;
					if(time==0)
						{beep (1,50); return(1);}
					delay_ms(8);
				}
		}
		else if(( left_start_key==0) && ( right_start_key == 0 )) //左右键均被按下
		{
			while(time)
			{
				if((left_start_key==0)&&(right_start_key==0))time--;
				else break;
				if(time==0)
				{
					while((left_start_key==0)||(right_start_key==0));
					beep (1,50);
					return(3);
				}
				delay_ms(8);
			}
		}
	}
}


