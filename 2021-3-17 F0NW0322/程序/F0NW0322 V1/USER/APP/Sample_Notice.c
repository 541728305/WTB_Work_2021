#include "sample.h"
#include "reg.h"
#include "other.h"
#include "menu.h"
#include "lcd3033.h"
#include "base_Config.h"
#include "stm32f10x_tim.h"
#include "delay.h"
#include "global.h"
#include "usart.h"
/*********************************************************************************************
	* File Name     : Init_TIM4
	* Description   : 初始化定时器4
  * Input         : arr，自动重装载值，psc 预分频系数, type 用途：0，定时器，1计数器，2，PWM输出
	* return        : /
	* Version       : V1.0 
	* Author        : Morton 
	* Date          : 24-Oct-2018 
*********************************************************************************************/ 
void Init_TIM4(uint32_t arr ,uint32_t psc  ){

		NVIC_InitTypeDef NVIC_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE); 

		TIM_DeInit (TIM4 ); 
		TIM_TimeBaseStructure.TIM_Period = arr; 
		TIM_TimeBaseStructure.TIM_Prescaler =psc; 
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
		TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 

		
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_Init(&NVIC_InitStructure);  
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  ); 
		TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); 
		TIM_Cmd(TIM4, ENABLE);
}

/*********************************************************************************************
	* File Name     : TIM4_IRQHandler
	* Description   : TIM4_IRQHandler
  * Input         : /
	* return        : /
	* Version       : V1.0 
	* Author        : Morton 
	* Date          : 10-Oct-2018 
*********************************************************************************************/ 
void TIM4_IRQHandler(){
	if(TIM_GetITStatus(TIM4 ,TIM_IT_Update )!= RESET ){
		Fixture.Sample_Time  ++;
	}
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update  ); 
}

/***************************************************
	* File Name     : Init_Smaple_Test_Notice
	* Description   : Init_Smaple_Test_Notice
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 11-April-2020
***************************************************/
void Init_Smaple_Test_Notice(void ){
	Init_TIM4(9999,7199);
}


/***************************************************
	* File Name     : Display_Sample_Time
	* Description   : Display_Sample_Time
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 11-April-2020
***************************************************/
void Display_Sample_Time(){
	float Time = 0;
	lcdreset ();
	lcdpos(0,0); lcd_printf ("样本:%3d分钟／次",(uint32_t)Reg[Sample_Cycle].Value );
	while(2){
		Time = (float)Reg[Sample_Cycle].Value*60- (float)Fixture.Sample_Time;
		if(Time < 0)
			Time = 0;
		if(GetKey_Status())
			break ;
		lcdpos(2,0);
		lcd_printf ("    %02d:%02d:%02d    ",((uint32_t)Time/60/60)%60,
		                                     ((uint32_t)Time/60)%60   ,
															            (uint32_t)Time%60);
	}
}


/***************************************************
	* File Name     : Sample_Notice_Enable_Set
	* Description   : Sample_Notice_Enable_Set
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
***************************************************/
void Sample_Notice_Enable_Set (void){
	uint8_t  Value = DISABLE ;
	char Name[2][17] = {"关闭","开启"};
	Value = Reg[Sample_Enable].Value ; 
	Choice_Menu("样本提示设置",Name,2, &Value);
	Reg[Sample_Enable].Value = Value;
	Save_Single_Reg_Value (Sample_Enable);	
	if(Reg[Sample_Enable].Value == DISABLE)
		TIM_Cmd(TIM4, DISABLE);
	else{
		Init_Smaple_Test_Notice();
	}
}

/***************************************************
	* File Name     : Sample_Cycle_Set
	* Description   : Sample_Cycle_Set
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
***************************************************/
void Sample_Cycle_Set (void){
		uint32_t T = 0 ;
		T = Reg[Sample_Cycle].Value;
		Choice_Menu_Num( "样本时间设置",
											Reg[Sample_Cycle].LSL,
											Reg[Sample_Cycle].USL,
											Reg[Sample_Cycle].Step_Length,
											&T,
											"分钟"
										);
		Reg[Sample_Cycle].Value = T;
		Save_Single_Reg_Value(Sample_Cycle);	
}

