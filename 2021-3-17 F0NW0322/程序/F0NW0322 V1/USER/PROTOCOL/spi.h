#ifndef _SPI_H_
#define _SPI_H_
#include "stm32f10x_it.h" 

void SPI1_Config(void);
void SPI2_Init(void);
uint8_t SPI_SendByte(uint8_t byte);
void SPI2_SetSpeed(u8 SpeedSet);
u8 SPI2_ReadWriteByte(u8 TxData);
uint16_t SPI_Trans_Frame(uint8_t cmd,uint16_t data);

#endif
