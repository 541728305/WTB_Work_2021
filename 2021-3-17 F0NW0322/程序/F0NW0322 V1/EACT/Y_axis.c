#include "Y_axis.h"
#include "modbus.h"
#include "delay.h"
#include "usart.h"
#include "lcd3033.h"	
#include "sys.h"	
#include "other.h"
#include "global.h"
#include "sup_fun.h"
#include "hold_data.h"
#include "base_Config.h"
#include "menu.h"

extern ACT_Parameter_Def ACT_Parameter[];
Act_typedef Y_Axis = {" Y轴"};
/**************************************************************************
	* File Name     : Init_Up_Down_EACT
	* Description   : 初始化上下运动电缸
  * Input         : 无
  * return        : 读取OK 0 反之非0
	* Author        : Morton
	* Date          : 2019/4/26
**************************************************************************/
void Init_Up_Down_EACT(void){
		uint16_t i = 0;
		
	if(ACT_Parameter[ACT_UP_DOWN_EN].data != ENABLE){
		return ;
	}
	
	
		if(left_start_key == 0 && right_start_key == 0){
			delay_ms (10);
			for( i = 0; i < 100; i ++ ){
				if(left_start_key == 1 || right_start_key == 1)
					break ;
				delay_ms (50);
			}
			if( i>80)
				Up_Down_EACT_set();
		}
	
	
	
	
	
	
	uart2_init(38400);
	Y_Axis.ID = 0x01;
	Y_Axis.Orig_Direction = 1;
	Y_Axis.Stroke = 102;
	Y_Axis.Max_Speed = 500;
	Y_Axis.Run_Speed = 300;
	Y_Axis.Protect_Mode = HOLD  ;	
	Y_Axis.Protect_Range_LSL = 0;
	Y_Axis.Protect_Range_USL = 100;	
	cyc4or3run ();
	lcd_printf("Y 轴通讯测试... ");	
	while( FWriteSingleCoil(Y_Axis.ID,Y30_Serial_EN,ENABLE) != LEC_Normal ) delay_ms (100);
	lcdpos (lcdcon-1,14);
	lcd_printf ("OK"); 
	cyc4or3run ();
	lcd_printf("Y 轴电缸状态... ");	lcdpos (lcdcon-1,14);
	if(Read_InputStatus(Y_Axis.ID,X4F_ALARM) == SET ){
			lcd_printf ("NG");
			FWriteSingleCoil(Y_Axis.ID,Y1B_RESET,SET );
			while(Read_InputStatus(Y_Axis.ID,X4F_ALARM) != SET) delay_ms (100);
			FWriteSingleCoil(Y_Axis.ID,Y1B_RESET,RESET);
	}
	lcd_printf ("OK"); 
	delay_ms (100);
	cyc4or3run ();
	lcd_printf("Y 轴电机上电... ");	lcdpos (lcdcon-1,14);
	FWriteSingleCoil(Y_Axis.ID,Y19_SVON,ENABLE);
	while(Read_InputStatus(Y_Axis.ID,X49_SVRE) != SET );
	lcd_printf ("OK"); 
	delay_ms (100);
	cyc4or3run ();
	lcd_printf("Y 轴电缸回零... ");	lcdpos (lcdcon-1,14);
	FWriteSingleCoil(Y_Axis.ID,Y1C_SETUP,ENABLE);
	while(Read_InputStatus(Y_Axis.ID,X4A_SETON) != SET || Read_InputStatus(Y_Axis.ID,X48_BUSY) != RESET||Read_InputStatus(0x01,X4B_INP ) != SET ){
		if(Safe_Grating_Sensor == SEN_SET ){
				FWriteSingleCoil(Y_Axis.ID,Y18_HOLD,ENABLE);	
				lcdpos(lcdcon-1, 0); lcd_printf("光栅被遮挡...   ");
				while(Safe_Grating_Sensor == SEN_SET ) delay_ms (100);
				delay_ms (300);
				lcdpos(lcdcon-1, 0); lcd_printf("Y 轴电缸回零... ");
				FWriteSingleCoil(Y_Axis.ID,Y18_HOLD,DISABLE);			
		}
	}
	lcdpos (lcdcon-1,14);
	lcd_printf ("OK"); 
	delay_ms (100);
	Y_Axis.Previous_Coordinate = 0.0;
	FWriteSingleCoil(Y_Axis.ID,Y1C_SETUP,DISABLE);
	FWriteSingleCoil(Y_Axis.ID,Y1C_SETUP,DISABLE);		
}