/***************************************************
	* File Name     : Sample_Cycle_Set
	* Description   : Sample_Cycle_Set
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
***************************************************/
void Sample_Time_Display (void){
	Display_Sample_Time();	
}

Menu_List_Typedef Sammple_List[] = 
{
	{"样本提示开启  ",Sample_Notice_Enable_Set},
	{"样本间隔时间  ",Sample_Cycle_Set},
	{"显示当前时间　",Sample_Time_Display},
	{NULL }
};


/***************************************************
	* File Name     : Init_Smaple_Test_Notice
	* Description   : Init_Smaple_Test_Notice
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 11-April-2020
***************************************************/
uint8_t  Smaple_Notice_Set(void){
	if(Fixture.Sample_Notice == DISABLE ){
		lcdreset ();
		lcdpos (2,0); lcd_printf("样本提示已屏蔽");
		step_test_mode_get_key ();
	}else 
		Menu_List_Fun("样本设置",Sammple_List);	
	RevertStartupScreen();
	return 1;
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
void Sample_Notice_Message(void ){
	int32_t  LOCK_Time = Reg[Sample_Cycle].Value *60 -Fixture.Sample_Time;	
	uint16_t  ___CNT = 0;
	lcdreset ();
	cyc4or3run ();lcd_printf ("样本时间%4d分钟",(uint32_t)Reg[Sample_Cycle].Value );
	cyc4or3run ();lcd_printf ("治具已锁定，测试");
	cyc4or3run ();lcd_printf ("样本，倒计时    ");
	cyc4or3run ();lcd_printf ("    %02d:%02d:%02d    ",(Fixture.Sample_Time/60/60)%60,
																										 (Fixture.Sample_Time/60)%60   ,
																										 	Fixture.Sample_Time%60);
	while(LOCK_Time){		
		delay_ms (50);		
		LOCK_Time = Reg[Sample_Cycle].Value *60 -Fixture.Sample_Time;
 
		if(LOCK_Time >= 0){
			lcdpos (3,0); 			
			lcd_printf ("    %02d:%02d:%02d    ",(LOCK_Time/60/60)%60,
																					 (LOCK_Time/60)%60   ,																										   
																				    LOCK_Time%60);	
		}	
		if(LOCK_Time<=0) {
			break ;
		}

	}
	cyc4or3run ();
	lcd_printf ("长按任意键 5秒, ");
	cyc4or3run ();
	lcd_printf ("  解除锁定      ");
	while(1){
		delay_ms (50);
		if(left_start_key == 0 ||right_start_key ==0){
				___CNT ++;
		}else {
				___CNT = 0;
		}
		if(left_start_key == 1 && right_start_key == 1){
				___CNT = 0;
		}
		lcdpos (lcdcon -1,14); ; lcd_printf ("%2d",(___CNT*50/1000));
				lcdpos (1,0); 
		if(LOCK_Time >= 0)
			 lcd_printf ("    %02d:%02d:%02d    ",(LOCK_Time/60/60)%60,
																										      (LOCK_Time/60)%60   ,																										   
																											     LOCK_Time%60);
//		lcdpos (1,0);  lcd_printf ("    %02d:%02d:%02d    ",(Fixture.Sample_Time/60/60)%60,
//																										  (Fixture.Sample_Time/60)%60   ,																										   
//																											Fixture.Sample_Time%60);
		if((___CNT*50) >= 5000){
			cyc4or3run ();
			lcd_printf ("请启动测试      ");
			cyc4or3run ();
			cyc4or3run ();
			lcd_printf ("    解锁成功    "); 
			cyc4or3run ();
			break;
		}		
	}
	Fixture.Sample_Time = 0;
	while(left_start_key == 0 ||right_start_key ==0 ) 
		delay_ms (10);
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
void Sample_Notice_Check(void ){
	if(Fixture.Sample_Notice == DISABLE )
		return ;
	if(Reg[Sample_Enable].Value  == ENABLE && Fixture.Status == RESET){
		if(Fixture.Sample_Time > (Reg[Sample_Cycle].Value*60-10)){
				Sample_Notice_Message();
		}
	}
}


