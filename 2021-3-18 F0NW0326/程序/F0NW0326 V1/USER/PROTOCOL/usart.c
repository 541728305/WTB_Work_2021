#include "usart.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "stm32f10x_dma.h"
#include "lcd3033.h"
#include "zdt.h"
#include "wtb.h"
#include "delay.h"
#define   RS485_EN
#define USART2_RS485_EN   PCout(0)

char  USART1_Buffer[USART1_Buffer_SIZE];
char  USART2_Buffer[USART1_Buffer_SIZE];
char  USART3_Buffer[USART1_Buffer_SIZE];
char  UART4_Buffer[USART1_Buffer_SIZE];
char  UART5_Buffer[USART1_Buffer_SIZE];

uint8_t  USART1_REV_CNT = RESET ;
uint8_t	 USART2_REV_CNT = RESET;
uint8_t	 USART3_REV_CNT = RESET;
uint8_t  UART4_REV_CNT  = RESET;
uint8_t  UART5_REV_CNT  = RESET;

const uint8_t HexTable[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};;
 
 
#pragma import(__use_no_semihosting)                             
struct __FILE 
{ 
	int handle; 
}; 
FILE __stdout;       
_sys_exit(int x) 
{ 
	x = x; 
} 
int fputc(int ch, FILE *f){ 
		lcdputchar((u8)(ch));
		return (ch);  
//		while((USART2->SR&0X40)==0);	
//		USART2->DR = (u8) ch;  
//		return ch;
}
/*****************************************************************************************
 * File Name     : COM_TransString
 * Description   : 串口打印函数
				USART-SR---9----8----7----6---5-----4-----3---2---1---0
				---------CTS--LBD--TXE--TC--RXNE--IDLE--ORE--NE--FE--PE 
 * Input         :  huart，串口 *fmt,输入字符格式
 * return        :  /
 * Version       :  V1.0
 * Author        :  Morton
 * Date          :  2018/6/25
****************************************************************************************/
void COM_TransString(USART_TypeDef *huart,char *str){
		while(*str != NULL){
				while((huart->SR&0X40)==0);
				huart->DR = (*str++ & (uint8_t)0xFF);
		}
		while((huart->SR&0X40)==0);
}

/*****************************************************************************************
 * File Name     : Uart_Putchar
 * Description   : 单字符打印函数
 * Input         : huart，串口 Char 字符
 * return        : 无
 * Version       : V1.0 
 * Author        : Morton
 * Date          : 2018/6/25
*********************************************************************************************/
void Uart_Putchar(USART_TypeDef *huart, uint8_t Char){
		while((huart->SR&0X40)==0);
		huart->DR = Char;
		while((huart->SR&0X40)==0);
}
 /******************************************************************************************
 * File Name     : Uart_Prinf_Hex
 * Description   : 打印HEX
 * Input         : uart 串口号 buf 待打印HEX CNT 数量  
 * return        : /
 * Version       : V1.0
 * Author        : Morton
 * Date          : 2019/1/4
*********************************************************************************************/
void  Uart_Prinf_Hex(USART_TypeDef *uart, char *buf, uint16_t CNT){
		uint16_t i;
		for( i = 0 ; i < CNT ; i ++){
		//	Uart_Putchar(uart ,'0');
		//	Uart_Putchar(uart ,'x');
			Uart_Putchar(uart ,HexTable[buf[i]>>4]);
			Uart_Putchar(uart ,HexTable[buf[i]&0xf ]);
			Uart_Putchar(uart ,' ');
		}
}

/*****************************************************************************************
 * File Name     :  UART_lcd_printf
 * Description   :  串口打印函数
 * Input         :  huart，串口 *fmt,输入字符格式
 * return        :  无
 * Version       :  V1.0
 * Author        :  Morton
 * Date          :  2018/6/25
****************************************************************************************/
void Uart_printf(USART_TypeDef *huart, char *fmt,...){
		va_list ap;	             /*This is support the format output*/ 
		char string[128];
		va_start(ap,fmt);
		vsprintf(string,fmt,ap); /* Store the string in the String buffer*/
		COM_TransString(huart,string);
		va_end(ap);
}
/*****************************************************************************************
 * File Name     : _Uart_lcd_printf
 * Description   : 串口打印函数
 * Input         : huart，串口 buf  Num
 * return        : 无
 * Version       :
 * Author        : Morton
 * Date          : 2018/6/25
 *********************************************************************************************/
