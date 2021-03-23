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
#include "ad7176.h"


FunctionalState  Motor_Debug_Flag = ENABLE;
//#define Debug_Mode
  

Motor_Par_Typedef Motor;

static uint32_t Motor_Pulse_couter = 0;
static double   Fre_Accelerate_Set = 0.0;



void GPIO_Initialize_Motor(void){
	
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOF,&GPIO_InitStructure);
		GPIO_ResetBits(GPIOF, GPIO_Pin_9|GPIO_Pin_10);	
		delay_ms (10);
}



void Init_TIM6_PWM(u16 arr,u16 psc){

		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	
		NVIC_InitTypeDef NVIC_InitStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);	//?????3??
		TIM_DeInit(TIM6);
		//初始化TIM3
		TIM_TimeBaseStructure.TIM_Period = arr; 
		TIM_TimeBaseStructure.TIM_Prescaler =psc; 
		TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
		TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); 
		
		NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_Init(&NVIC_InitStructure);  
		
		GPIO_ResetBits(Motor_PUL_Port ,Motor_PUL_Pin);	
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );
		TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE );
		TIM_Cmd(TIM6, ENABLE);  
}


//函数名： Calculate_Pulse_Count
//参  数： Coordinate,电缸移动至设定坐标点，Type移动类型，0绝对坐标，1相对正方向坐标
//功  能： 计算电机移动至目标位置所需脉冲数 圈数 = 距离/螺距*360/1.8*细分 一圈脉冲数 = 800 等价于细分 =  4
//作  者： Morton
//日  期： 2018.6.25
static void Calculate_Pulse_Count(uint8_t Axis,double Coordinate, uint8_t Type){
		double Step_Length = 0.0 ; 
		double Move_Distance = 0.0; //相对当前位置移动距离
		if(Type == Absolute ){ //绝对坐标判断,在超行程和小于零时报错
				if(Coordinate < 0 || Coordinate > Motor.Stroke  ){
						cyc4or3run (); lcd_printf ("电缸绝对坐标    ");
						cyc4or3run (); lcd_printf ("设置错误-%7.2f",Coordinate);
						while(1);
				}
				if(Coordinate >= Motor.Absolute_Coordinate ){
						Move_Distance = Coordinate - Motor.Absolute_Coordinate;
				}
				else
						Move_Distance = Motor.Absolute_Coordinate - Coordinate ;
				Motor.Absolute_Coordinate = Coordinate;
		}else if(Type == Relative ){ //判断相对移动之后是否在导程内
			
								
				#if defined Debug_Mode 
					Uart_printf (Fixture.Comm_Uart, "Absolute_Coordinate_Pre:%g\r\n", Motor.Absolute_Coordinate);
				#endif
			
				Motor.Absolute_Coordinate += Coordinate;
				if(Motor.Absolute_Coordinate >= 0 && Motor.Absolute_Coordinate <= Motor .Stroke ){
						if(Coordinate >= 0)
								Move_Distance = Coordinate ;
						else
								Move_Distance = - Coordinate ;	
				}
				else {
						cyc4or3run (); lcd_printf ("电缸相对坐标    ");
					  cyc4or3run (); lcd_printf ("设置错误:%7.2f",Coordinate);
					  cyc4or3run (); lcd_printf ("设置错误:%7.2f",Motor.Absolute_Coordinate);					
							#if defined Debug_Mode 
								Uart_printf (Fixture.Comm_Uart, "电缸相对坐标:%g\r\n", Coordinate);
				       	Uart_printf (Fixture.Comm_Uart, "Absolute_Coordinate Error:%g\r\n", Motor.Absolute_Coordinate);
							#endif
					
					
					
					
						while(1);
				}		
		}else{
				cyc4or3run (); lcd_printf("电缸坐标类型");
				cyc4or3run (); lcd_printf("设置错误");
				while(1);
		}
		Step_Length = (double)Motor.Screw_Pitch/(360.0/1.8*(double)Motor.Microstep);
		Motor.Pulse = (double)Move_Distance/Step_Length ;//(double)SMC_LECPAN.Screw_Pitch*360.0/1.8*(double)SMC_LECPAN.Microstep;
		
		#if defined Debug_Mode 
			Uart_printf (Fixture.Comm_Uart, "Motor Pulse:%d\r\n", Motor.Pulse);
		#endif
}
//函数名： Judge_Direction
//参  数： Coordinate,电缸移动至设定坐标点，Type移动类型，0绝对坐标，1相对正方向坐标
//功  能： 判断电机运行方向
//作  者： Morton
//日  期： 2018.6.25
static void Judge_Direction(uint8_t Axis,double Coordinate,uint8_t Type){
		if(Type == 0){ //绝对坐标方向判断
				if(Coordinate >= Motor.Absolute_Coordinate )
						Motor.Direction = Motor.Forward_Direction ;
				else
						Motor.Direction = !Motor.Forward_Direction ;
		}else if(Type == 1){ //相对坐标方向判断
				if(Coordinate >= 0)
						Motor.Direction = Motor.Forward_Direction ;
				else
						Motor.Direction = !Motor.Forward_Direction ;				
		}else{
				cyc4or3run (); lcd_printf("电缸坐标类型");
				cyc4or3run (); lcd_printf("设置错误");
				while(1);
		}
		Motor_DIR = Motor.Direction;  //加载电缸运行方向
		
		#if defined Debug_Mode 
		Uart_printf (Fixture.Comm_Uart, "Motor PUL:%s\r\n", Motor.Direction ==Motor.Forward_Direction ?"正方向":"反方向" );
		#endif
}