/***************************************************
	* File Name     : Up_Down_EACT_Enable_Set
	* Description   : Up_Down_EACT_Enable_Set
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
***************************************************/
void Up_Down_EACT_Enable_Set(void){
	char str[2][17]={"      关闭      ","      开启      "};
	uint8_t default_Val, Val = ACT_Parameter[ACT_UP_DOWN_EN].data;
  default_Val	 = Val;
	Choice_Menu( (char *)ACT_Parameter[ACT_UP_DOWN_EN].Name ,str,2,&Val);
	ACT_Parameter[ACT_UP_DOWN_EN].data = Val;
	Save_Hold_Reg_data(ACT_UP_DOWN_EN);	
	if(default_Val == DISABLE && Val == ENABLE ){
		Init_Up_Down_EACT();	
	}else if(default_Val == ENABLE && Val == DISABLE){
			FWriteSingleCoil(Y_Axis.ID,Y19_SVON,DISABLE);
	}
}
/***************************************************
	* File Name     : Up_Down_EACT_Speed_Set
	* Description   : Up_Down_EACT_Speed_Set
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
***************************************************/
void Up_Down_EACT_Speed_Set(void){
	uint32_t  Speed = ACT_Parameter[ACT_UP_DOWN_SPEED].data ;	

	Choice_Menu_Num((char *)ACT_Parameter[ACT_UP_DOWN_SPEED].Name ,
														ACT_Parameter[ACT_UP_DOWN_SPEED].LSL ,
														ACT_Parameter[ACT_UP_DOWN_SPEED].USL ,
														ACT_Parameter[ACT_UP_DOWN_SPEED].Step_Length,
														&Speed,"mm/s");		
	ACT_Parameter[ACT_UP_DOWN_SPEED].data  = Speed;
	Save_Hold_Reg_data(ACT_UP_DOWN_SPEED);
}
/***************************************************
	* File Name     : Up_Down_EACT_Standy_Set
	* Description   : Up_Down_EACT_Standy_Set
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
***************************************************/
void Up_Down_EACT_Standy_Set(void){
	u8 key = 0;
	double Coordinate =0.0;
	
	if(ACT_Parameter[ACT_UP_DOWN_EN].data != ENABLE ){
		lcdreset ();
		lcdpos (2,0);
		lcd_printf("上下电缸未开启");
		step_test_mode_get_key ();
		return ;
	}
	
	lcdreset ();
	lcdpos(0,0);			
	lcd_printf("%s",ACT_Parameter[ACT_Up].Name  );
	lcdpos(1,0);
	lcd_printf("范围:%3.0f-%3.0fmm  ",ACT_Parameter[ACT_Up].LSL,ACT_Parameter[ACT_Up].USL );
	lcdpos(2,0);	
	lcd_printf("Y=%8.3fmm    ",ACT_Parameter[ACT_Up].data ); //		
	FWriteSingleCoil(Y_Axis.ID ,Y19_SVON,DISABLE );						
	lcdpos(3,0);lcd_printf("L:退出  R:保存");
	while(1){
			Get_LEC_Current_Postion(Y_Axis.ID,&Coordinate);
			lcdpos(2,0);	
			lcd_printf("Y=%8.3fmm    ",Coordinate); //
			key = GetKey_Status();
			if(key == Left_Button_Pressed_Down ){
					break ;
			}else if(key == Right_Button_Pressed_Down ){
				if(Coordinate < ACT_Parameter[ACT_Up].USL && Coordinate > ACT_Parameter[ACT_Up].LSL )	{				
					lcdpos(3,0);lcd_printf("数据保存...     ");
					Get_LEC_Current_Postion(Y_Axis.ID,&Coordinate);
					ACT_Parameter[ACT_Up].data = Coordinate;
					Save_Hold_Reg_data(ACT_Up);
					lcdpos(3,0);lcd_printf("数据保存OK      ");
					break ;
				}else{
						lcdpos(2,0);	
						lcd_printf("设置数据超规格"); //
						startkeywait (1,1);
				}
			}
	}
	startkeywait (1,1);
}
/***************************************************
	* File Name     : Up_Down_EACT_Standy_Set
	* Description   : Up_Down_EACT_Standy_Set
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
***************************************************/
void Up_Down_EACT_Push_Set(void){
	u8 key = 0;
	double Coordinate =0.0;
	
	if(ACT_Parameter[ACT_UP_DOWN_EN].data != ENABLE ){
		lcdreset ();
		lcdpos (2,0);
		lcd_printf("上下电缸未开启");
		step_test_mode_get_key ();
		return ;
	}
		
	lcdreset ();
	lcdpos(0,0);			
	lcd_printf("%s",ACT_Parameter[ACT_Down].Name  );
	lcdpos(1,0);
	lcd_printf("范围:%3.0f-%3.0fmm  ",ACT_Parameter[ACT_Down].LSL,ACT_Parameter[ACT_Down].USL );
	lcdpos(2,0);	
	lcd_printf("Y=%8.3fmm    ",ACT_Parameter[ACT_Down].data ); //		
	FWriteSingleCoil(Y_Axis.ID ,Y19_SVON,DISABLE );						
	lcdpos(3,0);lcd_printf("L:退出  R:保存");
	while(1){
			Get_LEC_Current_Postion(Y_Axis.ID,&Coordinate);
			lcdpos(2,0);	
			lcd_printf("Y=%8.3fmm    ",Coordinate); //
			key = GetKey_Status();
			if(key == Left_Button_Pressed_Down ){
					break ;
			}else if(key == Right_Button_Pressed_Down ){
				if(Coordinate < ACT_Parameter[ACT_Down].USL && Coordinate > ACT_Parameter[ACT_Down].LSL )	{				
					lcdpos(3,0);lcd_printf("数据保存...     ");
					Get_LEC_Current_Postion(Y_Axis.ID,&Coordinate);
					ACT_Parameter[ACT_Down].data = Coordinate;
					Save_Hold_Reg_data(ACT_Down);
					lcdpos(3,0);lcd_printf("数据保存OK      ");
					break ;
				}else{
						lcdpos(2,0);	
						lcd_printf("设置数据超规格"); //
						startkeywait (1,1);
				}
			}
	}
	startkeywait (1,1);
}

