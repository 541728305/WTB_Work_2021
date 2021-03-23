#include "dot.h"
#include "reg.h"
#include "other.h"
#include "menu.h"
#include "lcd3033.h"
#include "base_Config.h"
#include "stm32f10x_tim.h"
#include "delay.h"
#include "global.h"
#include "usart.h"
#include "sup_fun.h"
//#define 	 Debug_Mode		
/*********************************************************************************************
  * File Name     : Dot_Enable
	* Description   : Dot_Enable
  * Input         : /
  * return        : /
  * Version       : V1.0
	* Author        : Morton
	* Date          : 2019/8/8
*********************************************************************************************/
void Dot_Enable_Set(void){
	uint8_t  Value = DISABLE ;// = Reg[Dot_Num_Check].Value ; 
	char Name[2][17] = {"关闭","开启"};
	Value = Reg[Dot_Enable].Value;
	Choice_Menu("打点功能",Name,2, &Value);	
	Reg[Dot_Enable].Value  = Value;
	Save_Single_Reg_Value (Dot_Enable);	
	
	
	
	
}


/*********************************************************************************************
  * File Name     : Dot_Time_Set
	* Description   : Dot_Time_Set
  * Input         : /
  * return        : Result
  * Version       : V1.0
	* Author        : Morton
	* Date          : 2020/4/5
*********************************************************************************************/
void Dot_Time_Set(void){	
		uint32_t  Num = Reg[Dot_Keep_Time].Value ;
		Choice_Menu_Num("打点时间设置    ",Reg[Dot_Keep_Time].LSL ,
																			 Reg[Dot_Keep_Time].USL,
																			 Reg[Dot_Keep_Time].Step_Length ,
																			&Num,"ms");
		Reg[Dot_Keep_Time].Value = Num ;
		Save_Single_Reg_Value (Dot_Keep_Time);
}
/*********************************************************************************************
  * File Name     : Dot_CNT_Enable_Set
	* Description   : Dot_CNT_Enable_Set
  * Input         : /
  * return        : Result
  * Version       : V1.0
	* Author        : Morton
	* Date          : 2020/4/5
*********************************************************************************************/
void Dot_CNT_Enable_Set(void){
	char Name[2][17] = {"关闭","开启"};	
	uint8_t Value = Reg[Dot_CNT_Enable].Value;
	Choice_Menu("打点次数管控",Name,2, &Value);	
	Reg[Dot_CNT_Enable].Value  = Value;
	Save_Single_Reg_Value (Dot_CNT_Enable);	
}
/*********************************************************************************************
  * File Name     : Dot_CNT_Set
	* Description   : Dot_CNT_Set
  * Input         : /
  * return        : Result
  * Version       : V1.0
	* Author        : Morton
	* Date          : 2020/4/5
*********************************************************************************************/
void Dot_CNT_Set(void) {
		uint32_t Num = Reg[Dot_Pen_MAX].Value ; 
		Choice_Menu_Num( "打点笔寿命",
												Reg[Dot_Pen_MAX].LSL,
												Reg[Dot_Pen_MAX].USL,
												Reg[Dot_Pen_MAX].Step_Length,
												&Num,
												"PCS/支"
											);
		Reg[Dot_Pen_MAX].Value = Num;
		Save_Single_Reg_Value (Dot_Pen_MAX);	
}
/*********************************************************************************************
  * File Name     : Dot_CNT_Clear
	* Description   : Dot_CNT_Clear
  * Input         : /
  * return        : Result
  * Version       : V1.0
	* Author        : Morton
	* Date          : 2020/4/5
*********************************************************************************************/
void Dot_CNT_Clear(void){
		lcdreset ();
		cyc4or3run();lcd_printf ("是否 ???        ");
		cyc4or3run();lcd_printf ("清零打点计数    ");
		cyc4or3run();lcd_printf ("                ");
		cyc4or3run();lcd_printf ("L:是  R:否      ");

		if(step_test_mode_get_key ()== Left_Button_Pressed_Down ){
			Reg[Dot_Pen_CNT].Value = 0;
			Save_Single_Reg_Value (Dot_Pen_CNT);
			cyc4or3run ();
			lcd_printf ("打点计数已清零");
			cyc4or3run ();
			lcd_printf ("......        ");
			step_test_mode_get_key ();
		}
}