void TIM6_IRQHandler(void){  //TIM3??
//		#if defined Debug_Mode 
//			Uart_printf (Fixture.Comm_Uart, "TIM6_IRQHandler:%d\r\n", Motor_Pulse_couter);
//		#endif
		if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) {
				Motor_Pulse_couter++;
				if((Motor_Pulse_couter >>1) >= Motor .Pulse){ 
						TIM_Cmd(TIM6, DISABLE ); 
						Motor_PUL = 0 ;
						Motor.Status = End;
				}
				else if(Motor_Pulse_couter & 0x01){
					   Motor_PUL = 1; 
				}
				else{  
						 Motor_PUL = 0 ;
					//分两种情况进行加减-------长距离,有匀速过程------------短距离,加速后直接减速-----------
						if((( Motor_Pulse_couter >>1) <= Motor.Accelerate_Pulse_CNT) &&(( Motor_Pulse_couter >>1) <= Motor.Pulse/2 )) {								
								TIM6->ARR =  1000000/(Motor.Start_Frequency + Fre_Accelerate_Set*( Motor_Pulse_couter >>1))/2-1 ; //(uint16_t)((-4.774*( SMC_Pulse_couter >>1))+1000)-1 ;
						}else if((( Motor_Pulse_couter >>1) > Motor.Pulse/2 )&&((Motor.Pulse -(Motor_Pulse_couter>>1))<= Motor.Accelerate_Pulse_CNT )) {
								TIM6->ARR = 1000000/(Motor.Start_Frequency + Fre_Accelerate_Set*(Motor.Pulse -(Motor_Pulse_couter>>1)-1))/2-1  ;//(uint16_t)(-4.774*((SMC_LECPAN.Pulse -(SMC_Pulse_couter>>1)-1))+1000)-1 ;
						}
						else //((SMC_Pulse_couter>>1) > Accelerate_Pulse_CNT)
						{
								TIM6->ARR = 1000000/(Motor.Max_Run_Frequency)/2-1 ;
						}
				}
				TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );  
		}
}