Menu_List_Typedef Eact_UpDown_List[] = 
{
	{"电缸开启      ",Up_Down_EACT_Enable_Set},
	{"速度设置      ",Up_Down_EACT_Speed_Set },
	{"待机位置　　　",Up_Down_EACT_Standy_Set},
	{"压合位置　　  ",Up_Down_EACT_Push_Set  },	
	{NULL }
};



/**************************************************************************
	* File Name     : Up_Down_EACT_set
	* Description   : 上下运动电缸参数设置
  * Input         : 无
  * return        : 读取OK 0 反之非0
	* Author        : Morton
	* Date          : 2019/4/26
**************************************************************************/
uint8_t  Up_Down_EACT_set(void)
{
	if(Fixture.UpDown == Valve ){
		lcdreset ();
		lcdpos (2,0); lcd_printf("本治具气缸下压");
		step_test_mode_get_key ();
		return 1;
	}else {
		Menu_List_Fun("上下电缸设置",Eact_UpDown_List);	
		if(ACT_Parameter[ACT_UP_DOWN_EN].data == ENABLE ){
			Init_Up_Down_EACT();
			Running_Position(Y_Axis,Absolute_Coordinate,ACT_Parameter[ACT_Up].data,ACT_Parameter[ACT_UP_DOWN_SPEED].data,ENABLE);	

		}		
	}
	RevertStartupScreen ();//显示界面	
	return 0;
}
/**************************************************************************
	* File Name     : Up_Down_EACT_set
	* Description   : 上下运动电缸参数设置
  * Input         : 无
  * return        : 读取OK 0 反之非0
	* Author        : Morton
	* Date          : 2019/4/26
**************************************************************************/

uint8_t Up_Down_EACT_MOVE( uint8_t Num){
	uint8_t  TEMP = 0;
	if(ACT_Parameter[ACT_UP_DOWN_EN].data != ENABLE){
		return  0;
	}
	while(Safe_Grating_Sensor == SEN_SET ) delay_ms (100);
	switch (Num){
		case 0 :	
				Y_Axis.Protect_Mode      =  HOLD ;
				Y_Axis.Protect_Range_LSL = -100;
				Y_Axis.Protect_Range_USL = 100 ;
				TEMP = Running_Position(Y_Axis,Absolute_Coordinate,ACT_Parameter[ACT_Up].data,ACT_Parameter[ACT_UP_DOWN_SPEED].data,ENABLE); break;
		case 1 :	
				Y_Axis.Protect_Mode      =  RETURN ;
				Y_Axis.Protect_Range_LSL = -100;
				Y_Axis.Protect_Range_USL = 100;
		  	TEMP = Running_Position(Y_Axis,Absolute_Coordinate,ACT_Parameter[ACT_Down].data,ACT_Parameter[ACT_UP_DOWN_SPEED].data-100,ENABLE); 
		
				if(TEMP == False ){
						lcdreset ();;
						lcdpos (1,0); 
						lcd_printf ("光栅被遮挡      ");
				}
				break;	
		default : break;
	}
	return TEMP;
}

