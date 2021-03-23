#include "usart.h"
#include "cmd.h"
#include "base_Config.h"
#include "stm32f10x_dma.h"

extern char  USART2_Buffer[USART1_Buffer_SIZE];
extern uint8_t  USART2_REV_CNT;
/*****************************************************************************************
  * File Name     : uart2_init
  * Description   : 串口2初始化函数，设置其波特率，使能为空闲中断，DMA接受串口数据 
										Usart1 receive  DMA_Channel6
										Usart1 transmit DMA_Channel7
  * Input         : bound，波特率设置/
  * return        : 无
  * Author        : Morton
  * Date          : 2016.12.6
****************************************************************************************/
void uart2_init(u32 Baud){
	
		DMA_InitTypeDef DMA_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	
		//PA2 Tx
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP ;	
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	  //PA3 Rx
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP ;	
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	
		USART_InitStructure.USART_BaudRate = Baud;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART2, &USART_InitStructure);
		
		//DMA_Receive
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE); 
		DMA_DeInit(DMA1_Channel6);        
		DMA_InitStructure.DMA_PeripheralBaseAddr = ((u32)(&(USART2->DR)));      
		DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART2_Buffer;
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;        
		DMA_InitStructure.DMA_BufferSize = USART1_Buffer_SIZE;       
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
		DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; 
		DMA_Init(DMA1_Channel6 , &DMA_InitStructure); 
		DMA_ClearFlag(DMA1_FLAG_TC6); 
		DMA_Cmd(DMA1_Channel6 , ENABLE) ;

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

		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
		NVIC_Init(&NVIC_InitStructure);	
		
		USART_ITConfig(USART2,USART_IT_IDLE,ENABLE); 
		USART_ITConfig(USART2,USART_IT_TXE,DISABLE); 
		USART_ITConfig(USART2,USART_IT_RXNE,DISABLE ); 	
		
		USART_ClearFlag(USART2 ,USART_FLAG_RXNE); 
		
		DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, DISABLE);
		USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE); 
		USART_Cmd(USART2, ENABLE);  	
}

/*****************************************************************************************
  * File Name     : USART2_IRQHandler
  * Description   : 串口2空闲中断服务函数，用于接受DMA数据
  * Input         : 无
  * return        : 无
  * Author        : Morton
  * Date          : 2016.12.6
*****************************************************************************************/
void USART2_IRQHandler(void){	
	u8 temp,counter;
	counter	=temp;	
	if(USART_GetITStatus(USART2 ,USART_IT_IDLE)==SET ){
			temp=USART2->SR;
			temp=USART2->DR;
			USART_ITConfig(USART2, USART_IT_IDLE, DISABLE );	
			DMA_Cmd(DMA1_Channel6,DISABLE);
			counter=USART1_Buffer_SIZE-DMA_GetCurrDataCounter(DMA1_Channel6);
			USART2_Buffer[counter]='\0';
			USART2_REV_CNT = 0x80+counter;
		
			if(Fixture.Comm_Uart == USART2 ){
				 Software_Cmd_Hander(USART2_Buffer,&USART2_REV_CNT);
			}
		
			DMA1_Channel6->CNDTR =USART1_Buffer_SIZE;
			DMA_Cmd(DMA1_Channel6,ENABLE );
			USART_ITConfig(USART2, USART_IT_IDLE, ENABLE  );
			USART_ClearITPendingBit (USART2 ,USART_IT_IDLE);
	}
}

