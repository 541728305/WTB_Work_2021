#include "usart.h"
#include "cmd.h"
#include "base_Config.h"
#include "stm32f10x_dma.h"


extern  char  USART1_Buffer[USART1_Buffer_SIZE];
extern  uint8_t  USART1_REV_CNT;
/*****************************************************************************************
 * File Name     : uart1_init
 * Description   : 串口1初始化函数，初始化串口IO口.中断.波特率，使能为空闲中断，DMA接受串口数据 
 * Input         : baud，波特率设置/  receive  DMA_Channel5
 * return        : transmit DMA_Channel4
 * Author        : Morton
 * Date          : 2016.12.6
******************************************************************************************/
void uart1_init(u32 Baud){
		DMA_InitTypeDef DMA_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure; 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	
		
		USART_DeInit(USART1);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStructure);  
		
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
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
		USART_Init(USART1, &USART_InitStructure); 

		USART_Cmd(USART1, ENABLE);   

	//DMA_Receive
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE); 
		DMA_InitStructure.DMA_PeripheralBaseAddr=(uint32_t)(&USART1->DR);
		DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)USART1_Buffer;
		DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;
		DMA_InitStructure.DMA_BufferSize= USART1_Buffer_SIZE;
		DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
		DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
		DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;
		DMA_InitStructure.DMA_Priority=DMA_Priority_Low; 
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		DMA_ITConfig(DMA1_Channel5,DMA_IT_TC,ENABLE) ; 
		DMA_Init(DMA1_Channel5,&DMA_InitStructure);   
		DMA_Cmd(DMA1_Channel5,ENABLE);
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
		USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
		USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
		USART_ClearFlag (USART1 ,USART_FLAG_IDLE );   

		USART_ITConfig(USART1,USART_IT_TC,DISABLE);
		USART_ITConfig(USART1,USART_IT_RXNE,DISABLE); 	             
}
/*********************************************************************************************
 * File Name     : USART1_IRQHandler
 * Description   : 无
 * Input         : 无
 * return        : 串口1空闲中断服务函数，用DMA接收数据
 * Author        : Morton
 * Date          : 2016.12.6
*********************************************************************************************/
void USART1_IRQHandler(void){	
		uint16_t tmp,counter=0;
		if(USART_GetITStatus(USART1 ,USART_IT_IDLE) == SET ){
			tmp =tmp;
			tmp=USART1->SR;
			tmp=USART1->DR;
			USART_ITConfig(USART1, USART_IT_IDLE, DISABLE );	
			DMA_Cmd(DMA1_Channel5,DISABLE);
			counter=USART1_Buffer_SIZE - DMA_GetCurrDataCounter(DMA1_Channel5);			
			USART1_Buffer[counter]='\0';
//		Uart_printf(USART1,"%s",USART1_Buffer);	
			USART1_REV_CNT |= 0x80 +counter ;
			if(Fixture.Comm_Uart == USART1 ){
				 Software_Cmd_Hander(USART1_Buffer,&USART1_REV_CNT);
			}
			DMA1_Channel5->CNDTR = USART1_Buffer_SIZE;
			DMA_Cmd(DMA1_Channel5,ENABLE );
			USART_ITConfig(USART1, USART_IT_IDLE, ENABLE  );
			USART_ClearITPendingBit (USART1,USART_IT_IDLE);
		}
} 