//函数名： SMC_LEC_Move
//参  数： Coordinate,电缸移动至设定坐标点，Type移动类型，0绝对坐标，1相对正方向坐标
//功  能： 电缸移动至设置坐标
//作  者： Morton
//日  期： 2018.6.25
void Motor_Move(uint8_t Axis,double Coordinate,uint8_t Type){
		double 	Step_Length  = (double)Motor.Screw_Pitch/(360.0/1.8*(double)Motor.Microstep);
		double  Previous_Coordinate = Motor.Absolute_Coordinate;	
		Judge_Direction(Axis, Coordinate, Type);  //判断运行方向.
		delay_ms (1); //脉冲信号必须滞后于方向信号
		Calculate_Pulse_Count(Axis, Coordinate,Type);  //计算脉冲数	
		Motor_Pulse_couter = 0;		//生成矩形脉冲
		Fre_Accelerate_Set = (Motor.Max_Run_Frequency - Motor.Start_Frequency )/(Motor.Accelerate_Pulse_CNT - 1); 
		if( Motor .Pulse  > 0)
				Init_TIM6_PWM( 1000000/Motor .Start_Frequency/2-1 ,Motor.Speed-1); //预分频为1MHz,ARR = 1M/Fre/2-1,50%占空比许除以2
		else
				return ;
		Motor.Status = Runing; 		
		while(1){
//				Motor.Absolute_Coordinate = Previous_Coordinate + (Motor_Pulse_couter>>1)*Step_Length; 
//				if(Motor.Display_Coordinate_Value == SET){
//						lcdpos (lcdcon -1,0); lcd_printf ("X = %6.3fmm    ",Motor.Absolute_Coordinate );
//				}
//				if(Motor.Status == End){
//						Motor.Absolute_Coordinate = Previous_Coordinate + (Motor_Pulse_couter>>1)*Step_Length; 
//						if(Motor.Display_Coordinate_Value == SET){
//								lcdpos (lcdcon -1,0); lcd_printf ("X = %6.3fmm    ",Motor.Absolute_Coordinate );
//						}
//						break ;
//				}

				if(Motor.Status == End)
						break ;
		}
		Motor.Status = Standby;
}


/***************************************************
	* File Name     : Motor_Limit_Check
	* Description   : Motor_Limit_Check
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 7-May-2020
***************************************************/
void Motor_Limit_Check(FunctionalState St){
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//????????
		
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource11);
  	EXTI_InitStructure.EXTI_Line = EXTI_Line11;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //检测信号上升沿
  	EXTI_InitStructure.EXTI_LineCmd = St;
  	EXTI_Init(&EXTI_InitStructure);	 	
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					
  	NVIC_InitStructure.NVIC_IRQChannelCmd = St;								
  	NVIC_Init(&NVIC_InitStructure); 
	

  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
  	EXTI_InitStructure.EXTI_Line = EXTI_Line0;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //检测信号上升沿
  	EXTI_InitStructure.EXTI_LineCmd = St;
  	EXTI_Init(&EXTI_InitStructure);	 	
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					
  	NVIC_InitStructure.NVIC_IRQChannelCmd = St;								
  	NVIC_Init(&NVIC_InitStructure); 	
	
	
}

/***************************************************
	* File Name     : EXTI15_10_IRQHandler
	* Description   : EXTI15_10_IRQHandler
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 7-May-2020
***************************************************/
void EXTI15_10_IRQHandler(void){
		if (EXTI_GetITStatus(EXTI_Line11) != RESET ){
				delay_ms(10);
				if(Motor_Origin_Sensor == Motor_Sensor_SET || Motor_Limit_Sensor == Motor_Sensor_SET ){
						lcdreset ();
						lcdpos (0,0); lcd_printf ("      警告     ");
						lcdpos (1,0); lcd_printf ("电缸超行程!!!  ");
						lcdpos (2,0); lcd_printf ("复位治具中...  ");
						beep (5,200);
					  TIM_Cmd(TIM6, DISABLE ); 
						STM32_Software_Reset_Hander();
				}
				EXTI_ClearITPendingBit(EXTI_Line11); 
		}
}
/***************************************************
	* File Name     : EXTI15_10_IRQHandler
	* Description   : EXTI15_10_IRQHandler
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 7-May-2020
***************************************************/
void EXTI0_IRQHandler(void){
		if (EXTI_GetITStatus(EXTI_Line0) != RESET ){
				delay_ms(10);
				if(Motor_Origin_Sensor == Motor_Sensor_SET || Motor_Limit_Sensor == Motor_Sensor_SET ){
						lcdreset ();
						lcdpos (0,0); lcd_printf ("      警告     ");
						lcdpos (1,0); lcd_printf ("电缸超行程!!!  ");
						lcdpos (2,0); lcd_printf ("复位治具中...  ");
						beep (5,200);
					  TIM_Cmd(TIM6, DISABLE ); 
						STM32_Software_Reset_Hander();
				}
				EXTI_ClearITPendingBit(EXTI_Line0); 
		}
}


