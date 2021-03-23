#include "timer.h"


uint32_t Sample_CNT = 0;

//void Init_TIM2(){
//	NVIC_InitTypeDef NVIC_InitStructure;
//	GPIO_InitTypeDef GPIO_InitStructure;
//  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM2_INT_Flag=0;
//	//Configuration TIM2 PA0 as Counter
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE );
//	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN_FLOATING ;
//	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0  ;
//	GPIO_InitStructure .GPIO_Speed =GPIO_Speed_50MHz ;
//	GPIO_Init (GPIOA ,&GPIO_InitStructure);
//	
//	TIM_DeInit (TIM2 );
//	TIM_TimeBaseStructure.TIM_Period =0xFFFF;
//	TIM_TimeBaseStructure.TIM_Prescaler =0x00;
//	TIM_TimeBaseStructure.TIM_ClockDivision =0x0;
//	TIM_TimeBaseStructure.TIM_CounterMode =TIM_CounterMode_Up ;
//	TIM_TimeBaseInit(TIM2 ,&TIM_TimeBaseStructure);
//	TIM_ETRClockMode2Config (TIM2,TIM_ExtTRGPSC_OFF ,TIM_ExtTRGPolarity_NonInverted ,0);
//	TIM_SetCounter (TIM2 ,0);
//	TIM_Cmd(TIM2 ,ENABLE );

//	//中断优先级NVIC设置
//	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
//	NVIC_Init(&NVIC_InitStructure);  
//	TIM_ClearITPendingBit(TIM2, TIM_IT_Update  ); 
//	
//	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); 
//	TIM_Cmd(TIM2, ENABLE);  				 
//}

 


// void TIM2_IRQHandler(void){
// 	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
//			TIM2_INT_Flag++;
// 			TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  
// 		}
// }



