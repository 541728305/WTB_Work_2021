#include "usb_move.h"
#include "motor.h"
#include "delay.h"
#include "24cxx.h"
#include "lcd3033.h"
#include "other.h"
#include "reg.h"
#include "global.h"
#include "sup_fun.h"
#include "stm32f10x_tim.h"
#include "usart.h"
#include "base_Config.h"
#include "stm32f10x_exti.h"
#include "menu.h"
#include "motor.h"

extern  FunctionalState  Motor_Debug_Flag ;


/***************************************************
	* File Name     : Init_USB_Move_Motor
	* Description   : Init_USB_Move_Motor
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 5-Jun-2020
***************************************************/
void Init_USB_Move_Motor(void ){
		if(Reg[Dot_Enable].Value != ENABLE)
			return ;

	
		Motor.Stroke             = 25;     //设定电缸行程
		Motor.Speed              = 100;
		Motor.Axis_Name          = 1 ;	
		Motor.Forward_Direction  = 1;
		Motor.Enable             = Reg[Dot_Enable].Value;
	
		Motor.Accelerate_Pulse_CNT = 500;
		Motor.Start_Frequency = 500;
	  Motor.Max_Run_Frequency = 30000;
		Motor.Standby_Position   = Reg[Dot_Motor_Standbypos].Value ;
		Motor.Product_Position   = Reg[Dot_Motor_Dotpos].Value;
	
		Motor.Microstep   = 4 ;      //驱动器细分
		Motor.Screw_Pitch = 2;      //螺距
		Motor.Direction   = Motor.Forward_Direction ; //初始化为为正方向
		Motor.Initialization_Fun = GPIO_Initialize_Motor ;
//		Motor.Limit_Set_Fun =  Motor_Limit_Check;
		Motor.Absolute_Coordinate = 0.0; // 绝对坐标初始化为0
		Motor.Standby_Position = 30.0;
		Motor.Status = Standby;
		Motor.Initialization_Fun();
			
		if(Motor_Setup(Motor.Stroke/Motor.Screw_Pitch*200.0*Motor.Microstep,ENABLE)== False)
				return ;
}


/***************************************************
	* File Name     : USB_MOVE
	* Description   : USB_MOVE
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 5-Jun-2020
***************************************************/
uint8_t  USB_MOVE(uint8_t Status){
	uint8_t Val=0;
	if(Fixture.USB_Move != ENABLE || Reg[Dot_Enable].Value != ENABLE )
		return True;
	Valve_Drive(USB_Block_Rress,SET); delay_ms (350);	
	if(Status == SET){
		Val = Dot_Move(Dot_Motor_Dotpos);		
	}else{
		Val = Motor_Setup(Motor.Stroke/Motor.Screw_Pitch*200.0*Motor.Microstep,DISABLE );	
	}
	Valve_Drive(USB_Block_Rress,RESET); 
	delay_ms (100);	
	return Val ;
}



/***************************************************
	* File Name     : USB_MOVE
	* Description   : USB_MOVE
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 5-Jun-2020
***************************************************/
void USB_Move_Display( void ){
	Dot_Move(Dot_Motor_Dotpos);		
	delay_ms (500);
	Motor_Setup(Motor.Stroke/Motor.Screw_Pitch*200.0*Motor.Microstep,DISABLE );	
	delay_ms (300);
}

/*********************************************************************************************
  * File Name     : Motor_Dot_Enable_Set
	* Description   : Motor_Dot_Enable_Set
  * Input         : /
  * return        : /
  * Version       : V1.0
	* Author        : Morton
	* Date          : 2019/8/8
*********************************************************************************************/
void USB_Motor_Enable_Set(void){
	uint8_t  Value ,preValue = Reg[Dot_Enable].Value ;// = Reg[Dot_Num_Check].Value ; 
	char Name[2][17] = {"关闭","开启"};
	Value = preValue;
	Choice_Menu("-USB电机",Name,2, &Value);	
	Reg[Dot_Enable].Value  = Value;
	Save_Single_Reg_Value (Dot_Enable);	
	
	if(Value == ENABLE &&preValue == DISABLE && Fixture.Dot_Type == __byMotor){
		if(Motor_Debug_Flag == DISABLE ){
		  Motor_Setup(Motor.Stroke/Motor.Screw_Pitch*200.0*Motor.Microstep,ENABLE);
		  Set_Motor_Debug_SETUP_Flag (ENABLE);
			Valve_Drive (Pen_Box,SET);
		}
	}

}
/*********************************************************************************************
  * File Name     : Motor_Dot_Speed_Set
	* Description   : Motor_Dot_Speed_Set
  * Input         : /
  * return        : /
  * Version       : V1.0
	* Author        : Morton
	* Date          : 2019/8/8
*********************************************************************************************/
void USB_SET_Speed_Set(void){
	Motor_Speed_Set("-USB置位速度  ",Dot_Motor_Speed_SET,"mm/s");
}
/*********************************************************************************************
  * File Name     : Motor_Pos_Set
	* Description   : Motor_Pos_Set
  * Input         : /
  * return        : /
  * Version       : V1.0
	* Author        : Morton
	* Date          : 2019/8/8
*********************************************************************************************/
void USB_SET_Pos_Set(void){
	Motor_Pos_Set("-USB位置设置",Dot_Motor_Dotpos);
}
/*********************************************************************************************
  * File Name     : Motor_RESET_Speed_Set
	* Description   : Motor_RESET_Speed_Set
  * Input         : /
  * return        : /
  * Version       : V1.0
	* Author        : Morton
	* Date          : 2019/8/8
*********************************************************************************************/
void USB_RESET_Speed_Set(void){
	Motor_Speed_Set("-USB退出速度  ",Dot_Motor_Speed_RESET,"mm/s");
}
Menu_List_Typedef usb_move_List[] = 
{
	{"电机开启      ",USB_Motor_Enable_Set },	
	{"-USB位置设置  ",USB_SET_Pos_Set      },		
	{"-USB插拔演示  ",USB_Move_Display     },		
	{"-USB置位速度　",USB_SET_Speed_Set    },
//	{"-USB退出速度  ",USB_RESET_Speed_Set  },

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
uint8_t USB_Move_Set(void){
	Set_Motor_Debug_SETUP_Flag(DISABLE);	
	Menu_List_Fun(" USB设置",usb_move_List);
	delay_ms(300);
	Motor_Setup(Motor.Stroke/Motor.Screw_Pitch*200.0*Motor.Microstep,ENABLE);
	delay_ms(300);		
	RevertStartupScreen();
	return 1;
}