void _Uart_printf(USART_TypeDef *huart, uint8_t *buf, uint8_t Num){
	uint8_t i;
	USART2_RS485_EN = 1;
	for( i = 0 ; i < Num ; i ++){
		while((huart->SR&0X40)==0);
		huart->DR = buf[i];
	}
	while((huart->SR&0X40)==0);
	USART2_RS485_EN = 0;
}
/*********************************************************************************************
	* File Name     : Get_USART_buffer
	* Description   : 发送指令并接受响应数据
  * Input         : cmd,发送指令直针nms 超时设定
  * return        : 收到数据返回0，超时返回1
	* Author        : Morton
	* Date          : 2018/8/13
*********************************************************************************************/
uint8_t Get_USART_buffer( USART_TypeDef *uart, const char *cmd, char *rev, uint16_t nms){
	uint16_t t=0,T_Max = nms/5;
	uint8_t Rev_CNT = 0;
	if(uart==USART1 ){
		memset (USART1_Buffer,0,USART1_Buffer_SIZE);	
		if(strlen(cmd))	
				Uart_printf (USART1,"%s",cmd); 
		USART1_REV_CNT = RESET;
	}
	if(uart==USART2 ){
		memset (USART2_Buffer,0,USART1_Buffer_SIZE);
		if(strlen(cmd))	
				Uart_printf (USART2,"%s",cmd); 
		USART2_REV_CNT = RESET;
	}
	if(uart==USART3 ){
		memset (USART3_Buffer,0,USART1_Buffer_SIZE);
		if(strlen(cmd))	
				Uart_printf (USART3,"%s",cmd); 
		USART3_REV_CNT = RESET;
	}
	if(uart==UART4 ){
		memset (UART4_Buffer,0,USART1_Buffer_SIZE);
		if(strlen(cmd))	
				Uart_printf (UART4,"%s",cmd); 
		UART4_REV_CNT = RESET;
	}
	if(uart==UART5 ){
		memset (UART5_Buffer,0,USART1_Buffer_SIZE);
		if(strlen(cmd))	
				Uart_printf (UART5,"%s",cmd); 
		UART5_REV_CNT = RESET;
	}	
	
	
	while(1){
			delay_ms (5);
			if(uart==USART1 && USART1_REV_CNT){
					Rev_CNT = USART1_REV_CNT&0x7F;
					strncpy(rev,USART1_Buffer,Rev_CNT);
					USART1_REV_CNT = RESET;
					break ;
			}
			if(uart==USART2 && USART2_REV_CNT){
					Rev_CNT = USART2_REV_CNT&0x7F;
					strncpy(rev,USART2_Buffer,Rev_CNT);
					USART2_REV_CNT = RESET;
					break ;
			}
			if(uart==USART3 && USART3_REV_CNT){
					Rev_CNT = USART3_REV_CNT&0x7F;
					strncpy(rev,USART3_Buffer,Rev_CNT);
					USART3_REV_CNT = RESET;
					break ;
			}
			if(uart==UART4 && UART4_REV_CNT){
					Rev_CNT = UART4_REV_CNT&0x7F;
					strncpy(rev,UART4_Buffer,Rev_CNT);
					UART4_REV_CNT = RESET;
					break ;
			}
			if(uart==UART5 && UART5_REV_CNT){
					Rev_CNT = UART5_REV_CNT&0x7F;
					strncpy(rev,UART5_Buffer,Rev_CNT);
					UART5_REV_CNT = RESET;
					break ;
			}
			t ++;
			if(t > T_Max){
				return 0;
			}
	}	
	return Rev_CNT;	
}
/***************************************************************************************
	* File Name     : _Get_USART_buffer
	* Description   : 发送指令并接受响应数据
  * Input         : uart 串口编号  rev 数据存储位置 nms 读取数据时间
  * return        : 收到数据返回字节数 ，超时返回0
	* Author        : Morton
	* Date          : 2018/8/13
**************************************************************************************/
uint8_t _Get_USART_buffer( USART_TypeDef *uart,  char *rev, uint16_t nms){
	uint16_t t=0,T_Max = nms/5,i;
	uint8_t Rev_CNT = 0;
	while(1){
			delay_ms (5);
			if(uart==USART1 && USART1_REV_CNT){
					Rev_CNT = USART1_REV_CNT&0x7F;
					for( i = 0; i < Rev_CNT ; i ++)
						rev[i] = USART1_Buffer [i];
					USART1_REV_CNT = RESET;
					break ;
			}
			if(uart==USART2 && USART2_REV_CNT){
					Rev_CNT = USART2_REV_CNT&0x7F;
					for( i = 0; i < Rev_CNT ; i ++)
						rev[i] = USART2_Buffer[i];
					USART2_REV_CNT = RESET;
					break ;
			}
			if(uart==USART3 && USART3_REV_CNT){
					Rev_CNT = USART3_REV_CNT&0x7F;
					for( i = 0; i < Rev_CNT ; i ++)
						rev[i] = USART3_Buffer[i];
					USART3_REV_CNT = RESET;
					break ;
			}
			if(uart==UART4 && UART4_REV_CNT){
					Rev_CNT = UART4_REV_CNT&0x7F;
					for( i = 0; i < Rev_CNT ; i ++)
						rev[i] = UART4_Buffer[i];
					UART4_REV_CNT = RESET;
					break ;
			}			
			if(uart==UART5 && UART5_REV_CNT){
					Rev_CNT = UART5_REV_CNT&0x7F;
					for( i = 0; i < Rev_CNT ; i ++)
						rev[i] = UART5_Buffer[i];
					UART5_REV_CNT = RESET;
					break ;
			}				
			
			t ++;
			if(t > T_Max){
				return 0;
			}
	}	
	return Rev_CNT;	
}
/*********************************************************************************************
	* File Name     : RESET_UART
	* Description   : 复位串口
  * Input         : 
  * return        : 
	* Author        : Morton
	* Date          : 2018/8/13
*********************************************************************************************/
void RESET_UART(USART_TypeDef *uart){
	if(uart==USART1 ){
		memset (USART1_Buffer,0,USART1_Buffer_SIZE);	
		USART1_REV_CNT = RESET;
	}
	if(uart==USART2 ){
		memset (USART2_Buffer,0,USART1_Buffer_SIZE);
		USART2_REV_CNT = RESET;
	}
	if(uart==USART3 ){
		memset (USART3_Buffer,0,USART1_Buffer_SIZE); 
		USART3_REV_CNT = RESET;
	}
	if(uart==UART4 ){
		memset (UART4_Buffer,0,USART1_Buffer_SIZE); 
		UART4_REV_CNT = RESET;
	}
	if(uart==UART5 ){
		memset (UART5_Buffer,0,USART1_Buffer_SIZE); 
		UART5_REV_CNT = RESET;
	}
}
/*********************************************************************************************
	* File Name     : Read_USART_buffer
	* Description   : 读取串口接收缓冲
  * Input         : uart 串口号 rev 接收3
  * return        : Rev_CNT 接收字节数
	* Author        : Morton
	* Date          : 2018/8/13
*********************************************************************************************/
uint8_t Read_USART_buffer( USART_TypeDef *uart, char  *rev){
	uint8_t Rev_CNT = 0,i = 0;
	if(uart == USART1 && USART1_REV_CNT){
			Rev_CNT = USART1_REV_CNT&0x7F;
			for( i = 0; i < Rev_CNT; i ++)
				rev[i] = USART1_Buffer[i];
			USART1_REV_CNT = RESET;
	}
	if(uart==USART2 && USART2_REV_CNT){
			Rev_CNT = USART2_REV_CNT&0x7F;
			for( i = 0; i < Rev_CNT; i ++)
				rev[i] = USART2_Buffer[i];
			USART2_REV_CNT = RESET;
	}
	if(uart==USART3 && USART3_REV_CNT){
			Rev_CNT = USART3_REV_CNT&0x7F;
			for( i = 0; i < Rev_CNT; i ++)
				rev[i] = USART3_Buffer[i];
			USART3_REV_CNT = RESET;
	}
	if(uart==UART4 && UART4_REV_CNT){
			Rev_CNT = UART4_REV_CNT&0x7F;
			for( i = 0; i < Rev_CNT; i ++)
				rev[i] = UART4_Buffer[i];
			UART4_REV_CNT = RESET;
	}
	if(uart==UART5 && UART5_REV_CNT){
			Rev_CNT = UART5_REV_CNT&0x7F;
			for( i = 0; i < Rev_CNT; i ++)
				rev[i] = UART5_Buffer[i];
			UART5_REV_CNT = RESET;
	}
	return Rev_CNT;	
}



