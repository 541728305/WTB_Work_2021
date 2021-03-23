#include "usart.h"
#include "cmd.h"
#include "base_Config.h"
#include "stm32f10x_dma.h"

extern  char     USART3_Buffer[USART1_Buffer_SIZE];
extern  uint8_t  USART3_REV_CNT;
/*************************************************************************************
 * File Name     : uart3_init
 * Description   : 串口3初始化函数，设置其波特率，使能为空闲中断，DMA接受串口数据			
									 Usart3 receive  DMA_Channel2
									 Usart3 transmit DMA_Channel3
 * Input         : bound，波特率设置/
 * return        : 无
 * Author        : Morton
 * Date          : 2016.12.6
****************************************************************************************/
void uart3_init(u32 Baud){
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef  USART_InitStructure;
			 
		DMA_InitTypeDef DMA_InitStructure;	
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB ,ENABLE);  
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE) ;
		//usart3_tx  PB 10 
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;	
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP; // can't be set on GPIO_Mode_Out_PP
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOB , &GPIO_InitStructure);
		//usart3_rx PB 11
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
		GPIO_Init(GPIOB ,&GPIO_InitStructure);
		//usart3 mode config
		USART_InitStructure.USART_BaudRate=Baud;
		USART_InitStructure.USART_WordLength=USART_WordLength_8b;
		USART_InitStructure.USART_StopBits=USART_StopBits_1;
		USART_InitStructure.USART_Parity=USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
		USART_Init(USART3,&USART_InitStructure); 

		USART_ITConfig(USART3,USART_IT_TC,DISABLE);
		USART_ITConfig(USART3,USART_IT_RXNE,DISABLE); 	   		
		USART_ITConfig(USART3,USART_IT_IDLE,ENABLE);	

		NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE); 
		//DMA_Receive configure
		DMA_DeInit(DMA1_Channel3);  
		DMA_InitStructure.DMA_PeripheralBaseAddr=(uint32_t)(&USART3->DR);
		DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)USART3_Buffer;
		DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;
		DMA_InitStructure.DMA_BufferSize= USART1_Buffer_SIZE;
		DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
		DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
		DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;
		DMA_InitStructure.DMA_Priority=DMA_Priority_Low; 
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	//		DMA_ITConfig(DMA1_Channel3,DMA_IT_TC,ENABLE) ; //enable DMA Channel3 complete transfer interrupt
		DMA_Init(DMA1_Channel3,&DMA_InitStructure);
		DMA_Cmd(DMA1_Channel3,ENABLE);

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
// 	DMA_ITConfig(DMA1_Channel2,DMA_IT_TC,ENABLE) ;
// 	DMA_Init(DMA1_Channel2,&DMA_InitStructure);

// 	NVIC_InitStructure.NVIC_IRQChannel=DMA1_Channel2_IRQn;
// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
// 	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
// 	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
// 	NVIC_Init(&NVIC_InitStructure);
//	NVIC_InitStructure.NVIC_IRQChannel=DMA1_Channel3_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure);	

		USART_ITConfig(USART3,USART_IT_IDLE,ENABLE); 
		USART_ITConfig(USART3,USART_IT_TXE,DISABLE); 
		USART_ITConfig(USART3,USART_IT_RXNE,DISABLE ); 
		
		USART_ClearFlag(USART3 ,USART_FLAG_RXNE); 
		
		DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, DISABLE);

		USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);
		USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);	//enable DMA received 
		USART_Cmd(USART3,ENABLE);	
}
/********************************************************************************************
 * File Name     : USART3_IRQHandler
 * Description   : 串口3空闲中断服务函数，用于接受DMA数据
 * Input         : 无
 * return        : 无
 * Author        : Morton
 * Date          : 2016.12.6
********************************************************************************************/
void USART3_IRQHandler(void){	
	u8 temp,counter;
	counter	=temp;	
	if(USART_GetITStatus(USART3 ,USART_IT_IDLE)==SET ){
			temp=USART3->SR;
			temp=USART3->DR;
			USART_ITConfig(USART3, USART_IT_IDLE, DISABLE );	
			DMA_Cmd(DMA1_Channel3,DISABLE);
			counter=USART1_Buffer_SIZE-DMA_GetCurrDataCounter(DMA1_Channel3);
			USART3_Buffer[counter]='\0';
			USART3_REV_CNT = 0x80+ counter;
		
			if(Fixture.Comm_Uart == USART3 ){
				 Software_Cmd_Hander(USART3_Buffer,&USART3_REV_CNT);
			}
		
			DMA1_Channel3->CNDTR =USART1_Buffer_SIZE;
			DMA_Cmd(DMA1_Channel3,ENABLE );
			USART_ITConfig(USART3, USART_IT_IDLE, ENABLE  );
			USART_ClearITPendingBit (USART3 ,USART_IT_IDLE);
	}
}