#define Motor_Setup_Time  60

/***************************************************
	* File Name     : Initialize_Motor
	* Description   : Initialize_Motor
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 4-May-2020
***************************************************/


uint8_t Motor_Setup( uint32_t Max_Pulse,uint8_t En_bit)
{
		uint32_t i = 0;
		//Motor.Limit_Set_Fun (DISABLE);
		if(En_bit == ENABLE){
				cyc4or3run ();
				lcd_printf ("滑台回零...     ");
		}			
		if(Motor_Origin_Sensor == Motor_Sensor_RESET ){ // Sensor RESET 
			Motor_DIR   = !Motor.Forward_Direction ; //传感器复位，反方向跑
			delay_ms (10);
			for(i = 0; i< Max_Pulse; i ++ ){
					Motor_PUL = 0;
					delay_us (Motor_Setup_Time);
					Motor_PUL = 1;
					delay_us (Motor_Setup_Time);
					if(Motor_Origin_Sensor == Motor_Sensor_SET ){
							Motor_DIR   = Motor.Forward_Direction ;
							Motor_PUL = 0;
							delay_us (Motor_Setup_Time);
							Motor_PUL = 1;
							delay_us (Motor_Setup_Time);
							if(En_bit == ENABLE){
									lcdpos (lcdcon -1 ,14);
									lcd_printf ("OK");
							}
							Motor.Absolute_Coordinate = 0.0; // 绝对坐标初始化为0
						 // Motor.Limit_Set_Fun (ENABLE);
							delay_ms (200);
							return 0 ;
					}
			}
			if(En_bit == DISABLE){
					cyc4or3run ();
					lcd_printf ("滑台回零...     ");
			}	
			lcdpos (lcdcon -1 ,14);
			lcd_printf ("NG");		
			beep (2,200);
		}else {  //传感器置位，正方向跑
				Motor_DIR   = Motor.Forward_Direction ; //初始化为为正方向
				delay_ms (10);
				for(i = 0; i< Max_Pulse; i ++ ){
						Motor_PUL = 0;
						delay_us (Motor_Setup_Time);
						Motor_PUL = 1;
						delay_us (Motor_Setup_Time);
						if(Motor_Origin_Sensor == Motor_Sensor_RESET ){
								if(En_bit == ENABLE){
									lcdpos (lcdcon -1 ,14);
									lcd_printf ("OK");
								}
								Motor.Absolute_Coordinate = 0.0; // 绝对坐标初始化为0
							//	Motor.Limit_Set_Fun (ENABLE);
								delay_ms (200);
								return 0 ;
						}
				}
				if(En_bit == DISABLE){
						cyc4or3run ();
						lcd_printf ("滑台回零...     ");
				}	
				lcdpos (lcdcon -1 ,14);
				lcd_printf ("NG");		
				beep (2,200);
		}
		return 1;
}



/***************************************************
	* File Name     : Initialize_Motor
	* Description   : Initialize_Motor
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 4-May-2020
***************************************************/
void Initialize_Motor(void ){
		if(Reg[Dot_Enable].Value == DISABLE)
			return ;
	
		Motor.Stroke             = 45;     //设定电缸行程
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
		Motor.Limit_Set_Fun =  Motor_Limit_Check;
		Motor.Absolute_Coordinate = 0.0; // 绝对坐标初始化为0
		Motor.Standby_Position = 30.0;
		Motor.Status = Standby;
		Motor.Initialization_Fun();
			
		if(Motor_Setup(Motor.Stroke/Motor.Screw_Pitch*200.0*Motor.Microstep,ENABLE)== False)
				return ;
		
		Dot_Move (Dot_Motor_Standbypos); 

}

