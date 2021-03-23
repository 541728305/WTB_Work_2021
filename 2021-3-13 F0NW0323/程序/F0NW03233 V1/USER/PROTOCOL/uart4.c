#include "uart4.h"
#include "usart.h"
#include "stm32f10x_dma.h"


extern  char  UART4_Buffer[USART1_Buffer_SIZE];
extern  uint8_t  UART4_REV_CNT;
/*****************************************************************************************
 * File Name     : uart1_init
 * Description   : 串口1初始化函数，初始化串口IO口.中断.波特率，使能为空闲中断，DMA接受串口数据 
 * Input         : baud，波特率设置/  receive  DMA_Channel5
 * return        : transmit DMA_Channel4
 * Author        : Morton
 * Date          : 2016.12.6
******************************************************************************************/
void uart4_init(u32 Baud){

		DMA_InitTypeDef DMA_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure; 
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	
	
		USART_DeInit(UART4);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOC, &GPIO_InitStructure);  
		
		NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
		NVIC_Init(&NVIC_InitStructure);	
		
		USART_InitStructure.USART_BaudRate = Baud;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
		USART_Init(UART4, &USART_InitStructure); 

		USART_Cmd(UART4, ENABLE);   

	//DMA_Receive
  	DMA_DeInit(DMA2_Channel3);	 //??DMA 2????	
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2,ENABLE); 
		
		DMA_InitStructure.DMA_PeripheralBaseAddr=(uint32_t)(&UART4->DR);
		DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)UART4_Buffer;
		DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;
		DMA_InitStructure.DMA_BufferSize= USART1_Buffer_SIZE;
		DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
		DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
		DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;
		DMA_InitStructure.DMA_Priority=DMA_Priority_Low; 
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		DMA_ITConfig(DMA2_Channel3,DMA_IT_TC,ENABLE) ; 
		DMA_Init(DMA2_Channel3,&DMA_InitStructure);   
		DMA_Cmd(DMA2_Channel3,ENABLE);
	//DMA_Transmit
	// 	DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)send_buf;
	// 	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralDST;
	// 	DMA_InitStructure.DMA_BufferSize= SEND_BUF_SIZE;
	// 	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	// 	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
	// 	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	// 	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	// 	DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;
	// 	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	// 	DMA_InitStructure.DMA_Priority=DMA_Priority_High; 
	// 	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE) ;
	// 	DMA_Init(DMA1_Channel4,&DMA_InitStructure);
	//	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE );
		USART_DMACmd(UART4,USART_DMAReq_Rx,ENABLE);
		USART_ITConfig(UART4, USART_IT_IDLE, ENABLE);
		USART_ClearFlag (UART4 ,USART_FLAG_IDLE );   

		USART_ITConfig(UART4,USART_IT_TC,DISABLE);
		USART_ITConfig(UART4,USART_IT_RXNE,DISABLE); 	             
}
/*********************************************************************************************
 * File Name     : USART1_IRQHandler
 * Description   : 无
 * Input         : 无
 * return        : 串口1空闲中断服务函数，用DMA接收数据
 * Author        : Morton
 * Date          : 2016.12.6
*********************************************************************************************/
void UART4_IRQHandler(void){	
		uint16_t tmp,counter=0;
		if(USART_GetITStatus(UART4 ,USART_IT_IDLE) == SET ){
			tmp =tmp;
			tmp=UART4->SR;
			tmp=UART4->DR;
			USART_ITConfig(UART4, USART_IT_IDLE, DISABLE );	
			DMA_Cmd(DMA2_Channel3,DISABLE);
			counter=USART1_Buffer_SIZE - DMA_GetCurrDataCounter(DMA2_Channel3);			
			UART4_Buffer[counter]='\0';
		//	Uart_printf(USART1,"%s",USART1_Buffer);	
			UART4_REV_CNT = 0x80 +counter ;
			DMA2_Channel3->CNDTR = USART1_Buffer_SIZE;
			DMA_Cmd(DMA2_Channel3,ENABLE );
			USART_ITConfig(UART4, USART_IT_IDLE, ENABLE  );
			USART_ClearITPendingBit (UART4,USART_IT_IDLE);
		}
} 




