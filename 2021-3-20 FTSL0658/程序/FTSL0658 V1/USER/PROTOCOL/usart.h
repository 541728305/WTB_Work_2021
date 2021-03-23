#ifndef _USART_DATA_H_
#define _USART_DATA_H_
#include "stdio.h"	
#include "sys.h" 
#define USART1_Buffer_SIZE  128
#define SEND_BUF_SIZE 128 

#define USART1_Baud  19200
#define USART2_Baud  38400
#define USART3_Baud  38400
void uart1_init(uint32_t );
void uart2_init(uint32_t );
void uart3_init(uint32_t );
void uart4_init(uint32_t );
void uart5_init(uint32_t );
void RESET_UART(USART_TypeDef *uart);
void Uart_printf(USART_TypeDef *huart, char *fmt,...);
void _Uart_printf(USART_TypeDef *huart, uint8_t *buf, uint8_t Num);

uint8_t Get_USART_buffer( USART_TypeDef *uart, const char *cmd, char *rev, uint16_t nms);
uint8_t _Get_USART_buffer( USART_TypeDef *uart, char *rev, uint16_t nms);
uint8_t Read_USART_buffer( USART_TypeDef *uart, char  *rev);

#endif 
