#include "fre.h"


#include "stm32f10x_tim.h"
#include "lcd3033.h"
#include "delay.h"

#define TCS23_S0     PGout(2)
#define TCS23_S1     PGout(3) 


#define TCS23_S2     PCout(11) 
#define TCS23_S3     PCout(10) 

uint8_t  COUNTER_Finish_Flag = 0;
uint16_t TIM3_COUNTER = 0;
uint32_t CNT = 0;

/*********************************************************************************************
	* File Name     : Init_TIM3
	* Description   : 初始化定时器3
  * Input         : arr，自动重装载值，psc 预分频系数, type 用途：0，定时器，1计数器，2，PWM输出
	* return        : /
	* Version       : V1.0 
	* Author        : Morton 
	* Date          : 24-Oct-2018 
*********************************************************************************************/ 
void Init_TIM3(uint32_t arr ,uint32_t psc  ){
		TIM_Type type = COUNTER;
		NVIC_InitTypeDef NVIC_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); 
		if(type == TIMER ){
				TIM_DeInit (TIM3 ); 
				TIM_TimeBaseStructure.TIM_Period = arr; 
				TIM_TimeBaseStructure.TIM_Prescaler =psc; 
				TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
				TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
				TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
		}
		else if(type == COUNTER){
				GPIO_InitTypeDef GPIO_InitStructure;
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE );
				GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN_FLOATING ;
				GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2  ;
				GPIO_Init (GPIOD ,&GPIO_InitStructure);
				TIM_DeInit (TIM3 );
				TIM_TimeBaseStructure.TIM_Period = arr;
				TIM_TimeBaseStructure.TIM_Prescaler =psc;
				TIM_TimeBaseStructure.TIM_ClockDivision =0x0;
				TIM_TimeBaseStructure.TIM_CounterMode =TIM_CounterMode_Up ;
				TIM_TimeBaseInit(TIM3 ,&TIM_TimeBaseStructure);
				TIM_ETRClockMode2Config (TIM3,TIM_ExtTRGPSC_OFF ,TIM_ExtTRGPolarity_NonInverted ,0);
				TIM_SetCounter (TIM3 ,0);
				TIM_Cmd(TIM3 ,ENABLE );
				TIM3_COUNTER = 0;
		}		
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_Init(&NVIC_InitStructure);  
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  ); 
		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); 
		TIM_Cmd(TIM3, ENABLE);
}

/*********************************************************************************************
	* File Name     : TIM3_IRQHandler
	* Description   : TIM3_IRQHandler
  * Input         : /
	* return        : /
	* Version       : V1.0 
	* Author        : Morton 
	* Date          : 10-Oct-2018 
*********************************************************************************************/ 
void TIM3_IRQHandler(){
	if(TIM_GetITStatus(TIM3 ,TIM_IT_Update )!= RESET ){
			TIM3_COUNTER ++;
	}
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update  ); 
}
/*********************************************************************************************
	* File Name     : Init_TIM5
	* Description   : Init_TIM5
  * Input         : arr，自动重装载值，psc 预分频系数, type 用途：0，定时器，1计数器，2，PWM输出
	* return        : /
	* Version       : V1.0 
	* Author        : Morton 
	* Date          : 10-Oct-2018 
*********************************************************************************************/ 
void Init_TIM5(uint32_t arr ,uint32_t psc ){
		NVIC_InitTypeDef NVIC_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE); 

		TIM_DeInit (TIM5 ); 
		TIM_TimeBaseStructure.TIM_Period = arr; 
		TIM_TimeBaseStructure.TIM_Prescaler =psc; 
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
		TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 

		NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_Init(&NVIC_InitStructure);  
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update  ); 
		TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE ); 
		TIM_Cmd(TIM5, ENABLE);
}

/*********************************************************************************************
		* File Name     : TIM4_IRQHandler
		* Description   : 定时器4中断服务函数
	  * Input         : 无
		* return        : 无
  	* Version       : 
		* Author        : Morton
		* Date          : 2018/10/10
*********************************************************************************************/
void TIM5_IRQHandler(){
	if(TIM_GetITStatus(TIM5 ,TIM_IT_Update )!= RESET ){
			TIM_Cmd(TIM5, DISABLE );
			TIM_Cmd(TIM3, DISABLE );
			CNT  = TIM3_COUNTER*65536+(TIM3->CNT);
			COUNTER_Finish_Flag = 1;
	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update  ); 
}
/*********************************************************************************************
	* File Name     : Get_Pulse_Fre
	* Description   : nms 定时长度单位 ms 
  * Input         : 无
	* return        : 无
	* Version       : 
	* Author        : Morton
	* Date          : 2018/10/10
*********************************************************************************************/
double  Get_Pulse_Fre( double nms){
	double Fre = 0;
	COUNTER_Finish_Flag = 0;
	Init_TIM3(0xFFFF,0);//启动计数器
	Init_TIM5( nms*10-1,7199); //启动定时器
	while(COUNTER_Finish_Flag == 0);
	Fre = (double)CNT*1000.0/(double)nms;
	return Fre;
}
/*********************************************************************************************
	* File Name     : Get_Color_Fre
	* Description   : Color 颜色
  * Input         : 无
	* return        : 无
	* Version       : 
	* Author        : Morton
	* Date          : 2018/10/10
*********************************************************************************************/
double Get_Color_Fre( uint8_t Color ,double nMS,uint8_t  Timer){
	uint8_t i;
	double Fre = 0.0 ;
	if(Color == RED){
		TCS23_S2 = 0;
		TCS23_S3 = 0;
	}else if(Color == BLUE ){
		TCS23_S2 = 0;
		TCS23_S3 = 1;		
	}else if(Color == GREEN){
		TCS23_S2 = 1;
		TCS23_S3 = 1;		
	}else if(Color == WHITE){
		TCS23_S2 = 1;
		TCS23_S3 = 0;	
	}else{
		lcdreset ();
		lcd_printf ("颜色设置错误");
		while(1);
	}
	delay_ms(2);
	for( i = 0; i < Timer ; i ++){
		Fre += Get_Pulse_Fre(nMS);
	}
	return Fre/Timer;
}
/*************************************************************
	* File Name     : Init_Fre_Test
	* Description   : Init_Fre_Test
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 26-June-2019
*************************************************************/
void Init_Fre_Test (void){
	
	
	
}