uint8_t Dot_Move( uint8_t pos){
	if(Reg[Dot_Enable].Value == DISABLE)
			return 0;
	switch(pos){
		case Dot_Motor_Standbypos :
					#if defined Debug_Mode
						  Uart_printf (Fixture.Comm_Uart ,"Run TO Dot_Motor_Standbypos\r\n");
							Uart_printf (Fixture.Comm_Uart ,"Coordinate = %g\r\n",Reg[Dot_Motor_Standbypos].Value);
					#endif
					
					Motor.Speed =  ( uint32_t)(Reg[Dot_Motor_Speed_RESET].Value*(-2.4)+792.0) ; // 300mm/s---30mm/s 72-720
	
					Motor_Move(1, Reg[Dot_Motor_Standbypos].Value , Absolute);  // 移动至待机位置 
					break ;
		case Dot_Motor_Dotpos     :  
					#if defined Debug_Mode
						  Uart_printf (Fixture.Comm_Uart ,"Run TO Dot_Motor_Dotpos\r\n");
							Uart_printf (Fixture.Comm_Uart ,"Coordinate = %g\r\n",Reg[Dot_Motor_Dotpos].Value);
					#endif
					Motor.Speed =  ( uint32_t)(Reg[Dot_Motor_Speed_SET].Value*(-2.4)+792.0)  ;
					Motor_Move(1, Reg[Dot_Motor_Dotpos].Value , Absolute);  // 移动至待机位置 
					break ;
		case Dot_Motor_Uppos  :
			
					#if defined Debug_Mode
						  Uart_printf (Fixture.Comm_Uart ,"Run TO Dot_Motor_Uppos\r\n");
							Uart_printf (Fixture.Comm_Uart ,"Coordinate = %g\r\n",Reg[Dot_Motor_Uppos].Value);
					#endif
		
					Motor.Speed =  ( uint32_t)(Reg[Dot_Motor_Speed_RESET].Value*(-2.4)+792.0) ;
					Motor_Move(1, Reg[Dot_Motor_Uppos].Value , Absolute);  // 移动至待机位置 
					break ;
	}
	return 0;
}

#include "menu.h"
/*********************************************************************************************
  * File Name     : Motor_Dot_Enable_Set
	* Description   : Motor_Dot_Enable_Set
  * Input         : /
  * return        : /
  * Version       : V1.0
	* Author        : Morton
	* Date          : 2019/8/8
*********************************************************************************************/
void Motor_Dot_Enable_Set(void){
	uint8_t  Value ,preValue = Reg[Dot_Enable].Value ;// = Reg[Dot_Num_Check].Value ; 
	char Name[2][17] = {"关闭","开启"};
	Value = preValue;
	Choice_Menu("打点功能",Name,2, &Value);	
	Reg[Dot_Enable].Value  = Value;
	Save_Single_Reg_Value (Dot_Enable);	
	
	if(Value == ENABLE &&preValue == DISABLE && Fixture.Dot_Type == __byMotor){
		if(Motor_Debug_Flag == DISABLE ){
		  Motor_Setup(Motor.Stroke/Motor.Screw_Pitch*200.0*Motor.Microstep,ENABLE );
		  Set_Motor_Debug_SETUP_Flag (ENABLE);
			Valve_Drive (Pen_Box,SET);
		}
	}

}

