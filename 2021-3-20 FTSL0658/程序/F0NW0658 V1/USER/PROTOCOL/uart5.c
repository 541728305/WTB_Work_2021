#include "usart.h"


extern  uint8_t  UART5_REV_CNT;
extern char  UART5_Buffer[USART1_Buffer_SIZE];
/*****************************************************************************************
 * File Name     : uart5_init
 * Description   : 串口1初始化函数，初始化串口IO口.中断.波特率，使能为空闲中断，DMA接受串口数据 
 * Input         : baud，波特率
 * return        : transmit DMA_Channel4
 * Author        : Morton
 * Date          : 2020.4.24
******************************************************************************************/
void uart5_init(uint32_t Baud)
{
		USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//??UART5,GPIOB??
    USART_DeInit(UART5);  
    //USART5_TX   PC12
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
    GPIO_Init(GPIOC, &GPIO_InitStructure); 
    //USART5_RX	  PD2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
 
    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
    NVIC_Init(&NVIC_InitStructure);	
 

    USART_InitStructure.USART_BaudRate = Baud;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
    USART_Init(UART5, &USART_InitStructure); 
		
 		USART_ITConfig(UART5,USART_IT_TC,DISABLE);
		USART_ITConfig(UART5, USART_IT_IDLE, ENABLE);
    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
    USART_Cmd(UART5, ENABLE);                    
}
#include "lcd3033.h"
uint8_t counter = 0 ;
//extern  uint8_t  UART5_REV_CNT;
//extern char  UART5_Buffer[USART1_Buffer_SIZE];
/*****************************************************************************************
 * File Name     : UART5_IRQHandler
 * Description   : UART5_IRQHandler
 * Input         : /
 * return        : /
 * Author        : Morton
 * Date          : 2020.4.24
******************************************************************************************/
void UART5_IRQHandler(void)
{
    if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET){ 			
			UART5_Buffer[counter] = UART5->DR ;				
			counter ++ ; 
			USART_ITConfig(UART5, USART_IT_IDLE, ENABLE);
			USART_ClearITPendingBit (UART5,USART_IT_RXNE);				
    }
		if(USART_GetITStatus(UART5, USART_IT_IDLE) != RESET){ 
			UART5_REV_CNT = 0x80 +counter ;
			UART5_Buffer[counter] = '\0';	
//			Uart_printf(UART5,"%s",UART5_Buffer);	
      counter = 0;
			USART_ITConfig(UART5, USART_IT_IDLE, DISABLE);
			USART_ClearITPendingBit (UART5,USART_IT_IDLE);			
    }
}