/***************************************************
	* File Name     : Sample_Notice_Msage
	* Description   : Sample_Notice_Msage
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 11-April-2020
***************************************************/
void Dot_Pen_Replace_Check(void ){
	
	uint16_t  CNT = 0;
	if(Fixture.Dot == DISABLE )
		return ;
	
	if( Reg[Dot_CNT_Enable].Value  == ENABLE &&
			Fixture.Status == RESET &&
		 (Reg[Dot_Pen_CNT].Value  >= Reg[Dot_Pen_MAX].Value))
		{	

			#ifdef Debug_Mode		
				Uart_printf (USART1,"%s Dot Counter:%d/%d\r\n",(Reg[Dot_CNT_Enable].Value  == ENABLE?"开启":"关闭"),
																											 (uint16_t )(Reg[Dot_Pen_CNT].Value),
																											 (uint16_t )(Reg[Dot_Pen_MAX].Value)   );
			#endif

			lcdreset ();
			cyc4or3run ();lcd_printf ("打点笔已累计使用");
			cyc4or3run ();lcd_printf ("%4d次, 治具已锁定",Reg[Dot_Pen_CNT].Value);
			cyc4or3run ();lcd_printf ("请长按任意键 5秒");
			cyc4or3run ();lcd_printf ("解除锁定        ");

			while(left_start_key == 0 ||right_start_key ==0 ) 
					delay_ms (10);
			while(1){
				delay_ms (50);
				if(left_start_key == 0 ||right_start_key ==0){
						CNT ++;
				}else {
						CNT = 0;
				}
				lcdpos (lcdcon -1,14);  lcd_printf ("%2d",(CNT*50/1000));
				if((CNT*50) >= 5000){
					cyc4or3run ();
					lcd_printf ("请启动测试      ");
					cyc4or3run ();
					cyc4or3run ();
					cyc4or3run ();
					lcd_printf ("    解锁成功    "); 
					break;
				}		
			}
	
		Reg[Dot_Pen_CNT].Value = 0;
		Save_Single_Reg_Value (Dot_Pen_CNT);
		while(left_start_key == 0 ||right_start_key ==0 ) 
					delay_ms (10);
	}
}


#include "motor.h"

Menu_List_Typedef dot_List[] = 
{
	{"打点开启      ",Dot_Enable_Set},
//	{"打点开启      ",Motor_Dot_Enable_Set },		
	{"打点时间      ",Dot_Time_Set         },
	{"打点演示      ",Product_Mark_Dot     },	
	{"打点计数　　　",Dot_CNT_Enable_Set   },
	{"打点笔寿命    ",Dot_CNT_Set          },	
	{"打点计数清零　",Dot_CNT_Clear        },
	
	{"打点速度    　",Motor_Dot_Speed_Set  },
	{"打点复位速度  ",Motor_RESET_Speed_Set},
	{"打点位置      ",Motor_Dot_Pos_Set    },	
	{"打点待机位置  ",Motor_Standby_Pos_Set},	
	{"打点抬起位置  ",Motor_Up_Pos_Set     },	
	{NULL }
};

/*********************************************************************************************
  * File Name     : Dot_Set
	* Description   : Dot_Set
  * Input         : /
  * return        : Result
  * Version       : V1.0
	* Author        : Morton
	* Date          : 2020/4/5
*********************************************************************************************/
uint8_t Dot_Set(void){
	if(Fixture.Dot == DISABLE ){
		lcdreset ();
		lcdpos (2,0); lcd_printf("打点已屏蔽");
		step_test_mode_get_key ();
	}else{
		if(Fixture.Dot_Type == __byMotor ){	
			Set_Motor_Debug_SETUP_Flag(DISABLE);
		}else {
			dot_List[6].Name = NULL ;
			dot_List[6].fun  = NULL ;
		}			
		Menu_List_Fun("打点设置",dot_List);
		if(Fixture.Dot_Type == __byMotor && Reg[Dot_Enable].Value == ENABLE ){
			Dot_Move (Dot_Motor_Uppos); 
			Valve_Drive (Pen_Box,RESET); delay_ms (500);
			Dot_Move (Dot_Motor_Standbypos); 
		}			
	}
	RevertStartupScreen();
	return 1;
}



/*********************************************************************************************
  * File Name     : Dot_Pen_RESET
	* Description   : Dot_Pen_RESET
  * Input         : /
  * return        : /
  * Version       : V1.0
	* Author        : Morton
	* Date          : 2019/8/8
*********************************************************************************************/
void Product_Mark_Dot(void){	
		uint16_t i=0;
	  if(Fixture.Dot_Type == __byValve ){
				Valve_Drive (Dot_Pen ,SET);   
			  delay_ms (400); 
		}else if(Fixture.Dot_Type ==  __byMotor )
				Dot_Move(Dot_Motor_Uppos);
		Valve_Drive(Pen_Box ,SET);    delay_ms (400); 
	  if(Fixture.Dot_Type == __byValve ){
				Valve_Drive(Dot_Pen ,RESET);
		}else if(Fixture.Dot_Type ==  __byMotor )
				Dot_Move(Dot_Motor_Dotpos);
		for(i = 0 ; i < (Reg[Dot_Keep_Time].Value); i += 100)
				delay_ms (100);
		
	  if(Fixture.Dot_Type == __byValve ){
				Valve_Drive(Dot_Pen ,SET);
				delay_ms (400); 
		}else if(Fixture.Dot_Type ==  __byMotor )
				Dot_Move(Dot_Motor_Uppos);

		Valve_Drive(Pen_Box ,RESET);   delay_ms (400); 	

	
	  if(Fixture.Dot_Type == __byValve ){		
				Valve_Drive(Dot_Pen ,RESET);  
		}else if(Fixture.Dot_Type ==  __byMotor )
				Dot_Move(Dot_Motor_Standbypos);
		
		if( Reg[Dot_CNT_Enable].Value  == ENABLE){

			Reg[Dot_Pen_CNT].Value += 1; 
			Save_Single_Reg_Value (Dot_Pen_CNT);
		}
	
}