/*********************************************************************************************
  * File Name     : Motor_Speed_Set
	* Description   : Motor_Speed_Set
  * Input         : /
  * return        : /
  * Version       : V1.0
	* Author        : Morton
	* Date          : 2019/8/8
*********************************************************************************************/
void Motor_Speed_Set(char *Name, uint16_t reg_Num,char *Unit){
		uint32_t  Num = Reg[reg_Num ].Value ;
		Choice_Menu_Num(Name,Reg[reg_Num].LSL ,
													 Reg[reg_Num].USL,
													 Reg[reg_Num].Step_Length ,
														&Num,Unit);
		Reg[reg_Num].Value = Num ;
		Save_Single_Reg_Value (reg_Num);
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
void Motor_Dot_Speed_Set(void){
	Motor_Speed_Set("打点速度设置",Dot_Motor_Speed_SET,"mm/s");
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
void Motor_RESET_Speed_Set(void){
	Motor_Speed_Set("打点抬起速度设置",Dot_Motor_Speed_RESET,"mm/s");
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
void Motor_Pos_Set( char *Name, uint16_t sNum){
	uint8_t Key_Status = 0;
	
  if(Reg[Dot_Enable].Value == DISABLE){
		lcdreset ();
		lcdpos(2,0); lcd_printf ("电机已屏蔽");
		return ;
	}else{
		if(Motor_Debug_Flag == DISABLE ){
				Motor_Setup(Motor.Stroke/Motor.Screw_Pitch*200.0*Motor.Microstep,ENABLE);
				Set_Motor_Debug_SETUP_Flag (ENABLE);
				Valve_Drive (Pen_Box ,SET );
				delay_ms (400);
		}
	}
	lcdreset ();
	lcdpos (0,0); lcd_printf ("%s",Name);
	lcdpos (2,0);  lcd_printf ("X = %6.3fmm    ",Motor.Absolute_Coordinate );	
	Motor.Display_Coordinate_Value = SET  ;
	Motor.Speed = 720 ;
	#if defined Debug_Mode
		Uart_printf (Fixture.Comm_Uart , "Reg[sNum].Value = %g\r\n",Reg[sNum].Value);
		Uart_printf (Fixture.Comm_Uart , "Absolute_CoordinateValue = %g\r\n",Motor.Absolute_Coordinate);
	#endif
	
	Motor_Move(1, Reg[sNum].Value , Absolute);  
	lcdpos (3,0); lcd_printf ("L:+ R:- L+R:SAVE");
	while(1){
		lcdpos (2,0);  lcd_printf ("X = %6.3fmm    ",Motor.Absolute_Coordinate );	
		Key_Status = Get_start_key_val();
		if(Key_Status == Left_Button_Pressed_Down ){
			if((Motor.Absolute_Coordinate+Reg[sNum].Step_Length) <  Motor.Stroke )
					Motor_Move(1, Motor.Absolute_Coordinate +Reg[sNum].Step_Length, Absolute);  
		}
		else if(Key_Status == Right_Button_Pressed_Down ){
			if((Motor.Absolute_Coordinate-Reg[sNum].Step_Length) > 0.0 )
					Motor_Move(1, Motor.Absolute_Coordinate -Reg[sNum].Step_Length, Absolute); 
		}
		else if(Key_Status == Double_Button_Pressed_Down )
			break ;
	}
	Reg[sNum].Value  = Motor.Absolute_Coordinate;
	Save_Single_Reg_Value (sNum);	
	step_test_mode_get_key ();
		Motor.Display_Coordinate_Value = RESET  ;
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
void Motor_Dot_Pos_Set(void){
	Motor_Pos_Set("打点位置设置",Dot_Motor_Dotpos);
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
void Motor_Standby_Pos_Set(void){
	Dot_Move(Dot_Motor_Uppos); delay_ms (300);
	Valve_Drive (Pen_Box ,RESET);delay_ms (500);
	Motor_Pos_Set("打点笔待机位置",Dot_Motor_Standbypos);
	Dot_Move(Dot_Motor_Uppos); delay_ms (300);
	Valve_Drive (Pen_Box ,SET);delay_ms (500);
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
void Motor_Up_Pos_Set(void){
	Motor_Pos_Set("打点笔抬起位置",Dot_Motor_Uppos);
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
void Set_Motor_Debug_SETUP_Flag(FunctionalState st)
{
	Motor_Debug_Flag = st;	
}

